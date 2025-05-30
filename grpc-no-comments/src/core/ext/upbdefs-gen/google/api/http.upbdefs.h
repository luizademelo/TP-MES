
#ifndef GOOGLE_API_HTTP_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_API_HTTP_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_api_http_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_api_Http_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_http_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.Http");
}

UPB_INLINE const upb_MessageDef *google_api_HttpRule_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_http_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.HttpRule");
}

UPB_INLINE const upb_MessageDef *google_api_CustomHttpPattern_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_http_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.CustomHttpPattern");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
