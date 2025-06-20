Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for protocol buffers
_sym_db = _symbol_database.Default()

# Import dependencies from other proto files
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the protocol buffer descriptor by adding the serialized file data
# This contains the binary representation of the .proto file
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1a\x65nvoy/admin/v3/certs.proto\x12\x0e\x65nvoy.admin.v3\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"j\n\x0c\x43\x65rtificates\x12\x31\n\x0c\x63\x65rtificates\x18\x01 \x03(\x0b\x32\x1b.envoy.admin.v3.Certificate:\'\x9a\xc5\x88\x1e\"\n envoy.admin.v2alpha.Certificates\"\xa2\x01\n\x0b\x43\x65rtificate\x12\x33\n\x07\x63\x61_cert\x18\x01 \x03(\x0b\x32\".envoy.admin.v3.CertificateDetails\x12\x36\n\ncert_chain\x18\x02 \x03(\x0b\x32\".envoy.admin.v3.CertificateDetails:&\x9a\xc5\x88\x1e!\n\x1f\x65nvoy.admin.v2alpha.Certificate\"\xe2\x03\n\x12\x43\x65rtificateDetails\x12\x0c\n\x04path\x18\x01 \x01(\t\x12\x15\n\rserial_number\x18\x02 \x01(\t\x12?\n\x11subject_alt_names\x18\x03 \x03(\x0b\x32$.envoy.admin.v3.SubjectAlternateName\x12\x1d\n\x15\x64\x61ys_until_expiration\x18\x04 \x01(\x04\x12.\n\nvalid_from\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x33\n\x0f\x65xpiration_time\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x44\n\x0cocsp_details\x18\x07 \x01(\x0b\x32..envoy.admin.v3.CertificateDetails.OcspDetails\x1am\n\x0bOcspDetails\x12.\n\nvalid_from\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12.\n\nexpiration\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:-\x9a\xc5\x88\x1e(\n&envoy.admin.v2alpha.CertificateDetails\"\x83\x01\n\x14SubjectAlternateName\x12\r\n\x03\x64ns\x18\x01 \x01(\tH\x00\x12\r\n\x03uri\x18\x02 \x01(\tH\x00\x12\x14\n\nip_address\x18\x03 \x01(\tH\x00:/\x9a\xc5\x88\x1e*\n(envoy.admin.v2alpha.SubjectAlternateNameB\x06\n\x04nameBs\n\x1cio.envoyproxy.envoy.admin.v3B\nCertsProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.certs_pb2', _globals)

# Configure descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set various options for the descriptors:
    # - Package and import path information
    # - Versioning annotations for backward compatibility
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\nCertsProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
    
    _CERTIFICATES._options = None
    _CERTIFICATES._serialized_options = b'\232\305\210\036\"\n envoy.admin.v2alpha.Certificates'
    
    _CERTIFICATE._options = None
    _CERTIFICATE._serialized_options = b'\232\305\210\036!\n\037envoy.admin.v2alpha.Certificate'
    
    _CERTIFICATEDETAILS._options = None
    _CERTIFICATEDETAILS._serialized_options = b'\232\305\210\036(\n&envoy.admin.v2alpha.CertificateDetails'
    
    _SUBJECTALTERNATENAME._options = None
    _SUBJECTALTERNATENAME._serialized_options = b'\232\305\210\036*\n(envoy.admin.v2alpha.SubjectAlternateName'

    # Define serialized start and end positions for each message in the descriptor
    _globals['_CERTIFICATES']._serialized_start=145
    _globals['_CERTIFICATES']._serialized_end=251
    _globals['_CERTIFICATE']._serialized_start=254
    _globals['_CERTIFICATE']._serialized_end=416
    _globals['_CERTIFICATEDETAILS']._serialized_start=419
    _globals['_CERTIFICATEDETAILS']._serialized_end=901
    _globals['_CERTIFICATEDETAILS_OCSPDETAILS']._serialized_start=745
    _globals['_CERTIFICATEDETAILS_OCSPDETAILS']._serialized_end=854
    _globals['_SUBJECTALTERNATENAME']._serialized_start=904
    _globals['_SUBJECTALTERNATENAME']._serialized_end=1035
```