
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+opencensus/proto/resource/v1/resource.proto\x12\x1copencensus.proto.resource.v1\"\x8b\x01\n\x08Resource\x12\x0c\n\x04type\x18\x01 \x01(\t\x12\x42\n\x06labels\x18\x02 \x03(\x0b\x32\x32.opencensus.proto.resource.v1.Resource.LabelsEntry\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x42\x98\x01\n\x1fio.opencensus.proto.resource.v1B\rResourceProtoP\x01ZEgithub.com/census-instrumentation/opencensus-proto/gen-go/resource/v1\xea\x02\x1cOpenCensus.Proto.Resource.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.resource.v1.resource_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\037io.opencensus.proto.resource.v1B\rResourceProtoP\001ZEgithub.com/census-instrumentation/opencensus-proto/gen-go/resource/v1\352\002\034OpenCensus.Proto.Resource.V1'
  _RESOURCE_LABELSENTRY._options = None
  _RESOURCE_LABELSENTRY._serialized_options = b'8\001'
  _globals['_RESOURCE']._serialized_start=78
  _globals['_RESOURCE']._serialized_end=217
  _globals['_RESOURCE_LABELSENTRY']._serialized_start=172
  _globals['_RESOURCE_LABELSENTRY']._serialized_end=217
