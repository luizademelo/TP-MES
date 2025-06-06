
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nNenvoy/config/filter/http/aws_request_signing/v2alpha/aws_request_signing.proto\x12\x34\x65nvoy.config.filter.http.aws_request_signing.v2alpha\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"a\n\x11\x41wsRequestSigning\x12\x1d\n\x0cservice_name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x17\n\x06region\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x14\n\x0chost_rewrite\x18\x03 \x01(\tB\xff\x01\nBio.envoyproxy.envoy.config.filter.http.aws_request_signing.v2alphaB\x16\x41wsRequestSigningProtoP\x01Z[github.com/envoyproxy/go-control-plane/envoy/config/filter/http/aws_request_signing/v2alpha\xf2\x98\xfe\x8f\x05\x36\x12\x34\x65nvoy.extensions.filters.http.aws_request_signing.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.aws_request_signing.v2alpha.aws_request_signing_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nBio.envoyproxy.envoy.config.filter.http.aws_request_signing.v2alphaB\026AwsRequestSigningProtoP\001Z[github.com/envoyproxy/go-control-plane/envoy/config/filter/http/aws_request_signing/v2alpha\362\230\376\217\0056\0224envoy.extensions.filters.http.aws_request_signing.v3\272\200\310\321\006\002\020\001'
  _AWSREQUESTSIGNING.fields_by_name['service_name']._options = None
  _AWSREQUESTSIGNING.fields_by_name['service_name']._serialized_options = b'\372B\004r\002 \001'
  _AWSREQUESTSIGNING.fields_by_name['region']._options = None
  _AWSREQUESTSIGNING.fields_by_name['region']._serialized_options = b'\372B\004r\002 \001'
  _globals['_AWSREQUESTSIGNING']._serialized_start=224
  _globals['_AWSREQUESTSIGNING']._serialized_end=321
