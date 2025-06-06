
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.expr.v1beta1 import source_pb2 as google_dot_api_dot_expr_dot_v1beta1_dot_source__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"google/api/expr/v1beta1/expr.proto\x12\x17google.api.expr.v1beta1\x1a$google/api/expr/v1beta1/source.proto\x1a\x1cgoogle/protobuf/struct.proto\"\x8b\x01\n\nParsedExpr\x12+\n\x04\x65xpr\x18\x02 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\x38\n\x0bsource_info\x18\x03 \x01(\x0b\x32#.google.api.expr.v1beta1.SourceInfo\x12\x16\n\x0esyntax_version\x18\x04 \x01(\t\"\xab\n\n\x04\x45xpr\x12\n\n\x02id\x18\x02 \x01(\x05\x12\x38\n\x0cliteral_expr\x18\x03 \x01(\x0b\x32 .google.api.expr.v1beta1.LiteralH\x00\x12\x39\n\nident_expr\x18\x04 \x01(\x0b\x32#.google.api.expr.v1beta1.Expr.IdentH\x00\x12;\n\x0bselect_expr\x18\x05 \x01(\x0b\x32$.google.api.expr.v1beta1.Expr.SelectH\x00\x12\x37\n\tcall_expr\x18\x06 \x01(\x0b\x32\".google.api.expr.v1beta1.Expr.CallH\x00\x12=\n\tlist_expr\x18\x07 \x01(\x0b\x32(.google.api.expr.v1beta1.Expr.CreateListH\x00\x12\x41\n\x0bstruct_expr\x18\x08 \x01(\x0b\x32*.google.api.expr.v1beta1.Expr.CreateStructH\x00\x12I\n\x12\x63omprehension_expr\x18\t \x01(\x0b\x32+.google.api.expr.v1beta1.Expr.ComprehensionH\x00\x1a\x15\n\x05Ident\x12\x0c\n\x04name\x18\x01 \x01(\t\x1aZ\n\x06Select\x12.\n\x07operand\x18\x01 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\r\n\x05\x66ield\x18\x02 \x01(\t\x12\x11\n\ttest_only\x18\x03 \x01(\x08\x1at\n\x04\x43\x61ll\x12-\n\x06target\x18\x01 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\x10\n\x08\x66unction\x18\x02 \x01(\t\x12+\n\x04\x61rgs\x18\x03 \x03(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x1a=\n\nCreateList\x12/\n\x08\x65lements\x18\x01 \x03(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x1a\xf6\x01\n\x0c\x43reateStruct\x12\x0c\n\x04type\x18\x01 \x01(\t\x12\x41\n\x07\x65ntries\x18\x02 \x03(\x0b\x32\x30.google.api.expr.v1beta1.Expr.CreateStruct.Entry\x1a\x94\x01\n\x05\x45ntry\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x13\n\tfield_key\x18\x02 \x01(\tH\x00\x12\x30\n\x07map_key\x18\x03 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.ExprH\x00\x12,\n\x05value\x18\x04 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.ExprB\n\n\x08key_kind\x1a\xb0\x02\n\rComprehension\x12\x10\n\x08iter_var\x18\x01 \x01(\t\x12\x31\n\niter_range\x18\x02 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\x10\n\x08\x61\x63\x63u_var\x18\x03 \x01(\t\x12\x30\n\taccu_init\x18\x04 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\x35\n\x0eloop_condition\x18\x05 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12\x30\n\tloop_step\x18\x06 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\x12-\n\x06result\x18\x07 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.ExprB\x0b\n\texpr_kind\"\xd8\x01\n\x07Literal\x12\x30\n\nnull_value\x18\x01 \x01(\x0e\x32\x1a.google.protobuf.NullValueH\x00\x12\x14\n\nbool_value\x18\x02 \x01(\x08H\x00\x12\x15\n\x0bint64_value\x18\x03 \x01(\x03H\x00\x12\x16\n\x0cuint64_value\x18\x04 \x01(\x04H\x00\x12\x16\n\x0c\x64ouble_value\x18\x05 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x06 \x01(\tH\x00\x12\x15\n\x0b\x62ytes_value\x18\x07 \x01(\x0cH\x00\x42\x0f\n\rconstant_kindBj\n\x1b\x63om.google.api.expr.v1beta1B\tExprProtoP\x01Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1beta1.expr_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033com.google.api.expr.v1beta1B\tExprProtoP\001Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\370\001\001'
  _globals['_PARSEDEXPR']._serialized_start=132
  _globals['_PARSEDEXPR']._serialized_end=271
  _globals['_EXPR']._serialized_start=274
  _globals['_EXPR']._serialized_end=1597
  _globals['_EXPR_IDENT']._serialized_start=734
  _globals['_EXPR_IDENT']._serialized_end=755
  _globals['_EXPR_SELECT']._serialized_start=757
  _globals['_EXPR_SELECT']._serialized_end=847
  _globals['_EXPR_CALL']._serialized_start=849
  _globals['_EXPR_CALL']._serialized_end=965
  _globals['_EXPR_CREATELIST']._serialized_start=967
  _globals['_EXPR_CREATELIST']._serialized_end=1028
  _globals['_EXPR_CREATESTRUCT']._serialized_start=1031
  _globals['_EXPR_CREATESTRUCT']._serialized_end=1277
  _globals['_EXPR_CREATESTRUCT_ENTRY']._serialized_start=1129
  _globals['_EXPR_CREATESTRUCT_ENTRY']._serialized_end=1277
  _globals['_EXPR_COMPREHENSION']._serialized_start=1280
  _globals['_EXPR_COMPREHENSION']._serialized_end=1584
  _globals['_LITERAL']._serialized_start=1600
  _globals['_LITERAL']._serialized_end=1816
