
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import grpc_service_pb2 as envoy_dot_config_dot_core_dot_v3_dot_grpc__service__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nBenvoy/extensions/stat_sinks/open_telemetry/v3/open_telemetry.proto\x12-envoy.extensions.stat_sinks.open_telemetry.v3\x1a\'envoy/config/core/v3/grpc_service.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xbd\x02\n\nSinkConfig\x12\x43\n\x0cgrpc_service\x18\x01 \x01(\x0b\x32!.envoy.config.core.v3.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12!\n\x19report_counters_as_deltas\x18\x02 \x01(\x08\x12#\n\x1breport_histograms_as_deltas\x18\x03 \x01(\x08\x12;\n\x17\x65mit_tags_as_attributes\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12:\n\x16use_tag_extracted_name\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x0e\n\x06prefix\x18\x06 \x01(\tB\x19\n\x12protocol_specifier\x12\x03\xf8\x42\x01\x42\xc2\x01\n;io.envoyproxy.envoy.extensions.stat_sinks.open_telemetry.v3B\x12OpenTelemetryProtoP\x01Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/stat_sinks/open_telemetry/v3;open_telemetryv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.stat_sinks.open_telemetry.v3.open_telemetry_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n;io.envoyproxy.envoy.extensions.stat_sinks.open_telemetry.v3B\022OpenTelemetryProtoP\001Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/stat_sinks/open_telemetry/v3;open_telemetryv3\272\200\310\321\006\002\020\002'
  _SINKCONFIG.oneofs_by_name['protocol_specifier']._options = None
  _SINKCONFIG.oneofs_by_name['protocol_specifier']._serialized_options = b'\370B\001'
  _SINKCONFIG.fields_by_name['grpc_service']._options = None
  _SINKCONFIG.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_SINKCONFIG']._serialized_start=247
  _globals['_SINKCONFIG']._serialized_end=564
