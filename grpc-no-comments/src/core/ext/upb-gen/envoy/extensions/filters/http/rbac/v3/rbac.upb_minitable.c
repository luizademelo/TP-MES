
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/filters/http/rbac/v3/rbac.upb_minitable.h"
#include "envoy/config/rbac/v3/rbac.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_filters_http_rbac_v3_RBAC__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__RBAC_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__RBAC_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__Matcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__Matcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_rbac_v3_RBAC__fields[7] = {
  {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__rbac__v3__RBAC_msg_init = {
  &envoy_extensions_filters_http_rbac_v3_RBAC__submsgs[0],
  &envoy_extensions_filters_http_rbac_v3_RBAC__fields[0],
  UPB_SIZE(48, 80), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.rbac.v3.RBAC",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000032, &upb_pss_1bt},
    {0x000900003f000038, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__filters__http__rbac__v3__RBAC_msg_init_ptr = &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_filters_http_rbac_v3_RBACPerRoute__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_filters_http_rbac_v3_RBACPerRoute__fields[1] = {
  {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init = {
  &envoy_extensions_filters_http_rbac_v3_RBACPerRoute__submsgs[0],
  &envoy_extensions_filters_http_rbac_v3_RBACPerRoute__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.filters.http.rbac.v3.RBACPerRoute",
#endif
};

const upb_MiniTable* envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init_ptr = &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init,
  &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init,
};

const upb_MiniTableFile envoy_extensions_filters_http_rbac_v3_rbac_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
