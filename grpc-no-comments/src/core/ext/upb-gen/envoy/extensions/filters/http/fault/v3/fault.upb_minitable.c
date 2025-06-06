
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/filters/http/fault/v3/fault.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/extensions/filters/common/fault/v3/fault.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_filters_http_fault_v3_FaultAbort__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_fault_v3_FaultAbort__fields[4] = {
  {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init = {
  &envoy_extensions_filters_http_fault_v3_FaultAbort__submsgs[0],
  &envoy_extensions_filters_http_fault_v3_FaultAbort__fields[0],
  UPB_SIZE(24, 32), 4, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.fault.v3.FaultAbort",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c02000010, &upb_pov4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c04010022, &upb_pom_1bt_max64b},
    {0x0018000c05000028, &upb_pov4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init_ptr = &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init;
const upb_MiniTable envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.fault.v3.FaultAbort.HeaderAbort",
#endif
};

const upb_MiniTable* envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init_ptr = &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_filters_http_fault_v3_HTTPFault__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_fault_v3_HTTPFault__fields[16] = {
  {1, UPB_SIZE(12, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 152), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 176), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 184), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {10, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(72, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(80, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(88, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(96, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {15, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(36, 192), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init = {
  &envoy_extensions_filters_http_fault_v3_HTTPFault__submsgs[0],
  &envoy_extensions_filters_http_fault_v3_HTTPFault__fields[0],
  UPB_SIZE(104, 200), 16, kUpb_ExtMode_NonExtendable, 16, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.fault.v3.HTTPFault",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x00a000003f020022, &upb_prm_1bt_maxmaxb},
    {0x00a800003f00002a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000042, &upb_pss_1bt},
    {0x003000003f00004a, &upb_pss_1bt},
    {0x004000003f000052, &upb_pss_1bt},
    {0x005000003f00005a, &upb_pss_1bt},
    {0x006000003f000062, &upb_pss_1bt},
    {0x007000003f00006a, &upb_pss_1bt},
    {0x008000003f000072, &upb_pss_1bt},
    {0x000900003f000078, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init_ptr = &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init,
  &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init,
  &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init,
};

const upb_MiniTableFile envoy_extensions_filters_http_fault_v3_fault_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
