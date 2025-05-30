
#ifndef ENVOY_CONFIG_CORE_V3_SUBSTITUTION_FORMAT_STRING_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_SUBSTITUTION_FORMAT_STRING_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_substitution_format_string_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_JsonFormatOptions_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_substitution_format_string_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.JsonFormatOptions");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SubstitutionFormatString_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_substitution_format_string_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SubstitutionFormatString");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
