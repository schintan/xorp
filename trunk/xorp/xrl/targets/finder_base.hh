/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/finder_base.hh,v 1.17 2003/06/19 00:44:46 hodson Exp $
 */


#ifndef __XRL_INTERFACES_FINDER_BASE_HH__
#define __XRL_INTERFACES_FINDER_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlFinderTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlFinderTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    XrlFinderTargetBase(XrlCmdMap* cmds) : _cmds(cmds) { add_handlers(); }
    virtual ~XrlFinderTargetBase() { remove_handlers(); }

    inline const string& name() const { return _cmds->name(); }
    inline const char* version() const { return "finder/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values, 
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values, 
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values, 
	uint32_t&	status, 
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Register client with Finder. Once client has been registered Xrl
     *  registrations may proceed. Once Xrl registrations have have been
     *  completed the client needs to be enabled for the Finder to respond to
     *  queries about the client. Fails if instance_name is already registered,
     *  or another instance of the same class is registered as a singleton. The
     *  target_name must support the finder_client interface in order to be
     *  able to process messages from the finder.
     */
    virtual XrlCmdError finder_0_2_register_finder_client(
	// Input values, 
	const string&	instance_name, 
	const string&	class_name, 
	const bool&	singleton, 
	const string&	in_cookie, 
	// Output values, 
	string&	out_cookie) = 0;

    virtual XrlCmdError finder_0_2_unregister_finder_client(
	// Input values, 
	const string&	instance_name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Enable resolution of Xrls associated with target. Disabling Xrls at
     *  present does not cause clients to flush state associated with target so
     *  cached entries in clients are unaffected by this Xrl. Caller must be
     *  client that registered Xrl.
     */
    virtual XrlCmdError finder_0_2_set_finder_client_enabled(
	// Input values, 
	const string&	instance_name, 
	const bool&	enabled) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get enabled state information associated with finder client.
     */
    virtual XrlCmdError finder_0_2_finder_client_enabled(
	// Input values, 
	const string&	instance_name, 
	// Output values, 
	bool&	enabled) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Add resolved Xrl into system, fails if xrl is already registered.
     */
    virtual XrlCmdError finder_0_2_add_xrl(
	// Input values, 
	const string&	xrl, 
	const string&	protocol_name, 
	const string&	protocol_args, 
	// Output values, 
	string&	resolved_xrl_method_name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Remove xrl
     */
    virtual XrlCmdError finder_0_2_remove_xrl(
	// Input values, 
	const string&	xrl) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Resolve Xrl
     */
    virtual XrlCmdError finder_0_2_resolve_xrl(
	// Input values, 
	const string&	xrl, 
	// Output values, 
	XrlAtomList&	resolutions) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of registered Xrl targets
     */
    virtual XrlCmdError finder_0_2_get_xrl_targets(
	// Output values, 
	XrlAtomList&	target_names) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of Xrls registered by target
     */
    virtual XrlCmdError finder_0_2_get_xrls_registered_by(
	// Input values, 
	const string&	target_name, 
	// Output values, 
	XrlAtomList&	xrls) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of IPv4 hosts that clients should accept IPC requests from.
     */
    virtual XrlCmdError finder_0_2_get_ipv4_permitted_hosts(
	// Output values, 
	XrlAtomList&	ipv4s) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of IPv4 nets that clients should accept IPC requests from.
     */
    virtual XrlCmdError finder_0_2_get_ipv4_permitted_nets(
	// Output values, 
	XrlAtomList&	ipv4nets) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of IPv6 hosts that clients should accept IPC requests from.
     */
    virtual XrlCmdError finder_0_2_get_ipv6_permitted_hosts(
	// Output values, 
	XrlAtomList&	ipv6s) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get list of IPv6 nets that clients should accept IPC requests from.
     */
    virtual XrlCmdError finder_0_2_get_ipv6_permitted_nets(
	// Output values, 
	XrlAtomList&	ipv6nets) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Register interest in events relating to a particular class.
     */
    virtual XrlCmdError finder_event_notifier_0_1_register_class_event_interest(
	// Input values, 
	const string&	requester_instance, 
	const string&	class_name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Deregister interest in events relating to a particular class.
     */
    virtual XrlCmdError finder_event_notifier_0_1_deregister_class_event_interest(
	// Input values, 
	const string&	requester_instance, 
	const string&	class_name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Register interest in events relating to a particular instance.
     */
    virtual XrlCmdError finder_event_notifier_0_1_register_instance_event_interest(
	// Input values, 
	const string&	requester_instance, 
	const string&	instance_name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Register interest in events relating to a particular instance.
     */
    virtual XrlCmdError finder_event_notifier_0_1_deregister_instance_event_interest(
	// Input values, 
	const string&	requester_instance, 
	const string&	instance_name) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_register_finder_client(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_unregister_finder_client(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_set_finder_client_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_finder_client_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_add_xrl(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_remove_xrl(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_resolve_xrl(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_xrl_targets(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_xrls_registered_by(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_ipv4_permitted_hosts(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_ipv4_permitted_nets(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_ipv6_permitted_hosts(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_0_2_get_ipv6_permitted_nets(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_notifier_0_1_register_class_event_interest(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_notifier_0_1_deregister_class_event_interest(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_notifier_0_1_register_instance_event_interest(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_notifier_0_1_deregister_instance_event_interest(const XrlArgs& in, XrlArgs* out);

    void add_handlers()
    {
	if (_cmds->add_handler("common/0.1/get_target_name", 
	    callback(this, &XrlFinderTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version", 
	    callback(this, &XrlFinderTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status", 
	    callback(this, &XrlFinderTargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown", 
	    callback(this, &XrlFinderTargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/common/0.1/shutdown");
	}
	if (_cmds->add_handler("finder/0.2/register_finder_client", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_register_finder_client)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/register_finder_client");
	}
	if (_cmds->add_handler("finder/0.2/unregister_finder_client", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_unregister_finder_client)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/unregister_finder_client");
	}
	if (_cmds->add_handler("finder/0.2/set_finder_client_enabled", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_set_finder_client_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/set_finder_client_enabled");
	}
	if (_cmds->add_handler("finder/0.2/finder_client_enabled", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_finder_client_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/finder_client_enabled");
	}
	if (_cmds->add_handler("finder/0.2/add_xrl", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_add_xrl)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/add_xrl");
	}
	if (_cmds->add_handler("finder/0.2/remove_xrl", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_remove_xrl)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/remove_xrl");
	}
	if (_cmds->add_handler("finder/0.2/resolve_xrl", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_resolve_xrl)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/resolve_xrl");
	}
	if (_cmds->add_handler("finder/0.2/get_xrl_targets", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_xrl_targets)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_xrl_targets");
	}
	if (_cmds->add_handler("finder/0.2/get_xrls_registered_by", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_xrls_registered_by)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_xrls_registered_by");
	}
	if (_cmds->add_handler("finder/0.2/get_ipv4_permitted_hosts", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_ipv4_permitted_hosts)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_ipv4_permitted_hosts");
	}
	if (_cmds->add_handler("finder/0.2/get_ipv4_permitted_nets", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_ipv4_permitted_nets)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_ipv4_permitted_nets");
	}
	if (_cmds->add_handler("finder/0.2/get_ipv6_permitted_hosts", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_ipv6_permitted_hosts)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_ipv6_permitted_hosts");
	}
	if (_cmds->add_handler("finder/0.2/get_ipv6_permitted_nets", 
	    callback(this, &XrlFinderTargetBase::handle_finder_0_2_get_ipv6_permitted_nets)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder/0.2/get_ipv6_permitted_nets");
	}
	if (_cmds->add_handler("finder_event_notifier/0.1/register_class_event_interest", 
	    callback(this, &XrlFinderTargetBase::handle_finder_event_notifier_0_1_register_class_event_interest)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder_event_notifier/0.1/register_class_event_interest");
	}
	if (_cmds->add_handler("finder_event_notifier/0.1/deregister_class_event_interest", 
	    callback(this, &XrlFinderTargetBase::handle_finder_event_notifier_0_1_deregister_class_event_interest)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder_event_notifier/0.1/deregister_class_event_interest");
	}
	if (_cmds->add_handler("finder_event_notifier/0.1/register_instance_event_interest", 
	    callback(this, &XrlFinderTargetBase::handle_finder_event_notifier_0_1_register_instance_event_interest)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder_event_notifier/0.1/register_instance_event_interest");
	}
	if (_cmds->add_handler("finder_event_notifier/0.1/deregister_instance_event_interest", 
	    callback(this, &XrlFinderTargetBase::handle_finder_event_notifier_0_1_deregister_instance_event_interest)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://finder/finder_event_notifier/0.1/deregister_instance_event_interest");
	}
	_cmds->finalize();
    }

    void remove_handlers()
    {
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("finder/0.2/register_finder_client");
	_cmds->remove_handler("finder/0.2/unregister_finder_client");
	_cmds->remove_handler("finder/0.2/set_finder_client_enabled");
	_cmds->remove_handler("finder/0.2/finder_client_enabled");
	_cmds->remove_handler("finder/0.2/add_xrl");
	_cmds->remove_handler("finder/0.2/remove_xrl");
	_cmds->remove_handler("finder/0.2/resolve_xrl");
	_cmds->remove_handler("finder/0.2/get_xrl_targets");
	_cmds->remove_handler("finder/0.2/get_xrls_registered_by");
	_cmds->remove_handler("finder/0.2/get_ipv4_permitted_hosts");
	_cmds->remove_handler("finder/0.2/get_ipv4_permitted_nets");
	_cmds->remove_handler("finder/0.2/get_ipv6_permitted_hosts");
	_cmds->remove_handler("finder/0.2/get_ipv6_permitted_nets");
	_cmds->remove_handler("finder_event_notifier/0.1/register_class_event_interest");
	_cmds->remove_handler("finder_event_notifier/0.1/deregister_class_event_interest");
	_cmds->remove_handler("finder_event_notifier/0.1/register_instance_event_interest");
	_cmds->remove_handler("finder_event_notifier/0.1/deregister_instance_event_interest");
    }
};

#endif /* __XRL_INTERFACES_FINDER_BASE_HH__ */
