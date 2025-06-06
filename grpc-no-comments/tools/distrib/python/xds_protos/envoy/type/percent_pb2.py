
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x18\x65nvoy/type/percent.proto\x12\nenvoy.type\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"1\n\x07Percent\x12&\n\x05value\x18\x01 \x01(\x01\x42\x17\xfa\x42\x14\x12\x12\x19\x00\x00\x00\x00\x00\x00Y@)\x00\x00\x00\x00\x00\x00\x00\x00\"\xb3\x01\n\x11\x46ractionalPercent\x12\x11\n\tnumerator\x18\x01 \x01(\r\x12L\n\x0b\x64\x65nominator\x18\x02 \x01(\x0e\x32-.envoy.type.FractionalPercent.DenominatorTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"=\n\x0f\x44\x65nominatorType\x12\x0b\n\x07HUNDRED\x10\x00\x12\x10\n\x0cTEN_THOUSAND\x10\x01\x12\x0b\n\x07MILLION\x10\x02\x42\x65\n\x18io.envoyproxy.envoy.typeB\x0cPercentProtoP\x01Z1github.com/envoyproxy/go-control-plane/envoy/type\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.percent_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\030io.envoyproxy.envoy.typeB\014PercentProtoP\001Z1github.com/envoyproxy/go-control-plane/envoy/type\272\200\310\321\006\002\020\001'
  _PERCENT.fields_by_name['value']._options = None
  _PERCENT.fields_by_name['value']._serialized_options = b'\372B\024\022\022\031\000\000\000\000\000\000Y@)\000\000\000\000\000\000\000\000'
  _FRACTIONALPERCENT.fields_by_name['denominator']._options = None
  _FRACTIONALPERCENT.fields_by_name['denominator']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_PERCENT']._serialized_start=96
  _globals['_PERCENT']._serialized_end=145
  _globals['_FRACTIONALPERCENT']._serialized_start=148
  _globals['_FRACTIONALPERCENT']._serialized_end=327
  _globals['_FRACTIONALPERCENT_DENOMINATORTYPE']._serialized_start=266
  _globals['_FRACTIONALPERCENT_DENOMINATORTYPE']._serialized_end=327
