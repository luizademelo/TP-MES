
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.common.dynamic_forward_proxy.v3 import dns_cache_pb2 as envoy_dot_extensions_dot_common_dot_dynamic__forward__proxy_dot_v3_dot_dns__cache__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\ncenvoy/extensions/filters/udp/udp_proxy/session/dynamic_forward_proxy/v3/dynamic_forward_proxy.proto\x12Genvoy.extensions.filters.udp.udp_proxy.session.dynamic_forward_proxy.v3\x1a@envoy/extensions/common/dynamic_forward_proxy/v3/dns_cache.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xb7\x03\n\x0c\x46ilterConfig\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x66\n\x10\x64ns_cache_config\x18\x02 \x01(\x0b\x32@.envoy.extensions.common.dynamic_forward_proxy.v3.DnsCacheConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12{\n\x0e\x62uffer_options\x18\x03 \x01(\x0b\x32\x63.envoy.extensions.filters.udp.udp_proxy.session.dynamic_forward_proxy.v3.FilterConfig.BufferOptions\x1a\x87\x01\n\rBufferOptions\x12<\n\x16max_buffered_datagrams\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x38\n\x12max_buffered_bytes\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\x1a\n\x18implementation_specifierB\x84\x02\nUio.envoyproxy.envoy.extensions.filters.udp.udp_proxy.session.dynamic_forward_proxy.v3B\x18\x44ynamicForwardProxyProtoP\x01Z\x86\x01github.com/envoyproxy/go-control-plane/envoy/extensions/filters/udp/udp_proxy/session/dynamic_forward_proxy/v3;dynamic_forward_proxyv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.udp.udp_proxy.session.dynamic_forward_proxy.v3.dynamic_forward_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nUio.envoyproxy.envoy.extensions.filters.udp.udp_proxy.session.dynamic_forward_proxy.v3B\030DynamicForwardProxyProtoP\001Z\206\001github.com/envoyproxy/go-control-plane/envoy/extensions/filters/udp/udp_proxy/session/dynamic_forward_proxy/v3;dynamic_forward_proxyv3\272\200\310\321\006\002\020\002'
  _FILTERCONFIG.fields_by_name['stat_prefix']._options = None
  _FILTERCONFIG.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _FILTERCONFIG.fields_by_name['dns_cache_config']._options = None
  _FILTERCONFIG.fields_by_name['dns_cache_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_FILTERCONFIG']._serialized_start=331
  _globals['_FILTERCONFIG']._serialized_end=770
  _globals['_FILTERCONFIG_BUFFEROPTIONS']._serialized_start=607
  _globals['_FILTERCONFIG_BUFFEROPTIONS']._serialized_end=742
