
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.metadata.v3 import metadata_pb2 as envoy_dot_type_dot_metadata_dot_v3_dot_metadata__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/type/tracing/v3/custom_tag.proto\x12\x15\x65nvoy.type.tracing.v3\x1a%envoy/type/metadata/v3/metadata.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xcf\x06\n\tCustomTag\x12\x14\n\x03tag\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12;\n\x07literal\x18\x02 \x01(\x0b\x32(.envoy.type.tracing.v3.CustomTag.LiteralH\x00\x12\x43\n\x0b\x65nvironment\x18\x03 \x01(\x0b\x32,.envoy.type.tracing.v3.CustomTag.EnvironmentH\x00\x12\x41\n\x0erequest_header\x18\x04 \x01(\x0b\x32\'.envoy.type.tracing.v3.CustomTag.HeaderH\x00\x12=\n\x08metadata\x18\x05 \x01(\x0b\x32).envoy.type.tracing.v3.CustomTag.MetadataH\x00\x1aQ\n\x07Literal\x12\x16\n\x05value\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01:.\x9a\xc5\x88\x1e)\n\'envoy.type.tracing.v2.CustomTag.Literal\x1ao\n\x0b\x45nvironment\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x15\n\rdefault_value\x18\x02 \x01(\t:2\x9a\xc5\x88\x1e-\n+envoy.type.tracing.v2.CustomTag.Environment\x1ak\n\x06Header\x12\x1b\n\x04name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x00\x12\x15\n\rdefault_value\x18\x02 \x01(\t:-\x9a\xc5\x88\x1e(\n&envoy.type.tracing.v2.CustomTag.Header\x1a\xc1\x01\n\x08Metadata\x12\x32\n\x04kind\x18\x01 \x01(\x0b\x32$.envoy.type.metadata.v3.MetadataKind\x12\x39\n\x0cmetadata_key\x18\x02 \x01(\x0b\x32#.envoy.type.metadata.v3.MetadataKey\x12\x15\n\rdefault_value\x18\x03 \x01(\t:/\x9a\xc5\x88\x1e*\n(envoy.type.tracing.v2.CustomTag.Metadata:&\x9a\xc5\x88\x1e!\n\x1f\x65nvoy.type.tracing.v2.CustomTagB\x0b\n\x04type\x12\x03\xf8\x42\x01\x42\x87\x01\n#io.envoyproxy.envoy.type.tracing.v3B\x0e\x43ustomTagProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/tracing/v3;tracingv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.tracing.v3.custom_tag_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.tracing.v3B\016CustomTagProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/tracing/v3;tracingv3\272\200\310\321\006\002\020\002'
  _CUSTOMTAG_LITERAL.fields_by_name['value']._options = None
  _CUSTOMTAG_LITERAL.fields_by_name['value']._serialized_options = b'\372B\004r\002\020\001'
  _CUSTOMTAG_LITERAL._options = None
  _CUSTOMTAG_LITERAL._serialized_options = b'\232\305\210\036)\n\'envoy.type.tracing.v2.CustomTag.Literal'
  _CUSTOMTAG_ENVIRONMENT.fields_by_name['name']._options = None
  _CUSTOMTAG_ENVIRONMENT.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _CUSTOMTAG_ENVIRONMENT._options = None
  _CUSTOMTAG_ENVIRONMENT._serialized_options = b'\232\305\210\036-\n+envoy.type.tracing.v2.CustomTag.Environment'
  _CUSTOMTAG_HEADER.fields_by_name['name']._options = None
  _CUSTOMTAG_HEADER.fields_by_name['name']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\000'
  _CUSTOMTAG_HEADER._options = None
  _CUSTOMTAG_HEADER._serialized_options = b'\232\305\210\036(\n&envoy.type.tracing.v2.CustomTag.Header'
  _CUSTOMTAG_METADATA._options = None
  _CUSTOMTAG_METADATA._serialized_options = b'\232\305\210\036*\n(envoy.type.tracing.v2.CustomTag.Metadata'
  _CUSTOMTAG.oneofs_by_name['type']._options = None
  _CUSTOMTAG.oneofs_by_name['type']._serialized_options = b'\370B\001'
  _CUSTOMTAG.fields_by_name['tag']._options = None
  _CUSTOMTAG.fields_by_name['tag']._serialized_options = b'\372B\004r\002\020\001'
  _CUSTOMTAG._options = None
  _CUSTOMTAG._serialized_options = b'\232\305\210\036!\n\037envoy.type.tracing.v2.CustomTag'
  _globals['_CUSTOMTAG']._serialized_start=196
  _globals['_CUSTOMTAG']._serialized_end=1043
  _globals['_CUSTOMTAG_LITERAL']._serialized_start=491
  _globals['_CUSTOMTAG_LITERAL']._serialized_end=572
  _globals['_CUSTOMTAG_ENVIRONMENT']._serialized_start=574
  _globals['_CUSTOMTAG_ENVIRONMENT']._serialized_end=685
  _globals['_CUSTOMTAG_HEADER']._serialized_start=687
  _globals['_CUSTOMTAG_HEADER']._serialized_end=794
  _globals['_CUSTOMTAG_METADATA']._serialized_start=797
  _globals['_CUSTOMTAG_METADATA']._serialized_end=990
