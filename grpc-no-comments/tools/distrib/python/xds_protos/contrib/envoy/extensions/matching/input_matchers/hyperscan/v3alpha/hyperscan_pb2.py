
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nRcontrib/envoy/extensions/matching/input_matchers/hyperscan/v3alpha/hyperscan.proto\x12:envoy.extensions.matching.input_matchers.hyperscan.v3alpha\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xab\x02\n\tHyperscan\x12\x66\n\x07regexes\x18\x01 \x03(\x0b\x32K.envoy.extensions.matching.input_matchers.hyperscan.v3alpha.Hyperscan.RegexB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\xb5\x01\n\x05Regex\x12\x16\n\x05regex\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\n\n\x02id\x18\x02 \x01(\r\x12\x10\n\x08\x63\x61seless\x18\x03 \x01(\x08\x12\x0f\n\x07\x64ot_all\x18\x04 \x01(\x08\x12\x11\n\tmultiline\x18\x05 \x01(\x08\x12\x13\n\x0b\x61llow_empty\x18\x06 \x01(\x08\x12\x0c\n\x04utf8\x18\x07 \x01(\x08\x12\x0b\n\x03ucp\x18\x08 \x01(\x08\x12\x13\n\x0b\x63ombination\x18\t \x01(\x08\x12\r\n\x05quiet\x18\n \x01(\x08\x42\xcf\x01\nHio.envoyproxy.envoy.extensions.matching.input_matchers.hyperscan.v3alphaB\x0eHyperscanProtoP\x01Zigithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/matching/input_matchers/hyperscan/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.matching.input_matchers.hyperscan.v3alpha.hyperscan_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nHio.envoyproxy.envoy.extensions.matching.input_matchers.hyperscan.v3alphaB\016HyperscanProtoP\001Zigithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/matching/input_matchers/hyperscan/v3alpha\272\200\310\321\006\002\020\002'
  _HYPERSCAN_REGEX.fields_by_name['regex']._options = None
  _HYPERSCAN_REGEX.fields_by_name['regex']._serialized_options = b'\372B\004r\002\020\001'
  _HYPERSCAN.fields_by_name['regexes']._options = None
  _HYPERSCAN.fields_by_name['regexes']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_HYPERSCAN']._serialized_start=203
  _globals['_HYPERSCAN']._serialized_end=502
  _globals['_HYPERSCAN_REGEX']._serialized_start=321
  _globals['_HYPERSCAN_REGEX']._serialized_end=502
