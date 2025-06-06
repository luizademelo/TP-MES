
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)google/api/cloudquotas/v1/resources.proto\x12\x19google.api.cloudquotas.v1\x1a\x1fgoogle/api/field_behavior.proto\x1a\x19google/api/resource.proto\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1egoogle/protobuf/wrappers.proto\"\x9f\x07\n\tQuotaInfo\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x10\n\x08quota_id\x18\x02 \x01(\t\x12\x0e\n\x06metric\x18\x03 \x01(\t\x12\x0f\n\x07service\x18\x04 \x01(\t\x12\x12\n\nis_precise\x18\x05 \x01(\x08\x12\x18\n\x10refresh_interval\x18\x06 \x01(\t\x12J\n\x0e\x63ontainer_type\x18\x07 \x01(\x0e\x32\x32.google.api.cloudquotas.v1.QuotaInfo.ContainerType\x12\x12\n\ndimensions\x18\x08 \x03(\t\x12\x1b\n\x13metric_display_name\x18\t \x01(\t\x12\x1a\n\x12quota_display_name\x18\n \x01(\t\x12\x13\n\x0bmetric_unit\x18\x0b \x01(\t\x12W\n\x1aquota_increase_eligibility\x18\x0c \x01(\x0b\x32\x33.google.api.cloudquotas.v1.QuotaIncreaseEligibility\x12\x10\n\x08is_fixed\x18\r \x01(\x08\x12\x43\n\x10\x64imensions_infos\x18\x0e \x03(\x0b\x32).google.api.cloudquotas.v1.DimensionsInfo\x12\x15\n\ris_concurrent\x18\x0f \x01(\x08\x12!\n\x19service_request_quota_uri\x18\x11 \x01(\t\"Z\n\rContainerType\x12\x1e\n\x1a\x43ONTAINER_TYPE_UNSPECIFIED\x10\x00\x12\x0b\n\x07PROJECT\x10\x01\x12\n\n\x06\x46OLDER\x10\x02\x12\x10\n\x0cORGANIZATION\x10\x03:\xae\x02\xea\x41\xaa\x02\n$cloudquotas.googleapis.com/QuotaInfo\x12Rprojects/{project}/locations/{location}/services/{service}/quotaInfos/{quota_info}\x12Pfolders/{folder}/locations/{location}/services/{service}/quotaInfos/{quota_info}\x12\\organizations/{organization}/locations/{location}/services/{service}/quotaInfos/{quota_info}\"\xfc\x01\n\x18QuotaIncreaseEligibility\x12\x13\n\x0bis_eligible\x18\x01 \x01(\x08\x12\x65\n\x14ineligibility_reason\x18\x02 \x01(\x0e\x32G.google.api.cloudquotas.v1.QuotaIncreaseEligibility.IneligibilityReason\"d\n\x13IneligibilityReason\x12$\n INELIGIBILITY_REASON_UNSPECIFIED\x10\x00\x12\x1c\n\x18NO_VALID_BILLING_ACCOUNT\x10\x01\x12\t\n\x05OTHER\x10\x02\"\x85\x06\n\x0fQuotaPreference\x12\x0c\n\x04name\x18\x01 \x01(\t\x12S\n\ndimensions\x18\x02 \x03(\x0b\x32:.google.api.cloudquotas.v1.QuotaPreference.DimensionsEntryB\x03\xe0\x41\x05\x12\x41\n\x0cquota_config\x18\x03 \x01(\x0b\x32&.google.api.cloudquotas.v1.QuotaConfigB\x03\xe0\x41\x02\x12\x11\n\x04\x65tag\x18\x04 \x01(\tB\x03\xe0\x41\x01\x12\x34\n\x0b\x63reate_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x14\n\x07service\x18\x07 \x01(\tB\x03\xe0\x41\x02\x12\x15\n\x08quota_id\x18\x08 \x01(\tB\x03\xe0\x41\x02\x12\x18\n\x0breconciling\x18\n \x01(\x08\x42\x03\xe0\x41\x03\x12\x15\n\rjustification\x18\x0b \x01(\t\x12\x1a\n\rcontact_email\x18\x0c \x01(\tB\x03\xe0\x41\x04\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01:\x9f\x02\xea\x41\x9b\x02\n*cloudquotas.googleapis.com/QuotaPreference\x12Kprojects/{project}/locations/{location}/quotaPreferences/{quota_preference}\x12Ifolders/{folder}/locations/{location}/quotaPreferences/{quota_preference}\x12Uorganizations/{organization}/locations/{location}/quotaPreferences/{quota_preference}\"\xb1\x03\n\x0bQuotaConfig\x12\x1c\n\x0fpreferred_value\x18\x01 \x01(\x03\x42\x03\xe0\x41\x02\x12\x19\n\x0cstate_detail\x18\x02 \x01(\tB\x03\xe0\x41\x03\x12\x37\n\rgranted_value\x18\x03 \x01(\x0b\x32\x1b.google.protobuf.Int64ValueB\x03\xe0\x41\x03\x12\x15\n\x08trace_id\x18\x04 \x01(\tB\x03\xe0\x41\x03\x12Q\n\x0b\x61nnotations\x18\x05 \x03(\x0b\x32\x37.google.api.cloudquotas.v1.QuotaConfig.AnnotationsEntryB\x03\xe0\x41\x01\x12J\n\x0erequest_origin\x18\x06 \x01(\x0e\x32-.google.api.cloudquotas.v1.QuotaConfig.OriginB\x03\xe0\x41\x03\x1a\x32\n\x10\x41nnotationsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"F\n\x06Origin\x12\x16\n\x12ORIGIN_UNSPECIFIED\x10\x00\x12\x11\n\rCLOUD_CONSOLE\x10\x01\x12\x11\n\rAUTO_ADJUSTER\x10\x02\"\xea\x01\n\x0e\x44imensionsInfo\x12M\n\ndimensions\x18\x01 \x03(\x0b\x32\x39.google.api.cloudquotas.v1.DimensionsInfo.DimensionsEntry\x12\x38\n\x07\x64\x65tails\x18\x02 \x01(\x0b\x32\'.google.api.cloudquotas.v1.QuotaDetails\x12\x1c\n\x14\x61pplicable_locations\x18\x03 \x03(\t\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"[\n\x0cQuotaDetails\x12\r\n\x05value\x18\x01 \x01(\x03\x12<\n\x0crollout_info\x18\x03 \x01(\x0b\x32&.google.api.cloudquotas.v1.RolloutInfo\"&\n\x0bRolloutInfo\x12\x17\n\x0fongoing_rollout\x18\x01 \x01(\x08*~\n\x10QuotaSafetyCheck\x12\"\n\x1eQUOTA_SAFETY_CHECK_UNSPECIFIED\x10\x00\x12\x1e\n\x1aQUOTA_DECREASE_BELOW_USAGE\x10\x01\x12&\n\"QUOTA_DECREASE_PERCENTAGE_TOO_HIGH\x10\x02\x42\xd1\x01\n\x1d\x63om.google.api.cloudquotas.v1B\x0eResourcesProtoP\x01ZAcloud.google.com/go/cloudquotas/apiv1/cloudquotaspb;cloudquotaspb\xaa\x02\x1bGoogle.Cloud.CloudQuotas.V1\xca\x02\x1bGoogle\\Cloud\\CloudQuotas\\V1\xea\x02\x1eGoogle::Cloud::CloudQuotas::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.cloudquotas.v1.resources_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\035com.google.api.cloudquotas.v1B\016ResourcesProtoP\001ZAcloud.google.com/go/cloudquotas/apiv1/cloudquotaspb;cloudquotaspb\252\002\033Google.Cloud.CloudQuotas.V1\312\002\033Google\\Cloud\\CloudQuotas\\V1\352\002\036Google::Cloud::CloudQuotas::V1'
  _QUOTAINFO._options = None
  _QUOTAINFO._serialized_options = b'\352A\252\002\n$cloudquotas.googleapis.com/QuotaInfo\022Rprojects/{project}/locations/{location}/services/{service}/quotaInfos/{quota_info}\022Pfolders/{folder}/locations/{location}/services/{service}/quotaInfos/{quota_info}\022\\organizations/{organization}/locations/{location}/services/{service}/quotaInfos/{quota_info}'
  _QUOTAPREFERENCE_DIMENSIONSENTRY._options = None
  _QUOTAPREFERENCE_DIMENSIONSENTRY._serialized_options = b'8\001'
  _QUOTAPREFERENCE.fields_by_name['dimensions']._options = None
  _QUOTAPREFERENCE.fields_by_name['dimensions']._serialized_options = b'\340A\005'
  _QUOTAPREFERENCE.fields_by_name['quota_config']._options = None
  _QUOTAPREFERENCE.fields_by_name['quota_config']._serialized_options = b'\340A\002'
  _QUOTAPREFERENCE.fields_by_name['etag']._options = None
  _QUOTAPREFERENCE.fields_by_name['etag']._serialized_options = b'\340A\001'
  _QUOTAPREFERENCE.fields_by_name['create_time']._options = None
  _QUOTAPREFERENCE.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _QUOTAPREFERENCE.fields_by_name['update_time']._options = None
  _QUOTAPREFERENCE.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _QUOTAPREFERENCE.fields_by_name['service']._options = None
  _QUOTAPREFERENCE.fields_by_name['service']._serialized_options = b'\340A\002'
  _QUOTAPREFERENCE.fields_by_name['quota_id']._options = None
  _QUOTAPREFERENCE.fields_by_name['quota_id']._serialized_options = b'\340A\002'
  _QUOTAPREFERENCE.fields_by_name['reconciling']._options = None
  _QUOTAPREFERENCE.fields_by_name['reconciling']._serialized_options = b'\340A\003'
  _QUOTAPREFERENCE.fields_by_name['contact_email']._options = None
  _QUOTAPREFERENCE.fields_by_name['contact_email']._serialized_options = b'\340A\004'
  _QUOTAPREFERENCE._options = None
  _QUOTAPREFERENCE._serialized_options = b'\352A\233\002\n*cloudquotas.googleapis.com/QuotaPreference\022Kprojects/{project}/locations/{location}/quotaPreferences/{quota_preference}\022Ifolders/{folder}/locations/{location}/quotaPreferences/{quota_preference}\022Uorganizations/{organization}/locations/{location}/quotaPreferences/{quota_preference}'
  _QUOTACONFIG_ANNOTATIONSENTRY._options = None
  _QUOTACONFIG_ANNOTATIONSENTRY._serialized_options = b'8\001'
  _QUOTACONFIG.fields_by_name['preferred_value']._options = None
  _QUOTACONFIG.fields_by_name['preferred_value']._serialized_options = b'\340A\002'
  _QUOTACONFIG.fields_by_name['state_detail']._options = None
  _QUOTACONFIG.fields_by_name['state_detail']._serialized_options = b'\340A\003'
  _QUOTACONFIG.fields_by_name['granted_value']._options = None
  _QUOTACONFIG.fields_by_name['granted_value']._serialized_options = b'\340A\003'
  _QUOTACONFIG.fields_by_name['trace_id']._options = None
  _QUOTACONFIG.fields_by_name['trace_id']._serialized_options = b'\340A\003'
  _QUOTACONFIG.fields_by_name['annotations']._options = None
  _QUOTACONFIG.fields_by_name['annotations']._serialized_options = b'\340A\001'
  _QUOTACONFIG.fields_by_name['request_origin']._options = None
  _QUOTACONFIG.fields_by_name['request_origin']._serialized_options = b'\340A\003'
  _DIMENSIONSINFO_DIMENSIONSENTRY._options = None
  _DIMENSIONSINFO_DIMENSIONSENTRY._serialized_options = b'8\001'
  _globals['_QUOTASAFETYCHECK']._serialized_start=2964
  _globals['_QUOTASAFETYCHECK']._serialized_end=3090
  _globals['_QUOTAINFO']._serialized_start=198
  _globals['_QUOTAINFO']._serialized_end=1125
  _globals['_QUOTAINFO_CONTAINERTYPE']._serialized_start=730
  _globals['_QUOTAINFO_CONTAINERTYPE']._serialized_end=820
  _globals['_QUOTAINCREASEELIGIBILITY']._serialized_start=1128
  _globals['_QUOTAINCREASEELIGIBILITY']._serialized_end=1380
  _globals['_QUOTAINCREASEELIGIBILITY_INELIGIBILITYREASON']._serialized_start=1280
  _globals['_QUOTAINCREASEELIGIBILITY_INELIGIBILITYREASON']._serialized_end=1380
  _globals['_QUOTAPREFERENCE']._serialized_start=1383
  _globals['_QUOTAPREFERENCE']._serialized_end=2156
  _globals['_QUOTAPREFERENCE_DIMENSIONSENTRY']._serialized_start=1817
  _globals['_QUOTAPREFERENCE_DIMENSIONSENTRY']._serialized_end=1866
  _globals['_QUOTACONFIG']._serialized_start=2159
  _globals['_QUOTACONFIG']._serialized_end=2592
  _globals['_QUOTACONFIG_ANNOTATIONSENTRY']._serialized_start=2470
  _globals['_QUOTACONFIG_ANNOTATIONSENTRY']._serialized_end=2520
  _globals['_QUOTACONFIG_ORIGIN']._serialized_start=2522
  _globals['_QUOTACONFIG_ORIGIN']._serialized_end=2592
  _globals['_DIMENSIONSINFO']._serialized_start=2595
  _globals['_DIMENSIONSINFO']._serialized_end=2829
  _globals['_DIMENSIONSINFO_DIMENSIONSENTRY']._serialized_start=1817
  _globals['_DIMENSIONSINFO_DIMENSIONSENTRY']._serialized_end=1866
  _globals['_QUOTADETAILS']._serialized_start=2831
  _globals['_QUOTADETAILS']._serialized_end=2922
  _globals['_ROLLOUTINFO']._serialized_start=2924
  _globals['_ROLLOUTINFO']._serialized_end=2962
