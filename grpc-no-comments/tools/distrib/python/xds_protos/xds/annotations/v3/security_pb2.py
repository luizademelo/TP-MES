
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!xds/annotations/v3/security.proto\x12\x12xds.annotations.v3\x1a\x1fxds/annotations/v3/status.proto\x1a google/protobuf/descriptor.proto\"o\n\x17\x46ieldSecurityAnnotation\x12*\n\"configure_for_untrusted_downstream\x18\x01 \x01(\x08\x12(\n configure_for_untrusted_upstream\x18\x02 \x01(\x08:_\n\x08security\x12\x1d.google.protobuf.FieldOptions\x18\xa7\x96\x9d/ \x01(\x0b\x32+.xds.annotations.v3.FieldSecurityAnnotationB3Z)github.com/cncf/xds/go/xds/annotations/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.annotations.v3.security_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'Z)github.com/cncf/xds/go/xds/annotations/v3\322\306\244\341\006\002\010\001'
  _globals['_FIELDSECURITYANNOTATION']._serialized_start=124
  _globals['_FIELDSECURITYANNOTATION']._serialized_end=235
