
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x18google/api/routing.proto\x12\ngoogle.api\x1a google/protobuf/descriptor.proto\"G\n\x0bRoutingRule\x12\x38\n\x12routing_parameters\x18\x02 \x03(\x0b\x32\x1c.google.api.RoutingParameter\"8\n\x10RoutingParameter\x12\r\n\x05\x66ield\x18\x01 \x01(\t\x12\x15\n\rpath_template\x18\x02 \x01(\t:K\n\x07routing\x12\x1e.google.protobuf.MethodOptions\x18\xb1\xca\xbc\" \x01(\x0b\x32\x17.google.api.RoutingRuleBj\n\x0e\x63om.google.apiB\x0cRoutingProtoP\x01ZAgoogle.golang.org/genproto/googleapis/api/annotations;annotations\xa2\x02\x04GAPIb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.routing_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\016com.google.apiB\014RoutingProtoP\001ZAgoogle.golang.org/genproto/googleapis/api/annotations;annotations\242\002\004GAPI'
  _globals['_ROUTINGRULE']._serialized_start=74
  _globals['_ROUTINGRULE']._serialized_end=145
  _globals['_ROUTINGPARAMETER']._serialized_start=147
  _globals['_ROUTINGPARAMETER']._serialized_end=203
