
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nIcontrib/envoy/extensions/network/connection_balance/dlb/v3alpha/dlb.proto\x12\x37\x65nvoy.extensions.network.connection_balance.dlb.v3alpha\x1a\x1dudpa/annotations/status.proto\"\xde\x01\n\x03\x44lb\x12\n\n\x02id\x18\x01 \x01(\r\x12\x13\n\x0bmax_retries\x18\x02 \x01(\r\x12\x64\n\x0f\x66\x61llback_policy\x18\x03 \x01(\x0e\x32K.envoy.extensions.network.connection_balance.dlb.v3alpha.Dlb.FallbackPolicy\"P\n\x0e\x46\x61llbackPolicy\x12\x08\n\x04None\x10\x00\x12\x18\n\x14NopConnectionBalance\x10\x01\x12\x1a\n\x16\x45xactConnectionBalance\x10\x02\x42\xc3\x01\nEio.envoyproxy.envoy.extensions.network.connection_balance.dlb.v3alphaB\x08\x44lbProtoP\x01Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/network/connection_balance/dlb/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.network.connection_balance.dlb.v3alpha.dlb_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.extensions.network.connection_balance.dlb.v3alphaB\010DlbProtoP\001Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/network/connection_balance/dlb/v3alpha\272\200\310\321\006\002\020\002'
  _globals['_DLB']._serialized_start=166
  _globals['_DLB']._serialized_end=388
  _globals['_DLB_FALLBACKPOLICY']._serialized_start=308
  _globals['_DLB_FALLBACKPOLICY']._serialized_end=388
