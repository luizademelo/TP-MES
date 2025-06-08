Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import required Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependencies for this proto file
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the protocol buffer descriptor by adding the serialized file
# This contains the binary representation of the proto file and its messages
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+envoy/config/listener/v3/api_listener.proto\x12\x18\x65nvoy.config.listener.v3\x1a\x19google/protobuf/any.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"f\n\x0b\x41piListener\x12*\n\x0c\x61pi_listener\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any:+\x9a\xc5\x88\x1e&\n$envoy.config.listener.v2.ApiListenerB\x90\x01\n&io.envoyproxy.envoy.config.listener.v3B\x10\x41piListenerProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v3;listenerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Access the global namespace
_globals = globals()

# Build message and enum descriptors from the descriptor
# This makes the generated classes available in the current module
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)

# Build top-level descriptors and messages
# This registers the message types with the specified module name
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.listener.v3.api_listener_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options including package name and Go import path
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.config.listener.v3B\020ApiListenerProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v3;listenerv3\272\200\310\321\006\002\020\002'
    
    # Set options for the ApiListener message
    _APILISTENER._options = None
    _APILISTENER._serialized_options = b'\232\305\210\036&\n$envoy.config.listener.v2.ApiListener'
    
    # Record the byte offsets for the ApiListener message in the serialized file
    _globals['_APILISTENER']._serialized_start = 166
    _globals['_APILISTENER']._serialized_end = 268
```

Key points explained in the comments:
1. The imports and their purposes
2. The symbol database initialization
3. The descriptor creation from serialized proto file
4. The message building process
5. The descriptor options configuration
6. The byte offset tracking for message locations

The comments provide context about what each section does without being overly verbose, making it easier for future maintainers to understand the generated code.