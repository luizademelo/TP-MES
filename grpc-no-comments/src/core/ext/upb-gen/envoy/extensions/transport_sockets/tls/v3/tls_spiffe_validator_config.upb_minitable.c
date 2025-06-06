
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls_spiffe_validator_config.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.SPIFFECertValidatorConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init = {
  &envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain__submsgs[0],
  &envoy_extensions_transport_sockets_tls_v3_SPIFFECertValidatorConfig_TrustDomain__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.transport_sockets.tls.v3.SPIFFECertValidatorConfig.TrustDomain",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init_ptr = &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig_msg_init,
  &envoy__extensions__transport_0sockets__tls__v3__SPIFFECertValidatorConfig__TrustDomain_msg_init,
};

const upb_MiniTableFile envoy_extensions_transport_sockets_tls_v3_tls_spiffe_validator_config_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
