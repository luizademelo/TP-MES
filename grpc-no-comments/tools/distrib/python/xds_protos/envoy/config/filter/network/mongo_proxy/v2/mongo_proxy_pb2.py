
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.filter.fault.v2 import fault_pb2 as envoy_dot_config_dot_filter_dot_fault_dot_v2_dot_fault__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n<envoy/config/filter/network/mongo_proxy/v2/mongo_proxy.proto\x12*envoy.config.filter.network.mongo_proxy.v2\x1a(envoy/config/filter/fault/v2/fault.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x96\x01\n\nMongoProxy\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x12\n\naccess_log\x18\x02 \x01(\t\x12\x37\n\x05\x64\x65lay\x18\x03 \x01(\x0b\x32(.envoy.config.filter.fault.v2.FaultDelay\x12\x1d\n\x15\x65mit_dynamic_metadata\x18\x04 \x01(\x08\x42\xed\x01\n8io.envoyproxy.envoy.config.filter.network.mongo_proxy.v2B\x0fMongoProxyProtoP\x01Z_github.com/envoyproxy/go-control-plane/envoy/config/filter/network/mongo_proxy/v2;mongo_proxyv2\xf2\x98\xfe\x8f\x05\x31\x12/envoy.extensions.filters.network.mongo_proxy.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.network.mongo_proxy.v2.mongo_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.config.filter.network.mongo_proxy.v2B\017MongoProxyProtoP\001Z_github.com/envoyproxy/go-control-plane/envoy/config/filter/network/mongo_proxy/v2;mongo_proxyv2\362\230\376\217\0051\022/envoy.extensions.filters.network.mongo_proxy.v3\272\200\310\321\006\002\020\001'
  _MONGOPROXY.fields_by_name['stat_prefix']._options = None
  _MONGOPROXY.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002 \001'
  _globals['_MONGOPROXY']._serialized_start=239
  _globals['_MONGOPROXY']._serialized_end=389
