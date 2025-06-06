
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%google/api/expr/v1alpha1/syntax.proto\x12\x18google.api.expr.v1alpha1\x1a\x1egoogle/protobuf/duration.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"u\n\nParsedExpr\x12,\n\x04\x65xpr\x18\x02 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x39\n\x0bsource_info\x18\x03 \x01(\x0b\x32$.google.api.expr.v1alpha1.SourceInfo\"\x8a\x0b\n\x04\x45xpr\x12\n\n\x02id\x18\x02 \x01(\x03\x12\x38\n\nconst_expr\x18\x03 \x01(\x0b\x32\".google.api.expr.v1alpha1.ConstantH\x00\x12:\n\nident_expr\x18\x04 \x01(\x0b\x32$.google.api.expr.v1alpha1.Expr.IdentH\x00\x12<\n\x0bselect_expr\x18\x05 \x01(\x0b\x32%.google.api.expr.v1alpha1.Expr.SelectH\x00\x12\x38\n\tcall_expr\x18\x06 \x01(\x0b\x32#.google.api.expr.v1alpha1.Expr.CallH\x00\x12>\n\tlist_expr\x18\x07 \x01(\x0b\x32).google.api.expr.v1alpha1.Expr.CreateListH\x00\x12\x42\n\x0bstruct_expr\x18\x08 \x01(\x0b\x32+.google.api.expr.v1alpha1.Expr.CreateStructH\x00\x12J\n\x12\x63omprehension_expr\x18\t \x01(\x0b\x32,.google.api.expr.v1alpha1.Expr.ComprehensionH\x00\x1a\x15\n\x05Ident\x12\x0c\n\x04name\x18\x01 \x01(\t\x1a[\n\x06Select\x12/\n\x07operand\x18\x01 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\r\n\x05\x66ield\x18\x02 \x01(\t\x12\x11\n\ttest_only\x18\x03 \x01(\x08\x1av\n\x04\x43\x61ll\x12.\n\x06target\x18\x01 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x10\n\x08\x66unction\x18\x02 \x01(\t\x12,\n\x04\x61rgs\x18\x03 \x03(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x1aX\n\nCreateList\x12\x30\n\x08\x65lements\x18\x01 \x03(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x18\n\x10optional_indices\x18\x02 \x03(\x05\x1a\x99\x02\n\x0c\x43reateStruct\x12\x14\n\x0cmessage_name\x18\x01 \x01(\t\x12\x42\n\x07\x65ntries\x18\x02 \x03(\x0b\x32\x31.google.api.expr.v1alpha1.Expr.CreateStruct.Entry\x1a\xae\x01\n\x05\x45ntry\x12\n\n\x02id\x18\x01 \x01(\x03\x12\x13\n\tfield_key\x18\x02 \x01(\tH\x00\x12\x31\n\x07map_key\x18\x03 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.ExprH\x00\x12-\n\x05value\x18\x04 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x16\n\x0eoptional_entry\x18\x05 \x01(\x08\x42\n\n\x08key_kind\x1a\xc8\x02\n\rComprehension\x12\x10\n\x08iter_var\x18\x01 \x01(\t\x12\x11\n\titer_var2\x18\x08 \x01(\t\x12\x32\n\niter_range\x18\x02 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x10\n\x08\x61\x63\x63u_var\x18\x03 \x01(\t\x12\x31\n\taccu_init\x18\x04 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x36\n\x0eloop_condition\x18\x05 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12\x31\n\tloop_step\x18\x06 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr\x12.\n\x06result\x18\x07 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.ExprB\x0b\n\texpr_kind\"\xcd\x02\n\x08\x43onstant\x12\x30\n\nnull_value\x18\x01 \x01(\x0e\x32\x1a.google.protobuf.NullValueH\x00\x12\x14\n\nbool_value\x18\x02 \x01(\x08H\x00\x12\x15\n\x0bint64_value\x18\x03 \x01(\x03H\x00\x12\x16\n\x0cuint64_value\x18\x04 \x01(\x04H\x00\x12\x16\n\x0c\x64ouble_value\x18\x05 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x06 \x01(\tH\x00\x12\x15\n\x0b\x62ytes_value\x18\x07 \x01(\x0cH\x00\x12\x37\n\x0e\x64uration_value\x18\x08 \x01(\x0b\x32\x19.google.protobuf.DurationB\x02\x18\x01H\x00\x12\x39\n\x0ftimestamp_value\x18\t \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x02\x18\x01H\x00\x42\x0f\n\rconstant_kind\"\xfc\x05\n\nSourceInfo\x12\x16\n\x0esyntax_version\x18\x01 \x01(\t\x12\x10\n\x08location\x18\x02 \x01(\t\x12\x14\n\x0cline_offsets\x18\x03 \x03(\x05\x12\x46\n\tpositions\x18\x04 \x03(\x0b\x32\x33.google.api.expr.v1alpha1.SourceInfo.PositionsEntry\x12I\n\x0bmacro_calls\x18\x05 \x03(\x0b\x32\x34.google.api.expr.v1alpha1.SourceInfo.MacroCallsEntry\x12\x42\n\nextensions\x18\x06 \x03(\x0b\x32..google.api.expr.v1alpha1.SourceInfo.Extension\x1a\xd1\x02\n\tExtension\x12\n\n\x02id\x18\x01 \x01(\t\x12U\n\x13\x61\x66\x66\x65\x63ted_components\x18\x02 \x03(\x0e\x32\x38.google.api.expr.v1alpha1.SourceInfo.Extension.Component\x12G\n\x07version\x18\x03 \x01(\x0b\x32\x36.google.api.expr.v1alpha1.SourceInfo.Extension.Version\x1a\'\n\x07Version\x12\r\n\x05major\x18\x01 \x01(\x03\x12\r\n\x05minor\x18\x02 \x01(\x03\"o\n\tComponent\x12\x19\n\x15\x43OMPONENT_UNSPECIFIED\x10\x00\x12\x14\n\x10\x43OMPONENT_PARSER\x10\x01\x12\x1a\n\x16\x43OMPONENT_TYPE_CHECKER\x10\x02\x12\x15\n\x11\x43OMPONENT_RUNTIME\x10\x03\x1a\x30\n\x0ePositionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\x03\x12\r\n\x05value\x18\x02 \x01(\x05:\x02\x38\x01\x1aQ\n\x0fMacroCallsEntry\x12\x0b\n\x03key\x18\x01 \x01(\x03\x12-\n\x05value\x18\x02 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.Expr:\x02\x38\x01\"P\n\x0eSourcePosition\x12\x10\n\x08location\x18\x01 \x01(\t\x12\x0e\n\x06offset\x18\x02 \x01(\x05\x12\x0c\n\x04line\x18\x03 \x01(\x05\x12\x0e\n\x06\x63olumn\x18\x04 \x01(\x05\x42n\n\x1c\x63om.google.api.expr.v1alpha1B\x0bSyntaxProtoP\x01Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1alpha1.syntax_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034com.google.api.expr.v1alpha1B\013SyntaxProtoP\001Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\370\001\001'
  _CONSTANT.fields_by_name['duration_value']._options = None
  _CONSTANT.fields_by_name['duration_value']._serialized_options = b'\030\001'
  _CONSTANT.fields_by_name['timestamp_value']._options = None
  _CONSTANT.fields_by_name['timestamp_value']._serialized_options = b'\030\001'
  _SOURCEINFO_POSITIONSENTRY._options = None
  _SOURCEINFO_POSITIONSENTRY._serialized_options = b'8\001'
  _SOURCEINFO_MACROCALLSENTRY._options = None
  _SOURCEINFO_MACROCALLSENTRY._serialized_options = b'8\001'
  _globals['_PARSEDEXPR']._serialized_start=162
  _globals['_PARSEDEXPR']._serialized_end=279
  _globals['_EXPR']._serialized_start=282
  _globals['_EXPR']._serialized_end=1700
  _globals['_EXPR_IDENT']._serialized_start=748
  _globals['_EXPR_IDENT']._serialized_end=769
  _globals['_EXPR_SELECT']._serialized_start=771
  _globals['_EXPR_SELECT']._serialized_end=862
  _globals['_EXPR_CALL']._serialized_start=864
  _globals['_EXPR_CALL']._serialized_end=982
  _globals['_EXPR_CREATELIST']._serialized_start=984
  _globals['_EXPR_CREATELIST']._serialized_end=1072
  _globals['_EXPR_CREATESTRUCT']._serialized_start=1075
  _globals['_EXPR_CREATESTRUCT']._serialized_end=1356
  _globals['_EXPR_CREATESTRUCT_ENTRY']._serialized_start=1182
  _globals['_EXPR_CREATESTRUCT_ENTRY']._serialized_end=1356
  _globals['_EXPR_COMPREHENSION']._serialized_start=1359
  _globals['_EXPR_COMPREHENSION']._serialized_end=1687
  _globals['_CONSTANT']._serialized_start=1703
  _globals['_CONSTANT']._serialized_end=2036
  _globals['_SOURCEINFO']._serialized_start=2039
  _globals['_SOURCEINFO']._serialized_end=2803
  _globals['_SOURCEINFO_EXTENSION']._serialized_start=2333
  _globals['_SOURCEINFO_EXTENSION']._serialized_end=2670
  _globals['_SOURCEINFO_EXTENSION_VERSION']._serialized_start=2518
  _globals['_SOURCEINFO_EXTENSION_VERSION']._serialized_end=2557
  _globals['_SOURCEINFO_EXTENSION_COMPONENT']._serialized_start=2559
  _globals['_SOURCEINFO_EXTENSION_COMPONENT']._serialized_end=2670
  _globals['_SOURCEINFO_POSITIONSENTRY']._serialized_start=2672
  _globals['_SOURCEINFO_POSITIONSENTRY']._serialized_end=2720
  _globals['_SOURCEINFO_MACROCALLSENTRY']._serialized_start=2722
  _globals['_SOURCEINFO_MACROCALLSENTRY']._serialized_end=2803
  _globals['_SOURCEPOSITION']._serialized_start=2805
  _globals['_SOURCEPOSITION']._serialized_end=2885
