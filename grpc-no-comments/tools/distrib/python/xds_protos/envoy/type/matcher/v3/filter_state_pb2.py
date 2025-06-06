
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import address_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_address__pb2
from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(envoy/type/matcher/v3/filter_state.proto\x12\x15\x65nvoy.type.matcher.v3\x1a#envoy/type/matcher/v3/address.proto\x1a\"envoy/type/matcher/v3/string.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xb8\x01\n\x12\x46ilterStateMatcher\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12<\n\x0cstring_match\x18\x02 \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcherH\x00\x12>\n\raddress_match\x18\x03 \x01(\x0b\x32%.envoy.type.matcher.v3.AddressMatcherH\x00\x42\x0e\n\x07matcher\x12\x03\xf8\x42\x01\x42\x89\x01\n#io.envoyproxy.envoy.type.matcher.v3B\x10\x46ilterStateProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.filter_state_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\020FilterStateProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _FILTERSTATEMATCHER.oneofs_by_name['matcher']._options = None
  _FILTERSTATEMATCHER.oneofs_by_name['matcher']._serialized_options = b'\370B\001'
  _FILTERSTATEMATCHER.fields_by_name['key']._options = None
  _FILTERSTATEMATCHER.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_FILTERSTATEMATCHER']._serialized_start=197
  _globals['_FILTERSTATEMATCHER']._serialized_end=381
