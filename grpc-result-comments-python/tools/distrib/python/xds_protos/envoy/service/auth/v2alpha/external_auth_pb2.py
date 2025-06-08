Here's the commented version of the code snippet:

```c++
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import the base external_auth proto definitions from v2
from envoy.service.auth.v2 import external_auth_pb2 as envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2

# Define the protocol buffer descriptor by adding the serialized file data
# This contains:
# - The proto file path: envoy/service/auth/v2alpha/external_auth.proto
# - The package name: envoy.service.auth.v2alpha
# - The imported proto file: envoy/service/auth/v2/external_auth.proto
# - The service definition (Authorization) with its RPC method (Check)
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n.envoy/service/auth/v2alpha/external_auth.proto\x12\x1a\x65nvoy.service.auth.v2alpha\x1a)envoy/service/auth/v2/external_auth.proto2c\n\rAuthorization\x12R\n\x05\x43heck\x12#.envoy.service.auth.v2.CheckRequest\x1a$.envoy.service.auth.v2.CheckResponseB{\n(io.envoyproxy.envoy.service.auth.v2alphaB\nCertsProtoP\x01ZAgithub.com/envoyproxy/go-control-plane/envoy/service/auth/v2alphab\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.auth.v2alpha.external_auth_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  # Set serialized options including:
  # - Java package (io.envoyproxy.envoy.service.auth.v2alpha)
  # - Proto file name (CertsProto)
  # - Go package path (github.com/envoyproxy/go-control-plane/envoy/service/auth/v2alpha)
  DESCRIPTOR._serialized_options = b'\n(io.envoyproxy.envoy.service.auth.v2alphaB\nCertsProtoP\001ZAgithub.com/envoyproxy/go-control-plane/envoy/service/auth/v2alpha'
  # Set the serialized start and end positions for the Authorization service
  _globals['_AUTHORIZATION']._serialized_start=121
  _globals['_AUTHORIZATION']._serialized_end=220
```