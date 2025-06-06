
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_TlsParameters__fields[5] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init = {
  NULL,
  &envoy_extensions_transport_sockets_tls_v3_TlsParameters__fields[0],
  UPB_SIZE(32, 40), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.TlsParameters",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x001000003f00001a, &upb_prs_1bt},
    {0x001800003f000022, &upb_prs_1bt},
    {0x002000003f00002a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider__fields[0],
  UPB_SIZE(32, 40), 3, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.PrivateKeyProvider",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0020000c0300001a, &upb_pom_1bt_maxmaxb},
    {0x000800003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_TlsCertificate__submsgs[8] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__WatchedDirectory_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_TlsCertificate__fields[8] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(40, 72), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_TlsCertificate__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_TlsCertificate__fields[0],
  UPB_SIZE(48, 80), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.TlsCertificate",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f04002a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.TlsSessionTicketKeys",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init;
static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init = {
  NULL,
  &envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CertificateProviderPluginInstance",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher__fields[3] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher__fields[0],
  UPB_SIZE(32, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.SubjectAltNameMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext__submsgs[10] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__WatchedDirectory_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext__fields[15] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(28, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(36, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(40, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(44, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(48, 80), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(56, 96), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(60, 104), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext__fields[0],
  UPB_SIZE(64, 112), 15, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CertificateValidationContext",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000012, &upb_prs_1bt},
    {0x002000003f00001a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000040, &upb_psb1_1bt},
    {0x003800003f03004a, &upb_prm_1bt_maxmaxb},
    {0x000c00003f000050, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000a00003f000070, &upb_psb1_1bt},
    {0x005800003f07007a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init;
const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CertificateValidationContext.SystemRootCerts",
#endif
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init;
static const upb_MiniTable *messages_layout[8] = {
  &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init,
};

const upb_MiniTableFile envoy_extensions_transport_sockets_tls_v3_common_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  8,
  0,
  0,
};

#include "upb/port/undef.inc"
