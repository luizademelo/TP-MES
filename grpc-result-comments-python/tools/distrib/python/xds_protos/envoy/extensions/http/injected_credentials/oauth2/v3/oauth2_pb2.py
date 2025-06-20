Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary protocol buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for protocol buffers
_sym_db = _symbol_database.Default()

# Import required protocol buffer definitions from other packages
from envoy.config.core.v3 import http_uri_pb2 as envoy_dot_config_dot_core_dot_v3_dot_http__uri__pb2
from envoy.extensions.transport_sockets.tls.v3 import secret_pb2 as envoy_dot_extensions_dot_transport__sockets_dot_tls_dot_v3_dot_secret__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the protocol buffer descriptor by adding the serialized file
# This contains the complete definition of the OAuth2 protocol buffer message
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nAenvoy/extensions/http/injected_credentials/oauth2/v3/oauth2.proto\x12\x34\x65nvoy.extensions.http.injected_credentials.oauth2.v3\x1a#envoy/config/core/v3/http_uri.proto\x1a\x36\x65nvoy/extensions/transport_sockets/tls/v3/secret.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xbf\x04\n\x06OAuth2\x12?\n\x0etoken_endpoint\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.HttpUriB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0e\n\x06scopes\x18\x02 \x03(\t\x12l\n\x12\x63lient_credentials\x18\x03 \x01(\x0b\x32N.envoy.extensions.http.injected_credentials.oauth2.v3.OAuth2.ClientCredentialsH\x00\x12I\n\x1atoken_fetch_retry_interval\x18\x04 \x01(\x0b\x32\x19.google.protobuf.DurationB\n\xfa\x42\x07\xaa\x01\x04\x32\x02\x08\x01\x1a\xe6\x01\n\x11\x43lientCredentials\x12\x1a\n\tclient_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12[\n\rclient_secret\x18\x02 \x01(\x0b\x32:.envoy.extensions.transport_sockets.tls.v3.SdsSecretConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12X\n\tauth_type\x18\x03 \x01(\x0e\x32\x45.envoy.extensions.http.injected_credentials.oauth2.v3.OAuth2.AuthType\"0\n\x08\x41uthType\x12\x0e\n\nBASIC_AUTH\x10\x00\x12\x14\n\x10URL_ENCODED_BODY\x10\x01\x42\x10\n\tflow_type\x12\x03\xf8\x42\x01\x42\xc9\x01\nBio.envoyproxy.envoy.extensions.http.injected_credentials.oauth2.v3B\x0bOauth2ProtoP\x01Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/injected_credentials/oauth2/v3;oauth2v3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.injected_credentials.oauth2.v3.oauth2_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set package-level options
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nBio.envoyproxy.envoy.extensions.http.injected_credentials.oauth2.v3B\013Oauth2ProtoP\001Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/injected_credentials/oauth2/v3;oauth2v3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  
  # Set field-specific options for ClientCredentials message
  _OAUTH2_CLIENTCREDENTIALS.fields_by_name['client_id']._options = None
  _OAUTH2_CLIENTCREDENTIALS.fields_by_name['client_id']._serialized_options = b'\372B\004r\002\020\001'
  _OAUTH2_CLIENTCREDENTIALS.fields_by_name['client_secret']._options = None
  _OAUTH2_CLIENTCREDENTIALS.fields_by_name['client_secret']._serialized_options = b'\372B\005\212\001\002\020\001'
  
  # Set options for OAuth2 oneof field
  _OAUTH2.oneofs_by_name['flow_type']._options = None
  _OAUTH2.oneofs_by_name['flow_type']._serialized_options = b'\370B\001'
  
  # Set field-specific options for OAuth2 message
  _OAUTH2.fields_by_name['token_endpoint']._options = None
  _OAUTH2.fields_by_name['token_endpoint']._serialized_options = b'\372B\005\212\001\002\020\001'
  _OAUTH2.fields_by_name['token_fetch_retry_interval']._options = None
  _OAUTH2.fields_by_name['token_fetch_retry_interval']._serialized_options = b'\372B\007\252\001\0042\002\010\001'
  
  # Define the serialized start and end positions for each message
  _globals['_OAUTH2']._serialized_start=338
  _globals['_OAUTH2']._serialized_end=913
  _globals['_OAUTH2_CLIENTCREDENTIALS']._serialized_start=615
  _globals['_OAUTH2_CLIENTCREDENTIALS']._serialized_end=845
  _globals['_OAUTH2_AUTHTYPE']._serialized_start=847
  _globals['_OAUTH2_AUTHTYPE']._serialized_end=895
```