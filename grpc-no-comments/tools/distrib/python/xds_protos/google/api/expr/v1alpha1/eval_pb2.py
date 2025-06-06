
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.expr.v1alpha1 import value_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_value__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#google/api/expr/v1alpha1/eval.proto\x12\x18google.api.expr.v1alpha1\x1a$google/api/expr/v1alpha1/value.proto\x1a\x17google/rpc/status.proto\"\xa4\x01\n\tEvalState\x12\x33\n\x06values\x18\x01 \x03(\x0b\x32#.google.api.expr.v1alpha1.ExprValue\x12;\n\x07results\x18\x03 \x03(\x0b\x32*.google.api.expr.v1alpha1.EvalState.Result\x1a%\n\x06Result\x12\x0c\n\x04\x65xpr\x18\x01 \x01(\x03\x12\r\n\x05value\x18\x02 \x01(\x03\"\xb3\x01\n\tExprValue\x12\x30\n\x05value\x18\x01 \x01(\x0b\x32\x1f.google.api.expr.v1alpha1.ValueH\x00\x12\x33\n\x05\x65rror\x18\x02 \x01(\x0b\x32\".google.api.expr.v1alpha1.ErrorSetH\x00\x12\x37\n\x07unknown\x18\x03 \x01(\x0b\x32$.google.api.expr.v1alpha1.UnknownSetH\x00\x42\x06\n\x04kind\".\n\x08\x45rrorSet\x12\"\n\x06\x65rrors\x18\x01 \x03(\x0b\x32\x12.google.rpc.Status\"\x1b\n\nUnknownSet\x12\r\n\x05\x65xprs\x18\x01 \x03(\x03\x42l\n\x1c\x63om.google.api.expr.v1alpha1B\tEvalProtoP\x01Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1alpha1.eval_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034com.google.api.expr.v1alpha1B\tEvalProtoP\001Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\370\001\001'
  _globals['_EVALSTATE']._serialized_start=129
  _globals['_EVALSTATE']._serialized_end=293
  _globals['_EVALSTATE_RESULT']._serialized_start=256
  _globals['_EVALSTATE_RESULT']._serialized_end=293
  _globals['_EXPRVALUE']._serialized_start=296
  _globals['_EXPRVALUE']._serialized_end=475
  _globals['_ERRORSET']._serialized_start=477
  _globals['_ERRORSET']._serialized_end=523
  _globals['_UNKNOWNSET']._serialized_start=525
  _globals['_UNKNOWNSET']._serialized_end=552
