Here's the commented version of the code:

```c++
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import custom Protocol Buffer definitions from udpa annotations
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the Protocol Buffer descriptor using a serialized file descriptor
# This contains the message definitions for the gRPC HTTP/1.1 bridge filter configuration
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?envoy/extensions/filters/http/grpc_http1_bridge/v3/config.proto\x12\x32\x65nvoy.extensions.filters.http.grpc_http1_bridge.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\x88\x01\n\x06\x43onfig\x12 \n\x18upgrade_protobuf_to_grpc\x18\x01 \x01(\x08\x12\x1f\n\x17ignore_query_parameters\x18\x02 \x01(\x08:;\x9a\xc5\x88\x1e\x36\n4envoy.config.filter.http.grpc_http1_bridge.v2.ConfigB\xc8\x01\n@io.envoyproxy.envoy.extensions.filters.http.grpc_http1_bridge.v3B\x0b\x43onfigProtoP\x01Zmgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/grpc_http1_bridge/v3;grpc_http1_bridgev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages for the specified module
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.grpc_http1_bridge.v3.config_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set descriptor options including package name and Go package path
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.filters.http.grpc_http1_bridge.v3B\013ConfigProtoP\001Zmgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/grpc_http1_bridge/v3;grpc_http1_bridgev3\272\200\310\321\006\002\020\002'
  
  # Set Config message specific options including versioning information
  _CONFIG._options = None
  _CONFIG._serialized_options = b'\232\305\210\0366\n4envoy.config.filter.http.grpc_http1_bridge.v2.Config'
  
  # Define the byte range where the Config message is located in the descriptor
  _globals['_CONFIG']._serialized_start=186
  _globals['_CONFIG']._serialized_end=322
```