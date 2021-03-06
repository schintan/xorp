// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// vim:set sts=4 ts=8:

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



#include "fea/fea_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/win_io.h"
#include "libxorp/ipv4net.hh"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_IPHLPAPI_H
#include <iphlpapi.h>
#endif

#include "fea/ifconfig.hh"

#include "ifconfig_get_iphelper.hh"


//
// Get information about network interfaces from the underlying system.
//
// The mechanism to obtain the information is the IP Helper API for
// Windows (IPHLPAPI.DLL).
//

#ifdef HOST_OS_WINDOWS

IfConfigGetIPHelper::IfConfigGetIPHelper(FeaDataPlaneManager& fea_data_plane_manager)
    : IfConfigGet(fea_data_plane_manager)
{
}

IfConfigGetIPHelper::~IfConfigGetIPHelper()
{
    string error_msg;

    if (stop(error_msg) != XORP_OK) {
	XLOG_ERROR("Cannot stop the IP Helper API mechanism to get "
		   "information about network interfaces from the underlying "
		   "system: %s",
		   error_msg.c_str());
    }
}

int
IfConfigGetIPHelper::start(string& error_msg)
{
    UNUSED(error_msg);

    if (_is_running)
	return (XORP_OK);

    _is_running = true;

    return (XORP_OK);
}

int
IfConfigGetIPHelper::stop(string& error_msg)
{
    UNUSED(error_msg);

    if (! _is_running)
	return (XORP_OK);

    _is_running = false;

    return (XORP_OK);
}

int
IfConfigGetIPHelper::pull_config(const IfTree* local_config, IfTree& iftree)
{
    return read_config(local_config, iftree);
}

int
IfConfigGetIPHelper::read_config(const IfTree* local_config, IfTree& iftree)
{
    PIP_ADAPTER_ADDRESSES pAdapters = NULL;
    PIP_ADAPTER_ADDRESSES curAdapter;
    DWORD	result, tries;
    ULONG	dwSize;

    tries = 0;
    result = ERROR_INSUFFICIENT_BUFFER;
    dwSize = sizeof(IP_ADAPTER_ADDRESSES);

    do {
        pAdapters = (PIP_ADAPTER_ADDRESSES) ((tries == 0) ? malloc(dwSize) :
                   realloc(pAdapters, dwSize));
        if (pAdapters == NULL)
            break;
	// XXX: Deal with HAVE_IPV6, anycast and multicast when needed.
        result = GetAdaptersAddresses(AF_UNSPEC,
                                      GAA_FLAG_INCLUDE_PREFIX |
				      GAA_FLAG_SKIP_ANYCAST |
				      GAA_FLAG_SKIP_MULTICAST |
				      GAA_FLAG_SKIP_DNS_SERVER,
                                      NULL, pAdapters, &dwSize);
	if (pAdapters == NULL)
	    break;
    } while ((++tries < 3) || (result == ERROR_INSUFFICIENT_BUFFER));

    if (result != NO_ERROR) {
	XLOG_ERROR("GetAdaptersAddresses(): %s\n", win_strerror(result));
	if (pAdapters != NULL)
	    free(pAdapters);
	return (XORP_ERROR);
    }

    char	if_name[MAX_ADAPTER_NAME_LENGTH+4];
    uint32_t	if_index;
    bool	is_newlink;

    for (curAdapter = pAdapters;
	 curAdapter != NULL;
	 curAdapter = curAdapter->Next)
    {
	if_index = curAdapter->IfIndex;

	// XXX: require IPv4. IfIndex will be 0 if IPv4 is not active
	// on this adapter.
	if (if_index == 0)
	    continue;

	wcstombs(if_name, curAdapter->FriendlyName, sizeof(if_name));
	//XLOG_INFO("Found Iface name: %s  idx: %i iftree: %s\n",
	//	  if_name, (int)(curAdapter->IfIndex), iftree.getName().c_str());

	// Name
	IfTreeInterface* ifp = iftree.find_interface(if_name);
	if (ifp == NULL) {
	    if (local_config && !local_config->find_interface(if_name)) {
		// Ignore, not configured to use this interface.
		continue;
	    }
	    iftree.add_interface(if_name);
	    is_newlink = true;
	    ifp = iftree.find_interface(if_name);
	    XLOG_ASSERT(ifp != NULL);
	}

	// Index
	if (is_newlink || (if_index != ifp->pif_index()))
	    ifp->set_pif_index(if_index);

	// MAC
	if (curAdapter->IfType == MIB_IF_TYPE_ETHERNET &&
	    curAdapter->PhysicalAddressLength == sizeof(struct ether_addr)) {
		struct ether_addr ea;
		memcpy(&ea, curAdapter->PhysicalAddress, sizeof(ea));
		Mac mac(ea);
		if (is_newlink || (mac != ifp->mac()))
		    ifp->set_mac(mac);
	}

	// MTU
	uint32_t mtu = curAdapter->Mtu;
	if (is_newlink || (mtu != ifp->mtu()))
	    ifp->set_mtu(mtu);

	// Link status and baudrate
	bool no_carrier = true;
	uint64_t baudrate = 0;
	if (curAdapter->OperStatus == IfOperStatusUp)
	    no_carrier = false;
	// TODO: find the baudrate
	if (is_newlink || no_carrier != ifp->no_carrier())
	    ifp->set_no_carrier(no_carrier);
	if (is_newlink || baudrate != ifp->baudrate())
	    ifp->set_baudrate(baudrate);

	ifp->set_enabled((curAdapter->OperStatus == IfOperStatusUp));

	// XXX: vifname == ifname on this platform
	if (is_newlink)
	    ifp->add_vif(if_name);

	IfTreeVif* vifp = ifp->find_vif(if_name);
	XLOG_ASSERT(vifp != NULL);

        if (is_newlink || (if_index != vifp->pif_index()))
            vifp->set_pif_index(if_index);

	vifp->set_enabled(ifp->enabled() &&
			  (curAdapter->OperStatus == IfOperStatusUp));
	vifp->set_broadcast(curAdapter->IfType == MIB_IF_TYPE_ETHERNET);
	vifp->set_multicast(curAdapter->IfType == MIB_IF_TYPE_ETHERNET);
	vifp->set_loopback(curAdapter->IfType == MIB_IF_TYPE_LOOPBACK);
	vifp->set_point_to_point(curAdapter->IfType == MIB_IF_TYPE_PPP);

	// Unicast addresses
	// XXX: Currently we only support IPv4.

	IPv4 lcl_addr;
	IPv4 bcast_addr;
	IPv4Net net_addr;
	uint32_t prefix_len;
	PIP_ADAPTER_UNICAST_ADDRESS curAddress;
	PIP_ADAPTER_PREFIX curPrefix;
	struct sockaddr* psa;
	struct sockaddr* psa2;

	for (curAddress = curAdapter->FirstUnicastAddress;
	     curAddress != NULL;
	     curAddress = curAddress->Next)
	{
	    psa = curAddress->Address.lpSockaddr;
	    if (psa->sa_family != AF_INET)
		continue;
	    lcl_addr.copy_in(*psa);

	    //
	    // Walk the prefix list to find a matching network prefix
	    // for this host address. If found, compute the directed
	    // broadcast address and store the prefix length.
	    // If we don't find a matching prefix, we assume the
	    // address is a host address (/32 prefix).
	    // represent a host-only address.
	    // Skip 0.0.0.0/0 default prefixes returned by GAA().
	    // XXX: Needs updated to support IPv6.
	    //
	    prefix_len = 32;
	    for (curPrefix = curAdapter->FirstPrefix;
		 curPrefix != NULL;
		 curPrefix = curPrefix->Next)
	    {
		psa2 = curPrefix->Address.lpSockaddr;
		if (psa2->sa_family != psa->sa_family)
		    continue;
		if (curPrefix->PrefixLength == 0)
		    continue;
		IPv4Net net_addr(IPv4(*psa2), curPrefix->PrefixLength);
		if (net_addr.contains(lcl_addr)) {
		    prefix_len = curPrefix->PrefixLength;
		    bcast_addr = net_addr.top_addr();
		    break;
		}
	    }

	    vifp->add_addr(lcl_addr);

	    IfTreeAddr4* ap = vifp->find_addr(lcl_addr);
	    XLOG_ASSERT(ap != NULL);
	    ap->set_enabled(vifp->enabled());
	    ap->set_loopback(vifp->loopback());
	    ap->set_point_to_point(vifp->point_to_point());
	    ap->set_multicast(vifp->multicast());
	    ap->set_prefix_len(prefix_len);
	    if (vifp->broadcast()) {
		ap->set_broadcast(true);
		ap->set_bcast(bcast_addr);
	    }
	}
    }

    free(pAdapters);

    //
    // Get the VLAN vif info
    //
    IfConfigVlanGet* ifconfig_vlan_get;
    ifconfig_vlan_get = fea_data_plane_manager().ifconfig_vlan_get();
    if (ifconfig_vlan_get != NULL) {
	bool mod = false; // doesn't matter.
	if (ifconfig_vlan_get->pull_config(iftree, mod) != XORP_OK)
	    return (XORP_ERROR);
    }

    return (XORP_OK);
}

#endif // HOST_OS_WINDOWS
