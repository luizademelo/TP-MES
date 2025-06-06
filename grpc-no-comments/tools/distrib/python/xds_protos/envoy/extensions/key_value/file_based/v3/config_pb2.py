
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/extensions/key_value/file_based/v3/config.proto\x12(envoy.extensions.key_value.file_based.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa9\x01\n\x1c\x46ileBasedKeyValueStoreConfig\x12\x19\n\x08\x66ilename\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x31\n\x0e\x66lush_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x31\n\x0bmax_entries\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value:\x08\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x42\xad\x01\n6io.envoyproxy.envoy.extensions.key_value.file_based.v3B\x0b\x43onfigProtoP\x01Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/key_value/file_based/v3;file_basedv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.key_value.file_based.v3.config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n6io.envoyproxy.envoy.extensions.key_value.file_based.v3B\013ConfigProtoP\001Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/key_value/file_based/v3;file_basedv3\272\200\310\321\006\002\020\002'
  _FILEBASEDKEYVALUESTORECONFIG.fields_by_name['filename']._options = None
  _FILEBASEDKEYVALUESTORECONFIG.fields_by_name['filename']._serialized_options = b'\372B\004r\002\020\001'
  _FILEBASEDKEYVALUESTORECONFIG._options = None
  _FILEBASEDKEYVALUESTORECONFIG._serialized_options = b'\322\306\244\341\006\002\010\001'
  _globals['_FILEBASEDKEYVALUESTORECONFIG']._serialized_start=253
  _globals['_FILEBASEDKEYVALUESTORECONFIG']._serialized_end=422
