
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"envoy/config/core/v3/backoff.proto\x12\x14\x65nvoy.config.core.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xb8\x01\n\x0f\x42\x61\x63koffStrategy\x12@\n\rbase_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0e\xfa\x42\x0b\xaa\x01\x08\x08\x01\x32\x04\x10\xc0\x84=\x12\x39\n\x0cmax_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00:(\x9a\xc5\x88\x1e#\n!envoy.api.v2.core.BackoffStrategyB\x80\x01\n\"io.envoyproxy.envoy.config.core.v3B\x0c\x42\x61\x63koffProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.backoff_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\014BackoffProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
  _BACKOFFSTRATEGY.fields_by_name['base_interval']._options = None
  _BACKOFFSTRATEGY.fields_by_name['base_interval']._serialized_options = b'\372B\013\252\001\010\010\0012\004\020\300\204='
  _BACKOFFSTRATEGY.fields_by_name['max_interval']._options = None
  _BACKOFFSTRATEGY.fields_by_name['max_interval']._serialized_options = b'\372B\005\252\001\002*\000'
  _BACKOFFSTRATEGY._options = None
  _BACKOFFSTRATEGY._serialized_options = b'\232\305\210\036#\n!envoy.api.v2.core.BackoffStrategy'
  _globals['_BACKOFFSTRATEGY']._serialized_start=184
  _globals['_BACKOFFSTRATEGY']._serialized_end=368
