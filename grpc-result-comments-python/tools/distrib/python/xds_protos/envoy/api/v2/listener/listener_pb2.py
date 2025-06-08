Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the default symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import the listener components protocol buffer definitions
from envoy.api.v2.listener import listener_components_pb2 as envoy_dot_api_dot_v2_dot_listener_dot_listener__components__pb2

# Import all symbols from listener_components.proto
from envoy.api.v2.listener.listener_components_pb2 import *

# Define the protocol buffer descriptor by adding the serialized file data
# This contains:
# - The path to the proto file (envoy/api/v2/listener/listener.proto)
# - The package name (envoy.api.v2.listener)
# - The imported proto file (listener_components.proto)
# - Various options including:
#   - Java package name
#   - Go package path
#   - C# namespace
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/api/v2/listener/listener.proto\x12\x15\x65nvoy.api.v2.listener\x1a/envoy/api/v2/listener/listener_components.protoB\xab\x01\n#io.envoyproxy.envoy.api.v2.listenerB\rListenerProtoP\x01Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\xaa\x02\x17\x45nvoy.Api.V2.ListenerNS\xea\x02\x1a\x45nvoy::Api::V2::ListenerNSP\x00\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.listener.listener_pb2', _globals)

# If not using C++ descriptors, set the descriptor options
# These options mirror the ones defined in the proto file
if _descriptor._USE_C_DESCRIPTORS == False:
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.api.v2.listenerB\rListenerProtoP\001Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\252\002\027Envoy.Api.V2.ListenerNS\352\002\032Envoy::Api::V2::ListenerNS'
```