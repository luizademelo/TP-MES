
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/config/trace/v2/lightstep.proto\x12\x15\x65nvoy.config.trace.v2\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x83\x02\n\x0fLightstepConfig\x12\"\n\x11\x63ollector_cluster\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\"\n\x11\x61\x63\x63\x65ss_token_file\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12`\n\x11propagation_modes\x18\x03 \x03(\x0e\x32\x36.envoy.config.trace.v2.LightstepConfig.PropagationModeB\r\xfa\x42\n\x92\x01\x07\"\x05\x82\x01\x02\x10\x01\"F\n\x0fPropagationMode\x12\t\n\x05\x45NVOY\x10\x00\x12\r\n\tLIGHTSTEP\x10\x01\x12\x06\n\x02\x42\x33\x10\x02\x12\x11\n\rTRACE_CONTEXT\x10\x03\x42\x85\x01\n#io.envoyproxy.envoy.config.trace.v2B\x0eLightstepProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.lightstep_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\016LightstepProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _LIGHTSTEPCONFIG.fields_by_name['collector_cluster']._options = None
  _LIGHTSTEPCONFIG.fields_by_name['collector_cluster']._serialized_options = b'\372B\004r\002 \001'
  _LIGHTSTEPCONFIG.fields_by_name['access_token_file']._options = None
  _LIGHTSTEPCONFIG.fields_by_name['access_token_file']._serialized_options = b'\372B\004r\002 \001'
  _LIGHTSTEPCONFIG.fields_by_name['propagation_modes']._options = None
  _LIGHTSTEPCONFIG.fields_by_name['propagation_modes']._serialized_options = b'\372B\n\222\001\007\"\005\202\001\002\020\001'
  _globals['_LIGHTSTEPCONFIG']._serialized_start=121
  _globals['_LIGHTSTEPCONFIG']._serialized_end=380
  _globals['_LIGHTSTEPCONFIG_PROPAGATIONMODE']._serialized_start=310
  _globals['_LIGHTSTEPCONFIG_PROPAGATIONMODE']._serialized_end=380
