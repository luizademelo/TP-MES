
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/protobuf/empty.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
const upb_MiniTable google__protobuf__Empty_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.Empty",
#endif
};

const upb_MiniTable* google__protobuf__Empty_msg_init_ptr = &google__protobuf__Empty_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &google__protobuf__Empty_msg_init,
};

const upb_MiniTableFile google_protobuf_empty_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
