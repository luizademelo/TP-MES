
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0bphone.proto\x12\x0cgrpc.testing\"-\n\x08\x43\x61llInfo\x12\x12\n\nsession_id\x18\x01 \x01(\t\x12\r\n\x05media\x18\x02 \x01(\t\"q\n\tCallState\x12,\n\x05state\x18\x02 \x01(\x0e\x32\x1d.grpc.testing.CallState.State\"6\n\x05State\x12\r\n\tUNDEFINED\x10\x00\x12\x07\n\x03NEW\x10\x01\x12\n\n\x06\x41\x43TIVE\x10\x06\x12\t\n\x05\x45NDED\x10\x07\")\n\x11StreamCallRequest\x12\x14\n\x0cphone_number\x18\x01 \x01(\t\"\x88\x01\n\x12StreamCallResponse\x12+\n\tcall_info\x18\x01 \x01(\x0b\x32\x16.grpc.testing.CallInfoH\x00\x12-\n\ncall_state\x18\x02 \x01(\x0b\x32\x17.grpc.testing.CallStateH\x00\x42\x16\n\x14stream_call_response2\\\n\x05Phone\x12S\n\nStreamCall\x12\x1f.grpc.testing.StreamCallRequest\x1a .grpc.testing.StreamCallResponse(\x01\x30\x01\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'phone_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
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
