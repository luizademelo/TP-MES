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

# Import dependencies from other Protocol Buffer files
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the Protocol Buffer descriptor by adding the serialized file data
# This contains the message definitions for proto message logging configuration
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nCenvoy/extensions/filters/http/proto_message_logging/v3/config.proto\x12\x36\x65nvoy.extensions.filters.http.proto_message_logging.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\"\xb5\x04\n\x19ProtoMessageLoggingConfig\x12\x37\n\x0b\x64\x61ta_source\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceH\x00\x12)\n\x1fproto_descriptor_typed_metadata\x18\x02 \x01(\tH\x00\x12g\n\x04mode\x18\x03 \x01(\x0e\x32Y.envoy.extensions.filters.http.proto_message_logging.v3.ProtoMessageLoggingConfig.LogMode\x12\x81\x01\n\x11logging_by_method\x18\x04 \x03(\x0b\x32\x66.envoy.extensions.filters.http.proto_message_logging.v3.ProtoMessageLoggingConfig.LoggingByMethodEntry\x1a}\n\x14LoggingByMethodEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12T\n\x05value\x18\x02 \x01(\x0b\x32\x45.envoy.extensions.filters.http.proto_message_logging.v3.MethodLogging:\x02\x38\x01\"6\n\x07LogMode\x12\x17\n\x13LogMode_UNSPECIFIED\x10\x00\x12\x12\n\x0e\x46IRST_AND_LAST\x10\x01\x42\x10\n\x0e\x64\x65scriptor_set\"\x89\x05\n\rMethodLogging\x12\x82\x01\n\x18request_logging_by_field\x18\x02 \x03(\x0b\x32`.envoy.extensions.filters.http.proto_message_logging.v3.MethodLogging.RequestLoggingByFieldEntry\x12\x84\x01\n\x19response_logging_by_field\x18\x03 \x03(\x0b\x32\x61.envoy.extensions.filters.http.proto_message_logging.v3.MethodLogging.ResponseLoggingByFieldEntry\x1a\x90\x01\n\x1aRequestLoggingByFieldEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x61\n\x05value\x18\x02 \x01(\x0e\x32R.envoy.extensions.filters.http.proto_message_logging.v3.MethodLogging.LogDirective:\x02\x38\x01\x1a\x91\x01\n\x1bResponseLoggingByFieldEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x61\n\x05value\x18\x02 \x01(\x0e\x32R.envoy.extensions.filters.http.proto_message_logging.v3.MethodLogging.LogDirective:\x02\x38\x01\"E\n\x0cLogDirective\x12\x1c\n\x18LogDirective_UNSPECIFIED\x10\x00\x12\x07\n\x03LOG\x10\x01\x12\x0e\n\nLOG_REDACT\x10\x02\x42\xdc\x01\nDio.envoyproxy.envoy.extensions.filters.http.proto_message_logging.v3B\x0b\x43onfigProtoP\x01Zugithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/proto_message_logging/v3;proto_message_loggingv3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.proto_message_logging.v3.config_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options including package and import paths
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\nDio.envoyproxy.envoy.extensions.filters.http.proto_message_logging.v3B\013ConfigProtoP\001Zugithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/proto_message_logging/v3;proto_message_loggingv3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
    
    # Set options for nested message entries
    _PROTOMESSAGELOGGINGCONFIG_LOGGINGBYMETHODENTRY._options = None
    _PROTOMESSAGELOGGINGCONFIG_LOGGINGBYMETHODENTRY._serialized_options = b'8\001'
    _METHODLOGGING_REQUESTLOGGINGBYFIELDENTRY._options = None
    _METHODLOGGING_REQUESTLOGGINGBYFIELDENTRY._serialized_options = b'8\001'
    _METHODLOGGING_RESPONSELOGGINGBYFIELDENTRY._options = None
    _METHODLOGGING_RESPONSELOGGINGBYFIELDENTRY._serialized_options = b'8\001'
    
    # Define serialized start and end positions for each message in the descriptor
    _globals['_PROTOMESSAGELOGGINGCONFIG']._serialized_start=225
    _globals['_PROTOMESSAGELOGGINGCONFIG']._serialized_end=790
    _globals['_PROTOMESSAGELOGGINGCONFIG_LOGGINGBYMETHODENTRY']._serialized_start=591
    _globals['_PROTOMESSAGELOGGINGCONFIG_LOGGINGBYMETHODENTRY']._serialized_end=716
    _globals['_PROTOMESSAGELOGGINGCONFIG_LOGMODE']._serialized_start=718
    _globals['_PROTOMESSAGELOGGINGCONFIG_LOGMODE']._serialized_end=772
    _globals['_METHODLOGGING']._serialized_start=793
    _globals['_METHODLOGGING']._serialized_end=1442
    _globals['_METHODLOGGING_REQUESTLOGGINGBYFIELDENTRY']._serialized_start=1079
    _globals['_METHODLOGGING_REQUESTLOGGINGBYFIELDENTRY']._serialized_end=1223
    _globals['_METHODLOGGING_RESPONSELOGGINGBYFIELDENTRY']._serialized_start=1226
    _globals['_METHODLOGGING_RESPONSELOGGINGBYFIELDENTRY']._serialized_end=1371
    _globals['_METHODLOGGING_LOGDIRECTIVE']._serialized_start=1373
    _globals['_METHODLOGGING_LOGDIRECTIVE']._serialized_end=1442
```