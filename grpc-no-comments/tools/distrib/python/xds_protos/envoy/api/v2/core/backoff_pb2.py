
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/api/v2/core/backoff.proto\x12\x11\x65nvoy.api.v2.core\x1a\x1egoogle/protobuf/duration.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x8e\x01\n\x0f\x42\x61\x63koffStrategy\x12@\n\rbase_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0e\xfa\x42\x0b\xaa\x01\x08\x08\x01\x32\x04\x10\xc0\x84=\x12\x39\n\x0cmax_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x42\x8f\x01\n\x1fio.envoyproxy.envoy.api.v2.coreB\x0c\x42\x61\x63koffProtoP\x01Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/core\xf2\x98\xfe\x8f\x05\x16\x12\x14\x65nvoy.config.core.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.core.backoff_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\037io.envoyproxy.envoy.api.v2.coreB\014BackoffProtoP\001Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/core\362\230\376\217\005\026\022\024envoy.config.core.v3\272\200\310\321\006\002\020\001'
  _BACKOFFSTRATEGY.fields_by_name['base_interval']._options = None
  _BACKOFFSTRATEGY.fields_by_name['base_interval']._serialized_options = b'\372B\013\252\001\010\010\0012\004\020\300\204='
  _BACKOFFSTRATEGY.fields_by_name['max_interval']._options = None
  _BACKOFFSTRATEGY.fields_by_name['max_interval']._serialized_options = b'\372B\005\252\001\002*\000'
  _globals['_BACKOFFSTRATEGY']._serialized_start=175
  _globals['_BACKOFFSTRATEGY']._serialized_end=317
