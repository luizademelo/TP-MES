
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/certs.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_Certificates__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__Certificate_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_Certificates__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__Certificates_msg_init = {
  &envoy_admin_v3_Certificates__submsgs[0],
  &envoy_admin_v3_Certificates__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.Certificates",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__admin__v3__Certificates_msg_init_ptr = &envoy__admin__v3__Certificates_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_Certificate__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__CertificateDetails_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__CertificateDetails_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_Certificate__fields[2] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__Certificate_msg_init = {
  &envoy_admin_v3_Certificate__submsgs[0],
  &envoy_admin_v3_Certificate__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.Certificate",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max128b},
    {0x001000003f010012, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__Certificate_msg_init_ptr = &envoy__admin__v3__Certificate_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_CertificateDetails__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__SubjectAlternateName_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_CertificateDetails__fields[7] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__CertificateDetails_msg_init = {
  &envoy_admin_v3_CertificateDetails__submsgs[0],
  &envoy_admin_v3_CertificateDetails__fields[0],
  UPB_SIZE(56, 88), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.CertificateDetails",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_prm_1bt_max64b},
    {0x003800003f000020, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__CertificateDetails_msg_init_ptr = &envoy__admin__v3__CertificateDetails_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_CertificateDetails_OcspDetails__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_CertificateDetails_OcspDetails__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__CertificateDetails__OcspDetails_msg_init = {
  &envoy_admin_v3_CertificateDetails_OcspDetails__submsgs[0],
  &envoy_admin_v3_CertificateDetails_OcspDetails__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.CertificateDetails.OcspDetails",
#endif
};

const upb_MiniTable* envoy__admin__v3__CertificateDetails__OcspDetails_msg_init_ptr = &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init;
static const upb_MiniTableField envoy_admin_v3_SubjectAlternateName__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__SubjectAlternateName_msg_init = {
  NULL,
  &envoy_admin_v3_SubjectAlternateName__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.SubjectAlternateName",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
    {0x0010000802000012, &upb_pos_1bt},
    {0x001000080300001a, &upb_pos_1bt},
  })
};

const upb_MiniTable* envoy__admin__v3__SubjectAlternateName_msg_init_ptr = &envoy__admin__v3__SubjectAlternateName_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__admin__v3__Certificates_msg_init,
  &envoy__admin__v3__Certificate_msg_init,
  &envoy__admin__v3__CertificateDetails_msg_init,
  &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init,
  &envoy__admin__v3__SubjectAlternateName_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_certs_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
