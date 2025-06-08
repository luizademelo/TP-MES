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

# Import dependency proto files for annotations
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the raw buffer protocol buffer descriptor by adding the serialized file
# This contains:
# - The proto file path
# - The package name
# - Dependencies on status and versioning annotations
# - The RawBuffer message definition with versioning information
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nAenvoy/extensions/transport_sockets/raw_buffer/v3/raw_buffer.proto\x12\x30\x65nvoy.extensions.transport_sockets.raw_buffer.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"I\n\tRawBuffer:<\x9a\xc5\x88\x1e\x37\n5envoy.config.transport_socket.raw_buffer.v2.RawBufferB\xc0\x01\n>io.envoyproxy.envoy.extensions.transport_sockets.raw_buffer.v3B\x0eRawBufferProtoP\x01Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/raw_buffer/v3;raw_bufferv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build the top descriptors and messages for the proto file
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.raw_buffer.v3.raw_buffer_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set descriptor options including:
  # - Java package name
  # - Go package path
  # - File descriptor set version
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.transport_sockets.raw_buffer.v3B\016RawBufferProtoP\001Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/raw_buffer/v3;raw_bufferv3\272\200\310\321\006\002\020\002'
  
  # Set RawBuffer message options including versioning information
  _RAWBUFFER._options = None
  _RAWBUFFER._serialized_options = b'\232\305\210\0367\n5envoy.config.transport_socket.raw_buffer.v2.RawBuffer'
  
  # Set the serialized start and end positions for the RawBuffer message
  _globals['_RAWBUFFER']._serialized_start=185
  _globals['_RAWBUFFER']._serialized_end=258
```

The comments explain:
1. The imports and their purposes
2. The symbol database initialization
3. The descriptor creation and what it contains
4. The message building process
5. The configuration of options when not using C++ descriptors
6. The specific options being set for both the file descriptor and the RawBuffer message
7. The serialized positions of the message in the descriptor

The code appears to be auto-generated Protocol Buffer code for Envoy's raw buffer transport socket configuration, with versioning support from v2 to v3.