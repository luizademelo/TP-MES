
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nMenvoy/extensions/quic/connection_debug_visitor/quic_stats/v3/quic_stats.proto\x12<envoy.extensions.quic.connection_debug_visitor.quic_stats.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"H\n\x06\x43onfig\x12>\n\rupdate_period\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0c\xfa\x42\t\xaa\x01\x06\x32\x04\x10\xc0\x84=B\xd8\x01\nJio.envoyproxy.envoy.extensions.quic.connection_debug_visitor.quic_stats.v3B\x0eQuicStatsProtoP\x01Zpgithub.com/envoyproxy/go-control-plane/envoy/extensions/quic/connection_debug_visitor/quic_stats/v3;quic_statsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.quic.connection_debug_visitor.quic_stats.v3.quic_stats_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nJio.envoyproxy.envoy.extensions.quic.connection_debug_visitor.quic_stats.v3B\016QuicStatsProtoP\001Zpgithub.com/envoyproxy/go-control-plane/envoy/extensions/quic/connection_debug_visitor/quic_stats/v3;quic_statsv3\272\200\310\321\006\002\020\002'
  _CONFIG.fields_by_name['update_period']._options = None
  _CONFIG.fields_by_name['update_period']._serialized_options = b'\372B\t\252\001\0062\004\020\300\204='
  _globals['_CONFIG']._serialized_start=231
  _globals['_CONFIG']._serialized_end=303
