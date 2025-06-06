
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import substitution_format_string_pb2 as envoy_dot_config_dot_core_dot_v3_dot_substitution__format__string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n6envoy/extensions/access_loggers/stream/v3/stream.proto\x12)envoy.extensions.access_loggers.stream.v3\x1a\x35\x65nvoy/config/core/v3/substitution_format_string.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"v\n\x0fStdoutAccessLog\x12N\n\nlog_format\x18\x01 \x01(\x0b\x32..envoy.config.core.v3.SubstitutionFormatStringB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x42\x13\n\x11\x61\x63\x63\x65ss_log_format\"v\n\x0fStderrAccessLog\x12N\n\nlog_format\x18\x01 \x01(\x0b\x32..envoy.config.core.v3.SubstitutionFormatStringB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x42\x13\n\x11\x61\x63\x63\x65ss_log_formatB\xab\x01\n7io.envoyproxy.envoy.extensions.access_loggers.stream.v3B\x0bStreamProtoP\x01ZYgithub.com/envoyproxy/go-control-plane/envoy/extensions/access_loggers/stream/v3;streamv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.access_loggers.stream.v3.stream_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.access_loggers.stream.v3B\013StreamProtoP\001ZYgithub.com/envoyproxy/go-control-plane/envoy/extensions/access_loggers/stream/v3;streamv3\272\200\310\321\006\002\020\002'
  _STDOUTACCESSLOG.fields_by_name['log_format']._options = None
  _STDOUTACCESSLOG.fields_by_name['log_format']._serialized_options = b'\372B\005\212\001\002\020\001'
  _STDERRACCESSLOG.fields_by_name['log_format']._options = None
  _STDERRACCESSLOG.fields_by_name['log_format']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_STDOUTACCESSLOG']._serialized_start=212
  _globals['_STDOUTACCESSLOG']._serialized_end=330
  _globals['_STDERRACCESSLOG']._serialized_start=332
  _globals['_STDERRACCESSLOG']._serialized_end=450
