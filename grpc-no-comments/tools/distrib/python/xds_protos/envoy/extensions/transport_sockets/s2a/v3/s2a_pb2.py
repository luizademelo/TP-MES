
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3envoy/extensions/transport_sockets/s2a/v3/s2a.proto\x12)envoy.extensions.transport_sockets.s2a.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"0\n\x10S2AConfiguration\x12\x1c\n\x0bs2a_address\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xa5\x01\n7io.envoyproxy.envoy.extensions.transport_sockets.s2a.v3B\x08S2aProtoP\x01ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/s2a/v3;s2av3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.s2a.v3.s2a_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.transport_sockets.s2a.v3B\010S2aProtoP\001ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/s2a/v3;s2av3\272\200\310\321\006\002\020\002'
  _S2ACONFIGURATION.fields_by_name['s2a_address']._options = None
  _S2ACONFIGURATION.fields_by_name['s2a_address']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_S2ACONFIGURATION']._serialized_start=154
  _globals['_S2ACONFIGURATION']._serialized_end=202
