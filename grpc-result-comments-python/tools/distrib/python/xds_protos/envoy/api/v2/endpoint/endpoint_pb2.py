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

# Import the endpoint components protocol buffer definitions
from envoy.api.v2.endpoint import endpoint_components_pb2 as envoy_dot_api_dot_v2_dot_endpoint_dot_endpoint__components__pb2
from envoy.api.v2.endpoint.endpoint_components_pb2 import *

# Define the descriptor for the endpoint.proto file by adding its serialized content
# This includes:
# - The proto file path ('envoy/api/v2/endpoint/endpoint.proto')
# - The package name ('envoy.api.v2.endpoint')
# - Its dependency on endpoint_components.proto
# - Additional metadata for code generation (Java package, Go package, etc.)
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/api/v2/endpoint/endpoint.proto\x12\x15\x65nvoy.api.v2.endpoint\x1a/envoy/api/v2/endpoint/endpoint_components.protoBt\n#io.envoyproxy.envoy.api.v2.endpointB\rEndpointProtoP\x01Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/endpointP\x00\x62\x06proto3')

# Build message and enum descriptors using the global symbol table
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages for the endpoint proto file
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.endpoint.endpoint_pb2', _globals)

# If not using C++ descriptors (Python runtime), set additional descriptor options
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options including:
    # - Java package ('io.envoyproxy.envoy.api.v2.endpoint')
    # - Proto file name ('EndpointProto')
    # - Go package path ('github.com/envoyproxy/go-control-plane/envoy/api/v2/endpoint')
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.api.v2.endpointB\rEndpointProtoP\001Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/endpoint'
```