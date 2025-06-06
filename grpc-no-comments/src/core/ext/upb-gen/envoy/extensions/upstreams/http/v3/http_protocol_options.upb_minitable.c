
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/upstreams/http/v3/http_protocol_options.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/protocol.upb_minitable.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_upstreams_http_v3_HttpProtocolOptions__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HttpProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_upstreams_http_v3_HttpProtocolOptions__fields[7] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 40), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init = {
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions__submsgs[0],
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions__fields[0],
  UPB_SIZE(40, 56), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.upstreams.http.v3.HttpProtocolOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0030000c0302001a, &upb_pom_1bt_max64b},
    {0x0030000c04030022, &upb_pom_1bt_max64b},
    {0x0030000c0504002a, &upb_pom_1bt_max64b},
    {0x002000003f050032, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init_ptr = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http1ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http2ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http3ProtocolOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init = {
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig__submsgs[0],
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.ExplicitHttpConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802010012, &upb_pom_1bt_maxmaxb},
    {0x001000080302001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init_ptr = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http1ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http2ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http3ProtocolOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init = {
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig__submsgs[0],
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.UseDownstreamHttpConfig",
#endif
};

const upb_MiniTable* envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init_ptr = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http1ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http2ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Http3ProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__AlternateProtocolsCacheOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init = {
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig__submsgs[0],
  &envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.AutoHttpConfig",
#endif
};

const upb_MiniTable* envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init_ptr = &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init,
  &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init,
  &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init,
  &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init,
};

const upb_MiniTableFile envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
