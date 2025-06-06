
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/http/v3/path_transformation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_http_v3_PathTransformation__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__http__v3__PathTransformation__Operation_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_http_v3_PathTransformation__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__http__v3__PathTransformation_msg_init = {
  &envoy_type_http_v3_PathTransformation__submsgs[0],
  &envoy_type_http_v3_PathTransformation__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.http.v3.PathTransformation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__http__v3__PathTransformation_msg_init_ptr = &envoy__type__http__v3__PathTransformation_msg_init;
static const upb_MiniTableSubInternal envoy_type_http_v3_PathTransformation_Operation__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_http_v3_PathTransformation_Operation__fields[2] = {
  {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__http__v3__PathTransformation__Operation_msg_init = {
  &envoy_type_http_v3_PathTransformation_Operation__submsgs[0],
  &envoy_type_http_v3_PathTransformation_Operation__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.http.v3.PathTransformation.Operation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000802000012, &upb_pom_1bt_max64b},
    {0x001000080301001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__http__v3__PathTransformation__Operation_msg_init_ptr = &envoy__type__http__v3__PathTransformation__Operation_msg_init;
const upb_MiniTable envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.http.v3.PathTransformation.Operation.NormalizePathRFC3986",
#endif
};

const upb_MiniTable* envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init_ptr = &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init;
const upb_MiniTable envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.http.v3.PathTransformation.Operation.MergeSlashes",
#endif
};

const upb_MiniTable* envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init_ptr = &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &envoy__type__http__v3__PathTransformation_msg_init,
  &envoy__type__http__v3__PathTransformation__Operation_msg_init,
  &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init,
  &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init,
};

const upb_MiniTableFile envoy_type_http_v3_path_transformation_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
