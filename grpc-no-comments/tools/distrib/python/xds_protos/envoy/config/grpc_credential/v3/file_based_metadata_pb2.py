
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import sensitive_pb2 as udpa_dot_annotations_dot_sensitive__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9envoy/config/grpc_credential/v3/file_based_metadata.proto\x12\x1f\x65nvoy.config.grpc_credential.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a udpa/annotations/sensitive.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xc8\x01\n\x17\x46ileBasedMetadataConfig\x12=\n\x0bsecret_data\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceB\x06\xb8\xb7\x8b\xa4\x02\x01\x12\x12\n\nheader_key\x18\x02 \x01(\t\x12\x15\n\rheader_prefix\x18\x03 \x01(\t:C\x9a\xc5\x88\x1e>\n<envoy.config.grpc_credential.v2alpha.FileBasedMetadataConfigB\xab\x01\n-io.envoyproxy.envoy.config.grpc_credential.v3B\x16\x46ileBasedMetadataProtoP\x01ZXgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v3;grpc_credentialv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.grpc_credential.v3.file_based_metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n-io.envoyproxy.envoy.config.grpc_credential.v3B\026FileBasedMetadataProtoP\001ZXgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v3;grpc_credentialv3\272\200\310\321\006\002\020\002'
  _FILEBASEDMETADATACONFIG.fields_by_name['secret_data']._options = None
  _FILEBASEDMETADATACONFIG.fields_by_name['secret_data']._serialized_options = b'\270\267\213\244\002\001'
  _FILEBASEDMETADATACONFIG._options = None
  _FILEBASEDMETADATACONFIG._serialized_options = b'\232\305\210\036>\n<envoy.config.grpc_credential.v2alpha.FileBasedMetadataConfig'
  _globals['_FILEBASEDMETADATACONFIG']._serialized_start=228
  _globals['_FILEBASEDMETADATACONFIG']._serialized_end=428
