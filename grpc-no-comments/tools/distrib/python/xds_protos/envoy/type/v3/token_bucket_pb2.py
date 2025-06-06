
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n envoy/type/v3/token_bucket.proto\x12\renvoy.type.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xc7\x01\n\x0bTokenBucket\x12\x1b\n\nmax_tokens\x18\x01 \x01(\rB\x07\xfa\x42\x04*\x02 \x00\x12>\n\x0ftokens_per_fill\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02 \x00\x12<\n\rfill_interval\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\n\xfa\x42\x07\xaa\x01\x04\x08\x01*\x00:\x1d\x9a\xc5\x88\x1e\x18\n\x16\x65nvoy.type.TokenBucketBv\n\x1bio.envoyproxy.envoy.type.v3B\x10TokenBucketProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.v3.token_bucket_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033io.envoyproxy.envoy.type.v3B\020TokenBucketProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\272\200\310\321\006\002\020\002'
  _TOKENBUCKET.fields_by_name['max_tokens']._options = None
  _TOKENBUCKET.fields_by_name['max_tokens']._serialized_options = b'\372B\004*\002 \000'
  _TOKENBUCKET.fields_by_name['tokens_per_fill']._options = None
  _TOKENBUCKET.fields_by_name['tokens_per_fill']._serialized_options = b'\372B\004*\002 \000'
  _TOKENBUCKET.fields_by_name['fill_interval']._options = None
  _TOKENBUCKET.fields_by_name['fill_interval']._serialized_options = b'\372B\007\252\001\004\010\001*\000'
  _TOKENBUCKET._options = None
  _TOKENBUCKET._serialized_options = b'\232\305\210\036\030\n\026envoy.type.TokenBucket'
  _globals['_TOKENBUCKET']._serialized_start=207
  _globals['_TOKENBUCKET']._serialized_end=406
