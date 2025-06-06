
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/load_balancing_policies/wrr_locality/v3/wrr_locality.upb_minitable.h"
#include "envoy/config/cluster/v3/cluster.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__cluster__v3__LoadBalancingPolicy_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init = {
  &envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality__submsgs[0],
  &envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.wrr_locality.v3.WrrLocality",
#endif
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init,
};

const upb_MiniTableFile envoy_extensions_load_balancing_policies_wrr_locality_v3_wrr_locality_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
