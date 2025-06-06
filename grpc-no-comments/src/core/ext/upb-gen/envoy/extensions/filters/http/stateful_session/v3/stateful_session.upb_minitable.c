
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/filters/http/stateful_session/v3/stateful_session.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_filters_http_stateful_session_v3_StatefulSession__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_stateful_session_v3_StatefulSession__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init = {
  &envoy_extensions_filters_http_stateful_session_v3_StatefulSession__submsgs[0],
  &envoy_extensions_filters_http_stateful_session_v3_StatefulSession__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.stateful_session.v3.StatefulSession",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init_ptr = &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init = {
  &envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute__submsgs[0],
  &envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.stateful_session.v3.StatefulSessionPerRoute",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000801000008, &upb_pob1_1bt},
    {0x0010000802000012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init_ptr = &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init,
  &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init,
};

const upb_MiniTableFile envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
