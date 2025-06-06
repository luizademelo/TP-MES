
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import value_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_value__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/type/matcher/v3/metadata.proto\x12\x15\x65nvoy.type.matcher.v3\x1a!envoy/type/matcher/v3/value.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xdd\x02\n\x0fMetadataMatcher\x12\x17\n\x06\x66ilter\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12J\n\x04path\x18\x02 \x03(\x0b\x32\x32.envoy.type.matcher.v3.MetadataMatcher.PathSegmentB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12<\n\x05value\x18\x03 \x01(\x0b\x32#.envoy.type.matcher.v3.ValueMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0e\n\x06invert\x18\x04 \x01(\x08\x1al\n\x0bPathSegment\x12\x16\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00:5\x9a\xc5\x88\x1e\x30\n.envoy.type.matcher.MetadataMatcher.PathSegmentB\x0e\n\x07segment\x12\x03\xf8\x42\x01:)\x9a\xc5\x88\x1e$\n\"envoy.type.matcher.MetadataMatcherB\x86\x01\n#io.envoyproxy.envoy.type.matcher.v3B\rMetadataProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\rMetadataProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _METADATAMATCHER_PATHSEGMENT.oneofs_by_name['segment']._options = None
  _METADATAMATCHER_PATHSEGMENT.oneofs_by_name['segment']._serialized_options = b'\370B\001'
  _METADATAMATCHER_PATHSEGMENT.fields_by_name['key']._options = None
  _METADATAMATCHER_PATHSEGMENT.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _METADATAMATCHER_PATHSEGMENT._options = None
  _METADATAMATCHER_PATHSEGMENT._serialized_options = b'\232\305\210\0360\n.envoy.type.matcher.MetadataMatcher.PathSegment'
  _METADATAMATCHER.fields_by_name['filter']._options = None
  _METADATAMATCHER.fields_by_name['filter']._serialized_options = b'\372B\004r\002\020\001'
  _METADATAMATCHER.fields_by_name['path']._options = None
  _METADATAMATCHER.fields_by_name['path']._serialized_options = b'\372B\005\222\001\002\010\001'
  _METADATAMATCHER.fields_by_name['value']._options = None
  _METADATAMATCHER.fields_by_name['value']._serialized_options = b'\372B\005\212\001\002\020\001'
  _METADATAMATCHER._options = None
  _METADATAMATCHER._serialized_options = b'\232\305\210\036$\n\"envoy.type.matcher.MetadataMatcher'
  _globals['_METADATAMATCHER']._serialized_start=190
  _globals['_METADATAMATCHER']._serialized_end=539
  _globals['_METADATAMATCHER_PATHSEGMENT']._serialized_start=388
  _globals['_METADATAMATCHER_PATHSEGMENT']._serialized_end=496
