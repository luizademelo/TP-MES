
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import http_uri_pb2 as envoy_dot_config_dot_core_dot_v3_dot_http__uri__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/config/core/v3/http_service.proto\x12\x14\x65nvoy.config.core.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a#envoy/config/core/v3/http_uri.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x92\x01\n\x0bHttpService\x12/\n\x08http_uri\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.HttpUri\x12R\n\x16request_headers_to_add\x18\x02 \x03(\x0b\x32\'.envoy.config.core.v3.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x42\x84\x01\n\"io.envoyproxy.envoy.config.core.v3B\x10HttpServiceProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.http_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\020HttpServiceProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
  _HTTPSERVICE.fields_by_name['request_headers_to_add']._options = None
  _HTTPSERVICE.fields_by_name['request_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _globals['_HTTPSERVICE']._serialized_start=192
  _globals['_HTTPSERVICE']._serialized_end=338
