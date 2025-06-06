
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n]envoy/extensions/quic/server_preferred_address/v3/fixed_server_preferred_address_config.proto\x12\x31\x65nvoy.extensions.quic.server_preferred_address.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1dudpa/annotations/status.proto\"\xd6\x03\n!FixedServerPreferredAddressConfig\x12\x14\n\x0cipv4_address\x18\x01 \x01(\t\x12}\n\x0bipv4_config\x18\x03 \x01(\x0b\x32h.envoy.extensions.quic.server_preferred_address.v3.FixedServerPreferredAddressConfig.AddressFamilyConfig\x12\x14\n\x0cipv6_address\x18\x02 \x01(\t\x12}\n\x0bipv6_config\x18\x04 \x01(\x0b\x32h.envoy.extensions.quic.server_preferred_address.v3.FixedServerPreferredAddressConfig.AddressFamilyConfig\x1a\x86\x01\n\x13\x41\x64\x64ressFamilyConfig\x12\x34\n\x07\x61\x64\x64ress\x18\x01 \x01(\x0b\x32#.envoy.config.core.v3.SocketAddress\x12\x39\n\x0c\x64nat_address\x18\x02 \x01(\x0b\x32#.envoy.config.core.v3.SocketAddressB\xe8\x01\n?io.envoyproxy.envoy.extensions.quic.server_preferred_address.v3B&FixedServerPreferredAddressConfigProtoP\x01Zsgithub.com/envoyproxy/go-control-plane/envoy/extensions/quic/server_preferred_address/v3;server_preferred_addressv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.quic.server_preferred_address.v3.fixed_server_preferred_address_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.quic.server_preferred_address.v3B&FixedServerPreferredAddressConfigProtoP\001Zsgithub.com/envoyproxy/go-control-plane/envoy/extensions/quic/server_preferred_address/v3;server_preferred_addressv3\272\200\310\321\006\002\020\002'
  _globals['_FIXEDSERVERPREFERREDADDRESSCONFIG']._serialized_start=216
  _globals['_FIXEDSERVERPREFERREDADDRESSCONFIG']._serialized_end=686
  _globals['_FIXEDSERVERPREFERREDADDRESSCONFIG_ADDRESSFAMILYCONFIG']._serialized_start=552
  _globals['_FIXEDSERVERPREFERREDADDRESSCONFIG_ADDRESSFAMILYCONFIG']._serialized_end=686
