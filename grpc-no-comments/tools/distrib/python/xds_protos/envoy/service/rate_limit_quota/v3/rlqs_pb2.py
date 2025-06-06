
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import ratelimit_strategy_pb2 as envoy_dot_type_dot_v3_dot_ratelimit__strategy__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,envoy/service/rate_limit_quota/v3/rlqs.proto\x12!envoy.service.rate_limit_quota.v3\x1a&envoy/type/v3/ratelimit_strategy.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x83\x03\n\x1aRateLimitQuotaUsageReports\x12\x17\n\x06\x64omain\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12u\n\x13\x62ucket_quota_usages\x18\x02 \x03(\x0b\x32N.envoy.service.rate_limit_quota.v3.RateLimitQuotaUsageReports.BucketQuotaUsageB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\xd4\x01\n\x10\x42ucketQuotaUsage\x12H\n\tbucket_id\x18\x01 \x01(\x0b\x32+.envoy.service.rate_limit_quota.v3.BucketIdB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12;\n\x0ctime_elapsed\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\n\xfa\x42\x07\xaa\x01\x04\x08\x01*\x00\x12\x1c\n\x14num_requests_allowed\x18\x03 \x01(\x04\x12\x1b\n\x13num_requests_denied\x18\x04 \x01(\x04\"\x93\x05\n\x16RateLimitQuotaResponse\x12g\n\rbucket_action\x18\x01 \x03(\x0b\x32\x46.envoy.service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketActionB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\x8f\x04\n\x0c\x42ucketAction\x12H\n\tbucket_id\x18\x01 \x01(\x0b\x32+.envoy.service.rate_limit_quota.v3.BucketIdB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x7f\n\x17quota_assignment_action\x18\x02 \x01(\x0b\x32\\.envoy.service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.QuotaAssignmentActionH\x00\x12n\n\x0e\x61\x62\x61ndon_action\x18\x03 \x01(\x0b\x32T.envoy.service.rate_limit_quota.v3.RateLimitQuotaResponse.BucketAction.AbandonActionH\x00\x1a\x9c\x01\n\x15QuotaAssignmentAction\x12\x44\n\x17\x61ssignment_time_to_live\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02\x32\x00\x12=\n\x13rate_limit_strategy\x18\x03 \x01(\x0b\x32 .envoy.type.v3.RateLimitStrategy\x1a\x0f\n\rAbandonActionB\x14\n\rbucket_action\x12\x03\xf8\x42\x01\"\x98\x01\n\x08\x42ucketId\x12]\n\x06\x62ucket\x18\x01 \x03(\x0b\x32\x37.envoy.service.rate_limit_quota.v3.BucketId.BucketEntryB\x14\xfa\x42\x11\x9a\x01\x0e\x08\x01\"\x04r\x02\x10\x01*\x04r\x02\x10\x01\x1a-\n\x0b\x42ucketEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x32\xb1\x01\n\x15RateLimitQuotaService\x12\x97\x01\n\x15StreamRateLimitQuotas\x12=.envoy.service.rate_limit_quota.v3.RateLimitQuotaUsageReports\x1a\x39.envoy.service.rate_limit_quota.v3.RateLimitQuotaResponse\"\x00(\x01\x30\x01\x42\xab\x01\n/io.envoyproxy.envoy.service.rate_limit_quota.v3B\tRlqsProtoP\x01Z[github.com/envoyproxy/go-control-plane/envoy/service/rate_limit_quota/v3;rate_limit_quotav3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.rate_limit_quota.v3.rlqs_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n/io.envoyproxy.envoy.service.rate_limit_quota.v3B\tRlqsProtoP\001Z[github.com/envoyproxy/go-control-plane/envoy/service/rate_limit_quota/v3;rate_limit_quotav3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE.fields_by_name['bucket_id']._options = None
  _RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE.fields_by_name['bucket_id']._serialized_options = b'\372B\005\212\001\002\020\001'
  _RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE.fields_by_name['time_elapsed']._options = None
  _RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE.fields_by_name['time_elapsed']._serialized_options = b'\372B\007\252\001\004\010\001*\000'
  _RATELIMITQUOTAUSAGEREPORTS.fields_by_name['domain']._options = None
  _RATELIMITQUOTAUSAGEREPORTS.fields_by_name['domain']._serialized_options = b'\372B\004r\002\020\001'
  _RATELIMITQUOTAUSAGEREPORTS.fields_by_name['bucket_quota_usages']._options = None
  _RATELIMITQUOTAUSAGEREPORTS.fields_by_name['bucket_quota_usages']._serialized_options = b'\372B\005\222\001\002\010\001'
  _RATELIMITQUOTARESPONSE_BUCKETACTION_QUOTAASSIGNMENTACTION.fields_by_name['assignment_time_to_live']._options = None
  _RATELIMITQUOTARESPONSE_BUCKETACTION_QUOTAASSIGNMENTACTION.fields_by_name['assignment_time_to_live']._serialized_options = b'\372B\005\252\001\0022\000'
  _RATELIMITQUOTARESPONSE_BUCKETACTION.oneofs_by_name['bucket_action']._options = None
  _RATELIMITQUOTARESPONSE_BUCKETACTION.oneofs_by_name['bucket_action']._serialized_options = b'\370B\001'
  _RATELIMITQUOTARESPONSE_BUCKETACTION.fields_by_name['bucket_id']._options = None
  _RATELIMITQUOTARESPONSE_BUCKETACTION.fields_by_name['bucket_id']._serialized_options = b'\372B\005\212\001\002\020\001'
  _RATELIMITQUOTARESPONSE.fields_by_name['bucket_action']._options = None
  _RATELIMITQUOTARESPONSE.fields_by_name['bucket_action']._serialized_options = b'\372B\005\222\001\002\010\001'
  _BUCKETID_BUCKETENTRY._options = None
  _BUCKETID_BUCKETENTRY._serialized_options = b'8\001'
  _BUCKETID.fields_by_name['bucket']._options = None
  _BUCKETID.fields_by_name['bucket']._serialized_options = b'\372B\021\232\001\016\010\001\"\004r\002\020\001*\004r\002\020\001'
  _globals['_RATELIMITQUOTAUSAGEREPORTS']._serialized_start=245
  _globals['_RATELIMITQUOTAUSAGEREPORTS']._serialized_end=632
  _globals['_RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE']._serialized_start=420
  _globals['_RATELIMITQUOTAUSAGEREPORTS_BUCKETQUOTAUSAGE']._serialized_end=632
  _globals['_RATELIMITQUOTARESPONSE']._serialized_start=635
  _globals['_RATELIMITQUOTARESPONSE']._serialized_end=1294
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION']._serialized_start=767
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION']._serialized_end=1294
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION_QUOTAASSIGNMENTACTION']._serialized_start=1099
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION_QUOTAASSIGNMENTACTION']._serialized_end=1255
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION_ABANDONACTION']._serialized_start=1257
  _globals['_RATELIMITQUOTARESPONSE_BUCKETACTION_ABANDONACTION']._serialized_end=1272
  _globals['_BUCKETID']._serialized_start=1297
  _globals['_BUCKETID']._serialized_end=1449
  _globals['_BUCKETID_BUCKETENTRY']._serialized_start=1404
  _globals['_BUCKETID_BUCKETENTRY']._serialized_end=1449
  _globals['_RATELIMITQUOTASERVICE']._serialized_start=1452
  _globals['_RATELIMITQUOTASERVICE']._serialized_end=1629
