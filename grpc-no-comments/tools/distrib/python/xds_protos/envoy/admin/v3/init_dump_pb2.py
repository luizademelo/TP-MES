
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/admin/v3/init_dump.proto\x12\x0e\x65nvoy.admin.v3\x1a\x1dudpa/annotations/status.proto\"\xa6\x01\n\x13UnreadyTargetsDumps\x12U\n\x15unready_targets_dumps\x18\x01 \x03(\x0b\x32\x36.envoy.admin.v3.UnreadyTargetsDumps.UnreadyTargetsDump\x1a\x38\n\x12UnreadyTargetsDump\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\x0ctarget_names\x18\x02 \x03(\tBv\n\x1cio.envoyproxy.envoy.admin.v3B\rInitDumpProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.init_dump_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\rInitDumpProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
  _globals['_UNREADYTARGETSDUMPS']._serialized_start=82
  _globals['_UNREADYTARGETSDUMPS']._serialized_end=248
  _globals['_UNREADYTARGETSDUMPS_UNREADYTARGETSDUMP']._serialized_start=192
  _globals['_UNREADYTARGETSDUMPS_UNREADYTARGETSDUMP']._serialized_end=248
