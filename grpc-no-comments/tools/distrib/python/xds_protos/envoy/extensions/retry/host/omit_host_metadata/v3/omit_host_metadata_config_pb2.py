
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nQenvoy/extensions/retry/host/omit_host_metadata/v3/omit_host_metadata_config.proto\x12\x31\x65nvoy.extensions.retry.host.omit_host_metadata.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\x98\x01\n\x16OmitHostMetadataConfig\x12\x36\n\x0emetadata_match\x18\x01 \x01(\x0b\x32\x1e.envoy.config.core.v3.Metadata:F\x9a\xc5\x88\x1e\x41\n?envoy.config.retry.omit_host_metadata.v2.OmitHostMetadataConfigB\xd7\x01\n?io.envoyproxy.envoy.extensions.retry.host.omit_host_metadata.v3B\x1bOmitHostMetadataConfigProtoP\x01Zmgithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/omit_host_metadata/v3;omit_host_metadatav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.retry.host.omit_host_metadata.v3.omit_host_metadata_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.retry.host.omit_host_metadata.v3B\033OmitHostMetadataConfigProtoP\001Zmgithub.com/envoyproxy/go-control-plane/envoy/extensions/retry/host/omit_host_metadata/v3;omit_host_metadatav3\272\200\310\321\006\002\020\002'
  _OMITHOSTMETADATACONFIG._options = None
  _OMITHOSTMETADATACONFIG._serialized_options = b'\232\305\210\036A\n?envoy.config.retry.omit_host_metadata.v2.OmitHostMetadataConfig'
  _globals['_OMITHOSTMETADATACONFIG']._serialized_start=236
  _globals['_OMITHOSTMETADATACONFIG']._serialized_end=388
