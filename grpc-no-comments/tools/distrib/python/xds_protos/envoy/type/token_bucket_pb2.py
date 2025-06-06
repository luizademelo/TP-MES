
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1d\x65nvoy/type/token_bucket.proto\x12\nenvoy.type\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa8\x01\n\x0bTokenBucket\x12\x1b\n\nmax_tokens\x18\x01 \x01(\rB\x07\xfa\x42\x04*\x02 \x00\x12>\n\x0ftokens_per_fill\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02 \x00\x12<\n\rfill_interval\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\n\xfa\x42\x07\xaa\x01\x04\x08\x01*\x00\x42i\n\x18io.envoyproxy.envoy.typeB\x10TokenBucketProtoP\x01Z1github.com/envoyproxy/go-control-plane/envoy/type\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.token_bucket_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\030io.envoyproxy.envoy.typeB\020TokenBucketProtoP\001Z1github.com/envoyproxy/go-control-plane/envoy/type\272\200\310\321\006\002\020\001'
  _TOKENBUCKET.fields_by_name['max_tokens']._options = None
  _TOKENBUCKET.fields_by_name['max_tokens']._serialized_options = b'\372B\004*\002 \000'
  _TOKENBUCKET.fields_by_name['tokens_per_fill']._options = None
  _TOKENBUCKET.fields_by_name['tokens_per_fill']._serialized_options = b'\372B\004*\002 \000'
  _TOKENBUCKET.fields_by_name['fill_interval']._options = None
  _TOKENBUCKET.fields_by_name['fill_interval']._serialized_options = b'\372B\007\252\001\004\010\001*\000'
  _globals['_TOKENBUCKET']._serialized_start=166
  _globals['_TOKENBUCKET']._serialized_end=334
