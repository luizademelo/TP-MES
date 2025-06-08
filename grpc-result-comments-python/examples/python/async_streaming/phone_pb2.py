Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database

# Initialize the symbol database which stores protocol buffer message types
_sym_db = _symbol_database.Default()

# Define the protocol buffer descriptor using a serialized file descriptor
# This contains the binary representation of the phone.proto file
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0bphone.proto\x12\x0cgrpc.testing\"-\n\x08\x43\x61llInfo\x12\x12\n\nsession_id\x18\x01 \x01(\t\x12\r\n\x05media\x18\x02 \x01(\t\"q\n\tCallState\x12,\n\x05state\x18\x02 \x01(\x0e\x32\x1d.grpc.testing.CallState.State\"6\n\x05State\x12\r\n\tUNDEFINED\x10\x00\x12\x07\n\x03NEW\x10\x01\x12\n\n\x06\x41\x43TIVE\x10\x06\x12\t\n\x05\x45NDED\x10\x07\")\n\x11StreamCallRequest\x12\x14\n\x0cphone_number\x18\x01 \x01(\t\"\x88\x01\n\x12StreamCallResponse\x12+\n\tcall_info\x18\x01 \x01(\x0b\x32\x16.grpc.testing.CallInfoH\x00\x12-\n\ncall_state\x18\x02 \x01(\x0b\x32\x17.grpc.testing.CallStateH\x00\x42\x16\n\x14stream_call_response2\\\n\x05Phone\x12S\n\nStreamCall\x12\x1f.grpc.testing.StreamCallRequest\x1a .grpc.testing.StreamCallResponse(\x01\x30\x01\x62\x06proto3')

# Build message and enum descriptors from the descriptor
# This makes the generated classes available in the global namespace
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
# Build top-level descriptors and messages
# This registers the generated classes with the 'phone_pb2' module
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'phone_pb2', globals())

# If not using C++ descriptors (Python implementation),
# set the serialized start and end positions for each message
if _descriptor._USE_C_DESCRIPTORS == False:
    DESCRIPTOR._options = None
    # Define serialized start and end positions for each protocol buffer message
    _CALLINFO._serialized_start=29
    _CALLINFO._serialized_end=74
    _CALLSTATE._serialized_start=76
    _CALLSTATE._serialized_end=189
    _CALLSTATE_STATE._serialized_start=135
    _CALLSTATE_STATE._serialized_end=189
    _STREAMCALLREQUEST._serialized_start=191
    _STREAMCALLREQUEST._serialized_end=232
    _STREAMCALLRESPONSE._serialized_start=235
    _STREAMCALLRESPONSE._serialized_end=371
    _PHONE._serialized_start=373
    _PHONE._serialized_end=465
```

Key explanations:
1. The code is auto-generated Protocol Buffer code from a `.proto` file definition
2. It defines several message types:
   - `CallInfo` with session_id and media fields
   - `CallState` with an enum State (UNDEFINED, NEW, ACTIVE, ENDED)
   - `StreamCallRequest` with a phone_number field
   - `StreamCallResponse` which can contain either CallInfo or CallState
3. It also defines a Phone service with a StreamCall RPC method
4. The serialized positions indicate where each message type is located in the binary descriptor

The comments explain:
- The purpose of each import
- The initialization of Protocol Buffer infrastructure
- The message definitions and their structure
- The build process that makes the generated classes available
- The serialized positions that are used when not using the C++ implementation