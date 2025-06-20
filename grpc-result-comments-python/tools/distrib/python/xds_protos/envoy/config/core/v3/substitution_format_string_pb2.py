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
from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer descriptor with serialized file data
# This contains the message definitions for SubstitutionFormatString and JsonFormatOptions
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/config/core/v3/substitution_format_string.proto\x12\x14\x65nvoy.config.core.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a$envoy/config/core/v3/extension.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\",\n\x11JsonFormatOptions\x12\x17\n\x0fsort_properties\x18\x01 \x01(\x08\"\x8b\x03\n\x18SubstitutionFormatString\x12\"\n\x0btext_format\x18\x01 \x01(\tB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\x38\n\x0bjson_format\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12>\n\x12text_format_source\x18\x05 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceH\x00\x12\x19\n\x11omit_empty_values\x18\x03 \x01(\x08\x12!\n\x0c\x63ontent_type\x18\x04 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00\x12>\n\nformatters\x18\x06 \x03(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x44\n\x13json_format_options\x18\x07 \x01(\x0b\x32\'.envoy.config.core.v3.JsonFormatOptionsB\r\n\x06\x66ormat\x12\x03\xf8\x42\x01\x42\x91\x01\n\"io.envoyproxy.envoy.config.core.v3B\x1dSubstitutionFormatStringProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.substitution_format_string_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set package and file options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\035SubstitutionFormatStringProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
    
    # Configure options for the 'format' oneof field in SubstitutionFormatString
    _SUBSTITUTIONFORMATSTRING.oneofs_by_name['format']._options = None
    _SUBSTITUTIONFORMATSTRING.oneofs_by_name['format']._serialized_options = b'\370B\001'
    
    # Configure options for individual fields in SubstitutionFormatString
    _SUBSTITUTIONFORMATSTRING.fields_by_name['text_format']._options = None
    _SUBSTITUTIONFORMATSTRING.fields_by_name['text_format']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
    _SUBSTITUTIONFORMATSTRING.fields_by_name['json_format']._options = None
    _SUBSTITUTIONFORMATSTRING.fields_by_name['json_format']._serialized_options = b'\372B\005\212\001\002\020\001'
    _SUBSTITUTIONFORMATSTRING.fields_by_name['content_type']._options = None
    _SUBSTITUTIONFORMATSTRING.fields_by_name['content_type']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
    
    # Define serialized start and end positions for each message in the descriptor
    _globals['_JSONFORMATOPTIONS']._serialized_start=273
    _globals['_JSONFORMATOPTIONS']._serialized_end=317
    _globals['_SUBSTITUTIONFORMATSTRING']._serialized_start=320
    _globals['_SUBSTITUTIONFORMATSTRING']._serialized_end=715
```