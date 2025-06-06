
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/protobuf/struct.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal google_protobuf_Struct__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct__FieldsEntry_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_Struct__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__Struct_msg_init = {
  &google_protobuf_Struct__submsgs[0],
  &google_protobuf_Struct__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.Struct",
#endif
};

const upb_MiniTable* google__protobuf__Struct_msg_init_ptr = &google__protobuf__Struct_msg_init;
static const upb_MiniTableSubInternal google_protobuf_Struct_FieldsEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Value_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_Struct_FieldsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__Struct__FieldsEntry_msg_init = {
  &google_protobuf_Struct_FieldsEntry__submsgs[0],
  &google_protobuf_Struct_FieldsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.Struct.FieldsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* google__protobuf__Struct__FieldsEntry_msg_init_ptr = &google__protobuf__Struct__FieldsEntry_msg_init;
static const upb_MiniTableSubInternal google_protobuf_Value__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__ListValue_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_Value__fields[6] = {
  {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, 16, -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 16, -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__Value_msg_init = {
  &google_protobuf_Value__submsgs[0],
  &google_protobuf_Value__fields[0],
  UPB_SIZE(24, 32), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.Value",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000801000008, &upb_pov4_1bt},
    {0x0010000802000011, &upb_pof8_1bt},
    {0x001000080300001a, &upb_pos_1bt},
    {0x0010000804000020, &upb_pob1_1bt},
    {0x001000080500002a, &upb_pom_1bt_max64b},
    {0x0010000806010032, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__Value_msg_init_ptr = &google__protobuf__Value_msg_init;
static const upb_MiniTableSubInternal google_protobuf_ListValue__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Value_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_ListValue__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__ListValue_msg_init = {
  &google_protobuf_ListValue__submsgs[0],
  &google_protobuf_ListValue__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.ListValue",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* google__protobuf__ListValue_msg_init_ptr = &google__protobuf__ListValue_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &google__protobuf__Struct_msg_init,
  &google__protobuf__Struct__FieldsEntry_msg_init,
  &google__protobuf__Value_msg_init,
  &google__protobuf__ListValue_msg_init,
};

const upb_MiniTableFile google_protobuf_struct_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
