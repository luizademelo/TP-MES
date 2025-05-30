
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_UTIL_DEF_TO_PROTO_H_
#define UPB_UTIL_DEF_TO_PROTO_H_

#include "upb/reflection/def.h"

#ifdef __cplusplus
extern "C" {
#endif

google_protobuf_DescriptorProto* upb_MessageDef_ToProto(const upb_MessageDef* m,
                                                        upb_Arena* a);
google_protobuf_EnumDescriptorProto* upb_EnumDef_ToProto(const upb_EnumDef* e,
                                                         upb_Arena* a);
google_protobuf_EnumValueDescriptorProto* upb_EnumValueDef_ToProto(
    const upb_EnumValueDef* e, upb_Arena* a);
google_protobuf_FieldDescriptorProto* upb_FieldDef_ToProto(
    const upb_FieldDef* f, upb_Arena* a);
google_protobuf_OneofDescriptorProto* upb_OneofDef_ToProto(
    const upb_OneofDef* o, upb_Arena* a);
google_protobuf_FileDescriptorProto* upb_FileDef_ToProto(const upb_FileDef* f,
                                                         upb_Arena* a);
google_protobuf_MethodDescriptorProto* upb_MethodDef_ToProto(
    const upb_MethodDef* m, upb_Arena* a);
google_protobuf_ServiceDescriptorProto* upb_ServiceDef_ToProto(
    const upb_ServiceDef* s, upb_Arena* a);

#ifdef __cplusplus
}
#endif

#endif
