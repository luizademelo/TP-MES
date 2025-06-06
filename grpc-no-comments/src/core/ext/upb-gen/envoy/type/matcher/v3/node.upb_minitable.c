
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/node.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/matcher/v3/struct.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_NodeMatcher__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StructMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_NodeMatcher__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__NodeMatcher_msg_init = {
  &envoy_type_matcher_v3_NodeMatcher__submsgs[0],
  &envoy_type_matcher_v3_NodeMatcher__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.NodeMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f010012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__NodeMatcher_msg_init_ptr = &envoy__type__matcher__v3__NodeMatcher_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__type__matcher__v3__NodeMatcher_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_node_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
