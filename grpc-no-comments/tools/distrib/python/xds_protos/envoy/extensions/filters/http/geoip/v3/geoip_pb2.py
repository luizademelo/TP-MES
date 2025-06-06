
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2envoy/extensions/filters/http/geoip/v3/geoip.proto\x12&envoy.extensions.filters.http.geoip.v3\x1a$envoy/config/core/v3/extension.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc7\x01\n\x05Geoip\x12K\n\nxff_config\x18\x01 \x01(\x0b\x32\x37.envoy.extensions.filters.http.geoip.v3.Geoip.XffConfig\x12\x46\n\x08provider\x18\x03 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x1a)\n\tXffConfig\x12\x1c\n\x14xff_num_trusted_hops\x18\x01 \x01(\rB\xab\x01\n4io.envoyproxy.envoy.extensions.filters.http.geoip.v3B\nGeoipProtoP\x01ZUgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/geoip/v3;geoipv3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.geoip.v3.geoip_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n4io.envoyproxy.envoy.extensions.filters.http.geoip.v3B\nGeoipProtoP\001ZUgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/geoip/v3;geoipv3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _GEOIP.fields_by_name['provider']._options = None
  _GEOIP.fields_by_name['provider']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_GEOIP']._serialized_start=222
  _globals['_GEOIP']._serialized_end=421
  _globals['_GEOIP_XFFCONFIG']._serialized_start=380
  _globals['_GEOIP_XFFCONFIG']._serialized_end=421
