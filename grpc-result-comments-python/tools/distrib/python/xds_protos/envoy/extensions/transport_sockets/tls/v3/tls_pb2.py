Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependent Protocol Buffer definitions
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from envoy.extensions.transport_sockets.tls.v3 import common_pb2 as envoy_dot_extensions_dot_transport__sockets_dot_tls_dot_v3_dot_common__pb2
from envoy.extensions.transport_sockets.tls.v3 import secret_pb2 as envoy_dot_extensions_dot_transport__sockets_dot_tls_dot_v3_dot_secret__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer descriptor with serialized file data
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3envoy/extensions/transport_sockets/tls/v3/tls.proto\x12)envoy.extensions.transport_sockets.tls.v3\x1a\"envoy/config/core/v3/address.proto\x1a$envoy/config/core/v3/extension.proto\x1a\x36\x65nvoy/extensions/transport_sockets/tls/v3/common.proto\x1a\x36\x65nvoy/extensions/transport_sockets/tls/v3/secret.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xf9\x02\n\x12UpstreamTlsContext\x12W\n\x12\x63ommon_tls_context\x18\x01 \x01(\x0b\x32;.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext\x12\x15\n\x03sni\x18\x02 \x01(\tB\x08\xfa\x42\x05r\x03(\xff\x01\x12\x15\n\rauto_host_sni\x18\x06 \x01(\x08\x12\x1f\n\x17\x61uto_sni_san_validation\x18\x07 \x01(\x08\x12\x1b\n\x13\x61llow_renegotiation\x18\x03 \x01(\x08\x12\x36\n\x10max_session_keys\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x39\n\x15\x65nforce_rsa_key_usage\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.BoolValue:+\x9a\xc5\x88\x1e&\n$envoy.api.v2.auth.UpstreamTlsContext\"\xc7\x07\n\x14\x44ownstreamTlsContext\x12W\n\x12\x63ommon_tls_context\x18\x01 \x01(\x0b\x32;.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext\x12>\n\x1arequire_client_certificate\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12/\n\x0brequire_sni\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12^\n\x13session_ticket_keys\x18\x04 \x01(\x0b\x32?.envoy.extensions.transport_sockets.tls.v3.TlsSessionTicketKeysH\x00\x12k\n%session_ticket_keys_sds_secret_config\x18\x05 \x01(\x0b\x32:.envoy.extensions.transport_sockets.tls.v3.SdsSecretConfigH\x00\x12.\n$disable_stateless_session_resumption\x18\x07 \x01(\x08H\x00\x12+\n#disable_stateful_session_resumption\x18\n \x01(\x08\x12\x44\n\x0fsession_timeout\x18\x06 \x01(\x0b\x32\x19.google.protobuf.DurationB\x10\xfa\x42\r\xaa\x01\n\x1a\x06\x08\x80\x80\x80\x80\x10\x32\x00\x12v\n\x12ocsp_staple_policy\x18\x08 \x01(\x0e\x32P.envoy.extensions.transport_sockets.tls.v3.DownstreamTlsContext.OcspStaplePolicyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x43\n\x1f\x66ull_scan_certs_on_sni_mismatch\x18\t \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x1d\n\x15prefer_client_ciphers\x18\x0b \x01(\x08\"N\n\x10OcspStaplePolicy\x12\x14\n\x10LENIENT_STAPLING\x10\x00\x12\x13\n\x0fSTRICT_STAPLING\x10\x01\x12\x0f\n\x0bMUST_STAPLE\x10\x02:-\x9a\xc5\x88\x1e(\n&envoy.api.v2.auth.DownstreamTlsContextB\x1a\n\x18session_ticket_keys_type\"\x9f\x01\n\tTlsKeyLog\x12\x15\n\x04path\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12<\n\x13local_address_range\x18\x02 \x03(\x0b\x32\x1f.envoy.config.core.v3.CidrRange\x12=\n\x14remote_address_range\x18\x03 \x03(\x0b\x32\x1f.envoy.config.core.v3.CidrRange\"\x80\x14\n\x10\x43ommonTlsContext\x12L\n\ntls_params\x18\x01 \x01(\x0b\x32\x38.envoy.extensions.transport_sockets.tls.v3.TlsParameters\x12S\n\x10tls_certificates\x18\x02 \x03(\x0b\x32\x39.envoy.extensions.transport_sockets.tls.v3.TlsCertificate\x12\x66\n\"tls_certificate_sds_secret_configs\x18\x06 \x03(\x0b\x32:.envoy.extensions.transport_sockets.tls.v3.SdsSecretConfig\x12w\n!tls_certificate_provider_instance\x18\x0e \x01(\x0b\x32L.envoy.extensions.transport_sockets.tls.v3.CertificateProviderPluginInstance\x12S\n\x1f\x63ustom_tls_certificate_selector\x18\x10 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x8a\x01\n$tls_certificate_certificate_provider\x18\t \x01(\x0b\x32O.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x9b\x01\n-tls_certificate_certificate_provider_instance\x18\x0b \x01(\x0b\x32W.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderInstanceB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x65\n\x12validation_context\x18\x03 \x01(\x0b\x32G.envoy.extensions.transport_sockets.tls.v3.CertificateValidationContextH\x00\x12j\n$validation_context_sds_secret_config\x18\x07 \x01(\x0b\x32:.envoy.extensions.transport_sockets.tls.v3.SdsSecretConfigH\x00\x12\x87\x01\n\x1b\x63ombined_validation_context\x18\x08 \x01(\x0b\x32`.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CombinedCertificateValidationContextH\x00\x12\x8f\x01\n\'validation_context_certificate_provider\x18\n \x01(\x0b\x32O.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\xa0\x01\n0validation_context_certificate_provider_instance\x18\x0c \x01(\x0b\x32W.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderInstanceB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\x16\n\x0e\x61lpn_protocols\x18\x04 \x03(\t\x12\x45\n\x11\x63ustom_handshaker\x18\r \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x45\n\x07key_log\x18\x0f \x01(\x0b\x32\x34.envoy.extensions.transport_sockets.tls.v3.TlsKeyLog\x1a\x7f\n\x13\x43\x65rtificateProvider\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x42\n\x0ctyped_config\x18\x02 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfigH\x00\x42\r\n\x06\x63onfig\x12\x03\xf8\x42\x01\x1aN\n\x1b\x43\x65rtificateProviderInstance\x12\x15\n\rinstance_name\x18\x01 \x01(\t\x12\x18\n\x10\x63\x65rtificate_name\x18\x02 \x01(\t\x1a\x92\x05\n$CombinedCertificateValidationContext\x12u\n\x1a\x64\x65\x66\x61ult_validation_context\x18\x01 \x01(\x0b\x32G.envoy.extensions.transport_sockets.tls.v3.CertificateValidationContextB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12r\n$validation_context_sds_secret_config\x18\x02 \x01(\x0b\x32:.envoy.extensions.transport_sockets.tls.v3.SdsSecretConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x8d\x01\n\'validation_context_certificate_provider\x18\x03 \x01(\x0b\x32O.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x9e\x01\n0validation_context_certificate_provider_instance\x18\x04 \x01(\x0b\x32W.envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderInstanceB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0:N\x9a\xc5\x88\x1eI\nGenvoy.api.v2.auth.CommonTlsContext.CombinedCertificateValidationContext:)\x9a\xc5\x88\x1e$\n\"envoy.api.v2.auth.CommonTlsContextB\x19\n\x17validation_context_typeJ\x04\x08\x05\x10\x06\x42\xa5\x01\n7io.envoyproxy.envoy.extensions.transport_sockets.tls.v3B\x08TlsProtoP\x01ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tls/v3;tlsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.tls.v3.tls_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Main descriptor options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.transport_sockets.tls.v3B\010TlsProtoP\001ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tls/v3;tlsv3\272\200\310\321\006\002\020\002'
    
    # UpstreamTlsContext options
    _UPSTREAMTLSCONTEXT.fields_by_name['sni']._options = None
    _UPSTREAMTLSCONTEXT.fields_by_name['sni']._serialized_options = b'\372B\005r\003(\377\001'
    _UPSTREAMTLSCONTEXT._options = None
    _UPSTREAMTLSCONTEXT._serialized_options = b'\232\305\210\036&\n$envoy.api.v2.auth.UpstreamTlsContext'
    
    # DownstreamTlsContext options
    _DOWNSTREAMTLSCONTEXT.fields_by_name['session_timeout']._options = None
    _DOWNSTREAMTLSCONTEXT.fields_by_name['session_timeout']._serialized_options = b'\372B\r\252\001\n\032\006\010\200\200\200\200\0202\000'
    _DOWNSTREAMTLSCONTEXT.fields_by_name['ocsp_staple_policy']._options = None
    _DOWNSTREAMTLSCONTEXT.fields_by_name['ocsp_staple_policy']._serialized_options = b'\372B\005\202\001\002\020\001'
    _DOWNSTREAMTLSCONTEXT._options = None
    _DOWNSTREAMTLSCONTEXT._serialized_options = b'\232\305\210\036(\n&envoy.api.v2.auth.DownstreamTlsContext'
    
    # TlsKeyLog options
    _TLSKEYLOG.fields_by_name['path']._options = None
    _TLSKEYLOG.fields_by_name['path']._serialized_options = b'\372B\004r\002\020\001'
    
    # CommonTlsContext options
    _COMMONTLSCONTEXT_CERTIFICATEPROVIDER.oneofs_by_name['config']._options = None
    _COMMONTLSCONTEXT_CERTIFICATEPROVIDER.oneofs_by_name['config']._serialized_options = b'\370B\001'
    _COMMONTLSCONTEXT_CERTIFICATEPROVIDER.fields_by_name['name']._options = None
    _COMMONTLSCONTEXT_CERTIFICATEPROVIDER.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['default_validation_context']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['default_validation_context']._serialized_options = b'\372B\005\212\001\002\020\001'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_sds_secret_config']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_sds_secret_config']._serialized_options = b'\372B\005\212\001\002\020\001'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_certificate_provider']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_certificate_provider']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_certificate_provider_instance']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_certificate_provider_instance']._serialized_options = b'\030\001\222\