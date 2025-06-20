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
from envoy.extensions.filters.network.thrift_proxy.v3 import thrift_proxy_pb2 as envoy_dot_extensions_dot_filters_dot_network_dot_thrift__proxy_dot_v3_dot_thrift__proxy__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer descriptor by adding the serialized file
# This contains all the message and enum definitions for the ThriftToMetadata filter
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nLenvoy/extensions/filters/http/thrift_to_metadata/v3/thrift_to_metadata.proto\x12\x33\x65nvoy.extensions.filters.http.thrift_to_metadata.v3\x1a\x43\x65nvoy/extensions/filters/network/thrift_proxy/v3/thrift_proxy.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"g\n\x0cKeyValuePair\x12\x1a\n\x12metadata_namespace\x18\x01 \x01(\t\x12\x14\n\x03key\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12%\n\x05value\x18\x03 \x01(\x0b\x32\x16.google.protobuf.Value\"\xa5\x01\n\rFieldSelector\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12 \n\x02id\x18\x02 \x01(\x05\x42\x14\xfa\x42\x11\x1a\x0f\x18\xff\xff\x01(\x80\x80\xfe\xff\xff\xff\xff\xff\xff\x01\x12Q\n\x05\x63hild\x18\x03 \x01(\x0b\x32\x42.envoy.extensions.filters.http.thrift_to_metadata.v3.FieldSelector:\x08\xd2\xc6\xa4\xe1\x06\x02\x08\x01\"\x84\x03\n\x04Rule\x12I\n\x05\x66ield\x18\x01 \x01(\x0e\x32:.envoy.extensions.filters.http.thrift_to_metadata.v3.Field\x12\x64\n\x0e\x66ield_selector\x18\x02 \x01(\x0b\x32\x42.envoy.extensions.filters.http.thrift_to_metadata.v3.FieldSelectorB\x08\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x12\x1d\n\x0bmethod_name\x18\x03 \x01(\tB\x08\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x12U\n\non_present\x18\x04 \x01(\x0b\x32\x41.envoy.extensions.filters.http.thrift_to_metadata.v3.KeyValuePair\x12U\n\non_missing\x18\x05 \x01(\x0b\x32\x41.envoy.extensions.filters.http.thrift_to_metadata.v3.KeyValuePair\"\xbe\x03\n\x10ThriftToMetadata\x12P\n\rrequest_rules\x18\x01 \x03(\x0b\x32\x39.envoy.extensions.filters.http.thrift_to_metadata.v3.Rule\x12Q\n\x0eresponse_rules\x18\x02 \x03(\x0b\x32\x39.envoy.extensions.filters.http.thrift_to_metadata.v3.Rule\x12\\\n\ttransport\x18\x03 \x01(\x0e\x32?.envoy.extensions.filters.network.thrift_proxy.v3.TransportTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12Z\n\x08protocol\x18\x04 \x01(\x0e\x32>.envoy.extensions.filters.network.thrift_proxy.v3.ProtocolTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12)\n\x13\x61llow_content_types\x18\x05 \x03(\tB\x0c\xfa\x42\t\x92\x01\x06\"\x04r\x02\x10\x01\x12 \n\x18\x61llow_empty_content_type\x18\x06 \x01(\x08\"\xc9\x01\n\x18ThriftToMetadataPerRoute\x12P\n\rrequest_rules\x18\x01 \x03(\x0b\x32\x39.envoy.extensions.filters.http.thrift_to_metadata.v3.Rule\x12Q\n\x0eresponse_rules\x18\x02 \x03(\x0b\x32\x39.envoy.extensions.filters.http.thrift_to_metadata.v3.Rule:\x08\xd2\xc6\xa4\xe1\x06\x02\x08\x01*z\n\x05\x46ield\x12\x0f\n\x0bMETHOD_NAME\x10\x00\x12\x0c\n\x08PROTOCOL\x10\x01\x12\r\n\tTRANSPORT\x10\x02\x12\x10\n\x0cHEADER_FLAGS\x10\x03\x12\x0f\n\x0bSEQUENCE_ID\x10\x04\x12\x10\n\x0cMESSAGE_TYPE\x10\x05\x12\x0e\n\nREPLY_TYPE\x10\x06\x42\xd5\x01\nAio.envoyproxy.envoy.extensions.filters.http.thrift_to_metadata.v3B\x15ThriftToMetadataProtoP\x01Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/thrift_to_metadata/v3;thrift_to_metadatav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.thrift_to_metadata.v3.thrift_to_metadata_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Main descriptor options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\nAio.envoyproxy.envoy.extensions.filters.http.thrift_to_metadata.v3B\025ThriftToMetadataProtoP\001Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/thrift_to_metadata/v3;thrift_to_metadatav3\272\200\310\321\006\002\020\002'
    
    # Field options for various messages
    _KEYVALUEPAIR.fields_by_name['key']._options = None
    _KEYVALUEPAIR.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
    
    _FIELDSELECTOR.fields_by_name['name']._options = None
    _FIELDSELECTOR.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
    _FIELDSELECTOR.fields_by_name['id']._options = None
    _FIELDSELECTOR.fields_by_name['id']._serialized_options = b'\372B\021\032\017\030\377\377\001(\200\200\376\377\377\377\377\377\377\001'
    _FIELDSELECTOR._options = None
    _FIELDSELECTOR._serialized_options = b'\322\306\244\341\006\002\010\001'
    
    _RULE.fields_by_name['field_selector']._options = None
    _RULE.fields_by_name['field_selector']._serialized_options = b'\322\306\244\341\006\002\010\001'
    _RULE.fields_by_name['method_name']._options = None
    _RULE.fields_by_name['method_name']._serialized_options = b'\322\306\244\341\006\002\010\001'
    
    _THRIFTTOMETADATA.fields_by_name['transport']._options = None
    _THRIFTTOMETADATA.fields_by_name['transport']._serialized_options = b'\372B\005\202\001\002\020\001'
    _THRIFTTOMETADATA.fields_by_name['protocol']._options = None
    _THRIFTTOMETADATA.fields_by_name['protocol']._serialized_options = b'\372B\005\202\001\002\020\001'
    _THRIFTTOMETADATA.fields_by_name['allow_content_types']._options = None
    _THRIFTTOMETADATA.fields_by_name['allow_content_types']._serialized_options = b'\372B\t\222\001\006\"\004r\002\020\001'
    
    _THRIFTTOMETADATAPERROUTE._options = None
    _THRIFTTOMETADATAPERROUTE._serialized_options = b'\322\306\244\341\006\002\010\001'

    # Define serialized start and end points for each message and enum
    _globals['_FIELD']._serialized_start=1638
    _globals['_FIELD']._serialized_end=1760
    _globals['_KEYVALUEPAIR']._serialized_start=321
    _globals['_KEYVALUEPAIR']._serialized_end=424
    _globals['_FIELDSELECTOR']._serialized_start=427
    _globals['_FIELDSELECTOR']._serialized_end=592
    _globals['_RULE']._serialized_start=595
    _globals['_RULE']._serialized_end=983
    _globals['_THRIFTTOMETADATA']._serialized_start=986
    _globals['_THRIFTTOMETADATA']._serialized_end=1432
    _globals['_THRIFTTOMETADATAPERROUTE']._serialized_start=1435
    _globals['_THRIFTTOMETADATAPERROUTE']._serialized_end=1636
```