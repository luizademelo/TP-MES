
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import service_pb2 as google_dot_api_dot_service__pb2
from google.api.servicemanagement.v1 import resources_pb2 as google_dot_api_dot_servicemanagement_dot_v1_dot_resources__pb2
from google.longrunning import operations_pb2 as google_dot_longrunning_dot_operations__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n4google/api/servicemanagement/v1/servicemanager.proto\x12\x1fgoogle.api.servicemanagement.v1\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a\x18google/api/service.proto\x1a/google/api/servicemanagement/v1/resources.proto\x1a#google/longrunning/operations.proto\x1a\x19google/protobuf/any.proto\x1a\x1bgoogle/protobuf/empty.proto\"r\n\x13ListServicesRequest\x12\x1b\n\x13producer_project_id\x18\x01 \x01(\t\x12\x11\n\tpage_size\x18\x05 \x01(\x05\x12\x12\n\npage_token\x18\x06 \x01(\t\x12\x17\n\x0b\x63onsumer_id\x18\x07 \x01(\tB\x02\x18\x01\"r\n\x14ListServicesResponse\x12\x41\n\x08services\x18\x01 \x03(\x0b\x32/.google.api.servicemanagement.v1.ManagedService\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\".\n\x11GetServiceRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\"]\n\x14\x43reateServiceRequest\x12\x45\n\x07service\x18\x01 \x01(\x0b\x32/.google.api.servicemanagement.v1.ManagedServiceB\x03\xe0\x41\x02\"1\n\x14\x44\x65leteServiceRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\"3\n\x16UndeleteServiceRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\"[\n\x17UndeleteServiceResponse\x12@\n\x07service\x18\x01 \x01(\x0b\x32/.google.api.servicemanagement.v1.ManagedService\"\xc2\x01\n\x17GetServiceConfigRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x16\n\tconfig_id\x18\x02 \x01(\tB\x03\xe0\x41\x02\x12Q\n\x04view\x18\x03 \x01(\x0e\x32\x43.google.api.servicemanagement.v1.GetServiceConfigRequest.ConfigView\"!\n\nConfigView\x12\t\n\x05\x42\x41SIC\x10\x00\x12\x08\n\x04\x46ULL\x10\x01\"]\n\x19ListServiceConfigsRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x12\n\npage_token\x18\x02 \x01(\t\x12\x11\n\tpage_size\x18\x03 \x01(\x05\"c\n\x1aListServiceConfigsResponse\x12,\n\x0fservice_configs\x18\x01 \x03(\x0b\x32\x13.google.api.Service\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"i\n\x1a\x43reateServiceConfigRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x30\n\x0eservice_config\x18\x02 \x01(\x0b\x32\x13.google.api.ServiceB\x03\xe0\x41\x02\"\x9d\x01\n\x19SubmitConfigSourceRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12I\n\rconfig_source\x18\x02 \x01(\x0b\x32-.google.api.servicemanagement.v1.ConfigSourceB\x03\xe0\x41\x02\x12\x1a\n\rvalidate_only\x18\x03 \x01(\x08\x42\x03\xe0\x41\x01\"I\n\x1aSubmitConfigSourceResponse\x12+\n\x0eservice_config\x18\x01 \x01(\x0b\x32\x13.google.api.Service\"x\n\x1b\x43reateServiceRolloutRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12>\n\x07rollout\x18\x02 \x01(\x0b\x32(.google.api.servicemanagement.v1.RolloutB\x03\xe0\x41\x02\"s\n\x1aListServiceRolloutsRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x12\n\npage_token\x18\x02 \x01(\t\x12\x11\n\tpage_size\x18\x03 \x01(\x05\x12\x13\n\x06\x66ilter\x18\x04 \x01(\tB\x03\xe0\x41\x02\"r\n\x1bListServiceRolloutsResponse\x12:\n\x08rollouts\x18\x01 \x03(\x0b\x32(.google.api.servicemanagement.v1.Rollout\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"N\n\x18GetServiceRolloutRequest\x12\x19\n\x0cservice_name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x17\n\nrollout_id\x18\x02 \x01(\tB\x03\xe0\x41\x02\"\x17\n\x15\x45nableServiceResponse\"{\n\x1bGenerateConfigReportRequest\x12-\n\nnew_config\x18\x01 \x01(\x0b\x32\x14.google.protobuf.AnyB\x03\xe0\x41\x02\x12-\n\nold_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.AnyB\x03\xe0\x41\x01\"\xc9\x01\n\x1cGenerateConfigReportResponse\x12\x14\n\x0cservice_name\x18\x01 \x01(\t\x12\n\n\x02id\x18\x02 \x01(\t\x12\x45\n\x0e\x63hange_reports\x18\x03 \x03(\x0b\x32-.google.api.servicemanagement.v1.ChangeReport\x12@\n\x0b\x64iagnostics\x18\x04 \x03(\x0b\x32+.google.api.servicemanagement.v1.Diagnostic2\xc8\x19\n\x0eServiceManager\x12\xb3\x01\n\x0cListServices\x12\x34.google.api.servicemanagement.v1.ListServicesRequest\x1a\x35.google.api.servicemanagement.v1.ListServicesResponse\"6\xda\x41\x1fproducer_project_id,consumer_id\x82\xd3\xe4\x93\x02\x0e\x12\x0c/v1/services\x12\xa5\x01\n\nGetService\x12\x32.google.api.servicemanagement.v1.GetServiceRequest\x1a/.google.api.servicemanagement.v1.ManagedService\"2\xda\x41\x0cservice_name\x82\xd3\xe4\x93\x02\x1d\x12\x1b/v1/services/{service_name}\x12\xf5\x01\n\rCreateService\x12\x35.google.api.servicemanagement.v1.CreateServiceRequest\x1a\x1d.google.longrunning.Operation\"\x8d\x01\xca\x41\x63\n.google.api.servicemanagement.v1.ManagedService\x12\x31google.api.servicemanagement.v1.OperationMetadata\xda\x41\x07service\x82\xd3\xe4\x93\x02\x17\"\x0c/v1/services:\x07service\x12\xe6\x01\n\rDeleteService\x12\x35.google.api.servicemanagement.v1.DeleteServiceRequest\x1a\x1d.google.longrunning.Operation\"\x7f\xca\x41J\n\x15google.protobuf.Empty\x12\x31google.api.servicemanagement.v1.OperationMetadata\xda\x41\x0cservice_name\x82\xd3\xe4\x93\x02\x1d*\x1b/v1/services/{service_name}\x12\x96\x02\n\x0fUndeleteService\x12\x37.google.api.servicemanagement.v1.UndeleteServiceRequest\x1a\x1d.google.longrunning.Operation\"\xaa\x01\xca\x41l\n7google.api.servicemanagement.v1.UndeleteServiceResponse\x12\x31google.api.servicemanagement.v1.OperationMetadata\xda\x41\x0cservice_name\x82\xd3\xe4\x93\x02&\"$/v1/services/{service_name}:undelete\x12\xc9\x01\n\x12ListServiceConfigs\x12:.google.api.servicemanagement.v1.ListServiceConfigsRequest\x1a;.google.api.servicemanagement.v1.ListServiceConfigsResponse\":\xda\x41\x0cservice_name\x82\xd3\xe4\x93\x02%\x12#/v1/services/{service_name}/configs\x12\xde\x01\n\x10GetServiceConfig\x12\x38.google.api.servicemanagement.v1.GetServiceConfigRequest\x1a\x13.google.api.Service\"{\xda\x41\x1bservice_name,config_id,view\x82\xd3\xe4\x93\x02W\x12//v1/services/{service_name}/configs/{config_id}Z$\x12\"/v1/services/{service_name}/config\x12\xc2\x01\n\x13\x43reateServiceConfig\x12;.google.api.servicemanagement.v1.CreateServiceConfigRequest\x1a\x13.google.api.Service\"Y\xda\x41\x1bservice_name,service_config\x82\xd3\xe4\x93\x02\x35\"#/v1/services/{service_name}/configs:\x0eservice_config\x12\xc4\x02\n\x12SubmitConfigSource\x12:.google.api.servicemanagement.v1.SubmitConfigSourceRequest\x1a\x1d.google.longrunning.Operation\"\xd2\x01\xca\x41o\n:google.api.servicemanagement.v1.SubmitConfigSourceResponse\x12\x31google.api.servicemanagement.v1.OperationMetadata\xda\x41(service_name,config_source,validate_only\x82\xd3\xe4\x93\x02/\"*/v1/services/{service_name}/configs:submit:\x01*\x12\xd4\x01\n\x13ListServiceRollouts\x12;.google.api.servicemanagement.v1.ListServiceRolloutsRequest\x1a<.google.api.servicemanagement.v1.ListServiceRolloutsResponse\"B\xda\x41\x13service_name,filter\x82\xd3\xe4\x93\x02&\x12$/v1/services/{service_name}/rollouts\x12\xcd\x01\n\x11GetServiceRollout\x12\x39.google.api.servicemanagement.v1.GetServiceRolloutRequest\x1a(.google.api.servicemanagement.v1.Rollout\"S\xda\x41\x17service_name,rollout_id\x82\xd3\xe4\x93\x02\x33\x12\x31/v1/services/{service_name}/rollouts/{rollout_id}\x12\xa1\x02\n\x14\x43reateServiceRollout\x12<.google.api.servicemanagement.v1.CreateServiceRolloutRequest\x1a\x1d.google.longrunning.Operation\"\xab\x01\xca\x41\\\n\'google.api.servicemanagement.v1.Rollout\x12\x31google.api.servicemanagement.v1.OperationMetadata\xda\x41\x14service_name,rollout\x82\xd3\xe4\x93\x02/\"$/v1/services/{service_name}/rollouts:\x07rollout\x12\xd9\x01\n\x14GenerateConfigReport\x12<.google.api.servicemanagement.v1.GenerateConfigReportRequest\x1a=.google.api.servicemanagement.v1.GenerateConfigReportResponse\"D\xda\x41\x15new_config,old_config\x82\xd3\xe4\x93\x02&\"!/v1/services:generateConfigReport:\x01*\x1a\xfd\x01\xca\x41 servicemanagement.googleapis.com\xd2\x41\xd6\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.management,https://www.googleapis.com/auth/service.management.readonlyB\x87\x02\n#com.google.api.servicemanagement.v1B\x13ServiceManagerProtoP\x01ZScloud.google.com/go/servicemanagement/apiv1/servicemanagementpb;servicemanagementpb\xa2\x02\x04GASM\xaa\x02!Google.Cloud.ServiceManagement.V1\xca\x02!Google\\Cloud\\ServiceManagement\\V1\xea\x02$Google::Cloud::ServiceManagement::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicemanagement.v1.servicemanager_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#com.google.api.servicemanagement.v1B\023ServiceManagerProtoP\001ZScloud.google.com/go/servicemanagement/apiv1/servicemanagementpb;servicemanagementpb\242\002\004GASM\252\002!Google.Cloud.ServiceManagement.V1\312\002!Google\\Cloud\\ServiceManagement\\V1\352\002$Google::Cloud::ServiceManagement::V1'
  _LISTSERVICESREQUEST.fields_by_name['consumer_id']._options = None
  _LISTSERVICESREQUEST.fields_by_name['consumer_id']._serialized_options = b'\030\001'
  _GETSERVICEREQUEST.fields_by_name['service_name']._options = None
  _GETSERVICEREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _CREATESERVICEREQUEST.fields_by_name['service']._options = None
  _CREATESERVICEREQUEST.fields_by_name['service']._serialized_options = b'\340A\002'
  _DELETESERVICEREQUEST.fields_by_name['service_name']._options = None
  _DELETESERVICEREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _UNDELETESERVICEREQUEST.fields_by_name['service_name']._options = None
  _UNDELETESERVICEREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _GETSERVICECONFIGREQUEST.fields_by_name['service_name']._options = None
  _GETSERVICECONFIGREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _GETSERVICECONFIGREQUEST.fields_by_name['config_id']._options = None
  _GETSERVICECONFIGREQUEST.fields_by_name['config_id']._serialized_options = b'\340A\002'
  _LISTSERVICECONFIGSREQUEST.fields_by_name['service_name']._options = None
  _LISTSERVICECONFIGSREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _CREATESERVICECONFIGREQUEST.fields_by_name['service_name']._options = None
  _CREATESERVICECONFIGREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _CREATESERVICECONFIGREQUEST.fields_by_name['service_config']._options = None
  _CREATESERVICECONFIGREQUEST.fields_by_name['service_config']._serialized_options = b'\340A\002'
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['service_name']._options = None
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['config_source']._options = None
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['config_source']._serialized_options = b'\340A\002'
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['validate_only']._options = None
  _SUBMITCONFIGSOURCEREQUEST.fields_by_name['validate_only']._serialized_options = b'\340A\001'
  _CREATESERVICEROLLOUTREQUEST.fields_by_name['service_name']._options = None
  _CREATESERVICEROLLOUTREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _CREATESERVICEROLLOUTREQUEST.fields_by_name['rollout']._options = None
  _CREATESERVICEROLLOUTREQUEST.fields_by_name['rollout']._serialized_options = b'\340A\002'
  _LISTSERVICEROLLOUTSREQUEST.fields_by_name['service_name']._options = None
  _LISTSERVICEROLLOUTSREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _LISTSERVICEROLLOUTSREQUEST.fields_by_name['filter']._options = None
  _LISTSERVICEROLLOUTSREQUEST.fields_by_name['filter']._serialized_options = b'\340A\002'
  _GETSERVICEROLLOUTREQUEST.fields_by_name['service_name']._options = None
  _GETSERVICEROLLOUTREQUEST.fields_by_name['service_name']._serialized_options = b'\340A\002'
  _GETSERVICEROLLOUTREQUEST.fields_by_name['rollout_id']._options = None
  _GETSERVICEROLLOUTREQUEST.fields_by_name['rollout_id']._serialized_options = b'\340A\002'
  _GENERATECONFIGREPORTREQUEST.fields_by_name['new_config']._options = None
  _GENERATECONFIGREPORTREQUEST.fields_by_name['new_config']._serialized_options = b'\340A\002'
  _GENERATECONFIGREPORTREQUEST.fields_by_name['old_config']._options = None
  _GENERATECONFIGREPORTREQUEST.fields_by_name['old_config']._serialized_options = b'\340A\001'
  _SERVICEMANAGER._options = None
  _SERVICEMANAGER._serialized_options = b'\312A servicemanagement.googleapis.com\322A\326\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/service.management,https://www.googleapis.com/auth/service.management.readonly'
  _SERVICEMANAGER.methods_by_name['ListServices']._options = None
  _SERVICEMANAGER.methods_by_name['ListServices']._serialized_options = b'\332A\037producer_project_id,consumer_id\202\323\344\223\002\016\022\014/v1/services'
  _SERVICEMANAGER.methods_by_name['GetService']._options = None
  _SERVICEMANAGER.methods_by_name['GetService']._serialized_options = b'\332A\014service_name\202\323\344\223\002\035\022\033/v1/services/{service_name}'
  _SERVICEMANAGER.methods_by_name['CreateService']._options = None
  _SERVICEMANAGER.methods_by_name['CreateService']._serialized_options = b'\312Ac\n.google.api.servicemanagement.v1.ManagedService\0221google.api.servicemanagement.v1.OperationMetadata\332A\007service\202\323\344\223\002\027\"\014/v1/services:\007service'
  _SERVICEMANAGER.methods_by_name['DeleteService']._options = None
  _SERVICEMANAGER.methods_by_name['DeleteService']._serialized_options = b'\312AJ\n\025google.protobuf.Empty\0221google.api.servicemanagement.v1.OperationMetadata\332A\014service_name\202\323\344\223\002\035*\033/v1/services/{service_name}'
  _SERVICEMANAGER.methods_by_name['UndeleteService']._options = None
  _SERVICEMANAGER.methods_by_name['UndeleteService']._serialized_options = b'\312Al\n7google.api.servicemanagement.v1.UndeleteServiceResponse\0221google.api.servicemanagement.v1.OperationMetadata\332A\014service_name\202\323\344\223\002&\"$/v1/services/{service_name}:undelete'
  _SERVICEMANAGER.methods_by_name['ListServiceConfigs']._options = None
  _SERVICEMANAGER.methods_by_name['ListServiceConfigs']._serialized_options = b'\332A\014service_name\202\323\344\223\002%\022#/v1/services/{service_name}/configs'
  _SERVICEMANAGER.methods_by_name['GetServiceConfig']._options = None
  _SERVICEMANAGER.methods_by_name['GetServiceConfig']._serialized_options = b'\332A\033service_name,config_id,view\202\323\344\223\002W\022//v1/services/{service_name}/configs/{config_id}Z$\022\"/v1/services/{service_name}/config'
  _SERVICEMANAGER.methods_by_name['CreateServiceConfig']._options = None
  _SERVICEMANAGER.methods_by_name['CreateServiceConfig']._serialized_options = b'\332A\033service_name,service_config\202\323\344\223\0025\"#/v1/services/{service_name}/configs:\016service_config'
  _SERVICEMANAGER.methods_by_name['SubmitConfigSource']._options = None
  _SERVICEMANAGER.methods_by_name['SubmitConfigSource']._serialized_options = b'\312Ao\n:google.api.servicemanagement.v1.SubmitConfigSourceResponse\0221google.api.servicemanagement.v1.OperationMetadata\332A(service_name,config_source,validate_only\202\323\344\223\002/\"*/v1/services/{service_name}/configs:submit:\001*'
  _SERVICEMANAGER.methods_by_name['ListServiceRollouts']._options = None
  _SERVICEMANAGER.methods_by_name['ListServiceRollouts']._serialized_options = b'\332A\023service_name,filter\202\323\344\223\002&\022$/v1/services/{service_name}/rollouts'
  _SERVICEMANAGER.methods_by_name['GetServiceRollout']._options = None
  _SERVICEMANAGER.methods_by_name['GetServiceRollout']._serialized_options = b'\332A\027service_name,rollout_id\202\323\344\223\0023\0221/v1/services/{service_name}/rollouts/{rollout_id}'
  _SERVICEMANAGER.methods_by_name['CreateServiceRollout']._options = None
  _SERVICEMANAGER.methods_by_name['CreateServiceRollout']._serialized_options = b'\312A\\\n\'google.api.servicemanagement.v1.Rollout\0221google.api.servicemanagement.v1.OperationMetadata\332A\024service_name,rollout\202\323\344\223\002/\"$/v1/services/{service_name}/rollouts:\007rollout'
  _SERVICEMANAGER.methods_by_name['GenerateConfigReport']._options = None
  _SERVICEMANAGER.methods_by_name['GenerateConfigReport']._serialized_options = b'\332A\025new_config,old_config\202\323\344\223\002&\"!/v1/services:generateConfigReport:\001*'
  _globals['_LISTSERVICESREQUEST']._serialized_start=345
  _globals['_LISTSERVICESREQUEST']._serialized_end=459
  _globals['_LISTSERVICESRESPONSE']._serialized_start=461
  _globals['_LISTSERVICESRESPONSE']._serialized_end=575
  _globals['_GETSERVICEREQUEST']._serialized_start=577
  _globals['_GETSERVICEREQUEST']._serialized_end=623
  _globals['_CREATESERVICEREQUEST']._serialized_start=625
  _globals['_CREATESERVICEREQUEST']._serialized_end=718
  _globals['_DELETESERVICEREQUEST']._serialized_start=720
  _globals['_DELETESERVICEREQUEST']._serialized_end=769
  _globals['_UNDELETESERVICEREQUEST']._serialized_start=771
  _globals['_UNDELETESERVICEREQUEST']._serialized_end=822
  _globals['_UNDELETESERVICERESPONSE']._serialized_start=824
  _globals['_UNDELETESERVICERESPONSE']._serialized_end=915
  _globals['_GETSERVICECONFIGREQUEST']._serialized_start=918
  _globals['_GETSERVICECONFIGREQUEST']._serialized_end=1112
  _globals['_GETSERVICECONFIGREQUEST_CONFIGVIEW']._serialized_start=1079
  _globals['_GETSERVICECONFIGREQUEST_CONFIGVIEW']._serialized_end=1112
  _globals['_LISTSERVICECONFIGSREQUEST']._serialized_start=1114
  _globals['_LISTSERVICECONFIGSREQUEST']._serialized_end=1207
  _globals['_LISTSERVICECONFIGSRESPONSE']._serialized_start=1209
  _globals['_LISTSERVICECONFIGSRESPONSE']._serialized_end=1308
  _globals['_CREATESERVICECONFIGREQUEST']._serialized_start=1310
  _globals['_CREATESERVICECONFIGREQUEST']._serialized_end=1415
  _globals['_SUBMITCONFIGSOURCEREQUEST']._serialized_start=1418
  _globals['_SUBMITCONFIGSOURCEREQUEST']._serialized_end=1575
  _globals['_SUBMITCONFIGSOURCERESPONSE']._serialized_start=1577
  _globals['_SUBMITCONFIGSOURCERESPONSE']._serialized_end=1650
  _globals['_CREATESERVICEROLLOUTREQUEST']._serialized_start=1652
  _globals['_CREATESERVICEROLLOUTREQUEST']._serialized_end=1772
  _globals['_LISTSERVICEROLLOUTSREQUEST']._serialized_start=1774
  _globals['_LISTSERVICEROLLOUTSREQUEST']._serialized_end=1889
  _globals['_LISTSERVICEROLLOUTSRESPONSE']._serialized_start=1891
  _globals['_LISTSERVICEROLLOUTSRESPONSE']._serialized_end=2005
  _globals['_GETSERVICEROLLOUTREQUEST']._serialized_start=2007
  _globals['_GETSERVICEROLLOUTREQUEST']._serialized_end=2085
  _globals['_ENABLESERVICERESPONSE']._serialized_start=2087
  _globals['_ENABLESERVICERESPONSE']._serialized_end=2110
  _globals['_GENERATECONFIGREPORTREQUEST']._serialized_start=2112
  _globals['_GENERATECONFIGREPORTREQUEST']._serialized_end=2235
  _globals['_GENERATECONFIGREPORTRESPONSE']._serialized_start=2238
  _globals['_GENERATECONFIGREPORTRESPONSE']._serialized_end=2439
  _globals['_SERVICEMANAGER']._serialized_start=2442
  _globals['_SERVICEMANAGER']._serialized_end=5714
