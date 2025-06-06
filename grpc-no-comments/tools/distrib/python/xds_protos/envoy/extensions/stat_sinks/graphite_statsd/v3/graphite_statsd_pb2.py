
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDenvoy/extensions/stat_sinks/graphite_statsd/v3/graphite_statsd.proto\x12.envoy.extensions.stat_sinks.graphite_statsd.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xb6\x01\n\x12GraphiteStatsdSink\x12\x30\n\x07\x61\x64\x64ress\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.AddressH\x00\x12\x0e\n\x06prefix\x18\x03 \x01(\t\x12\x45\n\x16max_bytes_per_datagram\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\x07\xfa\x42\x04\x32\x02 \x00\x42\x17\n\x10statsd_specifier\x12\x03\xf8\x42\x01\x42\xc6\x01\n<io.envoyproxy.envoy.extensions.stat_sinks.graphite_statsd.v3B\x13GraphiteStatsdProtoP\x01Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/stat_sinks/graphite_statsd/v3;graphite_statsdv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.stat_sinks.graphite_statsd.v3.graphite_statsd_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n<io.envoyproxy.envoy.extensions.stat_sinks.graphite_statsd.v3B\023GraphiteStatsdProtoP\001Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/stat_sinks/graphite_statsd/v3;graphite_statsdv3\272\200\310\321\006\002\020\002'
  _GRAPHITESTATSDSINK.oneofs_by_name['statsd_specifier']._options = None
  _GRAPHITESTATSDSINK.oneofs_by_name['statsd_specifier']._serialized_options = b'\370B\001'
  _GRAPHITESTATSDSINK.fields_by_name['max_bytes_per_datagram']._options = None
  _GRAPHITESTATSDSINK.fields_by_name['max_bytes_per_datagram']._serialized_options = b'\372B\0042\002 \000'
  _globals['_GRAPHITESTATSDSINK']._serialized_start=245
  _globals['_GRAPHITESTATSDSINK']._serialized_end=427
