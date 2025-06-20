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

# Import dependent protocol buffer definitions
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.service.auth.v3 import attribute_context_pb2 as envoy_dot_service_dot_auth_dot_v3_dot_attribute__context__pb2
from envoy.type.v3 import http_status_pb2 as envoy_dot_type_dot_v3_dot_http__status__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the protocol buffer descriptor by adding the serialized file
# This contains all the message and service definitions
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)envoy/service/auth/v3/external_auth.proto\x12\x15\x65nvoy.service.auth.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a-envoy/service/auth/v3/attribute_context.proto\x1a\x1f\x65nvoy/type/v3/http_status.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x17google/rpc/status.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"v\n\x0c\x43heckRequest\x12;\n\nattributes\x18\x01 \x01(\x0b\x32\'.envoy.service.auth.v3.AttributeContext:)\x9a\xc5\x88\x1e$\n\"envoy.service.auth.v2.CheckRequest\"\xb8\x01\n\x12\x44\x65niedHttpResponse\x12)\n\x06status\x18\x01 \x01(\x0b\x32\x19.envoy.type.v3.HttpStatus\x12\x38\n\x07headers\x18\x02 \x03(\x0b\x32\'.envoy.config.core.v3.HeaderValueOption\x12\x0c\n\x04\x62ody\x18\x03 \x01(\t:/\x9a\xc5\x88\x1e*\n(envoy.service.auth.v2.DeniedHttpResponse\"\x87\x03\n\x0eOkHttpResponse\x12\x38\n\x07headers\x18\x02 \x03(\x0b\x32\'.envoy.config.core.v3.HeaderValueOption\x12\x19\n\x11headers_to_remove\x18\x05 \x03(\t\x12>\n\x10\x64ynamic_metadata\x18\x03 \x01(\x0b\x32\x17.google.protobuf.StructB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12H\n\x17response_headers_to_add\x18\x06 \x03(\x0b\x32\'.envoy.config.core.v3.HeaderValueOption\x12\x45\n\x17query_parameters_to_set\x18\x07 \x03(\x0b\x32$.envoy.config.core.v3.QueryParameter\x12\"\n\x1aquery_parameters_to_remove\x18\x08 \x03(\t:+\x9a\xc5\x88\x1e&\n$envoy.service.auth.v2.OkHttpResponse\"\xa7\x02\n\rCheckResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.google.rpc.Status\x12\x44\n\x0f\x64\x65nied_response\x18\x02 \x01(\x0b\x32).envoy.service.auth.v3.DeniedHttpResponseH\x00\x12<\n\x0bok_response\x18\x03 \x01(\x0b\x32%.envoy.service.auth.v3.OkHttpResponseH\x00\x12\x31\n\x10\x64ynamic_metadata\x18\x04 \x01(\x0b\x32\x17.google.protobuf.Struct:*\x9a\xc5\x88\x1e%\n#envoy.service.auth.v2.CheckResponseB\x0f\n\rhttp_response2e\n\rAuthorization\x12T\n\x05\x43heck\x12#.envoy.service.auth.v3.CheckRequest\x1a$.envoy.service.auth.v3.CheckResponse\"\x00\x42\x87\x01\n#io.envoyproxy.envoy.service.auth.v3B\x11\x45xternalAuthProtoP\x01ZCgithub.com/envoyproxy/go-control-plane/envoy/service/auth/v3;authv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.auth.v3.external_auth_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set package and import path options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.service.auth.v3B\021ExternalAuthProtoP\001ZCgithub.com/envoyproxy/go-control-plane/envoy/service/auth/v3;authv3\272\200\310\321\006\002\020\002'
    
    # Set options for each message type
    _CHECKREQUEST._options = None
    _CHECKREQUEST._serialized_options = b'\232\305\210\036$\n\"envoy.service.auth.v2.CheckRequest'
    _DENIEDHTTPRESPONSE._options = None
    _DENIEDHTTPRESPONSE._serialized_options = b'\232\305\210\036*\n(envoy.service.auth.v2.DeniedHttpResponse'
    
    # Set field-specific options for OkHttpResponse
    _OKHTTPRESPONSE.fields_by_name['dynamic_metadata']._options = None
    _OKHTTPRESPONSE.fields_by_name['dynamic_metadata']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
    _OKHTTPRESPONSE._options = None
    _OKHTTPRESPONSE._serialized_options = b'\232\305\210\036&\n$envoy.service.auth.v2.OkHttpResponse'
    
    _CHECKRESPONSE._options = None
    _CHECKRESPONSE._serialized_options = b'\232\305\210\036%\n#envoy.service.auth.v2.CheckResponse'

# Define the serialized start and end positions for each message type
_globals['_CHECKREQUEST']._serialized_start=339
_globals['_CHECKREQUEST']._serialized_end=457
_globals['_DENIEDHTTPRESPONSE']._serialized_start=460
_globals['_DENIEDHTTPRESPONSE']._serialized_end=644
_globals['_OKHTTPRESPONSE']._serialized_start=647
_globals['_OKHTTPRESPONSE']._serialized_end=1038
_globals['_CHECKRESPONSE']._serialized_start=1041
_globals['_CHECKRESPONSE']._serialized_end=1336

# Define the Authorization service and its Check method
_globals['_AUTHORIZATION']._serialized_start=1338
_globals['_AUTHORIZATION']._serialized_end=1439
```