/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/tgt-gen'.
 */

#ident "$XORP: xorp/xrl/targets/rtrmgr_base.cc,v 1.2 2003/01/24 06:31:34 pavlin Exp $"


#include "rtrmgr_base.hh"

const XrlCmdError
XrlRtrmgrTargetBase::handle_common_0_1_get_target_name(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling common/0.1/get_target_name", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string name; 
    try {
	XrlCmdError e = common_0_1_get_target_name(
	    name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for common/0.1/get_target_name failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("name", name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_common_0_1_get_version(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling common/0.1/get_version", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string version; 
    try {
	XrlCmdError e = common_0_1_get_version(
	    version);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for common/0.1/get_version failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("version", version);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_pid(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 0) { 
	XLOG_ERROR("Wrong number of arguments (%u != 0) handling rtrmgr/0.1/get_pid", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    uint32_t pid; 
    try {
	XrlCmdError e = rtrmgr_0_1_get_pid(
	    pid);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/get_pid failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("pid", pid);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_register_client(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 2) { 
	XLOG_ERROR("Wrong number of arguments (%u != 2) handling rtrmgr/0.1/register_client", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string filename; 
    uint32_t pid; 
    try {
	XrlCmdError e = rtrmgr_0_1_register_client(
	    xrl.const_args().get_uint32("userid"), 
	    xrl.const_args().get_string("clientname"), 
	    filename, 
	    pid);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/register_client failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("filename", filename);
	args->add("pid", pid);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unregister_client(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling rtrmgr/0.1/unregister_client", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_unregister_client(
	    xrl.const_args().get_string("token"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/unregister_client failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_authenticate_client(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 3) { 
	XLOG_ERROR("Wrong number of arguments (%u != 3) handling rtrmgr/0.1/authenticate_client", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_authenticate_client(
	    xrl.const_args().get_uint32("userid"), 
	    xrl.const_args().get_string("clientname"), 
	    xrl.const_args().get_string("token"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/authenticate_client failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_enter_config_mode(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 2) { 
	XLOG_ERROR("Wrong number of arguments (%u != 2) handling rtrmgr/0.1/enter_config_mode", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_enter_config_mode(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_bool("exclusive"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/enter_config_mode failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_leave_config_mode(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling rtrmgr/0.1/leave_config_mode", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_leave_config_mode(
	    xrl.const_args().get_string("token"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/leave_config_mode failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_config_users(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling rtrmgr/0.1/get_config_users", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    XrlAtomList users; 
    try {
	XrlCmdError e = rtrmgr_0_1_get_config_users(
	    xrl.const_args().get_string("token"), 
	    users);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/get_config_users failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("users", users);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_running_config(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling rtrmgr/0.1/get_running_config", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string config; 
    try {
	XrlCmdError e = rtrmgr_0_1_get_running_config(
	    xrl.const_args().get_string("token"), 
	    config);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/get_running_config failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("config", config);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_apply_config_change(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 4) { 
	XLOG_ERROR("Wrong number of arguments (%u != 4) handling rtrmgr/0.1/apply_config_change", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_apply_config_change(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_string("target"), 
	    xrl.const_args().get_string("deltas"), 
	    xrl.const_args().get_string("deletions"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/apply_config_change failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_lock_config(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 2) { 
	XLOG_ERROR("Wrong number of arguments (%u != 2) handling rtrmgr/0.1/lock_config", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    bool success; 
    uint32_t holder; 
    try {
	XrlCmdError e = rtrmgr_0_1_lock_config(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_uint32("timeout"), 
	    success, 
	    holder);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/lock_config failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("success", success);
	args->add("holder", holder);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unlock_config(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 1) { 
	XLOG_ERROR("Wrong number of arguments (%u != 1) handling rtrmgr/0.1/unlock_config", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_unlock_config(
	    xrl.const_args().get_string("token"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/unlock_config failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_lock_node(const Xrl& xrl, XrlArgs* args)
{
    if (xrl.const_args().size() != 3) { 
	XLOG_ERROR("Wrong number of arguments (%u != 3) handling rtrmgr/0.1/lock_node", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    if (args == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    bool success; 
    uint32_t holder; 
    try {
	XrlCmdError e = rtrmgr_0_1_lock_node(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_string("node"), 
	    xrl.const_args().get_uint32("timeout"), 
	    success, 
	    holder);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/lock_node failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	args->add("success", success);
	args->add("holder", holder);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unlock_node(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 2) { 
	XLOG_ERROR("Wrong number of arguments (%u != 2) handling rtrmgr/0.1/unlock_node", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_unlock_node(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_string("node"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/unlock_node failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_save_config(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 2) { 
	XLOG_ERROR("Wrong number of arguments (%u != 2) handling rtrmgr/0.1/save_config", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_save_config(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_string("filename"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/save_config failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlRtrmgrTargetBase::handle_rtrmgr_0_1_load_config(const Xrl& xrl, XrlArgs* /* args */)
{
    if (xrl.const_args().size() != 3) { 
	XLOG_ERROR("Wrong number of arguments (%u != 3) handling rtrmgr/0.1/load_config", (uint32_t)xrl.const_args().size());
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = rtrmgr_0_1_load_config(
	    xrl.const_args().get_string("token"), 
	    xrl.const_args().get_string("target"), 
	    xrl.const_args().get_string("filename"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for rtrmgr/0.1/load_config failed: %s \"%s\"",
            		 e.str().c_str(), e.note().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

