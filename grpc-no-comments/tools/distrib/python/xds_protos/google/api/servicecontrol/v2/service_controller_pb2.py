
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.rpc.context import attribute_context_pb2 as google_dot_rpc_dot_context_dot_attribute__context__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5google/api/servicecontrol/v2/service_controller.proto\x12\x1cgoogle.api.servicecontrol.v2\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a*google/rpc/context/attribute_context.proto\x1a\x17google/rpc/status.proto\"\xc7\x01\n\x0c\x43heckRequest\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12\x19\n\x11service_config_id\x18\x02 \x01(\t\x12\x38\n\nattributes\x18\x03 \x01(\x0b\x32$.google.rpc.context.AttributeContext\x12=\n\tresources\x18\x04 \x03(\x0b\x32*.google.api.servicecontrol.v2.ResourceInfo\x12\r\n\x05\x66lags\x18\x05 \x01(\t\"c\n\x0cResourceInfo\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0c\n\x04type\x18\x02 \x01(\t\x12\x12\n\npermission\x18\x03 \x01(\t\x12\x11\n\tcontainer\x18\x04 \x01(\t\x12\x10\n\x08location\x18\x05 \x01(\t\"\xae\x01\n\rCheckResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.google.rpc.Status\x12I\n\x07headers\x18\x02 \x03(\x0b\x32\x38.google.api.servicecontrol.v2.CheckResponse.HeadersEntry\x1a.\n\x0cHeadersEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"z\n\rReportRequest\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12\x19\n\x11service_config_id\x18\x02 \x01(\t\x12\x38\n\noperations\x18\x03 \x03(\x0b\x32$.google.rpc.context.AttributeContext\"\x10\n\x0eReportResponse\"Q\n\x10ResourceInfoList\x12=\n\tresources\x18\x01 \x03(\x0b\x32*.google.api.servicecontrol.v2.ResourceInfo2\xbc\x03\n\x11ServiceController\x12\x8e\x01\n\x05\x43heck\x12*.google.api.servicecontrol.v2.CheckRequest\x1a+.google.api.servicecontrol.v2.CheckResponse\",\x82\xd3\xe4\x93\x02&\"!/v2/services/{service_name}:check:\x01*\x12\x92\x01\n\x06Report\x12+.google.api.servicecontrol.v2.ReportRequest\x1a,.google.api.servicecontrol.v2.ReportResponse\"-\x82\xd3\xe4\x93\x02\'\"\"/v2/services/{service_name}:report:\x01*\x1a\x80\x01\xca\x41\x1dservicecontrol.googleapis.com\xd2\x41]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrolB\xf8\x01\n com.google.api.servicecontrol.v2B\x16ServiceControllerProtoP\x01ZJgoogle.golang.org/genproto/googleapis/api/servicecontrol/v2;servicecontrol\xf8\x01\x01\xa2\x02\x04GASC\xaa\x02\x1eGoogle.Cloud.ServiceControl.V2\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V2\xea\x02!Google::Cloud::ServiceControl::V2b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v2.service_controller_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v2B\026ServiceControllerProtoP\001ZJgoogle.golang.org/genproto/googleapis/api/servicecontrol/v2;servicecontrol\370\001\001\242\002\004GASC\252\002\036Google.Cloud.ServiceControl.V2\312\002\036Google\\Cloud\\ServiceControl\\V2\352\002!Google::Cloud::ServiceControl::V2'
  _CHECKRESPONSE_HEADERSENTRY._options = None
  _CHECKRESPONSE_HEADERSENTRY._serialized_options = b'8\001'
  _SERVICECONTROLLER._options = None
  _SERVICECONTROLLER._serialized_options = b'\312A\035servicecontrol.googleapis.com\322A]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrol'
  _SERVICECONTROLLER.methods_by_name['Check']._options = None
  _SERVICECONTROLLER.methods_by_name['Check']._serialized_options = b'\202\323\344\223\002&\"!/v2/services/{service_name}:check:\001*'
  _SERVICECONTROLLER.methods_by_name['Report']._options = None
  _SERVICECONTROLLER.methods_by_name['Report']._serialized_options = b'\202\323\344\223\002\'\"\"/v2/services/{service_name}:report:\001*'
  _globals['_CHECKREQUEST']._serialized_start=212
  _globals['_CHECKREQUEST']._serialized_end=411
  _globals['_RESOURCEINFO']._serialized_start=413
  _globals['_RESOURCEINFO']._serialized_end=512
  _globals['_CHECKRESPONSE']._serialized_start=515
  _globals['_CHECKRESPONSE']._serialized_end=689
  _globals['_CHECKRESPONSE_HEADERSENTRY']._serialized_start=643
  _globals['_CHECKRESPONSE_HEADERSENTRY']._serialized_end=689
  _globals['_REPORTREQUEST']._serialized_start=691
  _globals['_REPORTREQUEST']._serialized_end=813
  _globals['_REPORTRESPONSE']._serialized_start=815
  _globals['_REPORTRESPONSE']._serialized_end=831
  _globals['_RESOURCEINFOLIST']._serialized_start=833
  _globals['_RESOURCEINFOLIST']._serialized_end=914
  _globals['_SERVICECONTROLLER']._serialized_start=917
  _globals['_SERVICECONTROLLER']._serialized_end=1361
