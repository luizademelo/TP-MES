
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import regex_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_regex__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\ndenvoy/extensions/filters/network/thrift_proxy/filters/header_to_metadata/v3/header_to_metadata.proto\x12Kenvoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3\x1a!envoy/type/matcher/v3/regex.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xdb\x07\n\x10HeaderToMetadata\x12\x83\x01\n\rrequest_rules\x18\x01 \x03(\x0b\x32\x62.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.HeaderToMetadata.RuleB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\xaa\x03\n\x0cKeyValuePair\x12\x1a\n\x12metadata_namespace\x18\x01 \x01(\t\x12\x14\n\x03key\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x0f\n\x05value\x18\x03 \x01(\tH\x00\x12M\n\x13regex_value_rewrite\x18\x04 \x01(\x0b\x32..envoy.type.matcher.v3.RegexMatchAndSubstituteH\x00\x12\x7f\n\x04type\x18\x05 \x01(\x0e\x32g.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.HeaderToMetadata.ValueTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12y\n\x06\x65ncode\x18\x06 \x01(\x0e\x32i.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.HeaderToMetadata.ValueEncodeB\x0c\n\nvalue_type\x1a\xb5\x02\n\x04Rule\x12\x1d\n\x06header\x18\x01 \x01(\tB\r\xfa\x42\nr\x08\x10\x01\xc0\x01\x01\xc8\x01\x00\x12~\n\non_present\x18\x02 \x01(\x0b\x32j.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.HeaderToMetadata.KeyValuePair\x12~\n\non_missing\x18\x03 \x01(\x0b\x32j.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.HeaderToMetadata.KeyValuePair\x12\x0e\n\x06remove\x18\x04 \x01(\x08\"7\n\tValueType\x12\n\n\x06STRING\x10\x00\x12\n\n\x06NUMBER\x10\x01\x12\x12\n\x0ePROTOBUF_VALUE\x10\x02\"#\n\x0bValueEncode\x12\x08\n\x04NONE\x10\x00\x12\n\n\x06\x42\x41SE64\x10\x01\x42\x86\x02\nYio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3B\x15HeaderToMetadataProtoP\x01Z\x87\x01github.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/filters/header_to_metadata/v3;header_to_metadatav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3.header_to_metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nYio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.filters.header_to_metadata.v3B\025HeaderToMetadataProtoP\001Z\207\001github.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/filters/header_to_metadata/v3;header_to_metadatav3\272\200\310\321\006\002\020\002'
  _HEADERTOMETADATA_KEYVALUEPAIR.fields_by_name['key']._options = None
  _HEADERTOMETADATA_KEYVALUEPAIR.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _HEADERTOMETADATA_KEYVALUEPAIR.fields_by_name['type']._options = None
  _HEADERTOMETADATA_KEYVALUEPAIR.fields_by_name['type']._serialized_options = b'\372B\005\202\001\002\020\001'
  _HEADERTOMETADATA_RULE.fields_by_name['header']._options = None
  _HEADERTOMETADATA_RULE.fields_by_name['header']._serialized_options = b'\372B\nr\010\020\001\300\001\001\310\001\000'
  _HEADERTOMETADATA.fields_by_name['request_rules']._options = None
  _HEADERTOMETADATA.fields_by_name['request_rules']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_HEADERTOMETADATA']._serialized_start=273
  _globals['_HEADERTOMETADATA']._serialized_end=1260
  _globals['_HEADERTOMETADATA_KEYVALUEPAIR']._serialized_start=428
  _globals['_HEADERTOMETADATA_KEYVALUEPAIR']._serialized_end=854
  _globals['_HEADERTOMETADATA_RULE']._serialized_start=857
  _globals['_HEADERTOMETADATA_RULE']._serialized_end=1166
  _globals['_HEADERTOMETADATA_VALUETYPE']._serialized_start=1168
  _globals['_HEADERTOMETADATA_VALUETYPE']._serialized_end=1223
  _globals['_HEADERTOMETADATA_VALUEENCODE']._serialized_start=1225
  _globals['_HEADERTOMETADATA_VALUEENCODE']._serialized_end=1260
