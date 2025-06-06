
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/data/orca/v3/orca_load_report.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_data_orca_v3_OrcaLoadReport__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init_ptr},
};

static const upb_MiniTableField xds_data_orca_v3_OrcaLoadReport__fields[9] = {
  {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 16), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 48, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {7, 56, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(64, 72), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__data__orca__v3__OrcaLoadReport_msg_init = {
  &xds_data_orca_v3_OrcaLoadReport__submsgs[0],
  &xds_data_orca_v3_OrcaLoadReport__fields[0],
  UPB_SIZE(72, 80), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.data.orca.v3.OrcaLoadReport",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000009, &upb_psf8_1bt},
    {0x001000003f000011, &upb_psf8_1bt},
    {0x001800003f000018, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f000031, &upb_psf8_1bt},
    {0x003800003f000039, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004800003f000049, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__data__orca__v3__OrcaLoadReport_msg_init_ptr = &xds__data__orca__v3__OrcaLoadReport_msg_init;
static const upb_MiniTableField xds_data_orca_v3_OrcaLoadReport_RequestCostEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init = {
  NULL,
  &xds_data_orca_v3_OrcaLoadReport_RequestCostEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.data.orca.v3.OrcaLoadReport.RequestCostEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000011, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init_ptr = &xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init;
static const upb_MiniTableField xds_data_orca_v3_OrcaLoadReport_UtilizationEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init = {
  NULL,
  &xds_data_orca_v3_OrcaLoadReport_UtilizationEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.data.orca.v3.OrcaLoadReport.UtilizationEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000011, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init_ptr = &xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init;
static const upb_MiniTableField xds_data_orca_v3_OrcaLoadReport_NamedMetricsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init = {
  NULL,
  &xds_data_orca_v3_OrcaLoadReport_NamedMetricsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.data.orca.v3.OrcaLoadReport.NamedMetricsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000011, &upb_psf8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init_ptr = &xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &xds__data__orca__v3__OrcaLoadReport_msg_init,
  &xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init,
  &xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init,
  &xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init,
};

const upb_MiniTableFile xds_data_orca_v3_orca_load_report_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
