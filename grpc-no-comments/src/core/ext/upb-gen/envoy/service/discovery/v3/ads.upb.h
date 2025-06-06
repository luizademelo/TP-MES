
#ifndef ENVOY_SERVICE_DISCOVERY_V3_ADS_PROTO_UPB_H__UPB_H_
#define ENVOY_SERVICE_DISCOVERY_V3_ADS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/service/discovery/v3/ads.upb_minitable.h"

#include "envoy/service/discovery/v3/discovery.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_service_discovery_v3_AdsDummy { upb_Message UPB_PRIVATE(base); } envoy_service_discovery_v3_AdsDummy;

UPB_INLINE envoy_service_discovery_v3_AdsDummy* envoy_service_discovery_v3_AdsDummy_new(upb_Arena* arena) {
  return (envoy_service_discovery_v3_AdsDummy*)_upb_Message_New(&envoy__service__discovery__v3__AdsDummy_msg_init, arena);
}
UPB_INLINE envoy_service_discovery_v3_AdsDummy* envoy_service_discovery_v3_AdsDummy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_discovery_v3_AdsDummy* ret = envoy_service_discovery_v3_AdsDummy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__discovery__v3__AdsDummy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_discovery_v3_AdsDummy* envoy_service_discovery_v3_AdsDummy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_discovery_v3_AdsDummy* ret = envoy_service_discovery_v3_AdsDummy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__discovery__v3__AdsDummy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_discovery_v3_AdsDummy_serialize(const envoy_service_discovery_v3_AdsDummy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__discovery__v3__AdsDummy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_discovery_v3_AdsDummy_serialize_ex(const envoy_service_discovery_v3_AdsDummy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__discovery__v3__AdsDummy_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
