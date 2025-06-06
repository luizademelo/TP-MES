
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.core.v3 import context_params_pb2 as xds_dot_core_dot_v3_dot_context__params__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"xds/core/v3/resource_locator.proto\x12\x0bxds.core.v3\x1a\x1fxds/annotations/v3/status.proto\x1a xds/core/v3/context_params.proto\x1a\x17validate/validate.proto\"\xc2\x03\n\x0fResourceLocator\x12=\n\x06scheme\x18\x01 \x01(\x0e\x32#.xds.core.v3.ResourceLocator.SchemeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\n\n\x02id\x18\x02 \x01(\t\x12\x11\n\tauthority\x18\x03 \x01(\t\x12\x1e\n\rresource_type\x18\x04 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x33\n\rexact_context\x18\x05 \x01(\x0b\x32\x1a.xds.core.v3.ContextParamsH\x00\x12:\n\ndirectives\x18\x06 \x03(\x0b\x32&.xds.core.v3.ResourceLocator.Directive\x1a|\n\tDirective\x12+\n\x03\x61lt\x18\x01 \x01(\x0b\x32\x1c.xds.core.v3.ResourceLocatorH\x00\x12\x30\n\x05\x65ntry\x18\x02 \x01(\tB\x1f\xfa\x42\x1cr\x1a\x10\x01\x32\x16^[0-9a-zA-Z_\\-\\./~:]+$H\x00\x42\x10\n\tdirective\x12\x03\xf8\x42\x01\"\'\n\x06Scheme\x12\t\n\x05XDSTP\x10\x00\x12\x08\n\x04HTTP\x10\x01\x12\x08\n\x04\x46ILE\x10\x02\x42\x19\n\x17\x63ontext_param_specifierB\\\n\x16\x63om.github.xds.core.v3B\x14ResourceLocatorProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.resource_locator_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\024ResourceLocatorProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3\322\306\244\341\006\002\010\001'
  _RESOURCELOCATOR_DIRECTIVE.oneofs_by_name['directive']._options = None
  _RESOURCELOCATOR_DIRECTIVE.oneofs_by_name['directive']._serialized_options = b'\370B\001'
  _RESOURCELOCATOR_DIRECTIVE.fields_by_name['entry']._options = None
  _RESOURCELOCATOR_DIRECTIVE.fields_by_name['entry']._serialized_options = b'\372B\034r\032\020\0012\026^[0-9a-zA-Z_\\-\\./~:]+$'
  _RESOURCELOCATOR.fields_by_name['scheme']._options = None
  _RESOURCELOCATOR.fields_by_name['scheme']._serialized_options = b'\372B\005\202\001\002\020\001'
  _RESOURCELOCATOR.fields_by_name['resource_type']._options = None
  _RESOURCELOCATOR.fields_by_name['resource_type']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_RESOURCELOCATOR']._serialized_start=144
  _globals['_RESOURCELOCATOR']._serialized_end=594
  _globals['_RESOURCELOCATOR_DIRECTIVE']._serialized_start=402
  _globals['_RESOURCELOCATOR_DIRECTIVE']._serialized_end=526
  _globals['_RESOURCELOCATOR_SCHEME']._serialized_start=528
  _globals['_RESOURCELOCATOR_SCHEME']._serialized_end=567
