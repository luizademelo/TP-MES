
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n envoy/admin/v2alpha/memory.proto\x12\x13\x65nvoy.admin.v2alpha\x1a\x1dudpa/annotations/status.proto\"\x9a\x01\n\x06Memory\x12\x11\n\tallocated\x18\x01 \x01(\x04\x12\x11\n\theap_size\x18\x02 \x01(\x04\x12\x19\n\x11pageheap_unmapped\x18\x03 \x01(\x04\x12\x15\n\rpageheap_free\x18\x04 \x01(\x04\x12\x1a\n\x12total_thread_cache\x18\x05 \x01(\x04\x12\x1c\n\x14total_physical_bytes\x18\x06 \x01(\x04\x42v\n!io.envoyproxy.envoy.admin.v2alphaB\x0bMemoryProtoP\x01Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v2alpha.memory_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.envoyproxy.envoy.admin.v2alphaB\013MemoryProtoP\001Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\272\200\310\321\006\002\020\001'
  _globals['_MEMORY']._serialized_start=89
  _globals['_MEMORY']._serialized_end=243
