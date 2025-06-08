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

# Import dependencies for this proto file
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the descriptor for the proto file by adding the serialized file content
# This contains:
# - The proto file path: envoy/config/listener/v2/api_listener.proto
# - The package name: envoy.config.listener.v2
# - Imported proto files (any.proto, migrate.proto, status.proto)
# - Message definition for ApiListener containing an any.proto field
# - Various options and metadata
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+envoy/config/listener/v2/api_listener.proto\x12\x18\x65nvoy.config.listener.v2\x1a\x19google/protobuf/any.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"9\n\x0b\x41piListener\x12*\n\x0c\x61pi_listener\x18\x01 \x01(\x0b\x32\x14.google.protobuf.AnyB\xb0\x01\n&io.envoyproxy.envoy.config.listener.v2B\x10\x41piListenerProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v2;listenerv2\xf2\x98\xfe\x8f\x05\x1a\x12\x18\x65nvoy.config.listener.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build the top descriptors and messages for the specified proto file
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.listener.v2.api_listener_pb2', _globals)

# If not using C++ descriptors (Python implementation), set additional options
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set descriptor options
  DESCRIPTOR._options = None
  # Serialized options include:
  # - Java package name
  # - Go package path
  # - Proto file versioning information
  DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.config.listener.v2B\020ApiListenerProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v2;listenerv2\362\230\376\217\005\032\022\030envoy.config.listener.v3\272\200\310\321\006\002\020\001'
  # Set the global variables for message start and end positions in the descriptor
  _globals['_APILISTENER']._serialized_start=163
  _globals['_APILISTENER']._serialized_end=220
```