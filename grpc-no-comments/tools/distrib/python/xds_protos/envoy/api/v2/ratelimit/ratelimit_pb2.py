
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/api/v2/ratelimit/ratelimit.proto\x12\x16\x65nvoy.api.v2.ratelimit\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x9a\x01\n\x13RateLimitDescriptor\x12L\n\x07\x65ntries\x18\x01 \x03(\x0b\x32\x31.envoy.api.v2.ratelimit.RateLimitDescriptor.EntryB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\x35\n\x05\x45ntry\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x16\n\x05value\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x42\xab\x01\n$io.envoyproxy.envoy.api.v2.ratelimitB\x0eRatelimitProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/api/v2/ratelimit\xf2\x98\xfe\x8f\x05&\x12$envoy.extensions.common.ratelimit.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.ratelimit.ratelimit_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.api.v2.ratelimitB\016RatelimitProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/api/v2/ratelimit\362\230\376\217\005&\022$envoy.extensions.common.ratelimit.v3\272\200\310\321\006\002\020\001'
  _RATELIMITDESCRIPTOR_ENTRY.fields_by_name['key']._options = None
  _RATELIMITDESCRIPTOR_ENTRY.fields_by_name['key']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMITDESCRIPTOR_ENTRY.fields_by_name['value']._options = None
  _RATELIMITDESCRIPTOR_ENTRY.fields_by_name['value']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMITDESCRIPTOR.fields_by_name['entries']._options = None
  _RATELIMITDESCRIPTOR.fields_by_name['entries']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_RATELIMITDESCRIPTOR']._serialized_start=155
  _globals['_RATELIMITDESCRIPTOR']._serialized_end=309
  _globals['_RATELIMITDESCRIPTOR_ENTRY']._serialized_start=256
  _globals['_RATELIMITDESCRIPTOR_ENTRY']._serialized_end=309
