
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import http_status_pb2 as envoy_dot_type_dot_v3_dot_http__status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nPenvoy/extensions/http/original_ip_detection/custom_header/v3/custom_header.proto\x12<envoy.extensions.http.original_ip_detection.custom_header.v3\x1a\x1f\x65nvoy/type/v3/http_status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa2\x01\n\x12\x43ustomHeaderConfig\x12\"\n\x0bheader_name\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x01\x12\x31\n)allow_extension_to_set_address_as_trusted\x18\x02 \x01(\x08\x12\x35\n\x12reject_with_status\x18\x03 \x01(\x0b\x32\x19.envoy.type.v3.HttpStatusB\xde\x01\nJio.envoyproxy.envoy.extensions.http.original_ip_detection.custom_header.v3B\x11\x43ustomHeaderProtoP\x01Zsgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/original_ip_detection/custom_header/v3;custom_headerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.original_ip_detection.custom_header.v3.custom_header_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nJio.envoyproxy.envoy.extensions.http.original_ip_detection.custom_header.v3B\021CustomHeaderProtoP\001Zsgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/original_ip_detection/custom_header/v3;custom_headerv3\272\200\310\321\006\002\020\002'
  _CUSTOMHEADERCONFIG.fields_by_name['header_name']._options = None
  _CUSTOMHEADERCONFIG.fields_by_name['header_name']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\001'
  _globals['_CUSTOMHEADERCONFIG']._serialized_start=236
  _globals['_CUSTOMHEADERCONFIG']._serialized_end=398
