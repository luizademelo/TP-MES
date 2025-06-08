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

# Import dependencies from other Protocol Buffer files
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the Protocol Buffer descriptor with the serialized file data
# This contains the message definitions for Listeners and ListenerStatus
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/admin/v3/listeners.proto\x12\x0e\x65nvoy.admin.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"l\n\tListeners\x12\x39\n\x11listener_statuses\x18\x01 \x03(\x0b\x32\x1e.envoy.admin.v3.ListenerStatus:$\x9a\xc5\x88\x1e\x1f\n\x1d\x65nvoy.admin.v2alpha.Listeners\"\xc2\x01\n\x0eListenerStatus\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x34\n\rlocal_address\x18\x02 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12\x41\n\x1a\x61\x64\x64itional_local_addresses\x18\x03 \x03(\x0b\x32\x1d.envoy.config.core.v3.Address:)\x9a\xc5\x88\x1e$\n\"envoy.admin.v2alpha.ListenerStatusBw\n\x1cio.envoyproxy.envoy.admin.v3B\x0eListenersProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor data
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.listeners_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options including package name and Go package path
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\016ListenersProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
    
    # Set options for the Listeners message type
    _LISTENERS._options = None
    _LISTENERS._serialized_options = b'\232\305\210\036\037\n\035envoy.admin.v2alpha.Listeners'
    
    # Set options for the ListenerStatus message type
    _LISTENERSTATUS._options = None
    _LISTENERSTATUS._serialized_options = b'\232\305\210\036$\n\"envoy.admin.v2alpha.ListenerStatus'
    
    # Define the byte ranges for each message type in the serialized data
    _globals['_LISTENERS']._serialized_start=152
    _globals['_LISTENERS']._serialized_end=260
    _globals['_LISTENERSTATUS']._serialized_start=263
    _globals['_LISTENERSTATUS']._serialized_end=457
```

Key explanations:
1. The code is auto-generated Protocol Buffer code for Envoy's admin listener status functionality
2. It defines two main message types:
   - `Listeners`: Contains repeated `ListenerStatus` messages
   - `ListenerStatus`: Contains listener name, local address, and additional local addresses
3. The code includes versioning annotations linking these v3 messages to their v2alpha equivalents
4. Descriptor options configure package naming and import paths
5. The serialized file data contains the Protocol Buffer message definitions in binary form

The comments explain both the high-level structure and specific implementation details to help maintainers understand the generated code.