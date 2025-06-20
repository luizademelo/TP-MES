Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependent Protocol Buffer definitions
from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from envoy.config.core.v3 import udp_socket_config_pb2 as envoy_dot_config_dot_core_dot_v3_dot_udp__socket__config__pb2
from envoy.config.listener.v3 import quic_config_pb2 as envoy_dot_config_dot_listener_dot_v3_dot_quic__config__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the Protocol Buffer descriptor by adding the serialized file
# This contains the message definitions for UDP listener configuration
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2envoy/config/listener/v3/udp_listener_config.proto\x12\x18\x65nvoy.config.listener.v3\x1a$envoy/config/core/v3/extension.proto\x1a,envoy/config/core/v3/udp_socket_config.proto\x1a*envoy/config/listener/v3/quic_config.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xcc\x02\n\x11UdpListenerConfig\x12G\n\x18\x64ownstream_socket_config\x18\x05 \x01(\x0b\x32%.envoy.config.core.v3.UdpSocketConfig\x12\x43\n\x0cquic_options\x18\x07 \x01(\x0b\x32-.envoy.config.listener.v3.QuicProtocolOptions\x12S\n\x1fudp_packet_packet_writer_config\x18\x08 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig:.\x9a\xc5\x88\x1e)\n\'envoy.api.v2.listener.UdpListenerConfigJ\x04\x08\x01\x10\x02J\x04\x08\x02\x10\x03J\x04\x08\x03\x10\x04J\x04\x08\x04\x10\x05J\x04\x08\x06\x10\x07R\x06\x63onfig\"U\n\x1a\x41\x63tiveRawUdpListenerConfig:7\x9a\xc5\x88\x1e\x32\n0envoy.api.v2.listener.ActiveRawUdpListenerConfigB\x96\x01\n&io.envoyproxy.envoy.config.listener.v3B\x16UdpListenerConfigProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v3;listenerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.listener.v3.udp_listener_config_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options including package name and Go package path
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.config.listener.v3B\026UdpListenerConfigProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v3;listenerv3\272\200\310\321\006\002\020\002'
    
    # Set options for UdpListenerConfig message
    _UDPLISTENERCONFIG._options = None
    _UDPLISTENERCONFIG._serialized_options = b'\232\305\210\036)\n\'envoy.api.v2.listener.UdpListenerConfig'
    
    # Set options for ActiveRawUdpListenerConfig message
    _ACTIVERAWUDPLISTENERCONFIG._options = None
    _ACTIVERAWUDPLISTENERCONFIG._serialized_options = b'\232\305\210\0362\n0envoy.api.v2.listener.ActiveRawUdpListenerConfig'
    
    # Define serialized start and end positions for each message in the descriptor
    _globals['_UDPLISTENERCONFIG']._serialized_start=275
    _globals['_UDPLISTENERCONFIG']._serialized_end=607
    _globals['_ACTIVERAWUDPLISTENERCONFIG']._serialized_start=609
    _globals['_ACTIVERAWUDPLISTENERCONFIG']._serialized_end=694
```