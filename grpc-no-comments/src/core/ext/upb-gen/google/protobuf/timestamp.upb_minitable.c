
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField google_protobuf_Timestamp__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__Timestamp_msg_init = {
  NULL,
  &google_protobuf_Timestamp__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.Timestamp",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__Timestamp_msg_init_ptr = &google__protobuf__Timestamp_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &google__protobuf__Timestamp_msg_init,
};

const upb_MiniTableFile google_protobuf_timestamp_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
