
import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor.FileDescriptor(
  name='messages.proto',
  package='grpc.testing',
  syntax='proto3',
  serialized_pb=_b('\n\x0emessages.proto\x12\x0cgrpc.testing\"\x1a\n\tBoolValue\x12\r\n\x05value\x18\x01 \x01(\x08\"@\n\x07Payload\x12\'\n\x04type\x18\x01 \x01(\x0e\x32\x19.grpc.testing.PayloadType\x12\x0c\n\x04\x62ody\x18\x02 \x01(\x0c\"+\n\nEchoStatus\x12\x0c\n\x04\x63ode\x18\x01 \x01(\x05\x12\x0f\n\x07message\x18\x02 \x01(\t\"\xce\x02\n\rSimpleRequest\x12\x30\n\rresponse_type\x18\x01 \x01(\x0e\x32\x19.grpc.testing.PayloadType\x12\x15\n\rresponse_size\x18\x02 \x01(\x05\x12&\n\x07payload\x18\x03 \x01(\x0b\x32\x15.grpc.testing.Payload\x12\x15\n\rfill_username\x18\x04 \x01(\x08\x12\x18\n\x10\x66ill_oauth_scope\x18\x05 \x01(\x08\x12\x34\n\x13response_compressed\x18\x06 \x01(\x0b\x32\x17.grpc.testing.BoolValue\x12\x31\n\x0fresponse_status\x18\x07 \x01(\x0b\x32\x18.grpc.testing.EchoStatus\x12\x32\n\x11\x65xpect_compressed\x18\x08 \x01(\x0b\x32\x17.grpc.testing.BoolValue\"_\n\x0eSimpleResponse\x12&\n\x07payload\x18\x01 \x01(\x0b\x32\x15.grpc.testing.Payload\x12\x10\n\x08username\x18\x02 \x01(\t\x12\x13\n\x0boauth_scope\x18\x03 \x01(\t\"w\n\x19StreamingInputCallRequest\x12&\n\x07payload\x18\x01 \x01(\x0b\x32\x15.grpc.testing.Payload\x12\x32\n\x11\x65xpect_compressed\x18\x02 \x01(\x0b\x32\x17.grpc.testing.BoolValue\"=\n\x1aStreamingInputCallResponse\x12\x1f\n\x17\x61ggregated_payload_size\x18\x01 \x01(\x05\"d\n\x12ResponseParameters\x12\x0c\n\x04size\x18\x01 \x01(\x05\x12\x13\n\x0binterval_us\x18\x02 \x01(\x05\x12+\n\ncompressed\x18\x03 \x01(\x0b\x32\x17.grpc.testing.BoolValue\"\xe8\x01\n\x1aStreamingOutputCallRequest\x12\x30\n\rresponse_type\x18\x01 \x01(\x0e\x32\x19.grpc.testing.PayloadType\x12=\n\x13response_parameters\x18\x02 \x03(\x0b\x32 .grpc.testing.ResponseParameters\x12&\n\x07payload\x18\x03 \x01(\x0b\x32\x15.grpc.testing.Payload\x12\x31\n\x0fresponse_status\x18\x07 \x01(\x0b\x32\x18.grpc.testing.EchoStatus\"E\n\x1bStreamingOutputCallResponse\x12&\n\x07payload\x18\x01 \x01(\x0b\x32\x15.grpc.testing.Payload\"3\n\x0fReconnectParams\x12 \n\x18max_reconnect_backoff_ms\x18\x01 \x01(\x05\"3\n\rReconnectInfo\x12\x0e\n\x06passed\x18\x01 \x01(\x08\x12\x12\n\nbackoff_ms\x18\x02 \x03(\x05*\x1f\n\x0bPayloadType\x12\x10\n\x0c\x43OMPRESSABLE\x10\x00\x62\x06proto3')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_PAYLOADTYPE = _descriptor.EnumDescriptor(
  name='PayloadType',
  full_name='grpc.testing.PayloadType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='COMPRESSABLE', index=0, number=0,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1303,
  serialized_end=1334,
)
_sym_db.RegisterEnumDescriptor(_PAYLOADTYPE)

PayloadType = enum_type_wrapper.EnumTypeWrapper(_PAYLOADTYPE)
COMPRESSABLE = 0

_BOOLVALUE = _descriptor.Descriptor(
  name='BoolValue',
  full_name='grpc.testing.BoolValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='value', full_name='grpc.testing.BoolValue.value', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=32,
  serialized_end=58,
)

_PAYLOAD = _descriptor.Descriptor(
  name='Payload',
  full_name='grpc.testing.Payload',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='grpc.testing.Payload.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='body', full_name='grpc.testing.Payload.body', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=60,
  serialized_end=124,
)

_ECHOSTATUS = _descriptor.Descriptor(
  name='EchoStatus',
  full_name='grpc.testing.EchoStatus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='code', full_name='grpc.testing.EchoStatus.code', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='message', full_name='grpc.testing.EchoStatus.message', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=126,
  serialized_end=169,
)

_SIMPLEREQUEST = _descriptor.Descriptor(
  name='SimpleRequest',
  full_name='grpc.testing.SimpleRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='response_type', full_name='grpc.testing.SimpleRequest.response_type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='response_size', full_name='grpc.testing.SimpleRequest.response_size', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='payload', full_name='grpc.testing.SimpleRequest.payload', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='fill_username', full_name='grpc.testing.SimpleRequest.fill_username', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='fill_oauth_scope', full_name='grpc.testing.SimpleRequest.fill_oauth_scope', index=4,
      number=5, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='response_compressed', full_name='grpc.testing.SimpleRequest.response_compressed', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='response_status', full_name='grpc.testing.SimpleRequest.response_status', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='expect_compressed', full_name='grpc.testing.SimpleRequest.expect_compressed', index=7,
      number=8, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=172,
  serialized_end=506,
)

_SIMPLERESPONSE = _descriptor.Descriptor(
  name='SimpleResponse',
  full_name='grpc.testing.SimpleResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='payload', full_name='grpc.testing.SimpleResponse.payload', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='username', full_name='grpc.testing.SimpleResponse.username', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='oauth_scope', full_name='grpc.testing.SimpleResponse.oauth_scope', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=508,
  serialized_end=603,
)

_STREAMINGINPUTCALLREQUEST = _descriptor.Descriptor(
  name='StreamingInputCallRequest',
  full_name='grpc.testing.StreamingInputCallRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='payload', full_name='grpc.testing.StreamingInputCallRequest.payload', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='expect_compressed', full_name='grpc.testing.StreamingInputCallRequest.expect_compressed', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=605,
  serialized_end=724,
)

_STREAMINGINPUTCALLRESPONSE = _descriptor.Descriptor(
  name='StreamingInputCallResponse',
  full_name='grpc.testing.StreamingInputCallResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='aggregated_payload_size', full_name='grpc.testing.StreamingInputCallResponse.aggregated_payload_size', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=726,
  serialized_end=787,
)

_RESPONSEPARAMETERS = _descriptor.Descriptor(
  name='ResponseParameters',
  full_name='grpc.testing.ResponseParameters',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='size', full_name='grpc.testing.ResponseParameters.size', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='interval_us', full_name='grpc.testing.ResponseParameters.interval_us', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='compressed', full_name='grpc.testing.ResponseParameters.compressed', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=789,
  serialized_end=889,
)

_STREAMINGOUTPUTCALLREQUEST = _descriptor.Descriptor(
  name='StreamingOutputCallRequest',
  full_name='grpc.testing.StreamingOutputCallRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='response_type', full_name='grpc.testing.StreamingOutputCallRequest.response_type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='response_parameters', full_name='grpc.testing.StreamingOutputCallRequest.response_parameters', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='payload', full_name='grpc.testing.StreamingOutputCallRequest.payload', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='response_status', full_name='grpc.testing.StreamingOutputCallRequest.response_status', index=3,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=892,
  serialized_end=1124,
)

_STREAMINGOUTPUTCALLRESPONSE = _descriptor.Descriptor(
  name='StreamingOutputCallResponse',
  full_name='grpc.testing.StreamingOutputCallResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='payload', full_name='grpc.testing.StreamingOutputCallResponse.payload', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1126,
  serialized_end=1195,
)

_RECONNECTPARAMS = _descriptor.Descriptor(
  name='ReconnectParams',
  full_name='grpc.testing.ReconnectParams',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='max_reconnect_backoff_ms', full_name='grpc.testing.ReconnectParams.max_reconnect_backoff_ms', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1197,
  serialized_end=1248,
)

_RECONNECTINFO = _descriptor.Descriptor(
  name='ReconnectInfo',
  full_name='grpc.testing.ReconnectInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='passed', full_name='grpc.testing.ReconnectInfo.passed', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='backoff_ms', full_name='grpc.testing.ReconnectInfo.backoff_ms', index=1,
      number=2, type=5, cpp_type=1, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1250,
  serialized_end=1301,
)

_PAYLOAD.fields_by_name['type'].enum_type = _PAYLOADTYPE
_SIMPLEREQUEST.fields_by_name['response_type'].enum_type = _PAYLOADTYPE
_SIMPLEREQUEST.fields_by_name['payload'].message_type = _PAYLOAD
_SIMPLEREQUEST.fields_by_name['response_compressed'].message_type = _BOOLVALUE
_SIMPLEREQUEST.fields_by_name['response_status'].message_type = _ECHOSTATUS
_SIMPLEREQUEST.fields_by_name['expect_compressed'].message_type = _BOOLVALUE
_SIMPLERESPONSE.fields_by_name['payload'].message_type = _PAYLOAD
_STREAMINGINPUTCALLREQUEST.fields_by_name['payload'].message_type = _PAYLOAD
_STREAMINGINPUTCALLREQUEST.fields_by_name['expect_compressed'].message_type = _BOOLVALUE
_RESPONSEPARAMETERS.fields_by_name['compressed'].message_type = _BOOLVALUE
_STREAMINGOUTPUTCALLREQUEST.fields_by_name['response_type'].enum_type = _PAYLOADTYPE
_STREAMINGOUTPUTCALLREQUEST.fields_by_name['response_parameters'].message_type = _RESPONSEPARAMETERS
_STREAMINGOUTPUTCALLREQUEST.fields_by_name['payload'].message_type = _PAYLOAD
_STREAMINGOUTPUTCALLREQUEST.fields_by_name['response_status'].message_type = _ECHOSTATUS
_STREAMINGOUTPUTCALLRESPONSE.fields_by_name['payload'].message_type = _PAYLOAD
DESCRIPTOR.message_types_by_name['BoolValue'] = _BOOLVALUE
DESCRIPTOR.message_types_by_name['Payload'] = _PAYLOAD
DESCRIPTOR.message_types_by_name['EchoStatus'] = _ECHOSTATUS
DESCRIPTOR.message_types_by_name['SimpleRequest'] = _SIMPLEREQUEST
DESCRIPTOR.message_types_by_name['SimpleResponse'] = _SIMPLERESPONSE
DESCRIPTOR.message_types_by_name['StreamingInputCallRequest'] = _STREAMINGINPUTCALLREQUEST
DESCRIPTOR.message_types_by_name['StreamingInputCallResponse'] = _STREAMINGINPUTCALLRESPONSE
DESCRIPTOR.message_types_by_name['ResponseParameters'] = _RESPONSEPARAMETERS
DESCRIPTOR.message_types_by_name['StreamingOutputCallRequest'] = _STREAMINGOUTPUTCALLREQUEST
DESCRIPTOR.message_types_by_name['StreamingOutputCallResponse'] = _STREAMINGOUTPUTCALLRESPONSE
DESCRIPTOR.message_types_by_name['ReconnectParams'] = _RECONNECTPARAMS
DESCRIPTOR.message_types_by_name['ReconnectInfo'] = _RECONNECTINFO
DESCRIPTOR.enum_types_by_name['PayloadType'] = _PAYLOADTYPE

BoolValue = _reflection.GeneratedProtocolMessageType('BoolValue', (_message.Message,), dict(
  DESCRIPTOR = _BOOLVALUE,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(BoolValue)

Payload = _reflection.GeneratedProtocolMessageType('Payload', (_message.Message,), dict(
  DESCRIPTOR = _PAYLOAD,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(Payload)

EchoStatus = _reflection.GeneratedProtocolMessageType('EchoStatus', (_message.Message,), dict(
  DESCRIPTOR = _ECHOSTATUS,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(EchoStatus)

SimpleRequest = _reflection.GeneratedProtocolMessageType('SimpleRequest', (_message.Message,), dict(
  DESCRIPTOR = _SIMPLEREQUEST,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(SimpleRequest)

SimpleResponse = _reflection.GeneratedProtocolMessageType('SimpleResponse', (_message.Message,), dict(
  DESCRIPTOR = _SIMPLERESPONSE,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(SimpleResponse)

StreamingInputCallRequest = _reflection.GeneratedProtocolMessageType('StreamingInputCallRequest', (_message.Message,), dict(
  DESCRIPTOR = _STREAMINGINPUTCALLREQUEST,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(StreamingInputCallRequest)

StreamingInputCallResponse = _reflection.GeneratedProtocolMessageType('StreamingInputCallResponse', (_message.Message,), dict(
  DESCRIPTOR = _STREAMINGINPUTCALLRESPONSE,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(StreamingInputCallResponse)

ResponseParameters = _reflection.GeneratedProtocolMessageType('ResponseParameters', (_message.Message,), dict(
  DESCRIPTOR = _RESPONSEPARAMETERS,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(ResponseParameters)

StreamingOutputCallRequest = _reflection.GeneratedProtocolMessageType('StreamingOutputCallRequest', (_message.Message,), dict(
  DESCRIPTOR = _STREAMINGOUTPUTCALLREQUEST,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(StreamingOutputCallRequest)

StreamingOutputCallResponse = _reflection.GeneratedProtocolMessageType('StreamingOutputCallResponse', (_message.Message,), dict(
  DESCRIPTOR = _STREAMINGOUTPUTCALLRESPONSE,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(StreamingOutputCallResponse)

ReconnectParams = _reflection.GeneratedProtocolMessageType('ReconnectParams', (_message.Message,), dict(
  DESCRIPTOR = _RECONNECTPARAMS,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(ReconnectParams)

ReconnectInfo = _reflection.GeneratedProtocolMessageType('ReconnectInfo', (_message.Message,), dict(
  DESCRIPTOR = _RECONNECTINFO,
  __module__ = 'messages_pb2'

  ))
_sym_db.RegisterMessage(ReconnectInfo)
