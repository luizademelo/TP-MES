
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.expr.v1beta1 import expr_pb2 as google_dot_api_dot_expr_dot_v1beta1_dot_expr__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"google/api/expr/v1beta1/decl.proto\x12\x17google.api.expr.v1beta1\x1a\"google/api/expr/v1beta1/expr.proto\"\xa5\x01\n\x04\x44\x65\x63l\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x0b\n\x03\x64oc\x18\x03 \x01(\t\x12\x33\n\x05ident\x18\x04 \x01(\x0b\x32\".google.api.expr.v1beta1.IdentDeclH\x00\x12\x39\n\x08\x66unction\x18\x05 \x01(\x0b\x32%.google.api.expr.v1beta1.FunctionDeclH\x00\x42\x06\n\x04kind\"\\\n\x08\x44\x65\x63lType\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0c\n\x04type\x18\x02 \x01(\t\x12\x36\n\x0btype_params\x18\x04 \x03(\x0b\x32!.google.api.expr.v1beta1.DeclType\"j\n\tIdentDecl\x12/\n\x04type\x18\x03 \x01(\x0b\x32!.google.api.expr.v1beta1.DeclType\x12,\n\x05value\x18\x04 \x01(\x0b\x32\x1d.google.api.expr.v1beta1.Expr\"\x93\x01\n\x0c\x46unctionDecl\x12\x30\n\x04\x61rgs\x18\x01 \x03(\x0b\x32\".google.api.expr.v1beta1.IdentDecl\x12\x36\n\x0breturn_type\x18\x02 \x01(\x0b\x32!.google.api.expr.v1beta1.DeclType\x12\x19\n\x11receiver_function\x18\x03 \x01(\x08\x42j\n\x1b\x63om.google.api.expr.v1beta1B\tDeclProtoP\x01Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1beta1.decl_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033com.google.api.expr.v1beta1B\tDeclProtoP\001Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\370\001\001'
  _globals['_DECL']._serialized_start=100
  _globals['_DECL']._serialized_end=265
  _globals['_DECLTYPE']._serialized_start=267
  _globals['_DECLTYPE']._serialized_end=359
  _globals['_IDENTDECL']._serialized_start=361
  _globals['_IDENTDECL']._serialized_end=467
  _globals['_FUNCTIONDECL']._serialized_start=470
  _globals['_FUNCTIONDECL']._serialized_end=617
