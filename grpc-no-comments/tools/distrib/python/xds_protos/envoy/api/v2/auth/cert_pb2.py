
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from envoy.api.v2.auth import common_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_common__pb2
from envoy.api.v2.auth import secret_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_secret__pb2
from envoy.api.v2.auth import tls_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_tls__pb2

from envoy.api.v2.auth.common_pb2 import *
from envoy.api.v2.auth.secret_pb2 import *
from envoy.api.v2.auth.tls_pb2 import *

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1c\x65nvoy/api/v2/auth/cert.proto\x12\x11\x65nvoy.api.v2.auth\x1a\x1eudpa/annotations/migrate.proto\x1a\x1e\x65nvoy/api/v2/auth/common.proto\x1a\x1e\x65nvoy/api/v2/auth/secret.proto\x1a\x1b\x65nvoy/api/v2/auth/tls.protoB\x99\x01\n\x1fio.envoyproxy.envoy.api.v2.authB\tCertProtoP\x01Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/auth\xf2\x98\xfe\x8f\x05+\x12)envoy.extensions.transport_sockets.tls.v3P\x01P\x02P\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.auth.cert_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\037io.envoyproxy.envoy.api.v2.authB\tCertProtoP\001Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/auth\362\230\376\217\005+\022)envoy.extensions.transport_sockets.tls.v3'
