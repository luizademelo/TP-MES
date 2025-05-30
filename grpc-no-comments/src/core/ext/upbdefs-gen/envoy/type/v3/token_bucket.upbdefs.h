
#ifndef ENVOY_TYPE_V3_TOKEN_BUCKET_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_TYPE_V3_TOKEN_BUCKET_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_type_v3_token_bucket_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_type_v3_TokenBucket_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_v3_token_bucket_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.v3.TokenBucket");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
