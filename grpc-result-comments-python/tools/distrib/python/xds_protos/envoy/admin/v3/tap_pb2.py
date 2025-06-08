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
from envoy.config.tap.v3 import common_pb2 as envoy_dot_config_dot_tap_dot_v3_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer descriptor by adding the serialized file data
# This contains the binary representation of the tap.proto file and its dependencies
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x18\x65nvoy/admin/v3/tap.proto\x12\x0e\x65nvoy.admin.v3\x1a envoy/config/tap/v3/common.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x8d\x01\n\nTapRequest\x12\x1a\n\tconfig_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12<\n\ntap_config\x18\x02 \x01(\x0b\x32\x1e.envoy.config.tap.v3.TapConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.admin.v2alpha.TapRequestBq\n\x1cio.envoyproxy.envoy.admin.v3B\x08TapProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.tap_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set package-level options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\010TapProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
    
    # Set field-specific options for TapRequest message
    _TAPREQUEST.fields_by_name['config_id']._options = None
    _TAPREQUEST.fields_by_name['config_id']._serialized_options = b'\372B\004r\002\020\001'
    _TAPREQUEST.fields_by_name['tap_config']._options = None
    _TAPREQUEST.fields_by_name['tap_config']._serialized_options = b'\372B\005\212\001\002\020\001'
    
    # Set message-level options for TapRequest
    _TAPREQUEST._options = None
    _TAPREQUEST._serialized_options = b'\232\305\210\036 \n\036envoy.admin.v2alpha.TapRequest'
    
    # Record the byte offsets where the TapRequest message starts and ends in the descriptor
    _globals['_TAPREQUEST']._serialized_start=170
    _globals['_TAPREQUEST']._serialized_end=311
```

Key aspects covered in the comments:
1. Imports and their purposes
2. Symbol database initialization
3. Protocol Buffer descriptor creation
4. Message and enum descriptor building
5. Options configuration for both package and message levels
6. Byte offset tracking for message location in descriptor
7. Conditional handling for C++ descriptor usage

The comments explain both the structural aspects of the Protocol Buffer implementation and the specific configurations being applied to the TapRequest message and its fields.