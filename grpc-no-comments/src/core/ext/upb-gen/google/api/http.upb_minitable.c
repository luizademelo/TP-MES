
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/api/http.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal google_api_Http__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__HttpRule_msg_init_ptr},
};

static const upb_MiniTableField google_api_Http__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__Http_msg_init = {
  &google_api_Http__submsgs[0],
  &google_api_Http__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.Http",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max128b},
    {0x000800003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__Http_msg_init_ptr = &google__api__Http_msg_init;
static const upb_MiniTableSubInternal google_api_HttpRule__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__CustomHttpPattern_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__HttpRule_msg_init_ptr},
};

static const upb_MiniTableField google_api_HttpRule__fields[10] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__HttpRule_msg_init = {
  &google_api_HttpRule__submsgs[0],
  &google_api_HttpRule__fields[0],
  UPB_SIZE(48, 88), 10, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.HttpRule",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0040000802000012, &upb_pos_1bt},
    {0x004000080300001a, &upb_pos_1bt},
    {0x0040000804000022, &upb_pos_1bt},
    {0x004000080500002a, &upb_pos_1bt},
    {0x0040000806000032, &upb_pos_1bt},
    {0x002000003f00003a, &upb_pss_1bt},
    {0x0040000808000042, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005000003f01005a, &upb_prm_1bt_max128b},
    {0x003000003f000062, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__HttpRule_msg_init_ptr = &google__api__HttpRule_msg_init;
static const upb_MiniTableField google_api_CustomHttpPattern__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__CustomHttpPattern_msg_init = {
  NULL,
  &google_api_CustomHttpPattern__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.CustomHttpPattern",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__CustomHttpPattern_msg_init_ptr = &google__api__CustomHttpPattern_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &google__api__Http_msg_init,
  &google__api__HttpRule_msg_init,
  &google__api__CustomHttpPattern_msg_init,
};

const upb_MiniTableFile google_api_http_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
