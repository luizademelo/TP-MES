
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/watchdog/v3/abort_action.proto\x12\x11\x65nvoy.watchdog.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\"E\n\x11\x41\x62ortActionConfig\x12\x30\n\rwait_duration\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x82\x01\n\x1fio.envoyproxy.envoy.watchdog.v3B\x10\x41\x62ortActionProtoP\x01ZCgithub.com/envoyproxy/go-control-plane/envoy/watchdog/v3;watchdogv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.watchdog.v3.abort_action_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\037io.envoyproxy.envoy.watchdog.v3B\020AbortActionProtoP\001ZCgithub.com/envoyproxy/go-control-plane/envoy/watchdog/v3;watchdogv3\272\200\310\321\006\002\020\002'
  _globals['_ABORTACTIONCONFIG']._serialized_start=122
  _globals['_ABORTACTIONCONFIG']._serialized_end=191
