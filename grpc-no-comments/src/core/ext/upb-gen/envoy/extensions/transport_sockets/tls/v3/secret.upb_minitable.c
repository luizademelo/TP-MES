
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_GenericSecret__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_GenericSecret__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_GenericSecret__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_GenericSecret__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.GenericSecret",
#endif
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.SdsSecretConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_Secret__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_Secret__fields[5] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_Secret__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_Secret__fields[0],
  UPB_SIZE(24, 40), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.Secret",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_maxmaxb},
    {0x002000080301001a, &upb_pom_1bt_maxmaxb},
    {0x0020000804020022, &upb_pom_1bt_maxmaxb},
    {0x002000080503002a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init,
};

const upb_MiniTableFile envoy_extensions_transport_sockets_tls_v3_secret_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
