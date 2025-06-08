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

# Define the Protocol Buffer descriptor using a serialized file
# This contains the compiled proto definition for:
# - HelloRequest message with 'name' field
# - HelloReply message with 'message' field
# - Greeter service with three RPC methods:
#   1. SayHello (unary-unary)
#   2. SayHelloStreamReply (unary-stream)
#   3. SayHelloBidiStream (bidirectional streaming)
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x10helloworld.proto\x12\nhelloworld\"\x1c\n\x0cHelloRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"\x1d\n\nHelloReply\x12\x0f\n\x07message\x18\x01 \x01(\t2\xe4\x01\n\x07Greeter\x12>\n\x08SayHello\x12\x18.helloworld.HelloRequest\x1a\x16.helloworld.HelloReply\"\x00\x12K\n\x13SayHelloStreamReply\x12\x18.helloworld.HelloRequest\x1a\x16.helloworld.HelloReply\"\x00\x30\x01\x12L\n\x12SayHelloBidiStream\x12\x18.helloworld.HelloRequest\x1a\x16.helloworld.HelloReply\"\x00(\x01\x30\x01\x42\x36\n\x1bio.grpc.examples.helloworldB\x0fHelloWorldProtoP\x01\xa2\x02\x03HLWb\x06proto3')

# Build message and enum descriptors from the compiled proto
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'helloworld_pb2', _globals)

# If not using C++ descriptors (using Python implementation instead),
# set additional descriptor options and serialized positions
if not _descriptor._USE_C_DESCRIPTORS:
    # Set package and file options
    _globals['DESCRIPTOR']._loaded_options = None
    _globals['DESCRIPTOR']._serialized_options = b'\n\033io.grpc.examples.helloworldB\017HelloWorldProtoP\001\242\002\003HLW'
    
    # Define byte positions for each message in the serialized file
    _globals['_HELLOREQUEST']._serialized_start=32
    _globals['_HELLOREQUEST']._serialized_end=60
    _globals['_HELLOREPLY']._serialized_start=62
    _globals['_HELLOREPLY']._serialized_end=91
    _globals['_GREETER']._serialized_start=94
    _globals['_GREETER']._serialized_end=322
```