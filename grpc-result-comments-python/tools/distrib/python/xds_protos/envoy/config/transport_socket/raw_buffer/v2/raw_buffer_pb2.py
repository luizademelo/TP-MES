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

# Import dependency proto files
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the raw buffer protocol buffer descriptor by adding the serialized file
# This contains:
# - The proto file path
# - The package name (envoy.config.transport_socket.raw_buffer.v2)
# - Dependencies on udpa annotations (migrate and status protos)
# - The actual message definition (RawBuffer message which is empty in this case)
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n<envoy/config/transport_socket/raw_buffer/v2/raw_buffer.proto\x12+envoy.config.transport_socket.raw_buffer.v2\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"\x0b\n\tRawBufferB\xee\x01\n9io.envoyproxy.envoy.config.transport_socket.raw_buffer.v2B\x0eRawBufferProtoP\x01Z_github.com/envoyproxy/go-control-plane/envoy/config/transport_socket/raw_buffer/v2;raw_bufferv2\xf2\x98\xfe\x8f\x05\x32\x12\x30\x65nvoy.extensions.transport_sockets.raw_buffer.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build the top descriptors and messages and register them in the global namespace
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.transport_socket.raw_buffer.v2.raw_buffer_pb2', _globals)

# If not using C++ descriptors (using Python implementation instead),
# set the descriptor options
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  # Set serialized options including:
  # - Java package name
  # - Go package path
  # - Proto file versioning information
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.config.transport_socket.raw_buffer.v2B\016RawBufferProtoP\001Z_github.com/envoyproxy/go-control-plane/envoy/config/transport_socket/raw_buffer/v2;raw_bufferv2\362\230\376\217\0052\0220envoy.extensions.transport_sockets.raw_buffer.v3\272\200\310\321\006\002\020\001'
  # Set the start and end positions of the RawBuffer message in the descriptor
  _globals['_RAWBUFFER']._serialized_start=172
  _globals['_RAWBUFFER']._serialized_end=183
```

Key points explained in the comments:
1. The imports and initialization of Protocol Buffer infrastructure
2. The descriptor creation which defines the protocol buffer schema
3. The message building process that makes the generated classes available
4. The options configuration for different language targets (Java, Go) and versioning
5. The position markers for the message in the descriptor

The code appears to be auto-generated Protocol Buffer code for Envoy's raw buffer transport socket configuration.