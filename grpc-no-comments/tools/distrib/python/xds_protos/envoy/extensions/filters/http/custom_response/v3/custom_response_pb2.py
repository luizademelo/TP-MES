
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.type.matcher.v3 import matcher_pb2 as xds_dot_type_dot_matcher_dot_v3_dot_matcher__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nFenvoy/extensions/filters/http/custom_response/v3/custom_response.proto\x12\x30\x65nvoy.extensions.filters.http.custom_response.v3\x1a\x1fxds/annotations/v3/status.proto\x1a!xds/type/matcher/v3/matcher.proto\x1a\x1dudpa/annotations/status.proto\"O\n\x0e\x43ustomResponse\x12=\n\x17\x63ustom_response_matcher\x18\x01 \x01(\x0b\x32\x1c.xds.type.matcher.v3.MatcherB\xd2\x01\n>io.envoyproxy.envoy.extensions.filters.http.custom_response.v3B\x13\x43ustomResponseProtoP\x01Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/custom_response/v3;custom_responsev3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.custom_response.v3.custom_response_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.filters.http.custom_response.v3B\023CustomResponseProtoP\001Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/custom_response/v3;custom_responsev3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _globals['_CUSTOMRESPONSE']._serialized_start=223
  _globals['_CUSTOMRESPONSE']._serialized_end=302
