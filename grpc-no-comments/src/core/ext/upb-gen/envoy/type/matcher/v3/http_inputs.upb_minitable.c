
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/http_inputs.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_type_matcher_v3_HttpRequestHeaderMatchInput__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init = {
  NULL,
  &envoy_type_matcher_v3_HttpRequestHeaderMatchInput__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpRequestHeaderMatchInput",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init;
static const upb_MiniTableField envoy_type_matcher_v3_HttpRequestTrailerMatchInput__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init = {
  NULL,
  &envoy_type_matcher_v3_HttpRequestTrailerMatchInput__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpRequestTrailerMatchInput",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init;
static const upb_MiniTableField envoy_type_matcher_v3_HttpResponseHeaderMatchInput__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init = {
  NULL,
  &envoy_type_matcher_v3_HttpResponseHeaderMatchInput__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpResponseHeaderMatchInput",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init;
static const upb_MiniTableField envoy_type_matcher_v3_HttpResponseTrailerMatchInput__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init = {
  NULL,
  &envoy_type_matcher_v3_HttpResponseTrailerMatchInput__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpResponseTrailerMatchInput",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init;
static const upb_MiniTableField envoy_type_matcher_v3_HttpRequestQueryParamMatchInput__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init = {
  NULL,
  &envoy_type_matcher_v3_HttpRequestQueryParamMatchInput__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpRequestQueryParamMatchInput",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init,
  &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init,
  &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init,
  &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init,
  &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_http_inputs_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
