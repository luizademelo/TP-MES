
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.common.key_value.v3 import config_pb2 as envoy_dot_config_dot_common_dot_key__value_dot_v3_dot_config__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nJcontrib/envoy/extensions/config/v3alpha/kv_store_xds_delegate_config.proto\x12\x1f\x65nvoy.extensions.config.v3alpha\x1a-envoy/config/common/key_value/v3/config.proto\x1a\x1dudpa/annotations/status.proto\"w\n\x1eKeyValueStoreXdsDelegateConfig\x12U\n\x16key_value_store_config\x18\x01 \x01(\x0b\x32\x35.envoy.config.common.key_value.v3.KeyValueStoreConfigB\xa8\x01\n-io.envoyproxy.envoy.extensions.config.v3alphaB\x1dKvStoreXdsDelegateConfigProtoP\x01ZNgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/config/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.config.v3alpha.kv_store_xds_delegate_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n-io.envoyproxy.envoy.extensions.config.v3alphaB\035KvStoreXdsDelegateConfigProtoP\001ZNgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/config/v3alpha\272\200\310\321\006\002\020\002'
  _globals['_KEYVALUESTOREXDSDELEGATECONFIG']._serialized_start=189
  _globals['_KEYVALUESTOREXDSDELEGATECONFIG']._serialized_end=308
