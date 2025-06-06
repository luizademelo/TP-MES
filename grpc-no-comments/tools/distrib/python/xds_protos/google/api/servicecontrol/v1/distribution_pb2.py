
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import distribution_pb2 as google_dot_api_dot_distribution__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/google/api/servicecontrol/v1/distribution.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a\x1dgoogle/api/distribution.proto\"\x9e\x05\n\x0c\x44istribution\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12\x0c\n\x04mean\x18\x02 \x01(\x01\x12\x0f\n\x07minimum\x18\x03 \x01(\x01\x12\x0f\n\x07maximum\x18\x04 \x01(\x01\x12 \n\x18sum_of_squared_deviation\x18\x05 \x01(\x01\x12\x15\n\rbucket_counts\x18\x06 \x03(\x03\x12R\n\x0elinear_buckets\x18\x07 \x01(\x0b\x32\x38.google.api.servicecontrol.v1.Distribution.LinearBucketsH\x00\x12\\\n\x13\x65xponential_buckets\x18\x08 \x01(\x0b\x32=.google.api.servicecontrol.v1.Distribution.ExponentialBucketsH\x00\x12V\n\x10\x65xplicit_buckets\x18\t \x01(\x0b\x32:.google.api.servicecontrol.v1.Distribution.ExplicitBucketsH\x00\x12\x34\n\texemplars\x18\n \x03(\x0b\x32!.google.api.Distribution.Exemplar\x1aJ\n\rLinearBuckets\x12\x1a\n\x12num_finite_buckets\x18\x01 \x01(\x05\x12\r\n\x05width\x18\x02 \x01(\x01\x12\x0e\n\x06offset\x18\x03 \x01(\x01\x1aV\n\x12\x45xponentialBuckets\x12\x1a\n\x12num_finite_buckets\x18\x01 \x01(\x05\x12\x15\n\rgrowth_factor\x18\x02 \x01(\x01\x12\r\n\x05scale\x18\x03 \x01(\x01\x1a!\n\x0f\x45xplicitBuckets\x12\x0e\n\x06\x62ounds\x18\x01 \x03(\x01\x42\x0f\n\rbucket_optionB\xec\x01\n com.google.api.servicecontrol.v1B\x11\x44istributionProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xf8\x01\x01\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.distribution_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\021DistributionProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\370\001\001\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _globals['_DISTRIBUTION']._serialized_start=113
  _globals['_DISTRIBUTION']._serialized_end=783
  _globals['_DISTRIBUTION_LINEARBUCKETS']._serialized_start=569
  _globals['_DISTRIBUTION_LINEARBUCKETS']._serialized_end=643
  _globals['_DISTRIBUTION_EXPONENTIALBUCKETS']._serialized_start=645
  _globals['_DISTRIBUTION_EXPONENTIALBUCKETS']._serialized_end=731
  _globals['_DISTRIBUTION_EXPLICITBUCKETS']._serialized_start=733
  _globals['_DISTRIBUTION_EXPLICITBUCKETS']._serialized_end=766
