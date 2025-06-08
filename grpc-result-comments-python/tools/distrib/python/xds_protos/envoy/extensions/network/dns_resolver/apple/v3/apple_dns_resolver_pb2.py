Here's the commented version of the code:

```c++
"""Generated protocol buffer code."""
# Import required Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the default symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependency for UDPA (Universal Data Plane API) status annotations
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the Protocol Buffer descriptor by adding the serialized file
# This contains the definition of the AppleDnsResolverConfig message and its fields
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGenvoy/extensions/network/dns_resolver/apple/v3/apple_dns_resolver.proto\x12.envoy.extensions.network.dns_resolver.apple.v3\x1a\x1dudpa/annotations/status.proto\"=\n\x16\x41ppleDnsResolverConfig\x12#\n\x1binclude_unroutable_families\x18\x01 \x01(\x08\x42\xbe\x01\n<io.envoyproxy.envoy.extensions.network.dns_resolver.apple.v3B\x15\x41ppleDnsResolverProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/extensions/network/dns_resolver/apple/v3;applev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Get the global symbol table
_globals = globals()

# Build message and enum descriptors from the defined protocol buffer
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)

# Build top-level descriptors and messages for the specified module
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.network.dns_resolver.apple.v3.apple_dns_resolver_pb2', _globals)

# If not using C++ descriptors (Python-only), set additional options
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set descriptor options including package name and Go import path
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n<io.envoyproxy.envoy.extensions.network.dns_resolver.apple.v3B\025AppleDnsResolverProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/extensions/network/dns_resolver/apple/v3;applev3\272\200\310\321\006\002\020\002'
  
  # Set the byte offsets for the AppleDnsResolverConfig message in the serialized file
  _globals['_APPLEDNSRESOLVERCONFIG']._serialized_start=154
  _globals['_APPLEDNSRESOLVERCONFIG']._serialized_end=215
```

Key notes about the code:
1. This is auto-generated Protocol Buffer code for the Apple DNS Resolver configuration
2. It defines a message `AppleDnsResolverConfig` with a boolean field `include_unroutable_families`
3. The code handles both Python and C++ descriptor implementations
4. Includes metadata for the Go package path and version information
5. The serialized protocol buffer definition contains all the message and field definitions in a compact binary format