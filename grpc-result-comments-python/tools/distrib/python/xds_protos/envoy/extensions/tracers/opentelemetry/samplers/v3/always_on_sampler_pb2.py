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

# Import dependency proto file for UDPA annotations
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the protocol buffer descriptor by adding the serialized file data
# This contains:
# - The full path to the proto file
# - The package name (envoy.extensions.tracers.opentelemetry.samplers.v3)
# - The imported proto file (status.proto)
# - The message definition (AlwaysOnSamplerConfig)
# - Various options including Go package path and proto version
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nJenvoy/extensions/tracers/opentelemetry/samplers/v3/always_on_sampler.proto\x12\x32\x65nvoy.extensions.tracers.opentelemetry.samplers.v3\x1a\x1dudpa/annotations/status.proto\"\x17\n\x15\x41lwaysOnSamplerConfigB\xc8\x01\n@io.envoyproxy.envoy.extensions.tracers.opentelemetry.samplers.v3B\x14\x41lwaysOnSamplerProtoP\x01Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/samplers/v3;samplersv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Get the global symbol table
_globals = globals()

# Build message and enum descriptors from the descriptor
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)

# Build top-level descriptors and messages
# This registers the generated classes in the global namespace
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.tracers.opentelemetry.samplers.v3.always_on_sampler_pb2', _globals)

# If not using C++ descriptors (Python implementation),
# set descriptor options and serialized options
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set descriptor options to None to use Python implementation
    DESCRIPTOR._options = None
    
    # Set serialized options including:
    # - Java package name
    # - Go package path
    # - Proto version annotation
    DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.tracers.opentelemetry.samplers.v3B\024AlwaysOnSamplerProtoP\001Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/samplers/v3;samplersv3\272\200\310\321\006\002\020\002'
    
    # Set the byte offsets for the AlwaysOnSamplerConfig message
    # in the serialized file
    _globals['_ALWAYSONSAMPLERCONFIG']._serialized_start=161
    _globals['_ALWAYSONSAMPLERCONFIG']._serialized_end=184
```