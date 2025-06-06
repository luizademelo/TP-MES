
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/envoy/config/filter/http/squash/v2/squash.proto\x12\"envoy.config.filter.http.squash.v2\x1a\x1egoogle/protobuf/duration.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xfe\x01\n\x06Squash\x12\x18\n\x07\x63luster\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x34\n\x13\x61ttachment_template\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct\x12\x32\n\x0frequest_timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x35\n\x12\x61ttachment_timeout\x18\x04 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x39\n\x16\x61ttachment_poll_period\x18\x05 \x01(\x0b\x32\x19.google.protobuf.DurationB\xcc\x01\n0io.envoyproxy.envoy.config.filter.http.squash.v2B\x0bSquashProtoP\x01ZRgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/squash/v2;squashv2\xf2\x98\xfe\x8f\x05)\x12\'envoy.extensions.filters.http.squash.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.squash.v2.squash_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n0io.envoyproxy.envoy.config.filter.http.squash.v2B\013SquashProtoP\001ZRgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/squash/v2;squashv2\362\230\376\217\005)\022\'envoy.extensions.filters.http.squash.v3\272\200\310\321\006\002\020\001'
  _SQUASH.fields_by_name['cluster']._options = None
  _SQUASH.fields_by_name['cluster']._serialized_options = b'\372B\004r\002 \001'
  _globals['_SQUASH']._serialized_start=238
  _globals['_SQUASH']._serialized_end=492
