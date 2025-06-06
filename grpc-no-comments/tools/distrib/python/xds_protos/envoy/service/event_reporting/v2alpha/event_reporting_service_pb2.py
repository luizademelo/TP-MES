
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nCenvoy/service/event_reporting/v2alpha/event_reporting_service.proto\x12%envoy.service.event_reporting.v2alpha\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a\x19google/protobuf/any.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xdf\x01\n\x13StreamEventsRequest\x12Y\n\nidentifier\x18\x01 \x01(\x0b\x32\x45.envoy.service.event_reporting.v2alpha.StreamEventsRequest.Identifier\x12.\n\x06\x65vents\x18\x02 \x03(\x0b\x32\x14.google.protobuf.AnyB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a=\n\nIdentifier\x12/\n\x04node\x18\x01 \x01(\x0b\x32\x17.envoy.api.v2.core.NodeB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\"\x16\n\x14StreamEventsResponse2\xa7\x01\n\x15\x45ventReportingService\x12\x8d\x01\n\x0cStreamEvents\x12:.envoy.service.event_reporting.v2alpha.StreamEventsRequest\x1a;.envoy.service.event_reporting.v2alpha.StreamEventsResponse\"\x00(\x01\x30\x01\x42\xd1\x01\n3io.envoyproxy.envoy.service.event_reporting.v2alphaB\x1a\x45ventReportingServiceProtoP\x01ZLgithub.com/envoyproxy/go-control-plane/envoy/service/event_reporting/v2alpha\xf2\x98\xfe\x8f\x05\"\x12 envoy.service.event_reporting.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.event_reporting.v2alpha.event_reporting_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n3io.envoyproxy.envoy.service.event_reporting.v2alphaB\032EventReportingServiceProtoP\001ZLgithub.com/envoyproxy/go-control-plane/envoy/service/event_reporting/v2alpha\362\230\376\217\005\"\022 envoy.service.event_reporting.v3\272\200\310\321\006\002\020\001'
  _STREAMEVENTSREQUEST_IDENTIFIER.fields_by_name['node']._options = None
  _STREAMEVENTSREQUEST_IDENTIFIER.fields_by_name['node']._serialized_options = b'\372B\005\212\001\002\020\001'
  _STREAMEVENTSREQUEST.fields_by_name['events']._options = None
  _STREAMEVENTSREQUEST.fields_by_name['events']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_STREAMEVENTSREQUEST']._serialized_start=256
  _globals['_STREAMEVENTSREQUEST']._serialized_end=479
  _globals['_STREAMEVENTSREQUEST_IDENTIFIER']._serialized_start=418
  _globals['_STREAMEVENTSREQUEST_IDENTIFIER']._serialized_end=479
  _globals['_STREAMEVENTSRESPONSE']._serialized_start=481
  _globals['_STREAMEVENTSRESPONSE']._serialized_end=503
  _globals['_EVENTREPORTINGSERVICE']._serialized_start=506
  _globals['_EVENTREPORTINGSERVICE']._serialized_end=673
