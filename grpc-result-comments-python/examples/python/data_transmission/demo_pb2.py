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
# The serialized data contains the compiled version of demo.proto
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\ndemo.proto\x12\x04\x64\x65mo\"2\n\x07Request\x12\x11\n\tclient_id\x18\x01 \x01(\x03\x12\x14\n\x0crequest_data\x18\x02 \x01(\t\"4\n\x08Response\x12\x11\n\tserver_id\x18\x01 \x01(\x03\x12\x15\n\rresponse_data\x18\x02 \x01(\t2\xf0\x01\n\x08GRPCDemo\x12-\n\x0cSimpleMethod\x12\r.demo.Request\x1a\x0e.demo.Response\x12\x38\n\x15\x43lientStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response(\x01\x12\x38\n\x15ServerStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response0\x01\x12\x41\n\x1c\x42idirectionalStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response(\x01\x30\x01\x62\x06proto3')

# Build message and enum descriptors from the serialized data
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
# Build top-level descriptors and messages, making them available in the current namespace
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'demo_pb2', globals())

# If not using C++ descriptors (using Python implementation instead),
# set additional descriptor options and serialization information
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options (currently None as no options are specified)
    DESCRIPTOR._options = None
    
    # Define serialization start and end points for each message type
    _REQUEST._serialized_start=20
    _REQUEST._serialized_end=70
    _RESPONSE._serialized_start=72
    _RESPONSE._serialized_end=124
    _GRPCDEMO._serialized_start=127
    _GRPCDEMO._serialized_end=367
```

Key explanations:
1. The code is auto-generated Protocol Buffer code from a .proto file definition
2. It defines:
   - A Request message with client_id (int64) and request_data (string) fields
   - A Response message with server_id (int64) and response_data (string) fields
   - A GRPCDemo service with four RPC methods:
     * SimpleMethod - unary RPC
     * ClientStreamingMethod - client streaming RPC
     * ServerStreamingMethod - server streaming RPC
     * BidirectionalStreamingMethod - bidirectional streaming RPC
3. The serialized data contains the compiled Protocol Buffer definitions
4. The builder functions create Python classes from these definitions
5. The if block handles Python-specific descriptor implementations