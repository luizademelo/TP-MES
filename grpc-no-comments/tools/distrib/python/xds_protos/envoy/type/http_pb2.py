
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x15\x65nvoy/type/http.proto\x12\nenvoy.type\x1a\x1dudpa/annotations/status.proto*2\n\x0f\x43odecClientType\x12\t\n\x05HTTP1\x10\x00\x12\t\n\x05HTTP2\x10\x01\x12\t\n\x05HTTP3\x10\x02\x42\x62\n\x18io.envoyproxy.envoy.typeB\tHttpProtoP\x01Z1github.com/envoyproxy/go-control-plane/envoy/type\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.http_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\030io.envoyproxy.envoy.typeB\tHttpProtoP\001Z1github.com/envoyproxy/go-control-plane/envoy/type\272\200\310\321\006\002\020\001'
  _globals['_CODECCLIENTTYPE']._serialized_start=68
  _globals['_CODECCLIENTTYPE']._serialized_end=118
