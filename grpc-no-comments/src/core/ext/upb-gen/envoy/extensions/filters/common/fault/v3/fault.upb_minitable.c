
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/filters/common/fault/v3/fault.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_filters_common_fault_v3_FaultDelay__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__common__fault__v3__FaultDelay__HeaderDelay_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_common_fault_v3_FaultDelay__fields[3] = {
  {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init = {
  &envoy_extensions_filters_common_fault_v3_FaultDelay__submsgs[0],
  &envoy_extensions_filters_common_fault_v3_FaultDelay__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.common.fault.v3.FaultDelay",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c0300001a, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c0502002a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init_ptr = &envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init;
const upb_MiniTable envoy__extensions__filters__common__fault__v3__FaultDelay__HeaderDelay_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.common.fault.v3.FaultDelay.HeaderDelay",
#endif
};

const upb_MiniTable* envoy__extensions__filters__common__fault__v3__FaultDelay__HeaderDelay_msg_init_ptr = &envoy__extensions__filters__common__fault__v3__FaultDelay__HeaderDelay_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_filters_common_fault_v3_FaultRateLimit__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__common__fault__v3__FaultRateLimit__FixedLimit_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__common__fault__v3__FaultRateLimit__HeaderLimit_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_common_fault_v3_FaultRateLimit__fields[3] = {
  {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init = {
  &envoy_extensions_filters_common_fault_v3_FaultRateLimit__submsgs[0],
  &envoy_extensions_filters_common_fault_v3_FaultRateLimit__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.common.fault.v3.FaultRateLimit",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c0100000a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c0302001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init_ptr = &envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init;
static const upb_MiniTableField envoy_extensions_filters_common_fault_v3_FaultRateLimit_FixedLimit__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__common__fault__v3__FaultRateLimit__FixedLimit_msg_init = {
  NULL,
  &envoy_extensions_filters_common_fault_v3_FaultRateLimit_FixedLimit__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.common.fault.v3.FaultRateLimit.FixedLimit",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv8_1bt},
  })
};

const upb_MiniTable* envoy__extensions__filters__common__fault__v3__FaultRateLimit__FixedLimit_msg_init_ptr = &envoy__extensions__filters__common__fault__v3__FaultRateLimit__FixedLimit_msg_init;
const upb_MiniTable envoy__extensions__filters__common__fault__v3__FaultRateLimit__HeaderLimit_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.common.fault.v3.FaultRateLimit.HeaderLimit",
#endif
};

const upb_MiniTable* envoy__extensions__filters__common__fault__v3__FaultRateLimit__HeaderLimit_msg_init_ptr = &envoy__extensions__filters__common__fault__v3__FaultRateLimit__HeaderLimit_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init,
  &envoy__extensions__filters__common__fault__v3__FaultDelay__HeaderDelay_msg_init,
  &envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init,
  &envoy__extensions__filters__common__fault__v3__FaultRateLimit__FixedLimit_msg_init,
  &envoy__extensions__filters__common__fault__v3__FaultRateLimit__HeaderLimit_msg_init,
};

const upb_MiniTableFile envoy_extensions_filters_common_fault_v3_fault_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
