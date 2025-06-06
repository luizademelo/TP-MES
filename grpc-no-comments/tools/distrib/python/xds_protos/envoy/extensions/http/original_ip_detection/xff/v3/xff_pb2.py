
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n<envoy/extensions/http/original_ip_detection/xff/v3/xff.proto\x12\x32\x65nvoy.extensions.http.original_ip_detection.xff.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\"\xbe\x01\n\tXffConfig\x12\x1c\n\x14xff_num_trusted_hops\x18\x01 \x01(\r\x12^\n\x11xff_trusted_cidrs\x18\x02 \x01(\x0b\x32\x43.envoy.extensions.http.original_ip_detection.xff.v3.XffTrustedCidrs\x12\x33\n\x0fskip_xff_append\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\"A\n\x0fXffTrustedCidrs\x12.\n\x05\x63idrs\x18\x01 \x03(\x0b\x32\x1f.envoy.config.core.v3.CidrRangeB\xb7\x01\n@io.envoyproxy.envoy.extensions.http.original_ip_detection.xff.v3B\x08XffProtoP\x01Z_github.com/envoyproxy/go-control-plane/envoy/extensions/http/original_ip_detection/xff/v3;xffv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.original_ip_detection.xff.v3.xff_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.http.original_ip_detection.xff.v3B\010XffProtoP\001Z_github.com/envoyproxy/go-control-plane/envoy/extensions/http/original_ip_detection/xff/v3;xffv3\272\200\310\321\006\002\020\002'
  _globals['_XFFCONFIG']._serialized_start=216
  _globals['_XFFCONFIG']._serialized_end=406
  _globals['_XFFTRUSTEDCIDRS']._serialized_start=408
  _globals['_XFFTRUSTEDCIDRS']._serialized_end=473
