
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nBenvoy/extensions/retry/host/previous_hosts/v3/previous_hosts.proto\x12-envoy.extensions.retry.host.previous_hosts.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\\\n\x16PreviousHostsPredicate:B\x9a\xc5\x88\x1e=\n;envoy.config.retry.previous_hosts.v2.PreviousHostsPredicateB\xc2\x01\n;io.envoyproxy.envoy.extensions.retry.host.previous_hosts.v3B\x12PreviousHostsProtoP\x01Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/previous_hosts/v3;previous_hostsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.retry.host.previous_hosts.v3.previous_hosts_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n;io.envoyproxy.envoy.extensions.retry.host.previous_hosts.v3B\022PreviousHostsProtoP\001Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/previous_hosts/v3;previous_hostsv3\272\200\310\321\006\002\020\002'
  _PREVIOUSHOSTSPREDICATE._options = None
  _PREVIOUSHOSTSPREDICATE._serialized_options = b'\232\305\210\036=\n;envoy.config.retry.previous_hosts.v2.PreviousHostsPredicate'
  _globals['_PREVIOUSHOSTSPREDICATE']._serialized_start=183
  _globals['_PREVIOUSHOSTSPREDICATE']._serialized_end=275
