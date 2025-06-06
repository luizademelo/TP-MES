
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api.apikeys.v2 import resources_pb2 as google_dot_api_dot_apikeys_dot_v2_dot_resources__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.longrunning import operations_pb2 as google_dot_longrunning_dot_operations__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.protobuf import field_mask_pb2 as google_dot_protobuf_dot_field__mask__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#google/api/apikeys/v2/apikeys.proto\x12\x15google.api.apikeys.v2\x1a\x1cgoogle/api/annotations.proto\x1a%google/api/apikeys/v2/resources.proto\x1a\x17google/api/client.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a\x19google/api/resource.proto\x1a#google/longrunning/operations.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a google/protobuf/field_mask.proto\"\x84\x01\n\x10\x43reateKeyRequest\x12\x32\n\x06parent\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\x12\x1a\x61pikeys.googleapis.com/Key\x12,\n\x03key\x18\x02 \x01(\x0b\x32\x1a.google.api.apikeys.v2.KeyB\x03\xe0\x41\x02\x12\x0e\n\x06key_id\x18\x03 \x01(\t\"\x91\x01\n\x0fListKeysRequest\x12\x32\n\x06parent\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\x12\x1a\x61pikeys.googleapis.com/Key\x12\x16\n\tpage_size\x18\x02 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x03 \x01(\tB\x03\xe0\x41\x01\x12\x19\n\x0cshow_deleted\x18\x06 \x01(\x08\x42\x03\xe0\x41\x01\"U\n\x10ListKeysResponse\x12(\n\x04keys\x18\x01 \x03(\x0b\x32\x1a.google.api.apikeys.v2.Key\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"A\n\rGetKeyRequest\x12\x30\n\x04name\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\n\x1a\x61pikeys.googleapis.com/Key\"G\n\x13GetKeyStringRequest\x12\x30\n\x04name\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\n\x1a\x61pikeys.googleapis.com/Key\"*\n\x14GetKeyStringResponse\x12\x12\n\nkey_string\x18\x01 \x01(\t\"q\n\x10UpdateKeyRequest\x12,\n\x03key\x18\x01 \x01(\x0b\x32\x1a.google.api.apikeys.v2.KeyB\x03\xe0\x41\x02\x12/\n\x0bupdate_mask\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.FieldMask\"W\n\x10\x44\x65leteKeyRequest\x12\x30\n\x04name\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\n\x1a\x61pikeys.googleapis.com/Key\x12\x11\n\x04\x65tag\x18\x02 \x01(\tB\x03\xe0\x41\x01\"F\n\x12UndeleteKeyRequest\x12\x30\n\x04name\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\n\x1a\x61pikeys.googleapis.com/Key\"+\n\x10LookupKeyRequest\x12\x17\n\nkey_string\x18\x01 \x01(\tB\x03\xe0\x41\x02\"1\n\x11LookupKeyResponse\x12\x0e\n\x06parent\x18\x01 \x01(\t\x12\x0c\n\x04name\x18\x02 \x01(\t2\xbe\x0b\n\x07\x41piKeys\x12\xbd\x01\n\tCreateKey\x12\'.google.api.apikeys.v2.CreateKeyRequest\x1a\x1d.google.longrunning.Operation\"h\xca\x41\x1c\n\x03Key\x12\x15google.protobuf.Empty\xda\x41\x11parent,key,key_id\x82\xd3\xe4\x93\x02/\"(/v2/{parent=projects/*/locations/*}/keys:\x03key\x12\x96\x01\n\x08ListKeys\x12&.google.api.apikeys.v2.ListKeysRequest\x1a\'.google.api.apikeys.v2.ListKeysResponse\"9\xda\x41\x06parent\x82\xd3\xe4\x93\x02*\x12(/v2/{parent=projects/*/locations/*}/keys\x12\x83\x01\n\x06GetKey\x12$.google.api.apikeys.v2.GetKeyRequest\x1a\x1a.google.api.apikeys.v2.Key\"7\xda\x41\x04name\x82\xd3\xe4\x93\x02*\x12(/v2/{name=projects/*/locations/*/keys/*}\x12\xaa\x01\n\x0cGetKeyString\x12*.google.api.apikeys.v2.GetKeyStringRequest\x1a+.google.api.apikeys.v2.GetKeyStringResponse\"A\xda\x41\x04name\x82\xd3\xe4\x93\x02\x34\x12\x32/v2/{name=projects/*/locations/*/keys/*}/keyString\x12\xbf\x01\n\tUpdateKey\x12\'.google.api.apikeys.v2.UpdateKeyRequest\x1a\x1d.google.longrunning.Operation\"j\xca\x41\x1c\n\x03Key\x12\x15google.protobuf.Empty\xda\x41\x0fkey,update_mask\x82\xd3\xe4\x93\x02\x33\x32,/v2/{key.name=projects/*/locations/*/keys/*}:\x03key\x12\xab\x01\n\tDeleteKey\x12\'.google.api.apikeys.v2.DeleteKeyRequest\x1a\x1d.google.longrunning.Operation\"V\xca\x41\x1c\n\x03Key\x12\x15google.protobuf.Empty\xda\x41\x04name\x82\xd3\xe4\x93\x02**(/v2/{name=projects/*/locations/*/keys/*}\x12\xb4\x01\n\x0bUndeleteKey\x12).google.api.apikeys.v2.UndeleteKeyRequest\x1a\x1d.google.longrunning.Operation\"[\xca\x41\x1c\n\x03Key\x12\x15google.protobuf.Empty\x82\xd3\xe4\x93\x02\x36\"1/v2/{name=projects/*/locations/*/keys/*}:undelete:\x01*\x12z\n\tLookupKey\x12\'.google.api.apikeys.v2.LookupKeyRequest\x1a(.google.api.apikeys.v2.LookupKeyResponse\"\x1a\x82\xd3\xe4\x93\x02\x14\x12\x12/v2/keys:lookupKey\x1a\x83\x01\xca\x41\x16\x61pikeys.googleapis.com\xd2\x41ghttps://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-onlyB\xb3\x01\n\x19\x63om.google.api.apikeys.v2B\x0c\x41piKeysProtoP\x01Z5cloud.google.com/go/apikeys/apiv2/apikeyspb;apikeyspb\xaa\x02\x17Google.Cloud.ApiKeys.V2\xca\x02\x17Google\\Cloud\\ApiKeys\\V2\xea\x02\x1aGoogle::Cloud::ApiKeys::V2b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.apikeys.v2.apikeys_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\031com.google.api.apikeys.v2B\014ApiKeysProtoP\001Z5cloud.google.com/go/apikeys/apiv2/apikeyspb;apikeyspb\252\002\027Google.Cloud.ApiKeys.V2\312\002\027Google\\Cloud\\ApiKeys\\V2\352\002\032Google::Cloud::ApiKeys::V2'
  _CREATEKEYREQUEST.fields_by_name['parent']._options = None
  _CREATEKEYREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\034\022\032apikeys.googleapis.com/Key'
  _CREATEKEYREQUEST.fields_by_name['key']._options = None
  _CREATEKEYREQUEST.fields_by_name['key']._serialized_options = b'\340A\002'
  _LISTKEYSREQUEST.fields_by_name['parent']._options = None
  _LISTKEYSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\034\022\032apikeys.googleapis.com/Key'
  _LISTKEYSREQUEST.fields_by_name['page_size']._options = None
  _LISTKEYSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTKEYSREQUEST.fields_by_name['page_token']._options = None
  _LISTKEYSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTKEYSREQUEST.fields_by_name['show_deleted']._options = None
  _LISTKEYSREQUEST.fields_by_name['show_deleted']._serialized_options = b'\340A\001'
  _GETKEYREQUEST.fields_by_name['name']._options = None
  _GETKEYREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\034\n\032apikeys.googleapis.com/Key'
  _GETKEYSTRINGREQUEST.fields_by_name['name']._options = None
  _GETKEYSTRINGREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\034\n\032apikeys.googleapis.com/Key'
  _UPDATEKEYREQUEST.fields_by_name['key']._options = None
  _UPDATEKEYREQUEST.fields_by_name['key']._serialized_options = b'\340A\002'
  _DELETEKEYREQUEST.fields_by_name['name']._options = None
  _DELETEKEYREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\034\n\032apikeys.googleapis.com/Key'
  _DELETEKEYREQUEST.fields_by_name['etag']._options = None
  _DELETEKEYREQUEST.fields_by_name['etag']._serialized_options = b'\340A\001'
  _UNDELETEKEYREQUEST.fields_by_name['name']._options = None
  _UNDELETEKEYREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\034\n\032apikeys.googleapis.com/Key'
  _LOOKUPKEYREQUEST.fields_by_name['key_string']._options = None
  _LOOKUPKEYREQUEST.fields_by_name['key_string']._serialized_options = b'\340A\002'
  _APIKEYS._options = None
  _APIKEYS._serialized_options = b'\312A\026apikeys.googleapis.com\322Aghttps://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only'
  _APIKEYS.methods_by_name['CreateKey']._options = None
  _APIKEYS.methods_by_name['CreateKey']._serialized_options = b'\312A\034\n\003Key\022\025google.protobuf.Empty\332A\021parent,key,key_id\202\323\344\223\002/\"(/v2/{parent=projects/*/locations/*}/keys:\003key'
  _APIKEYS.methods_by_name['ListKeys']._options = None
  _APIKEYS.methods_by_name['ListKeys']._serialized_options = b'\332A\006parent\202\323\344\223\002*\022(/v2/{parent=projects/*/locations/*}/keys'
  _APIKEYS.methods_by_name['GetKey']._options = None
  _APIKEYS.methods_by_name['GetKey']._serialized_options = b'\332A\004name\202\323\344\223\002*\022(/v2/{name=projects/*/locations/*/keys/*}'
  _APIKEYS.methods_by_name['GetKeyString']._options = None
  _APIKEYS.methods_by_name['GetKeyString']._serialized_options = b'\332A\004name\202\323\344\223\0024\0222/v2/{name=projects/*/locations/*/keys/*}/keyString'
  _APIKEYS.methods_by_name['UpdateKey']._options = None
  _APIKEYS.methods_by_name['UpdateKey']._serialized_options = b'\312A\034\n\003Key\022\025google.protobuf.Empty\332A\017key,update_mask\202\323\344\223\00232,/v2/{key.name=projects/*/locations/*/keys/*}:\003key'
  _APIKEYS.methods_by_name['DeleteKey']._options = None
  _APIKEYS.methods_by_name['DeleteKey']._serialized_options = b'\312A\034\n\003Key\022\025google.protobuf.Empty\332A\004name\202\323\344\223\002**(/v2/{name=projects/*/locations/*/keys/*}'
  _APIKEYS.methods_by_name['UndeleteKey']._options = None
  _APIKEYS.methods_by_name['UndeleteKey']._serialized_options = b'\312A\034\n\003Key\022\025google.protobuf.Empty\202\323\344\223\0026\"1/v2/{name=projects/*/locations/*/keys/*}:undelete:\001*'
  _APIKEYS.methods_by_name['LookupKey']._options = None
  _APIKEYS.methods_by_name['LookupKey']._serialized_options = b'\202\323\344\223\002\024\022\022/v2/keys:lookupKey'
  _globals['_CREATEKEYREQUEST']._serialized_start=317
  _globals['_CREATEKEYREQUEST']._serialized_end=449
  _globals['_LISTKEYSREQUEST']._serialized_start=452
  _globals['_LISTKEYSREQUEST']._serialized_end=597
  _globals['_LISTKEYSRESPONSE']._serialized_start=599
  _globals['_LISTKEYSRESPONSE']._serialized_end=684
  _globals['_GETKEYREQUEST']._serialized_start=686
  _globals['_GETKEYREQUEST']._serialized_end=751
  _globals['_GETKEYSTRINGREQUEST']._serialized_start=753
  _globals['_GETKEYSTRINGREQUEST']._serialized_end=824
  _globals['_GETKEYSTRINGRESPONSE']._serialized_start=826
  _globals['_GETKEYSTRINGRESPONSE']._serialized_end=868
  _globals['_UPDATEKEYREQUEST']._serialized_start=870
  _globals['_UPDATEKEYREQUEST']._serialized_end=983
  _globals['_DELETEKEYREQUEST']._serialized_start=985
  _globals['_DELETEKEYREQUEST']._serialized_end=1072
  _globals['_UNDELETEKEYREQUEST']._serialized_start=1074
  _globals['_UNDELETEKEYREQUEST']._serialized_end=1144
  _globals['_LOOKUPKEYREQUEST']._serialized_start=1146
  _globals['_LOOKUPKEYREQUEST']._serialized_end=1189
  _globals['_LOOKUPKEYRESPONSE']._serialized_start=1191
  _globals['_LOOKUPKEYRESPONSE']._serialized_end=1240
  _globals['_APIKEYS']._serialized_start=1243
  _globals['_APIKEYS']._serialized_end=2713
