
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.core.v3 import cidr_pb2 as xds_dot_core_dot_v3_dot_cidr__pb2
from xds.type.matcher.v3 import matcher_pb2 as xds_dot_type_dot_matcher_dot_v3_dot_matcher__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1cxds/type/matcher/v3/ip.proto\x12\x13xds.type.matcher.v3\x1a\x1fxds/annotations/v3/status.proto\x1a\x16xds/core/v3/cidr.proto\x1a!xds/type/matcher/v3/matcher.proto\x1a\x17validate/validate.proto\"\xe2\x01\n\tIPMatcher\x12\x45\n\x0erange_matchers\x18\x01 \x03(\x0b\x32-.xds.type.matcher.v3.IPMatcher.IPRangeMatcher\x1a\x8d\x01\n\x0eIPRangeMatcher\x12\x30\n\x06ranges\x18\x01 \x03(\x0b\x32\x16.xds.core.v3.CidrRangeB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x36\n\x08on_match\x18\x02 \x01(\x0b\x32$.xds.type.matcher.v3.Matcher.OnMatch\x12\x11\n\texclusive\x18\x03 \x01(\x08\x42\x66\n\x1e\x63om.github.xds.type.matcher.v3B\x0eIPMatcherProtoP\x01Z*github.com/cncf/xds/go/xds/type/matcher/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.type.matcher.v3.ip_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.github.xds.type.matcher.v3B\016IPMatcherProtoP\001Z*github.com/cncf/xds/go/xds/type/matcher/v3\322\306\244\341\006\002\010\001'
  _IPMATCHER_IPRANGEMATCHER.fields_by_name['ranges']._options = None
  _IPMATCHER_IPRANGEMATCHER.fields_by_name['ranges']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_IPMATCHER']._serialized_start=171
  _globals['_IPMATCHER']._serialized_end=397
  _globals['_IPMATCHER_IPRANGEMATCHER']._serialized_start=256
  _globals['_IPMATCHER_IPRANGEMATCHER']._serialized_end=397
