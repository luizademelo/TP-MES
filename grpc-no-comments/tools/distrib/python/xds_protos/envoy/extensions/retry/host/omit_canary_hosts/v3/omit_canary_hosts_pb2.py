
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nHenvoy/extensions/retry/host/omit_canary_hosts/v3/omit_canary_hosts.proto\x12\x30\x65nvoy.extensions.retry.host.omit_canary_hosts.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"c\n\x18OmitCanaryHostsPredicate:G\x9a\xc5\x88\x1e\x42\n@envoy.config.retry.omit_canary_hosts.v2.OmitCanaryHostsPredicateB\xcd\x01\n>io.envoyproxy.envoy.extensions.retry.host.omit_canary_hosts.v3B\x14OmitCanaryHostsProtoP\x01Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/omit_canary_hosts/v3;omit_canary_hostsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.retry.host.omit_canary_hosts.v3.omit_canary_hosts_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.retry.host.omit_canary_hosts.v3B\024OmitCanaryHostsProtoP\001Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/omit_canary_hosts/v3;omit_canary_hostsv3\272\200\310\321\006\002\020\002'
  _OMITCANARYHOSTSPREDICATE._options = None
  _OMITCANARYHOSTSPREDICATE._serialized_options = b'\232\305\210\036B\n@envoy.config.retry.omit_canary_hosts.v2.OmitCanaryHostsPredicate'
  _globals['_OMITCANARYHOSTSPREDICATE']._serialized_start=192
  _globals['_OMITCANARYHOSTSPREDICATE']._serialized_end=291
