// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
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

#ident "$XORP: xorp/fea/xrl_ifupdate.cc,v 1.1.1.1 2002/12/11 23:56:03 hodson Exp $"

#include "config.h"
#include "fea_module.h"
#include "libxorp/xlog.h"

#include "xrl_ifupdate.hh"
#include "xrl/interfaces/fea_ifmgr_client_xif.hh"

/******************************************************************************
 *
 * This implementation has the bug/feature that it simply signals a change
 * has occurred.  The receiver of that information then has to query what
 * the delta is.  This means an extra rtt plus processing in propapating
 * a piece of information that is time sensitive.  This design is therefore
 * not ideal, and should probably be re-evaluated when the FEA has settled
 * down.
 *
 *****************************************************************************/

/*
 * These definitions must match enumerations in:
 * 	${XORP}/xrl/fea_ifmgr_clientspy.xif
 */
enum XrlIfUpdate {
    CREATED = 1,
    DELETED = 2,
    CHANGED = 3
};

/*
 * Helper function to map Fea's concept of an event into Xrl enumerated value
 */
static XrlIfUpdate
xrl_update(IfConfigUpdateReporterBase::Update u)
{
    switch (u) {
    case IfConfigUpdateReporterBase::CREATED:
	return CREATED;
    case IfConfigUpdateReporterBase::DELETED:
	return DELETED;
    case IfConfigUpdateReporterBase::CHANGED:
	return CHANGED;
    }
    return CHANGED; /* Fix for compiler warning */
}

/* ------------------------------------------------------------------------- */
/* XrlIfConfigUpdateReporter */

XrlIfConfigUpdateReporter::XrlIfConfigUpdateReporter(XrlRouter& r) : _rtr(r)
{}

bool
XrlIfConfigUpdateReporter::add_reportee(const string& tgt)
{
    if (find(_tgts.begin(), _tgts.end(), tgt) != _tgts.end())
	return false;
    _tgts.push_back(tgt);
    return true;
}

bool
XrlIfConfigUpdateReporter::remove_reportee(const string& tgt)
{
    TgtList::iterator ti = find(_tgts.begin(), _tgts.end(), tgt);
    if (ti == _tgts.end())
	return false;
    _tgts.erase(ti);
    return true;
}

void
XrlIfConfigUpdateReporter::interface_update(const string& ifname,
					    const Update& u)
{
    XrlFeaIfmgrClientV0p1Client c(&_rtr);

    for (TgtList::const_iterator ti = _tgts.begin(); ti != _tgts.end(); ++ti) {
	c.send_interface_update(ti->c_str(), ifname, xrl_update(u),
	    callback(this, &XrlIfConfigUpdateReporter::xrl_sent, *ti));
    }
}

void
XrlIfConfigUpdateReporter::vif_update(const string& ifname,
				      const string& vifname,
				      const Update& u)
{
    XrlFeaIfmgrClientV0p1Client c(&_rtr);

    for (TgtList::const_iterator ti = _tgts.begin(); ti != _tgts.end(); ++ti) {
	c.send_vif_update(ti->c_str(), ifname, vifname, xrl_update(u),
	    callback(this, &XrlIfConfigUpdateReporter::xrl_sent, *ti));
    }
}

void
XrlIfConfigUpdateReporter::vifaddr4_update(const string& ifname,
					   const string& vifname,
					   const IPv4&	 ip,
					   const Update& u)
{
    XrlFeaIfmgrClientV0p1Client c(&_rtr);

    for (TgtList::const_iterator ti = _tgts.begin(); ti != _tgts.end(); ++ti) {
	c.send_vifaddr4_update(ti->c_str(), ifname, vifname, ip, xrl_update(u),
	    callback(this, &XrlIfConfigUpdateReporter::xrl_sent, *ti));
    }
}

void
XrlIfConfigUpdateReporter::vifaddr6_update(const string& ifname,
					   const string& vifname,
					   const IPv6&	 ip,
					   const Update& u)
{
    XrlFeaIfmgrClientV0p1Client c(&_rtr);

    for (TgtList::const_iterator ti = _tgts.begin(); ti != _tgts.end(); ++ti) {
	c.send_vifaddr6_update(ti->c_str(), ifname, vifname, ip, xrl_update(u),
	    callback(this, &XrlIfConfigUpdateReporter::xrl_sent, *ti));
    }
}

void
XrlIfConfigUpdateReporter::xrl_sent(const XrlError& e, const string tgt)
{
    if (e != XrlError::OKAY()) {
	//
	// On an error we should think about removing target or at least
	// putting it on probation to be removed.
	//
	XLOG_ERROR("Error sending update to %s (%s), continuing.",
		   tgt.c_str(), e.str().c_str());
    }
}
