
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n8envoy/extensions/filters/http/cdn_loop/v3/cdn_loop.proto\x12)envoy.extensions.filters.http.cdn_loop.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"I\n\rCdnLoopConfig\x12\x17\n\x06\x63\x64n_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x1f\n\x17max_allowed_occurrences\x18\x02 \x01(\rB\xae\x01\n7io.envoyproxy.envoy.extensions.filters.http.cdn_loop.v3B\x0c\x43\x64nLoopProtoP\x01Z[github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/cdn_loop/v3;cdn_loopv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.cdn_loop.v3.cdn_loop_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.filters.http.cdn_loop.v3B\014CdnLoopProtoP\001Z[github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/cdn_loop/v3;cdn_loopv3\272\200\310\321\006\002\020\002'
  _CDNLOOPCONFIG.fields_by_name['cdn_id']._options = None
  _CDNLOOPCONFIG.fields_by_name['cdn_id']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_CDNLOOPCONFIG']._serialized_start=159
  _globals['_CDNLOOPCONFIG']._serialized_end=232
