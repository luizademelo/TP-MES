
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_core_v3_SocketOption__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption__SocketType_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_SocketOption__fields[7] = {
  {1, 24, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), UPB_SIZE(-21, -17), kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(48, 40), UPB_SIZE(-21, -17), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__SocketOption_msg_init = {
  &envoy_config_core_v3_SocketOption__submsgs[0],
  &envoy_config_core_v3_SocketOption__fields[0],
  UPB_SIZE(56, 80), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketOption",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f00000a, &upb_pss_1bt},
    {0x003800003f000010, &upb_psv8_1bt},
    {0x004000003f000018, &upb_psv8_1bt},
    {0x0028001004000020, &upb_pov8_1bt},
    {0x002800100500002a, &upb_pob_1bt},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__SocketOption_msg_init_ptr = &envoy__config__core__v3__SocketOption_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_SocketOption_SocketType__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption__SocketType__Stream_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption__SocketType__Datagram_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_SocketOption_SocketType__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__SocketOption__SocketType_msg_init = {
  &envoy_config_core_v3_SocketOption_SocketType__submsgs[0],
  &envoy_config_core_v3_SocketOption_SocketType__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketOption.SocketType",
#endif
};

const upb_MiniTable* envoy__config__core__v3__SocketOption__SocketType_msg_init_ptr = &envoy__config__core__v3__SocketOption__SocketType_msg_init;
const upb_MiniTable envoy__config__core__v3__SocketOption__SocketType__Stream_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketOption.SocketType.Stream",
#endif
};

const upb_MiniTable* envoy__config__core__v3__SocketOption__SocketType__Stream_msg_init_ptr = &envoy__config__core__v3__SocketOption__SocketType__Stream_msg_init;
const upb_MiniTable envoy__config__core__v3__SocketOption__SocketType__Datagram_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketOption.SocketType.Datagram",
#endif
};

const upb_MiniTable* envoy__config__core__v3__SocketOption__SocketType__Datagram_msg_init_ptr = &envoy__config__core__v3__SocketOption__SocketType__Datagram_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_SocketOptionsOverride__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_SocketOptionsOverride__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__SocketOptionsOverride_msg_init = {
  &envoy_config_core_v3_SocketOptionsOverride__submsgs[0],
  &envoy_config_core_v3_SocketOptionsOverride__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketOptionsOverride",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* envoy__config__core__v3__SocketOptionsOverride_msg_init_ptr = &envoy__config__core__v3__SocketOptionsOverride_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__config__core__v3__SocketOption_msg_init,
  &envoy__config__core__v3__SocketOption__SocketType_msg_init,
  &envoy__config__core__v3__SocketOption__SocketType__Stream_msg_init,
  &envoy__config__core__v3__SocketOption__SocketType__Datagram_msg_init,
  &envoy__config__core__v3__SocketOptionsOverride_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_socket_option_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
