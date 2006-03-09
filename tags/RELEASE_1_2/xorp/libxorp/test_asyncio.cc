// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// Copyright (c) 2001-2005 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/libxorp/test_asyncio.cc,v 1.11 2005/08/30 01:32:36 pavlin Exp $"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "libxorp_module.h"

#include "libxorp/xorp.h"
#include "libxorp/debug.h"
#include "libxorp/xorpfd.hh"
#include "libxorp/xlog.h"
#include "libxorp/random.h"
#include "libcomm/comm_api.h"

#include "asyncio.hh"

static const int TIMEOUT_MS	  = 2000;
static const int MAX_ITERS	  = 50;
static const int MAX_BUFFERS	  = 200;
static const int MAX_BUFFER_BYTES = 1000000;

#ifdef DETAILED_DEBUG
static int bytes_read = 0;
static int bytes_written = 0;
#endif

static void
writer_check(AsyncFileReader::Event ev,
	     const uint8_t* buf, size_t bytes, size_t offset,
	     uint8_t* exp_buf,XorpTimer* t)
{
    assert(ev == AsyncFileWriter::DATA || ev == AsyncFileWriter::FLUSHING);
    assert(buf == exp_buf);
    assert(offset <= bytes);

#ifdef DETAILED_DEBUG
    bytes_written += bytes;
#endif

    // Defer timeout
    t->schedule_after_ms(TIMEOUT_MS);
}

static void
reader_check(AsyncFileReader::Event ev,
	     const uint8_t* buf, size_t bytes, size_t offset, 
	     uint8_t* exp_buf, uint8_t data_value, XorpTimer* t)
{
    assert(ev == AsyncFileReader::DATA || ev == AsyncFileReader::FLUSHING);
    assert(buf == exp_buf);
    assert(offset <= bytes);

    // Defer timeout
    t->schedule_after_ms(TIMEOUT_MS);
    
    if (offset == bytes) {
#ifdef DETAILED_DEBUG
    	bytes_read += bytes;
#endif
	// Check buffer is filled with expected value (== iteration no)
	for (size_t i = 0; i < bytes; i++) {
	    assert(buf[i] == data_value);
	}
    }
}

static void
reader_eof_check(AsyncFileReader::Event ev,
		 const uint8_t* buf, size_t bytes, size_t offset,
		 uint8_t* exp_buf, bool* done)
{
    assert(ev == AsyncFileReader::END_OF_FILE);
    assert(buf == exp_buf);
    assert(offset <= bytes);
    assert(offset == 0);
    *done = true;
}

static void
timeout()
{
    fprintf(stderr, "Timed out");
    exit(-1);
}

static void
run_test()
{
    EventLoop e;

    xsock_t s[2]; // pair of sockets - one for read, one for write
    if (comm_sock_pair(AF_UNIX, SOCK_STREAM, 0, s) != XORP_OK) {
	puts(comm_get_last_error_str());
	exit(-1);
    }
    if (comm_sock_set_blocking(s[0], 0) != XORP_OK) {
	puts(comm_get_last_error_str());
	exit(-1);
    }
    if (comm_sock_set_blocking(s[1], 0) != XORP_OK) {
	puts(comm_get_last_error_str());
	exit(-1);
    }

    AsyncFileWriter afw(e, s[0]);
    AsyncFileReader afr(e, s[1]);

    static uint8_t msg[MAX_BUFFER_BYTES];
    const size_t msg_bytes = sizeof(msg) / sizeof(msg[0]);

    XorpTimer t = e.new_oneoff_after_ms(TIMEOUT_MS, callback(timeout));

    uint32_t bytes_transferred = 0;
    for (int i = 0; i <= MAX_ITERS; i++) {
	// set value of each bytes in buffer to be test iteration number
	// then we can check for corruption
	memset(msg, i, msg_bytes); 
	bool was_started = afr.start();
	UNUSED(was_started);
	assert(was_started == false); // can't start no buffer
	// Choose number of buffers to use
	int n = 1 + (random() % MAX_BUFFERS);
	printf("%d ", n); fflush(stdout);
	while (n >= 0) {
	    // Size of buffer add must be at least 1
	    size_t b_bytes = 1 + (rand() % (MAX_BUFFER_BYTES - 1)); 
	    afw.add_buffer(msg, b_bytes, 
			   callback(&writer_check, msg, &t));
	    afr.add_buffer(msg, b_bytes,
 			   callback(&reader_check, msg, (uint8_t)i, &t));
	    n--;
	    bytes_transferred += b_bytes;
	}

	// XXX: Because of the new ioevent semantics, start and stop
	// calls must be exactly matched in Win32.
	afr.stop();

	afw.start(); afw.stop(); afw.start(); // Just walk thru starting and
	afr.start(); afr.stop(); afr.start(); // stopping...

	while (afw.running() || afr.running()) {
	    e.run();
#ifdef DETAILED_DEBUG
	    printf("bytes_read = %d bytes_written = %d\n",
			bytes_read, bytes_written);
	    fflush(stdout);
#endif
	}
	assert(afw.buffers_remaining() == 0 && afr.buffers_remaining() == 0);

	afw.stop(); // utterly redundant call to stop()
	afr.stop(); // utterly redundant call to stop()

	assert(afw.start() == false); // can't start, no buffers
	assert(afr.start() == false); // can't start, no buffers
    }

    // test END_OF_FILE
    comm_close(s[0]); // close writer's file descriptor

    bool eof_test_done = false;
    afr.add_buffer(msg, msg_bytes,
		   callback(reader_eof_check, msg, &eof_test_done));
    afr.start();
    while (eof_test_done == false)
	e.run();

    printf("\nTransfered %u bytes between AsyncFileWriter and "
	   "AsyncFileReader.\n", XORP_UINT_CAST(bytes_transferred));
}

int
main(int /* argc */, char *argv[]) 
{

    comm_init();

    //
    // Initialize and start xlog
    //
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);		// Least verbose messages
    // XXX: verbosity of the error messages temporary increased
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    
    xlog_add_default_output();
    xlog_start();

    // Some of test generates warnings - under normal circumstances the
    // end user wants to know, but here not.
    xlog_disable(XLOG_LEVEL_WARNING);
    run_test();

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();

    comm_exit();
    
    return 0;
}