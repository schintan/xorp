/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/fea_ifmgr_client_xif.hh,v 1.4 2003/02/06 22:21:25 hodson Exp $
 */

#ifndef __XRL_INTERFACES_FEA_IFMGR_CLIENT_XIF_HH__
#define __XRL_INTERFACES_FEA_IFMGR_CLIENT_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifFeaIfmgrClient"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlFeaIfmgrClientV0p1Client {
public:
    XrlFeaIfmgrClientV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlFeaIfmgrClientV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB0;

    bool send_interface_update(
	const char*	target_name, 
	const string&	ifname, 
	const uint32_t&	event, 
	const CB0&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB1;

    bool send_vif_update(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vifname, 
	const uint32_t&	event, 
	const CB1&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB2;

    bool send_vifaddr4_update(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vifname, 
	const IPv4&	addr, 
	const uint32_t&	event, 
	const CB2&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB3;

    bool send_vifaddr6_update(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vifname, 
	const IPv6&	addr, 
	const uint32_t&	event, 
	const CB3&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall0(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB0		cb
    );

    void unmarshall1(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB1		cb
    );

    void unmarshall2(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB2		cb
    );

    void unmarshall3(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB3		cb
    );

};

#endif /* __XRL_INTERFACES_FEA_IFMGR_CLIENT_XIF_HH__ */
