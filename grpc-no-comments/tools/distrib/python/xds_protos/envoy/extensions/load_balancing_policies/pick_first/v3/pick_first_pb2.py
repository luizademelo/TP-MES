
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGenvoy/extensions/load_balancing_policies/pick_first/v3/pick_first.proto\x12\x36\x65nvoy.extensions.load_balancing_policies.pick_first.v3\x1a\x1dudpa/annotations/status.proto\")\n\tPickFirst\x12\x1c\n\x14shuffle_address_list\x18\x01 \x01(\x08\x42\xcc\x01\nDio.envoyproxy.envoy.extensions.load_balancing_policies.pick_first.v3B\x0ePickFirstProtoP\x01Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/pick_first/v3;pick_firstv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.pick_first.v3.pick_first_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nDio.envoyproxy.envoy.extensions.load_balancing_policies.pick_first.v3B\016PickFirstProtoP\001Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/pick_first/v3;pick_firstv3\272\200\310\321\006\002\020\002'
  _globals['_PICKFIRST']._serialized_start=162
  _globals['_PICKFIRST']._serialized_end=203
