
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from envoy.type.matcher.v3 import struct_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_struct__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n envoy/type/matcher/v3/node.proto\x12\x15\x65nvoy.type.matcher.v3\x1a\"envoy/type/matcher/v3/string.proto\x1a\"envoy/type/matcher/v3/struct.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xa9\x01\n\x0bNodeMatcher\x12\x35\n\x07node_id\x18\x01 \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcher\x12<\n\x0enode_metadatas\x18\x02 \x03(\x0b\x32$.envoy.type.matcher.v3.StructMatcher:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.type.matcher.NodeMatcherB\x82\x01\n#io.envoyproxy.envoy.type.matcher.v3B\tNodeProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.node_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\tNodeProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _NODEMATCHER._options = None
  _NODEMATCHER._serialized_options = b'\232\305\210\036 \n\036envoy.type.matcher.NodeMatcher'
  _globals['_NODEMATCHER']._serialized_start=198
  _globals['_NODEMATCHER']._serialized_end=367
