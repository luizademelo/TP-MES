
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n1envoy/extensions/clusters/common/dns/v3/dns.proto\x12\'envoy.extensions.clusters.common.dns.v3\x1a\x1dudpa/annotations/status.proto*a\n\x0f\x44nsLookupFamily\x12\x0f\n\x0bUNSPECIFIED\x10\x00\x12\x08\n\x04\x41UTO\x10\x01\x12\x0b\n\x07V4_ONLY\x10\x02\x12\x0b\n\x07V6_ONLY\x10\x03\x12\x10\n\x0cV4_PREFERRED\x10\x04\x12\x07\n\x03\x41LL\x10\x05\x42\xa1\x01\n5io.envoyproxy.envoy.extensions.clusters.common.dns.v3B\x08\x44nsProtoP\x01ZTgithub.com/envoyproxy/go-control-plane/envoy/extensions/clusters/common/dns/v3;dnsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.clusters.common.dns.v3.dns_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n5io.envoyproxy.envoy.extensions.clusters.common.dns.v3B\010DnsProtoP\001ZTgithub.com/envoyproxy/go-control-plane/envoy/extensions/clusters/common/dns/v3;dnsv3\272\200\310\321\006\002\020\002'
  _globals['_DNSLOOKUPFAMILY']._serialized_start=125
  _globals['_DNSLOOKUPFAMILY']._serialized_end=222
