/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Throwaway instrumentation for amdxdna-arm-coverage-instrumentation.
 * Not upstream material as-is: one counter per ioctl dispatch arm on the
 * AIE2 path (this box's architecture, PCI id 17f0), incremented at the top
 * of each `case` in aie2_get_info/aie2_get_array/aie2_set_state (aie2_pci.c),
 * aie2_hwctx_config (aie2_ctx.c) and amdxdna_drm_submit_cmd_ioctl
 * (amdxdna_ctx.c). Dumped via debugfs (arm_coverage, parseable) and once
 * more to dmesg on module remove.
 */
#ifndef _AMDXDNA_ARM_COVERAGE_H_
#define _AMDXDNA_ARM_COVERAGE_H_

struct dentry;

enum amdxdna_arm_id {
	/* GET_INFO (aie2_get_info, aie2_pci.c) */
	ARM_GET_INFO_QUERY_AIE_STATUS,
	ARM_GET_INFO_QUERY_AIE_METADATA,
	ARM_GET_INFO_QUERY_AIE_VERSION,
	ARM_GET_INFO_QUERY_CLOCK_METADATA,
	ARM_GET_INFO_QUERY_SENSORS,
	ARM_GET_INFO_QUERY_HW_CONTEXTS,
	ARM_GET_INFO_QUERY_FIRMWARE_VERSION,
	ARM_GET_INFO_GET_POWER_MODE,
	ARM_GET_INFO_QUERY_TELEMETRY,
	ARM_GET_INFO_QUERY_RESOURCE_INFO,
	ARM_GET_INFO_GET_FORCE_PREEMPT_STATE,
	ARM_GET_INFO_GET_FRAME_BOUNDARY_PREEMPT_STATE,
	ARM_GET_INFO_GET_AUTO_COREDUMP,
	ARM_GET_INFO_DEFAULT,

	/* GET_ARRAY (aie2_get_array, aie2_pci.c) */
	ARM_GET_ARRAY_HW_CONTEXT_ALL,
	ARM_GET_ARRAY_HW_CONTEXT_BY_ID,
	ARM_GET_ARRAY_HW_LAST_ASYNC_ERR,
	ARM_GET_ARRAY_AIE_COREDUMP,
	ARM_GET_ARRAY_BO_USAGE,
	ARM_GET_ARRAY_AIE_TILE_READ,
	ARM_GET_ARRAY_FW_LOG,
	ARM_GET_ARRAY_FW_LOG_CONFIG,
	ARM_GET_ARRAY_FW_TRACE,
	ARM_GET_ARRAY_FW_TRACE_CONFIG,
	ARM_GET_ARRAY_DEFAULT,

	/* SET_STATE (aie2_set_state, aie2_pci.c) */
	ARM_SET_STATE_SET_POWER_MODE,
	ARM_SET_STATE_SET_FORCE_PREEMPT,
	ARM_SET_STATE_SET_FRAME_BOUNDARY_PREEMPT,
	ARM_SET_STATE_AIE_TILE_WRITE,
	ARM_SET_STATE_SET_FW_LOG_STATE,
	ARM_SET_STATE_SET_FW_TRACE_STATE,
	ARM_SET_STATE_SET_AUTO_COREDUMP,
	ARM_SET_STATE_DEFAULT,

	/* CONFIG_HWCTX (aie2_hwctx_config, aie2_ctx.c) */
	ARM_HWCTX_CONFIG_CU,
	ARM_HWCTX_ASSIGN_DBG_BUF,
	ARM_HWCTX_REMOVE_DBG_BUF,
	ARM_HWCTX_CONFIG_DEFAULT,

	/* EXEC_CMD (amdxdna_drm_submit_cmd_ioctl, amdxdna_ctx.c) */
	ARM_EXEC_CMD_EXEC_BUF,
	ARM_EXEC_CMD_DEFAULT,

	AMDXDNA_ARM_COUNT,
};

void amdxdna_arm_hit(enum amdxdna_arm_id id);
void amdxdna_arm_coverage_debugfs_init(struct dentry *parent);
void amdxdna_arm_coverage_dump_dmesg(void);

#endif /* _AMDXDNA_ARM_COVERAGE_H_ */
