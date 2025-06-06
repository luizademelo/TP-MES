
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/load_balancing_policies/pick_first/v3/pick_first.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_extensions_load_balancing_policies_pick_first_v3_PickFirst__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__pick_0first__v3__PickFirst_msg_init = {
  NULL,
  &envoy_extensions_load_balancing_policies_pick_first_v3_PickFirst__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.pick_first.v3.PickFirst",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__pick_0first__v3__PickFirst_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__pick_0first__v3__PickFirst_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__extensions__load_0balancing_0policies__pick_0first__v3__PickFirst_msg_init,
};

const upb_MiniTableFile envoy_extensions_load_balancing_policies_pick_first_v3_pick_first_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
