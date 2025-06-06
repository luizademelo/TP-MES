
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api.serviceusage.v1 import resources_pb2 as google_dot_api_dot_serviceusage_dot_v1_dot_resources__pb2
from google.longrunning import operations_pb2 as google_dot_longrunning_dot_operations__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n-google/api/serviceusage/v1/serviceusage.proto\x12\x1agoogle.api.serviceusage.v1\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a*google/api/serviceusage/v1/resources.proto\x1a#google/longrunning/operations.proto\"$\n\x14\x45nableServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"M\n\x15\x45nableServiceResponse\x12\x34\n\x07service\x18\x01 \x01(\x0b\x32#.google.api.serviceusage.v1.Service\"\x92\x02\n\x15\x44isableServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\"\n\x1a\x64isable_dependent_services\x18\x02 \x01(\x08\x12l\n\x1a\x63heck_if_service_has_usage\x18\x03 \x01(\x0e\x32H.google.api.serviceusage.v1.DisableServiceRequest.CheckIfServiceHasUsage\"Y\n\x16\x43heckIfServiceHasUsage\x12*\n&CHECK_IF_SERVICE_HAS_USAGE_UNSPECIFIED\x10\x00\x12\x08\n\x04SKIP\x10\x01\x12\t\n\x05\x43HECK\x10\x02\"N\n\x16\x44isableServiceResponse\x12\x34\n\x07service\x18\x01 \x01(\x0b\x32#.google.api.serviceusage.v1.Service\"!\n\x11GetServiceRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"\\\n\x13ListServicesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x02 \x01(\x05\x12\x12\n\npage_token\x18\x03 \x01(\t\x12\x0e\n\x06\x66ilter\x18\x04 \x01(\t\"f\n\x14ListServicesResponse\x12\x35\n\x08services\x18\x01 \x03(\x0b\x32#.google.api.serviceusage.v1.Service\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"A\n\x1a\x42\x61tchEnableServicesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x13\n\x0bservice_ids\x18\x02 \x03(\t\"\xe9\x01\n\x1b\x42\x61tchEnableServicesResponse\x12\x35\n\x08services\x18\x01 \x03(\x0b\x32#.google.api.serviceusage.v1.Service\x12W\n\x08\x66\x61ilures\x18\x02 \x03(\x0b\x32\x45.google.api.serviceusage.v1.BatchEnableServicesResponse.EnableFailure\x1a:\n\rEnableFailure\x12\x12\n\nservice_id\x18\x01 \x01(\t\x12\x15\n\rerror_message\x18\x02 \x01(\t\"8\n\x17\x42\x61tchGetServicesRequest\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\r\n\x05names\x18\x02 \x03(\t\"Q\n\x18\x42\x61tchGetServicesResponse\x12\x35\n\x08services\x18\x01 \x03(\x0b\x32#.google.api.serviceusage.v1.Service2\xe8\t\n\x0cServiceUsage\x12\xba\x01\n\rEnableService\x12\x30.google.api.serviceusage.v1.EnableServiceRequest\x1a\x1d.google.longrunning.Operation\"X\xca\x41*\n\x15\x45nableServiceResponse\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02%\" /v1/{name=*/*/services/*}:enable:\x01*\x12\xbe\x01\n\x0e\x44isableService\x12\x31.google.api.serviceusage.v1.DisableServiceRequest\x1a\x1d.google.longrunning.Operation\"Z\xca\x41+\n\x16\x44isableServiceResponse\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02&\"!/v1/{name=*/*/services/*}:disable:\x01*\x12\x83\x01\n\nGetService\x12-.google.api.serviceusage.v1.GetServiceRequest\x1a#.google.api.serviceusage.v1.Service\"!\x82\xd3\xe4\x93\x02\x1b\x12\x19/v1/{name=*/*/services/*}\x12\x94\x01\n\x0cListServices\x12/.google.api.serviceusage.v1.ListServicesRequest\x1a\x30.google.api.serviceusage.v1.ListServicesResponse\"!\x82\xd3\xe4\x93\x02\x1b\x12\x19/v1/{parent=*/*}/services\x12\xd1\x01\n\x13\x42\x61tchEnableServices\x12\x36.google.api.serviceusage.v1.BatchEnableServicesRequest\x1a\x1d.google.longrunning.Operation\"c\xca\x41\x30\n\x1b\x42\x61tchEnableServicesResponse\x12\x11OperationMetadata\x82\xd3\xe4\x93\x02*\"%/v1/{parent=*/*}/services:batchEnable:\x01*\x12\xa9\x01\n\x10\x42\x61tchGetServices\x12\x33.google.api.serviceusage.v1.BatchGetServicesRequest\x1a\x34.google.api.serviceusage.v1.BatchGetServicesResponse\"*\x82\xd3\xe4\x93\x02$\x12\"/v1/{parent=*/*}/services:batchGet\x1a\xbc\x01\xca\x41\x1bserviceusage.googleapis.com\xd2\x41\x9a\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.managementB\xdb\x01\n\x1e\x63om.google.api.serviceusage.v1B\x11ServiceUsageProtoP\x01ZDcloud.google.com/go/serviceusage/apiv1/serviceusagepb;serviceusagepb\xaa\x02\x1cGoogle.Cloud.ServiceUsage.V1\xca\x02\x1cGoogle\\Cloud\\ServiceUsage\\V1\xea\x02\x1fGoogle::Cloud::ServiceUsage::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.serviceusage.v1.serviceusage_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.google.api.serviceusage.v1B\021ServiceUsageProtoP\001ZDcloud.google.com/go/serviceusage/apiv1/serviceusagepb;serviceusagepb\252\002\034Google.Cloud.ServiceUsage.V1\312\002\034Google\\Cloud\\ServiceUsage\\V1\352\002\037Google::Cloud::ServiceUsage::V1'
  _SERVICEUSAGE._options = None
  _SERVICEUSAGE._serialized_options = b'\312A\033serviceusage.googleapis.com\322A\232\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.management'
  _SERVICEUSAGE.methods_by_name['EnableService']._options = None
  _SERVICEUSAGE.methods_by_name['EnableService']._serialized_options = b'\312A*\n\025EnableServiceResponse\022\021OperationMetadata\202\323\344\223\002%\" /v1/{name=*/*/services/*}:enable:\001*'
  _SERVICEUSAGE.methods_by_name['DisableService']._options = None
  _SERVICEUSAGE.methods_by_name['DisableService']._serialized_options = b'\312A+\n\026DisableServiceResponse\022\021OperationMetadata\202\323\344\223\002&\"!/v1/{name=*/*/services/*}:disable:\001*'
  _SERVICEUSAGE.methods_by_name['GetService']._options = None
  _SERVICEUSAGE.methods_by_name['GetService']._serialized_options = b'\202\323\344\223\002\033\022\031/v1/{name=*/*/services/*}'
  _SERVICEUSAGE.methods_by_name['ListServices']._options = None
  _SERVICEUSAGE.methods_by_name['ListServices']._serialized_options = b'\202\323\344\223\002\033\022\031/v1/{parent=*/*}/services'
  _SERVICEUSAGE.methods_by_name['BatchEnableServices']._options = None
  _SERVICEUSAGE.methods_by_name['BatchEnableServices']._serialized_options = b'\312A0\n\033BatchEnableServicesResponse\022\021OperationMetadata\202\323\344\223\002*\"%/v1/{parent=*/*}/services:batchEnable:\001*'
  _SERVICEUSAGE.methods_by_name['BatchGetServices']._options = None
  _SERVICEUSAGE.methods_by_name['BatchGetServices']._serialized_options = b'\202\323\344\223\002$\022\"/v1/{parent=*/*}/services:batchGet'
  _globals['_ENABLESERVICEREQUEST']._serialized_start=213
  _globals['_ENABLESERVICEREQUEST']._serialized_end=249
  _globals['_ENABLESERVICERESPONSE']._serialized_start=251
  _globals['_ENABLESERVICERESPONSE']._serialized_end=328
  _globals['_DISABLESERVICEREQUEST']._serialized_start=331
  _globals['_DISABLESERVICEREQUEST']._serialized_end=605
  _globals['_DISABLESERVICEREQUEST_CHECKIFSERVICEHASUSAGE']._serialized_start=516
  _globals['_DISABLESERVICEREQUEST_CHECKIFSERVICEHASUSAGE']._serialized_end=605
  _globals['_DISABLESERVICERESPONSE']._serialized_start=607
  _globals['_DISABLESERVICERESPONSE']._serialized_end=685
  _globals['_GETSERVICEREQUEST']._serialized_start=687
  _globals['_GETSERVICEREQUEST']._serialized_end=720
  _globals['_LISTSERVICESREQUEST']._serialized_start=722
  _globals['_LISTSERVICESREQUEST']._serialized_end=814
  _globals['_LISTSERVICESRESPONSE']._serialized_start=816
  _globals['_LISTSERVICESRESPONSE']._serialized_end=918
  _globals['_BATCHENABLESERVICESREQUEST']._serialized_start=920
  _globals['_BATCHENABLESERVICESREQUEST']._serialized_end=985
  _globals['_BATCHENABLESERVICESRESPONSE']._serialized_start=988
  _globals['_BATCHENABLESERVICESRESPONSE']._serialized_end=1221
  _globals['_BATCHENABLESERVICESRESPONSE_ENABLEFAILURE']._serialized_start=1163
  _globals['_BATCHENABLESERVICESRESPONSE_ENABLEFAILURE']._serialized_end=1221
  _globals['_BATCHGETSERVICESREQUEST']._serialized_start=1223
  _globals['_BATCHGETSERVICESREQUEST']._serialized_end=1279
  _globals['_BATCHGETSERVICESRESPONSE']._serialized_start=1281
  _globals['_BATCHGETSERVICESRESPONSE']._serialized_end=1362
  _globals['_SERVICEUSAGE']._serialized_start=1365
  _globals['_SERVICEUSAGE']._serialized_end=2621
