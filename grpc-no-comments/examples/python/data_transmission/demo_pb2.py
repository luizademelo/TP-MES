
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\ndemo.proto\x12\x04\x64\x65mo\"2\n\x07Request\x12\x11\n\tclient_id\x18\x01 \x01(\x03\x12\x14\n\x0crequest_data\x18\x02 \x01(\t\"4\n\x08Response\x12\x11\n\tserver_id\x18\x01 \x01(\x03\x12\x15\n\rresponse_data\x18\x02 \x01(\t2\xf0\x01\n\x08GRPCDemo\x12-\n\x0cSimpleMethod\x12\r.demo.Request\x1a\x0e.demo.Response\x12\x38\n\x15\x43lientStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response(\x01\x12\x38\n\x15ServerStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response0\x01\x12\x41\n\x1c\x42idirectionalStreamingMethod\x12\r.demo.Request\x1a\x0e.demo.Response(\x01\x30\x01\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'demo_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _REQUEST._serialized_start=20
  _REQUEST._serialized_end=70
  _RESPONSE._serialized_start=72
  _RESPONSE._serialized_end=124
  _GRPCDEMO._serialized_start=127
  _GRPCDEMO._serialized_end=367
