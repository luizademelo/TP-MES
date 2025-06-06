
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/http/stateful_session/cookie/v3/cookie.upb_minitable.h"
#include "envoy/type/http/v3/cookie.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_http_stateful_session_cookie_v3_CookieBasedSessionState__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__http__v3__Cookie_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_http_stateful_session_cookie_v3_CookieBasedSessionState__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__http__stateful_0session__cookie__v3__CookieBasedSessionState_msg_init = {
  &envoy_extensions_http_stateful_session_cookie_v3_CookieBasedSessionState__submsgs[0],
  &envoy_extensions_http_stateful_session_cookie_v3_CookieBasedSessionState__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.http.stateful_session.cookie.v3.CookieBasedSessionState",
#endif
};

const upb_MiniTable* envoy__extensions__http__stateful_0session__cookie__v3__CookieBasedSessionState_msg_init_ptr = &envoy__extensions__http__stateful_0session__cookie__v3__CookieBasedSessionState_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__extensions__http__stateful_0session__cookie__v3__CookieBasedSessionState_msg_init,
};

const upb_MiniTableFile envoy_extensions_http_stateful_session_cookie_v3_cookie_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
