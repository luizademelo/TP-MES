
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.data.tap.v3 import wrapper_pb2 as envoy_dot_data_dot_tap_dot_v3_dot_wrapper__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/service/tap/v3/tap.proto\x12\x14\x65nvoy.service.tap.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1f\x65nvoy/data/tap/v3/wrapper.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xe3\x02\n\x11StreamTapsRequest\x12\x46\n\nidentifier\x18\x01 \x01(\x0b\x32\x32.envoy.service.tap.v3.StreamTapsRequest.Identifier\x12\x10\n\x08trace_id\x18\x02 \x01(\x04\x12.\n\x05trace\x18\x03 \x01(\x0b\x32\x1f.envoy.data.tap.v3.TraceWrapper\x1a\x8f\x01\n\nIdentifier\x12\x32\n\x04node\x18\x01 \x01(\x0b\x32\x1a.envoy.config.core.v3.NodeB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0e\n\x06tap_id\x18\x02 \x01(\t:=\x9a\xc5\x88\x1e\x38\n6envoy.service.tap.v2alpha.StreamTapsRequest.Identifier:2\x9a\xc5\x88\x1e-\n+envoy.service.tap.v2alpha.StreamTapsRequest\"I\n\x12StreamTapsResponse:3\x9a\xc5\x88\x1e.\n,envoy.service.tap.v2alpha.StreamTapsResponse2u\n\x0eTapSinkService\x12\x63\n\nStreamTaps\x12\'.envoy.service.tap.v3.StreamTapsRequest\x1a(.envoy.service.tap.v3.StreamTapsResponse\"\x00(\x01\x42{\n\"io.envoyproxy.envoy.service.tap.v3B\x08TapProtoP\x01ZAgithub.com/envoyproxy/go-control-plane/envoy/service/tap/v3;tapv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.tap.v3.tap_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.service.tap.v3B\010TapProtoP\001ZAgithub.com/envoyproxy/go-control-plane/envoy/service/tap/v3;tapv3\272\200\310\321\006\002\020\002'
  _STREAMTAPSREQUEST_IDENTIFIER.fields_by_name['node']._options = None
  _STREAMTAPSREQUEST_IDENTIFIER.fields_by_name['node']._serialized_options = b'\372B\005\212\001\002\020\001'
  _STREAMTAPSREQUEST_IDENTIFIER._options = None
  _STREAMTAPSREQUEST_IDENTIFIER._serialized_options = b'\232\305\210\0368\n6envoy.service.tap.v2alpha.StreamTapsRequest.Identifier'
  _STREAMTAPSREQUEST._options = None
  _STREAMTAPSREQUEST._serialized_options = b'\232\305\210\036-\n+envoy.service.tap.v2alpha.StreamTapsRequest'
  _STREAMTAPSRESPONSE._options = None
  _STREAMTAPSRESPONSE._serialized_options = b'\232\305\210\036.\n,envoy.service.tap.v2alpha.StreamTapsResponse'
  _globals['_STREAMTAPSREQUEST']._serialized_start=214
  _globals['_STREAMTAPSREQUEST']._serialized_end=569
  _globals['_STREAMTAPSREQUEST_IDENTIFIER']._serialized_start=374
  _globals['_STREAMTAPSREQUEST_IDENTIFIER']._serialized_end=517
  _globals['_STREAMTAPSRESPONSE']._serialized_start=571
  _globals['_STREAMTAPSRESPONSE']._serialized_end=644
  _globals['_TAPSINKSERVICE']._serialized_start=646
  _globals['_TAPSINKSERVICE']._serialized_end=763
