/*
 * Copyright (c) 2001-2004 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP$
 */

#ifndef __XRL_INTERFACES_PACKET_ACL_XIF_HH__
#define __XRL_INTERFACES_PACKET_ACL_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifPacketAcl"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlPacketAclV0p1Client {
public:
    XrlPacketAclV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlPacketAclV0p1Client() {}

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr GetBackendCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the name of the ACL backend currently in use.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_backend(
	const char*	target_name,
	const GetBackendCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetBackendCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set the underlying packet ACL backend type in use. NOTE: If XORP rules
     *  currently exist, this operation will perform an implicit flush and
     *  reload when switching to the new provider.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_backend(
	const char*	target_name,
	const string&	name,
	const SetBackendCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr GetVersionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the underlying packet ACL provider version in use.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_version(
	const char*	target_name,
	const GetVersionCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr StartTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Start ACL transaction.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_start_transaction(
	const char*	target_name,
	const StartTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CommitTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Commit ACL transaction.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     */
    bool send_commit_transaction(
	const char*	target_name,
	const uint32_t&	tid,
	const CommitTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AbortTransactionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Abort ACL transaction.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     */
    bool send_abort_transaction(
	const char*	target_name,
	const uint32_t&	tid,
	const AbortTransactionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddEntry4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an IPv4 family ACL entry.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     *
     *  @param ifname Name of the interface where this filter is to be applied.
     *
     *  @param vifname Name of the vif where this filter is to be applied.
     *
     *  @param src Source IPv4 address with network prefix.
     *
     *  @param dst Destination IPv4 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param action Action taken when this filter is matched.
     */
    bool send_add_entry4(
	const char*	target_name,
	const uint32_t&	tid,
	const string&	ifname,
	const string&	vifname,
	const IPv4Net&	src,
	const IPv4Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const string&	action,
	const AddEntry4CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteEntry4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete an IPv4 family ACL entry.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     *
     *  @param ifname Name of the interface where this filter is to be deleted.
     *
     *  @param vifname Name of the vif where this filter is to be deleted.
     *
     *  @param src Source IPv4 address with network prefix.
     *
     *  @param dst Destination IPv4 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     */
    bool send_delete_entry4(
	const char*	target_name,
	const uint32_t&	tid,
	const string&	ifname,
	const string&	vifname,
	const IPv4Net&	src,
	const IPv4Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const DeleteEntry4CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteAllEntries4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete all IPv4 family ACL entries.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     */
    bool send_delete_all_entries4(
	const char*	target_name,
	const uint32_t&	tid,
	const DeleteAllEntries4CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddEntry6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an IPv6 family ACL entry.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     *
     *  @param ifname Name of the interface where this filter is to be applied.
     *
     *  @param vifname Name of the vif where this filter is to be applied.
     *
     *  @param src Source IPv6 address with network prefix.
     *
     *  @param dst Destination IPv6 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param action Action taken when this filter is matched.
     */
    bool send_add_entry6(
	const char*	target_name,
	const uint32_t&	tid,
	const string&	ifname,
	const string&	vifname,
	const IPv6Net&	src,
	const IPv6Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const string&	action,
	const AddEntry6CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteEntry6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete an IPv6 family ACL entry.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     *
     *  @param ifname Name of the interface where this filter is to be deleted.
     *
     *  @param vifname Name of the vif where this filter is to be deleted.
     *
     *  @param src Source IPv6 address with network prefix.
     *
     *  @param dst Destination IPv6 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     */
    bool send_delete_entry6(
	const char*	target_name,
	const uint32_t&	tid,
	const string&	ifname,
	const string&	vifname,
	const IPv6Net&	src,
	const IPv6Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const DeleteEntry6CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteAllEntries6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete all IPv6 family ACL entries.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param tid the transaction ID for this operation.
     */
    bool send_delete_all_entries6(
	const char*	target_name,
	const uint32_t&	tid,
	const DeleteAllEntries6CB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const uint32_t*, const bool*>::RefPtr GetEntryListStart4CB;

    bool send_get_entry_list_start4(
	const char*	target_name,
	const GetEntryListStart4CB&	cb
    );

    typedef XorpCallback10<void, const XrlError&, const string*, const string*, const IPv4Net*, const IPv4Net*, const uint32_t*, const uint32_t*, const uint32_t*, const string*, const bool*>::RefPtr GetEntryListNext4CB;

    bool send_get_entry_list_next4(
	const char*	target_name,
	const uint32_t&	token,
	const GetEntryListNext4CB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_get_backend(
	const XrlError&	e,
	XrlArgs*	a,
	GetBackendCB		cb
    );

    void unmarshall_set_backend(
	const XrlError&	e,
	XrlArgs*	a,
	SetBackendCB		cb
    );

    void unmarshall_get_version(
	const XrlError&	e,
	XrlArgs*	a,
	GetVersionCB		cb
    );

    void unmarshall_start_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	StartTransactionCB		cb
    );

    void unmarshall_commit_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	CommitTransactionCB		cb
    );

    void unmarshall_abort_transaction(
	const XrlError&	e,
	XrlArgs*	a,
	AbortTransactionCB		cb
    );

    void unmarshall_add_entry4(
	const XrlError&	e,
	XrlArgs*	a,
	AddEntry4CB		cb
    );

    void unmarshall_delete_entry4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteEntry4CB		cb
    );

    void unmarshall_delete_all_entries4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteAllEntries4CB		cb
    );

    void unmarshall_add_entry6(
	const XrlError&	e,
	XrlArgs*	a,
	AddEntry6CB		cb
    );

    void unmarshall_delete_entry6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteEntry6CB		cb
    );

    void unmarshall_delete_all_entries6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteAllEntries6CB		cb
    );

    void unmarshall_get_entry_list_start4(
	const XrlError&	e,
	XrlArgs*	a,
	GetEntryListStart4CB		cb
    );

    void unmarshall_get_entry_list_next4(
	const XrlError&	e,
	XrlArgs*	a,
	GetEntryListNext4CB		cb
    );

};

#endif /* __XRL_INTERFACES_PACKET_ACL_XIF_HH__ */
