
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@envoy/extensions/watchdog/profile_action/v3/profile_action.proto\x12+envoy.extensions.watchdog.profile_action.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x7f\n\x13ProfileActionConfig\x12\x33\n\x10profile_duration\x18\x01 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x1d\n\x0cprofile_path\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x14\n\x0cmax_profiles\x18\x03 \x01(\x04\x42\xbe\x01\n9io.envoyproxy.envoy.extensions.watchdog.profile_action.v3B\x12ProfileActionProtoP\x01Zcgithub.com/envoyproxy/go-control-plane/envoy/extensions/watchdog/profile_action/v3;profile_actionv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.watchdog.profile_action.v3.profile_action_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.extensions.watchdog.profile_action.v3B\022ProfileActionProtoP\001Zcgithub.com/envoyproxy/go-control-plane/envoy/extensions/watchdog/profile_action/v3;profile_actionv3\272\200\310\321\006\002\020\002'
  _PROFILEACTIONCONFIG.fields_by_name['profile_path']._options = None
  _PROFILEACTIONCONFIG.fields_by_name['profile_path']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_PROFILEACTIONCONFIG']._serialized_start=201
  _globals['_PROFILEACTIONCONFIG']._serialized_end=328
