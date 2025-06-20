Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary protocol buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize symbol database for protocol buffers
_sym_db = _symbol_database.Default()

# Import various protocol buffer definitions from Envoy and other dependencies
from envoy.config.common.mutation_rules.v3 import mutation_rules_pb2 as envoy_dot_config_dot_common_dot_mutation__rules_dot_v3_dot_mutation__rules__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import config_source_pb2 as envoy_dot_config_dot_core_dot_v3_dot_config__source__pb2
from envoy.config.core.v3 import grpc_service_pb2 as envoy_dot_config_dot_core_dot_v3_dot_grpc__service__pb2
from envoy.config.core.v3 import http_uri_pb2 as envoy_dot_config_dot_core_dot_v3_dot_http__uri__pb2
from envoy.type.matcher.v3 import metadata_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_metadata__pb2
from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from envoy.type.v3 import http_status_pb2 as envoy_dot_type_dot_v3_dot_http__status__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import sensitive_pb2 as udpa_dot_annotations_dot_sensitive__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the main descriptor for the ExtAuthz proto file
# This contains the serialized protocol buffer definition
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n:envoy/extensions/filters/http/ext_authz/v3/ext_authz.proto\x12*envoy.extensions.filters.http.ext_authz.v3\x1a:envoy/config/common/mutation_rules/v3/mutation_rules.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a(envoy/config/core/v3/config_source.proto\x1a\'envoy/config/core/v3/grpc_service.proto\x1a#envoy/config/core/v3/http_uri.proto\x1a$envoy/type/matcher/v3/metadata.proto\x1a\"envoy/type/matcher/v3/string.proto\x1a\x1f\x65nvoy/type/v3/http_status.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a udpa/annotations/sensitive.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x9a\x0c\n\x08\x45xtAuthz\x12\x39\n\x0cgrpc_service\x18\x01 \x01(\x0b\x32!.envoy.config.core.v3.GrpcServiceH\x00\x12O\n\x0chttp_service\x18\x03 \x01(\x0b\x32\x37.envoy.extensions.filters.http.ext_authz.v3.HttpServiceH\x00\x12I\n\x15transport_api_version\x18\x0c \x01(\x0e\x32 .envoy.config.core.v3.ApiVersionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x1a\n\x12\x66\x61ilure_mode_allow\x18\x02 \x01(\x08\x12%\n\x1d\x66\x61ilure_mode_allow_header_add\x18\x13 \x01(\x08\x12U\n\x11with_request_body\x18\x05 \x01(\x0b\x32:.envoy.extensions.filters.http.ext_authz.v3.BufferSettings\x12\x19\n\x11\x63lear_route_cache\x18\x06 \x01(\x08\x12\x32\n\x0fstatus_on_error\x18\x07 \x01(\x0b\x32\x19.envoy.type.v3.HttpStatus\x12\x1a\n\x12validate_mutations\x18\x18 \x01(\x08\x12#\n\x1bmetadata_context_namespaces\x18\x08 \x03(\t\x12)\n!typed_metadata_context_namespaces\x18\x10 \x03(\t\x12)\n!route_metadata_context_namespaces\x18\x15 \x03(\t\x12/\n\'route_typed_metadata_context_namespaces\x18\x16 \x03(\t\x12\x46\n\x0e\x66ilter_enabled\x18\t \x01(\x0b\x32..envoy.config.core.v3.RuntimeFractionalPercent\x12G\n\x17\x66ilter_enabled_metadata\x18\x0e \x01(\x0b\x32&.envoy.type.matcher.v3.MetadataMatcher\x12\x41\n\x0f\x64\x65ny_at_disable\x18\x0b \x01(\x0b\x32(.envoy.config.core.v3.RuntimeFeatureFlag\x12 \n\x18include_peer_certificate\x18\n \x01(\x08\x12\x13\n\x0bstat_prefix\x18\r \x01(\t\x12%\n\x1d\x62ootstrap_metadata_labels_key\x18\x0f \x01(\t\x12\x41\n\x0f\x61llowed_headers\x18\x11 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12\x44\n\x12\x64isallowed_headers\x18\x19 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12\x1b\n\x13include_tls_session\x18\x12 \x01(\x08\x12\x41\n\x1d\x63harge_cluster_response_stats\x18\x14 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x1a\n\x12\x65ncode_raw_headers\x18\x17 \x01(\x08\x12\x61\n\x1d\x64\x65\x63oder_header_mutation_rules\x18\x1a \x01(\x0b\x32:.envoy.config.common.mutation_rules.v3.HeaderMutationRules\x12\x45\n!enable_dynamic_metadata_ingestion\x18\x1b \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x30\n\x0f\x66ilter_metadata\x18\x1c \x01(\x0b\x32\x17.google.protobuf.Struct\x12\x1f\n\x17\x65mit_filter_state_stats\x18\x1d \x01(\x08:5\x9a\xc5\x88\x1e\x30\n.envoy.config.filter.http.ext_authz.v3.ExtAuthzB\n\n\x08servicesJ\x04\x08\x04\x10\x05R\tuse_alpha\"\xa7\x01\n\x0e\x42ufferSettings\x12\"\n\x11max_request_bytes\x18\x01 \x01(\rB\x07\xfa\x42\x04*\x02 \x00\x12\x1d\n\x15\x61llow_partial_message\x18\x02 \x01(\x08\x12\x15\n\rpack_as_bytes\x18\x03 \x01(\x08:;\x9a\xc5\x88\x1e\x36\n4envoy.config.filter.http.ext_authz.v2.BufferSettings\"\xeb\x02\n\x0bHttpService\x12\x31\n\nserver_uri\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.HttpUri\x12\x13\n\x0bpath_prefix\x18\x02 \x01(\t\x12_\n\x15\x61uthorization_request\x18\x07 \x01(\x0b\x32@.envoy.extensions.filters.http.ext_authz.v3.AuthorizationRequest\x12\x61\n\x16\x61uthorization_response\x18\x08 \x01(\x0b\x32\x41.envoy.extensions.filters.http.ext_authz.v3.AuthorizationResponse:8\x9a\xc5\x88\x1e\x33\n1envoy.config.filter.http.ext_authz.v2.HttpServiceJ\x04\x08\x03\x10\x04J\x04\x08\x04\x10\x05J\x04\x08\x05\x10\x06J\x04\x08\x06\x10\x07\"\xe4\x01\n\x14\x41uthorizationRequest\x12N\n\x0f\x61llowed_headers\x18\x01 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcherB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x39\n\x0eheaders_to_add\x18\x02 \x03(\x0b\x32!.envoy.config.core.v3.HeaderValue:A\x9a\xc5\x88\x1e<\n:envoy.config.filter.http.ext_authz.v2.AuthorizationRequest\"\xed\x03\n\x15\x41uthorizationResponse\x12J\n\x18\x61llowed_upstream_headers\x18\x01 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12T\n\"allowed_upstream_headers_to_append\x18\x03 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12H\n\x16\x61llowed_client_headers\x18\x02 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12S\n!allowed_client_headers_on_success\x18\x04 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher\x12O\n\x1d\x64ynamic_metadata_from_headers\x18\x05 \x01(\x0b\x32(.envoy.type.matcher.v3.ListStringMatcher:B\x9a\xc5\x88\x1e=\n;envoy.config.filter.http.ext_authz.v2.AuthorizationResponse\"\xde\x01\n\x10\x45xtAuthzPerRoute\x12\x1b\n\x08\x64isabled\x18\x01 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12]\n\x0e\x63heck_settings\x18\x02 \x01(\x0b\x32\x39.envoy.extensions.filters.http.ext_authz.v3.CheckSettingsB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00:=\x9a\xc5\x88\x1e\x38\n6envoy.config.filter.http.ext_authz.v2.ExtAuthzPerRouteB\x0f\n\x08override\x12\x03\xf8\x42\x01\"\xfa\x02\n\rCheckSettings\x12t\n\x12\x63ontext_extensions\x18\x01 \x03(\x0b\x32P.envoy.extensions.filters.http.ext_authz.v3.CheckSettings.ContextExtensionsEntryB\x06\xb8\xb7\x8b\xa4\x02\x01\x12&\n\x1e\x64isable_request_body_buffering\x18\x02 \x01(\x08\x12U\n\x11with_request_body\x18\x03 \x01(\x0b\x32:.envoy.extensions.filters.http.ext_authz.v3.BufferSettings\x1a\x38\n\x16\x43ontextExtensionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01::\x9a\xc5\x88\x1e\x35\n3envoy.config.filter.http.ext_authz.v2.CheckSettingsB\xb2\x01\n8io.envoyproxy.envoy.extensions.filters.http.ext_authz.v3B\rExtAuthzProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/ext_authz/v3;ext_authzv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.ext_authz.v3.ext_authz_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  # Main descriptor options
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.extensions.filters.http.ext_authz.v3B\rExtAuthzProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/ext_authz/v3;ext_authzv3\272\200\310\321\006\002\020\002'
  
  # ExtAuthz message options
  _EXTAUTHZ.fields_by_name['transport_api_version']._options = None
  _EXTAUTHZ.fields_by_name['transport_api_version']._serialized_options = b'\372B\005\202\001\002\020\001'
  _EXTAUTHZ._options = None
  _EXTAUTHZ._serialized_options = b'\232\305\210\0360\n.envoy.config.filter.http.ext_authz.v3.ExtAuthz'
  
  # BufferSettings message options
  _BUFFERSETTINGS.fields_by_name['max_request_bytes']._options = None
  _BUFFERSETTINGS.fields_by_name['max_request_bytes']._serialized_options = b'\372B\004*\002 \000'
  _BUFFERSETTINGS._options = None
  _BUFFERSETTINGS._serialized_options = b'\232\305\210\0366\n4envoy.config.filter.http.ext_authz.v2.BufferSettings'
  
  # HttpService message options
  _HTTPSERVICE._options = None
  _HTTPSERVICE._serialized_options = b'\232\305\210\0363\n1envoy.config.filter.http.ext_authz.v2.HttpService'
  
  # AuthorizationRequest message options
  _AUTHORIZATIONREQUEST.fields_by_name['allowed_headers']._options = None
  _AUTHORIZATIONREQUEST.fields_by_name['allowed_headers']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _AUTHORIZATIONREQUEST._options = None
  _AUTHORIZATIONREQUEST._serialized_options = b'\232\305\210\036<\n:envoy.config.filter.http.ext_authz.v2.AuthorizationRequest'
  
  # AuthorizationResponse message options
  _AUTHORIZATIONRESPONSE._options = None
  _AUTHORIZATIONRESPONSE._serialized_options = b'\232\305\210\036=\n;envoy.config.filter.http.ext_authz.v2.AuthorizationResponse'
  
  # ExtAuthzPerRoute message options
  _EXTAUTHZPERROUTE.oneofs_by_name['override']._options = None
  _EXTAUTHZPERROUTE.oneofs_by_name['override']._serialized_options = b'\370B\001'
  _EXTAUTHZPERROUTE.fields_by_name['disabled']._options = None
  _EXTAUTHZPERROUTE.fields_by_name['disabled']._serialized_options = b'\372B\004j\002\010\001'
  _EXTAUTHZPERROUTE.fields_by_name['check_settings']._options = None
  _EXTAUTHZPERROUTE.fields_by_name['check_settings']._serialized_options = b'\372B\005\212\001\002\020\001'
  _EXTAUTHZPERROUTE._options = None
  _EXTAUTHZPERROUTE._serialized_options = b'\232\305\210\0368\n6envoy.config.filter.http.ext_authz.v2.ExtAuthzPerRoute'
  
  # CheckSettings message options
  _CHECKSETTINGS_CONTEXTEXTENSIONSENTRY._options = None
  _CHECKSETTINGS_CONTEXTEXTENSIONSENTRY._serialized_options = b'8\001'
  _CHECKSETTINGS.fields_by_name['context_extensions']._options = None
  _CHECKSETTINGS.fields_by_name['context_extensions']._serialized_options = b'\270\267\213\244\002\001'
  _CHECKSETTINGS._options = None
  _CHECKSETTINGS._serialized_options = b'\232\305\210\0365\n3envoy.config.filter.http.ext_authz.v2.CheckSettings'

# Define serialized start and end positions for each