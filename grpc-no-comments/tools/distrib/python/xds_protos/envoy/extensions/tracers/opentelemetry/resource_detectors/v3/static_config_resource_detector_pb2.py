
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nbenvoy/extensions/tracers/opentelemetry/resource_detectors/v3/static_config_resource_detector.proto\x12<envoy.extensions.tracers.opentelemetry.resource_detectors.v3\x1a\x1dudpa/annotations/status.proto\"\xde\x01\n\"StaticConfigResourceDetectorConfig\x12\x84\x01\n\nattributes\x18\x01 \x03(\x0b\x32p.envoy.extensions.tracers.opentelemetry.resource_detectors.v3.StaticConfigResourceDetectorConfig.AttributesEntry\x1a\x31\n\x0f\x41ttributesEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x42\xf3\x01\nJio.envoyproxy.envoy.extensions.tracers.opentelemetry.resource_detectors.v3B!StaticConfigResourceDetectorProtoP\x01Zxgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/resource_detectors/v3;resource_detectorsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.tracers.opentelemetry.resource_detectors.v3.static_config_resource_detector_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nJio.envoyproxy.envoy.extensions.tracers.opentelemetry.resource_detectors.v3B!StaticConfigResourceDetectorProtoP\001Zxgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/resource_detectors/v3;resource_detectorsv3\272\200\310\321\006\002\020\002'
  _STATICCONFIGRESOURCEDETECTORCONFIG_ATTRIBUTESENTRY._options = None
  _STATICCONFIGRESOURCEDETECTORCONFIG_ATTRIBUTESENTRY._serialized_options = b'8\001'
  _globals['_STATICCONFIGRESOURCEDETECTORCONFIG']._serialized_start=196
  _globals['_STATICCONFIGRESOURCEDETECTORCONFIG']._serialized_end=418
  _globals['_STATICCONFIGRESOURCEDETECTORCONFIG_ATTRIBUTESENTRY']._serialized_start=369
  _globals['_STATICCONFIGRESOURCEDETECTORCONFIG_ATTRIBUTESENTRY']._serialized_end=418
