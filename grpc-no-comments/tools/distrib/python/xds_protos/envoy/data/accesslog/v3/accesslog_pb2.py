
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/data/accesslog/v3/accesslog.proto\x12\x17\x65nvoy.data.accesslog.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x19google/protobuf/any.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xd8\x01\n\x11TCPAccessLogEntry\x12\x43\n\x11\x63ommon_properties\x18\x01 \x01(\x0b\x32(.envoy.data.accesslog.v3.AccessLogCommon\x12L\n\x15\x63onnection_properties\x18\x02 \x01(\x0b\x32-.envoy.data.accesslog.v3.ConnectionProperties:0\x9a\xc5\x88\x1e+\n)envoy.data.accesslog.v2.TCPAccessLogEntry\"\xba\x03\n\x12HTTPAccessLogEntry\x12\x43\n\x11\x63ommon_properties\x18\x01 \x01(\x0b\x32(.envoy.data.accesslog.v3.AccessLogCommon\x12Q\n\x10protocol_version\x18\x02 \x01(\x0e\x32\x37.envoy.data.accesslog.v3.HTTPAccessLogEntry.HTTPVersion\x12?\n\x07request\x18\x03 \x01(\x0b\x32..envoy.data.accesslog.v3.HTTPRequestProperties\x12\x41\n\x08response\x18\x04 \x01(\x0b\x32/.envoy.data.accesslog.v3.HTTPResponseProperties\"U\n\x0bHTTPVersion\x12\x18\n\x14PROTOCOL_UNSPECIFIED\x10\x00\x12\n\n\x06HTTP10\x10\x01\x12\n\n\x06HTTP11\x10\x02\x12\t\n\x05HTTP2\x10\x03\x12\t\n\x05HTTP3\x10\x04:1\x9a\xc5\x88\x1e,\n*envoy.data.accesslog.v2.HTTPAccessLogEntry\"w\n\x14\x43onnectionProperties\x12\x16\n\x0ereceived_bytes\x18\x01 \x01(\x04\x12\x12\n\nsent_bytes\x18\x02 \x01(\x04:3\x9a\xc5\x88\x1e.\n,envoy.data.accesslog.v2.ConnectionProperties\"\xb3\x0f\n\x0f\x41\x63\x63\x65ssLogCommon\x12,\n\x0bsample_rate\x18\x01 \x01(\x01\x42\x17\xfa\x42\x14\x12\x12\x19\x00\x00\x00\x00\x00\x00\xf0?!\x00\x00\x00\x00\x00\x00\x00\x00\x12@\n\x19\x64ownstream_remote_address\x18\x02 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12?\n\x18\x64ownstream_local_address\x18\x03 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12>\n\x0etls_properties\x18\x04 \x01(\x0b\x32&.envoy.data.accesslog.v3.TLSProperties\x12.\n\nstart_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x14time_to_last_rx_byte\x18\x06 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x41\n\x1etime_to_first_upstream_tx_byte\x18\x07 \x01(\x0b\x32\x19.google.protobuf.Duration\x12@\n\x1dtime_to_last_upstream_tx_byte\x18\x08 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x41\n\x1etime_to_first_upstream_rx_byte\x18\t \x01(\x0b\x32\x19.google.protobuf.Duration\x12@\n\x1dtime_to_last_upstream_rx_byte\x18\n \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x43\n time_to_first_downstream_tx_byte\x18\x0b \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x42\n\x1ftime_to_last_downstream_tx_byte\x18\x0c \x01(\x0b\x32\x19.google.protobuf.Duration\x12>\n\x17upstream_remote_address\x18\r \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12=\n\x16upstream_local_address\x18\x0e \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12\x18\n\x10upstream_cluster\x18\x0f \x01(\t\x12>\n\x0eresponse_flags\x18\x10 \x01(\x0b\x32&.envoy.data.accesslog.v3.ResponseFlags\x12\x30\n\x08metadata\x18\x11 \x01(\x0b\x32\x1e.envoy.config.core.v3.Metadata\x12)\n!upstream_transport_failure_reason\x18\x12 \x01(\t\x12\x12\n\nroute_name\x18\x13 \x01(\t\x12G\n downstream_direct_remote_address\x18\x14 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12^\n\x14\x66ilter_state_objects\x18\x15 \x03(\x0b\x32@.envoy.data.accesslog.v3.AccessLogCommon.FilterStateObjectsEntry\x12M\n\x0b\x63ustom_tags\x18\x16 \x03(\x0b\x32\x38.envoy.data.accesslog.v3.AccessLogCommon.CustomTagsEntry\x12+\n\x08\x64uration\x18\x17 \x01(\x0b\x32\x19.google.protobuf.Duration\x12&\n\x1eupstream_request_attempt_count\x18\x18 \x01(\r\x12&\n\x1e\x63onnection_termination_details\x18\x19 \x01(\t\x12\x11\n\tstream_id\x18\x1a \x01(\t\x12+\n\x16intermediate_log_entry\x18\x1b \x01(\x08\x42\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12+\n#downstream_transport_failure_reason\x18\x1c \x01(\t\x12\"\n\x1a\x64ownstream_wire_bytes_sent\x18\x1d \x01(\x04\x12&\n\x1e\x64ownstream_wire_bytes_received\x18\x1e \x01(\x04\x12 \n\x18upstream_wire_bytes_sent\x18\x1f \x01(\x04\x12$\n\x1cupstream_wire_bytes_received\x18  \x01(\x04\x12?\n\x0f\x61\x63\x63\x65ss_log_type\x18! \x01(\x0e\x32&.envoy.data.accesslog.v3.AccessLogType\x1aO\n\x17\x46ilterStateObjectsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any:\x02\x38\x01\x1a\x31\n\x0f\x43ustomTagsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01:.\x9a\xc5\x88\x1e)\n\'envoy.data.accesslog.v2.AccessLogCommon\"\xb9\t\n\rResponseFlags\x12 \n\x18\x66\x61iled_local_healthcheck\x18\x01 \x01(\x08\x12\x1b\n\x13no_healthy_upstream\x18\x02 \x01(\x08\x12 \n\x18upstream_request_timeout\x18\x03 \x01(\x08\x12\x13\n\x0blocal_reset\x18\x04 \x01(\x08\x12\x1d\n\x15upstream_remote_reset\x18\x05 \x01(\x08\x12#\n\x1bupstream_connection_failure\x18\x06 \x01(\x08\x12\'\n\x1fupstream_connection_termination\x18\x07 \x01(\x08\x12\x19\n\x11upstream_overflow\x18\x08 \x01(\x08\x12\x16\n\x0eno_route_found\x18\t \x01(\x08\x12\x16\n\x0e\x64\x65lay_injected\x18\n \x01(\x08\x12\x16\n\x0e\x66\x61ult_injected\x18\x0b \x01(\x08\x12\x14\n\x0crate_limited\x18\x0c \x01(\x08\x12Q\n\x14unauthorized_details\x18\r \x01(\x0b\x32\x33.envoy.data.accesslog.v3.ResponseFlags.Unauthorized\x12 \n\x18rate_limit_service_error\x18\x0e \x01(\x08\x12)\n!downstream_connection_termination\x18\x0f \x01(\x08\x12%\n\x1dupstream_retry_limit_exceeded\x18\x10 \x01(\x08\x12\x1b\n\x13stream_idle_timeout\x18\x11 \x01(\x08\x12%\n\x1dinvalid_envoy_request_headers\x18\x12 \x01(\x08\x12!\n\x19\x64ownstream_protocol_error\x18\x13 \x01(\x08\x12,\n$upstream_max_stream_duration_reached\x18\x14 \x01(\x08\x12\"\n\x1aresponse_from_cache_filter\x18\x15 \x01(\x08\x12\x1e\n\x16no_filter_config_found\x18\x16 \x01(\x08\x12\x18\n\x10\x64uration_timeout\x18\x17 \x01(\x08\x12\x1f\n\x17upstream_protocol_error\x18\x18 \x01(\x08\x12\x18\n\x10no_cluster_found\x18\x19 \x01(\x08\x12\x18\n\x10overload_manager\x18\x1a \x01(\x08\x12\x1e\n\x16\x64ns_resolution_failure\x18\x1b \x01(\x08\x12\x1f\n\x17\x64ownstream_remote_reset\x18\x1c \x01(\x08\x1a\xcd\x01\n\x0cUnauthorized\x12J\n\x06reason\x18\x01 \x01(\x0e\x32:.envoy.data.accesslog.v3.ResponseFlags.Unauthorized.Reason\"6\n\x06Reason\x12\x16\n\x12REASON_UNSPECIFIED\x10\x00\x12\x14\n\x10\x45XTERNAL_SERVICE\x10\x01:9\x9a\xc5\x88\x1e\x34\n2envoy.data.accesslog.v2.ResponseFlags.Unauthorized:,\x9a\xc5\x88\x1e\'\n%envoy.data.accesslog.v2.ResponseFlags\"\x99\x07\n\rTLSProperties\x12\x46\n\x0btls_version\x18\x01 \x01(\x0e\x32\x31.envoy.data.accesslog.v3.TLSProperties.TLSVersion\x12\x36\n\x10tls_cipher_suite\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x18\n\x10tls_sni_hostname\x18\x03 \x01(\t\x12\x62\n\x1clocal_certificate_properties\x18\x04 \x01(\x0b\x32<.envoy.data.accesslog.v3.TLSProperties.CertificateProperties\x12\x61\n\x1bpeer_certificate_properties\x18\x05 \x01(\x0b\x32<.envoy.data.accesslog.v3.TLSProperties.CertificateProperties\x12\x16\n\x0etls_session_id\x18\x06 \x01(\t\x12\x17\n\x0fja3_fingerprint\x18\x07 \x01(\t\x1a\xee\x02\n\x15\x43\x65rtificateProperties\x12\x65\n\x10subject_alt_name\x18\x01 \x03(\x0b\x32K.envoy.data.accesslog.v3.TLSProperties.CertificateProperties.SubjectAltName\x12\x0f\n\x07subject\x18\x02 \x01(\t\x12\x0e\n\x06issuer\x18\x03 \x01(\t\x1a\x88\x01\n\x0eSubjectAltName\x12\r\n\x03uri\x18\x01 \x01(\tH\x00\x12\r\n\x03\x64ns\x18\x02 \x01(\tH\x00:Q\x9a\xc5\x88\x1eL\nJenvoy.data.accesslog.v2.TLSProperties.CertificateProperties.SubjectAltNameB\x05\n\x03san:B\x9a\xc5\x88\x1e=\n;envoy.data.accesslog.v2.TLSProperties.CertificateProperties\"W\n\nTLSVersion\x12\x17\n\x13VERSION_UNSPECIFIED\x10\x00\x12\t\n\x05TLSv1\x10\x01\x12\x0b\n\x07TLSv1_1\x10\x02\x12\x0b\n\x07TLSv1_2\x10\x03\x12\x0b\n\x07TLSv1_3\x10\x04:,\x9a\xc5\x88\x1e\'\n%envoy.data.accesslog.v2.TLSProperties\"\xf5\x04\n\x15HTTPRequestProperties\x12\x45\n\x0erequest_method\x18\x01 \x01(\x0e\x32#.envoy.config.core.v3.RequestMethodB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x0e\n\x06scheme\x18\x02 \x01(\t\x12\x11\n\tauthority\x18\x03 \x01(\t\x12*\n\x04port\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x0c\n\x04path\x18\x05 \x01(\t\x12\x12\n\nuser_agent\x18\x06 \x01(\t\x12\x0f\n\x07referer\x18\x07 \x01(\t\x12\x15\n\rforwarded_for\x18\x08 \x01(\t\x12\x12\n\nrequest_id\x18\t \x01(\t\x12\x15\n\roriginal_path\x18\n \x01(\t\x12\x1d\n\x15request_headers_bytes\x18\x0b \x01(\x04\x12\x1a\n\x12request_body_bytes\x18\x0c \x01(\x04\x12[\n\x0frequest_headers\x18\r \x03(\x0b\x32\x42.envoy.data.accesslog.v3.HTTPRequestProperties.RequestHeadersEntry\x12\"\n\x1aupstream_header_bytes_sent\x18\x0e \x01(\x04\x12(\n downstream_header_bytes_received\x18\x0f \x01(\x04\x1a\x35\n\x13RequestHeadersEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01:4\x9a\xc5\x88\x1e/\n-envoy.data.accesslog.v2.HTTPRequestProperties\"\xe1\x04\n\x16HTTPResponseProperties\x12\x33\n\rresponse_code\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x1e\n\x16response_headers_bytes\x18\x02 \x01(\x04\x12\x1b\n\x13response_body_bytes\x18\x03 \x01(\x04\x12^\n\x10response_headers\x18\x04 \x03(\x0b\x32\x44.envoy.data.accesslog.v3.HTTPResponseProperties.ResponseHeadersEntry\x12`\n\x11response_trailers\x18\x05 \x03(\x0b\x32\x45.envoy.data.accesslog.v3.HTTPResponseProperties.ResponseTrailersEntry\x12\x1d\n\x15response_code_details\x18\x06 \x01(\t\x12&\n\x1eupstream_header_bytes_received\x18\x07 \x01(\x04\x12$\n\x1c\x64ownstream_header_bytes_sent\x18\x08 \x01(\x04\x1a\x36\n\x14ResponseHeadersEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x1a\x37\n\x15ResponseTrailersEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01:5\x9a\xc5\x88\x1e\x30\n.envoy.data.accesslog.v2.HTTPResponseProperties*\xcb\x02\n\rAccessLogType\x12\n\n\x06NotSet\x10\x00\x12\x18\n\x14TcpUpstreamConnected\x10\x01\x12\x0f\n\x0bTcpPeriodic\x10\x02\x12\x14\n\x10TcpConnectionEnd\x10\x03\x12\x13\n\x0f\x44ownstreamStart\x10\x04\x12\x16\n\x12\x44ownstreamPeriodic\x10\x05\x12\x11\n\rDownstreamEnd\x10\x06\x12\x15\n\x11UpstreamPoolReady\x10\x07\x12\x14\n\x10UpstreamPeriodic\x10\x08\x12\x0f\n\x0bUpstreamEnd\x10\t\x12+\n\'DownstreamTunnelSuccessfullyEstablished\x10\n\x12\x1e\n\x1aUdpTunnelUpstreamConnected\x10\x0b\x12\x0f\n\x0bUdpPeriodic\x10\x0c\x12\x11\n\rUdpSessionEnd\x10\rB\x8d\x01\n%io.envoyproxy.envoy.data.accesslog.v3B\x0e\x41\x63\x63\x65sslogProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/data/accesslog/v3;accesslogv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.data.accesslog.v3.accesslog_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.data.accesslog.v3B\016AccesslogProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/data/accesslog/v3;accesslogv3\272\200\310\321\006\002\020\002'
  _TCPACCESSLOGENTRY._options = None
  _TCPACCESSLOGENTRY._serialized_options = b'\232\305\210\036+\n)envoy.data.accesslog.v2.TCPAccessLogEntry'
  _HTTPACCESSLOGENTRY._options = None
  _HTTPACCESSLOGENTRY._serialized_options = b'\232\305\210\036,\n*envoy.data.accesslog.v2.HTTPAccessLogEntry'
  _CONNECTIONPROPERTIES._options = None
  _CONNECTIONPROPERTIES._serialized_options = b'\232\305\210\036.\n,envoy.data.accesslog.v2.ConnectionProperties'
  _ACCESSLOGCOMMON_FILTERSTATEOBJECTSENTRY._options = None
  _ACCESSLOGCOMMON_FILTERSTATEOBJECTSENTRY._serialized_options = b'8\001'
  _ACCESSLOGCOMMON_CUSTOMTAGSENTRY._options = None
  _ACCESSLOGCOMMON_CUSTOMTAGSENTRY._serialized_options = b'8\001'
  _ACCESSLOGCOMMON.fields_by_name['sample_rate']._options = None
  _ACCESSLOGCOMMON.fields_by_name['sample_rate']._serialized_options = b'\372B\024\022\022\031\000\000\000\000\000\000\360?!\000\000\000\000\000\000\000\000'
  _ACCESSLOGCOMMON.fields_by_name['intermediate_log_entry']._options = None
  _ACCESSLOGCOMMON.fields_by_name['intermediate_log_entry']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _ACCESSLOGCOMMON._options = None
  _ACCESSLOGCOMMON._serialized_options = b'\232\305\210\036)\n\'envoy.data.accesslog.v2.AccessLogCommon'
  _RESPONSEFLAGS_UNAUTHORIZED._options = None
  _RESPONSEFLAGS_UNAUTHORIZED._serialized_options = b'\232\305\210\0364\n2envoy.data.accesslog.v2.ResponseFlags.Unauthorized'
  _RESPONSEFLAGS._options = None
  _RESPONSEFLAGS._serialized_options = b'\232\305\210\036\'\n%envoy.data.accesslog.v2.ResponseFlags'
  _TLSPROPERTIES_CERTIFICATEPROPERTIES_SUBJECTALTNAME._options = None
  _TLSPROPERTIES_CERTIFICATEPROPERTIES_SUBJECTALTNAME._serialized_options = b'\232\305\210\036L\nJenvoy.data.accesslog.v2.TLSProperties.CertificateProperties.SubjectAltName'
  _TLSPROPERTIES_CERTIFICATEPROPERTIES._options = None
  _TLSPROPERTIES_CERTIFICATEPROPERTIES._serialized_options = b'\232\305\210\036=\n;envoy.data.accesslog.v2.TLSProperties.CertificateProperties'
  _TLSPROPERTIES._options = None
  _TLSPROPERTIES._serialized_options = b'\232\305\210\036\'\n%envoy.data.accesslog.v2.TLSProperties'
  _HTTPREQUESTPROPERTIES_REQUESTHEADERSENTRY._options = None
  _HTTPREQUESTPROPERTIES_REQUESTHEADERSENTRY._serialized_options = b'8\001'
  _HTTPREQUESTPROPERTIES.fields_by_name['request_method']._options = None
  _HTTPREQUESTPROPERTIES.fields_by_name['request_method']._serialized_options = b'\372B\005\202\001\002\020\001'
  _HTTPREQUESTPROPERTIES._options = None
  _HTTPREQUESTPROPERTIES._serialized_options = b'\232\305\210\036/\n-envoy.data.accesslog.v2.HTTPRequestProperties'
  _HTTPRESPONSEPROPERTIES_RESPONSEHEADERSENTRY._options = None
  _HTTPRESPONSEPROPERTIES_RESPONSEHEADERSENTRY._serialized_options = b'8\001'
  _HTTPRESPONSEPROPERTIES_RESPONSETRAILERSENTRY._options = None
  _HTTPRESPONSEPROPERTIES_RESPONSETRAILERSENTRY._serialized_options = b'8\001'
  _HTTPRESPONSEPROPERTIES._options = None
  _HTTPRESPONSEPROPERTIES._serialized_options = b'\232\305\210\0360\n.envoy.data.accesslog.v2.HTTPResponseProperties'
  _globals['_ACCESSLOGTYPE']._serialized_start=6529
  _globals['_ACCESSLOGTYPE']._serialized_end=6860
  _globals['_TCPACCESSLOGENTRY']._serialized_start=390
  _globals['_TCPACCESSLOGENTRY']._serialized_end=606
  _globals['_HTTPACCESSLOGENTRY']._serialized_start=609
  _globals['_HTTPACCESSLOGENTRY']._serialized_end=1051
  _globals['_HTTPACCESSLOGENTRY_HTTPVERSION']._serialized_start=915
  _globals['_HTTPACCESSLOGENTRY_HTTPVERSION']._serialized_end=1000
  _globals['_CONNECTIONPROPERTIES']._serialized_start=1053
  _globals['_CONNECTIONPROPERTIES']._serialized_end=1172
  _globals['_ACCESSLOGCOMMON']._serialized_start=1175
  _globals['_ACCESSLOGCOMMON']._serialized_end=3146
  _globals['_ACCESSLOGCOMMON_FILTERSTATEOBJECTSENTRY']._serialized_start=2968
  _globals['_ACCESSLOGCOMMON_FILTERSTATEOBJECTSENTRY']._serialized_end=3047
  _globals['_ACCESSLOGCOMMON_CUSTOMTAGSENTRY']._serialized_start=3049
  _globals['_ACCESSLOGCOMMON_CUSTOMTAGSENTRY']._serialized_end=3098
  _globals['_RESPONSEFLAGS']._serialized_start=3149
  _globals['_RESPONSEFLAGS']._serialized_end=4358
  _globals['_RESPONSEFLAGS_UNAUTHORIZED']._serialized_start=4107
  _globals['_RESPONSEFLAGS_UNAUTHORIZED']._serialized_end=4312
  _globals['_RESPONSEFLAGS_UNAUTHORIZED_REASON']._serialized_start=4199
  _globals['_RESPONSEFLAGS_UNAUTHORIZED_REASON']._serialized_end=4253
  _globals['_TLSPROPERTIES']._serialized_start=4361
  _globals['_TLSPROPERTIES']._serialized_end=5282
  _globals['_TLSPROPERTIES_CERTIFICATEPROPERTIES']._serialized_start=4781
  _globals['_TLSPROPERTIES_CERTIFICATEPROPERTIES']._serialized_end=5147
  _globals['_TLSPROPERTIES_CERTIFICATEPROPERTIES_SUBJECTALTNAME']._serialized_start=4943
  _globals['_TLSPROPERTIES_CERTIFICATEPROPERTIES_SUBJECTALTNAME']._serialized_end=5079
  _globals['_TLSPROPERTIES_TLSVERSION']._serialized_start=5149
  _globals['_TLSPROPERTIES_TLSVERSION']._serialized_end=5236
  _globals['_HTTPREQUESTPROPERTIES']._serialized_start=5285
  _globals['_HTTPREQUESTPROPERTIES']._serialized_end=5914
  _globals['_HTTPREQUESTPROPERTIES_REQUESTHEADERSENTRY']._serialized_start=5807
  _globals['_HTTPREQUESTPROPERTIES_REQUESTHEADERSENTRY']._serialized_end=5860
  _globals['_HTTPRESPONSEPROPERTIES']._serialized_start=5917
  _globals['_HTTPRESPONSEPROPERTIES']._serialized_end=6526
  _globals['_HTTPRESPONSEPROPERTIES_RESPONSEHEADERSENTRY']._serialized_start=6360
  _globals['_HTTPRESPONSEPROPERTIES_RESPONSEHEADERSENTRY']._serialized_end=6414
  _globals['_HTTPRESPONSEPROPERTIES_RESPONSETRAILERSENTRY']._serialized_start=6416
  _globals['_HTTPRESPONSEPROPERTIES_RESPONSETRAILERSENTRY']._serialized_end=6471
