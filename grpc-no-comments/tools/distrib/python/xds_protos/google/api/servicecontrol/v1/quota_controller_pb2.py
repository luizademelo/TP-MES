
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api.servicecontrol.v1 import metric_value_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_metric__value__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3google/api/servicecontrol/v1/quota_controller.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a\x1cgoogle/api/annotations.proto\x1a/google/api/servicecontrol/v1/metric_value.proto\x1a\x17google/rpc/status.proto\x1a\x17google/api/client.proto\"\x91\x01\n\x14\x41llocateQuotaRequest\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12H\n\x12\x61llocate_operation\x18\x02 \x01(\x0b\x32,.google.api.servicecontrol.v1.QuotaOperation\x12\x19\n\x11service_config_id\x18\x04 \x01(\t\"\xc6\x03\n\x0eQuotaOperation\x12\x14\n\x0coperation_id\x18\x01 \x01(\t\x12\x13\n\x0bmethod_name\x18\x02 \x01(\t\x12\x13\n\x0b\x63onsumer_id\x18\x03 \x01(\t\x12H\n\x06labels\x18\x04 \x03(\x0b\x32\x38.google.api.servicecontrol.v1.QuotaOperation.LabelsEntry\x12\x43\n\rquota_metrics\x18\x05 \x03(\x0b\x32,.google.api.servicecontrol.v1.MetricValueSet\x12J\n\nquota_mode\x18\x06 \x01(\x0e\x32\x36.google.api.servicecontrol.v1.QuotaOperation.QuotaMode\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"j\n\tQuotaMode\x12\x0f\n\x0bUNSPECIFIED\x10\x00\x12\n\n\x06NORMAL\x10\x01\x12\x0f\n\x0b\x42\x45ST_EFFORT\x10\x02\x12\x0e\n\nCHECK_ONLY\x10\x03\x12\x0e\n\nQUERY_ONLY\x10\x04\x12\x0f\n\x0b\x41\x44JUST_ONLY\x10\x05\"\xd0\x01\n\x15\x41llocateQuotaResponse\x12\x14\n\x0coperation_id\x18\x01 \x01(\t\x12\x41\n\x0f\x61llocate_errors\x18\x02 \x03(\x0b\x32(.google.api.servicecontrol.v1.QuotaError\x12\x43\n\rquota_metrics\x18\x03 \x03(\x0b\x32,.google.api.servicecontrol.v1.MetricValueSet\x12\x19\n\x11service_config_id\x18\x04 \x01(\t\"\x9c\x02\n\nQuotaError\x12;\n\x04\x63ode\x18\x01 \x01(\x0e\x32-.google.api.servicecontrol.v1.QuotaError.Code\x12\x0f\n\x07subject\x18\x02 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x03 \x01(\t\x12\"\n\x06status\x18\x04 \x01(\x0b\x32\x12.google.rpc.Status\"\x86\x01\n\x04\x43ode\x12\x0f\n\x0bUNSPECIFIED\x10\x00\x12\x16\n\x12RESOURCE_EXHAUSTED\x10\x08\x12\x16\n\x12\x42ILLING_NOT_ACTIVE\x10k\x12\x13\n\x0fPROJECT_DELETED\x10l\x12\x13\n\x0f\x41PI_KEY_INVALID\x10i\x12\x13\n\x0f\x41PI_KEY_EXPIRED\x10p2\xc5\x02\n\x0fQuotaController\x12\xae\x01\n\rAllocateQuota\x12\x32.google.api.servicecontrol.v1.AllocateQuotaRequest\x1a\x33.google.api.servicecontrol.v1.AllocateQuotaResponse\"4\x82\xd3\xe4\x93\x02.\")/v1/services/{service_name}:allocateQuota:\x01*\x1a\x80\x01\xca\x41\x1dservicecontrol.googleapis.com\xd2\x41]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrolB\xef\x01\n com.google.api.servicecontrol.v1B\x14QuotaControllerProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xf8\x01\x01\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.quota_controller_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\024QuotaControllerProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\370\001\001\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _QUOTAOPERATION_LABELSENTRY._options = None
  _QUOTAOPERATION_LABELSENTRY._serialized_options = b'8\001'
  _QUOTACONTROLLER._options = None
  _QUOTACONTROLLER._serialized_options = b'\312A\035servicecontrol.googleapis.com\322A]https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/servicecontrol'
  _QUOTACONTROLLER.methods_by_name['AllocateQuota']._options = None
  _QUOTACONTROLLER.methods_by_name['AllocateQuota']._serialized_options = b'\202\323\344\223\002.\")/v1/services/{service_name}:allocateQuota:\001*'
  _globals['_ALLOCATEQUOTAREQUEST']._serialized_start=215
  _globals['_ALLOCATEQUOTAREQUEST']._serialized_end=360
  _globals['_QUOTAOPERATION']._serialized_start=363
  _globals['_QUOTAOPERATION']._serialized_end=817
  _globals['_QUOTAOPERATION_LABELSENTRY']._serialized_start=664
  _globals['_QUOTAOPERATION_LABELSENTRY']._serialized_end=709
  _globals['_QUOTAOPERATION_QUOTAMODE']._serialized_start=711
  _globals['_QUOTAOPERATION_QUOTAMODE']._serialized_end=817
  _globals['_ALLOCATEQUOTARESPONSE']._serialized_start=820
  _globals['_ALLOCATEQUOTARESPONSE']._serialized_end=1028
  _globals['_QUOTAERROR']._serialized_start=1031
  _globals['_QUOTAERROR']._serialized_end=1315
  _globals['_QUOTAERROR_CODE']._serialized_start=1181
  _globals['_QUOTAERROR_CODE']._serialized_end=1315
  _globals['_QUOTACONTROLLER']._serialized_start=1318
  _globals['_QUOTACONTROLLER']._serialized_end=1643
