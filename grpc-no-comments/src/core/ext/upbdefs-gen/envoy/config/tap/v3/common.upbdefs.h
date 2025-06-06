
#ifndef ENVOY_CONFIG_TAP_V3_COMMON_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_TAP_V3_COMMON_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_tap_v3_common_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_TapConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.TapConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_MatchPredicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.MatchPredicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_MatchPredicate_MatchSet_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.MatchPredicate.MatchSet");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_HttpHeadersMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.HttpHeadersMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_HttpGenericBodyMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.HttpGenericBodyMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_HttpGenericBodyMatch_GenericTextMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.HttpGenericBodyMatch.GenericTextMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_OutputConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.OutputConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_OutputSink_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.OutputSink");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_StreamingAdminSink_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.StreamingAdminSink");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_BufferedAdminSink_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.BufferedAdminSink");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_FilePerTapSink_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.FilePerTapSink");
}

UPB_INLINE const upb_MessageDef *envoy_config_tap_v3_StreamingGrpcSink_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_tap_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.tap.v3.StreamingGrpcSink");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
