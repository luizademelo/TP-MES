
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?envoy/extensions/matching/common_inputs/ssl/v3/ssl_inputs.proto\x12.envoy.extensions.matching.common_inputs.ssl.v3\x1a\x1dudpa/annotations/status.proto\"\r\n\x0bUriSanInput\"\r\n\x0b\x44nsSanInput\"\x0e\n\x0cSubjectInputB\xb5\x01\n<io.envoyproxy.envoy.extensions.matching.common_inputs.ssl.v3B\x0eSslInputsProtoP\x01Z[github.com/envoyproxy/go-control-plane/envoy/extensions/matching/common_inputs/ssl/v3;sslv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.matching.common_inputs.ssl.v3.ssl_inputs_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n<io.envoyproxy.envoy.extensions.matching.common_inputs.ssl.v3B\016SslInputsProtoP\001Z[github.com/envoyproxy/go-control-plane/envoy/extensions/matching/common_inputs/ssl/v3;sslv3\272\200\310\321\006\002\020\002'
  _globals['_URISANINPUT']._serialized_start=146
  _globals['_URISANINPUT']._serialized_end=159
  _globals['_DNSSANINPUT']._serialized_start=161
  _globals['_DNSSANINPUT']._serialized_end=174
  _globals['_SUBJECTINPUT']._serialized_start=176
  _globals['_SUBJECTINPUT']._serialized_end=190
