
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher import string_pb2 as envoy_dot_type_dot_matcher_dot_string__pb2
from envoy.type.matcher import struct_pb2 as envoy_dot_type_dot_matcher_dot_struct__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1d\x65nvoy/type/matcher/node.proto\x12\x12\x65nvoy.type.matcher\x1a\x1f\x65nvoy/type/matcher/string.proto\x1a\x1f\x65nvoy/type/matcher/struct.proto\x1a\x1dudpa/annotations/status.proto\"|\n\x0bNodeMatcher\x12\x32\n\x07node_id\x18\x01 \x01(\x0b\x32!.envoy.type.matcher.StringMatcher\x12\x39\n\x0enode_metadatas\x18\x02 \x03(\x0b\x32!.envoy.type.matcher.StructMatcherBr\n io.envoyproxy.envoy.type.matcherB\tNodeProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.node_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\tNodeProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _globals['_NODEMATCHER']._serialized_start=150
  _globals['_NODEMATCHER']._serialized_end=274
