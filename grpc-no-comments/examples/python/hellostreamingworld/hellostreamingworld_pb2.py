
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x19hellostreamingworld.proto\x12\x13hellostreamingworld\"3\n\x0cHelloRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x15\n\rnum_greetings\x18\x02 \x01(\t\"\x1d\n\nHelloReply\x12\x0f\n\x07message\x18\x01 \x01(\t2b\n\x0cMultiGreeter\x12R\n\x08sayHello\x12!.hellostreamingworld.HelloRequest\x1a\x1f.hellostreamingworld.HelloReply\"\x00\x30\x01\x42\x0f\n\x07\x65x.grpc\xa2\x02\x03HSWb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'hellostreamingworld_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\007ex.grpc\242\002\003HSW'
  _HELLOREQUEST._serialized_start=50
  _HELLOREQUEST._serialized_end=101
  _HELLOREPLY._serialized_start=103
  _HELLOREPLY._serialized_end=132
  _MULTIGREETER._serialized_start=134
  _MULTIGREETER._serialized_end=232
