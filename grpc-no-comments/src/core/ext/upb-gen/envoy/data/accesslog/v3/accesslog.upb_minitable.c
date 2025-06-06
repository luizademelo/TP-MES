
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/data/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_TCPAccessLogEntry__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__AccessLogCommon_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__ConnectionProperties_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_TCPAccessLogEntry__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init = {
  &envoy_data_accesslog_v3_TCPAccessLogEntry__submsgs[0],
  &envoy_data_accesslog_v3_TCPAccessLogEntry__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.TCPAccessLogEntry",
#endif
};

const upb_MiniTable* envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init_ptr = &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_HTTPAccessLogEntry__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__AccessLogCommon_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_HTTPAccessLogEntry__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init = {
  &envoy_data_accesslog_v3_HTTPAccessLogEntry__submsgs[0],
  &envoy_data_accesslog_v3_HTTPAccessLogEntry__fields[0],
  UPB_SIZE(32, 40), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPAccessLogEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init_ptr = &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_ConnectionProperties__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__ConnectionProperties_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_ConnectionProperties__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.ConnectionProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv8_1bt},
    {0x001000003f000010, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__ConnectionProperties_msg_init_ptr = &envoy__data__accesslog__v3__ConnectionProperties_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_AccessLogCommon__submsgs[19] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__TLSProperties_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__ResponseFlags_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_AccessLogCommon__fields[33] = {
  {1, UPB_SIZE(144, 120), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 128), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 136), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 144), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 152), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 160), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 168), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 176), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(40, 184), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(44, 192), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(48, 200), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(52, 208), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(56, 216), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(60, 224), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(96, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(64, 232), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(68, 240), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(104, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(112, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(72, 248), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(84, 272), 80, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(88, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {25, UPB_SIZE(120, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {26, UPB_SIZE(128, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {27, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {28, UPB_SIZE(136, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {29, UPB_SIZE(152, 280), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {30, UPB_SIZE(160, 288), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {31, UPB_SIZE(168, 296), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {32, UPB_SIZE(176, 304), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {33, UPB_SIZE(92, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__AccessLogCommon_msg_init = {
  &envoy_data_accesslog_v3_AccessLogCommon__submsgs[0],
  &envoy_data_accesslog_v3_AccessLogCommon__fields[0],
  UPB_SIZE(184, 312), 33, kUpb_ExtMode_NonExtendable, 33, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.AccessLogCommon",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x007800003f000009, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f00007a, &upb_pss_1bt},
    {0x013000003f000280, &upb_psv8_2bt},
    {0x001000003f000288, &upb_psv4_2bt},
    {0x002800003f000192, &upb_pss_2bt},
    {0x003800003f00019a, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f0001c0, &upb_psv4_2bt},
    {0x004800003f0001ca, &upb_pss_2bt},
    {0x005800003f0001d2, &upb_pss_2bt},
    {0x000b00003f0001d8, &upb_psb1_2bt},
    {0x006800003f0001e2, &upb_pss_2bt},
    {0x011800003f0001e8, &upb_psv8_2bt},
    {0x012000003f0001f0, &upb_psv8_2bt},
    {0x012800003f0001f8, &upb_psv8_2bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__AccessLogCommon_msg_init_ptr = &envoy__data__accesslog__v3__AccessLogCommon_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_AccessLogCommon_FilterStateObjectsEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_AccessLogCommon_FilterStateObjectsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init = {
  &envoy_data_accesslog_v3_AccessLogCommon_FilterStateObjectsEntry__submsgs[0],
  &envoy_data_accesslog_v3_AccessLogCommon_FilterStateObjectsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.AccessLogCommon.FilterStateObjectsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init_ptr = &envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_AccessLogCommon_CustomTagsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_AccessLogCommon_CustomTagsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.AccessLogCommon.CustomTagsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init_ptr = &envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_ResponseFlags__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_ResponseFlags__fields[28] = {
  {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {8, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {9, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {10, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {12, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(36, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {16, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, 24, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {18, 25, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {19, 26, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {20, 27, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {21, 28, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {22, 29, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {23, 30, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {24, 31, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {25, 32, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {26, 33, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {27, 34, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {28, 35, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__ResponseFlags_msg_init = {
  &envoy_data_accesslog_v3_ResponseFlags__submsgs[0],
  &envoy_data_accesslog_v3_ResponseFlags__fields[0],
  UPB_SIZE(40, 48), 28, kUpb_ExtMode_NonExtendable, 28, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.ResponseFlags",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000008, &upb_psb1_1bt},
    {0x000a00003f000010, &upb_psb1_1bt},
    {0x000b00003f000018, &upb_psb1_1bt},
    {0x000c00003f000020, &upb_psb1_1bt},
    {0x000d00003f000028, &upb_psb1_1bt},
    {0x000e00003f000030, &upb_psb1_1bt},
    {0x000f00003f000038, &upb_psb1_1bt},
    {0x001000003f000040, &upb_psb1_1bt},
    {0x001100003f000048, &upb_psb1_1bt},
    {0x001200003f000050, &upb_psb1_1bt},
    {0x001300003f000058, &upb_psb1_1bt},
    {0x001400003f000060, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001500003f000070, &upb_psb1_1bt},
    {0x001600003f000078, &upb_psb1_1bt},
    {0x001700003f000180, &upb_psb1_2bt},
    {0x001800003f000188, &upb_psb1_2bt},
    {0x001900003f000190, &upb_psb1_2bt},
    {0x001a00003f000198, &upb_psb1_2bt},
    {0x001b00003f0001a0, &upb_psb1_2bt},
    {0x001c00003f0001a8, &upb_psb1_2bt},
    {0x001d00003f0001b0, &upb_psb1_2bt},
    {0x001e00003f0001b8, &upb_psb1_2bt},
    {0x001f00003f0001c0, &upb_psb1_2bt},
    {0x002000003f0001c8, &upb_psb1_2bt},
    {0x002100003f0001d0, &upb_psb1_2bt},
    {0x002200003f0001d8, &upb_psb1_2bt},
    {0x002300003f0001e0, &upb_psb1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__ResponseFlags_msg_init_ptr = &envoy__data__accesslog__v3__ResponseFlags_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_ResponseFlags_Unauthorized__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_ResponseFlags_Unauthorized__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.ResponseFlags.Unauthorized",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init_ptr = &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_TLSProperties__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_TLSProperties__fields[7] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__TLSProperties_msg_init = {
  &envoy_data_accesslog_v3_TLSProperties__submsgs[0],
  &envoy_data_accesslog_v3_TLSProperties__fields[0],
  UPB_SIZE(56, 88), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.TLSProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000032, &upb_pss_1bt},
    {0x003000003f00003a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__TLSProperties_msg_init_ptr = &envoy__data__accesslog__v3__TLSProperties_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_TLSProperties_CertificateProperties__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_TLSProperties_CertificateProperties__fields[3] = {
  {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init = {
  &envoy_data_accesslog_v3_TLSProperties_CertificateProperties__submsgs[0],
  &envoy_data_accesslog_v3_TLSProperties_CertificateProperties__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.TLSProperties.CertificateProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f00000a, &upb_prm_1bt_max64b},
    {0x000800003f000012, &upb_pss_1bt},
    {0x001800003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init_ptr = &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.TLSProperties.CertificateProperties.SubjectAltName",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
    {0x0010000802000012, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init_ptr = &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_HTTPRequestProperties__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_HTTPRequestProperties__fields[15] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(64, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(72, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(80, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(88, 152), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(96, 160), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(104, 176), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(112, 184), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPRequestProperties_msg_init = {
  &envoy_data_accesslog_v3_HTTPRequestProperties__submsgs[0],
  &envoy_data_accesslog_v3_HTTPRequestProperties__fields[0],
  UPB_SIZE(120, 192), 15, kUpb_ExtMode_NonExtendable, 15, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPRequestProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_pss_1bt},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f00002a, &upb_pss_1bt},
    {0x004000003f000032, &upb_pss_1bt},
    {0x005000003f00003a, &upb_pss_1bt},
    {0x006000003f000042, &upb_pss_1bt},
    {0x007000003f00004a, &upb_pss_1bt},
    {0x008000003f000052, &upb_pss_1bt},
    {0x009800003f000058, &upb_psv8_1bt},
    {0x00a000003f000060, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00b000003f000070, &upb_psv8_1bt},
    {0x00b800003f000078, &upb_psv8_1bt},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPRequestProperties_msg_init_ptr = &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_HTTPRequestProperties_RequestHeadersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_HTTPRequestProperties_RequestHeadersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPRequestProperties.RequestHeadersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init_ptr = &envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init;
static const upb_MiniTableSubInternal envoy_data_accesslog_v3_HTTPResponseProperties__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_data_accesslog_v3_HTTPResponseProperties__fields[8] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 48), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(48, 72), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(56, 80), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPResponseProperties_msg_init = {
  &envoy_data_accesslog_v3_HTTPResponseProperties__submsgs[0],
  &envoy_data_accesslog_v3_HTTPResponseProperties__fields[0],
  UPB_SIZE(64, 88), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPResponseProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f000010, &upb_psv8_1bt},
    {0x003000003f000018, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000032, &upb_pss_1bt},
    {0x004800003f000038, &upb_psv8_1bt},
    {0x005000003f000040, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPResponseProperties_msg_init_ptr = &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_HTTPResponseProperties_ResponseHeadersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_HTTPResponseProperties_ResponseHeadersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPResponseProperties.ResponseHeadersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init_ptr = &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init;
static const upb_MiniTableField envoy_data_accesslog_v3_HTTPResponseProperties_ResponseTrailersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init = {
  NULL,
  &envoy_data_accesslog_v3_HTTPResponseProperties_ResponseTrailersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.data.accesslog.v3.HTTPResponseProperties.ResponseTrailersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init_ptr = &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init;
static const upb_MiniTable *messages_layout[16] = {
  &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init,
  &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init,
  &envoy__data__accesslog__v3__ConnectionProperties_msg_init,
  &envoy__data__accesslog__v3__AccessLogCommon_msg_init,
  &envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init,
  &envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init,
  &envoy__data__accesslog__v3__ResponseFlags_msg_init,
  &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init,
  &envoy__data__accesslog__v3__TLSProperties_msg_init,
  &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init,
  &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init,
  &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init,
  &envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init,
  &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init,
  &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init,
  &envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init,
};

const upb_MiniTableFile envoy_data_accesslog_v3_accesslog_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  16,
  0,
  0,
};

#include "upb/port/undef.inc"
