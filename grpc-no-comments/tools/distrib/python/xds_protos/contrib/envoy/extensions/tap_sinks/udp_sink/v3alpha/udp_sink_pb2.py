
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nBcontrib/envoy/extensions/tap_sinks/udp_sink/v3alpha/udp_sink.proto\x12+envoy.extensions.tap_sinks.udp_sink.v3alpha\x1a\"envoy/config/core/v3/address.proto\x1a\x1dudpa/annotations/status.proto\"C\n\x07UdpSink\x12\x38\n\x0budp_address\x18\x01 \x01(\x0b\x32#.envoy.config.core.v3.SocketAddressB\xaf\x01\n9io.envoyproxy.envoy.extensions.tap_sinks.udp_sink.v3alphaB\x0cUdpSinkProtoP\x01ZZgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/tap_sinks/udp_sink/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.tap_sinks.udp_sink.v3alpha.udp_sink_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.extensions.tap_sinks.udp_sink.v3alphaB\014UdpSinkProtoP\001ZZgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/tap_sinks/udp_sink/v3alpha\272\200\310\321\006\002\020\002'
  _globals['_UDPSINK']._serialized_start=182
  _globals['_UDPSINK']._serialized_end=249
