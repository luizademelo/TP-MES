
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.geoip_providers.common.v3 import common_pb2 as envoy_dot_extensions_dot_geoip__providers_dot_common_dot_v3_dot_common__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9envoy/extensions/geoip_providers/maxmind/v3/maxmind.proto\x12+envoy.extensions.geoip_providers.maxmind.v3\x1a\x37\x65nvoy/extensions/geoip_providers/common/v3/common.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x83\x02\n\rMaxMindConfig\x12*\n\x0c\x63ity_db_path\x18\x01 \x01(\tB\x14\xfa\x42\x11r\x0f\x32\r^$|^.*\\.mmdb$\x12)\n\x0bisp_db_path\x18\x02 \x01(\tB\x14\xfa\x42\x11r\x0f\x32\r^$|^.*\\.mmdb$\x12*\n\x0c\x61non_db_path\x18\x03 \x01(\tB\x14\xfa\x42\x11r\x0f\x32\r^$|^.*\\.mmdb$\x12o\n\x16\x63ommon_provider_config\x18\x04 \x01(\x0b\x32\x45.envoy.extensions.geoip_providers.common.v3.CommonGeoipProviderConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\xb9\x01\n9io.envoyproxy.envoy.extensions.geoip_providers.maxmind.v3B\x0cMaxmindProtoP\x01Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/geoip_providers/maxmind/v3;maxmindv3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.geoip_providers.maxmind.v3.maxmind_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.extensions.geoip_providers.maxmind.v3B\014MaxmindProtoP\001Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/geoip_providers/maxmind/v3;maxmindv3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _MAXMINDCONFIG.fields_by_name['city_db_path']._options = None
  _MAXMINDCONFIG.fields_by_name['city_db_path']._serialized_options = b'\372B\021r\0172\r^$|^.*\\.mmdb$'
  _MAXMINDCONFIG.fields_by_name['isp_db_path']._options = None
  _MAXMINDCONFIG.fields_by_name['isp_db_path']._serialized_options = b'\372B\021r\0172\r^$|^.*\\.mmdb$'
  _MAXMINDCONFIG.fields_by_name['anon_db_path']._options = None
  _MAXMINDCONFIG.fields_by_name['anon_db_path']._serialized_options = b'\372B\021r\0172\r^$|^.*\\.mmdb$'
  _MAXMINDCONFIG.fields_by_name['common_provider_config']._options = None
  _MAXMINDCONFIG.fields_by_name['common_provider_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_MAXMINDCONFIG']._serialized_start=253
  _globals['_MAXMINDCONFIG']._serialized_end=512
