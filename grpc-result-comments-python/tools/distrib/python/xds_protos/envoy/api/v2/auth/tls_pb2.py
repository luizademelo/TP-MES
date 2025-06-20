Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependent Protocol Buffer definitions
from envoy.api.v2.auth import common_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_common__pb2
from envoy.api.v2.auth import secret_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_secret__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer message descriptors
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1b\x65nvoy/api/v2/auth/tls.proto\x12\x11\x65nvoy.api.v2.auth\x1a\x1e\x65nvoy/api/v2/auth/common.proto\x1a\x1e\x65nvoy/api/v2/auth/secret.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc1\x01\n\x12UpstreamTlsContext\x12?\n\x12\x63ommon_tls_context\x18\x01 \x01(\x0b\x32#.envoy.api.v2.auth.CommonTlsContext\x12\x15\n\x03sni\x18\x02 \x01(\tB\x08\xfa\x42\x05r\x03(\xff\x01\x12\x1b\n\x13\x61llow_renegotiation\x18\x03 \x01(\x08\x12\x36\n\x10max_session_keys\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\"\xf7\x03\n\x14\x44ownstreamTlsContext\x12?\n\x12\x63ommon_tls_context\x18\x01 \x01(\x0b\x32#.envoy.api.v2.auth.CommonTlsContext\x12>\n\x1arequire_client_certificate\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12/\n\x0brequire_sni\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x46\n\x13session_ticket_keys\x18\x04 \x01(\x0b\x32\'.envoy.api.v2.auth.TlsSessionTicketKeysH\x00\x12S\n%session_ticket_keys_sds_secret_config\x18\x05 \x01(\x0b\x32\".envoy.api.v2.auth.SdsSecretConfigH\x00\x12.\n$disable_stateless_session_resumption\x18\x07 \x01(\x08H\x00\x12\x44\n\x0fsession_timeout\x18\x06 \x01(\x0b\x32\x19.google.protobuf.DurationB\x10\xfa\x42\r\xaa\x01\n\x1a\x06\x08\x80\x80\x80\x80\x10\x32\x00\x42\x1a\n\x18session_ticket_keys_type\"\x90\x06\n\x10\x43ommonTlsContext\x12\x34\n\ntls_params\x18\x01 \x01(\x0b\x32 .envoy.api.v2.auth.TlsParameters\x12;\n\x10tls_certificates\x18\x02 \x03(\x0b\x32!.envoy.api.v2.auth.TlsCertificate\x12X\n\"tls_certificate_sds_secret_configs\x18\x06 \x03(\x0b\x32\".envoy.api.v2.auth.SdsSecretConfigB\x08\xfa\x42\x05\x92\x01\x02\x10\x01\x12M\n\x12validation_context\x18\x03 \x01(\x0b\x32/.envoy.api.v2.auth.CertificateValidationContextH\x00\x12R\n$validation_context_sds_secret_config\x18\x07 \x01(\x0b\x32\".envoy.api.v2.auth.SdsSecretConfigH\x00\x12o\n\x1b\x63ombined_validation_context\x18\x08 \x01(\x0b\x32H.envoy.api.v2.auth.CommonTlsContext.CombinedCertificateValidationContextH\x00\x12\x16\n\x0e\x61lpn_protocols\x18\x04 \x03(\t\x1a\xe1\x01\n$CombinedCertificateValidationContext\x12]\n\x1a\x64\x65\x66\x61ult_validation_context\x18\x01 \x01(\x0b\x32/.envoy.api.v2.auth.CertificateValidationContextB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12Z\n$validation_context_sds_secret_config\x18\x02 \x01(\x0b\x32\".envoy.api.v2.auth.SdsSecretConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\x19\n\x17validation_context_typeJ\x04\x08\x05\x10\x06\x42\xa0\x01\n\x1fio.envoyproxy.envoy.api.v2.authB\x08TlsProtoP\x01Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/auth\xf2\x98\xfe\x8f\x05+\x12)envoy.extensions.transport_sockets.tls.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

# Build message and enum descriptors
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.auth.tls_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set package and file options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n\037io.envoyproxy.envoy.api.v2.authB\010TlsProtoP\001Z8github.com/envoyproxy/go-control-plane/envoy/api/v2/auth\362\230\376\217\005+\022)envoy.extensions.transport_sockets.tls.v3\272\200\310\321\006\002\020\001'
    
    # Set field-specific options
    _UPSTREAMTLSCONTEXT.fields_by_name['sni']._options = None
    _UPSTREAMTLSCONTEXT.fields_by_name['sni']._serialized_options = b'\372B\005r\003(\377\001'
    _DOWNSTREAMTLSCONTEXT.fields_by_name['session_timeout']._options = None
    _DOWNSTREAMTLSCONTEXT.fields_by_name['session_timeout']._serialized_options = b'\372B\r\252\001\n\032\006\010\200\200\200\200\0202\000'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['default_validation_context']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['default_validation_context']._serialized_options = b'\372B\005\212\001\002\020\001'
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_sds_secret_config']._options = None
    _COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT.fields_by_name['validation_context_sds_secret_config']._serialized_options = b'\372B\005\212\001\002\020\001'
    _COMMONTLSCONTEXT.fields_by_name['tls_certificate_sds_secret_configs']._options = None
    _COMMONTLSCONTEXT.fields_by_name['tls_certificate_sds_secret_configs']._serialized_options = b'\372B\005\222\001\002\020\001'
    
    # Define serialized start and end positions for each message
    _globals['_UPSTREAMTLSCONTEXT']._serialized_start=267
    _globals['_UPSTREAMTLSCONTEXT']._serialized_end=460
    _globals['_DOWNSTREAMTLSCONTEXT']._serialized_start=463
    _globals['_DOWNSTREAMTLSCONTEXT']._serialized_end=966
    _globals['_COMMONTLSCONTEXT']._serialized_start=969
    _globals['_COMMONTLSCONTEXT']._serialized_end=1753
    _globals['_COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT']._serialized_start=1495
    _globals['_COMMONTLSCONTEXT_COMBINEDCERTIFICATEVALIDATIONCONTEXT']._serialized_end=1720
```

Key aspects covered in the comments:
1. Import statements and their purposes
2. Protocol Buffer symbol database initialization
3. Message descriptor definitions
4. Builder operations for generating message and enum descriptors
5. Configuration of descriptor options when not using C++ descriptors
6. Field-specific options and validations
7. Serialized position markers for message definitions

The comments provide clear explanations of each section's purpose and functionality, making it easier for future developers to understand and maintain the code.