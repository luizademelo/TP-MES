
#ifndef ENVOY_ANNOTATIONS_DEPRECATION_PROTO_UPB_H__UPB_MINITABLE_H_
#define ENVOY_ANNOTATIONS_DEPRECATION_PROTO_UPB_H__UPB_MINITABLE_H_

#include "upb/generated_code_support.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern const upb_MiniTableExtension envoy_annotations_disallowed_by_default_ext;
extern const upb_MiniTableExtension envoy_annotations_deprecated_at_minor_version_ext;
extern const upb_MiniTableExtension envoy_annotations_disallowed_by_default_enum_ext;
extern const upb_MiniTableExtension envoy_annotations_deprecated_at_minor_version_enum_ext;

extern const upb_MiniTableFile envoy_annotations_deprecation_proto_upb_file_layout;

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
