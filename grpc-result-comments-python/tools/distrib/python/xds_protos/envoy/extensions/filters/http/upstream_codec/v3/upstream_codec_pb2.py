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

# Import dependency: status annotations from udpa
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

# Define the Protocol Buffer descriptor by adding the serialized file data
# This contains the message definitions and package information for:
# envoy.extensions.filters.http.upstream_codec.v3.UpstreamCodec
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDenvoy/extensions/filters/http/upstream_codec/v3/upstream_codec.proto\x12/envoy.extensions.filters.http.upstream_codec.v3\x1a\x1dudpa/annotations/status.proto\"\x0f\n\rUpstreamCodecB\xc6\x01\n=io.envoyproxy.envoy.extensions.filters.http.upstream_codec.v3B\x12UpstreamCodecProtoP\x01Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/upstream_codec/v3;upstream_codecv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
# Build top-level descriptors and messages for the specified proto file
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.upstream_codec.v3.upstream_codec_pb2', _globals)

# Configure descriptor options when not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  # Set descriptor options including:
  # - Java package name
  # - Go package path
  # - Metadata for Envoy API versioning
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n=io.envoyproxy.envoy.extensions.filters.http.upstream_codec.v3B\022UpstreamCodecProtoP\001Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/upstream_codec/v3;upstream_codecv3\272\200\310\321\006\002\020\002'
  
  # Set the byte offsets for the UpstreamCodec message in the serialized file
  _globals['_UPSTREAMCODEC']._serialized_start=152
  _globals['_UPSTREAMCODEC']._serialized_end=167
```