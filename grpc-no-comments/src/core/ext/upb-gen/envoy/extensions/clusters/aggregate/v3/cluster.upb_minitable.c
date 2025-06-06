
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_extensions_clusters_aggregate_v3_ClusterConfig__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init = {
  NULL,
  &envoy_extensions_clusters_aggregate_v3_ClusterConfig__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.clusters.aggregate.v3.ClusterConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prs_1bt},
  })
};

const upb_MiniTable* envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init_ptr = &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init,
};

const upb_MiniTableFile envoy_extensions_clusters_aggregate_v3_cluster_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
