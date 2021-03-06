// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2011 XORP, Inc and Others
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License, Version 2, June
// 1991 as published by the Free Software Foundation. Redistribution
// and/or modification of this program under the terms of any other
// version of the GNU General Public License is not permitted.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. For more details,
// see the GNU General Public License, Version 2, a copy of which can be
// found in the XORP LICENSE.gpl file.
// 
// XORP Inc, 2953 Bunker Hill Lane, Suite 204, Santa Clara, CA 95054, USA;
// http://xorp.net

#include <xorp_config.h>
#ifdef HAVE_NETLINK_SOCKETS


#include "fea/fea_module.h"
#include "fea/fibconfig.hh"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/ipvx.hh"

#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif
#ifdef HAVE_LINUX_TYPES_H
#include <linux/types.h>
#endif
#ifdef HAVE_LINUX_RTNETLINK_H
#include <linux/rtnetlink.h>
#endif

#include "libproto/packet.hh"

#include "netlink_socket.hh"
#include "netlink_socket_utilities.hh"
#include "system_utilities.hh"


//
// NETLINK format related utilities for manipulating data
// (e.g., obtained by netlink(7) sockets mechanism).
//


string NlmUtils::nlm_print_msg(const vector<uint8_t>& buffer) {
    ostringstream oss;

    size_t buffer_bytes = buffer.size();
    AlignData<struct nlmsghdr> align_data(buffer);
    const struct nlmsghdr* nlh;

    for (nlh = align_data.payload();
	 NLMSG_OK(nlh, buffer_bytes);
	 nlh = NLMSG_NEXT(const_cast<struct nlmsghdr*>(nlh), buffer_bytes)) {
	void* nlmsg_data = NLMSG_DATA(const_cast<struct nlmsghdr*>(nlh));

	oss << "type:  " << NlmUtils::nlm_msg_type(nlh->nlmsg_type);
	
	// Decode a few further.
	switch (nlh->nlmsg_type) {
	case NLMSG_ERROR: {
	    const struct nlmsgerr* err;
	    
	    err = reinterpret_cast<const struct nlmsgerr*>(nlmsg_data);
	    if (nlh->nlmsg_len < NLMSG_LENGTH(sizeof(*err))) {
		XLOG_ERROR("AF_NETLINK nlmsgerr length error");
		break;
	    }
	    errno = -err->error;
	    oss << "  AF_NETLINK NLMSG_ERROR message: " << strerror(errno) << endl;
	    break;
	}
	
	case RTM_NEWROUTE:
	case RTM_DELROUTE:
	case RTM_GETROUTE: {

	    const struct rtmsg* rtmsg;
	    int rta_len = RTM_PAYLOAD(nlh);
	    
	    if (rta_len < 0) {
		XLOG_ERROR("AF_NETLINK rtmsg length error");
		break;
	    }
	    rtmsg = reinterpret_cast<const struct rtmsg*>(nlmsg_data);

	    oss << " rtm_type: ";
	    if (rtmsg->rtm_type == RTN_MULTICAST)
		oss << "MULTICAST";
	    else if (rtmsg->rtm_type == RTN_BROADCAST)
		oss << "BROADCAST";
	    else if (rtmsg->rtm_type == RTN_UNICAST)
		oss << "UNICAST";
	    else
		oss << (int)(rtmsg->rtm_type);
		
	    const struct rtattr *rtattr;
	    const struct rtattr *rta_array[RTA_MAX + 1];
	    int family = rtmsg->rtm_family;
    
	    //
	    // Get the attributes
	    //
	    memset(rta_array, 0, sizeof(rta_array));
	    rtattr = RTM_RTA(const_cast<struct rtmsg *>(rtmsg));
	    NlmUtils::get_rtattr(rtattr, rta_len, rta_array,
				 sizeof(rta_array) / sizeof(rta_array[0]));

	    int rtmt = rtmsg->rtm_table;
#ifdef HAVE_NETLINK_SOCKET_ATTRIBUTE_RTA_TABLE
	    if (rta_array[RTA_TABLE] != NULL) {
		const uint8_t* p = static_cast<const uint8_t *>(
		    RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_TABLE])));
		rtmt = extract_host_int(p);
	    }
#endif
	    oss << " table: " << rtmt;


	    IPvX nexthop_addr(family);
	    IPvX dst_addr(family);

	    if (rta_array[RTA_DST] == NULL) {
		// The default entry
	    } else {
		// TODO: fix this!!
		dst_addr.copy_in(family, (uint8_t *)RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_DST])));
		dst_addr = system_adjust_ipvx_recv(dst_addr);
		oss << " dest: " << dst_addr.str() << "/" << (int)(rtmsg->rtm_dst_len);
	    }

    
	    if (rta_array[RTA_GATEWAY] != NULL) {
		nexthop_addr.copy_in(family, (uint8_t *)RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_GATEWAY])));
		oss << " nexthop: " << nexthop_addr.str();
	    }


	    if (rtmsg->rtm_protocol == RTPROT_XORP)
		oss << " proto: XORP";
	    else
		oss << " proto: " << rtmsg->rtm_protocol;
	    
	    // Get the interface index
	    if (rta_array[RTA_OIF] != NULL) {
		const uint8_t* p = static_cast<const uint8_t *>(
		    RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_OIF])));
		oss << " iface: " << extract_host_int(p);
	    }

	    if (rta_array[RTA_PRIORITY] != NULL) {
		const uint8_t* p = static_cast<const uint8_t *>(
		    RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_PRIORITY])));
		oss << " metric: " << extract_host_int(p);
	    }
	    oss << endl;
	}
	
	default:
	    // ignore
	    oss << endl;
	}
    }
    return oss.str();
}//nlm_print_msg


/**
 * @param m message type from netlink socket message
 * @return human readable form.
 */
string
NlmUtils::nlm_msg_type(uint32_t m)
{
    struct {
	uint32_t 	value;
	const char*	name;
    } nlm_msg_types[] = {
#define RTM_MSG_ENTRY(X) { X, #X }
#ifdef NLMSG_ERROR
	RTM_MSG_ENTRY(NLMSG_ERROR),
#endif
#ifdef NLMSG_DONE
	RTM_MSG_ENTRY(NLMSG_DONE),
#endif
#ifdef NLMSG_NOOP
	RTM_MSG_ENTRY(NLMSG_NOOP),
#endif
#ifdef RTM_NEWLINK
	RTM_MSG_ENTRY(RTM_NEWLINK),
#endif
#ifdef RTM_DELLINK
	RTM_MSG_ENTRY(RTM_DELLINK),
#endif
#ifdef RTM_GETLINK
	RTM_MSG_ENTRY(RTM_GETLINK),
#endif
#ifdef RTM_NEWADDR
	RTM_MSG_ENTRY(RTM_NEWADDR),
#endif
#ifdef RTM_DELADDR
	RTM_MSG_ENTRY(RTM_DELADDR),
#endif
#ifdef RTM_GETADDR
	RTM_MSG_ENTRY(RTM_GETADDR),
#endif
#ifdef RTM_NEWROUTE
	RTM_MSG_ENTRY(RTM_NEWROUTE),
#endif
#ifdef RTM_DELROUTE
	RTM_MSG_ENTRY(RTM_DELROUTE),
#endif
#ifdef RTM_GETROUTE
	RTM_MSG_ENTRY(RTM_GETROUTE),
#endif
#ifdef RTM_NEWNEIGH
	RTM_MSG_ENTRY(RTM_NEWNEIGH),
#endif
#ifdef RTM_DELNEIGH
	RTM_MSG_ENTRY(RTM_DELNEIGH),
#endif
#ifdef RTM_GETNEIGH
	RTM_MSG_ENTRY(RTM_GETNEIGH),
#endif
#ifdef RTM_NEWRULE
	RTM_MSG_ENTRY(RTM_NEWRULE),
#endif
#ifdef RTM_DELRULE
	RTM_MSG_ENTRY(RTM_DELRULE),
#endif
#ifdef RTM_GETRULE
	RTM_MSG_ENTRY(RTM_GETRULE),
#endif
#ifdef RTM_NEWQDISC
	RTM_MSG_ENTRY(RTM_NEWQDISC),
#endif
#ifdef RTM_DELQDISC
	RTM_MSG_ENTRY(RTM_DELQDISC),
#endif
#ifdef RTM_GETQDISC
	RTM_MSG_ENTRY(RTM_GETQDISC),
#endif
#ifdef RTM_NEWTCLASS
	RTM_MSG_ENTRY(RTM_NEWTCLASS),
#endif
#ifdef RTM_DELTCLASS
	RTM_MSG_ENTRY(RTM_DELTCLASS),
#endif
#ifdef RTM_GETTCLASS
	RTM_MSG_ENTRY(RTM_GETTCLASS),
#endif
#ifdef RTM_NEWTFILTER
	RTM_MSG_ENTRY(RTM_NEWTFILTER),
#endif
#ifdef RTM_DELTFILTER
	RTM_MSG_ENTRY(RTM_DELTFILTER),
#endif
#ifdef RTM_GETTFILTER
	RTM_MSG_ENTRY(RTM_GETTFILTER),
#endif
#ifdef RTM_MAX
	RTM_MSG_ENTRY(RTM_MAX),
#endif
	{ ~0U, "Unknown" }
    };
    const size_t n_nlm_msgs = sizeof(nlm_msg_types) / sizeof(nlm_msg_types[0]);
    const char* ret = 0;
    for (size_t i = 0; i < n_nlm_msgs; i++) {
	ret = nlm_msg_types[i].name;
	if (nlm_msg_types[i].value == m)
	    break;
    }
    return ret;
}

void
NlmUtils::get_rtattr(const struct rtattr* rtattr, int rta_len,
		     const struct rtattr* rta_array[], size_t rta_array_n)
{
    while (RTA_OK(rtattr, rta_len)) {
	if (rtattr->rta_type < rta_array_n)
	    rta_array[rtattr->rta_type] = rtattr;
	rtattr = RTA_NEXT(const_cast<struct rtattr *>(rtattr), rta_len);
    }
    
    if (rta_len) {
	XLOG_WARNING("get_rtattr() failed: AF_NETLINK deficit in rtattr: "
		     "%d rta_len remaining",
		     rta_len);
    }
}

int
NlmUtils::nlm_get_to_fte_cfg(const IfTree& iftree, FteX& fte,
			     const struct nlmsghdr* nlh,
			     const struct rtmsg* rtmsg, int rta_len, const FibConfig& fibconfig,
			     string& err_msg)
{
    const struct rtattr *rtattr;
    const struct rtattr *rta_array[RTA_MAX + 1];
    int if_index = 0;		// XXX: initialized with an invalid value
    bool lookup_ifindex = true;
    string if_name;
    string vif_name;
    int family = fte.nexthop().af();
    bool is_deleted = false;
    
    // Reset the result
    fte.zero();
    
    // Test if this entry was deleted
    if (nlh->nlmsg_type == RTM_DELROUTE)
	is_deleted = true;


    //
    // Get the attributes
    //
    memset(rta_array, 0, sizeof(rta_array));
    rtattr = RTM_RTA(const_cast<struct rtmsg *>(rtmsg));
    NlmUtils::get_rtattr(rtattr, rta_len, rta_array,
			 sizeof(rta_array) / sizeof(rta_array[0]));

    // Discard the route if we are using a specific table.
    if (fibconfig.unicast_forwarding_table_id_is_configured(family)) {
	int rttable = fibconfig.unicast_forwarding_table_id(family);
	int rtmt = rtmsg->rtm_table;
#ifdef HAVE_NETLINK_SOCKET_ATTRIBUTE_RTA_TABLE
	if (rta_array[RTA_TABLE] != NULL) {
	    const uint8_t* p = static_cast<const uint8_t *>(
		RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_TABLE])));
	    rtmt = extract_host_int(p);
	}
#endif
	if ((rtmt != RT_TABLE_UNSPEC) && (rtmt != rttable)) {
	    err_msg += c_format("Ignoring route from table: %i\n", rtmt);
	    return XORP_ERROR;
	}
	else {
	    //XLOG_WARNING("Accepting route from table: %i\n", rtmt);
	}
    }


    IPvX nexthop_addr(family);
    IPvX dst_addr(family);
    int dst_mask_len = 0;

    //XLOG_INFO("rtm type: %i\n", (int)(rtmsg->rtm_type));

    //
    // Type-specific processing
    //
    switch (rtmsg->rtm_type) {
    case RTN_LOCAL:
	// TODO: XXX: PAVPAVPAV: handle it, if needed!
	err_msg += "RTM type is RTN_LOCAL, ignoring.\n";
	return (XORP_ERROR);		// TODO: is it really an error?

    case RTN_BLACKHOLE:
    case RTN_PROHIBIT:
    {
	//
	// Try to map discard routes back to the first software discard
	// interface in the tree. If we don't have one, then ignore this route.
	// We have to scan all interfaces because IfTree elements
	// are held in a map, and we don't key on this property.
	//
	const IfTreeInterface* pi = NULL;
	for (IfTree::IfMap::const_iterator ii = iftree.interfaces().begin();
	     ii != iftree.interfaces().end(); ++ii) {
	    if (ii->second->discard()) {
		pi = ii->second;
		break;
	    }
	}
	if (pi == NULL) {
	    //
	    // XXX: Cannot map a discard route back to an FEA soft discard
	    // interface.
	    //
	    err_msg += "Can't map discard route back to FEA soft discard interface.\n";
	    return (XORP_ERROR);
	}
	if_name = pi->ifname();
	vif_name = if_name;		// XXX: ifname == vifname
	// XXX: Do we need to change nexthop_addr?
	lookup_ifindex = false;
	break;
    }

    case RTN_UNREACHABLE:
    {
	//
	// Try to map unreachable routes back to the first software unreachable
	// interface in the tree. If we don't have one, then ignore this route.
	// We have to scan all interfaces because IfTree elements
	// are held in a map, and we don't key on this property.
	//
	const IfTreeInterface* pi = NULL;
	for (IfTree::IfMap::const_iterator ii = iftree.interfaces().begin();
	     ii != iftree.interfaces().end(); ++ii) {
	    if (ii->second->unreachable()) {
		pi = ii->second;
		break;
	    }
	}
	if (pi == NULL) {
	    //
	    // XXX: Cannot map an unreachable route back to an FEA soft
	    // unreachable interface.
	    //
	    err_msg += "Can't map unreachable route back to FEA soft unreachable interface.\n";
	    return (XORP_ERROR);
	}
	if_name = pi->ifname();
	vif_name = if_name;		// XXX: ifname == vifname
	// XXX: Do we need to change nexthop_addr?
	lookup_ifindex = false;
	break;
    }

    case RTN_UNICAST:
	break;

    default:
	XLOG_ERROR("nlm_get_to_fte_cfg() failed: "
		   "unrecognized AF_NETLINK route type: %d",
		   rtmsg->rtm_type);
	err_msg += c_format("Unrecognized route type: %i\n", (int)(rtmsg->rtm_type));
	return (XORP_ERROR);
    }

    //
    // Check the address family
    //
    if (rtmsg->rtm_family != family) {
	err_msg += "Invalid family.\n";
	return (XORP_ERROR);
    }

    //
    // Get the destination
    //
    if (rta_array[RTA_DST] == NULL) {
	// The default entry
    } else {
	// TODO: fix this!!
	dst_addr.copy_in(family, (uint8_t *)RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_DST])));
	dst_addr = system_adjust_ipvx_recv(dst_addr);
	if (! dst_addr.is_unicast()) {
	    // TODO: should we make this check?
	    fte.zero();
	    err_msg += c_format("Ignoring non-unicast destination: %s\n", dst_addr.str().c_str());
	    return (XORP_ERROR);
	}
    }
    
    //
    // Get the next-hop router address
    //
    if (rta_array[RTA_GATEWAY] != NULL) {
	nexthop_addr.copy_in(family, (uint8_t *)RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_GATEWAY])));
    }
    
    //
    // Get the destination mask length
    //
    dst_mask_len = rtmsg->rtm_dst_len;

    //
    // Test whether we installed this route
    //
    bool xorp_route = false;
    if (rtmsg->rtm_protocol == RTPROT_XORP)
	xorp_route = true;

    //
    // Get the interface/vif name and index
    //
    if (lookup_ifindex) {
	// Get the interface index
	if (rta_array[RTA_OIF] != NULL) {
	    const uint8_t* p = static_cast<const uint8_t *>(
		RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_OIF])));
	    if_index = extract_host_int(p);
	} else {
	    XLOG_ERROR("nlm_get_to_fte_cfg() failed: no interface found");
	    err_msg += "Could not find interface (no RTA_OIF)\n";
	    return (XORP_ERROR);
	}

	// Get the interface/vif name
	const IfTreeVif* vifp = iftree.find_vif(if_index);
	if (vifp != NULL) {
	    if_name = vifp->ifname();
	    vif_name = vifp->vifname();
	}

	// Test whether the interface/vif name was found
	if (if_name.empty() || vif_name.empty()) {
	    if (is_deleted) {
		//
		// XXX: If the route is deleted and we cannot find
		// the corresponding interface/vif, this could be because
		// an interface/vif is deleted from the kernel, and
		// the kernel might send first the upcall message
		// that deletes the interface from user space.
		// Hence the upcall message that followed to delete the
		// corresponding route for the connected subnet
		// won't find the interface/vif.
		// Propagate the route deletion with empty interface
		// and vif name.
		//
	    } else {
		//
		// XXX: A route was added, but we cannot find the corresponding
		// interface/vif.
		// This is probably because the interface in question is not in our
		// local config.
		// Another possibility:  This might happen because of a race
		// condition. E.g., an interface was added and then
		// immediately deleted, but the processing for the addition of
		// the corresponding connected route was delayed.
		// Note that the misorder in the processing might happen
		// because the interface and routing control messages are
		// received on different control sockets.
		// For the time being make it a fatal error until there is
		// enough evidence and the issue is understood.
		//
		//IPvXNet dst_subnet(dst_addr, dst_mask_len);
		err_msg += c_format("WARNING:  Decoding for route %s next hop %s failed: "
				    "could not find interface and vif for index %d",
				    dst_addr.str().c_str(),
				    nexthop_addr.str().c_str(),
				    if_index);
		return XORP_ERROR;
	    }
	}
    }

    //
    // Get the route metric
    //
    uint32_t route_metric = 0xffff;
    if (rta_array[RTA_PRIORITY] != NULL) {
	const uint8_t* p = static_cast<const uint8_t *>(
	    RTA_DATA(const_cast<struct rtattr *>(rta_array[RTA_PRIORITY])));
	int int_priority = extract_host_int(p);
	route_metric = int_priority;
    }

    //
    // TODO: define default admin distance instead of 0xffff
    //
    try {
	fte = FteX(IPvXNet(dst_addr, dst_mask_len), nexthop_addr,
		   if_name, vif_name, route_metric, 0xffff, xorp_route);
    }
    catch (XorpException& xe) {
	err_msg += "exception in nlm_get_to_fte_cfg: ";
	err_msg += xe.str();
	err_msg += "\n";
	XLOG_ERROR("exception in nlm_get_to_fte_cfg: %s", xe.str().c_str());
	return XORP_ERROR;
    }

    if (is_deleted)
	fte.mark_deleted();

    //XLOG_INFO("get_fte_cfg, route: %s", fte.str().c_str());
    
    return (XORP_OK);
}

/**
 * Check that a previous netlink request has succeeded.
 *
 * @param ns_reader the NetlinkSocketReader to use for reading data.
 * @param ns the NetlinkSocket to use for reading data.
 * @param seqno the sequence nomer of the netlink request to check for.
 * @param last_errno the last error number (if error).
 * @param error_msg the error message (if error).
 * @return XORP_OK on success, otherwise XORP_ERROR.
 */
int
NlmUtils::check_netlink_request(NetlinkSocketReader& ns_reader,
				NetlinkSocket& ns,
				uint32_t seqno,
				int& last_errno,
				string& error_msg)
{
    size_t buffer_bytes;
    const struct nlmsghdr* nlh;

    last_errno = 0;		// XXX: reset the value

    //
    // Force to receive data from the kernel, and then parse it
    //
    if (ns_reader.receive_data(ns, seqno, error_msg) != XORP_OK)
	return (XORP_ERROR);

    const vector<uint8_t>& buffer = ns_reader.buffer();
    buffer_bytes = buffer.size();
    AlignData<struct nlmsghdr> align_data(buffer);
    for (nlh = align_data.payload();
	 NLMSG_OK(nlh, buffer_bytes);
	 nlh = NLMSG_NEXT(const_cast<struct nlmsghdr*>(nlh), buffer_bytes)) {
	void* nlmsg_data = NLMSG_DATA(const_cast<struct nlmsghdr*>(nlh));
	
	switch (nlh->nlmsg_type) {
	case NLMSG_ERROR:
	{
	    const struct nlmsgerr* err;

	    err = reinterpret_cast<const struct nlmsgerr*>(nlmsg_data);
	    if (nlh->nlmsg_len < NLMSG_LENGTH(sizeof(*err))) {
		error_msg += "AF_NETLINK nlmsgerr length error\n";
		return (XORP_ERROR);
	    }
	    if (err->error == 0)
		return (XORP_OK);	// No error
	    errno = -err->error;
	    last_errno = errno;
	    error_msg += c_format("AF_NETLINK NLMSG_ERROR message: %s\n",
				  strerror(errno));
	    return (XORP_ERROR);
	}
	break;
	
	case NLMSG_DONE:
	{
	    // End-of-message, and no ACK was received: error.
	    error_msg += "No ACK was received\n";
	    return (XORP_ERROR);
	}
	break;

	case NLMSG_NOOP:
	    break;

	default:
	    debug_msg("Unhandled type %s(%d) (%u bytes)\n",
		      NlmUtils::nlm_msg_type(nlh->nlmsg_type).c_str(),
		      nlh->nlmsg_type, XORP_UINT_CAST(nlh->nlmsg_len));
	    break;
	}
    }

    error_msg += "No ACK was received\n";
    return (XORP_ERROR);		// No ACK was received: error.
}

#endif // HAVE_NETLINK_SOCKETS
