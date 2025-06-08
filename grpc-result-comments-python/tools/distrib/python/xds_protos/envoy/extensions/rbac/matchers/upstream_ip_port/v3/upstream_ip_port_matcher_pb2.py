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

# Import dependency Protocol Buffer definitions
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.type.v3 import range_pb2 as envoy_dot_type_dot_v3_dot_range__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the Protocol Buffer message descriptor by adding the serialized file
# This contains the binary representation of the .proto file
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nQenvoy/extensions/rbac/matchers/upstream_ip_port/v3/upstream_ip_port_matcher.proto\x12\x32\x65nvoy.extensions.rbac.matchers.upstream_ip_port.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x19\x65nvoy/type/v3/range.proto\x1a\x1dudpa/annotations/status.proto\"\x85\x01\n\x15UpstreamIpPortMatcher\x12\x34\n\x0bupstream_ip\x18\x01 \x01(\x0b\x32\x1f.envoy.config.core.v3.CidrRange\x12\x36\n\x13upstream_port_range\x18\x02 \x01(\x0b\x32\x19.envoy.type.v3.Int64RangeB\xd6\x01\n@io.envoyproxy.envoy.extensions.rbac.matchers.upstream_ip_port.v3B\x1aUpstreamIpPortMatcherProtoP\x01Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/rbac/matchers/upstream_ip_port/v3;upstream_ip_portv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Access global variables dictionary
_globals = globals()

# Build message and enum descriptors from the descriptor
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.rbac.matchers.upstream_ip_port.v3.upstream_ip_port_matcher_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.rbac.matchers.upstream_ip_port.v3B\032UpstreamIpPortMatcherProtoP\001Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/rbac/matchers/upstream_ip_port/v3;upstream_ip_portv3\272\200\310\321\006\002\020\002'
    
    # Set the serialized start and end positions for the UpstreamIpPortMatcher message
    _globals['_UPSTREAMIPPORTMATCHER']._serialized_start = 232
    _globals['_UPSTREAMIPPORTMATCHER']._serialized_end = 365
```

Key points about the comments:
1. Added explanation for each import statement
2. Documented the purpose of the symbol database initialization
3. Explained the DESCRIPTOR creation and what it contains
4. Added comments for the builder operations that generate the message classes
5. Documented the conditional block for descriptor options
6. Explained the serialized start/end positions for the message type

The comments provide context for each section while maintaining readability and explaining the Protocol Buffer-specific operations.