
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from udpa.annotations import sensitive_pb2 as udpa_dot_annotations_dot_sensitive__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n>envoy/config/grpc_credential/v2alpha/file_based_metadata.proto\x12$envoy.config.grpc_credential.v2alpha\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a udpa/annotations/sensitive.proto\x1a\x1dudpa/annotations/status.proto\"\x80\x01\n\x17\x46ileBasedMetadataConfig\x12:\n\x0bsecret_data\x18\x01 \x01(\x0b\x32\x1d.envoy.api.v2.core.DataSourceB\x06\xb8\xb7\x8b\xa4\x02\x01\x12\x12\n\nheader_key\x18\x02 \x01(\t\x12\x15\n\rheader_prefix\x18\x03 \x01(\tB\xa3\x01\n2io.envoyproxy.envoy.config.grpc_credential.v2alphaB\x16\x46ileBasedMetadataProtoP\x01ZKgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.grpc_credential.v2alpha.file_based_metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n2io.envoyproxy.envoy.config.grpc_credential.v2alphaB\026FileBasedMetadataProtoP\001ZKgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v2alpha\272\200\310\321\006\002\020\001'
  _FILEBASEDMETADATACONFIG.fields_by_name['secret_data']._options = None
  _FILEBASEDMETADATACONFIG.fields_by_name['secret_data']._serialized_options = b'\270\267\213\244\002\001'
  _globals['_FILEBASEDMETADATACONFIG']._serialized_start=200
  _globals['_FILEBASEDMETADATACONFIG']._serialized_end=328
