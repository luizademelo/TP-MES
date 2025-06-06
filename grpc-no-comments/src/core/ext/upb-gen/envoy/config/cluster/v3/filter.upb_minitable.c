
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/cluster/v3/filter.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_cluster_v3_Filter__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ExtensionConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_cluster_v3_Filter__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__cluster__v3__Filter_msg_init = {
  &envoy_config_cluster_v3_Filter__submsgs[0],
  &envoy_config_cluster_v3_Filter__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.cluster.v3.Filter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__cluster__v3__Filter_msg_init_ptr = &envoy__config__cluster__v3__Filter_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__config__cluster__v3__Filter_msg_init,
};

const upb_MiniTableFile envoy_config_cluster_v3_filter_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
