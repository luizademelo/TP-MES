
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/type/v3/semantic_version.proto\x12\renvoy.type.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"o\n\x0fSemanticVersion\x12\x14\n\x0cmajor_number\x18\x01 \x01(\r\x12\x14\n\x0cminor_number\x18\x02 \x01(\r\x12\r\n\x05patch\x18\x03 \x01(\r:!\x9a\xc5\x88\x1e\x1c\n\x1a\x65nvoy.type.SemanticVersionBz\n\x1bio.envoyproxy.envoy.type.v3B\x14SemanticVersionProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.v3.semantic_version_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033io.envoyproxy.envoy.type.v3B\024SemanticVersionProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\272\200\310\321\006\002\020\002'
  _SEMANTICVERSION._options = None
  _SEMANTICVERSION._serialized_options = b'\232\305\210\036\034\n\032envoy.type.SemanticVersion'
  _globals['_SEMANTICVERSION']._serialized_start=121
  _globals['_SEMANTICVERSION']._serialized_end=232
