
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import auth_pb2 as google_dot_api_dot_auth__pb2
from google.api import documentation_pb2 as google_dot_api_dot_documentation__pb2
from google.api import endpoint_pb2 as google_dot_api_dot_endpoint__pb2
from google.api import monitored_resource_pb2 as google_dot_api_dot_monitored__resource__pb2
from google.api import monitoring_pb2 as google_dot_api_dot_monitoring__pb2
from google.api import quota_pb2 as google_dot_api_dot_quota__pb2
from google.api import usage_pb2 as google_dot_api_dot_usage__pb2
from google.protobuf import api_pb2 as google_dot_protobuf_dot_api__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/google/api/serviceusage/v1beta1/resources.proto\x12\x1fgoogle.api.serviceusage.v1beta1\x1a\x15google/api/auth.proto\x1a\x1egoogle/api/documentation.proto\x1a\x19google/api/endpoint.proto\x1a#google/api/monitored_resource.proto\x1a\x1bgoogle/api/monitoring.proto\x1a\x16google/api/quota.proto\x1a\x16google/api/usage.proto\x1a\x19google/protobuf/api.proto\"\x9e\x01\n\x07Service\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0e\n\x06parent\x18\x05 \x01(\t\x12>\n\x06\x63onfig\x18\x02 \x01(\x0b\x32..google.api.serviceusage.v1beta1.ServiceConfig\x12\x35\n\x05state\x18\x04 \x01(\x0e\x32&.google.api.serviceusage.v1beta1.State\"\x95\x03\n\rServiceConfig\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05title\x18\x02 \x01(\t\x12\"\n\x04\x61pis\x18\x03 \x03(\x0b\x32\x14.google.protobuf.Api\x12\x30\n\rdocumentation\x18\x06 \x01(\x0b\x32\x19.google.api.Documentation\x12 \n\x05quota\x18\n \x01(\x0b\x32\x11.google.api.Quota\x12\x32\n\x0e\x61uthentication\x18\x0b \x01(\x0b\x32\x1a.google.api.Authentication\x12 \n\x05usage\x18\x0f \x01(\x0b\x32\x11.google.api.Usage\x12\'\n\tendpoints\x18\x12 \x03(\x0b\x32\x14.google.api.Endpoint\x12\x44\n\x13monitored_resources\x18\x19 \x03(\x0b\x32\'.google.api.MonitoredResourceDescriptor\x12*\n\nmonitoring\x18\x1c \x01(\x0b\x32\x16.google.api.Monitoring\"+\n\x11OperationMetadata\x12\x16\n\x0eresource_names\x18\x02 \x03(\t\"\x8a\x02\n\x13\x43onsumerQuotaMetric\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0e\n\x06metric\x18\x04 \x01(\t\x12\x14\n\x0c\x64isplay_name\x18\x02 \x01(\t\x12R\n\x15\x63onsumer_quota_limits\x18\x03 \x03(\x0b\x32\x33.google.api.serviceusage.v1beta1.ConsumerQuotaLimit\x12]\n descendant_consumer_quota_limits\x18\x06 \x03(\x0b\x32\x33.google.api.serviceusage.v1beta1.ConsumerQuotaLimit\x12\x0c\n\x04unit\x18\x05 \x01(\t\"\xd6\x01\n\x12\x43onsumerQuotaLimit\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0e\n\x06metric\x18\x08 \x01(\t\x12\x0c\n\x04unit\x18\x02 \x01(\t\x12\x12\n\nis_precise\x18\x03 \x01(\x08\x12\x1e\n\x16\x61llows_admin_overrides\x18\x07 \x01(\x08\x12\x43\n\rquota_buckets\x18\t \x03(\x0b\x32,.google.api.serviceusage.v1beta1.QuotaBucket\x12\x1b\n\x13supported_locations\x18\x0b \x03(\t\"\xf5\x03\n\x0bQuotaBucket\x12\x17\n\x0f\x65\x66\x66\x65\x63tive_limit\x18\x01 \x01(\x03\x12\x15\n\rdefault_limit\x18\x02 \x01(\x03\x12I\n\x11producer_override\x18\x03 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12I\n\x11\x63onsumer_override\x18\x04 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\x46\n\x0e\x61\x64min_override\x18\x05 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12S\n\x15producer_quota_policy\x18\x07 \x01(\x0b\x32\x34.google.api.serviceusage.v1beta1.ProducerQuotaPolicy\x12P\n\ndimensions\x18\x06 \x03(\x0b\x32<.google.api.serviceusage.v1beta1.QuotaBucket.DimensionsEntry\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\xfb\x01\n\rQuotaOverride\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x16\n\x0eoverride_value\x18\x02 \x01(\x03\x12R\n\ndimensions\x18\x03 \x03(\x0b\x32>.google.api.serviceusage.v1beta1.QuotaOverride.DimensionsEntry\x12\x0e\n\x06metric\x18\x04 \x01(\t\x12\x0c\n\x04unit\x18\x05 \x01(\t\x12\x1f\n\x17\x61\x64min_override_ancestor\x18\x06 \x01(\t\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"Y\n\x14OverrideInlineSource\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\"\xf7\x01\n\x13ProducerQuotaPolicy\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\x0cpolicy_value\x18\x02 \x01(\x03\x12X\n\ndimensions\x18\x03 \x03(\x0b\x32\x44.google.api.serviceusage.v1beta1.ProducerQuotaPolicy.DimensionsEntry\x12\x0e\n\x06metric\x18\x04 \x01(\t\x12\x0c\n\x04unit\x18\x05 \x01(\t\x12\x11\n\tcontainer\x18\x06 \x01(\t\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\xf1\x01\n\x10\x41\x64minQuotaPolicy\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\x0cpolicy_value\x18\x02 \x01(\x03\x12U\n\ndimensions\x18\x03 \x03(\x0b\x32\x41.google.api.serviceusage.v1beta1.AdminQuotaPolicy.DimensionsEntry\x12\x0e\n\x06metric\x18\x04 \x01(\t\x12\x0c\n\x04unit\x18\x05 \x01(\t\x12\x11\n\tcontainer\x18\x06 \x01(\t\x1a\x31\n\x0f\x44imensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"3\n\x0fServiceIdentity\x12\r\n\x05\x65mail\x18\x01 \x01(\t\x12\x11\n\tunique_id\x18\x02 \x01(\t*9\n\x05State\x12\x15\n\x11STATE_UNSPECIFIED\x10\x00\x12\x0c\n\x08\x44ISABLED\x10\x01\x12\x0b\n\x07\x45NABLED\x10\x02*<\n\tQuotaView\x12\x1a\n\x16QUOTA_VIEW_UNSPECIFIED\x10\x00\x12\t\n\x05\x42\x41SIC\x10\x01\x12\x08\n\x04\x46ULL\x10\x02*~\n\x10QuotaSafetyCheck\x12\"\n\x1eQUOTA_SAFETY_CHECK_UNSPECIFIED\x10\x00\x12\x1e\n\x1aLIMIT_DECREASE_BELOW_USAGE\x10\x01\x12&\n\"LIMIT_DECREASE_PERCENTAGE_TOO_HIGH\x10\x02\x42\xed\x01\n#com.google.api.serviceusage.v1beta1B\x0eResourcesProtoP\x01ZKgoogle.golang.org/genproto/googleapis/api/serviceusage/v1beta1;serviceusage\xaa\x02\x1fGoogle.Api.ServiceUsage.V1Beta1\xca\x02\x1fGoogle\\Api\\ServiceUsage\\V1beta1\xea\x02\"Google::Api::ServiceUsage::V1beta1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.serviceusage.v1beta1.resources_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#com.google.api.serviceusage.v1beta1B\016ResourcesProtoP\001ZKgoogle.golang.org/genproto/googleapis/api/serviceusage/v1beta1;serviceusage\252\002\037Google.Api.ServiceUsage.V1Beta1\312\002\037Google\\Api\\ServiceUsage\\V1beta1\352\002\"Google::Api::ServiceUsage::V1beta1'
  _QUOTABUCKET_DIMENSIONSENTRY._options = None
  _QUOTABUCKET_DIMENSIONSENTRY._serialized_options = b'8\001'
  _QUOTAOVERRIDE_DIMENSIONSENTRY._options = None
  _QUOTAOVERRIDE_DIMENSIONSENTRY._serialized_options = b'8\001'
  _PRODUCERQUOTAPOLICY_DIMENSIONSENTRY._options = None
  _PRODUCERQUOTAPOLICY_DIMENSIONSENTRY._serialized_options = b'8\001'
  _ADMINQUOTAPOLICY_DIMENSIONSENTRY._options = None
  _ADMINQUOTAPOLICY_DIMENSIONSENTRY._serialized_options = b'8\001'
  _globals['_STATE']._serialized_start=2803
  _globals['_STATE']._serialized_end=2860
  _globals['_QUOTAVIEW']._serialized_start=2862
  _globals['_QUOTAVIEW']._serialized_end=2922
  _globals['_QUOTASAFETYCHECK']._serialized_start=2924
  _globals['_QUOTASAFETYCHECK']._serialized_end=3050
  _globals['_SERVICE']._serialized_start=308
  _globals['_SERVICE']._serialized_end=466
  _globals['_SERVICECONFIG']._serialized_start=469
  _globals['_SERVICECONFIG']._serialized_end=874
  _globals['_OPERATIONMETADATA']._serialized_start=876
  _globals['_OPERATIONMETADATA']._serialized_end=919
  _globals['_CONSUMERQUOTAMETRIC']._serialized_start=922
  _globals['_CONSUMERQUOTAMETRIC']._serialized_end=1188
  _globals['_CONSUMERQUOTALIMIT']._serialized_start=1191
  _globals['_CONSUMERQUOTALIMIT']._serialized_end=1405
  _globals['_QUOTABUCKET']._serialized_start=1408
  _globals['_QUOTABUCKET']._serialized_end=1909
  _globals['_QUOTABUCKET_DIMENSIONSENTRY']._serialized_start=1860
  _globals['_QUOTABUCKET_DIMENSIONSENTRY']._serialized_end=1909
  _globals['_QUOTAOVERRIDE']._serialized_start=1912
  _globals['_QUOTAOVERRIDE']._serialized_end=2163
  _globals['_QUOTAOVERRIDE_DIMENSIONSENTRY']._serialized_start=1860
  _globals['_QUOTAOVERRIDE_DIMENSIONSENTRY']._serialized_end=1909
  _globals['_OVERRIDEINLINESOURCE']._serialized_start=2165
  _globals['_OVERRIDEINLINESOURCE']._serialized_end=2254
  _globals['_PRODUCERQUOTAPOLICY']._serialized_start=2257
  _globals['_PRODUCERQUOTAPOLICY']._serialized_end=2504
  _globals['_PRODUCERQUOTAPOLICY_DIMENSIONSENTRY']._serialized_start=1860
  _globals['_PRODUCERQUOTAPOLICY_DIMENSIONSENTRY']._serialized_end=1909
  _globals['_ADMINQUOTAPOLICY']._serialized_start=2507
  _globals['_ADMINQUOTAPOLICY']._serialized_end=2748
  _globals['_ADMINQUOTAPOLICY_DIMENSIONSENTRY']._serialized_start=1860
  _globals['_ADMINQUOTAPOLICY_DIMENSIONSENTRY']._serialized_end=1909
  _globals['_SERVICEIDENTITY']._serialized_start=2750
  _globals['_SERVICEIDENTITY']._serialized_end=2801
