
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/core/v3/collection_entry.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/resource_locator.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_core_v3_CollectionEntry__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &xds__core__v3__ResourceLocator_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__core__v3__CollectionEntry__InlineEntry_msg_init_ptr},
};

static const upb_MiniTableField xds_core_v3_CollectionEntry__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__core__v3__CollectionEntry_msg_init = {
  &xds_core_v3_CollectionEntry__submsgs[0],
  &xds_core_v3_CollectionEntry__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.core.v3.CollectionEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__core__v3__CollectionEntry_msg_init_ptr = &xds__core__v3__CollectionEntry_msg_init;
static const upb_MiniTableSubInternal xds_core_v3_CollectionEntry_InlineEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField xds_core_v3_CollectionEntry_InlineEntry__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__core__v3__CollectionEntry__InlineEntry_msg_init = {
  &xds_core_v3_CollectionEntry_InlineEntry__submsgs[0],
  &xds_core_v3_CollectionEntry_InlineEntry__fields[0],
  UPB_SIZE(32, 56), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.core.v3.CollectionEntry.InlineEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__core__v3__CollectionEntry__InlineEntry_msg_init_ptr = &xds__core__v3__CollectionEntry__InlineEntry_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &xds__core__v3__CollectionEntry_msg_init,
  &xds__core__v3__CollectionEntry__InlineEntry_msg_init,
};

const upb_MiniTableFile xds_core_v3_collection_entry_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
