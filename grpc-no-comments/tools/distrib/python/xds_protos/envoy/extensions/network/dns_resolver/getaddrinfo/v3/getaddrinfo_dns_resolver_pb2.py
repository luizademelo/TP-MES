
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nSenvoy/extensions/network/dns_resolver/getaddrinfo/v3/getaddrinfo_dns_resolver.proto\x12\x34\x65nvoy.extensions.network.dns_resolver.getaddrinfo.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\"Q\n\x1cGetAddrInfoDnsResolverConfig\x12\x31\n\x0bnum_retries\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\xd6\x01\nBio.envoyproxy.envoy.extensions.network.dns_resolver.getaddrinfo.v3B\x1bGetaddrinfoDnsResolverProtoP\x01Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/network/dns_resolver/getaddrinfo/v3;getaddrinfov3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.network.dns_resolver.getaddrinfo.v3.getaddrinfo_dns_resolver_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nBio.envoyproxy.envoy.extensions.network.dns_resolver.getaddrinfo.v3B\033GetaddrinfoDnsResolverProtoP\001Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/network/dns_resolver/getaddrinfo/v3;getaddrinfov3\272\200\310\321\006\002\020\002'
  _globals['_GETADDRINFODNSRESOLVERCONFIG']._serialized_start=204
  _globals['_GETADDRINFODNSRESOLVERCONFIG']._serialized_end=285
