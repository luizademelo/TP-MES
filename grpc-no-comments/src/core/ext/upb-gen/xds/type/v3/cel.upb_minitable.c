
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/type/v3/cel.upb_minitable.h"
#include "google/api/expr/v1alpha1/checked.upb_minitable.h"
#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_type_v3_CelExpression__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__ParsedExpr_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__CheckedExpr_msg_init_ptr},
};

static const upb_MiniTableField xds_type_v3_CelExpression__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__v3__CelExpression_msg_init = {
  &xds_type_v3_CelExpression__submsgs[0],
  &xds_type_v3_CelExpression__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.v3.CelExpression",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802010012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__type__v3__CelExpression_msg_init_ptr = &xds__type__v3__CelExpression_msg_init;
static const upb_MiniTableSubInternal xds_type_v3_CelExtractString__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &xds__type__v3__CelExpression_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__StringValue_msg_init_ptr},
};

static const upb_MiniTableField xds_type_v3_CelExtractString__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__v3__CelExtractString_msg_init = {
  &xds_type_v3_CelExtractString__submsgs[0],
  &xds_type_v3_CelExtractString__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.v3.CelExtractString",
#endif
};

const upb_MiniTable* xds__type__v3__CelExtractString_msg_init_ptr = &xds__type__v3__CelExtractString_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &xds__type__v3__CelExpression_msg_init,
  &xds__type__v3__CelExtractString_msg_init,
};

const upb_MiniTableFile xds_type_v3_cel_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
