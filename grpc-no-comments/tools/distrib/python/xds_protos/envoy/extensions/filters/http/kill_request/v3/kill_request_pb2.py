
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import percent_pb2 as envoy_dot_type_dot_v3_dot_percent__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@envoy/extensions/filters/http/kill_request/v3/kill_request.proto\x12-envoy.extensions.filters.http.kill_request.v3\x1a\x1b\x65nvoy/type/v3/percent.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xf9\x01\n\x0bKillRequest\x12\x35\n\x0bprobability\x18\x01 \x01(\x0b\x32 .envoy.type.v3.FractionalPercent\x12(\n\x13kill_request_header\x18\x02 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12\x61\n\tdirection\x18\x03 \x01(\x0e\x32\x44.envoy.extensions.filters.http.kill_request.v3.KillRequest.DirectionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"&\n\tDirection\x12\x0b\n\x07REQUEST\x10\x00\x12\x0c\n\x08RESPONSE\x10\x01\x42\xbe\x01\n;io.envoyproxy.envoy.extensions.filters.http.kill_request.v3B\x10KillRequestProtoP\x01Zcgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/kill_request/v3;kill_requestv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.kill_request.v3.kill_request_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n;io.envoyproxy.envoy.extensions.filters.http.kill_request.v3B\020KillRequestProtoP\001Zcgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/kill_request/v3;kill_requestv3\272\200\310\321\006\002\020\002'
  _KILLREQUEST.fields_by_name['kill_request_header']._options = None
  _KILLREQUEST.fields_by_name['kill_request_header']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _KILLREQUEST.fields_by_name['direction']._options = None
  _KILLREQUEST.fields_by_name['direction']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_KILLREQUEST']._serialized_start=201
  _globals['_KILLREQUEST']._serialized_end=450
  _globals['_KILLREQUEST_DIRECTION']._serialized_start=412
  _globals['_KILLREQUEST_DIRECTION']._serialized_end=450
