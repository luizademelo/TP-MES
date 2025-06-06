
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api.expr.v1alpha1 import checked_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_checked__pb2
from google.api.expr.v1alpha1 import eval_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_eval__pb2
from google.api.expr.v1alpha1 import syntax_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_syntax__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n>google/api/expr/conformance/v1alpha1/conformance_service.proto\x12$google.api.expr.conformance.v1alpha1\x1a\x17google/api/client.proto\x1a&google/api/expr/v1alpha1/checked.proto\x1a#google/api/expr/v1alpha1/eval.proto\x1a%google/api/expr/v1alpha1/syntax.proto\x1a\x17google/rpc/status.proto\"k\n\x0cParseRequest\x12\x12\n\ncel_source\x18\x01 \x01(\t\x12\x16\n\x0esyntax_version\x18\x02 \x01(\t\x12\x17\n\x0fsource_location\x18\x03 \x01(\t\x12\x16\n\x0e\x64isable_macros\x18\x04 \x01(\x08\"n\n\rParseResponse\x12\x39\n\x0bparsed_expr\x18\x01 \x01(\x0b\x32$.google.api.expr.v1alpha1.ParsedExpr\x12\"\n\x06issues\x18\x02 \x03(\x0b\x32\x12.google.rpc.Status\"\xa2\x01\n\x0c\x43heckRequest\x12\x39\n\x0bparsed_expr\x18\x01 \x01(\x0b\x32$.google.api.expr.v1alpha1.ParsedExpr\x12\x30\n\x08type_env\x18\x02 \x03(\x0b\x32\x1e.google.api.expr.v1alpha1.Decl\x12\x11\n\tcontainer\x18\x03 \x01(\t\x12\x12\n\nno_std_env\x18\x04 \x01(\x08\"p\n\rCheckResponse\x12;\n\x0c\x63hecked_expr\x18\x01 \x01(\x0b\x32%.google.api.expr.v1alpha1.CheckedExpr\x12\"\n\x06issues\x18\x02 \x03(\x0b\x32\x12.google.rpc.Status\"\xd2\x02\n\x0b\x45valRequest\x12;\n\x0bparsed_expr\x18\x01 \x01(\x0b\x32$.google.api.expr.v1alpha1.ParsedExprH\x00\x12=\n\x0c\x63hecked_expr\x18\x02 \x01(\x0b\x32%.google.api.expr.v1alpha1.CheckedExprH\x00\x12Q\n\x08\x62indings\x18\x03 \x03(\x0b\x32?.google.api.expr.conformance.v1alpha1.EvalRequest.BindingsEntry\x12\x11\n\tcontainer\x18\x04 \x01(\t\x1aT\n\rBindingsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x32\n\x05value\x18\x02 \x01(\x0b\x32#.google.api.expr.v1alpha1.ExprValue:\x02\x38\x01\x42\x0b\n\texpr_kind\"g\n\x0c\x45valResponse\x12\x33\n\x06result\x18\x01 \x01(\x0b\x32#.google.api.expr.v1alpha1.ExprValue\x12\"\n\x06issues\x18\x02 \x03(\x0b\x32\x12.google.rpc.Status\"P\n\x0eSourcePosition\x12\x10\n\x08location\x18\x01 \x01(\t\x12\x0e\n\x06offset\x18\x02 \x01(\x05\x12\x0c\n\x04line\x18\x03 \x01(\x05\x12\x0e\n\x06\x63olumn\x18\x04 \x01(\x05\"\x80\x02\n\x0cIssueDetails\x12M\n\x08severity\x18\x01 \x01(\x0e\x32;.google.api.expr.conformance.v1alpha1.IssueDetails.Severity\x12\x46\n\x08position\x18\x02 \x01(\x0b\x32\x34.google.api.expr.conformance.v1alpha1.SourcePosition\x12\n\n\x02id\x18\x03 \x01(\x03\"M\n\x08Severity\x12\x18\n\x14SEVERITY_UNSPECIFIED\x10\x00\x12\x0f\n\x0b\x44\x45PRECATION\x10\x01\x12\x0b\n\x07WARNING\x10\x02\x12\t\n\x05\x45RROR\x10\x03\x32\x84\x03\n\x12\x43onformanceService\x12r\n\x05Parse\x12\x32.google.api.expr.conformance.v1alpha1.ParseRequest\x1a\x33.google.api.expr.conformance.v1alpha1.ParseResponse\"\x00\x12r\n\x05\x43heck\x12\x32.google.api.expr.conformance.v1alpha1.CheckRequest\x1a\x33.google.api.expr.conformance.v1alpha1.CheckResponse\"\x00\x12o\n\x04\x45val\x12\x31.google.api.expr.conformance.v1alpha1.EvalRequest\x1a\x32.google.api.expr.conformance.v1alpha1.EvalResponse\"\x00\x1a\x15\xca\x41\x12\x63\x65l.googleapis.comB\x94\x01\n(com.google.api.expr.conformance.v1alpha1B\x17\x43onformanceServiceProtoP\x01ZJgoogle.golang.org/genproto/googleapis/api/expr/conformance/v1alpha1;confpb\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.conformance.v1alpha1.conformance_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(com.google.api.expr.conformance.v1alpha1B\027ConformanceServiceProtoP\001ZJgoogle.golang.org/genproto/googleapis/api/expr/conformance/v1alpha1;confpb\370\001\001'
  _EVALREQUEST_BINDINGSENTRY._options = None
  _EVALREQUEST_BINDINGSENTRY._serialized_options = b'8\001'
  _CONFORMANCESERVICE._options = None
  _CONFORMANCESERVICE._serialized_options = b'\312A\022cel.googleapis.com'
  _globals['_PARSEREQUEST']._serialized_start=270
  _globals['_PARSEREQUEST']._serialized_end=377
  _globals['_PARSERESPONSE']._serialized_start=379
  _globals['_PARSERESPONSE']._serialized_end=489
  _globals['_CHECKREQUEST']._serialized_start=492
  _globals['_CHECKREQUEST']._serialized_end=654
  _globals['_CHECKRESPONSE']._serialized_start=656
  _globals['_CHECKRESPONSE']._serialized_end=768
  _globals['_EVALREQUEST']._serialized_start=771
  _globals['_EVALREQUEST']._serialized_end=1109
  _globals['_EVALREQUEST_BINDINGSENTRY']._serialized_start=1012
  _globals['_EVALREQUEST_BINDINGSENTRY']._serialized_end=1096
  _globals['_EVALRESPONSE']._serialized_start=1111
  _globals['_EVALRESPONSE']._serialized_end=1214
  _globals['_SOURCEPOSITION']._serialized_start=1216
  _globals['_SOURCEPOSITION']._serialized_end=1296
  _globals['_ISSUEDETAILS']._serialized_start=1299
  _globals['_ISSUEDETAILS']._serialized_end=1555
  _globals['_ISSUEDETAILS_SEVERITY']._serialized_start=1478
  _globals['_ISSUEDETAILS_SEVERITY']._serialized_end=1555
  _globals['_CONFORMANCESERVICE']._serialized_start=1558
  _globals['_CONFORMANCESERVICE']._serialized_end=1946
