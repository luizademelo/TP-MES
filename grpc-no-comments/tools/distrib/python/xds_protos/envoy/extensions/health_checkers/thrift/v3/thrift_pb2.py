
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.filters.network.thrift_proxy.v3 import thrift_proxy_pb2 as envoy_dot_extensions_dot_filters_dot_network_dot_thrift__proxy_dot_v3_dot_thrift__proxy__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7envoy/extensions/health_checkers/thrift/v3/thrift.proto\x12*envoy.extensions.health_checkers.thrift.v3\x1a\x43\x65nvoy/extensions/filters/network/thrift_proxy/v3/thrift_proxy.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xe0\x01\n\x06Thrift\x12\x1c\n\x0bmethod_name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\\\n\ttransport\x18\x02 \x01(\x0e\x32?.envoy.extensions.filters.network.thrift_proxy.v3.TransportTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12Z\n\x08protocol\x18\x03 \x01(\x0e\x32>.envoy.extensions.filters.network.thrift_proxy.v3.ProtocolTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x42\xad\x01\n8io.envoyproxy.envoy.extensions.health_checkers.thrift.v3B\x0bThriftProtoP\x01ZZgithub.com/envoyproxy/go-control-plane/envoy/extensions/health_checkers/thrift/v3;thriftv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.health_checkers.thrift.v3.thrift_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.extensions.health_checkers.thrift.v3B\013ThriftProtoP\001ZZgithub.com/envoyproxy/go-control-plane/envoy/extensions/health_checkers/thrift/v3;thriftv3\272\200\310\321\006\002\020\002'
  _THRIFT.fields_by_name['method_name']._options = None
  _THRIFT.fields_by_name['method_name']._serialized_options = b'\372B\004r\002\020\001'
  _THRIFT.fields_by_name['transport']._options = None
  _THRIFT.fields_by_name['transport']._serialized_options = b'\372B\005\202\001\002\020\001'
  _THRIFT.fields_by_name['protocol']._options = None
  _THRIFT.fields_by_name['protocol']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_THRIFT']._serialized_start=229
  _globals['_THRIFT']._serialized_end=453
