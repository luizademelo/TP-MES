
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/config/core/v3/resolver.proto\x12\x14\x65nvoy.config.core.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"W\n\x12\x44nsResolverOptions\x12\x1f\n\x17use_tcp_for_dns_lookups\x18\x01 \x01(\x08\x12 \n\x18no_default_search_domain\x18\x02 \x01(\x08\"\x99\x01\n\x13\x44nsResolutionConfig\x12:\n\tresolvers\x18\x01 \x03(\x0b\x32\x1d.envoy.config.core.v3.AddressB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x46\n\x14\x64ns_resolver_options\x18\x02 \x01(\x0b\x32(.envoy.config.core.v3.DnsResolverOptionsB\x81\x01\n\"io.envoyproxy.envoy.config.core.v3B\rResolverProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.resolver_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\rResolverProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
  _DNSRESOLUTIONCONFIG.fields_by_name['resolvers']._options = None
  _DNSRESOLUTIONCONFIG.fields_by_name['resolvers']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_DNSRESOLVEROPTIONS']._serialized_start=153
  _globals['_DNSRESOLVEROPTIONS']._serialized_end=240
  _globals['_DNSRESOLUTIONCONFIG']._serialized_start=243
  _globals['_DNSRESOLUTIONCONFIG']._serialized_end=396
