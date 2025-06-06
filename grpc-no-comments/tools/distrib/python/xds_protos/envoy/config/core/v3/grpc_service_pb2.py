
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import sensitive_pb2 as udpa_dot_annotations_dot_sensitive__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/config/core/v3/grpc_service.proto\x12\x14\x65nvoy.config.core.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x19google/protobuf/any.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a udpa/annotations/sensitive.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xbc\x1d\n\x0bGrpcService\x12\x41\n\nenvoy_grpc\x18\x01 \x01(\x0b\x32+.envoy.config.core.v3.GrpcService.EnvoyGrpcH\x00\x12\x43\n\x0bgoogle_grpc\x18\x02 \x01(\x0b\x32,.envoy.config.core.v3.GrpcService.GoogleGrpcH\x00\x12*\n\x07timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12;\n\x10initial_metadata\x18\x05 \x03(\x0b\x32!.envoy.config.core.v3.HeaderValue\x12\x37\n\x0cretry_policy\x18\x06 \x01(\x0b\x32!.envoy.config.core.v3.RetryPolicy\x1a\x97\x02\n\tEnvoyGrpc\x12\x1d\n\x0c\x63luster_name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12$\n\tauthority\x18\x02 \x01(\tB\x11\xfa\x42\x0er\x0c\x10\x00(\x80\x80\x01\xc0\x01\x02\xc8\x01\x00\x12\x37\n\x0cretry_policy\x18\x03 \x01(\x0b\x32!.envoy.config.core.v3.RetryPolicy\x12@\n\x1amax_receive_message_length\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x1a\n\x12skip_envoy_headers\x18\x05 \x01(\x08:.\x9a\xc5\x88\x1e)\n\'envoy.api.v2.core.GrpcService.EnvoyGrpc\x1a\xa3\x18\n\nGoogleGrpc\x12\x1b\n\ntarget_uri\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\\\n\x13\x63hannel_credentials\x18\x02 \x01(\x0b\x32?.envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelCredentials\x12V\n\x10\x63\x61ll_credentials\x18\x03 \x03(\x0b\x32<.envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials\x12\x1c\n\x0bstat_prefix\x18\x04 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12 \n\x18\x63redentials_factory_name\x18\x05 \x01(\t\x12\'\n\x06\x63onfig\x18\x06 \x01(\x0b\x32\x17.google.protobuf.Struct\x12\x43\n\x1dper_stream_buffer_limit_bytes\x18\x07 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12N\n\x0c\x63hannel_args\x18\x08 \x01(\x0b\x32\x38.envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs\x1a\xfb\x01\n\x0eSslCredentials\x12\x34\n\nroot_certs\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSource\x12=\n\x0bprivate_key\x18\x02 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceB\x06\xb8\xb7\x8b\xa4\x02\x01\x12\x34\n\ncert_chain\x18\x03 \x01(\x0b\x32 .envoy.config.core.v3.DataSource:>\x9a\xc5\x88\x1e\x39\n7envoy.api.v2.core.GrpcService.GoogleGrpc.SslCredentials\x1a`\n\x16GoogleLocalCredentials:F\x9a\xc5\x88\x1e\x41\n?envoy.api.v2.core.GrpcService.GoogleGrpc.GoogleLocalCredentials\x1a\xe1\x02\n\x12\x43hannelCredentials\x12V\n\x0fssl_credentials\x18\x01 \x01(\x0b\x32;.envoy.config.core.v3.GrpcService.GoogleGrpc.SslCredentialsH\x00\x12\x30\n\x0egoogle_default\x18\x02 \x01(\x0b\x32\x16.google.protobuf.EmptyH\x00\x12`\n\x11local_credentials\x18\x03 \x01(\x0b\x32\x43.envoy.config.core.v3.GrpcService.GoogleGrpc.GoogleLocalCredentialsH\x00:B\x9a\xc5\x88\x1e=\n;envoy.api.v2.core.GrpcService.GoogleGrpc.ChannelCredentialsB\x1b\n\x14\x63redential_specifier\x12\x03\xf8\x42\x01\x1a\xb1\x0c\n\x0f\x43\x61llCredentials\x12\x16\n\x0c\x61\x63\x63\x65ss_token\x18\x01 \x01(\tH\x00\x12\x37\n\x15google_compute_engine\x18\x02 \x01(\x0b\x32\x16.google.protobuf.EmptyH\x00\x12\x1e\n\x14google_refresh_token\x18\x03 \x01(\tH\x00\x12\x85\x01\n\x1aservice_account_jwt_access\x18\x04 \x01(\x0b\x32_.envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.ServiceAccountJWTAccessCredentialsH\x00\x12g\n\ngoogle_iam\x18\x05 \x01(\x0b\x32Q.envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.GoogleIAMCredentialsH\x00\x12q\n\x0b\x66rom_plugin\x18\x06 \x01(\x0b\x32Z.envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.MetadataCredentialsFromPluginH\x00\x12^\n\x0bsts_service\x18\x07 \x01(\x0b\x32G.envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.StsServiceH\x00\x1a\xba\x01\n\"ServiceAccountJWTAccessCredentials\x12\x10\n\x08json_key\x18\x01 \x01(\t\x12\x1e\n\x16token_lifetime_seconds\x18\x02 \x01(\x04:b\x9a\xc5\x88\x1e]\n[envoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.ServiceAccountJWTAccessCredentials\x1a\xa5\x01\n\x14GoogleIAMCredentials\x12\x1b\n\x13\x61uthorization_token\x18\x01 \x01(\t\x12\x1a\n\x12\x61uthority_selector\x18\x02 \x01(\t:T\x9a\xc5\x88\x1eO\nMenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.GoogleIAMCredentials\x1a\xd7\x01\n\x1dMetadataCredentialsFromPlugin\x12\x0c\n\x04name\x18\x01 \x01(\t\x12,\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00:]\x9a\xc5\x88\x1eX\nVenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.MetadataCredentialsFromPluginB\r\n\x0b\x63onfig_typeJ\x04\x08\x02\x10\x03R\x06\x63onfig\x1a\xcb\x02\n\nStsService\x12\"\n\x1atoken_exchange_service_uri\x18\x01 \x01(\t\x12\x10\n\x08resource\x18\x02 \x01(\t\x12\x10\n\x08\x61udience\x18\x03 \x01(\t\x12\r\n\x05scope\x18\x04 \x01(\t\x12\x1c\n\x14requested_token_type\x18\x05 \x01(\t\x12#\n\x12subject_token_path\x18\x06 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12#\n\x12subject_token_type\x18\x07 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x18\n\x10\x61\x63tor_token_path\x18\x08 \x01(\t\x12\x18\n\x10\x61\x63tor_token_type\x18\t \x01(\t:J\x9a\xc5\x88\x1e\x45\nCenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.StsService:?\x9a\xc5\x88\x1e:\n8envoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentialsB\x1b\n\x14\x63redential_specifier\x12\x03\xf8\x42\x01\x1a\x9a\x02\n\x0b\x43hannelArgs\x12P\n\x04\x61rgs\x18\x01 \x03(\x0b\x32\x42.envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs.ArgsEntry\x1aL\n\x05Value\x12\x16\n\x0cstring_value\x18\x01 \x01(\tH\x00\x12\x13\n\tint_value\x18\x02 \x01(\x03H\x00\x42\x16\n\x0fvalue_specifier\x12\x03\xf8\x42\x01\x1ak\n\tArgsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12M\n\x05value\x18\x02 \x01(\x0b\x32>.envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs.Value:\x02\x38\x01:/\x9a\xc5\x88\x1e*\n(envoy.api.v2.core.GrpcService.GoogleGrpc:$\x9a\xc5\x88\x1e\x1f\n\x1d\x65nvoy.api.v2.core.GrpcServiceB\x17\n\x10target_specifier\x12\x03\xf8\x42\x01J\x04\x08\x04\x10\x05\x42\x84\x01\n\"io.envoyproxy.envoy.config.core.v3B\x10GrpcServiceProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.grpc_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\020GrpcServiceProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
  _GRPCSERVICE_ENVOYGRPC.fields_by_name['cluster_name']._options = None
  _GRPCSERVICE_ENVOYGRPC.fields_by_name['cluster_name']._serialized_options = b'\372B\004r\002\020\001'
  _GRPCSERVICE_ENVOYGRPC.fields_by_name['authority']._options = None
  _GRPCSERVICE_ENVOYGRPC.fields_by_name['authority']._serialized_options = b'\372B\016r\014\020\000(\200\200\001\300\001\002\310\001\000'
  _GRPCSERVICE_ENVOYGRPC._options = None
  _GRPCSERVICE_ENVOYGRPC._serialized_options = b'\232\305\210\036)\n\'envoy.api.v2.core.GrpcService.EnvoyGrpc'
  _GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS.fields_by_name['private_key']._options = None
  _GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS.fields_by_name['private_key']._serialized_options = b'\270\267\213\244\002\001'
  _GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS._serialized_options = b'\232\305\210\0369\n7envoy.api.v2.core.GrpcService.GoogleGrpc.SslCredentials'
  _GRPCSERVICE_GOOGLEGRPC_GOOGLELOCALCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_GOOGLELOCALCREDENTIALS._serialized_options = b'\232\305\210\036A\n?envoy.api.v2.core.GrpcService.GoogleGrpc.GoogleLocalCredentials'
  _GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS.oneofs_by_name['credential_specifier']._options = None
  _GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS.oneofs_by_name['credential_specifier']._serialized_options = b'\370B\001'
  _GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS._serialized_options = b'\232\305\210\036=\n;envoy.api.v2.core.GrpcService.GoogleGrpc.ChannelCredentials'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_SERVICEACCOUNTJWTACCESSCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_SERVICEACCOUNTJWTACCESSCREDENTIALS._serialized_options = b'\232\305\210\036]\n[envoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.ServiceAccountJWTAccessCredentials'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_GOOGLEIAMCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_GOOGLEIAMCREDENTIALS._serialized_options = b'\232\305\210\036O\nMenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.GoogleIAMCredentials'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_METADATACREDENTIALSFROMPLUGIN._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_METADATACREDENTIALSFROMPLUGIN._serialized_options = b'\232\305\210\036X\nVenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.MetadataCredentialsFromPlugin'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE.fields_by_name['subject_token_path']._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE.fields_by_name['subject_token_path']._serialized_options = b'\372B\004r\002\020\001'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE.fields_by_name['subject_token_type']._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE.fields_by_name['subject_token_type']._serialized_options = b'\372B\004r\002\020\001'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE._serialized_options = b'\232\305\210\036E\nCenvoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials.StsService'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS.oneofs_by_name['credential_specifier']._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS.oneofs_by_name['credential_specifier']._serialized_options = b'\370B\001'
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS._options = None
  _GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS._serialized_options = b'\232\305\210\036:\n8envoy.api.v2.core.GrpcService.GoogleGrpc.CallCredentials'
  _GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_VALUE.oneofs_by_name['value_specifier']._options = None
  _GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_VALUE.oneofs_by_name['value_specifier']._serialized_options = b'\370B\001'
  _GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_ARGSENTRY._options = None
  _GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_ARGSENTRY._serialized_options = b'8\001'
  _GRPCSERVICE_GOOGLEGRPC.fields_by_name['target_uri']._options = None
  _GRPCSERVICE_GOOGLEGRPC.fields_by_name['target_uri']._serialized_options = b'\372B\004r\002\020\001'
  _GRPCSERVICE_GOOGLEGRPC.fields_by_name['stat_prefix']._options = None
  _GRPCSERVICE_GOOGLEGRPC.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _GRPCSERVICE_GOOGLEGRPC._options = None
  _GRPCSERVICE_GOOGLEGRPC._serialized_options = b'\232\305\210\036*\n(envoy.api.v2.core.GrpcService.GoogleGrpc'
  _GRPCSERVICE.oneofs_by_name['target_specifier']._options = None
  _GRPCSERVICE.oneofs_by_name['target_specifier']._serialized_options = b'\370B\001'
  _GRPCSERVICE._options = None
  _GRPCSERVICE._serialized_options = b'\232\305\210\036\037\n\035envoy.api.v2.core.GrpcService'
  _globals['_GRPCSERVICE']._serialized_start=374
  _globals['_GRPCSERVICE']._serialized_end=4146
  _globals['_GRPCSERVICE_ENVOYGRPC']._serialized_start=688
  _globals['_GRPCSERVICE_ENVOYGRPC']._serialized_end=967
  _globals['_GRPCSERVICE_GOOGLEGRPC']._serialized_start=970
  _globals['_GRPCSERVICE_GOOGLEGRPC']._serialized_end=4077
  _globals['_GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS']._serialized_start=1450
  _globals['_GRPCSERVICE_GOOGLEGRPC_SSLCREDENTIALS']._serialized_end=1701
  _globals['_GRPCSERVICE_GOOGLEGRPC_GOOGLELOCALCREDENTIALS']._serialized_start=1703
  _globals['_GRPCSERVICE_GOOGLEGRPC_GOOGLELOCALCREDENTIALS']._serialized_end=1799
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS']._serialized_start=1802
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELCREDENTIALS']._serialized_end=2155
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS']._serialized_start=2158
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS']._serialized_end=3743
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_SERVICEACCOUNTJWTACCESSCREDENTIALS']._serialized_start=2743
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_SERVICEACCOUNTJWTACCESSCREDENTIALS']._serialized_end=2929
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_GOOGLEIAMCREDENTIALS']._serialized_start=2932
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_GOOGLEIAMCREDENTIALS']._serialized_end=3097
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_METADATACREDENTIALSFROMPLUGIN']._serialized_start=3100
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_METADATACREDENTIALSFROMPLUGIN']._serialized_end=3315
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE']._serialized_start=3318
  _globals['_GRPCSERVICE_GOOGLEGRPC_CALLCREDENTIALS_STSSERVICE']._serialized_end=3649
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS']._serialized_start=3746
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS']._serialized_end=4028
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_VALUE']._serialized_start=3843
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_VALUE']._serialized_end=3919
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_ARGSENTRY']._serialized_start=3921
  _globals['_GRPCSERVICE_GOOGLEGRPC_CHANNELARGS_ARGSENTRY']._serialized_end=4028
