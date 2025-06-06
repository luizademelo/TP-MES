
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api.servicecontrol.v1 import check_error_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_check__error__pb2
from google.api.servicecontrol.v1 import operation_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_operation__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5google/api/servicecontrol/v1/service_controller.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a.google/api/servicecontrol/v1/check_error.proto\x1a,google/api/servicecontrol/v1/operation.proto\x1a\x17google/rpc/status.proto\"{\n\x0c\x43heckRequest\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12:\n\toperation\x18\x02 \x01(\x0b\x32\'.google.api.servicecontrol.v1.Operation\x12\x19\n\x11service_config_id\x18\x04 \x01(\t\"\xfc\x04\n\rCheckResponse\x12\x14\n\x0coperation_id\x18\x01 \x01(\t\x12>\n\x0c\x63heck_errors\x18\x02 \x03(\x0b\x32(.google.api.servicecontrol.v1.CheckError\x12\x19\n\x11service_config_id\x18\x05 \x01(\t\x12\x1a\n\x12service_rollout_id\x18\x0b \x01(\t\x12I\n\ncheck_info\x18\x06 \x01(\x0b\x32\x35.google.api.servicecontrol.v1.CheckResponse.CheckInfo\x1a\x8b\x01\n\tCheckInfo\x12\x18\n\x10unused_arguments\x18\x01 \x03(\t\x12O\n\rconsumer_info\x18\x02 \x01(\x0b\x32\x38.google.api.servicecontrol.v1.CheckResponse.ConsumerInfo\x12\x13\n\x0b\x61pi_key_uid\x18\x05 \x01(\t\x1a\x84\x02\n\x0c\x43onsumerInfo\x12\x16\n\x0eproject_number\x18\x01 \x01(\x03\x12S\n\x04type\x18\x02 \x01(\x0e\x32\x45.google.api.servicecontrol.v1.CheckResponse.ConsumerInfo.ConsumerType\x12\x17\n\x0f\x63onsumer_number\x18\x03 \x01(\x03\"n\n\x0c\x43onsumerType\x12\x1d\n\x19\x43ONSUMER_TYPE_UNSPECIFIED\x10\x00\x12\x0b\n\x07PROJECT\x10\x01\x12\n\n\x06\x46OLDER\x10\x02\x12\x10\n\x0cORGANIZATION\x10\x03\x12\x14\n\x10SERVICE_SPECIFIC\x10\x04\"}\n\rReportRequest\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12;\n\noperations\x18\x02 \x03(\x0b\x32\'.google.api.servicecontrol.v1.Operation\x12\x19\n\x11service_config_id\x18\x03 \x01(\t\"\xe1\x01\n\x0eReportResponse\x12O\n\rreport_errors\x18\x01 \x03(\x0b\x32\x38.google.api.servicecontrol.v1.ReportResponse.ReportError\x12\x19\n\x11service_config_id\x18\x02 \x01(\t\x12\x1a\n\x12service_rollout_id\x18\x04 \x01(\t\x1aG\n\x0bReportError\x12\x14\n\x0coperation_id\x18\x01 \x01(\t\x12\"\n\x06status\x18\x02 \x01(\x0b\x32\x12.google.rpc.Status2\xbc\x03\n\x11ServiceController\x12\x8e\x01\n\x05\x43heck\x12*.google.api.servicecontrol.v1.CheckRequest\x1a+.google.api.servicecontrol.v1.CheckResponse\",\x82\xd3\xe4\x93\x02&\"!/v1/services/{service_name}:check:\x01*\x12\x92\x01\n\x06Report\x12+.google.api.servicecontrol.v1.ReportRequest\x1a,.google.api.servicecontrol.v1.ReportResponse\"-\x82\xd3\xe4\x93\x02\'\"\"/v1/services/{service_name}:report:\x01*\x1a\x80\x01\xca\x41\x1dservicecontrol.googleapis.com\xd2\x41]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrolB\xf8\x01\n com.google.api.servicecontrol.v1B\x16ServiceControllerProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xf8\x01\x01\xa2\x02\x04GASC\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.service_controller_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\026ServiceControllerProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\370\001\001\242\002\004GASC\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _SERVICECONTROLLER._options = None
  _SERVICECONTROLLER._serialized_options = b'\312A\035servicecontrol.googleapis.com\322A]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrol'
  _SERVICECONTROLLER.methods_by_name['Check']._options = None
  _SERVICECONTROLLER.methods_by_name['Check']._serialized_options = b'\202\323\344\223\002&\"!/v1/services/{service_name}:check:\001*'
  _SERVICECONTROLLER.methods_by_name['Report']._options = None
  _SERVICECONTROLLER.methods_by_name['Report']._serialized_options = b'\202\323\344\223\002\'\"\"/v1/services/{service_name}:report:\001*'
  _globals['_CHECKREQUEST']._serialized_start=261
  _globals['_CHECKREQUEST']._serialized_end=384
  _globals['_CHECKRESPONSE']._serialized_start=387
  _globals['_CHECKRESPONSE']._serialized_end=1023
  _globals['_CHECKRESPONSE_CHECKINFO']._serialized_start=621
  _globals['_CHECKRESPONSE_CHECKINFO']._serialized_end=760
  _globals['_CHECKRESPONSE_CONSUMERINFO']._serialized_start=763
  _globals['_CHECKRESPONSE_CONSUMERINFO']._serialized_end=1023
  _globals['_CHECKRESPONSE_CONSUMERINFO_CONSUMERTYPE']._serialized_start=913
  _globals['_CHECKRESPONSE_CONSUMERINFO_CONSUMERTYPE']._serialized_end=1023
  _globals['_REPORTREQUEST']._serialized_start=1025
  _globals['_REPORTREQUEST']._serialized_end=1150
  _globals['_REPORTRESPONSE']._serialized_start=1153
  _globals['_REPORTRESPONSE']._serialized_end=1378
  _globals['_REPORTRESPONSE_REPORTERROR']._serialized_start=1307
  _globals['_REPORTRESPONSE_REPORTERROR']._serialized_end=1378
  _globals['_SERVICECONTROLLER']._serialized_start=1381
  _globals['_SERVICECONTROLLER']._serialized_end=1825
