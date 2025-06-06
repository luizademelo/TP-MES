
#ifndef ENVOY_ADMIN_V3_SERVER_INFO_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_SERVER_INFO_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/server_info.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_ServerInfo { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ServerInfo;
typedef struct envoy_admin_v3_CommandLineOptions { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_CommandLineOptions;
struct envoy_config_core_v3_Node;
struct google_protobuf_Duration;

typedef enum {
  envoy_admin_v3_CommandLineOptions_Gradual = 0,
  envoy_admin_v3_CommandLineOptions_Immediate = 1
} envoy_admin_v3_CommandLineOptions_DrainStrategy;

typedef enum {
  envoy_admin_v3_CommandLineOptions_v4 = 0,
  envoy_admin_v3_CommandLineOptions_v6 = 1
} envoy_admin_v3_CommandLineOptions_IpVersion;

typedef enum {
  envoy_admin_v3_CommandLineOptions_Serve = 0,
  envoy_admin_v3_CommandLineOptions_Validate = 1,
  envoy_admin_v3_CommandLineOptions_InitOnly = 2
} envoy_admin_v3_CommandLineOptions_Mode;

typedef enum {
  envoy_admin_v3_ServerInfo_LIVE = 0,
  envoy_admin_v3_ServerInfo_DRAINING = 1,
  envoy_admin_v3_ServerInfo_PRE_INITIALIZING = 2,
  envoy_admin_v3_ServerInfo_INITIALIZING = 3
} envoy_admin_v3_ServerInfo_State;

UPB_INLINE envoy_admin_v3_ServerInfo* envoy_admin_v3_ServerInfo_new(upb_Arena* arena) {
  return (envoy_admin_v3_ServerInfo*)_upb_Message_New(&envoy__admin__v3__ServerInfo_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ServerInfo* envoy_admin_v3_ServerInfo_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ServerInfo* ret = envoy_admin_v3_ServerInfo_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ServerInfo_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ServerInfo* envoy_admin_v3_ServerInfo_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ServerInfo* ret = envoy_admin_v3_ServerInfo_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ServerInfo_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ServerInfo_serialize(const envoy_admin_v3_ServerInfo* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ServerInfo_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ServerInfo_serialize_ex(const envoy_admin_v3_ServerInfo* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ServerInfo_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_version(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ServerInfo_version(const envoy_admin_v3_ServerInfo* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_state(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_ServerInfo_state(const envoy_admin_v3_ServerInfo* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_uptime_current_epoch(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_admin_v3_ServerInfo_uptime_current_epoch(const envoy_admin_v3_ServerInfo* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ServerInfo_has_uptime_current_epoch(const envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_uptime_all_epochs(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_admin_v3_ServerInfo_uptime_all_epochs(const envoy_admin_v3_ServerInfo* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ServerInfo_has_uptime_all_epochs(const envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_hot_restart_version(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ServerInfo_hot_restart_version(const envoy_admin_v3_ServerInfo* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_command_line_options(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_CommandLineOptions* envoy_admin_v3_ServerInfo_command_line_options(const envoy_admin_v3_ServerInfo* msg) {
  const envoy_admin_v3_CommandLineOptions* default_val = NULL;
  const envoy_admin_v3_CommandLineOptions* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CommandLineOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ServerInfo_has_command_line_options(const envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_clear_node(envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Node* envoy_admin_v3_ServerInfo_node(const envoy_admin_v3_ServerInfo* msg) {
  const struct envoy_config_core_v3_Node* default_val = NULL;
  const struct envoy_config_core_v3_Node* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ServerInfo_has_node(const envoy_admin_v3_ServerInfo* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_ServerInfo_set_version(envoy_admin_v3_ServerInfo *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_state(envoy_admin_v3_ServerInfo *msg, int32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_uptime_current_epoch(envoy_admin_v3_ServerInfo *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_admin_v3_ServerInfo_mutable_uptime_current_epoch(envoy_admin_v3_ServerInfo* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_admin_v3_ServerInfo_uptime_current_epoch(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_admin_v3_ServerInfo_set_uptime_current_epoch(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_uptime_all_epochs(envoy_admin_v3_ServerInfo *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_admin_v3_ServerInfo_mutable_uptime_all_epochs(envoy_admin_v3_ServerInfo* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_admin_v3_ServerInfo_uptime_all_epochs(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_admin_v3_ServerInfo_set_uptime_all_epochs(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_hot_restart_version(envoy_admin_v3_ServerInfo *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_command_line_options(envoy_admin_v3_ServerInfo *msg, envoy_admin_v3_CommandLineOptions* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CommandLineOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_CommandLineOptions* envoy_admin_v3_ServerInfo_mutable_command_line_options(envoy_admin_v3_ServerInfo* msg, upb_Arena* arena) {
  struct envoy_admin_v3_CommandLineOptions* sub = (struct envoy_admin_v3_CommandLineOptions*)envoy_admin_v3_ServerInfo_command_line_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_CommandLineOptions*)_upb_Message_New(&envoy__admin__v3__CommandLineOptions_msg_init, arena);
    if (sub) envoy_admin_v3_ServerInfo_set_command_line_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ServerInfo_set_node(envoy_admin_v3_ServerInfo *msg, struct envoy_config_core_v3_Node* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Node* envoy_admin_v3_ServerInfo_mutable_node(envoy_admin_v3_ServerInfo* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Node* sub = (struct envoy_config_core_v3_Node*)envoy_admin_v3_ServerInfo_node(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Node*)_upb_Message_New(&envoy__config__core__v3__Node_msg_init, arena);
    if (sub) envoy_admin_v3_ServerInfo_set_node(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_CommandLineOptions* envoy_admin_v3_CommandLineOptions_new(upb_Arena* arena) {
  return (envoy_admin_v3_CommandLineOptions*)_upb_Message_New(&envoy__admin__v3__CommandLineOptions_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_CommandLineOptions* envoy_admin_v3_CommandLineOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_CommandLineOptions* ret = envoy_admin_v3_CommandLineOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CommandLineOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_CommandLineOptions* envoy_admin_v3_CommandLineOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_CommandLineOptions* ret = envoy_admin_v3_CommandLineOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CommandLineOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_CommandLineOptions_serialize(const envoy_admin_v3_CommandLineOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CommandLineOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_CommandLineOptions_serialize_ex(const envoy_admin_v3_CommandLineOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CommandLineOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_base_id(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(168, 240), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_CommandLineOptions_base_id(const envoy_admin_v3_CommandLineOptions* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(168, 240), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_concurrency(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_admin_v3_CommandLineOptions_concurrency(const envoy_admin_v3_CommandLineOptions* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_config_path(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(68, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_config_path(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(68, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_config_yaml(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(76, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_config_yaml(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(76, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_allow_unknown_static_fields(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_allow_unknown_static_fields(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_admin_address_path(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(84, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_admin_address_path(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(84, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_local_address_ip_version(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {7, 28, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_CommandLineOptions_local_address_ip_version(const envoy_admin_v3_CommandLineOptions* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {7, 28, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_log_level(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(92, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_log_level(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(92, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_component_log_level(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(100, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_component_log_level(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(100, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_log_format(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(108, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_log_format(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, UPB_SIZE(108, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_log_path(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(116, 144), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_log_path(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {11, UPB_SIZE(116, 144), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_service_cluster(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(124, 160), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_service_cluster(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {13, UPB_SIZE(124, 160), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_service_node(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(132, 176), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_service_node(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {14, UPB_SIZE(132, 176), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_service_zone(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(140, 192), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_service_zone(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {15, UPB_SIZE(140, 192), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_file_flush_interval(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(32, 248), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_file_flush_interval(const envoy_admin_v3_CommandLineOptions* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(32, 248), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_has_file_flush_interval(const envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(32, 248), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_drain_time(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(36, 256), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_drain_time(const envoy_admin_v3_CommandLineOptions* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(36, 256), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_has_drain_time(const envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(36, 256), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_parent_shutdown_time(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(40, 264), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_parent_shutdown_time(const envoy_admin_v3_CommandLineOptions* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(40, 264), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_has_parent_shutdown_time(const envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(40, 264), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_mode(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(44, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_CommandLineOptions_mode(const envoy_admin_v3_CommandLineOptions* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {19, UPB_SIZE(44, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_disable_hot_restart(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {22, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_disable_hot_restart(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {22, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_enable_mutex_tracing(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_enable_mutex_tracing(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_restart_epoch(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(48, 36), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_admin_v3_CommandLineOptions_restart_epoch(const envoy_admin_v3_CommandLineOptions* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {24, UPB_SIZE(48, 36), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_cpuset_threads(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {25, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_cpuset_threads(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {25, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_reject_unknown_dynamic_fields(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {26, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_reject_unknown_dynamic_fields(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {26, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_log_format_escaped(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {27, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_log_format_escaped(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {27, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_disabled_extensions(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_admin_v3_CommandLineOptions_disabled_extensions(const envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  const upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_CommandLineOptions_disabled_extensions_upb_array(const envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  const upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_CommandLineOptions_disabled_extensions_mutable_upb_array(envoy_admin_v3_CommandLineOptions* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_ignore_unknown_dynamic_fields(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {30, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_ignore_unknown_dynamic_fields(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {30, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_use_dynamic_base_id(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {31, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_use_dynamic_base_id(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {31, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_base_id_path(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(148, 208), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_base_id_path(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {32, UPB_SIZE(148, 208), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_drain_strategy(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(56, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_CommandLineOptions_drain_strategy(const envoy_admin_v3_CommandLineOptions* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {33, UPB_SIZE(56, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_enable_fine_grain_logging(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {34, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_enable_fine_grain_logging(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {34, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_socket_path(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(156, 224), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CommandLineOptions_socket_path(const envoy_admin_v3_CommandLineOptions* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {35, UPB_SIZE(156, 224), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_socket_mode(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(60, 44), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_admin_v3_CommandLineOptions_socket_mode(const envoy_admin_v3_CommandLineOptions* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {36, UPB_SIZE(60, 44), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_enable_core_dump(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {37, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_enable_core_dump(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {37, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_stats_tag(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_admin_v3_CommandLineOptions_stats_tag(const envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  const upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_CommandLineOptions_stats_tag_upb_array(const envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  const upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_CommandLineOptions_stats_tag_mutable_upb_array(envoy_admin_v3_CommandLineOptions* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_skip_hot_restart_on_no_parent(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {39, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_skip_hot_restart_on_no_parent(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {39, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_skip_hot_restart_parent_stats(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {40, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_skip_hot_restart_parent_stats(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {40, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_clear_skip_deprecated_logs(envoy_admin_v3_CommandLineOptions* msg) {
  const upb_MiniTableField field = {41, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_skip_deprecated_logs(const envoy_admin_v3_CommandLineOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {41, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_base_id(envoy_admin_v3_CommandLineOptions *msg, uint64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(168, 240), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_concurrency(envoy_admin_v3_CommandLineOptions *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_config_path(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(68, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_config_yaml(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(76, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_allow_unknown_static_fields(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_admin_address_path(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(84, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_local_address_ip_version(envoy_admin_v3_CommandLineOptions *msg, int32_t value) {
  const upb_MiniTableField field = {7, 28, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_log_level(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(92, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_component_log_level(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(100, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_log_format(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, UPB_SIZE(108, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_log_path(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {11, UPB_SIZE(116, 144), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_service_cluster(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {13, UPB_SIZE(124, 160), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_service_node(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {14, UPB_SIZE(132, 176), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_service_zone(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {15, UPB_SIZE(140, 192), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_file_flush_interval(envoy_admin_v3_CommandLineOptions *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(32, 248), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_mutable_file_flush_interval(envoy_admin_v3_CommandLineOptions* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_admin_v3_CommandLineOptions_file_flush_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_admin_v3_CommandLineOptions_set_file_flush_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_drain_time(envoy_admin_v3_CommandLineOptions *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(36, 256), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_mutable_drain_time(envoy_admin_v3_CommandLineOptions* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_admin_v3_CommandLineOptions_drain_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_admin_v3_CommandLineOptions_set_drain_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_parent_shutdown_time(envoy_admin_v3_CommandLineOptions *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(40, 264), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_admin_v3_CommandLineOptions_mutable_parent_shutdown_time(envoy_admin_v3_CommandLineOptions* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_admin_v3_CommandLineOptions_parent_shutdown_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_admin_v3_CommandLineOptions_set_parent_shutdown_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_mode(envoy_admin_v3_CommandLineOptions *msg, int32_t value) {
  const upb_MiniTableField field = {19, UPB_SIZE(44, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_disable_hot_restart(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {22, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_enable_mutex_tracing(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_restart_epoch(envoy_admin_v3_CommandLineOptions *msg, uint32_t value) {
  const upb_MiniTableField field = {24, UPB_SIZE(48, 36), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_cpuset_threads(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {25, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_reject_unknown_dynamic_fields(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {26, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_log_format_escaped(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {27, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_admin_v3_CommandLineOptions_mutable_disabled_extensions(envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_admin_v3_CommandLineOptions_resize_disabled_extensions(envoy_admin_v3_CommandLineOptions* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_add_disabled_extensions(envoy_admin_v3_CommandLineOptions* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {28, UPB_SIZE(52, 272), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_ignore_unknown_dynamic_fields(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {30, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_use_dynamic_base_id(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {31, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_base_id_path(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {32, UPB_SIZE(148, 208), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_drain_strategy(envoy_admin_v3_CommandLineOptions *msg, int32_t value) {
  const upb_MiniTableField field = {33, UPB_SIZE(56, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_enable_fine_grain_logging(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {34, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_socket_path(envoy_admin_v3_CommandLineOptions *msg, upb_StringView value) {
  const upb_MiniTableField field = {35, UPB_SIZE(156, 224), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_socket_mode(envoy_admin_v3_CommandLineOptions *msg, uint32_t value) {
  const upb_MiniTableField field = {36, UPB_SIZE(60, 44), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_enable_core_dump(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {37, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_admin_v3_CommandLineOptions_mutable_stats_tag(envoy_admin_v3_CommandLineOptions* msg, size_t* size) {
  upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_admin_v3_CommandLineOptions_resize_stats_tag(envoy_admin_v3_CommandLineOptions* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_admin_v3_CommandLineOptions_add_stats_tag(envoy_admin_v3_CommandLineOptions* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {38, UPB_SIZE(64, 280), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_skip_hot_restart_on_no_parent(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {39, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_skip_hot_restart_parent_stats(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {40, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CommandLineOptions_set_skip_deprecated_logs(envoy_admin_v3_CommandLineOptions *msg, bool value) {
  const upb_MiniTableField field = {41, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
