
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.expr.v1alpha1 import value_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_value__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&google/api/expr/v1alpha1/explain.proto\x12\x18google.api.expr.v1alpha1\x1a$google/api/expr/v1alpha1/value.proto\"\xab\x01\n\x07\x45xplain\x12/\n\x06values\x18\x01 \x03(\x0b\x32\x1f.google.api.expr.v1alpha1.Value\x12>\n\nexpr_steps\x18\x02 \x03(\x0b\x32*.google.api.expr.v1alpha1.Explain.ExprStep\x1a+\n\x08\x45xprStep\x12\n\n\x02id\x18\x01 \x01(\x03\x12\x13\n\x0bvalue_index\x18\x02 \x01(\x05:\x02\x18\x01\x42o\n\x1c\x63om.google.api.expr.v1alpha1B\x0c\x45xplainProtoP\x01Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1alpha1.explain_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034com.google.api.expr.v1alpha1B\014ExplainProtoP\001Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\370\001\001'
  _EXPLAIN._options = None
  _EXPLAIN._serialized_options = b'\030\001'
  _globals['_EXPLAIN']._serialized_start=107
  _globals['_EXPLAIN']._serialized_end=278
  _globals['_EXPLAIN_EXPRSTEP']._serialized_start=231
  _globals['_EXPLAIN_EXPRSTEP']._serialized_end=274
