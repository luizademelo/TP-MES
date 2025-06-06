
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api.serviceusage.v1beta1 import resources_pb2 as google_dot_api_dot_serviceusage_dot_v1beta1_dot_resources__pb2
from google.longrunning import operations_pb2 as google_dot_longrunning_dot_operations__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.protobuf import field_mask_pb2 as google_dot_protobuf_dot_field__mask__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2google/api/serviceusage/v1beta1/serviceusage.proto\x12\x1fgoogle.api.serviceusage.v1beta1\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a/google/api/serviceusage/v1beta1/resources.proto\x1a#google/longrunning/operations.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a google/protobuf/field_mask.proto\"$\n\x14\x45nableServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"%\n\x15\x44isableServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"!\n\x11GetServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"\\\n\x13ListServicesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x02 \x01(\x05\x12\x12\n\npage_token\x18\x03 \x01(\t\x12\x0e\n\x06\x66ilter\x18\x04 \x01(\t\"k\n\x14ListServicesResponse\x12:\n\x08services\x18\x01 \x03(\x0b\x32(.google.api.serviceusage.v1beta1.Service\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"A\n\x1a\x42\x61tchEnableServicesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x13\n\x0bservice_ids\x18\x02 \x03(\t\"\x92\x01\n\x1fListConsumerQuotaMetricsRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x02 \x01(\x05\x12\x12\n\npage_token\x18\x03 \x01(\t\x12\x38\n\x04view\x18\x04 \x01(\x0e\x32*.google.api.serviceusage.v1beta1.QuotaView\"\x82\x01\n ListConsumerQuotaMetricsResponse\x12\x45\n\x07metrics\x18\x01 \x03(\x0b\x32\x34.google.api.serviceusage.v1beta1.ConsumerQuotaMetric\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"g\n\x1dGetConsumerQuotaMetricRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x38\n\x04view\x18\x02 \x01(\x0e\x32*.google.api.serviceusage.v1beta1.QuotaView\"f\n\x1cGetConsumerQuotaLimitRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x38\n\x04view\x18\x02 \x01(\x0e\x32*.google.api.serviceusage.v1beta1.QuotaView\"\xc4\x01\n\x1a\x43reateAdminOverrideRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12@\n\x08override\x18\x02 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12\x45\n\nforce_only\x18\x04 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"\xf3\x01\n\x1aUpdateAdminOverrideRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12@\n\x08override\x18\x02 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12/\n\x0bupdate_mask\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.FieldMask\x12\x45\n\nforce_only\x18\x05 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"\x80\x01\n\x1a\x44\x65leteAdminOverrideRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05\x66orce\x18\x02 \x01(\x08\x12\x45\n\nforce_only\x18\x03 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"R\n\x19ListAdminOverridesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x02 \x01(\x05\x12\x12\n\npage_token\x18\x03 \x01(\t\"x\n\x1aListAdminOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"f\n!BatchCreateAdminOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\"\xdd\x01\n\x1bImportAdminOverridesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12N\n\rinline_source\x18\x02 \x01(\x0b\x32\x35.google.api.serviceusage.v1beta1.OverrideInlineSourceH\x00\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12\x45\n\nforce_only\x18\x04 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheckB\x08\n\x06source\"a\n\x1cImportAdminOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\"\x1e\n\x1cImportAdminOverridesMetadata\"\xc7\x01\n\x1d\x43reateConsumerOverrideRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12@\n\x08override\x18\x02 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12\x45\n\nforce_only\x18\x04 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"\xf6\x01\n\x1dUpdateConsumerOverrideRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12@\n\x08override\x18\x02 \x01(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12/\n\x0bupdate_mask\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.FieldMask\x12\x45\n\nforce_only\x18\x05 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"\x83\x01\n\x1d\x44\x65leteConsumerOverrideRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05\x66orce\x18\x02 \x01(\x08\x12\x45\n\nforce_only\x18\x03 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheck\"U\n\x1cListConsumerOverridesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x02 \x01(\x05\x12\x12\n\npage_token\x18\x03 \x01(\t\"{\n\x1dListConsumerOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"i\n$BatchCreateConsumerOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\"\xe0\x01\n\x1eImportConsumerOverridesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12N\n\rinline_source\x18\x02 \x01(\x0b\x32\x35.google.api.serviceusage.v1beta1.OverrideInlineSourceH\x00\x12\r\n\x05\x66orce\x18\x03 \x01(\x08\x12\x45\n\nforce_only\x18\x04 \x03(\x0e\x32\x31.google.api.serviceusage.v1beta1.QuotaSafetyCheckB\x08\n\x06source\"d\n\x1fImportConsumerOverridesResponse\x12\x41\n\toverrides\x18\x01 \x03(\x0b\x32..google.api.serviceusage.v1beta1.QuotaOverride\"!\n\x1fImportConsumerOverridesMetadata\"g\n ImportAdminQuotaPoliciesResponse\x12\x43\n\x08policies\x18\x01 \x03(\x0b\x32\x31.google.api.serviceusage.v1beta1.AdminQuotaPolicy\"\"\n ImportAdminQuotaPoliciesMetadata\" \n\x1e\x43reateAdminQuotaPolicyMetadata\" \n\x1eUpdateAdminQuotaPolicyMetadata\" \n\x1e\x44\x65leteAdminQuotaPolicyMetadata\"0\n\x1eGenerateServiceIdentityRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\"\xf7\x01\n\x1aGetServiceIdentityResponse\x12\x42\n\x08identity\x18\x01 \x01(\x0b\x32\x30.google.api.serviceusage.v1beta1.ServiceIdentity\x12X\n\x05state\x18\x02 \x01(\x0e\x32I.google.api.serviceusage.v1beta1.GetServiceIdentityResponse.IdentityState\";\n\rIdentityState\x12\x1e\n\x1aIDENTITY_STATE_UNSPECIFIED\x10\x00\x12\n\n\x06\x41\x43TIVE\x10\x01\"\x1c\n\x1aGetServiceIdentityMetadata2\xfc#\n\x0cServiceUsage\x12\xc7\x01\n\rEnableService\x12\x35.google.api.serviceusage.v1beta1.EnableServiceRequest\x1a\x1d.google.longrunning.Operation\"`\x88\x02\x01\xca\x41*\n\x15google.protobuf.Empty\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02*\"%/v1beta1/{name=*/*/services/*}:enable:\x01*\x12\xca\x01\n\x0e\x44isableService\x12\x36.google.api.serviceusage.v1beta1.DisableServiceRequest\x1a\x1d.google.longrunning.Operation\"a\x88\x02\x01\xca\x41*\n\x15google.protobuf.Empty\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02+\"&/v1beta1/{name=*/*/services/*}:disable:\x01*\x12\x95\x01\n\nGetService\x12\x32.google.api.serviceusage.v1beta1.GetServiceRequest\x1a(.google.api.serviceusage.v1beta1.Service\")\x88\x02\x01\x82\xd3\xe4\x93\x02 \x12\x1e/v1beta1/{name=*/*/services/*}\x12\xa6\x01\n\x0cListServices\x12\x34.google.api.serviceusage.v1beta1.ListServicesRequest\x1a\x35.google.api.serviceusage.v1beta1.ListServicesResponse\")\x88\x02\x01\x82\xd3\xe4\x93\x02 \x12\x1e/v1beta1/{parent=*/*}/services\x12\xd8\x01\n\x13\x42\x61tchEnableServices\x12;.google.api.serviceusage.v1beta1.BatchEnableServicesRequest\x1a\x1d.google.longrunning.Operation\"e\x88\x02\x01\xca\x41*\n\x15google.protobuf.Empty\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02/\"*/v1beta1/{parent=*/*}/services:batchEnable:\x01*\x12\xde\x01\n\x18ListConsumerQuotaMetrics\x12@.google.api.serviceusage.v1beta1.ListConsumerQuotaMetricsRequest\x1a\x41.google.api.serviceusage.v1beta1.ListConsumerQuotaMetricsResponse\"=\x82\xd3\xe4\x93\x02\x37\x12\x35/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics\x12\xcd\x01\n\x16GetConsumerQuotaMetric\x12>.google.api.serviceusage.v1beta1.GetConsumerQuotaMetricRequest\x1a\x34.google.api.serviceusage.v1beta1.ConsumerQuotaMetric\"=\x82\xd3\xe4\x93\x02\x37\x12\x35/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*}\x12\xd3\x01\n\x15GetConsumerQuotaLimit\x12=.google.api.serviceusage.v1beta1.GetConsumerQuotaLimitRequest\x1a\x33.google.api.serviceusage.v1beta1.ConsumerQuotaLimit\"F\x82\xd3\xe4\x93\x02@\x12>/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*}\x12\xfa\x01\n\x13\x43reateAdminOverride\x12;.google.api.serviceusage.v1beta1.CreateAdminOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x86\x01\xca\x41\"\n\rQuotaOverride\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02[\"O/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/adminOverrides:\x08override\x12\xfa\x01\n\x13UpdateAdminOverride\x12;.google.api.serviceusage.v1beta1.UpdateAdminOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x86\x01\xca\x41\"\n\rQuotaOverride\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02[2O/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/adminOverrides/*}:\x08override\x12\xf8\x01\n\x13\x44\x65leteAdminOverride\x12;.google.api.serviceusage.v1beta1.DeleteAdminOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x84\x01\xca\x41*\n\x15google.protobuf.Empty\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02Q*O/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/adminOverrides/*}\x12\xe6\x01\n\x12ListAdminOverrides\x12:.google.api.serviceusage.v1beta1.ListAdminOverridesRequest\x1a;.google.api.serviceusage.v1beta1.ListAdminOverridesResponse\"W\x82\xd3\xe4\x93\x02Q\x12O/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/adminOverrides\x12\x8a\x02\n\x14ImportAdminOverrides\x12<.google.api.serviceusage.v1beta1.ImportAdminOverridesRequest\x1a\x1d.google.longrunning.Operation\"\x94\x01\xca\x41<\n\x1cImportAdminOverridesResponse\x12\x1cImportAdminOverridesMetadata\x82\xd3\xe4\x93\x02O\"J/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics:importAdminOverrides:\x01*\x12\x83\x02\n\x16\x43reateConsumerOverride\x12>.google.api.serviceusage.v1beta1.CreateConsumerOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x89\x01\xca\x41\"\n\rQuotaOverride\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02^\"R/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/consumerOverrides:\x08override\x12\x83\x02\n\x16UpdateConsumerOverride\x12>.google.api.serviceusage.v1beta1.UpdateConsumerOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x89\x01\xca\x41\"\n\rQuotaOverride\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02^2R/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/consumerOverrides/*}:\x08override\x12\x81\x02\n\x16\x44\x65leteConsumerOverride\x12>.google.api.serviceusage.v1beta1.DeleteConsumerOverrideRequest\x1a\x1d.google.longrunning.Operation\"\x87\x01\xca\x41*\n\x15google.protobuf.Empty\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02T*R/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/consumerOverrides/*}\x12\xf2\x01\n\x15ListConsumerOverrides\x12=.google.api.serviceusage.v1beta1.ListConsumerOverridesRequest\x1a>.google.api.serviceusage.v1beta1.ListConsumerOverridesResponse\"Z\x82\xd3\xe4\x93\x02T\x12R/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/consumerOverrides\x12\x99\x02\n\x17ImportConsumerOverrides\x12?.google.api.serviceusage.v1beta1.ImportConsumerOverridesRequest\x1a\x1d.google.longrunning.Operation\"\x9d\x01\xca\x41\x42\n\x1fImportConsumerOverridesResponse\x12\x1fImportConsumerOverridesMetadata\x82\xd3\xe4\x93\x02R\"M/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics:importConsumerOverrides:\x01*\x12\xe6\x01\n\x17GenerateServiceIdentity\x12?.google.api.serviceusage.v1beta1.GenerateServiceIdentityRequest\x1a\x1d.google.longrunning.Operation\"k\xca\x41(\n\x0fServiceIdentity\x12\x15google.protobuf.Empty\x82\xd3\xe4\x93\x02:\"8/v1beta1/{parent=*/*/services/*}:generateServiceIdentity\x1a\xbc\x01\xca\x41\x1bserviceusage.googleapis.com\xd2\x41\x9a\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.managementB\xf0\x01\n#com.google.api.serviceusage.v1beta1B\x11ServiceUsageProtoP\x01ZKgoogle.golang.org/genproto/googleapis/api/serviceusage/v1beta1;serviceusage\xaa\x02\x1fGoogle.Api.ServiceUsage.V1Beta1\xca\x02\x1fGoogle\\Api\\ServiceUsage\\V1beta1\xea\x02\"Google::Api::ServiceUsage::V1beta1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.serviceusage.v1beta1.serviceusage_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#com.google.api.serviceusage.v1beta1B\021ServiceUsageProtoP\001ZKgoogle.golang.org/genproto/googleapis/api/serviceusage/v1beta1;serviceusage\252\002\037Google.Api.ServiceUsage.V1Beta1\312\002\037Google\\Api\\ServiceUsage\\V1beta1\352\002\"Google::Api::ServiceUsage::V1beta1'
  _SERVICEUSAGE._options = None
  _SERVICEUSAGE._serialized_options = b'\312A\033serviceusage.googleapis.com\322A\232\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.management'
  _SERVICEUSAGE.methods_by_name['EnableService']._options = None
  _SERVICEUSAGE.methods_by_name['EnableService']._serialized_options = b'\210\002\001\312A*\n\025google.protobuf.Empty\022\021OperationMetadata\202\323\344\223\002*\"%/v1beta1/{name=*/*/services/*}:enable:\001*'
  _SERVICEUSAGE.methods_by_name['DisableService']._options = None
  _SERVICEUSAGE.methods_by_name['DisableService']._serialized_options = b'\210\002\001\312A*\n\025google.protobuf.Empty\022\021OperationMetadata\202\323\344\223\002+\"&/v1beta1/{name=*/*/services/*}:disable:\001*'
  _SERVICEUSAGE.methods_by_name['GetService']._options = None
  _SERVICEUSAGE.methods_by_name['GetService']._serialized_options = b'\210\002\001\202\323\344\223\002 \022\036/v1beta1/{name=*/*/services/*}'
  _SERVICEUSAGE.methods_by_name['ListServices']._options = None
  _SERVICEUSAGE.methods_by_name['ListServices']._serialized_options = b'\210\002\001\202\323\344\223\002 \022\036/v1beta1/{parent=*/*}/services'
  _SERVICEUSAGE.methods_by_name['BatchEnableServices']._options = None
  _SERVICEUSAGE.methods_by_name['BatchEnableServices']._serialized_options = b'\210\002\001\312A*\n\025google.protobuf.Empty\022\021OperationMetadata\202\323\344\223\002/\"*/v1beta1/{parent=*/*}/services:batchEnable:\001*'
  _SERVICEUSAGE.methods_by_name['ListConsumerQuotaMetrics']._options = None
  _SERVICEUSAGE.methods_by_name['ListConsumerQuotaMetrics']._serialized_options = b'\202\323\344\223\0027\0225/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics'
  _SERVICEUSAGE.methods_by_name['GetConsumerQuotaMetric']._options = None
  _SERVICEUSAGE.methods_by_name['GetConsumerQuotaMetric']._serialized_options = b'\202\323\344\223\0027\0225/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*}'
  _SERVICEUSAGE.methods_by_name['GetConsumerQuotaLimit']._options = None
  _SERVICEUSAGE.methods_by_name['GetConsumerQuotaLimit']._serialized_options = b'\202\323\344\223\002@\022>/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*}'
  _SERVICEUSAGE.methods_by_name['CreateAdminOverride']._options = None
  _SERVICEUSAGE.methods_by_name['CreateAdminOverride']._serialized_options = b'\312A\"\n\rQuotaOverride\022\021OperationMetadata\202\323\344\223\002[\"O/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/adminOverrides:\010override'
  _SERVICEUSAGE.methods_by_name['UpdateAdminOverride']._options = None
  _SERVICEUSAGE.methods_by_name['UpdateAdminOverride']._serialized_options = b'\312A\"\n\rQuotaOverride\022\021OperationMetadata\202\323\344\223\002[2O/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/adminOverrides/*}:\010override'
  _SERVICEUSAGE.methods_by_name['DeleteAdminOverride']._options = None
  _SERVICEUSAGE.methods_by_name['DeleteAdminOverride']._serialized_options = b'\312A*\n\025google.protobuf.Empty\022\021OperationMetadata\202\323\344\223\002Q*O/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/adminOverrides/*}'
  _SERVICEUSAGE.methods_by_name['ListAdminOverrides']._options = None
  _SERVICEUSAGE.methods_by_name['ListAdminOverrides']._serialized_options = b'\202\323\344\223\002Q\022O/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/adminOverrides'
  _SERVICEUSAGE.methods_by_name['ImportAdminOverrides']._options = None
  _SERVICEUSAGE.methods_by_name['ImportAdminOverrides']._serialized_options = b'\312A<\n\034ImportAdminOverridesResponse\022\034ImportAdminOverridesMetadata\202\323\344\223\002O\"J/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics:importAdminOverrides:\001*'
  _SERVICEUSAGE.methods_by_name['CreateConsumerOverride']._options = None
  _SERVICEUSAGE.methods_by_name['CreateConsumerOverride']._serialized_options = b'\312A\"\n\rQuotaOverride\022\021OperationMetadata\202\323\344\223\002^\"R/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/consumerOverrides:\010override'
  _SERVICEUSAGE.methods_by_name['UpdateConsumerOverride']._options = None
  _SERVICEUSAGE.methods_by_name['UpdateConsumerOverride']._serialized_options = b'\312A\"\n\rQuotaOverride\022\021OperationMetadata\202\323\344\223\002^2R/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/consumerOverrides/*}:\010override'
  _SERVICEUSAGE.methods_by_name['DeleteConsumerOverride']._options = None
  _SERVICEUSAGE.methods_by_name['DeleteConsumerOverride']._serialized_options = b'\312A*\n\025google.protobuf.Empty\022\021OperationMetadata\202\323\344\223\002T*R/v1beta1/{name=*/*/services/*/consumerQuotaMetrics/*/limits/*/consumerOverrides/*}'
  _SERVICEUSAGE.methods_by_name['ListConsumerOverrides']._options = None
  _SERVICEUSAGE.methods_by_name['ListConsumerOverrides']._serialized_options = b'\202\323\344\223\002T\022R/v1beta1/{parent=*/*/services/*/consumerQuotaMetrics/*/limits/*}/consumerOverrides'
  _SERVICEUSAGE.methods_by_name['ImportConsumerOverrides']._options = None
  _SERVICEUSAGE.methods_by_name['ImportConsumerOverrides']._serialized_options = b'\312AB\n\037ImportConsumerOverridesResponse\022\037ImportConsumerOverridesMetadata\202\323\344\223\002R\"M/v1beta1/{parent=*/*/services/*}/consumerQuotaMetrics:importConsumerOverrides:\001*'
  _SERVICEUSAGE.methods_by_name['GenerateServiceIdentity']._options = None
  _SERVICEUSAGE.methods_by_name['GenerateServiceIdentity']._serialized_options = b'\312A(\n\017ServiceIdentity\022\025google.protobuf.Empty\202\323\344\223\002:\"8/v1beta1/{parent=*/*/services/*}:generateServiceIdentity'
  _globals['_ENABLESERVICEREQUEST']._serialized_start=324
  _globals['_ENABLESERVICEREQUEST']._serialized_end=360
  _globals['_DISABLESERVICEREQUEST']._serialized_start=362
  _globals['_DISABLESERVICEREQUEST']._serialized_end=399
  _globals['_GETSERVICEREQUEST']._serialized_start=401
  _globals['_GETSERVICEREQUEST']._serialized_end=434
  _globals['_LISTSERVICESREQUEST']._serialized_start=436
  _globals['_LISTSERVICESREQUEST']._serialized_end=528
  _globals['_LISTSERVICESRESPONSE']._serialized_start=530
  _globals['_LISTSERVICESRESPONSE']._serialized_end=637
  _globals['_BATCHENABLESERVICESREQUEST']._serialized_start=639
  _globals['_BATCHENABLESERVICESREQUEST']._serialized_end=704
  _globals['_LISTCONSUMERQUOTAMETRICSREQUEST']._serialized_start=707
  _globals['_LISTCONSUMERQUOTAMETRICSREQUEST']._serialized_end=853
  _globals['_LISTCONSUMERQUOTAMETRICSRESPONSE']._serialized_start=856
  _globals['_LISTCONSUMERQUOTAMETRICSRESPONSE']._serialized_end=986
  _globals['_GETCONSUMERQUOTAMETRICREQUEST']._serialized_start=988
  _globals['_GETCONSUMERQUOTAMETRICREQUEST']._serialized_end=1091
  _globals['_GETCONSUMERQUOTALIMITREQUEST']._serialized_start=1093
  _globals['_GETCONSUMERQUOTALIMITREQUEST']._serialized_end=1195
  _globals['_CREATEADMINOVERRIDEREQUEST']._serialized_start=1198
  _globals['_CREATEADMINOVERRIDEREQUEST']._serialized_end=1394
  _globals['_UPDATEADMINOVERRIDEREQUEST']._serialized_start=1397
  _globals['_UPDATEADMINOVERRIDEREQUEST']._serialized_end=1640
  _globals['_DELETEADMINOVERRIDEREQUEST']._serialized_start=1643
  _globals['_DELETEADMINOVERRIDEREQUEST']._serialized_end=1771
  _globals['_LISTADMINOVERRIDESREQUEST']._serialized_start=1773
  _globals['_LISTADMINOVERRIDESREQUEST']._serialized_end=1855
  _globals['_LISTADMINOVERRIDESRESPONSE']._serialized_start=1857
  _globals['_LISTADMINOVERRIDESRESPONSE']._serialized_end=1977
  _globals['_BATCHCREATEADMINOVERRIDESRESPONSE']._serialized_start=1979
  _globals['_BATCHCREATEADMINOVERRIDESRESPONSE']._serialized_end=2081
  _globals['_IMPORTADMINOVERRIDESREQUEST']._serialized_start=2084
  _globals['_IMPORTADMINOVERRIDESREQUEST']._serialized_end=2305
  _globals['_IMPORTADMINOVERRIDESRESPONSE']._serialized_start=2307
  _globals['_IMPORTADMINOVERRIDESRESPONSE']._serialized_end=2404
  _globals['_IMPORTADMINOVERRIDESMETADATA']._serialized_start=2406
  _globals['_IMPORTADMINOVERRIDESMETADATA']._serialized_end=2436
  _globals['_CREATECONSUMEROVERRIDEREQUEST']._serialized_start=2439
  _globals['_CREATECONSUMEROVERRIDEREQUEST']._serialized_end=2638
  _globals['_UPDATECONSUMEROVERRIDEREQUEST']._serialized_start=2641
  _globals['_UPDATECONSUMEROVERRIDEREQUEST']._serialized_end=2887
  _globals['_DELETECONSUMEROVERRIDEREQUEST']._serialized_start=2890
  _globals['_DELETECONSUMEROVERRIDEREQUEST']._serialized_end=3021
  _globals['_LISTCONSUMEROVERRIDESREQUEST']._serialized_start=3023
  _globals['_LISTCONSUMEROVERRIDESREQUEST']._serialized_end=3108
  _globals['_LISTCONSUMEROVERRIDESRESPONSE']._serialized_start=3110
  _globals['_LISTCONSUMEROVERRIDESRESPONSE']._serialized_end=3233
  _globals['_BATCHCREATECONSUMEROVERRIDESRESPONSE']._serialized_start=3235
  _globals['_BATCHCREATECONSUMEROVERRIDESRESPONSE']._serialized_end=3340
  _globals['_IMPORTCONSUMEROVERRIDESREQUEST']._serialized_start=3343
  _globals['_IMPORTCONSUMEROVERRIDESREQUEST']._serialized_end=3567
  _globals['_IMPORTCONSUMEROVERRIDESRESPONSE']._serialized_start=3569
  _globals['_IMPORTCONSUMEROVERRIDESRESPONSE']._serialized_end=3669
  _globals['_IMPORTCONSUMEROVERRIDESMETADATA']._serialized_start=3671
  _globals['_IMPORTCONSUMEROVERRIDESMETADATA']._serialized_end=3704
  _globals['_IMPORTADMINQUOTAPOLICIESRESPONSE']._serialized_start=3706
  _globals['_IMPORTADMINQUOTAPOLICIESRESPONSE']._serialized_end=3809
  _globals['_IMPORTADMINQUOTAPOLICIESMETADATA']._serialized_start=3811
  _globals['_IMPORTADMINQUOTAPOLICIESMETADATA']._serialized_end=3845
  _globals['_CREATEADMINQUOTAPOLICYMETADATA']._serialized_start=3847
  _globals['_CREATEADMINQUOTAPOLICYMETADATA']._serialized_end=3879
  _globals['_UPDATEADMINQUOTAPOLICYMETADATA']._serialized_start=3881
  _globals['_UPDATEADMINQUOTAPOLICYMETADATA']._serialized_end=3913
  _globals['_DELETEADMINQUOTAPOLICYMETADATA']._serialized_start=3915
  _globals['_DELETEADMINQUOTAPOLICYMETADATA']._serialized_end=3947
  _globals['_GENERATESERVICEIDENTITYREQUEST']._serialized_start=3949
  _globals['_GENERATESERVICEIDENTITYREQUEST']._serialized_end=3997
  _globals['_GETSERVICEIDENTITYRESPONSE']._serialized_start=4000
  _globals['_GETSERVICEIDENTITYRESPONSE']._serialized_end=4247
  _globals['_GETSERVICEIDENTITYRESPONSE_IDENTITYSTATE']._serialized_start=4188
  _globals['_GETSERVICEIDENTITYRESPONSE_IDENTITYSTATE']._serialized_end=4247
  _globals['_GETSERVICEIDENTITYMETADATA']._serialized_start=4249
  _globals['_GETSERVICEIDENTITYMETADATA']._serialized_end=4277
  _globals['_SERVICEUSAGE']._serialized_start=4280
  _globals['_SERVICEUSAGE']._serialized_end=8884
