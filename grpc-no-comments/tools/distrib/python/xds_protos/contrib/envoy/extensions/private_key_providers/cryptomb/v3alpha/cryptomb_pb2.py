
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import sensitive_pb2 as udpa_dot_annotations_dot_sensitive__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nNcontrib/envoy/extensions/private_key_providers/cryptomb/v3alpha/cryptomb.proto\x12\x37\x65nvoy.extensions.private_key_providers.cryptomb.v3alpha\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1egoogle/protobuf/duration.proto\x1a udpa/annotations/sensitive.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x9e\x01\n\x1e\x43ryptoMbPrivateKeyMethodConfig\x12=\n\x0bprivate_key\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceB\x06\xb8\xb7\x8b\xa4\x02\x01\x12=\n\npoll_delay\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0e\xfa\x42\x0b\xaa\x01\x08\x08\x01\x32\x04\x10\xc0\x84=B\xc8\x01\nEio.envoyproxy.envoy.extensions.private_key_providers.cryptomb.v3alphaB\rCryptombProtoP\x01Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/private_key_providers/cryptomb/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.private_key_providers.cryptomb.v3alpha.cryptomb_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.extensions.private_key_providers.cryptomb.v3alphaB\rCryptombProtoP\001Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/private_key_providers/cryptomb/v3alpha\272\200\310\321\006\002\020\002'
  _CRYPTOMBPRIVATEKEYMETHODCONFIG.fields_by_name['private_key']._options = None
  _CRYPTOMBPRIVATEKEYMETHODCONFIG.fields_by_name['private_key']._serialized_options = b'\270\267\213\244\002\001'
  _CRYPTOMBPRIVATEKEYMETHODCONFIG.fields_by_name['poll_delay']._options = None
  _CRYPTOMBPRIVATEKEYMETHODCONFIG.fields_by_name['poll_delay']._serialized_options = b'\372B\013\252\001\010\010\0012\004\020\300\204='
  _globals['_CRYPTOMBPRIVATEKEYMETHODCONFIG']._serialized_start=295
  _globals['_CRYPTOMBPRIVATEKEYMETHODCONFIG']._serialized_end=453
