
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
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.api import usage_pb2 as google_dot_api_dot_usage__pb2
from google.protobuf import api_pb2 as google_dot_protobuf_dot_api__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*google/api/serviceusage/v1/resources.proto\x12\x1agoogle.api.serviceusage.v1\x1a\x15google/api/auth.proto\x1a\x1egoogle/api/documentation.proto\x1a\x19google/api/endpoint.proto\x1a#google/api/monitored_resource.proto\x1a\x1bgoogle/api/monitoring.proto\x1a\x16google/api/quota.proto\x1a\x19google/api/resource.proto\x1a\x16google/api/usage.proto\x1a\x19google/protobuf/api.proto\"\xbd\x02\n\x07Service\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0e\n\x06parent\x18\x05 \x01(\t\x12\x39\n\x06\x63onfig\x18\x02 \x01(\x0b\x32).google.api.serviceusage.v1.ServiceConfig\x12\x30\n\x05state\x18\x04 \x01(\x0e\x32!.google.api.serviceusage.v1.State:\xa6\x01\xea\x41\xa2\x01\n#serviceusage.googleapis.com/Service\x12%projects/{project}/services/{service}\x12#folders/{folder}/services/{service}\x12/organizations/{organization}/services/{service}\"\x95\x03\n\rServiceConfig\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05title\x18\x02 \x01(\t\x12\"\n\x04\x61pis\x18\x03 \x03(\x0b\x32\x14.google.protobuf.Api\x12\x30\n\rdocumentation\x18\x06 \x01(\x0b\x32\x19.google.api.Documentation\x12 \n\x05quota\x18\n \x01(\x0b\x32\x11.google.api.Quota\x12\x32\n\x0e\x61uthentication\x18\x0b \x01(\x0b\x32\x1a.google.api.Authentication\x12 \n\x05usage\x18\x0f \x01(\x0b\x32\x11.google.api.Usage\x12\'\n\tendpoints\x18\x12 \x03(\x0b\x32\x14.google.api.Endpoint\x12\x44\n\x13monitored_resources\x18\x19 \x03(\x0b\x32\'.google.api.MonitoredResourceDescriptor\x12*\n\nmonitoring\x18\x1c \x01(\x0b\x32\x16.google.api.Monitoring\"+\n\x11OperationMetadata\x12\x16\n\x0eresource_names\x18\x02 \x03(\t*9\n\x05State\x12\x15\n\x11STATE_UNSPECIFIED\x10\x00\x12\x0c\n\x08\x44ISABLED\x10\x01\x12\x0b\n\x07\x45NABLED\x10\x02\x42\xd8\x01\n\x1e\x63om.google.api.serviceusage.v1B\x0eResourcesProtoP\x01ZDcloud.google.com/go/serviceusage/apiv1/serviceusagepb;serviceusagepb\xaa\x02\x1cGoogle.Cloud.ServiceUsage.V1\xca\x02\x1cGoogle\\Cloud\\ServiceUsage\\V1\xea\x02\x1fGoogle::Cloud::ServiceUsage::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.serviceusage.v1.resources_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.google.api.serviceusage.v1B\016ResourcesProtoP\001ZDcloud.google.com/go/serviceusage/apiv1/serviceusagepb;serviceusagepb\252\002\034Google.Cloud.ServiceUsage.V1\312\002\034Google\\Cloud\\ServiceUsage\\V1\352\002\037Google::Cloud::ServiceUsage::V1'
  _SERVICE._options = None
  _SERVICE._serialized_options = b'\352A\242\001\n#serviceusage.googleapis.com/Service\022%projects/{project}/services/{service}\022#folders/{folder}/services/{service}\022/organizations/{organization}/services/{service}'
  _globals['_STATE']._serialized_start=1097
  _globals['_STATE']._serialized_end=1154
  _globals['_SERVICE']._serialized_start=325
  _globals['_SERVICE']._serialized_end=642
  _globals['_SERVICECONFIG']._serialized_start=645
  _globals['_SERVICECONFIG']._serialized_end=1050
  _globals['_OPERATIONMETADATA']._serialized_start=1052
  _globals['_OPERATIONMETADATA']._serialized_end=1095
