
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.core.v3 import cidr_pb2 as xds_dot_core_dot_v3_dot_cidr__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/type/matcher/v3/address.proto\x12\x15\x65nvoy.type.matcher.v3\x1a\x16xds/core/v3/cidr.proto\x1a\x1dudpa/annotations/status.proto\"8\n\x0e\x41\x64\x64ressMatcher\x12&\n\x06ranges\x18\x01 \x03(\x0b\x32\x16.xds.core.v3.CidrRangeB\x85\x01\n#io.envoyproxy.envoy.type.matcher.v3B\x0c\x41\x64\x64ressProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.address_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\014AddressProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _globals['_ADDRESSMATCHER']._serialized_start=117
  _globals['_ADDRESSMATCHER']._serialized_end=173
