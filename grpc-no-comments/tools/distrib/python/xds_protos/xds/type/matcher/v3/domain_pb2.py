
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.type.matcher.v3 import matcher_pb2 as xds_dot_type_dot_matcher_dot_v3_dot_matcher__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n xds/type/matcher/v3/domain.proto\x12\x13xds.type.matcher.v3\x1a\x1fxds/annotations/v3/status.proto\x1a!xds/type/matcher/v3/matcher.proto\x1a\x17validate/validate.proto\"\xc6\x01\n\x11ServerNameMatcher\x12M\n\x0f\x64omain_matchers\x18\x01 \x03(\x0b\x32\x34.xds.type.matcher.v3.ServerNameMatcher.DomainMatcher\x1a\x62\n\rDomainMatcher\x12\x19\n\x07\x64omains\x18\x01 \x03(\tB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x36\n\x08on_match\x18\x02 \x01(\x0b\x32$.xds.type.matcher.v3.Matcher.OnMatchBn\n\x1e\x63om.github.xds.type.matcher.v3B\x16ServerNameMatcherProtoP\x01Z*github.com/cncf/xds/go/xds/type/matcher/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.type.matcher.v3.domain_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.github.xds.type.matcher.v3B\026ServerNameMatcherProtoP\001Z*github.com/cncf/xds/go/xds/type/matcher/v3\322\306\244\341\006\002\010\001'
  _SERVERNAMEMATCHER_DOMAINMATCHER.fields_by_name['domains']._options = None
  _SERVERNAMEMATCHER_DOMAINMATCHER.fields_by_name['domains']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_SERVERNAMEMATCHER']._serialized_start=151
  _globals['_SERVERNAMEMATCHER']._serialized_end=349
  _globals['_SERVERNAMEMATCHER_DOMAINMATCHER']._serialized_start=251
  _globals['_SERVERNAMEMATCHER_DOMAINMATCHER']._serialized_end=349
