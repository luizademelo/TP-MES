
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/data/core/v3/tlv_metadata.proto\x12\x12\x65nvoy.data.core.v3\x1a\x1dudpa/annotations/status.proto\"\x91\x01\n\x0cTlvsMetadata\x12K\n\x0etyped_metadata\x18\x01 \x03(\x0b\x32\x33.envoy.data.core.v3.TlvsMetadata.TypedMetadataEntry\x1a\x34\n\x12TypedMetadataEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x0c:\x02\x38\x01\x42\x80\x01\n io.envoyproxy.envoy.data.core.v3B\x10TlvMetadataProtoP\x01Z@github.com/envoyproxy/go-control-plane/envoy/data/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.data.core.v3.tlv_metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.data.core.v3B\020TlvMetadataProtoP\001Z@github.com/envoyproxy/go-control-plane/envoy/data/core/v3;corev3\272\200\310\321\006\002\020\002'
  _TLVSMETADATA_TYPEDMETADATAENTRY._options = None
  _TLVSMETADATA_TYPEDMETADATAENTRY._serialized_options = b'8\001'
  _globals['_TLVSMETADATA']._serialized_start=93
  _globals['_TLVSMETADATA']._serialized_end=238
  _globals['_TLVSMETADATA_TYPEDMETADATAENTRY']._serialized_start=186
  _globals['_TLVSMETADATA_TYPEDMETADATAENTRY']._serialized_end=238
