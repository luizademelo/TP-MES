
#ifndef ENVOY_DATA_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_DATA_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_data_accesslog_v3_accesslog_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_TCPAccessLogEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.TCPAccessLogEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPAccessLogEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPAccessLogEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_ConnectionProperties_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.ConnectionProperties");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_AccessLogCommon_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.AccessLogCommon");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_AccessLogCommon_FilterStateObjectsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.AccessLogCommon.FilterStateObjectsEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_AccessLogCommon_CustomTagsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.AccessLogCommon.CustomTagsEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_ResponseFlags_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.ResponseFlags");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_ResponseFlags_Unauthorized_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.ResponseFlags.Unauthorized");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_TLSProperties_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.TLSProperties");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_TLSProperties_CertificateProperties_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.TLSProperties.CertificateProperties");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.TLSProperties.CertificateProperties.SubjectAltName");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPRequestProperties_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPRequestProperties");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPRequestProperties_RequestHeadersEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPRequestProperties.RequestHeadersEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPResponseProperties_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPResponseProperties");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPResponseProperties_ResponseHeadersEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPResponseProperties.ResponseHeadersEntry");
}

UPB_INLINE const upb_MessageDef *envoy_data_accesslog_v3_HTTPResponseProperties_ResponseTrailersEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_data_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.data.accesslog.v3.HTTPResponseProperties.ResponseTrailersEntry");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
