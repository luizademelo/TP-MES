
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nsenvoy/extensions/load_balancing_policies/client_side_weighted_round_robin/v3/client_side_weighted_round_robin.proto\x12Lenvoy.extensions.load_balancing_policies.client_side_weighted_round_robin.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xb9\x03\n\x1c\x43lientSideWeightedRoundRobin\x12:\n\x16\x65nable_oob_load_report\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x37\n\x14oob_reporting_period\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x32\n\x0f\x62lackout_period\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12;\n\x18weight_expiration_period\x18\x04 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x37\n\x14weight_update_period\x18\x05 \x01(\x0b\x32\x19.google.protobuf.Duration\x12J\n\x19\x65rror_utilization_penalty\x18\x06 \x01(\x0b\x32\x1b.google.protobuf.FloatValueB\n\xfa\x42\x07\n\x05-\x00\x00\x00\x00\x12.\n&metric_names_for_computing_utilization\x18\x07 \x03(\tB\xa2\x02\nZio.envoyproxy.envoy.extensions.load_balancing_policies.client_side_weighted_round_robin.v3B!ClientSideWeightedRoundRobinProtoP\x01Z\x96\x01github.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/client_side_weighted_round_robin/v3;client_side_weighted_round_robinv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.client_side_weighted_round_robin.v3.client_side_weighted_round_robin_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nZio.envoyproxy.envoy.extensions.load_balancing_policies.client_side_weighted_round_robin.v3B!ClientSideWeightedRoundRobinProtoP\001Z\226\001github.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/client_side_weighted_round_robin/v3;client_side_weighted_round_robinv3\272\200\310\321\006\002\020\002'
  _CLIENTSIDEWEIGHTEDROUNDROBIN.fields_by_name['error_utilization_penalty']._options = None
  _CLIENTSIDEWEIGHTEDROUNDROBIN.fields_by_name['error_utilization_penalty']._serialized_options = b'\372B\007\n\005-\000\000\000\000'
  _globals['_CLIENTSIDEWEIGHTEDROUNDROBIN']._serialized_start=318
  _globals['_CLIENTSIDEWEIGHTEDROUNDROBIN']._serialized_end=759
