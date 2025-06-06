
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.accesslog.v3 import accesslog_pb2 as envoy_dot_config_dot_accesslog_dot_v3_dot_accesslog__pb2
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import config_source_pb2 as envoy_dot_config_dot_core_dot_v3_dot_config__source__pb2
from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from envoy.config.core.v3 import protocol_pb2 as envoy_dot_config_dot_core_dot_v3_dot_protocol__pb2
from envoy.config.core.v3 import substitution_format_string_pb2 as envoy_dot_config_dot_core_dot_v3_dot_substitution__format__string__pb2
from envoy.config.route.v3 import route_pb2 as envoy_dot_config_dot_route_dot_v3_dot_route__pb2
from envoy.config.route.v3 import scoped_route_pb2 as envoy_dot_config_dot_route_dot_v3_dot_scoped__route__pb2
from envoy.config.trace.v3 import http_tracer_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_http__tracer__pb2
from envoy.type.http.v3 import path_transformation_pb2 as envoy_dot_type_dot_http_dot_v3_dot_path__transformation__pb2
from envoy.type.tracing.v3 import custom_tag_pb2 as envoy_dot_type_dot_tracing_dot_v3_dot_custom__tag__pb2
from envoy.type.v3 import percent_pb2 as envoy_dot_type_dot_v3_dot_percent__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import security_pb2 as udpa_dot_annotations_dot_security__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nYenvoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.proto\x12;envoy.extensions.filters.network.http_connection_manager.v3\x1a)envoy/config/accesslog/v3/accesslog.proto\x1a\"envoy/config/core/v3/address.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a(envoy/config/core/v3/config_source.proto\x1a$envoy/config/core/v3/extension.proto\x1a#envoy/config/core/v3/protocol.proto\x1a\x35\x65nvoy/config/core/v3/substitution_format_string.proto\x1a!envoy/config/route/v3/route.proto\x1a(envoy/config/route/v3/scoped_route.proto\x1a\'envoy/config/trace/v3/http_tracer.proto\x1a,envoy/type/http/v3/path_transformation.proto\x1a&envoy/type/tracing/v3/custom_tag.proto\x1a\x1b\x65nvoy/type/v3/percent.proto\x1a\x19google/protobuf/any.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1fudpa/annotations/security.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xa8\x35\n\x15HttpConnectionManager\x12z\n\ncodec_type\x18\x01 \x01(\x0e\x32\\.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.CodecTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x1c\n\x0bstat_prefix\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12O\n\x03rds\x18\x03 \x01(\x0b\x32@.envoy.extensions.filters.network.http_connection_manager.v3.RdsH\x00\x12\x41\n\x0croute_config\x18\x04 \x01(\x0b\x32).envoy.config.route.v3.RouteConfigurationH\x00\x12\x62\n\rscoped_routes\x18\x1f \x01(\x0b\x32I.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRoutesH\x00\x12]\n\x0chttp_filters\x18\x05 \x03(\x0b\x32G.envoy.extensions.filters.network.http_connection_manager.v3.HttpFilter\x12\x32\n\x0e\x61\x64\x64_user_agent\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12k\n\x07tracing\x18\x07 \x01(\x0b\x32Z.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.Tracing\x12X\n\x1c\x63ommon_http_protocol_options\x18# \x01(\x0b\x32).envoy.config.core.v3.HttpProtocolOptionsB\x07\x8a\x93\xb7*\x02\x08\x01\x12*\n\"http1_safe_max_connection_duration\x18: \x01(\x08\x12I\n\x15http_protocol_options\x18\x08 \x01(\x0b\x32*.envoy.config.core.v3.Http1ProtocolOptions\x12S\n\x16http2_protocol_options\x18\t \x01(\x0b\x32*.envoy.config.core.v3.Http2ProtocolOptionsB\x07\x8a\x93\xb7*\x02\x08\x01\x12J\n\x16http3_protocol_options\x18, \x01(\x0b\x32*.envoy.config.core.v3.Http3ProtocolOptions\x12 \n\x0bserver_name\x18\n \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12\x9d\x01\n\x1cserver_header_transformation\x18\" \x01(\x0e\x32m.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.ServerHeaderTransformationB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12V\n\x1cscheme_header_transformation\x18\x30 \x01(\x0b\x32\x30.envoy.config.core.v3.SchemeHeaderTransformation\x12H\n\x16max_request_headers_kb\x18\x1d \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\n\xfa\x42\x07*\x05\x18\x80@ \x00\x12?\n\x13stream_idle_timeout\x18\x18 \x01(\x0b\x32\x19.google.protobuf.DurationB\x07\x8a\x93\xb7*\x02\x08\x01\x12;\n\x0frequest_timeout\x18\x1c \x01(\x0b\x32\x19.google.protobuf.DurationB\x07\x8a\x93\xb7*\x02\x08\x01\x12K\n\x17request_headers_timeout\x18) \x01(\x0b\x32\x19.google.protobuf.DurationB\x0f\xfa\x42\x05\xaa\x01\x02\x32\x00\x8a\x93\xb7*\x02\x08\x01\x12\x30\n\rdrain_timeout\x18\x0c \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x38\n\x15\x64\x65layed_close_timeout\x18\x1a \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x38\n\naccess_log\x18\r \x03(\x0b\x32$.envoy.config.accesslog.v3.AccessLog\x12U\n\x19\x61\x63\x63\x65ss_log_flush_interval\x18\x36 \x01(\x0b\x32\x19.google.protobuf.DurationB\x17\x18\x01\xfa\x42\t\xaa\x01\x06\x32\x04\x10\xc0\x84=\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x34\n\x1f\x66lush_access_log_on_new_request\x18\x37 \x01(\x08\x42\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x82\x01\n\x12\x61\x63\x63\x65ss_log_options\x18\x38 \x01(\x0b\x32\x66.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.HcmAccessLogOptions\x12?\n\x12use_remote_address\x18\x0e \x01(\x0b\x32\x1a.google.protobuf.BoolValueB\x07\x8a\x93\xb7*\x02\x08\x01\x12\x1c\n\x14xff_num_trusted_hops\x18\x13 \x01(\r\x12T\n original_ip_detection_extensions\x18. \x03(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12T\n early_header_mutation_extensions\x18\x34 \x03(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x89\x01\n\x17internal_address_config\x18\x19 \x01(\x0b\x32h.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.InternalAddressConfig\x12\x17\n\x0fskip_xff_append\x18\x15 \x01(\x08\x12\x18\n\x03via\x18\x16 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12\x37\n\x13generate_request_id\x18\x0f \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12$\n\x1cpreserve_external_request_id\x18  \x01(\x08\x12)\n!always_set_request_id_in_response\x18% \x01(\x08\x12\x9a\x01\n\x1b\x66orward_client_cert_details\x18\x10 \x01(\x0e\x32k.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.ForwardClientCertDetailsB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x97\x01\n\x1fset_current_client_cert_details\x18\x11 \x01(\x0b\x32n.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.SetCurrentClientCertDetails\x12\x1a\n\x12proxy_100_continue\x18\x12 \x01(\x08\x12\x39\n1represent_ipv4_remote_address_as_ipv4_mapped_ipv6\x18\x14 \x01(\x08\x12y\n\x0fupgrade_configs\x18\x17 \x03(\x0b\x32`.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.UpgradeConfig\x12\x32\n\x0enormalize_path\x18\x1e \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x15\n\rmerge_slashes\x18! \x01(\x08\x12\x99\x01\n path_with_escaped_slashes_action\x18- \x01(\x0e\x32o.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.PathWithEscapedSlashesAction\x12m\n\x14request_id_extension\x18$ \x01(\x0b\x32O.envoy.extensions.filters.network.http_connection_manager.v3.RequestIDExtension\x12i\n\x12local_reply_config\x18& \x01(\x0b\x32M.envoy.extensions.filters.network.http_connection_manager.v3.LocalReplyConfig\x12\x39\n\x18strip_matching_host_port\x18\' \x01(\x08\x42\x17\xf2\x98\xfe\x8f\x05\x11\x12\x0fstrip_port_mode\x12\x1d\n\x13strip_any_host_port\x18* \x01(\x08H\x01\x12H\n$stream_error_on_invalid_http_message\x18( \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x8f\x01\n\x1apath_normalization_options\x18+ \x01(\x0b\x32k.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.PathNormalizationOptions\x12\x1f\n\x17strip_trailing_host_dot\x18/ \x01(\x08\x12\x81\x01\n\x13proxy_status_config\x18\x31 \x01(\x0b\x32\x64.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManager.ProxyStatusConfig\x12R\n\x1etyped_header_validation_config\x18\x32 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x1f\n\x17\x61ppend_x_forwarded_port\x18\x33 \x01(\x08\x12\x1d\n\x15\x61ppend_local_overload\x18\x39 \x01(\x08\x12G\n#add_proxy_protocol_connection_state\x18\x35 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x1a\xcd\x04\n\x07Tracing\x12/\n\x0f\x63lient_sampling\x18\x03 \x01(\x0b\x32\x16.envoy.type.v3.Percent\x12/\n\x0frandom_sampling\x18\x04 \x01(\x0b\x32\x16.envoy.type.v3.Percent\x12\x30\n\x10overall_sampling\x18\x05 \x01(\x0b\x32\x16.envoy.type.v3.Percent\x12\x0f\n\x07verbose\x18\x06 \x01(\x08\x12\x39\n\x13max_path_tag_length\x18\x07 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x35\n\x0b\x63ustom_tags\x18\x08 \x03(\x0b\x32 .envoy.type.tracing.v3.CustomTag\x12\x35\n\x08provider\x18\t \x01(\x0b\x32#.envoy.config.trace.v3.Tracing.Http\x12\x37\n\x13spawn_upstream_span\x18\n \x01(\x0b\x32\x1a.google.protobuf.BoolValue\"(\n\rOperationName\x12\x0b\n\x07INGRESS\x10\x00\x12\n\n\x06\x45GRESS\x10\x01:[\x9a\xc5\x88\x1eV\nTenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.TracingJ\x04\x08\x01\x10\x02J\x04\x08\x02\x10\x03R\x0eoperation_nameR\x18request_headers_for_tags\x1a\xce\x01\n\x15InternalAddressConfig\x12\x14\n\x0cunix_sockets\x18\x01 \x01(\x08\x12\x34\n\x0b\x63idr_ranges\x18\x02 \x03(\x0b\x32\x1f.envoy.config.core.v3.CidrRange:i\x9a\xc5\x88\x1e\x64\nbenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.InternalAddressConfig\x1a\xf8\x01\n\x1bSetCurrentClientCertDetails\x12+\n\x07subject\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x0c\n\x04\x63\x65rt\x18\x03 \x01(\x08\x12\r\n\x05\x63hain\x18\x06 \x01(\x08\x12\x0b\n\x03\x64ns\x18\x04 \x01(\x08\x12\x0b\n\x03uri\x18\x05 \x01(\x08:o\x9a\xc5\x88\x1ej\nhenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.SetCurrentClientCertDetailsJ\x04\x08\x02\x10\x03\x1a\x8f\x02\n\rUpgradeConfig\x12\x14\n\x0cupgrade_type\x18\x01 \x01(\t\x12X\n\x07\x66ilters\x18\x02 \x03(\x0b\x32G.envoy.extensions.filters.network.http_connection_manager.v3.HttpFilter\x12+\n\x07\x65nabled\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValue:a\x9a\xc5\x88\x1e\\\nZenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.UpgradeConfig\x1a\xb1\x01\n\x18PathNormalizationOptions\x12I\n\x19\x66orwarding_transformation\x18\x01 \x01(\x0b\x32&.envoy.type.http.v3.PathTransformation\x12J\n\x1ahttp_filter_transformation\x18\x02 \x01(\x0b\x32&.envoy.type.http.v3.PathTransformation\x1a\xe3\x01\n\x11ProxyStatusConfig\x12\x16\n\x0eremove_details\x18\x01 \x01(\x08\x12-\n%remove_connection_termination_details\x18\x02 \x01(\x08\x12\x1d\n\x15remove_response_flags\x18\x03 \x01(\x08\x12%\n\x1dset_recommended_response_code\x18\x04 \x01(\x08\x12\x15\n\x0buse_node_id\x18\x05 \x01(\x08H\x00\x12\x1c\n\x12literal_proxy_name\x18\x06 \x01(\tH\x00\x42\x0c\n\nproxy_name\x1a\xc0\x01\n\x13HcmAccessLogOptions\x12J\n\x19\x61\x63\x63\x65ss_log_flush_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0c\xfa\x42\t\xaa\x01\x06\x32\x04\x10\xc0\x84=\x12\'\n\x1f\x66lush_access_log_on_new_request\x18\x02 \x01(\x08\x12\x34\n,flush_log_on_tunnel_successfully_established\x18\x03 \x01(\x08\"6\n\tCodecType\x12\x08\n\x04\x41UTO\x10\x00\x12\t\n\x05HTTP1\x10\x01\x12\t\n\x05HTTP2\x10\x02\x12\t\n\x05HTTP3\x10\x03\"S\n\x1aServerHeaderTransformation\x12\r\n\tOVERWRITE\x10\x00\x12\x14\n\x10\x41PPEND_IF_ABSENT\x10\x01\x12\x10\n\x0cPASS_THROUGH\x10\x02\"y\n\x18\x46orwardClientCertDetails\x12\x0c\n\x08SANITIZE\x10\x00\x12\x10\n\x0c\x46ORWARD_ONLY\x10\x01\x12\x12\n\x0e\x41PPEND_FORWARD\x10\x02\x12\x10\n\x0cSANITIZE_SET\x10\x03\x12\x17\n\x13\x41LWAYS_FORWARD_ONLY\x10\x04\"\xa0\x01\n\x1cPathWithEscapedSlashesAction\x12#\n\x1fIMPLEMENTATION_SPECIFIC_DEFAULT\x10\x00\x12\x12\n\x0eKEEP_UNCHANGED\x10\x01\x12\x12\n\x0eREJECT_REQUEST\x10\x02\x12\x19\n\x15UNESCAPE_AND_REDIRECT\x10\x03\x12\x18\n\x14UNESCAPE_AND_FORWARD\x10\x04:S\x9a\xc5\x88\x1eN\nLenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManagerB\x16\n\x0froute_specifier\x12\x03\xf8\x42\x01\x42\x11\n\x0fstrip_port_modeJ\x04\x08\x1b\x10\x1cJ\x04\x08\x0b\x10\x0cR\x0cidle_timeout\"\xb5\x01\n\x10LocalReplyConfig\x12\\\n\x07mappers\x18\x01 \x03(\x0b\x32K.envoy.extensions.filters.network.http_connection_manager.v3.ResponseMapper\x12\x43\n\x0b\x62ody_format\x18\x02 \x01(\x0b\x32..envoy.config.core.v3.SubstitutionFormatString\"\xe0\x02\n\x0eResponseMapper\x12\x44\n\x06\x66ilter\x18\x01 \x01(\x0b\x32*.envoy.config.accesslog.v3.AccessLogFilterB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12>\n\x0bstatus_code\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0b\xfa\x42\x08*\x06\x10\xd8\x04(\xc8\x01\x12.\n\x04\x62ody\x18\x03 \x01(\x0b\x32 .envoy.config.core.v3.DataSource\x12L\n\x14\x62ody_format_override\x18\x04 \x01(\x0b\x32..envoy.config.core.v3.SubstitutionFormatString\x12J\n\x0eheaders_to_add\x18\x05 \x03(\x0b\x32\'.envoy.config.core.v3.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\"\xa8\x01\n\x03Rds\x12\x43\n\rconfig_source\x18\x01 \x01(\x0b\x32\".envoy.config.core.v3.ConfigSourceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x19\n\x11route_config_name\x18\x02 \x01(\t:A\x9a\xc5\x88\x1e<\n:envoy.config.filter.network.http_connection_manager.v2.Rds\"\xdc\x01\n\x1dScopedRouteConfigurationsList\x12^\n\x1bscoped_route_configurations\x18\x01 \x03(\x0b\x32/.envoy.config.route.v3.ScopedRouteConfigurationB\x08\xfa\x42\x05\x92\x01\x02\x08\x01:[\x9a\xc5\x88\x1eV\nTenvoy.config.filter.network.http_connection_manager.v2.ScopedRouteConfigurationsList\"\xb9\r\n\x0cScopedRoutes\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12~\n\x11scope_key_builder\x18\x02 \x01(\x0b\x32Y.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRoutes.ScopeKeyBuilderB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12=\n\x11rds_config_source\x18\x03 \x01(\x0b\x32\".envoy.config.core.v3.ConfigSource\x12\x86\x01\n scoped_route_configurations_list\x18\x04 \x01(\x0b\x32Z.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRouteConfigurationsListH\x00\x12\\\n\nscoped_rds\x18\x05 \x01(\x0b\x32\x46.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRdsH\x00\x1a\x86\t\n\x0fScopeKeyBuilder\x12\x86\x01\n\tfragments\x18\x01 \x03(\x0b\x32i.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRoutes.ScopeKeyBuilder.FragmentBuilderB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\x8d\x07\n\x0f\x46ragmentBuilder\x12\xa0\x01\n\x16header_value_extractor\x18\x01 \x01(\x0b\x32~.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractorH\x00\x1a\xdd\x04\n\x14HeaderValueExtractor\x12\x1b\n\x04name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x00\x12\x19\n\x11\x65lement_separator\x18\x02 \x01(\t\x12\x0f\n\x05index\x18\x03 \x01(\rH\x00\x12\x9c\x01\n\x07\x65lement\x18\x04 \x01(\x0b\x32\x88\x01.envoy.extensions.filters.network.http_connection_manager.v3.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractor.KvElementH\x00\x1a\xcb\x01\n\tKvElement\x12\x1a\n\tseparator\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x14\n\x03key\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01:\x8b\x01\x9a\xc5\x88\x1e\x85\x01\n\x82\x01\x65nvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractor.KvElement:\x7f\x9a\xc5\x88\x1ez\nxenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractorB\x0e\n\x0c\x65xtract_type:j\x9a\xc5\x88\x1e\x65\ncenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilderB\x0b\n\x04type\x12\x03\xf8\x42\x01:Z\x9a\xc5\x88\x1eU\nSenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder:J\x9a\xc5\x88\x1e\x45\nCenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutesB\x17\n\x10\x63onfig_specifier\x12\x03\xf8\x42\x01\"\xc4\x01\n\tScopedRds\x12N\n\x18scoped_rds_config_source\x18\x01 \x01(\x0b\x32\".envoy.config.core.v3.ConfigSourceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x1e\n\x16srds_resources_locator\x18\x02 \x01(\t:G\x9a\xc5\x88\x1e\x42\n@envoy.config.filter.network.http_connection_manager.v2.ScopedRds\"\xae\x02\n\nHttpFilter\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12,\n\x0ctyped_config\x18\x04 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x12G\n\x10\x63onfig_discovery\x18\x05 \x01(\x0b\x32+.envoy.config.core.v3.ExtensionConfigSourceH\x00\x12\x13\n\x0bis_optional\x18\x06 \x01(\x08\x12\x10\n\x08\x64isabled\x18\x07 \x01(\x08:H\x9a\xc5\x88\x1e\x43\nAenvoy.config.filter.network.http_connection_manager.v2.HttpFilterB\r\n\x0b\x63onfig_typeJ\x04\x08\x03\x10\x04J\x04\x08\x02\x10\x03R\x06\x63onfig\"\x92\x01\n\x12RequestIDExtension\x12*\n\x0ctyped_config\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any:P\x9a\xc5\x88\x1eK\nIenvoy.config.filter.network.http_connection_manager.v2.RequestIDExtension\"\x86\x01\n EnvoyMobileHttpConnectionManager\x12\x62\n\x06\x63onfig\x18\x01 \x01(\x0b\x32R.envoy.extensions.filters.network.http_connection_manager.v3.HttpConnectionManagerB\xef\x01\nIio.envoyproxy.envoy.extensions.filters.network.http_connection_manager.v3B\x1aHttpConnectionManagerProtoP\x01Z|github.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/http_connection_manager/v3;http_connection_managerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.http_connection_manager.v3.http_connection_manager_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nIio.envoyproxy.envoy.extensions.filters.network.http_connection_manager.v3B\032HttpConnectionManagerProtoP\001Z|github.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/http_connection_manager/v3;http_connection_managerv3\272\200\310\321\006\002\020\002'
  _HTTPCONNECTIONMANAGER_TRACING._options = None
  _HTTPCONNECTIONMANAGER_TRACING._serialized_options = b'\232\305\210\036V\nTenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.Tracing'
  _HTTPCONNECTIONMANAGER_INTERNALADDRESSCONFIG._options = None
  _HTTPCONNECTIONMANAGER_INTERNALADDRESSCONFIG._serialized_options = b'\232\305\210\036d\nbenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.InternalAddressConfig'
  _HTTPCONNECTIONMANAGER_SETCURRENTCLIENTCERTDETAILS._options = None
  _HTTPCONNECTIONMANAGER_SETCURRENTCLIENTCERTDETAILS._serialized_options = b'\232\305\210\036j\nhenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.SetCurrentClientCertDetails'
  _HTTPCONNECTIONMANAGER_UPGRADECONFIG._options = None
  _HTTPCONNECTIONMANAGER_UPGRADECONFIG._serialized_options = b'\232\305\210\036\\\nZenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager.UpgradeConfig'
  _HTTPCONNECTIONMANAGER_HCMACCESSLOGOPTIONS.fields_by_name['access_log_flush_interval']._options = None
  _HTTPCONNECTIONMANAGER_HCMACCESSLOGOPTIONS.fields_by_name['access_log_flush_interval']._serialized_options = b'\372B\t\252\001\0062\004\020\300\204='
  _HTTPCONNECTIONMANAGER.oneofs_by_name['route_specifier']._options = None
  _HTTPCONNECTIONMANAGER.oneofs_by_name['route_specifier']._serialized_options = b'\370B\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['codec_type']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['codec_type']._serialized_options = b'\372B\005\202\001\002\020\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['stat_prefix']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['common_http_protocol_options']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['common_http_protocol_options']._serialized_options = b'\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['http2_protocol_options']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['http2_protocol_options']._serialized_options = b'\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['server_name']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['server_name']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _HTTPCONNECTIONMANAGER.fields_by_name['server_header_transformation']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['server_header_transformation']._serialized_options = b'\372B\005\202\001\002\020\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['max_request_headers_kb']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['max_request_headers_kb']._serialized_options = b'\372B\007*\005\030\200@ \000'
  _HTTPCONNECTIONMANAGER.fields_by_name['stream_idle_timeout']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['stream_idle_timeout']._serialized_options = b'\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['request_timeout']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['request_timeout']._serialized_options = b'\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['request_headers_timeout']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['request_headers_timeout']._serialized_options = b'\372B\005\252\001\0022\000\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['access_log_flush_interval']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['access_log_flush_interval']._serialized_options = b'\030\001\372B\t\252\001\0062\004\020\300\204=\222\307\206\330\004\0033.0'
  _HTTPCONNECTIONMANAGER.fields_by_name['flush_access_log_on_new_request']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['flush_access_log_on_new_request']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _HTTPCONNECTIONMANAGER.fields_by_name['use_remote_address']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['use_remote_address']._serialized_options = b'\212\223\267*\002\010\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['via']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['via']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _HTTPCONNECTIONMANAGER.fields_by_name['forward_client_cert_details']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['forward_client_cert_details']._serialized_options = b'\372B\005\202\001\002\020\001'
  _HTTPCONNECTIONMANAGER.fields_by_name['strip_matching_host_port']._options = None
  _HTTPCONNECTIONMANAGER.fields_by_name['strip_matching_host_port']._serialized_options = b'\362\230\376\217\005\021\022\017strip_port_mode'
  _HTTPCONNECTIONMANAGER._options = None
  _HTTPCONNECTIONMANAGER._serialized_options = b'\232\305\210\036N\nLenvoy.config.filter.network.http_connection_manager.v2.HttpConnectionManager'
  _RESPONSEMAPPER.fields_by_name['filter']._options = None
  _RESPONSEMAPPER.fields_by_name['filter']._serialized_options = b'\372B\005\212\001\002\020\001'
  _RESPONSEMAPPER.fields_by_name['status_code']._options = None
  _RESPONSEMAPPER.fields_by_name['status_code']._serialized_options = b'\372B\010*\006\020\330\004(\310\001'
  _RESPONSEMAPPER.fields_by_name['headers_to_add']._options = None
  _RESPONSEMAPPER.fields_by_name['headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _RDS.fields_by_name['config_source']._options = None
  _RDS.fields_by_name['config_source']._serialized_options = b'\372B\005\212\001\002\020\001'
  _RDS._options = None
  _RDS._serialized_options = b'\232\305\210\036<\n:envoy.config.filter.network.http_connection_manager.v2.Rds'
  _SCOPEDROUTECONFIGURATIONSLIST.fields_by_name['scoped_route_configurations']._options = None
  _SCOPEDROUTECONFIGURATIONSLIST.fields_by_name['scoped_route_configurations']._serialized_options = b'\372B\005\222\001\002\010\001'
  _SCOPEDROUTECONFIGURATIONSLIST._options = None
  _SCOPEDROUTECONFIGURATIONSLIST._serialized_options = b'\232\305\210\036V\nTenvoy.config.filter.network.http_connection_manager.v2.ScopedRouteConfigurationsList'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT.fields_by_name['separator']._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT.fields_by_name['separator']._serialized_options = b'\372B\004r\002\020\001'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT.fields_by_name['key']._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT._serialized_options = b'\232\305\210\036\205\001\n\202\001envoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractor.KvElement'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR.fields_by_name['name']._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR.fields_by_name['name']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\000'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR._serialized_options = b'\232\305\210\036z\nxenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder.HeaderValueExtractor'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER.oneofs_by_name['type']._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER.oneofs_by_name['type']._serialized_options = b'\370B\001'
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER._serialized_options = b'\232\305\210\036e\ncenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder.FragmentBuilder'
  _SCOPEDROUTES_SCOPEKEYBUILDER.fields_by_name['fragments']._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER.fields_by_name['fragments']._serialized_options = b'\372B\005\222\001\002\010\001'
  _SCOPEDROUTES_SCOPEKEYBUILDER._options = None
  _SCOPEDROUTES_SCOPEKEYBUILDER._serialized_options = b'\232\305\210\036U\nSenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes.ScopeKeyBuilder'
  _SCOPEDROUTES.oneofs_by_name['config_specifier']._options = None
  _SCOPEDROUTES.oneofs_by_name['config_specifier']._serialized_options = b'\370B\001'
  _SCOPEDROUTES.fields_by_name['name']._options = None
  _SCOPEDROUTES.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _SCOPEDROUTES.fields_by_name['scope_key_builder']._options = None
  _SCOPEDROUTES.fields_by_name['scope_key_builder']._serialized_options = b'\372B\005\212\001\002\020\001'
  _SCOPEDROUTES._options = None
  _SCOPEDROUTES._serialized_options = b'\232\305\210\036E\nCenvoy.config.filter.network.http_connection_manager.v2.ScopedRoutes'
  _SCOPEDRDS.fields_by_name['scoped_rds_config_source']._options = None
  _SCOPEDRDS.fields_by_name['scoped_rds_config_source']._serialized_options = b'\372B\005\212\001\002\020\001'
  _SCOPEDRDS._options = None
  _SCOPEDRDS._serialized_options = b'\232\305\210\036B\n@envoy.config.filter.network.http_connection_manager.v2.ScopedRds'
  _HTTPFILTER.fields_by_name['name']._options = None
  _HTTPFILTER.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _HTTPFILTER._options = None
  _HTTPFILTER._serialized_options = b'\232\305\210\036C\nAenvoy.config.filter.network.http_connection_manager.v2.HttpFilter'
  _REQUESTIDEXTENSION._options = None
  _REQUESTIDEXTENSION._serialized_options = b'\232\305\210\036K\nIenvoy.config.filter.network.http_connection_manager.v2.RequestIDExtension'
  _globals['_HTTPCONNECTIONMANAGER']._serialized_start=956
  _globals['_HTTPCONNECTIONMANAGER']._serialized_end=7780
  _globals['_HTTPCONNECTIONMANAGER_TRACING']._serialized_start=5271
  _globals['_HTTPCONNECTIONMANAGER_TRACING']._serialized_end=5860
  _globals['_HTTPCONNECTIONMANAGER_TRACING_OPERATIONNAME']._serialized_start=5673
  _globals['_HTTPCONNECTIONMANAGER_TRACING_OPERATIONNAME']._serialized_end=5713
  _globals['_HTTPCONNECTIONMANAGER_INTERNALADDRESSCONFIG']._serialized_start=5863
  _globals['_HTTPCONNECTIONMANAGER_INTERNALADDRESSCONFIG']._serialized_end=6069
  _globals['_HTTPCONNECTIONMANAGER_SETCURRENTCLIENTCERTDETAILS']._serialized_start=6072
  _globals['_HTTPCONNECTIONMANAGER_SETCURRENTCLIENTCERTDETAILS']._serialized_end=6320
  _globals['_HTTPCONNECTIONMANAGER_UPGRADECONFIG']._serialized_start=6323
  _globals['_HTTPCONNECTIONMANAGER_UPGRADECONFIG']._serialized_end=6594
  _globals['_HTTPCONNECTIONMANAGER_PATHNORMALIZATIONOPTIONS']._serialized_start=6597
  _globals['_HTTPCONNECTIONMANAGER_PATHNORMALIZATIONOPTIONS']._serialized_end=6774
  _globals['_HTTPCONNECTIONMANAGER_PROXYSTATUSCONFIG']._serialized_start=6777
  _globals['_HTTPCONNECTIONMANAGER_PROXYSTATUSCONFIG']._serialized_end=7004
  _globals['_HTTPCONNECTIONMANAGER_HCMACCESSLOGOPTIONS']._serialized_start=7007
  _globals['_HTTPCONNECTIONMANAGER_HCMACCESSLOGOPTIONS']._serialized_end=7199
  _globals['_HTTPCONNECTIONMANAGER_CODECTYPE']._serialized_start=7201
  _globals['_HTTPCONNECTIONMANAGER_CODECTYPE']._serialized_end=7255
  _globals['_HTTPCONNECTIONMANAGER_SERVERHEADERTRANSFORMATION']._serialized_start=7257
  _globals['_HTTPCONNECTIONMANAGER_SERVERHEADERTRANSFORMATION']._serialized_end=7340
  _globals['_HTTPCONNECTIONMANAGER_FORWARDCLIENTCERTDETAILS']._serialized_start=7342
  _globals['_HTTPCONNECTIONMANAGER_FORWARDCLIENTCERTDETAILS']._serialized_end=7463
  _globals['_HTTPCONNECTIONMANAGER_PATHWITHESCAPEDSLASHESACTION']._serialized_start=7466
  _globals['_HTTPCONNECTIONMANAGER_PATHWITHESCAPEDSLASHESACTION']._serialized_end=7626
  _globals['_LOCALREPLYCONFIG']._serialized_start=7783
  _globals['_LOCALREPLYCONFIG']._serialized_end=7964
  _globals['_RESPONSEMAPPER']._serialized_start=7967
  _globals['_RESPONSEMAPPER']._serialized_end=8319
  _globals['_RDS']._serialized_start=8322
  _globals['_RDS']._serialized_end=8490
  _globals['_SCOPEDROUTECONFIGURATIONSLIST']._serialized_start=8493
  _globals['_SCOPEDROUTECONFIGURATIONSLIST']._serialized_end=8713
  _globals['_SCOPEDROUTES']._serialized_start=8716
  _globals['_SCOPEDROUTES']._serialized_end=10437
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER']._serialized_start=9178
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER']._serialized_end=10336
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER']._serialized_start=9335
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER']._serialized_end=10244
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR']._serialized_start=9518
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR']._serialized_end=10123
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT']._serialized_start=9775
  _globals['_SCOPEDROUTES_SCOPEKEYBUILDER_FRAGMENTBUILDER_HEADERVALUEEXTRACTOR_KVELEMENT']._serialized_end=9978
  _globals['_SCOPEDRDS']._serialized_start=10440
  _globals['_SCOPEDRDS']._serialized_end=10636
  _globals['_HTTPFILTER']._serialized_start=10639
  _globals['_HTTPFILTER']._serialized_end=10941
  _globals['_REQUESTIDEXTENSION']._serialized_start=10944
  _globals['_REQUESTIDEXTENSION']._serialized_end=11090
  _globals['_ENVOYMOBILEHTTPCONNECTIONMANAGER']._serialized_start=11093
  _globals['_ENVOYMOBILEHTTPCONNECTIONMANAGER']._serialized_end=11227
