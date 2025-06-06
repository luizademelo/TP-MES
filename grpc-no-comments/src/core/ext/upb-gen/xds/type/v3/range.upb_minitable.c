
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/type/v3/range.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField xds_type_v3_Int64Range__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__v3__Int64Range_msg_init = {
  NULL,
  &xds_type_v3_Int64Range__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.v3.Int64Range",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv8_1bt},
    {0x001000003f000010, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__type__v3__Int64Range_msg_init_ptr = &xds__type__v3__Int64Range_msg_init;
static const upb_MiniTableField xds_type_v3_Int32Range__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__v3__Int32Range_msg_init = {
  NULL,
  &xds_type_v3_Int32Range__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.v3.Int32Range",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__type__v3__Int32Range_msg_init_ptr = &xds__type__v3__Int32Range_msg_init;
static const upb_MiniTableField xds_type_v3_DoubleRange__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__v3__DoubleRange_msg_init = {
  NULL,
  &xds_type_v3_DoubleRange__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.v3.DoubleRange",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000009, &upb_psf8_1bt},
    {0x001000003f000011, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__type__v3__DoubleRange_msg_init_ptr = &xds__type__v3__DoubleRange_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &xds__type__v3__Int64Range_msg_init,
  &xds__type__v3__Int32Range_msg_init,
  &xds__type__v3__DoubleRange_msg_init,
};

const upb_MiniTableFile xds_type_v3_range_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
