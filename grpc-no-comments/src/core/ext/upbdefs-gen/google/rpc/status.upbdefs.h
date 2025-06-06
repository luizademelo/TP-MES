
#ifndef GOOGLE_RPC_STATUS_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_RPC_STATUS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_rpc_status_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_rpc_Status_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_rpc_status_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.rpc.Status");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
