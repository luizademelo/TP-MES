
#ifndef ENVOY_CONFIG_COMMON_MATCHER_V3_MATCHER_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_COMMON_MATCHER_V3_MATCHER_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_common_matcher_v3_matcher_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_OnMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.OnMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherList_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherList");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherList.Predicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherList.Predicate.SinglePredicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherList.Predicate.PredicateList");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherList.FieldMatcher");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherTree_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherTree");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherTree.MatchMap");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_MapEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.Matcher.MatcherTree.MatchMap.MapEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_MatchPredicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.MatchPredicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_MatchPredicate_MatchSet_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.MatchPredicate.MatchSet");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_HttpHeadersMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.HttpHeadersMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_HttpGenericBodyMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.HttpGenericBodyMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_common_matcher_v3_matcher_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.common.matcher.v3.HttpGenericBodyMatch.GenericTextMatch");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
