// SPDX-License-Identifier: GPL-2.0
/*
 * Throwaway instrumentation, not upstream material. See
 * amdxdna_arm_coverage.h for what this counts and where.
 */
#include "amdxdna_arm_coverage.h"

#include <linux/atomic.h>
#include <linux/debugfs.h>
#include <linux/printk.h>
#include <linux/seq_file.h>

static atomic64_t arm_hits[AMDXDNA_ARM_COUNT];

static const char * const arm_names[AMDXDNA_ARM_COUNT] = {
	[ARM_GET_INFO_QUERY_AIE_STATUS]			= "GET_INFO/QUERY_AIE_STATUS",
	[ARM_GET_INFO_QUERY_AIE_METADATA]			= "GET_INFO/QUERY_AIE_METADATA",
	[ARM_GET_INFO_QUERY_AIE_VERSION]			= "GET_INFO/QUERY_AIE_VERSION",
	[ARM_GET_INFO_QUERY_CLOCK_METADATA]			= "GET_INFO/QUERY_CLOCK_METADATA",
	[ARM_GET_INFO_QUERY_SENSORS]				= "GET_INFO/QUERY_SENSORS",
	[ARM_GET_INFO_QUERY_HW_CONTEXTS]			= "GET_INFO/QUERY_HW_CONTEXTS(legacy)",
	[ARM_GET_INFO_QUERY_FIRMWARE_VERSION]			= "GET_INFO/QUERY_FIRMWARE_VERSION",
	[ARM_GET_INFO_GET_POWER_MODE]				= "GET_INFO/GET_POWER_MODE",
	[ARM_GET_INFO_QUERY_TELEMETRY]				= "GET_INFO/QUERY_TELEMETRY",
	[ARM_GET_INFO_QUERY_RESOURCE_INFO]			= "GET_INFO/QUERY_RESOURCE_INFO",
	[ARM_GET_INFO_GET_FORCE_PREEMPT_STATE]			= "GET_INFO/GET_FORCE_PREEMPT_STATE",
	[ARM_GET_INFO_GET_FRAME_BOUNDARY_PREEMPT_STATE]	= "GET_INFO/GET_FRAME_BOUNDARY_PREEMPT_STATE",
	[ARM_GET_INFO_GET_AUTO_COREDUMP]			= "GET_INFO/GET_AUTO_COREDUMP",
	[ARM_GET_INFO_DEFAULT]					= "GET_INFO/*unsupported-param*",

	[ARM_GET_ARRAY_HW_CONTEXT_ALL]				= "GET_ARRAY/HW_CONTEXT_ALL",
	[ARM_GET_ARRAY_HW_CONTEXT_BY_ID]			= "GET_ARRAY/HW_CONTEXT_BY_ID",
	[ARM_GET_ARRAY_HW_LAST_ASYNC_ERR]			= "GET_ARRAY/HW_LAST_ASYNC_ERR",
	[ARM_GET_ARRAY_AIE_COREDUMP]				= "GET_ARRAY/AIE_COREDUMP",
	[ARM_GET_ARRAY_BO_USAGE]				= "GET_ARRAY/BO_USAGE",
	[ARM_GET_ARRAY_AIE_TILE_READ]				= "GET_ARRAY/AIE_TILE_READ",
	[ARM_GET_ARRAY_FW_LOG]					= "GET_ARRAY/FW_LOG",
	[ARM_GET_ARRAY_FW_LOG_CONFIG]				= "GET_ARRAY/FW_LOG_CONFIG",
	[ARM_GET_ARRAY_FW_TRACE]				= "GET_ARRAY/FW_TRACE",
	[ARM_GET_ARRAY_FW_TRACE_CONFIG]			= "GET_ARRAY/FW_TRACE_CONFIG",
	[ARM_GET_ARRAY_DEFAULT]				= "GET_ARRAY/*unsupported-param*",

	[ARM_SET_STATE_SET_POWER_MODE]				= "SET_STATE/SET_POWER_MODE",
	[ARM_SET_STATE_SET_FORCE_PREEMPT]			= "SET_STATE/SET_FORCE_PREEMPT",
	[ARM_SET_STATE_SET_FRAME_BOUNDARY_PREEMPT]		= "SET_STATE/SET_FRAME_BOUNDARY_PREEMPT",
	[ARM_SET_STATE_AIE_TILE_WRITE]				= "SET_STATE/AIE_TILE_WRITE",
	[ARM_SET_STATE_SET_FW_LOG_STATE]			= "SET_STATE/SET_FW_LOG_STATE",
	[ARM_SET_STATE_SET_FW_TRACE_STATE]			= "SET_STATE/SET_FW_TRACE_STATE",
	[ARM_SET_STATE_SET_AUTO_COREDUMP]			= "SET_STATE/SET_AUTO_COREDUMP",
	[ARM_SET_STATE_DEFAULT]				= "SET_STATE/*unsupported-param*",

	[ARM_HWCTX_CONFIG_CU]					= "CONFIG_HWCTX/CONFIG_CU",
	[ARM_HWCTX_ASSIGN_DBG_BUF]				= "CONFIG_HWCTX/ASSIGN_DBG_BUF",
	[ARM_HWCTX_REMOVE_DBG_BUF]				= "CONFIG_HWCTX/REMOVE_DBG_BUF",
	[ARM_HWCTX_CONFIG_DEFAULT]				= "CONFIG_HWCTX/*unsupported-type*",

	[ARM_EXEC_CMD_EXEC_BUF]					= "EXEC_CMD/EXEC_BUF",
	[ARM_EXEC_CMD_DEFAULT]					= "EXEC_CMD/*unsupported-type*",
};

void amdxdna_arm_hit(enum amdxdna_arm_id id)
{
	if (WARN_ON_ONCE(id >= AMDXDNA_ARM_COUNT))
		return;
	atomic64_inc(&arm_hits[id]);
}

static int amdxdna_arm_coverage_show(struct seq_file *m, void *unused)
{
	int i;

	for (i = 0; i < AMDXDNA_ARM_COUNT; i++)
		seq_printf(m, "%-48s %lld\n", arm_names[i],
			  atomic64_read(&arm_hits[i]));
	return 0;
}
DEFINE_SHOW_ATTRIBUTE(amdxdna_arm_coverage);

void amdxdna_arm_coverage_debugfs_init(struct dentry *parent)
{
	debugfs_create_file("arm_coverage", 0400, parent, NULL,
			    &amdxdna_arm_coverage_fops);
}

void amdxdna_arm_coverage_dump_dmesg(void)
{
	int i;

	pr_info("amdxdna arm_coverage: dump on remove\n");
	for (i = 0; i < AMDXDNA_ARM_COUNT; i++)
		pr_info("amdxdna arm_coverage: %-48s %lld\n", arm_names[i],
			atomic64_read(&arm_hits[i]));
}
