
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDenvoy/extensions/filters/listener/original_src/v3/original_src.proto\x12\x31\x65nvoy.extensions.filters.listener.original_src.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"u\n\x0bOriginalSrc\x12\x11\n\tbind_port\x18\x01 \x01(\x08\x12\x0c\n\x04mark\x18\x02 \x01(\r:E\x9a\xc5\x88\x1e@\n>envoy.config.filter.listener.original_src.v2alpha1.OriginalSrcB\xc6\x01\n?io.envoyproxy.envoy.extensions.filters.listener.original_src.v3B\x10OriginalSrcProtoP\x01Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/listener/original_src/v3;original_srcv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.listener.original_src.v3.original_src_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.filters.listener.original_src.v3B\020OriginalSrcProtoP\001Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/listener/original_src/v3;original_srcv3\272\200\310\321\006\002\020\002'
  _ORIGINALSRC._options = None
  _ORIGINALSRC._serialized_options = b'\232\305\210\036@\n>envoy.config.filter.listener.original_src.v2alpha1.OriginalSrc'
  _globals['_ORIGINALSRC']._serialized_start=189
  _globals['_ORIGINALSRC']._serialized_end=306
