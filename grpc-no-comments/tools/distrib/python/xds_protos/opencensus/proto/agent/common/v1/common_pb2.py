
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n-opencensus/proto/agent/common/v1/common.proto\x12 opencensus.proto.agent.common.v1\x1a\x1fgoogle/protobuf/timestamp.proto\"\xd8\x02\n\x04Node\x12G\n\nidentifier\x18\x01 \x01(\x0b\x32\x33.opencensus.proto.agent.common.v1.ProcessIdentifier\x12\x43\n\x0clibrary_info\x18\x02 \x01(\x0b\x32-.opencensus.proto.agent.common.v1.LibraryInfo\x12\x43\n\x0cservice_info\x18\x03 \x01(\x0b\x32-.opencensus.proto.agent.common.v1.ServiceInfo\x12J\n\nattributes\x18\x04 \x03(\x0b\x32\x36.opencensus.proto.agent.common.v1.Node.AttributesEntry\x1a\x31\n\x0f\x41ttributesEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"h\n\x11ProcessIdentifier\x12\x11\n\thost_name\x18\x01 \x01(\t\x12\x0b\n\x03pid\x18\x02 \x01(\r\x12\x33\n\x0fstart_timestamp\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\"\xa7\x02\n\x0bLibraryInfo\x12H\n\x08language\x18\x01 \x01(\x0e\x32\x36.opencensus.proto.agent.common.v1.LibraryInfo.Language\x12\x18\n\x10\x65xporter_version\x18\x02 \x01(\t\x12\x1c\n\x14\x63ore_library_version\x18\x03 \x01(\t\"\x95\x01\n\x08Language\x12\x18\n\x14LANGUAGE_UNSPECIFIED\x10\x00\x12\x07\n\x03\x43PP\x10\x01\x12\x0b\n\x07\x43_SHARP\x10\x02\x12\n\n\x06\x45RLANG\x10\x03\x12\x0b\n\x07GO_LANG\x10\x04\x12\x08\n\x04JAVA\x10\x05\x12\x0b\n\x07NODE_JS\x10\x06\x12\x07\n\x03PHP\x10\x07\x12\n\n\x06PYTHON\x10\x08\x12\x08\n\x04RUBY\x10\t\x12\n\n\x06WEB_JS\x10\n\"\x1b\n\x0bServiceInfo\x12\x0c\n\x04name\x18\x01 \x01(\tB\xa2\x01\n#io.opencensus.proto.agent.common.v1B\x0b\x43ommonProtoP\x01ZIgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/common/v1\xea\x02 OpenCensus.Proto.Agent.Common.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.agent.common.v1.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.opencensus.proto.agent.common.v1B\013CommonProtoP\001ZIgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/common/v1\352\002 OpenCensus.Proto.Agent.Common.V1'
  _NODE_ATTRIBUTESENTRY._options = None
  _NODE_ATTRIBUTESENTRY._serialized_options = b'8\001'
  _globals['_NODE']._serialized_start=117
  _globals['_NODE']._serialized_end=461
  _globals['_NODE_ATTRIBUTESENTRY']._serialized_start=412
  _globals['_NODE_ATTRIBUTESENTRY']._serialized_end=461
  _globals['_PROCESSIDENTIFIER']._serialized_start=463
  _globals['_PROCESSIDENTIFIER']._serialized_end=567
  _globals['_LIBRARYINFO']._serialized_start=570
  _globals['_LIBRARYINFO']._serialized_end=865
  _globals['_LIBRARYINFO_LANGUAGE']._serialized_start=716
  _globals['_LIBRARYINFO_LANGUAGE']._serialized_end=865
  _globals['_SERVICEINFO']._serialized_start=867
  _globals['_SERVICEINFO']._serialized_end=894
