
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext__fields[7] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext__fields[0],
  UPB_SIZE(32, 56), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.UpstreamTlsContext",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x000900003f000018, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000a00003f000030, &upb_psb1_1bt},
    {0x000b00003f000038, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext__fields[11] = {
  {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 40), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 48), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 56), 68, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext__fields[0],
  UPB_SIZE(48, 72), 11, kUpb_ExtMode_NonExtendable, 11, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.DownstreamTlsContext",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0040001004030022, &upb_pom_1bt_maxmaxb},
    {0x004000100504002a, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0040001007000038, &upb_pob1_1bt},
    {0x000c00003f000040, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000050, &upb_psb1_1bt},
    {0x000a00003f000058, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_TlsKeyLog__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_TlsKeyLog__fields[3] = {
  {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_TlsKeyLog__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_TlsKeyLog__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.TlsKeyLog",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prm_1bt_maxmaxb},
    {0x002000003f01001a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_CommonTlsContext__submsgs[14] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CommonTlsContext__fields[15] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 48), 65, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(32, 56), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(36, 64), 67, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(40, 72), 68, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(44, 80), 69, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(48, 88), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext__fields[0],
  UPB_SIZE(64, 104), 15, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f010012, &upb_prm_1bt_maxmaxb},
    {0x0060000c0302001a, &upb_pom_1bt_maxmaxb},
    {0x002000003f000022, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f030032, &upb_prm_1bt_maxmaxb},
    {0x0060000c0704003a, &upb_pom_1bt_maxmaxb},
    {0x0060000c08050042, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0060000c0a070052, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0060000c0c090062, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProvider",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init;
static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init = {
  NULL,
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderInstance",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CombinedCertificateValidationContext",
#endif
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init;
static const upb_MiniTable *messages_layout[7] = {
  &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init,
};

const upb_MiniTableFile envoy_extensions_transport_sockets_tls_v3_tls_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  7,
  0,
  0,
};

#include "upb/port/undef.inc"
