
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.filters.common.set_filter_state.v3 import value_pb2 as envoy_dot_extensions_dot_filters_dot_common_dot_set__filter__state_dot_v3_dot_value__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nHenvoy/extensions/filters/http/set_filter_state/v3/set_filter_state.proto\x12\x31\x65nvoy.extensions.filters.http.set_filter_state.v3\x1a?envoy/extensions/filters/common/set_filter_state/v3/value.proto\x1a\x1dudpa/annotations/status.proto\"k\n\x06\x43onfig\x12\x61\n\x12on_request_headers\x18\x01 \x03(\x0b\x32\x45.envoy.extensions.filters.common.set_filter_state.v3.FilterStateValueB\xcd\x01\n?io.envoyproxy.envoy.extensions.filters.http.set_filter_state.v3B\x13SetFilterStateProtoP\x01Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/set_filter_state/v3;set_filter_statev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.set_filter_state.v3.set_filter_state_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.filters.http.set_filter_state.v3B\023SetFilterStateProtoP\001Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/set_filter_state/v3;set_filter_statev3\272\200\310\321\006\002\020\002'
  _globals['_CONFIG']._serialized_start=223
  _globals['_CONFIG']._serialized_end=330
