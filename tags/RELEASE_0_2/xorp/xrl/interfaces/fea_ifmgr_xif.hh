/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/fea_ifmgr_xif.hh,v 1.5 2003/02/06 22:21:25 hodson Exp $
 */

#ifndef __XRL_INTERFACES_FEA_IFMGR_XIF_HH__
#define __XRL_INTERFACES_FEA_IFMGR_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifFeaIfmgr"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlIfmgrV0p1Client {
public:
    XrlIfmgrV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlIfmgrV0p1Client() {}

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB0;

    bool send_get_all_interface_names(
	const char*	target_name, 
	const CB0&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB1;

    bool send_get_configured_interface_names(
	const char*	target_name, 
	const CB1&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB2;

    bool send_get_all_vif_names(
	const char*	target_name, 
	const string&	ifname, 
	const CB2&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB3;

    bool send_get_configured_vif_names(
	const char*	target_name, 
	const string&	ifname, 
	const CB3&	cb
    );

    typedef XorpCallback6<void, const XrlError&, const bool*, const bool*, const bool*, const bool*, const bool*>::RefPtr CB4;

    bool send_get_vif_flags4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB4&	cb
    );

    typedef XorpCallback5<void, const XrlError&, const bool*, const bool*, const bool*, const bool*>::RefPtr CB5;

    bool send_get_vif_flags6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB5&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB6;

    bool send_get_all_vif_addresses4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const CB6&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB7;

    bool send_get_configured_vif_addresses4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const CB7&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB8;

    bool send_get_all_vif_addresses6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const CB8&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr CB9;

    bool send_get_configured_vif_addresses6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const CB9&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr CB10;

    bool send_get_interface_enabled(
	const char*	target_name, 
	const string&	ifname, 
	const CB10&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const Mac*>::RefPtr CB11;

    bool send_get_mac(
	const char*	target_name, 
	const string&	ifname, 
	const CB11&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr CB12;

    bool send_get_mtu(
	const char*	target_name, 
	const string&	ifname, 
	const CB12&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr CB13;

    bool send_get_vif_enabled(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const CB13&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr CB14;

    bool send_get_prefix4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB14&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const IPv4*>::RefPtr CB15;

    bool send_get_broadcast4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB15&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const IPv4*>::RefPtr CB16;

    bool send_get_endpoint4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB16&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr CB17;

    bool send_get_prefix6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB17&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const IPv6*>::RefPtr CB18;

    bool send_get_endpoint6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB18&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr CB19;

    bool send_start_transaction(
	const char*	target_name, 
	const CB19&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB20;

    bool send_commit_transaction(
	const char*	target_name, 
	const uint32_t&	tid, 
	const CB20&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB21;

    bool send_abort_transaction(
	const char*	target_name, 
	const uint32_t&	tid, 
	const CB21&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB22;

    bool send_create_interface(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const CB22&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB23;

    bool send_delete_interface(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const CB23&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB24;

    bool send_set_interface_enabled(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const bool&	enabled, 
	const CB24&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB25;

    bool send_set_mac(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const Mac&	mac, 
	const CB25&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB26;

    bool send_set_mtu(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const uint32_t&	mtu, 
	const CB26&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB27;
    /**
     *  Send Xrl intended to:
     *  
     *  Create a vif
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param ifname the name of the physical interface associated with the
     *  new vif.
     *  
     *  @param vif name for new vif, must be unique across all the vifs in the
     *  system.
     */
    bool send_create_vif(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const CB27&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB28;

    bool send_delete_vif(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const CB28&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB29;

    bool send_set_vif_enabled(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const bool&	enabled, 
	const CB29&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB30;

    bool send_create_address4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB30&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB31;

    bool send_delete_address4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB31&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB32;

    bool send_set_address_enabled4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const bool&	enabled, 
	const CB32&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr CB33;

    bool send_get_address_enabled4(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const CB33&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB34;

    bool send_set_prefix4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const uint32_t&	prefix, 
	const CB34&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB35;

    bool send_set_broadcast4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const IPv4&	broadcast, 
	const CB35&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB36;

    bool send_set_endpoint4(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv4&	address, 
	const IPv4&	endpoint, 
	const CB36&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB37;

    bool send_create_address6(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB37&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB38;

    bool send_delete_address6(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB38&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB39;

    bool send_set_address_enabled6(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const bool&	enabled, 
	const CB39&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr CB40;

    bool send_get_address_enabled6(
	const char*	target_name, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const CB40&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB41;

    bool send_set_prefix6(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const uint32_t&	prefix, 
	const CB41&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB42;

    bool send_set_endpoint6(
	const char*	target_name, 
	const uint32_t&	tid, 
	const string&	ifname, 
	const string&	vif, 
	const IPv6&	address, 
	const IPv6&	endpoint, 
	const CB42&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB43;
    /**
     *  Send Xrl intended to:
     *  
     *  Register network interface observer
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param clientname name of xrl entity supporting fea_ifmgr_client.xif
     *  methods.
     */
    bool send_register_client(
	const char*	target_name, 
	const string&	clientname, 
	const CB43&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB44;
    /**
     *  Send Xrl intended to:
     *  
     *  Unregister network interface observer. This method is not strictly
     *  necessary, the fea will remove the interface observer from it's list of
     *  known observers if interface update XRLs fail.
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_unregister_client(
	const char*	target_name, 
	const string&	clientname, 
	const CB44&	cb
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

    void unmarshall4(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB4		cb
    );

    void unmarshall5(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB5		cb
    );

    void unmarshall6(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB6		cb
    );

    void unmarshall7(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB7		cb
    );

    void unmarshall8(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB8		cb
    );

    void unmarshall9(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB9		cb
    );

    void unmarshall10(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB10		cb
    );

    void unmarshall11(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB11		cb
    );

    void unmarshall12(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB12		cb
    );

    void unmarshall13(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB13		cb
    );

    void unmarshall14(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB14		cb
    );

    void unmarshall15(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB15		cb
    );

    void unmarshall16(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB16		cb
    );

    void unmarshall17(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB17		cb
    );

    void unmarshall18(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB18		cb
    );

    void unmarshall19(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB19		cb
    );

    void unmarshall20(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB20		cb
    );

    void unmarshall21(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB21		cb
    );

    void unmarshall22(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB22		cb
    );

    void unmarshall23(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB23		cb
    );

    void unmarshall24(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB24		cb
    );

    void unmarshall25(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB25		cb
    );

    void unmarshall26(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB26		cb
    );

    void unmarshall27(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB27		cb
    );

    void unmarshall28(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB28		cb
    );

    void unmarshall29(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB29		cb
    );

    void unmarshall30(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB30		cb
    );

    void unmarshall31(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB31		cb
    );

    void unmarshall32(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB32		cb
    );

    void unmarshall33(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB33		cb
    );

    void unmarshall34(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB34		cb
    );

    void unmarshall35(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB35		cb
    );

    void unmarshall36(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB36		cb
    );

    void unmarshall37(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB37		cb
    );

    void unmarshall38(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB38		cb
    );

    void unmarshall39(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB39		cb
    );

    void unmarshall40(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB40		cb
    );

    void unmarshall41(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB41		cb
    );

    void unmarshall42(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB42		cb
    );

    void unmarshall43(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB43		cb
    );

    void unmarshall44(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB44		cb
    );

};

#endif /* __XRL_INTERFACES_FEA_IFMGR_XIF_HH__ */
