
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/bootstrap/v3/bootstrap.upb_minitable.h"
#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/cluster/v3/cluster.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/event_service_config.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/resolver.upb_minitable.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "envoy/config/listener/v3/listener.upb_minitable.h"
#include "envoy/config/metrics/v3/stats.upb_minitable.h"
#include "envoy/config/overload/v3/overload.upb_minitable.h"
#include "envoy/config/trace/v3/http_tracer.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/security.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap__submsgs[31] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__ClusterManager_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__metrics__v3__StatsSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Watchdog_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__trace__v3__Tracing_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Admin_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__metrics__v3__StatsConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ApiConfigSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__overload__v3__OverloadManager_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__LayeredRuntime_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt64Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Watchdogs_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__FatalAction_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DnsResolutionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap__fields[39] = {
  {1, UPB_SIZE(16, 88), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 96), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 104), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(28, 112), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(148, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 128), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(40, 136), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(44, 144), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(48, 152), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(52, 160), 72, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(56, 168), 73, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(60, 176), 74, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(64, 184), 75, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(156, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(68, 192), 76, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(80, 216), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(164, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {27, UPB_SIZE(92, 240), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {30, UPB_SIZE(100, 256), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {31, UPB_SIZE(104, 264), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {33, UPB_SIZE(172, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(112, 280), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {35, UPB_SIZE(116, 288), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {36, UPB_SIZE(120, 296), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {37, UPB_SIZE(124, 304), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {38, UPB_SIZE(128, 312), 85, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {39, UPB_SIZE(132, 320), 86, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {40, UPB_SIZE(136, 328), 87, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {41, UPB_SIZE(140, 336), 88, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap__fields[0],
  UPB_SIZE(184, 344), 39, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f00002a, &upb_pss_1bt},
    {0x007800003f040032, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000180, &upb_psb1_2bt},
    {0x004800003f00028a, &upb_pss_2bt},
    {0x002800003f000192, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000d00003f0001a0, &upb_psb1_2bt},
    {0x00c800003f0e01aa, &upb_prm_2bt_maxmaxb},
    {0x00d000003f0f01b2, &upb_prm_2bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f0001c2, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00e800003f0001d2, &upb_prs_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00f800003f1301e2, &upb_prm_2bt_max64b},
    {0x000e00101d0001e8, &upb_pob1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_StaticResources__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__Listener_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__cluster__v3__Cluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_StaticResources__fields[3] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_StaticResources__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_StaticResources__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.StaticResources",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_maxmaxb},
    {0x001000003f010012, &upb_prm_1bt_maxmaxb},
    {0x001800003f02001a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_DynamicResources__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ApiConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_DynamicResources__fields[5] = {
  {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_DynamicResources__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_DynamicResources__fields[0],
  UPB_SIZE(40, 72), 5, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.DynamicResources",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00002a, &upb_pss_1bt},
    {0x002000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.ApplicationLogConfig",
#endif
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.ApplicationLogConfig.LogFormat",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802000012, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init;
static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init = {
  NULL,
  &envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.DeferredStatOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.GrpcAsyncClientManagerConfig",
#endif
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init = {
  &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__submsgs[0],
  &envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Bootstrap.CertificateProviderInstancesEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init_ptr = &envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Admin__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AccessLog_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Admin__fields[6] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Admin_msg_init = {
  &envoy_config_bootstrap_v3_Admin__submsgs[0],
  &envoy_config_bootstrap_v3_Admin__fields[0],
  UPB_SIZE(40, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Admin",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f010022, &upb_prm_1bt_maxmaxb},
    {0x004000003f02002a, &upb_prm_1bt_maxmaxb},
    {0x000900003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Admin_msg_init_ptr = &envoy__config__bootstrap__v3__Admin_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_ClusterManager__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__BindConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ApiConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_ClusterManager__fields[5] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__ClusterManager_msg_init = {
  &envoy_config_bootstrap_v3_ClusterManager__submsgs[0],
  &envoy_config_bootstrap_v3_ClusterManager__fields[0],
  UPB_SIZE(32, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.ClusterManager",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000028, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__ClusterManager_msg_init_ptr = &envoy__config__bootstrap__v3__ClusterManager_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__EventServiceConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init = {
  &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__submsgs[0],
  &envoy_config_bootstrap_v3_ClusterManager_OutlierDetection__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.ClusterManager.OutlierDetection",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init_ptr = &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Watchdogs__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Watchdog_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Watchdog_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdogs__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Watchdogs_msg_init = {
  &envoy_config_bootstrap_v3_Watchdogs__submsgs[0],
  &envoy_config_bootstrap_v3_Watchdogs__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Watchdogs",
#endif
};

const upb_MiniTable* envoy__config__bootstrap__v3__Watchdogs_msg_init_ptr = &envoy__config__bootstrap__v3__Watchdogs_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Watchdog__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdog__fields[7] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Watchdog_msg_init = {
  &envoy_config_bootstrap_v3_Watchdog__submsgs[0],
  &envoy_config_bootstrap_v3_Watchdog__fields[0],
  UPB_SIZE(40, 72), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Watchdog",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f06003a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Watchdog_msg_init_ptr = &envoy__config__bootstrap__v3__Watchdog_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Watchdog_WatchdogAction__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Watchdog_WatchdogAction__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init = {
  &envoy_config_bootstrap_v3_Watchdog_WatchdogAction__submsgs[0],
  &envoy_config_bootstrap_v3_Watchdog_WatchdogAction__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Watchdog.WatchdogAction",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init_ptr = &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_FatalAction__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_FatalAction__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__FatalAction_msg_init = {
  &envoy_config_bootstrap_v3_FatalAction__submsgs[0],
  &envoy_config_bootstrap_v3_FatalAction__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.FatalAction",
#endif
};

const upb_MiniTable* envoy__config__bootstrap__v3__FatalAction_msg_init_ptr = &envoy__config__bootstrap__v3__FatalAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_Runtime__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_Runtime__fields[4] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__Runtime_msg_init = {
  &envoy_config_bootstrap_v3_Runtime__submsgs[0],
  &envoy_config_bootstrap_v3_Runtime__fields[0],
  UPB_SIZE(40, 72), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.Runtime",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__Runtime_msg_init_ptr = &envoy__config__bootstrap__v3__Runtime_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_RuntimeLayer__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer__fields[5] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__RuntimeLayer_msg_init = {
  &envoy_config_bootstrap_v3_RuntimeLayer__submsgs[0],
  &envoy_config_bootstrap_v3_RuntimeLayer__fields[0],
  UPB_SIZE(24, 40), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.RuntimeLayer",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_maxmaxb},
    {0x002000080301001a, &upb_pom_1bt_max64b},
    {0x0020000804020022, &upb_pom_1bt_max64b},
    {0x002000080503002a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__RuntimeLayer_msg_init_ptr = &envoy__config__bootstrap__v3__RuntimeLayer_msg_init;
static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init = {
  NULL,
  &envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.RuntimeLayer.DiskLayer",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psb1_1bt},
    {0x002000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init_ptr = &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init;
const upb_MiniTable envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.RuntimeLayer.AdminLayer",
#endif
};

const upb_MiniTable* envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init_ptr = &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init = {
  &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__submsgs[0],
  &envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.RuntimeLayer.RtdsLayer",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init_ptr = &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_LayeredRuntime__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__RuntimeLayer_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_LayeredRuntime__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__LayeredRuntime_msg_init = {
  &envoy_config_bootstrap_v3_LayeredRuntime__submsgs[0],
  &envoy_config_bootstrap_v3_LayeredRuntime__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.LayeredRuntime",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__LayeredRuntime_msg_init_ptr = &envoy__config__bootstrap__v3__LayeredRuntime_msg_init;
static const upb_MiniTableField envoy_config_bootstrap_v3_CustomInlineHeader__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__CustomInlineHeader_msg_init = {
  NULL,
  &envoy_config_bootstrap_v3_CustomInlineHeader__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.CustomInlineHeader",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__CustomInlineHeader_msg_init_ptr = &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init;
static const upb_MiniTableSubInternal envoy_config_bootstrap_v3_MemoryAllocatorManager__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_bootstrap_v3_MemoryAllocatorManager__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init = {
  &envoy_config_bootstrap_v3_MemoryAllocatorManager__submsgs[0],
  &envoy_config_bootstrap_v3_MemoryAllocatorManager__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.bootstrap.v3.MemoryAllocatorManager",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
  })
};

const upb_MiniTable* envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init_ptr = &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init;
static const upb_MiniTable *messages_layout[23] = {
  &envoy__config__bootstrap__v3__Bootstrap_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init,
  &envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init,
  &envoy__config__bootstrap__v3__Admin_msg_init,
  &envoy__config__bootstrap__v3__ClusterManager_msg_init,
  &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init,
  &envoy__config__bootstrap__v3__Watchdogs_msg_init,
  &envoy__config__bootstrap__v3__Watchdog_msg_init,
  &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init,
  &envoy__config__bootstrap__v3__FatalAction_msg_init,
  &envoy__config__bootstrap__v3__Runtime_msg_init,
  &envoy__config__bootstrap__v3__RuntimeLayer_msg_init,
  &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init,
  &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init,
  &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init,
  &envoy__config__bootstrap__v3__LayeredRuntime_msg_init,
  &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init,
  &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init,
};

const upb_MiniTableFile envoy_config_bootstrap_v3_bootstrap_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  23,
  0,
  0,
};

#include "upb/port/undef.inc"
