
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/path.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_PathMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_PathMatcher__fields[1] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__PathMatcher_msg_init = {
  &envoy_type_matcher_v3_PathMatcher__submsgs[0],
  &envoy_type_matcher_v3_PathMatcher__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.PathMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__PathMatcher_msg_init_ptr = &envoy__type__matcher__v3__PathMatcher_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__type__matcher__v3__PathMatcher_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_path_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
