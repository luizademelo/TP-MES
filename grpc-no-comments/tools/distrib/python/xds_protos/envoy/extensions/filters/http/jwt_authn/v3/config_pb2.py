
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import http_uri_pb2 as envoy_dot_config_dot_core_dot_v3_dot_http__uri__pb2
from envoy.config.route.v3 import route_components_pb2 as envoy_dot_config_dot_route_dot_v3_dot_route__components__pb2
from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7envoy/extensions/filters/http/jwt_authn/v3/config.proto\x12*envoy.extensions.filters.http.jwt_authn.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a#envoy/config/core/v3/http_uri.proto\x1a,envoy/config/route/v3/route_components.proto\x1a\"envoy/type/matcher/v3/string.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xd9\x08\n\x0bJwtProvider\x12\x0e\n\x06issuer\x18\x01 \x01(\t\x12\x11\n\taudiences\x18\x02 \x03(\t\x12\x36\n\x08subjects\x18\x13 \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcher\x12\x1a\n\x12require_expiration\x18\x14 \x01(\x08\x12/\n\x0cmax_lifetime\x18\x15 \x01(\x0b\x32\x19.google.protobuf.Duration\x12M\n\x0bremote_jwks\x18\x03 \x01(\x0b\x32\x36.envoy.extensions.filters.http.jwt_authn.v3.RemoteJwksH\x00\x12\x36\n\nlocal_jwks\x18\x04 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceH\x00\x12\x0f\n\x07\x66orward\x18\x05 \x01(\x08\x12K\n\x0c\x66rom_headers\x18\x06 \x03(\x0b\x32\x35.envoy.extensions.filters.http.jwt_authn.v3.JwtHeader\x12\x13\n\x0b\x66rom_params\x18\x07 \x03(\t\x12\x14\n\x0c\x66rom_cookies\x18\r \x03(\t\x12+\n\x16\x66orward_payload_header\x18\x08 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x01\xc8\x01\x00\x12\"\n\x1apad_forward_payload_header\x18\x0b \x01(\x08\x12\x1b\n\x13payload_in_metadata\x18\t \x01(\t\x12o\n\x1dnormalize_payload_in_metadata\x18\x12 \x01(\x0b\x32H.envoy.extensions.filters.http.jwt_authn.v3.JwtProvider.NormalizePayload\x12\x1a\n\x12header_in_metadata\x18\x0e \x01(\t\x12!\n\x19\x66\x61iled_status_in_metadata\x18\x10 \x01(\t\x12\x1a\n\x12\x63lock_skew_seconds\x18\n \x01(\r\x12T\n\x10jwt_cache_config\x18\x0c \x01(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtCacheConfig\x12V\n\x10\x63laim_to_headers\x18\x0f \x03(\x0b\x32<.envoy.extensions.filters.http.jwt_authn.v3.JwtClaimToHeader\x12\x19\n\x11\x63lear_route_cache\x18\x11 \x01(\x08\x1a\x32\n\x10NormalizePayload\x12\x1e\n\x16space_delimited_claims\x18\x01 \x03(\t:=\x9a\xc5\x88\x1e\x38\n6envoy.config.filter.http.jwt_authn.v2alpha.JwtProviderB\x1c\n\x15jwks_source_specifier\x12\x03\xf8\x42\x01\"(\n\x0eJwtCacheConfig\x12\x16\n\x0ejwt_cache_size\x18\x01 \x01(\r\"\xd8\x02\n\nRemoteJwks\x12\x39\n\x08http_uri\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.HttpUriB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12G\n\x0e\x63\x61\x63he_duration\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x14\xfa\x42\x11\xaa\x01\x0e\x1a\x06\x08\x80\xb4\xc4\xc3!2\x04\x10\xc0\x84=\x12O\n\x0b\x61sync_fetch\x18\x03 \x01(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwksAsyncFetch\x12\x37\n\x0cretry_policy\x18\x04 \x01(\x0b\x32!.envoy.config.core.v3.RetryPolicy:<\x9a\xc5\x88\x1e\x37\n5envoy.config.filter.http.jwt_authn.v2alpha.RemoteJwks\"c\n\x0eJwksAsyncFetch\x12\x15\n\rfast_listener\x18\x01 \x01(\x08\x12:\n\x17\x66\x61iled_refetch_duration\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\"\x88\x01\n\tJwtHeader\x12\x1b\n\x04name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x00\x12!\n\x0cvalue_prefix\x18\x02 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00:;\x9a\xc5\x88\x1e\x36\n4envoy.config.filter.http.jwt_authn.v2alpha.JwtHeader\"\x8a\x01\n\x15ProviderWithAudiences\x12\x15\n\rprovider_name\x18\x01 \x01(\t\x12\x11\n\taudiences\x18\x02 \x03(\t:G\x9a\xc5\x88\x1e\x42\n@envoy.config.filter.http.jwt_authn.v2alpha.ProviderWithAudiences\"\x82\x04\n\x0eJwtRequirement\x12\x17\n\rprovider_name\x18\x01 \x01(\tH\x00\x12\x63\n\x16provider_and_audiences\x18\x02 \x01(\x0b\x32\x41.envoy.extensions.filters.http.jwt_authn.v3.ProviderWithAudiencesH\x00\x12X\n\x0crequires_any\x18\x03 \x01(\x0b\x32@.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirementOrListH\x00\x12Y\n\x0crequires_all\x18\x04 \x01(\x0b\x32\x41.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirementAndListH\x00\x12\x39\n\x17\x61llow_missing_or_failed\x18\x05 \x01(\x0b\x32\x16.google.protobuf.EmptyH\x00\x12/\n\rallow_missing\x18\x06 \x01(\x0b\x32\x16.google.protobuf.EmptyH\x00:@\x9a\xc5\x88\x1e;\n9envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirementB\x0f\n\rrequires_type\"\xba\x01\n\x14JwtRequirementOrList\x12Z\n\x0crequirements\x18\x01 \x03(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirementB\x08\xfa\x42\x05\x92\x01\x02\x08\x02:F\x9a\xc5\x88\x1e\x41\n?envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirementOrList\"\xbc\x01\n\x15JwtRequirementAndList\x12Z\n\x0crequirements\x18\x01 \x03(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirementB\x08\xfa\x42\x05\x92\x01\x02\x08\x02:G\x9a\xc5\x88\x1e\x42\n@envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirementAndList\"\x99\x02\n\x0fRequirementRule\x12:\n\x05match\x18\x01 \x01(\x0b\x32!.envoy.config.route.v3.RouteMatchB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12N\n\x08requires\x18\x02 \x01(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirementH\x00\x12#\n\x10requirement_name\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00:A\x9a\xc5\x88\x1e<\n:envoy.config.filter.http.jwt_authn.v2alpha.RequirementRuleB\x12\n\x10requirement_type\"\xb5\x02\n\x0f\x46ilterStateRule\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12[\n\x08requires\x18\x03 \x03(\x0b\x32I.envoy.extensions.filters.http.jwt_authn.v3.FilterStateRule.RequiresEntry\x1ak\n\rRequiresEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12I\n\x05value\x18\x02 \x01(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirement:\x02\x38\x01:A\x9a\xc5\x88\x1e<\n:envoy.config.filter.http.jwt_authn.v2alpha.FilterStateRule\"\xe7\x05\n\x11JwtAuthentication\x12_\n\tproviders\x18\x01 \x03(\x0b\x32L.envoy.extensions.filters.http.jwt_authn.v3.JwtAuthentication.ProvidersEntry\x12J\n\x05rules\x18\x02 \x03(\x0b\x32;.envoy.extensions.filters.http.jwt_authn.v3.RequirementRule\x12W\n\x12\x66ilter_state_rules\x18\x03 \x01(\x0b\x32;.envoy.extensions.filters.http.jwt_authn.v3.FilterStateRule\x12\x1d\n\x15\x62ypass_cors_preflight\x18\x04 \x01(\x08\x12j\n\x0frequirement_map\x18\x05 \x03(\x0b\x32Q.envoy.extensions.filters.http.jwt_authn.v3.JwtAuthentication.RequirementMapEntry\x12\x1e\n\x16strip_failure_response\x18\x06 \x01(\x08\x1ai\n\x0eProvidersEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x46\n\x05value\x18\x02 \x01(\x0b\x32\x37.envoy.extensions.filters.http.jwt_authn.v3.JwtProvider:\x02\x38\x01\x1aq\n\x13RequirementMapEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12I\n\x05value\x18\x02 \x01(\x0b\x32:.envoy.extensions.filters.http.jwt_authn.v3.JwtRequirement:\x02\x38\x01:C\x9a\xc5\x88\x1e>\n<envoy.config.filter.http.jwt_authn.v2alpha.JwtAuthentication\"p\n\x0ePerRouteConfig\x12\x1b\n\x08\x64isabled\x18\x01 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12#\n\x10requirement_name\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x42\x1c\n\x15requirement_specifier\x12\x03\xf8\x42\x01\"S\n\x10JwtClaimToHeader\x12\"\n\x0bheader_name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x00\x12\x1b\n\nclaim_name\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xb0\x01\n8io.envoyproxy.envoy.extensions.filters.http.jwt_authn.v3B\x0b\x43onfigProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/jwt_authn/v3;jwt_authnv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.jwt_authn.v3.config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.extensions.filters.http.jwt_authn.v3B\013ConfigProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/jwt_authn/v3;jwt_authnv3\272\200\310\321\006\002\020\002'
  _JWTPROVIDER.oneofs_by_name['jwks_source_specifier']._options = None
  _JWTPROVIDER.oneofs_by_name['jwks_source_specifier']._serialized_options = b'\370B\001'
  _JWTPROVIDER.fields_by_name['forward_payload_header']._options = None
  _JWTPROVIDER.fields_by_name['forward_payload_header']._serialized_options = b'\372B\010r\006\300\001\001\310\001\000'
  _JWTPROVIDER._options = None
  _JWTPROVIDER._serialized_options = b'\232\305\210\0368\n6envoy.config.filter.http.jwt_authn.v2alpha.JwtProvider'
  _REMOTEJWKS.fields_by_name['http_uri']._options = None
  _REMOTEJWKS.fields_by_name['http_uri']._serialized_options = b'\372B\005\212\001\002\020\001'
  _REMOTEJWKS.fields_by_name['cache_duration']._options = None
  _REMOTEJWKS.fields_by_name['cache_duration']._serialized_options = b'\372B\021\252\001\016\032\006\010\200\264\304\303!2\004\020\300\204='
  _REMOTEJWKS._options = None
  _REMOTEJWKS._serialized_options = b'\232\305\210\0367\n5envoy.config.filter.http.jwt_authn.v2alpha.RemoteJwks'
  _JWTHEADER.fields_by_name['name']._options = None
  _JWTHEADER.fields_by_name['name']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\000'
  _JWTHEADER.fields_by_name['value_prefix']._options = None
  _JWTHEADER.fields_by_name['value_prefix']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _JWTHEADER._options = None
  _JWTHEADER._serialized_options = b'\232\305\210\0366\n4envoy.config.filter.http.jwt_authn.v2alpha.JwtHeader'
  _PROVIDERWITHAUDIENCES._options = None
  _PROVIDERWITHAUDIENCES._serialized_options = b'\232\305\210\036B\n@envoy.config.filter.http.jwt_authn.v2alpha.ProviderWithAudiences'
  _JWTREQUIREMENT._options = None
  _JWTREQUIREMENT._serialized_options = b'\232\305\210\036;\n9envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirement'
  _JWTREQUIREMENTORLIST.fields_by_name['requirements']._options = None
  _JWTREQUIREMENTORLIST.fields_by_name['requirements']._serialized_options = b'\372B\005\222\001\002\010\002'
  _JWTREQUIREMENTORLIST._options = None
  _JWTREQUIREMENTORLIST._serialized_options = b'\232\305\210\036A\n?envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirementOrList'
  _JWTREQUIREMENTANDLIST.fields_by_name['requirements']._options = None
  _JWTREQUIREMENTANDLIST.fields_by_name['requirements']._serialized_options = b'\372B\005\222\001\002\010\002'
  _JWTREQUIREMENTANDLIST._options = None
  _JWTREQUIREMENTANDLIST._serialized_options = b'\232\305\210\036B\n@envoy.config.filter.http.jwt_authn.v2alpha.JwtRequirementAndList'
  _REQUIREMENTRULE.fields_by_name['match']._options = None
  _REQUIREMENTRULE.fields_by_name['match']._serialized_options = b'\372B\005\212\001\002\020\001'
  _REQUIREMENTRULE.fields_by_name['requirement_name']._options = None
  _REQUIREMENTRULE.fields_by_name['requirement_name']._serialized_options = b'\372B\004r\002\020\001'
  _REQUIREMENTRULE._options = None
  _REQUIREMENTRULE._serialized_options = b'\232\305\210\036<\n:envoy.config.filter.http.jwt_authn.v2alpha.RequirementRule'
  _FILTERSTATERULE_REQUIRESENTRY._options = None
  _FILTERSTATERULE_REQUIRESENTRY._serialized_options = b'8\001'
  _FILTERSTATERULE.fields_by_name['name']._options = None
  _FILTERSTATERULE.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _FILTERSTATERULE._options = None
  _FILTERSTATERULE._serialized_options = b'\232\305\210\036<\n:envoy.config.filter.http.jwt_authn.v2alpha.FilterStateRule'
  _JWTAUTHENTICATION_PROVIDERSENTRY._options = None
  _JWTAUTHENTICATION_PROVIDERSENTRY._serialized_options = b'8\001'
  _JWTAUTHENTICATION_REQUIREMENTMAPENTRY._options = None
  _JWTAUTHENTICATION_REQUIREMENTMAPENTRY._serialized_options = b'8\001'
  _JWTAUTHENTICATION._options = None
  _JWTAUTHENTICATION._serialized_options = b'\232\305\210\036>\n<envoy.config.filter.http.jwt_authn.v2alpha.JwtAuthentication'
  _PERROUTECONFIG.oneofs_by_name['requirement_specifier']._options = None
  _PERROUTECONFIG.oneofs_by_name['requirement_specifier']._serialized_options = b'\370B\001'
  _PERROUTECONFIG.fields_by_name['disabled']._options = None
  _PERROUTECONFIG.fields_by_name['disabled']._serialized_options = b'\372B\004j\002\010\001'
  _PERROUTECONFIG.fields_by_name['requirement_name']._options = None
  _PERROUTECONFIG.fields_by_name['requirement_name']._serialized_options = b'\372B\004r\002\020\001'
  _JWTCLAIMTOHEADER.fields_by_name['header_name']._options = None
  _JWTCLAIMTOHEADER.fields_by_name['header_name']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\000'
  _JWTCLAIMTOHEADER.fields_by_name['claim_name']._options = None
  _JWTCLAIMTOHEADER.fields_by_name['claim_name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_JWTPROVIDER']._serialized_start=408
  _globals['_JWTPROVIDER']._serialized_end=1521
  _globals['_JWTPROVIDER_NORMALIZEPAYLOAD']._serialized_start=1378
  _globals['_JWTPROVIDER_NORMALIZEPAYLOAD']._serialized_end=1428
  _globals['_JWTCACHECONFIG']._serialized_start=1523
  _globals['_JWTCACHECONFIG']._serialized_end=1563
  _globals['_REMOTEJWKS']._serialized_start=1566
  _globals['_REMOTEJWKS']._serialized_end=1910
  _globals['_JWKSASYNCFETCH']._serialized_start=1912
  _globals['_JWKSASYNCFETCH']._serialized_end=2011
  _globals['_JWTHEADER']._serialized_start=2014
  _globals['_JWTHEADER']._serialized_end=2150
  _globals['_PROVIDERWITHAUDIENCES']._serialized_start=2153
  _globals['_PROVIDERWITHAUDIENCES']._serialized_end=2291
  _globals['_JWTREQUIREMENT']._serialized_start=2294
  _globals['_JWTREQUIREMENT']._serialized_end=2808
  _globals['_JWTREQUIREMENTORLIST']._serialized_start=2811
  _globals['_JWTREQUIREMENTORLIST']._serialized_end=2997
  _globals['_JWTREQUIREMENTANDLIST']._serialized_start=3000
  _globals['_JWTREQUIREMENTANDLIST']._serialized_end=3188
  _globals['_REQUIREMENTRULE']._serialized_start=3191
  _globals['_REQUIREMENTRULE']._serialized_end=3472
  _globals['_FILTERSTATERULE']._serialized_start=3475
  _globals['_FILTERSTATERULE']._serialized_end=3784
  _globals['_FILTERSTATERULE_REQUIRESENTRY']._serialized_start=3610
  _globals['_FILTERSTATERULE_REQUIRESENTRY']._serialized_end=3717
  _globals['_JWTAUTHENTICATION']._serialized_start=3787
  _globals['_JWTAUTHENTICATION']._serialized_end=4530
  _globals['_JWTAUTHENTICATION_PROVIDERSENTRY']._serialized_start=4241
  _globals['_JWTAUTHENTICATION_PROVIDERSENTRY']._serialized_end=4346
  _globals['_JWTAUTHENTICATION_REQUIREMENTMAPENTRY']._serialized_start=4348
  _globals['_JWTAUTHENTICATION_REQUIREMENTMAPENTRY']._serialized_end=4461
  _globals['_PERROUTECONFIG']._serialized_start=4532
  _globals['_PERROUTECONFIG']._serialized_end=4644
  _globals['_JWTCLAIMTOHEADER']._serialized_start=4646
  _globals['_JWTCLAIMTOHEADER']._serialized_end=4729
