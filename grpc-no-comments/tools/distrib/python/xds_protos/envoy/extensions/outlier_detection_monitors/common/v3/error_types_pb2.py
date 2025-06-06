
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import range_pb2 as envoy_dot_type_dot_v3_dot_range__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGenvoy/extensions/outlier_detection_monitors/common/v3/error_types.proto\x12\x35\x65nvoy.extensions.outlier_detection_monitors.common.v3\x1a\x19\x65nvoy/type/v3/range.proto\x1a\x1dudpa/annotations/status.proto\"6\n\nHttpErrors\x12(\n\x05range\x18\x01 \x01(\x0b\x32\x19.envoy.type.v3.Int32Range\"\x13\n\x11LocalOriginErrors\"\x10\n\x0e\x44\x61tabaseErrors\"\xad\x02\n\x0c\x45rrorBuckets\x12V\n\x0bhttp_errors\x18\x01 \x03(\x0b\x32\x41.envoy.extensions.outlier_detection_monitors.common.v3.HttpErrors\x12\x65\n\x13local_origin_errors\x18\x02 \x03(\x0b\x32H.envoy.extensions.outlier_detection_monitors.common.v3.LocalOriginErrors\x12^\n\x0f\x64\x61tabase_errors\x18\x03 \x03(\x0b\x32\x45.envoy.extensions.outlier_detection_monitors.common.v3.DatabaseErrorsB\xc7\x01\nCio.envoyproxy.envoy.extensions.outlier_detection_monitors.common.v3B\x0f\x45rrorTypesProtoP\x01Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/outlier_detection_monitors/common/v3;commonv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.outlier_detection_monitors.common.v3.error_types_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nCio.envoyproxy.envoy.extensions.outlier_detection_monitors.common.v3B\017ErrorTypesProtoP\001Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/outlier_detection_monitors/common/v3;commonv3\272\200\310\321\006\002\020\002'
  _globals['_HTTPERRORS']._serialized_start=188
  _globals['_HTTPERRORS']._serialized_end=242
  _globals['_LOCALORIGINERRORS']._serialized_start=244
  _globals['_LOCALORIGINERRORS']._serialized_end=263
  _globals['_DATABASEERRORS']._serialized_start=265
  _globals['_DATABASEERRORS']._serialized_end=281
  _globals['_ERRORBUCKETS']._serialized_start=284
  _globals['_ERRORBUCKETS']._serialized_end=585
