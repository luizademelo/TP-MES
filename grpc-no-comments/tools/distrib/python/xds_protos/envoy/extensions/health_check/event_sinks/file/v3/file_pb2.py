
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n<envoy/extensions/health_check/event_sinks/file/v3/file.proto\x12\x31\x65nvoy.extensions.health_check.event_sinks.file.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\";\n\x18HealthCheckEventFileSink\x12\x1f\n\x0e\x65vent_log_path\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xb7\x01\n?io.envoyproxy.envoy.extensions.health_check.event_sinks.file.v3B\tFileProtoP\x01Z_github.com/envoyproxy/go-control-plane/envoy/extensions/health_check/event_sinks/file/v3;filev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.health_check.event_sinks.file.v3.file_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.health_check.event_sinks.file.v3B\tFileProtoP\001Z_github.com/envoyproxy/go-control-plane/envoy/extensions/health_check/event_sinks/file/v3;filev3\272\200\310\321\006\002\020\002'
  _HEALTHCHECKEVENTFILESINK.fields_by_name['event_log_path']._options = None
  _HEALTHCHECKEVENTFILESINK.fields_by_name['event_log_path']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_HEALTHCHECKEVENTFILESINK']._serialized_start=171
  _globals['_HEALTHCHECKEVENTFILESINK']._serialized_end=230
