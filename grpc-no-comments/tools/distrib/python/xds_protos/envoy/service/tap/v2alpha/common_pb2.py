
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from envoy.api.v2.core import grpc_service_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__service__pb2
from envoy.api.v2.route import route_components_pb2 as envoy_dot_api_dot_v2_dot_route_dot_route__components__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/service/tap/v2alpha/common.proto\x12\x19\x65nvoy.service.tap.v2alpha\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a$envoy/api/v2/core/grpc_service.proto\x1a)envoy/api/v2/route/route_components.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xe2\x01\n\tTapConfig\x12I\n\x0cmatch_config\x18\x01 \x01(\x0b\x32).envoy.service.tap.v2alpha.MatchPredicateB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12H\n\routput_config\x18\x02 \x01(\x0b\x32\'.envoy.service.tap.v2alpha.OutputConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12@\n\x0btap_enabled\x18\x03 \x01(\x0b\x32+.envoy.api.v2.core.RuntimeFractionalPercent\"\xac\x05\n\x0eMatchPredicate\x12\x46\n\x08or_match\x18\x01 \x01(\x0b\x32\x32.envoy.service.tap.v2alpha.MatchPredicate.MatchSetH\x00\x12G\n\tand_match\x18\x02 \x01(\x0b\x32\x32.envoy.service.tap.v2alpha.MatchPredicate.MatchSetH\x00\x12>\n\tnot_match\x18\x03 \x01(\x0b\x32).envoy.service.tap.v2alpha.MatchPredicateH\x00\x12\x1c\n\tany_match\x18\x04 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12Q\n\x1ahttp_request_headers_match\x18\x05 \x01(\x0b\x32+.envoy.service.tap.v2alpha.HttpHeadersMatchH\x00\x12R\n\x1bhttp_request_trailers_match\x18\x06 \x01(\x0b\x32+.envoy.service.tap.v2alpha.HttpHeadersMatchH\x00\x12R\n\x1bhttp_response_headers_match\x18\x07 \x01(\x0b\x32+.envoy.service.tap.v2alpha.HttpHeadersMatchH\x00\x12S\n\x1chttp_response_trailers_match\x18\x08 \x01(\x0b\x32+.envoy.service.tap.v2alpha.HttpHeadersMatchH\x00\x1aN\n\x08MatchSet\x12\x42\n\x05rules\x18\x01 \x03(\x0b\x32).envoy.service.tap.v2alpha.MatchPredicateB\x08\xfa\x42\x05\x92\x01\x02\x08\x02\x42\x0b\n\x04rule\x12\x03\xf8\x42\x01\"F\n\x10HttpHeadersMatch\x12\x32\n\x07headers\x18\x01 \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcher\"\xdd\x01\n\x0cOutputConfig\x12@\n\x05sinks\x18\x01 \x03(\x0b\x32%.envoy.service.tap.v2alpha.OutputSinkB\n\xfa\x42\x07\x92\x01\x04\x08\x01\x10\x01\x12;\n\x15max_buffered_rx_bytes\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12;\n\x15max_buffered_tx_bytes\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x11\n\tstreaming\x18\x04 \x01(\x08\"\xc2\x03\n\nOutputSink\x12\x46\n\x06\x66ormat\x18\x01 \x01(\x0e\x32,.envoy.service.tap.v2alpha.OutputSink.FormatB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12H\n\x0fstreaming_admin\x18\x02 \x01(\x0b\x32-.envoy.service.tap.v2alpha.StreamingAdminSinkH\x00\x12\x41\n\x0c\x66ile_per_tap\x18\x03 \x01(\x0b\x32).envoy.service.tap.v2alpha.FilePerTapSinkH\x00\x12\x46\n\x0estreaming_grpc\x18\x04 \x01(\x0b\x32,.envoy.service.tap.v2alpha.StreamingGrpcSinkH\x00\"~\n\x06\x46ormat\x12\x16\n\x12JSON_BODY_AS_BYTES\x10\x00\x12\x17\n\x13JSON_BODY_AS_STRING\x10\x01\x12\x10\n\x0cPROTO_BINARY\x10\x02\x12!\n\x1dPROTO_BINARY_LENGTH_DELIMITED\x10\x03\x12\x0e\n\nPROTO_TEXT\x10\x04\x42\x17\n\x10output_sink_type\x12\x03\xf8\x42\x01\"\x14\n\x12StreamingAdminSink\".\n\x0e\x46ilePerTapSink\x12\x1c\n\x0bpath_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\"c\n\x11StreamingGrpcSink\x12\x0e\n\x06tap_id\x18\x01 \x01(\t\x12>\n\x0cgrpc_service\x18\x02 \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\x9d\x01\n\'io.envoyproxy.envoy.service.tap.v2alphaB\x0b\x43ommonProtoP\x01Z@github.com/envoyproxy/go-control-plane/envoy/service/tap/v2alpha\xf2\x98\xfe\x8f\x05\x15\x12\x13\x65nvoy.config.tap.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.tap.v2alpha.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\'io.envoyproxy.envoy.service.tap.v2alphaB\013CommonProtoP\001Z@github.com/envoyproxy/go-control-plane/envoy/service/tap/v2alpha\362\230\376\217\005\025\022\023envoy.config.tap.v3\272\200\310\321\006\002\020\001'
  _TAPCONFIG.fields_by_name['match_config']._options = None
  _TAPCONFIG.fields_by_name['match_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _TAPCONFIG.fields_by_name['output_config']._options = None
  _TAPCONFIG.fields_by_name['output_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _MATCHPREDICATE_MATCHSET.fields_by_name['rules']._options = None
  _MATCHPREDICATE_MATCHSET.fields_by_name['rules']._serialized_options = b'\372B\005\222\001\002\010\002'
  _MATCHPREDICATE.oneofs_by_name['rule']._options = None
  _MATCHPREDICATE.oneofs_by_name['rule']._serialized_options = b'\370B\001'
  _MATCHPREDICATE.fields_by_name['any_match']._options = None
  _MATCHPREDICATE.fields_by_name['any_match']._serialized_options = b'\372B\004j\002\010\001'
  _OUTPUTCONFIG.fields_by_name['sinks']._options = None
  _OUTPUTCONFIG.fields_by_name['sinks']._serialized_options = b'\372B\007\222\001\004\010\001\020\001'
  _OUTPUTSINK.oneofs_by_name['output_sink_type']._options = None
  _OUTPUTSINK.oneofs_by_name['output_sink_type']._serialized_options = b'\370B\001'
  _OUTPUTSINK.fields_by_name['format']._options = None
  _OUTPUTSINK.fields_by_name['format']._serialized_options = b'\372B\005\202\001\002\020\001'
  _FILEPERTAPSINK.fields_by_name['path_prefix']._options = None
  _FILEPERTAPSINK.fields_by_name['path_prefix']._serialized_options = b'\372B\004r\002 \001'
  _STREAMINGGRPCSINK.fields_by_name['grpc_service']._options = None
  _STREAMINGGRPCSINK.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_TAPCONFIG']._serialized_start=301
  _globals['_TAPCONFIG']._serialized_end=527
  _globals['_MATCHPREDICATE']._serialized_start=530
  _globals['_MATCHPREDICATE']._serialized_end=1214
  _globals['_MATCHPREDICATE_MATCHSET']._serialized_start=1123
  _globals['_MATCHPREDICATE_MATCHSET']._serialized_end=1201
  _globals['_HTTPHEADERSMATCH']._serialized_start=1216
  _globals['_HTTPHEADERSMATCH']._serialized_end=1286
  _globals['_OUTPUTCONFIG']._serialized_start=1289
  _globals['_OUTPUTCONFIG']._serialized_end=1510
  _globals['_OUTPUTSINK']._serialized_start=1513
  _globals['_OUTPUTSINK']._serialized_end=1963
  _globals['_OUTPUTSINK_FORMAT']._serialized_start=1812
  _globals['_OUTPUTSINK_FORMAT']._serialized_end=1938
  _globals['_STREAMINGADMINSINK']._serialized_start=1965
  _globals['_STREAMINGADMINSINK']._serialized_end=1985
  _globals['_FILEPERTAPSINK']._serialized_start=1987
  _globals['_FILEPERTAPSINK']._serialized_end=2033
  _globals['_STREAMINGGRPCSINK']._serialized_start=2035
  _globals['_STREAMINGGRPCSINK']._serialized_end=2134
