
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,envoy/type/http/v3/path_transformation.proto\x12\x12\x65nvoy.type.http.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xee\x02\n\x12PathTransformation\x12\x44\n\noperations\x18\x01 \x03(\x0b\x32\x30.envoy.type.http.v3.PathTransformation.Operation\x1a\x91\x02\n\tOperation\x12h\n\x17normalize_path_rfc_3986\x18\x02 \x01(\x0b\x32\x45.envoy.type.http.v3.PathTransformation.Operation.NormalizePathRFC3986H\x00\x12V\n\rmerge_slashes\x18\x03 \x01(\x0b\x32=.envoy.type.http.v3.PathTransformation.Operation.MergeSlashesH\x00\x1a\x16\n\x14NormalizePathRFC3986\x1a\x0e\n\x0cMergeSlashesB\x1a\n\x13operation_specifier\x12\x03\xf8\x42\x01\x42\x87\x01\n io.envoyproxy.envoy.type.http.v3B\x17PathTransformationProtoP\x01Z@github.com/envoyproxy/go-control-plane/envoy/type/http/v3;httpv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.http.v3.path_transformation_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.http.v3B\027PathTransformationProtoP\001Z@github.com/envoyproxy/go-control-plane/envoy/type/http/v3;httpv3\272\200\310\321\006\002\020\002'
  _PATHTRANSFORMATION_OPERATION.oneofs_by_name['operation_specifier']._options = None
  _PATHTRANSFORMATION_OPERATION.oneofs_by_name['operation_specifier']._serialized_options = b'\370B\001'
  _globals['_PATHTRANSFORMATION']._serialized_start=125
  _globals['_PATHTRANSFORMATION']._serialized_end=491
  _globals['_PATHTRANSFORMATION_OPERATION']._serialized_start=218
  _globals['_PATHTRANSFORMATION_OPERATION']._serialized_end=491
  _globals['_PATHTRANSFORMATION_OPERATION_NORMALIZEPATHRFC3986']._serialized_start=425
  _globals['_PATHTRANSFORMATION_OPERATION_NORMALIZEPATHRFC3986']._serialized_end=447
  _globals['_PATHTRANSFORMATION_OPERATION_MERGESLASHES']._serialized_start=449
  _globals['_PATHTRANSFORMATION_OPERATION_MERGESLASHES']._serialized_end=463
