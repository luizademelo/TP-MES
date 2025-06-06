
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/api/annotations.upb_minitable.h"
#include "google/api/http.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension google_api_http_ext = {
  {72295728, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__MethodOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &google__api__HttpRule_msg_init},

};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &google_api_http_ext,
};

const upb_MiniTableFile google_api_annotations_proto_upb_file_layout = {
  NULL,
  NULL,
  extensions_layout,
  0,
  0,
  1,
};

#include "upb/port/undef.inc"
