Here's the commented version of the code:

```c++
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Define the Protocol Buffer message descriptors and service using serialized data
# The serialized data contains the compiled proto definitions for:
# - HelloRequest message with fields: name (string) and num_greetings (string)
# - HelloReply message with field: message (string)
# - MultiGreeter service with sayHello RPC method (client streaming)
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x19hellostreamingworld.proto\x12\x13hellostreamingworld\"3\n\x0cHelloRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x15\n\rnum_greetings\x18\x02 \x01(\t\"\x1d\n\nHelloReply\x12\x0f\n\x07message\x18\x01 \x01(\t2b\n\x0cMultiGreeter\x12R\n\x08sayHello\x12!.hellostreamingworld.HelloRequest\x1a\x1f.hellostreamingworld.HelloReply\"\x00\x30\x01\x42\x0f\n\x07\x65x.grpc\xa2\x02\x03HSWb\x06proto3')

# Build message and enum descriptors from the serialized data
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
# Build top-level descriptors and register them in the global namespace
# under the module name 'hellostreamingworld_pb2'
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'hellostreamingworld_pb2', globals())

# If not using C++ descriptors (Python implementation), set additional options
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options
    DESCRIPTOR._options = None
    # Additional serialized options including package name and prefix
    DESCRIPTOR._serialized_options = b'\n\007ex.grpc\242\002\003HSW'
    
    # Define the byte offsets for each message and service in the serialized data
    _HELLOREQUEST._serialized_start = 50  # Start position of HelloRequest message
    _HELLOREQUEST._serialized_end = 101   # End position of HelloRequest message
    _HELLOREPLY._serialized_start = 103   # Start position of HelloReply message
    _HELLOREPLY._serialized_end = 132     # End position of HelloReply message
    _MULTIGREETER._serialized_start = 134 # Start position of MultiGreeter service
    _MULTIGREETER._serialized_end = 232   # End position of MultiGreeter service
```