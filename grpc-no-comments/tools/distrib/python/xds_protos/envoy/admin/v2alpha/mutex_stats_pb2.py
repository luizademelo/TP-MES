
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/admin/v2alpha/mutex_stats.proto\x12\x13\x65nvoy.admin.v2alpha\x1a\x1dudpa/annotations/status.proto\"`\n\nMutexStats\x12\x17\n\x0fnum_contentions\x18\x01 \x01(\x04\x12\x1b\n\x13\x63urrent_wait_cycles\x18\x02 \x01(\x04\x12\x1c\n\x14lifetime_wait_cycles\x18\x03 \x01(\x04\x42z\n!io.envoyproxy.envoy.admin.v2alphaB\x0fMutexStatsProtoP\x01Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v2alpha.mutex_stats_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.envoyproxy.envoy.admin.v2alphaB\017MutexStatsProtoP\001Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\272\200\310\321\006\002\020\001'
  _globals['_MUTEXSTATS']._serialized_start=93
  _globals['_MUTEXSTATS']._serialized_end=189
