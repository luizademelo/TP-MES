
#ifndef ENVOY_ADMIN_V3_CONFIG_DUMP_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_ADMIN_V3_CONFIG_DUMP_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_admin_v3_config_dump_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_BootstrapConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.BootstrapConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_SecretsConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.SecretsConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_SecretsConfigDump_DynamicSecret_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.SecretsConfigDump.DynamicSecret");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_SecretsConfigDump_StaticSecret_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.SecretsConfigDump.StaticSecret");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
