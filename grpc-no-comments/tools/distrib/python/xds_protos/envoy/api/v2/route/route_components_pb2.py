
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
from envoy.type.matcher import regex_pb2 as envoy_dot_type_dot_matcher_dot_regex__pb2
from envoy.type.matcher import string_pb2 as envoy_dot_type_dot_matcher_dot_string__pb2
from envoy.type import percent_pb2 as envoy_dot_type_dot_percent__pb2
from envoy.type import range_pb2 as envoy_dot_type_dot_range__pb2
from envoy.type.tracing.v2 import custom_tag_pb2 as envoy_dot_type_dot_tracing_dot_v2_dot_custom__tag__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)envoy/api/v2/route/route_components.proto\x12\x12\x65nvoy.api.v2.route\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a\x1e\x65nvoy/type/matcher/regex.proto\x1a\x1f\x65nvoy/type/matcher/string.proto\x1a\x18\x65nvoy/type/percent.proto\x1a\x16\x65nvoy/type/range.proto\x1a&envoy/type/tracing/v2/custom_tag.proto\x1a\x19google/protobuf/any.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa7\n\n\x0bVirtualHost\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12#\n\x07\x64omains\x18\x02 \x03(\tB\x12\xfa\x42\x0f\x92\x01\x0c\x08\x01\"\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12)\n\x06routes\x18\x03 \x03(\x0b\x32\x19.envoy.api.v2.route.Route\x12Q\n\x0brequire_tls\x18\x04 \x01(\x0e\x32\x32.envoy.api.v2.route.VirtualHost.TlsRequirementTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12<\n\x10virtual_clusters\x18\x05 \x03(\x0b\x32\".envoy.api.v2.route.VirtualCluster\x12\x32\n\x0brate_limits\x18\x06 \x03(\x0b\x32\x1d.envoy.api.v2.route.RateLimit\x12O\n\x16request_headers_to_add\x18\x07 \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12!\n\x19request_headers_to_remove\x18\r \x03(\t\x12P\n\x17response_headers_to_add\x18\n \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12\"\n\x1aresponse_headers_to_remove\x18\x0b \x03(\t\x12,\n\x04\x63ors\x18\x08 \x01(\x0b\x32\x1e.envoy.api.v2.route.CorsPolicy\x12S\n\x11per_filter_config\x18\x0c \x03(\x0b\x32\x34.envoy.api.v2.route.VirtualHost.PerFilterConfigEntryB\x02\x18\x01\x12Z\n\x17typed_per_filter_config\x18\x0f \x03(\x0b\x32\x39.envoy.api.v2.route.VirtualHost.TypedPerFilterConfigEntry\x12%\n\x1dinclude_request_attempt_count\x18\x0e \x01(\x08\x12)\n!include_attempt_count_in_response\x18\x13 \x01(\x08\x12\x35\n\x0cretry_policy\x18\x10 \x01(\x0b\x32\x1f.envoy.api.v2.route.RetryPolicy\x12\x37\n\x19retry_policy_typed_config\x18\x14 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x35\n\x0chedge_policy\x18\x11 \x01(\x0b\x32\x1f.envoy.api.v2.route.HedgePolicy\x12\x44\n\x1eper_request_buffer_limit_bytes\x18\x12 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x1aO\n\x14PerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12&\n\x05value\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct:\x02\x38\x01\x1aQ\n\x19TypedPerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any:\x02\x38\x01\":\n\x12TlsRequirementType\x12\x08\n\x04NONE\x10\x00\x12\x11\n\rEXTERNAL_ONLY\x10\x01\x12\x07\n\x03\x41LL\x10\x02J\x04\x08\t\x10\n\"4\n\x0c\x46ilterAction\x12$\n\x06\x61\x63tion\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\"\xd5\x08\n\x05Route\x12\x0c\n\x04name\x18\x0e \x01(\t\x12\x37\n\x05match\x18\x01 \x01(\x0b\x32\x1e.envoy.api.v2.route.RouteMatchB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x30\n\x05route\x18\x02 \x01(\x0b\x32\x1f.envoy.api.v2.route.RouteActionH\x00\x12\x36\n\x08redirect\x18\x03 \x01(\x0b\x32\".envoy.api.v2.route.RedirectActionH\x00\x12\x43\n\x0f\x64irect_response\x18\x07 \x01(\x0b\x32(.envoy.api.v2.route.DirectResponseActionH\x00\x12\x39\n\rfilter_action\x18\x11 \x01(\x0b\x32 .envoy.api.v2.route.FilterActionH\x00\x12-\n\x08metadata\x18\x04 \x01(\x0b\x32\x1b.envoy.api.v2.core.Metadata\x12\x30\n\tdecorator\x18\x05 \x01(\x0b\x32\x1d.envoy.api.v2.route.Decorator\x12M\n\x11per_filter_config\x18\x08 \x03(\x0b\x32..envoy.api.v2.route.Route.PerFilterConfigEntryB\x02\x18\x01\x12T\n\x17typed_per_filter_config\x18\r \x03(\x0b\x32\x33.envoy.api.v2.route.Route.TypedPerFilterConfigEntry\x12O\n\x16request_headers_to_add\x18\t \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12!\n\x19request_headers_to_remove\x18\x0c \x03(\t\x12P\n\x17response_headers_to_add\x18\n \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12\"\n\x1aresponse_headers_to_remove\x18\x0b \x03(\t\x12,\n\x07tracing\x18\x0f \x01(\x0b\x32\x1b.envoy.api.v2.route.Tracing\x12\x44\n\x1eper_request_buffer_limit_bytes\x18\x10 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x1aO\n\x14PerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12&\n\x05value\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct:\x02\x38\x01\x1aQ\n\x19TypedPerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any:\x02\x38\x01\x42\r\n\x06\x61\x63tion\x12\x03\xf8\x42\x01J\x04\x08\x06\x10\x07\"\xae\x07\n\x0fWeightedCluster\x12M\n\x08\x63lusters\x18\x01 \x03(\x0b\x32\x31.envoy.api.v2.route.WeightedCluster.ClusterWeightB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12;\n\x0ctotal_weight\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(\x01\x12\x1a\n\x12runtime_key_prefix\x18\x02 \x01(\t\x1a\xf2\x05\n\rClusterWeight\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12,\n\x06weight\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x33\n\x0emetadata_match\x18\x03 \x01(\x0b\x32\x1b.envoy.api.v2.core.Metadata\x12O\n\x16request_headers_to_add\x18\x04 \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12!\n\x19request_headers_to_remove\x18\t \x03(\t\x12P\n\x17response_headers_to_add\x18\x05 \x03(\x0b\x32$.envoy.api.v2.core.HeaderValueOptionB\t\xfa\x42\x06\x92\x01\x03\x10\xe8\x07\x12\"\n\x1aresponse_headers_to_remove\x18\x06 \x03(\t\x12\x65\n\x11per_filter_config\x18\x08 \x03(\x0b\x32\x46.envoy.api.v2.route.WeightedCluster.ClusterWeight.PerFilterConfigEntryB\x02\x18\x01\x12l\n\x17typed_per_filter_config\x18\n \x03(\x0b\x32K.envoy.api.v2.route.WeightedCluster.ClusterWeight.TypedPerFilterConfigEntry\x1aO\n\x14PerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12&\n\x05value\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct:\x02\x38\x01\x1aQ\n\x19TypedPerFilterConfigEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any:\x02\x38\x01J\x04\x08\x07\x10\x08\"\xc5\x05\n\nRouteMatch\x12\x10\n\x06prefix\x18\x01 \x01(\tH\x00\x12\x0e\n\x04path\x18\x02 \x01(\tH\x00\x12!\n\x05regex\x18\x03 \x01(\tB\x10\x18\x01\xfa\x42\x05r\x03(\x80\x08\xb8\xee\xf2\xd2\x05\x01H\x00\x12@\n\nsafe_regex\x18\n \x01(\x0b\x32 .envoy.type.matcher.RegexMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12\x32\n\x0e\x63\x61se_sensitive\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x45\n\x10runtime_fraction\x18\t \x01(\x0b\x32+.envoy.api.v2.core.RuntimeFractionalPercent\x12\x32\n\x07headers\x18\x06 \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcher\x12\x43\n\x10query_parameters\x18\x07 \x03(\x0b\x32).envoy.api.v2.route.QueryParameterMatcher\x12\x42\n\x04grpc\x18\x08 \x01(\x0b\x32\x34.envoy.api.v2.route.RouteMatch.GrpcRouteMatchOptions\x12J\n\x0btls_context\x18\x0b \x01(\x0b\x32\x35.envoy.api.v2.route.RouteMatch.TlsContextMatchOptions\x1a\x17\n\x15GrpcRouteMatchOptions\x1av\n\x16TlsContextMatchOptions\x12-\n\tpresented\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12-\n\tvalidated\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValueB\x15\n\x0epath_specifier\x12\x03\xf8\x42\x01J\x04\x08\x05\x10\x06\"\x87\x04\n\nCorsPolicy\x12\x1e\n\x0c\x61llow_origin\x18\x01 \x03(\tB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12+\n\x12\x61llow_origin_regex\x18\x08 \x03(\tB\x0f\x18\x01\xfa\x42\n\x92\x01\x07\"\x05r\x03(\x80\x08\x12\x44\n\x19\x61llow_origin_string_match\x18\x0b \x03(\x0b\x32!.envoy.type.matcher.StringMatcher\x12\x15\n\rallow_methods\x18\x02 \x01(\t\x12\x15\n\rallow_headers\x18\x03 \x01(\t\x12\x16\n\x0e\x65xpose_headers\x18\x04 \x01(\t\x12\x0f\n\x07max_age\x18\x05 \x01(\t\x12\x35\n\x11\x61llow_credentials\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x37\n\x07\x65nabled\x18\x07 \x01(\x0b\x32\x1a.google.protobuf.BoolValueB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01H\x00\x12\x45\n\x0e\x66ilter_enabled\x18\t \x01(\x0b\x32+.envoy.api.v2.core.RuntimeFractionalPercentH\x00\x12\x43\n\x0eshadow_enabled\x18\n \x01(\x0b\x32+.envoy.api.v2.core.RuntimeFractionalPercentB\x13\n\x11\x65nabled_specifier\"\xf7\x16\n\x0bRouteAction\x12\x1a\n\x07\x63luster\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01H\x00\x12\'\n\x0e\x63luster_header\x18\x02 \x01(\tB\r\xfa\x42\nr\x08 \x01\xc0\x01\x01\xc8\x01\x00H\x00\x12@\n\x11weighted_clusters\x18\x03 \x01(\x0b\x32#.envoy.api.v2.route.WeightedClusterH\x00\x12n\n\x1f\x63luster_not_found_response_code\x18\x14 \x01(\x0e\x32;.envoy.api.v2.route.RouteAction.ClusterNotFoundResponseCodeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x33\n\x0emetadata_match\x18\x04 \x01(\x0b\x32\x1b.envoy.api.v2.core.Metadata\x12#\n\x0eprefix_rewrite\x18\x05 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12\x42\n\rregex_rewrite\x18  \x01(\x0b\x32+.envoy.type.matcher.RegexMatchAndSubstitute\x12?\n\x0chost_rewrite\x18\x06 \x01(\tB\'\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\xf2\x98\xfe\x8f\x05\x16\n\x14host_rewrite_literalH\x01\x12\x37\n\x11\x61uto_host_rewrite\x18\x07 \x01(\x0b\x32\x1a.google.protobuf.BoolValueH\x01\x12J\n\x18\x61uto_host_rewrite_header\x18\x1d \x01(\tB&\xfa\x42\x08r\x06\xc0\x01\x01\xc8\x01\x00\xf2\x98\xfe\x8f\x05\x15\n\x13host_rewrite_headerH\x01\x12*\n\x07timeout\x18\x08 \x01(\x0b\x32\x19.google.protobuf.Duration\x12/\n\x0cidle_timeout\x18\x18 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x35\n\x0cretry_policy\x18\t \x01(\x0b\x32\x1f.envoy.api.v2.route.RetryPolicy\x12\x37\n\x19retry_policy_typed_config\x18! \x01(\x0b\x32\x14.google.protobuf.Any\x12V\n\x15request_mirror_policy\x18\n \x01(\x0b\x32\x33.envoy.api.v2.route.RouteAction.RequestMirrorPolicyB\x02\x18\x01\x12T\n\x17request_mirror_policies\x18\x1e \x03(\x0b\x32\x33.envoy.api.v2.route.RouteAction.RequestMirrorPolicy\x12>\n\x08priority\x18\x0b \x01(\x0e\x32\".envoy.api.v2.core.RoutingPriorityB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x32\n\x0brate_limits\x18\r \x03(\x0b\x32\x1d.envoy.api.v2.route.RateLimit\x12:\n\x16include_vh_rate_limits\x18\x0e \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12?\n\x0bhash_policy\x18\x0f \x03(\x0b\x32*.envoy.api.v2.route.RouteAction.HashPolicy\x12,\n\x04\x63ors\x18\x11 \x01(\x0b\x32\x1e.envoy.api.v2.route.CorsPolicy\x12\x33\n\x10max_grpc_timeout\x18\x17 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x36\n\x13grpc_timeout_offset\x18\x1c \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x46\n\x0fupgrade_configs\x18\x19 \x03(\x0b\x32-.envoy.api.v2.route.RouteAction.UpgradeConfig\x12X\n\x18internal_redirect_action\x18\x1a \x01(\x0e\x32\x36.envoy.api.v2.route.RouteAction.InternalRedirectAction\x12<\n\x16max_internal_redirects\x18\x1f \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x35\n\x0chedge_policy\x18\x1b \x01(\x0b\x32\x1f.envoy.api.v2.route.HedgePolicy\x1a\xc8\x01\n\x13RequestMirrorPolicy\x12\x18\n\x07\x63luster\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x1d\n\x0bruntime_key\x18\x02 \x01(\tB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12\x45\n\x10runtime_fraction\x18\x03 \x01(\x0b\x32+.envoy.api.v2.core.RuntimeFractionalPercent\x12\x31\n\rtrace_sampled\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x1a\xc7\x05\n\nHashPolicy\x12\x43\n\x06header\x18\x01 \x01(\x0b\x32\x31.envoy.api.v2.route.RouteAction.HashPolicy.HeaderH\x00\x12\x43\n\x06\x63ookie\x18\x02 \x01(\x0b\x32\x31.envoy.api.v2.route.RouteAction.HashPolicy.CookieH\x00\x12`\n\x15\x63onnection_properties\x18\x03 \x01(\x0b\x32?.envoy.api.v2.route.RouteAction.HashPolicy.ConnectionPropertiesH\x00\x12T\n\x0fquery_parameter\x18\x05 \x01(\x0b\x32\x39.envoy.api.v2.route.RouteAction.HashPolicy.QueryParameterH\x00\x12N\n\x0c\x66ilter_state\x18\x06 \x01(\x0b\x32\x36.envoy.api.v2.route.RouteAction.HashPolicy.FilterStateH\x00\x12\x10\n\x08terminal\x18\x04 \x01(\x08\x1a,\n\x06Header\x12\"\n\x0bheader_name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08 \x01\xc0\x01\x01\xc8\x01\x00\x1aU\n\x06\x43ookie\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12&\n\x03ttl\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x0c\n\x04path\x18\x03 \x01(\t\x1a)\n\x14\x43onnectionProperties\x12\x11\n\tsource_ip\x18\x01 \x01(\x08\x1a\'\n\x0eQueryParameter\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x1a#\n\x0b\x46ilterState\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x42\x17\n\x10policy_specifier\x12\x03\xf8\x42\x01\x1a_\n\rUpgradeConfig\x12!\n\x0cupgrade_type\x18\x01 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12+\n\x07\x65nabled\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\"E\n\x1b\x43lusterNotFoundResponseCode\x12\x17\n\x13SERVICE_UNAVAILABLE\x10\x00\x12\r\n\tNOT_FOUND\x10\x01\"Z\n\x16InternalRedirectAction\x12\"\n\x1ePASS_THROUGH_INTERNAL_REDIRECT\x10\x00\x12\x1c\n\x18HANDLE_INTERNAL_REDIRECT\x10\x01\x42\x18\n\x11\x63luster_specifier\x12\x03\xf8\x42\x01\x42\x18\n\x16host_rewrite_specifierJ\x04\x08\x0c\x10\rJ\x04\x08\x12\x10\x13J\x04\x08\x13\x10\x14J\x04\x08\x10\x10\x11J\x04\x08\x16\x10\x17J\x04\x08\x15\x10\x16\"\xed\x07\n\x0bRetryPolicy\x12\x10\n\x08retry_on\x18\x01 \x01(\t\x12\x31\n\x0bnum_retries\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x32\n\x0fper_try_timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x45\n\x0eretry_priority\x18\x04 \x01(\x0b\x32-.envoy.api.v2.route.RetryPolicy.RetryPriority\x12P\n\x14retry_host_predicate\x18\x05 \x03(\x0b\x32\x32.envoy.api.v2.route.RetryPolicy.RetryHostPredicate\x12)\n!host_selection_retry_max_attempts\x18\x06 \x01(\x03\x12\x1e\n\x16retriable_status_codes\x18\x07 \x03(\r\x12\x44\n\x0eretry_back_off\x18\x08 \x01(\x0b\x32,.envoy.api.v2.route.RetryPolicy.RetryBackOff\x12<\n\x11retriable_headers\x18\t \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcher\x12\x44\n\x19retriable_request_headers\x18\n \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcher\x1a\x92\x01\n\rRetryPriority\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12-\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x02\x18\x01H\x00\x12,\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x42\r\n\x0b\x63onfig_type\x1a\x97\x01\n\x12RetryHostPredicate\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12-\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x02\x18\x01H\x00\x12,\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x42\r\n\x0b\x63onfig_type\x1a\x87\x01\n\x0cRetryBackOff\x12<\n\rbase_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\n\xfa\x42\x07\xaa\x01\x04\x08\x01*\x00\x12\x39\n\x0cmax_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\"\xb2\x01\n\x0bHedgePolicy\x12?\n\x10initial_requests\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(\x01\x12@\n\x19\x61\x64\x64itional_request_chance\x18\x02 \x01(\x0b\x32\x1d.envoy.type.FractionalPercent\x12 \n\x18hedge_on_per_try_timeout\x18\x03 \x01(\x08\"\xeb\x03\n\x0eRedirectAction\x12\x18\n\x0ehttps_redirect\x18\x04 \x01(\x08H\x00\x12\x19\n\x0fscheme_redirect\x18\x07 \x01(\tH\x00\x12\"\n\rhost_redirect\x18\x01 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12\x15\n\rport_redirect\x18\x08 \x01(\r\x12$\n\rpath_redirect\x18\x02 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00H\x01\x12%\n\x0eprefix_rewrite\x18\x05 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00H\x01\x12X\n\rresponse_code\x18\x03 \x01(\x0e\x32\x37.envoy.api.v2.route.RedirectAction.RedirectResponseCodeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x13\n\x0bstrip_query\x18\x06 \x01(\x08\"w\n\x14RedirectResponseCode\x12\x15\n\x11MOVED_PERMANENTLY\x10\x00\x12\t\n\x05\x46OUND\x10\x01\x12\r\n\tSEE_OTHER\x10\x02\x12\x16\n\x12TEMPORARY_REDIRECT\x10\x03\x12\x16\n\x12PERMANENT_REDIRECT\x10\x04\x42\x1a\n\x18scheme_rewrite_specifierB\x18\n\x16path_rewrite_specifier\"_\n\x14\x44irectResponseAction\x12\x1a\n\x06status\x18\x01 \x01(\rB\n\xfa\x42\x07*\x05\x10\xd8\x04(d\x12+\n\x04\x62ody\x18\x02 \x01(\x0b\x32\x1d.envoy.api.v2.core.DataSource\"V\n\tDecorator\x12\x1a\n\toperation\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12-\n\tpropagate\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\"\xe9\x01\n\x07Tracing\x12\x36\n\x0f\x63lient_sampling\x18\x01 \x01(\x0b\x32\x1d.envoy.type.FractionalPercent\x12\x36\n\x0frandom_sampling\x18\x02 \x01(\x0b\x32\x1d.envoy.type.FractionalPercent\x12\x37\n\x10overall_sampling\x18\x03 \x01(\x0b\x32\x1d.envoy.type.FractionalPercent\x12\x35\n\x0b\x63ustom_tags\x18\x04 \x03(\x0b\x32 .envoy.type.tracing.v2.CustomTag\"\xba\x01\n\x0eVirtualCluster\x12!\n\x07pattern\x18\x01 \x01(\tB\x10\x18\x01\xfa\x42\x05r\x03(\x80\x08\xb8\xee\xf2\xd2\x05\x01\x12\x32\n\x07headers\x18\x04 \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcher\x12\x15\n\x04name\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12:\n\x06method\x18\x03 \x01(\x0e\x32 .envoy.api.v2.core.RequestMethodB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\"\x84\x08\n\tRateLimit\x12\x34\n\x05stage\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02\x18\n\x12\x13\n\x0b\x64isable_key\x18\x02 \x01(\t\x12?\n\x07\x61\x63tions\x18\x03 \x03(\x0b\x32$.envoy.api.v2.route.RateLimit.ActionB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\xea\x06\n\x06\x41\x63tion\x12L\n\x0esource_cluster\x18\x01 \x01(\x0b\x32\x32.envoy.api.v2.route.RateLimit.Action.SourceClusterH\x00\x12V\n\x13\x64\x65stination_cluster\x18\x02 \x01(\x0b\x32\x37.envoy.api.v2.route.RateLimit.Action.DestinationClusterH\x00\x12N\n\x0frequest_headers\x18\x03 \x01(\x0b\x32\x33.envoy.api.v2.route.RateLimit.Action.RequestHeadersH\x00\x12L\n\x0eremote_address\x18\x04 \x01(\x0b\x32\x32.envoy.api.v2.route.RateLimit.Action.RemoteAddressH\x00\x12\x46\n\x0bgeneric_key\x18\x05 \x01(\x0b\x32/.envoy.api.v2.route.RateLimit.Action.GenericKeyH\x00\x12S\n\x12header_value_match\x18\x06 \x01(\x0b\x32\x35.envoy.api.v2.route.RateLimit.Action.HeaderValueMatchH\x00\x1a\x0f\n\rSourceCluster\x1a\x14\n\x12\x44\x65stinationCluster\x1aU\n\x0eRequestHeaders\x12\"\n\x0bheader_name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08 \x01\xc0\x01\x01\xc8\x01\x00\x12\x1f\n\x0e\x64\x65scriptor_key\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x1a\x0f\n\rRemoteAddress\x1a/\n\nGenericKey\x12!\n\x10\x64\x65scriptor_value\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x1a\xa5\x01\n\x10HeaderValueMatch\x12!\n\x10\x64\x65scriptor_value\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x30\n\x0c\x65xpect_match\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12<\n\x07headers\x18\x03 \x03(\x0b\x32!.envoy.api.v2.route.HeaderMatcherB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x42\x17\n\x10\x61\x63tion_specifier\x12\x03\xf8\x42\x01\"\xf0\x02\n\rHeaderMatcher\x12\x1b\n\x04name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08 \x01\xc0\x01\x01\xc8\x01\x00\x12\x15\n\x0b\x65xact_match\x18\x04 \x01(\tH\x00\x12\'\n\x0bregex_match\x18\x05 \x01(\tB\x10\x18\x01\xfa\x42\x05r\x03(\x80\x08\xb8\xee\xf2\xd2\x05\x01H\x00\x12<\n\x10safe_regex_match\x18\x0b \x01(\x0b\x32 .envoy.type.matcher.RegexMatcherH\x00\x12-\n\x0brange_match\x18\x06 \x01(\x0b\x32\x16.envoy.type.Int64RangeH\x00\x12\x17\n\rpresent_match\x18\x07 \x01(\x08H\x00\x12\x1f\n\x0cprefix_match\x18\t \x01(\tB\x07\xfa\x42\x04r\x02 \x01H\x00\x12\x1f\n\x0csuffix_match\x18\n \x01(\tB\x07\xfa\x42\x04r\x02 \x01H\x00\x12\x14\n\x0cinvert_match\x18\x08 \x01(\x08\x42\x18\n\x16header_match_specifierJ\x04\x08\x02\x10\x03J\x04\x08\x03\x10\x04\"\x80\x02\n\x15QueryParameterMatcher\x12\x18\n\x04name\x18\x01 \x01(\tB\n\xfa\x42\x07r\x05 \x01(\x80\x08\x12\x17\n\x05value\x18\x03 \x01(\tB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12\x33\n\x05regex\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.BoolValueB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12\x43\n\x0cstring_match\x18\x05 \x01(\x0b\x32!.envoy.type.matcher.StringMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12\x17\n\rpresent_match\x18\x06 \x01(\x08H\x00\x42!\n\x1fquery_parameter_match_specifierB\x9a\x01\n io.envoyproxy.envoy.api.v2.routeB\x14RouteComponentsProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/api/v2/route\xf2\x98\xfe\x8f\x05\x17\x12\x15\x65nvoy.config.route.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.route.route_components_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.api.v2.routeB\024RouteComponentsProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/api/v2/route\362\230\376\217\005\027\022\025envoy.config.route.v3\272\200\310\321\006\002\020\001'
  _VIRTUALHOST_PERFILTERCONFIGENTRY._options = None
  _VIRTUALHOST_PERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _VIRTUALHOST_TYPEDPERFILTERCONFIGENTRY._options = None
  _VIRTUALHOST_TYPEDPERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _VIRTUALHOST.fields_by_name['name']._options = None
  _VIRTUALHOST.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _VIRTUALHOST.fields_by_name['domains']._options = None
  _VIRTUALHOST.fields_by_name['domains']._serialized_options = b'\372B\017\222\001\014\010\001\"\010r\006\300\001\002\310\001\000'
  _VIRTUALHOST.fields_by_name['require_tls']._options = None
  _VIRTUALHOST.fields_by_name['require_tls']._serialized_options = b'\372B\005\202\001\002\020\001'
  _VIRTUALHOST.fields_by_name['request_headers_to_add']._options = None
  _VIRTUALHOST.fields_by_name['request_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _VIRTUALHOST.fields_by_name['response_headers_to_add']._options = None
  _VIRTUALHOST.fields_by_name['response_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _VIRTUALHOST.fields_by_name['per_filter_config']._options = None
  _VIRTUALHOST.fields_by_name['per_filter_config']._serialized_options = b'\030\001'
  _ROUTE_PERFILTERCONFIGENTRY._options = None
  _ROUTE_PERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _ROUTE_TYPEDPERFILTERCONFIGENTRY._options = None
  _ROUTE_TYPEDPERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _ROUTE.oneofs_by_name['action']._options = None
  _ROUTE.oneofs_by_name['action']._serialized_options = b'\370B\001'
  _ROUTE.fields_by_name['match']._options = None
  _ROUTE.fields_by_name['match']._serialized_options = b'\372B\005\212\001\002\020\001'
  _ROUTE.fields_by_name['per_filter_config']._options = None
  _ROUTE.fields_by_name['per_filter_config']._serialized_options = b'\030\001'
  _ROUTE.fields_by_name['request_headers_to_add']._options = None
  _ROUTE.fields_by_name['request_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _ROUTE.fields_by_name['response_headers_to_add']._options = None
  _ROUTE.fields_by_name['response_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT_PERFILTERCONFIGENTRY._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT_PERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT_TYPEDPERFILTERCONFIGENTRY._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT_TYPEDPERFILTERCONFIGENTRY._serialized_options = b'8\001'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['name']._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['request_headers_to_add']._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['request_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['response_headers_to_add']._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['response_headers_to_add']._serialized_options = b'\372B\006\222\001\003\020\350\007'
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['per_filter_config']._options = None
  _WEIGHTEDCLUSTER_CLUSTERWEIGHT.fields_by_name['per_filter_config']._serialized_options = b'\030\001'
  _WEIGHTEDCLUSTER.fields_by_name['clusters']._options = None
  _WEIGHTEDCLUSTER.fields_by_name['clusters']._serialized_options = b'\372B\005\222\001\002\010\001'
  _WEIGHTEDCLUSTER.fields_by_name['total_weight']._options = None
  _WEIGHTEDCLUSTER.fields_by_name['total_weight']._serialized_options = b'\372B\004*\002(\001'
  _ROUTEMATCH.oneofs_by_name['path_specifier']._options = None
  _ROUTEMATCH.oneofs_by_name['path_specifier']._serialized_options = b'\370B\001'
  _ROUTEMATCH.fields_by_name['regex']._options = None
  _ROUTEMATCH.fields_by_name['regex']._serialized_options = b'\030\001\372B\005r\003(\200\010\270\356\362\322\005\001'
  _ROUTEMATCH.fields_by_name['safe_regex']._options = None
  _ROUTEMATCH.fields_by_name['safe_regex']._serialized_options = b'\372B\005\212\001\002\020\001'
  _CORSPOLICY.fields_by_name['allow_origin']._options = None
  _CORSPOLICY.fields_by_name['allow_origin']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _CORSPOLICY.fields_by_name['allow_origin_regex']._options = None
  _CORSPOLICY.fields_by_name['allow_origin_regex']._serialized_options = b'\030\001\372B\n\222\001\007\"\005r\003(\200\010'
  _CORSPOLICY.fields_by_name['enabled']._options = None
  _CORSPOLICY.fields_by_name['enabled']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _ROUTEACTION_REQUESTMIRRORPOLICY.fields_by_name['cluster']._options = None
  _ROUTEACTION_REQUESTMIRRORPOLICY.fields_by_name['cluster']._serialized_options = b'\372B\004r\002 \001'
  _ROUTEACTION_REQUESTMIRRORPOLICY.fields_by_name['runtime_key']._options = None
  _ROUTEACTION_REQUESTMIRRORPOLICY.fields_by_name['runtime_key']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _ROUTEACTION_HASHPOLICY_HEADER.fields_by_name['header_name']._options = None
  _ROUTEACTION_HASHPOLICY_HEADER.fields_by_name['header_name']._serialized_options = b'\372B\nr\010 \001\300\001\001\310\001\000'
  _ROUTEACTION_HASHPOLICY_COOKIE.fields_by_name['name']._options = None
  _ROUTEACTION_HASHPOLICY_COOKIE.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _ROUTEACTION_HASHPOLICY_QUERYPARAMETER.fields_by_name['name']._options = None
  _ROUTEACTION_HASHPOLICY_QUERYPARAMETER.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _ROUTEACTION_HASHPOLICY_FILTERSTATE.fields_by_name['key']._options = None
  _ROUTEACTION_HASHPOLICY_FILTERSTATE.fields_by_name['key']._serialized_options = b'\372B\004r\002 \001'
  _ROUTEACTION_HASHPOLICY.oneofs_by_name['policy_specifier']._options = None
  _ROUTEACTION_HASHPOLICY.oneofs_by_name['policy_specifier']._serialized_options = b'\370B\001'
  _ROUTEACTION_UPGRADECONFIG.fields_by_name['upgrade_type']._options = None
  _ROUTEACTION_UPGRADECONFIG.fields_by_name['upgrade_type']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _ROUTEACTION.oneofs_by_name['cluster_specifier']._options = None
  _ROUTEACTION.oneofs_by_name['cluster_specifier']._serialized_options = b'\370B\001'
  _ROUTEACTION.fields_by_name['cluster']._options = None
  _ROUTEACTION.fields_by_name['cluster']._serialized_options = b'\372B\004r\002 \001'
  _ROUTEACTION.fields_by_name['cluster_header']._options = None
  _ROUTEACTION.fields_by_name['cluster_header']._serialized_options = b'\372B\nr\010 \001\300\001\001\310\001\000'
  _ROUTEACTION.fields_by_name['cluster_not_found_response_code']._options = None
  _ROUTEACTION.fields_by_name['cluster_not_found_response_code']._serialized_options = b'\372B\005\202\001\002\020\001'
  _ROUTEACTION.fields_by_name['prefix_rewrite']._options = None
  _ROUTEACTION.fields_by_name['prefix_rewrite']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _ROUTEACTION.fields_by_name['host_rewrite']._options = None
  _ROUTEACTION.fields_by_name['host_rewrite']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000\362\230\376\217\005\026\n\024host_rewrite_literal'
  _ROUTEACTION.fields_by_name['auto_host_rewrite_header']._options = None
  _ROUTEACTION.fields_by_name['auto_host_rewrite_header']._serialized_options = b'\372B\010r\006\300\001\001\310\001\000\362\230\376\217\005\025\n\023host_rewrite_header'
  _ROUTEACTION.fields_by_name['request_mirror_policy']._options = None
  _ROUTEACTION.fields_by_name['request_mirror_policy']._serialized_options = b'\030\001'
  _ROUTEACTION.fields_by_name['priority']._options = None
  _ROUTEACTION.fields_by_name['priority']._serialized_options = b'\372B\005\202\001\002\020\001'
  _RETRYPOLICY_RETRYPRIORITY.fields_by_name['name']._options = None
  _RETRYPOLICY_RETRYPRIORITY.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _RETRYPOLICY_RETRYPRIORITY.fields_by_name['config']._options = None
  _RETRYPOLICY_RETRYPRIORITY.fields_by_name['config']._serialized_options = b'\030\001'
  _RETRYPOLICY_RETRYHOSTPREDICATE.fields_by_name['name']._options = None
  _RETRYPOLICY_RETRYHOSTPREDICATE.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _RETRYPOLICY_RETRYHOSTPREDICATE.fields_by_name['config']._options = None
  _RETRYPOLICY_RETRYHOSTPREDICATE.fields_by_name['config']._serialized_options = b'\030\001'
  _RETRYPOLICY_RETRYBACKOFF.fields_by_name['base_interval']._options = None
  _RETRYPOLICY_RETRYBACKOFF.fields_by_name['base_interval']._serialized_options = b'\372B\007\252\001\004\010\001*\000'
  _RETRYPOLICY_RETRYBACKOFF.fields_by_name['max_interval']._options = None
  _RETRYPOLICY_RETRYBACKOFF.fields_by_name['max_interval']._serialized_options = b'\372B\005\252\001\002*\000'
  _HEDGEPOLICY.fields_by_name['initial_requests']._options = None
  _HEDGEPOLICY.fields_by_name['initial_requests']._serialized_options = b'\372B\004*\002(\001'
  _REDIRECTACTION.fields_by_name['host_redirect']._options = None
  _REDIRECTACTION.fields_by_name['host_redirect']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _REDIRECTACTION.fields_by_name['path_redirect']._options = None
  _REDIRECTACTION.fields_by_name['path_redirect']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _REDIRECTACTION.fields_by_name['prefix_rewrite']._options = None
  _REDIRECTACTION.fields_by_name['prefix_rewrite']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _REDIRECTACTION.fields_by_name['response_code']._options = None
  _REDIRECTACTION.fields_by_name['response_code']._serialized_options = b'\372B\005\202\001\002\020\001'
  _DIRECTRESPONSEACTION.fields_by_name['status']._options = None
  _DIRECTRESPONSEACTION.fields_by_name['status']._serialized_options = b'\372B\007*\005\020\330\004(d'
  _DECORATOR.fields_by_name['operation']._options = None
  _DECORATOR.fields_by_name['operation']._serialized_options = b'\372B\004r\002 \001'
  _VIRTUALCLUSTER.fields_by_name['pattern']._options = None
  _VIRTUALCLUSTER.fields_by_name['pattern']._serialized_options = b'\030\001\372B\005r\003(\200\010\270\356\362\322\005\001'
  _VIRTUALCLUSTER.fields_by_name['name']._options = None
  _VIRTUALCLUSTER.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _VIRTUALCLUSTER.fields_by_name['method']._options = None
  _VIRTUALCLUSTER.fields_by_name['method']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _RATELIMIT_ACTION_REQUESTHEADERS.fields_by_name['header_name']._options = None
  _RATELIMIT_ACTION_REQUESTHEADERS.fields_by_name['header_name']._serialized_options = b'\372B\nr\010 \001\300\001\001\310\001\000'
  _RATELIMIT_ACTION_REQUESTHEADERS.fields_by_name['descriptor_key']._options = None
  _RATELIMIT_ACTION_REQUESTHEADERS.fields_by_name['descriptor_key']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMIT_ACTION_GENERICKEY.fields_by_name['descriptor_value']._options = None
  _RATELIMIT_ACTION_GENERICKEY.fields_by_name['descriptor_value']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMIT_ACTION_HEADERVALUEMATCH.fields_by_name['descriptor_value']._options = None
  _RATELIMIT_ACTION_HEADERVALUEMATCH.fields_by_name['descriptor_value']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMIT_ACTION_HEADERVALUEMATCH.fields_by_name['headers']._options = None
  _RATELIMIT_ACTION_HEADERVALUEMATCH.fields_by_name['headers']._serialized_options = b'\372B\005\222\001\002\010\001'
  _RATELIMIT_ACTION.oneofs_by_name['action_specifier']._options = None
  _RATELIMIT_ACTION.oneofs_by_name['action_specifier']._serialized_options = b'\370B\001'
  _RATELIMIT.fields_by_name['stage']._options = None
  _RATELIMIT.fields_by_name['stage']._serialized_options = b'\372B\004*\002\030\n'
  _RATELIMIT.fields_by_name['actions']._options = None
  _RATELIMIT.fields_by_name['actions']._serialized_options = b'\372B\005\222\001\002\010\001'
  _HEADERMATCHER.fields_by_name['name']._options = None
  _HEADERMATCHER.fields_by_name['name']._serialized_options = b'\372B\nr\010 \001\300\001\001\310\001\000'
  _HEADERMATCHER.fields_by_name['regex_match']._options = None
  _HEADERMATCHER.fields_by_name['regex_match']._serialized_options = b'\030\001\372B\005r\003(\200\010\270\356\362\322\005\001'
  _HEADERMATCHER.fields_by_name['prefix_match']._options = None
  _HEADERMATCHER.fields_by_name['prefix_match']._serialized_options = b'\372B\004r\002 \001'
  _HEADERMATCHER.fields_by_name['suffix_match']._options = None
  _HEADERMATCHER.fields_by_name['suffix_match']._serialized_options = b'\372B\004r\002 \001'
  _QUERYPARAMETERMATCHER.fields_by_name['name']._options = None
  _QUERYPARAMETERMATCHER.fields_by_name['name']._serialized_options = b'\372B\007r\005 \001(\200\010'
  _QUERYPARAMETERMATCHER.fields_by_name['value']._options = None
  _QUERYPARAMETERMATCHER.fields_by_name['value']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _QUERYPARAMETERMATCHER.fields_by_name['regex']._options = None
  _QUERYPARAMETERMATCHER.fields_by_name['regex']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _QUERYPARAMETERMATCHER.fields_by_name['string_match']._options = None
  _QUERYPARAMETERMATCHER.fields_by_name['string_match']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_VIRTUALHOST']._serialized_start=497
  _globals['_VIRTUALHOST']._serialized_end=1816
  _globals['_VIRTUALHOST_PERFILTERCONFIGENTRY']._serialized_start=1588
  _globals['_VIRTUALHOST_PERFILTERCONFIGENTRY']._serialized_end=1667
  _globals['_VIRTUALHOST_TYPEDPERFILTERCONFIGENTRY']._serialized_start=1669
  _globals['_VIRTUALHOST_TYPEDPERFILTERCONFIGENTRY']._serialized_end=1750
  _globals['_VIRTUALHOST_TLSREQUIREMENTTYPE']._serialized_start=1752
  _globals['_VIRTUALHOST_TLSREQUIREMENTTYPE']._serialized_end=1810
  _globals['_FILTERACTION']._serialized_start=1818
  _globals['_FILTERACTION']._serialized_end=1870
  _globals['_ROUTE']._serialized_start=1873
  _globals['_ROUTE']._serialized_end=2982
  _globals['_ROUTE_PERFILTERCONFIGENTRY']._serialized_start=1588
  _globals['_ROUTE_PERFILTERCONFIGENTRY']._serialized_end=1667
  _globals['_ROUTE_TYPEDPERFILTERCONFIGENTRY']._serialized_start=1669
  _globals['_ROUTE_TYPEDPERFILTERCONFIGENTRY']._serialized_end=1750
  _globals['_WEIGHTEDCLUSTER']._serialized_start=2985
  _globals['_WEIGHTEDCLUSTER']._serialized_end=3927
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT']._serialized_start=3173
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT']._serialized_end=3927
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT_PERFILTERCONFIGENTRY']._serialized_start=1588
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT_PERFILTERCONFIGENTRY']._serialized_end=1667
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT_TYPEDPERFILTERCONFIGENTRY']._serialized_start=1669
  _globals['_WEIGHTEDCLUSTER_CLUSTERWEIGHT_TYPEDPERFILTERCONFIGENTRY']._serialized_end=1750
  _globals['_ROUTEMATCH']._serialized_start=3930
  _globals['_ROUTEMATCH']._serialized_end=4639
  _globals['_ROUTEMATCH_GRPCROUTEMATCHOPTIONS']._serialized_start=4467
  _globals['_ROUTEMATCH_GRPCROUTEMATCHOPTIONS']._serialized_end=4490
  _globals['_ROUTEMATCH_TLSCONTEXTMATCHOPTIONS']._serialized_start=4492
  _globals['_ROUTEMATCH_TLSCONTEXTMATCHOPTIONS']._serialized_end=4610
  _globals['_CORSPOLICY']._serialized_start=4642
  _globals['_CORSPOLICY']._serialized_end=5161
  _globals['_ROUTEACTION']._serialized_start=5164
  _globals['_ROUTEACTION']._serialized_end=8099
  _globals['_ROUTEACTION_REQUESTMIRRORPOLICY']._serialized_start=6837
  _globals['_ROUTEACTION_REQUESTMIRRORPOLICY']._serialized_end=7037
  _globals['_ROUTEACTION_HASHPOLICY']._serialized_start=7040
  _globals['_ROUTEACTION_HASHPOLICY']._serialized_end=7751
  _globals['_ROUTEACTION_HASHPOLICY_HEADER']._serialized_start=7474
  _globals['_ROUTEACTION_HASHPOLICY_HEADER']._serialized_end=7518
  _globals['_ROUTEACTION_HASHPOLICY_COOKIE']._serialized_start=7520
  _globals['_ROUTEACTION_HASHPOLICY_COOKIE']._serialized_end=7605
  _globals['_ROUTEACTION_HASHPOLICY_CONNECTIONPROPERTIES']._serialized_start=7607
  _globals['_ROUTEACTION_HASHPOLICY_CONNECTIONPROPERTIES']._serialized_end=7648
  _globals['_ROUTEACTION_HASHPOLICY_QUERYPARAMETER']._serialized_start=7650
  _globals['_ROUTEACTION_HASHPOLICY_QUERYPARAMETER']._serialized_end=7689
  _globals['_ROUTEACTION_HASHPOLICY_FILTERSTATE']._serialized_start=7691
  _globals['_ROUTEACTION_HASHPOLICY_FILTERSTATE']._serialized_end=7726
  _globals['_ROUTEACTION_UPGRADECONFIG']._serialized_start=7753
  _globals['_ROUTEACTION_UPGRADECONFIG']._serialized_end=7848
  _globals['_ROUTEACTION_CLUSTERNOTFOUNDRESPONSECODE']._serialized_start=7850
  _globals['_ROUTEACTION_CLUSTERNOTFOUNDRESPONSECODE']._serialized_end=7919
  _globals['_ROUTEACTION_INTERNALREDIRECTACTION']._serialized_start=7921
  _globals['_ROUTEACTION_INTERNALREDIRECTACTION']._serialized_end=8011
  _globals['_RETRYPOLICY']._serialized_start=8102
  _globals['_RETRYPOLICY']._serialized_end=9107
  _globals['_RETRYPOLICY_RETRYPRIORITY']._serialized_start=8669
  _globals['_RETRYPOLICY_RETRYPRIORITY']._serialized_end=8815
  _globals['_RETRYPOLICY_RETRYHOSTPREDICATE']._serialized_start=8818
  _globals['_RETRYPOLICY_RETRYHOSTPREDICATE']._serialized_end=8969
  _globals['_RETRYPOLICY_RETRYBACKOFF']._serialized_start=8972
  _globals['_RETRYPOLICY_RETRYBACKOFF']._serialized_end=9107
  _globals['_HEDGEPOLICY']._serialized_start=9110
  _globals['_HEDGEPOLICY']._serialized_end=9288
  _globals['_REDIRECTACTION']._serialized_start=9291
  _globals['_REDIRECTACTION']._serialized_end=9782
  _globals['_REDIRECTACTION_REDIRECTRESPONSECODE']._serialized_start=9609
  _globals['_REDIRECTACTION_REDIRECTRESPONSECODE']._serialized_end=9728
  _globals['_DIRECTRESPONSEACTION']._serialized_start=9784
  _globals['_DIRECTRESPONSEACTION']._serialized_end=9879
  _globals['_DECORATOR']._serialized_start=9881
  _globals['_DECORATOR']._serialized_end=9967
  _globals['_TRACING']._serialized_start=9970
  _globals['_TRACING']._serialized_end=10203
  _globals['_VIRTUALCLUSTER']._serialized_start=10206
  _globals['_VIRTUALCLUSTER']._serialized_end=10392
  _globals['_RATELIMIT']._serialized_start=10395
  _globals['_RATELIMIT']._serialized_end=11423
  _globals['_RATELIMIT_ACTION']._serialized_start=10549
  _globals['_RATELIMIT_ACTION']._serialized_end=11423
  _globals['_RATELIMIT_ACTION_SOURCECLUSTER']._serialized_start=11040
  _globals['_RATELIMIT_ACTION_SOURCECLUSTER']._serialized_end=11055
  _globals['_RATELIMIT_ACTION_DESTINATIONCLUSTER']._serialized_start=11057
  _globals['_RATELIMIT_ACTION_DESTINATIONCLUSTER']._serialized_end=11077
  _globals['_RATELIMIT_ACTION_REQUESTHEADERS']._serialized_start=11079
  _globals['_RATELIMIT_ACTION_REQUESTHEADERS']._serialized_end=11164
  _globals['_RATELIMIT_ACTION_REMOTEADDRESS']._serialized_start=11166
  _globals['_RATELIMIT_ACTION_REMOTEADDRESS']._serialized_end=11181
  _globals['_RATELIMIT_ACTION_GENERICKEY']._serialized_start=11183
  _globals['_RATELIMIT_ACTION_GENERICKEY']._serialized_end=11230
  _globals['_RATELIMIT_ACTION_HEADERVALUEMATCH']._serialized_start=11233
  _globals['_RATELIMIT_ACTION_HEADERVALUEMATCH']._serialized_end=11398
  _globals['_HEADERMATCHER']._serialized_start=11426
  _globals['_HEADERMATCHER']._serialized_end=11794
  _globals['_QUERYPARAMETERMATCHER']._serialized_start=11797
  _globals['_QUERYPARAMETERMATCHER']._serialized_end=12053
