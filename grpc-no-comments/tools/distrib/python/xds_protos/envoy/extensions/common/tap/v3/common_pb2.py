
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.tap.v3 import common_pb2 as envoy_dot_config_dot_tap_dot_v3_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+envoy/extensions/common/tap/v3/common.proto\x12\x1e\x65nvoy.extensions.common.tap.v3\x1a envoy/config/tap/v3/common.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xe7\x01\n\x15\x43ommonExtensionConfig\x12\x43\n\x0c\x61\x64min_config\x18\x01 \x01(\x0b\x32+.envoy.extensions.common.tap.v3.AdminConfigH\x00\x12\x37\n\rstatic_config\x18\x02 \x01(\x0b\x32\x1e.envoy.config.tap.v3.TapConfigH\x00:<\x9a\xc5\x88\x1e\x37\n5envoy.config.common.tap.v2alpha.CommonExtensionConfigB\x12\n\x0b\x63onfig_type\x12\x03\xf8\x42\x01\"]\n\x0b\x41\x64minConfig\x12\x1a\n\tconfig_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01:2\x9a\xc5\x88\x1e-\n+envoy.config.common.tap.v2alpha.AdminConfigB\x92\x01\n,io.envoyproxy.envoy.extensions.common.tap.v3B\x0b\x43ommonProtoP\x01ZKgithub.com/envoyproxy/go-control-plane/envoy/extensions/common/tap/v3;tapv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.common.tap.v3.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n,io.envoyproxy.envoy.extensions.common.tap.v3B\013CommonProtoP\001ZKgithub.com/envoyproxy/go-control-plane/envoy/extensions/common/tap/v3;tapv3\272\200\310\321\006\002\020\002'
  _COMMONEXTENSIONCONFIG.oneofs_by_name['config_type']._options = None
  _COMMONEXTENSIONCONFIG.oneofs_by_name['config_type']._serialized_options = b'\370B\001'
  _COMMONEXTENSIONCONFIG._options = None
  _COMMONEXTENSIONCONFIG._serialized_options = b'\232\305\210\0367\n5envoy.config.common.tap.v2alpha.CommonExtensionConfig'
  _ADMINCONFIG.fields_by_name['config_id']._options = None
  _ADMINCONFIG.fields_by_name['config_id']._serialized_options = b'\372B\004r\002\020\001'
  _ADMINCONFIG._options = None
  _ADMINCONFIG._serialized_options = b'\232\305\210\036-\n+envoy.config.common.tap.v2alpha.AdminConfig'
  _globals['_COMMONEXTENSIONCONFIG']._serialized_start=205
  _globals['_COMMONEXTENSIONCONFIG']._serialized_end=436
  _globals['_ADMINCONFIG']._serialized_start=438
  _globals['_ADMINCONFIG']._serialized_end=531
