
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nKenvoy/extensions/transport_sockets/tls/v3/tls_spiffe_validator_config.proto\x12)envoy.extensions.transport_sockets.tls.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa5\x02\n\x19SPIFFECertValidatorConfig\x12q\n\rtrust_domains\x18\x01 \x03(\x0b\x32P.envoy.extensions.transport_sockets.tls.v3.SPIFFECertValidatorConfig.TrustDomainB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x37\n\rtrust_bundles\x18\x02 \x01(\x0b\x32 .envoy.config.core.v3.DataSource\x1a\\\n\x0bTrustDomain\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x36\n\x0ctrust_bundle\x18\x02 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceB\xba\x01\n7io.envoyproxy.envoy.extensions.transport_sockets.tls.v3B\x1dTlsSpiffeValidatorConfigProtoP\x01ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tls/v3;tlsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.tls.v3.tls_spiffe_validator_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.transport_sockets.tls.v3B\035TlsSpiffeValidatorConfigProtoP\001ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tls/v3;tlsv3\272\200\310\321\006\002\020\002'
  _SPIFFECERTVALIDATORCONFIG_TRUSTDOMAIN.fields_by_name['name']._options = None
  _SPIFFECERTVALIDATORCONFIG_TRUSTDOMAIN.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _SPIFFECERTVALIDATORCONFIG.fields_by_name['trust_domains']._options = None
  _SPIFFECERTVALIDATORCONFIG.fields_by_name['trust_domains']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_SPIFFECERTVALIDATORCONFIG']._serialized_start=212
  _globals['_SPIFFECERTVALIDATORCONFIG']._serialized_end=505
  _globals['_SPIFFECERTVALIDATORCONFIG_TRUSTDOMAIN']._serialized_start=413
  _globals['_SPIFFECERTVALIDATORCONFIG_TRUSTDOMAIN']._serialized_end=505
