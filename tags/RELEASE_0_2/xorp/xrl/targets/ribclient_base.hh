/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/ribclient_base.hh,v 1.5 2003/03/05 19:36:00 hodson Exp $
 */


#ifndef __XRL_INTERFACES_RIBCLIENT_BASE_HH__
#define __XRL_INTERFACES_RIBCLIENT_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRibclientTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlRibclientTargetBase {
protected:
    XrlCmdMap* _cmds;
    
public:
    XrlRibclientTargetBase(XrlCmdMap* cmds) : _cmds(cmds) { add_handlers(); }
    virtual ~XrlRibclientTargetBase() { remove_handlers(); }

    inline const string& name() const { return _cmds->name(); }
    inline const char* version() const { return "ribclient/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Route Info Changed route_info_changed is called by the RIB on the RIB
     *  client (typically a routing protocol) that had registered an interest
     *  in the routing of an address. This can be because the metric and/or
     *  nexthop changed.
     *  
     *  @param addr base address of the subnet that was registered
     *  
     *  @param prefix_len prefix length of the subnet that was registered
     */
    virtual XrlCmdError rib_client_0_1_route_info_changed4(
	// Input values, 
	const IPv4&	addr, 
	const uint32_t&	prefix_len, 
	const IPv4&	nexthop, 
	const uint32_t&	metric) = 0;

    virtual XrlCmdError rib_client_0_1_route_info_changed6(
	// Input values, 
	const IPv6&	addr, 
	const uint32_t&	prefix_len, 
	const IPv6&	nexthop, 
	const uint32_t&	metric) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Route Info Invalid route_info_invalid is called by the RIB on the RIB
     *  client (typically a routing protocol) that had registere d an interest
     *  in the routing of an address. This can be because the information
     *  previously reported as applying no longer applies for any number of
     *  reasons. When the RIB sends this message, it has automatically
     *  de-registered interest in the route, and the client will normally need
     *  to send a register_interest request again.
     */
    virtual XrlCmdError rib_client_0_1_route_info_invalid4(
	// Input values, 
	const IPv4&	addr, 
	const uint32_t&	prefix_len) = 0;

    virtual XrlCmdError rib_client_0_1_route_info_invalid6(
	// Input values, 
	const IPv6&	addr, 
	const uint32_t&	prefix_len) = 0;

private:
    const XrlCmdError handle_rib_client_0_1_route_info_changed4(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rib_client_0_1_route_info_changed6(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rib_client_0_1_route_info_invalid4(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rib_client_0_1_route_info_invalid6(const Xrl& x, XrlArgs* a);

    void add_handlers()
    {
	if (_cmds->add_handler("rib_client/0.1/route_info_changed4", 
	    callback(this, &XrlRibclientTargetBase::handle_rib_client_0_1_route_info_changed4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ribclient/rib_client/0.1/route_info_changed4");
	}
	if (_cmds->add_handler("rib_client/0.1/route_info_changed6", 
	    callback(this, &XrlRibclientTargetBase::handle_rib_client_0_1_route_info_changed6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ribclient/rib_client/0.1/route_info_changed6");
	}
	if (_cmds->add_handler("rib_client/0.1/route_info_invalid4", 
	    callback(this, &XrlRibclientTargetBase::handle_rib_client_0_1_route_info_invalid4)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ribclient/rib_client/0.1/route_info_invalid4");
	}
	if (_cmds->add_handler("rib_client/0.1/route_info_invalid6", 
	    callback(this, &XrlRibclientTargetBase::handle_rib_client_0_1_route_info_invalid6)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ribclient/rib_client/0.1/route_info_invalid6");
	}
	_cmds->finalize();
    }

    void remove_handlers()
    {
	_cmds->remove_handler("rib_client/0.1/route_info_changed4");
	_cmds->remove_handler("rib_client/0.1/route_info_changed6");
	_cmds->remove_handler("rib_client/0.1/route_info_invalid4");
	_cmds->remove_handler("rib_client/0.1/route_info_invalid6");
    }
};

#endif /* __XRL_INTERFACES_RIBCLIENT_BASE_HH__ */
