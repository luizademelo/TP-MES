
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

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9envoy/config/filter/udp/udp_proxy/v2alpha/udp_proxy.proto\x12)envoy.config.filter.udp.udp_proxy.v2alpha\x1a\x1egoogle/protobuf/duration.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x93\x01\n\x0eUdpProxyConfig\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x1a\n\x07\x63luster\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01H\x00\x12/\n\x0cidle_timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\x16\n\x0froute_specifier\x12\x03\xf8\x42\x01\x42\xd5\x01\n7io.envoyproxy.envoy.config.filter.udp.udp_proxy.v2alphaB\rUdpProxyProtoP\x01ZPgithub.com/envoyproxy/go-control-plane/envoy/config/filter/udp/udp_proxy/v2alpha\xf2\x98\xfe\x8f\x05+\x12)envoy.extensions.filters.udp.udp_proxy.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.udp.udp_proxy.v2alpha.udp_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.config.filter.udp.udp_proxy.v2alphaB\rUdpProxyProtoP\001ZPgithub.com/envoyproxy/go-control-plane/envoy/config/filter/udp/udp_proxy/v2alpha\362\230\376\217\005+\022)envoy.extensions.filters.udp.udp_proxy.v3\272\200\310\321\006\002\020\001'
  _UDPPROXYCONFIG.oneofs_by_name['route_specifier']._options = None
  _UDPPROXYCONFIG.oneofs_by_name['route_specifier']._serialized_options = b'\370B\001'
  _UDPPROXYCONFIG.fields_by_name['stat_prefix']._options = None
  _UDPPROXYCONFIG.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002 \001'
  _UDPPROXYCONFIG.fields_by_name['cluster']._options = None
  _UDPPROXYCONFIG.fields_by_name['cluster']._serialized_options = b'\372B\004r\002 \001'
  _globals['_UDPPROXYCONFIG']._serialized_start=225
  _globals['_UDPPROXYCONFIG']._serialized_end=372
