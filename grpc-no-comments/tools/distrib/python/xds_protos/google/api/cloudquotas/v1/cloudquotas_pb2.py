
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api.cloudquotas.v1 import resources_pb2 as google_dot_api_dot_cloudquotas_dot_v1_dot_resources__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.protobuf import field_mask_pb2 as google_dot_protobuf_dot_field__mask__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+google/api/cloudquotas/v1/cloudquotas.proto\x12\x19google.api.cloudquotas.v1\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a)google/api/cloudquotas/v1/resources.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a\x19google/api/resource.proto\x1a google/protobuf/field_mask.proto\"\x86\x01\n\x15ListQuotaInfosRequest\x12<\n\x06parent\x18\x01 \x01(\tB,\xe0\x41\x02\xfa\x41&\x12$cloudquotas.googleapis.com/QuotaInfo\x12\x16\n\tpage_size\x18\x02 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x03 \x01(\tB\x03\xe0\x41\x01\"l\n\x16ListQuotaInfosResponse\x12\x39\n\x0bquota_infos\x18\x01 \x03(\x0b\x32$.google.api.cloudquotas.v1.QuotaInfo\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"Q\n\x13GetQuotaInfoRequest\x12:\n\x04name\x18\x01 \x01(\tB,\xe0\x41\x02\xfa\x41&\n$cloudquotas.googleapis.com/QuotaInfo\"\xbe\x01\n\x1bListQuotaPreferencesRequest\x12\x42\n\x06parent\x18\x01 \x01(\tB2\xe0\x41\x02\xfa\x41,\x12*cloudquotas.googleapis.com/QuotaPreference\x12\x16\n\tpage_size\x18\x02 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x03 \x01(\tB\x03\xe0\x41\x01\x12\x13\n\x06\x66ilter\x18\x04 \x01(\tB\x03\xe0\x41\x01\x12\x15\n\x08order_by\x18\x05 \x01(\tB\x03\xe0\x41\x01\"\x93\x01\n\x1cListQuotaPreferencesResponse\x12\x45\n\x11quota_preferences\x18\x01 \x03(\x0b\x32*.google.api.cloudquotas.v1.QuotaPreference\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\x12\x13\n\x0bunreachable\x18\x03 \x03(\t\"]\n\x19GetQuotaPreferenceRequest\x12@\n\x04name\x18\x01 \x01(\tB2\xe0\x41\x02\xfa\x41,\n*cloudquotas.googleapis.com/QuotaPreference\"\x9a\x02\n\x1c\x43reateQuotaPreferenceRequest\x12\x42\n\x06parent\x18\x01 \x01(\tB2\xe0\x41\x02\xfa\x41,\x12*cloudquotas.googleapis.com/QuotaPreference\x12 \n\x13quota_preference_id\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12I\n\x10quota_preference\x18\x03 \x01(\x0b\x32*.google.api.cloudquotas.v1.QuotaPreferenceB\x03\xe0\x41\x02\x12I\n\x14ignore_safety_checks\x18\x04 \x03(\x0e\x32+.google.api.cloudquotas.v1.QuotaSafetyCheck\"\xa2\x02\n\x1cUpdateQuotaPreferenceRequest\x12\x34\n\x0bupdate_mask\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x01\x12I\n\x10quota_preference\x18\x02 \x01(\x0b\x32*.google.api.cloudquotas.v1.QuotaPreferenceB\x03\xe0\x41\x02\x12\x1a\n\rallow_missing\x18\x03 \x01(\x08\x42\x03\xe0\x41\x01\x12\x1a\n\rvalidate_only\x18\x04 \x01(\x08\x42\x03\xe0\x41\x01\x12I\n\x14ignore_safety_checks\x18\x05 \x03(\x0e\x32+.google.api.cloudquotas.v1.QuotaSafetyCheck2\xb9\x11\n\x0b\x43loudQuotas\x12\xc1\x02\n\x0eListQuotaInfos\x12\x30.google.api.cloudquotas.v1.ListQuotaInfosRequest\x1a\x31.google.api.cloudquotas.v1.ListQuotaInfosResponse\"\xc9\x01\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xb9\x01\x12\x39/v1/{parent=projects/*/locations/*/services/*}/quotaInfosZ@\x12>/v1/{parent=organizations/*/locations/*/services/*}/quotaInfosZ:\x12\x38/v1/{parent=folders/*/locations/*/services/*}/quotaInfos\x12\xae\x02\n\x0cGetQuotaInfo\x12..google.api.cloudquotas.v1.GetQuotaInfoRequest\x1a$.google.api.cloudquotas.v1.QuotaInfo\"\xc7\x01\xda\x41\x04name\x82\xd3\xe4\x93\x02\xb9\x01\x12\x39/v1/{name=projects/*/locations/*/services/*/quotaInfos/*}Z@\x12>/v1/{name=organizations/*/locations/*/services/*/quotaInfos/*}Z:\x12\x38/v1/{name=folders/*/locations/*/services/*/quotaInfos/*}\x12\xc4\x02\n\x14ListQuotaPreferences\x12\x36.google.api.cloudquotas.v1.ListQuotaPreferencesRequest\x1a\x37.google.api.cloudquotas.v1.ListQuotaPreferencesResponse\"\xba\x01\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xaa\x01\x12\x34/v1/{parent=projects/*/locations/*}/quotaPreferencesZ5\x12\x33/v1/{parent=folders/*/locations/*}/quotaPreferencesZ;\x12\x39/v1/{parent=organizations/*/locations/*}/quotaPreferences\x12\xb1\x02\n\x12GetQuotaPreference\x12\x34.google.api.cloudquotas.v1.GetQuotaPreferenceRequest\x1a*.google.api.cloudquotas.v1.QuotaPreference\"\xb8\x01\xda\x41\x04name\x82\xd3\xe4\x93\x02\xaa\x01\x12\x34/v1/{name=projects/*/locations/*/quotaPreferences/*}Z;\x12\x39/v1/{name=organizations/*/locations/*/quotaPreferences/*}Z5\x12\x33/v1/{name=folders/*/locations/*/quotaPreferences/*}\x12\xae\x03\n\x15\x43reateQuotaPreference\x12\x37.google.api.cloudquotas.v1.CreateQuotaPreferenceRequest\x1a*.google.api.cloudquotas.v1.QuotaPreference\"\xaf\x02\xda\x41+parent,quota_preference,quota_preference_id\xda\x41\x17parent,quota_preference\x82\xd3\xe4\x93\x02\xe0\x01\"4/v1/{parent=projects/*/locations/*}/quotaPreferences:\x10quota_preferenceZG\"3/v1/{parent=folders/*/locations/*}/quotaPreferences:\x10quota_preferenceZM\"9/v1/{parent=organizations/*/locations/*}/quotaPreferences:\x10quota_preference\x12\xb8\x03\n\x15UpdateQuotaPreference\x12\x37.google.api.cloudquotas.v1.UpdateQuotaPreferenceRequest\x1a*.google.api.cloudquotas.v1.QuotaPreference\"\xb9\x02\xda\x41\x1cquota_preference,update_mask\x82\xd3\xe4\x93\x02\x93\x02\x32\x45/v1/{quota_preference.name=projects/*/locations/*/quotaPreferences/*}:\x10quota_preferenceZX2D/v1/{quota_preference.name=folders/*/locations/*/quotaPreferences/*}:\x10quota_preferenceZ^2J/v1/{quota_preference.name=organizations/*/locations/*/quotaPreferences/*}:\x10quota_preference\x1aN\xca\x41\x1a\x63loudquotas.googleapis.com\xd2\x41.https://www.googleapis.com/auth/cloud-platformB\xe3\x04\n\x1d\x63om.google.api.cloudquotas.v1B\x10\x43loudquotasProtoP\x01ZAcloud.google.com/go/cloudquotas/apiv1/cloudquotaspb;cloudquotaspb\xaa\x02\x1bGoogle.Cloud.CloudQuotas.V1\xca\x02\x1bGoogle\\Cloud\\CloudQuotas\\V1\xea\x02\x1eGoogle::Cloud::CloudQuotas::V1\xea\x41\xe0\x01\n\"cloudquotas.googleapis.com/Service\x12:projects/{project}/locations/{location}/services/{service}\x12\x38\x66olders/{folder}/locations/{location}/services/{service}\x12\x44organizations/{organization}/locations/{location}/services/{service}\xea\x41\xa8\x01\n#cloudquotas.googleapis.com/Location\x12\'projects/{project}/locations/{location}\x12%folders/{folder}/locations/{location}\x12\x31organizations/{organization}/locations/{location}b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.cloudquotas.v1.cloudquotas_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\035com.google.api.cloudquotas.v1B\020CloudquotasProtoP\001ZAcloud.google.com/go/cloudquotas/apiv1/cloudquotaspb;cloudquotaspb\252\002\033Google.Cloud.CloudQuotas.V1\312\002\033Google\\Cloud\\CloudQuotas\\V1\352\002\036Google::Cloud::CloudQuotas::V1\352A\340\001\n\"cloudquotas.googleapis.com/Service\022:projects/{project}/locations/{location}/services/{service}\0228folders/{folder}/locations/{location}/services/{service}\022Dorganizations/{organization}/locations/{location}/services/{service}\352A\250\001\n#cloudquotas.googleapis.com/Location\022\'projects/{project}/locations/{location}\022%folders/{folder}/locations/{location}\0221organizations/{organization}/locations/{location}'
  _LISTQUOTAINFOSREQUEST.fields_by_name['parent']._options = None
  _LISTQUOTAINFOSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A&\022$cloudquotas.googleapis.com/QuotaInfo'
  _LISTQUOTAINFOSREQUEST.fields_by_name['page_size']._options = None
  _LISTQUOTAINFOSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTQUOTAINFOSREQUEST.fields_by_name['page_token']._options = None
  _LISTQUOTAINFOSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _GETQUOTAINFOREQUEST.fields_by_name['name']._options = None
  _GETQUOTAINFOREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A&\n$cloudquotas.googleapis.com/QuotaInfo'
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['parent']._options = None
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A,\022*cloudquotas.googleapis.com/QuotaPreference'
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['page_size']._options = None
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['page_token']._options = None
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['filter']._options = None
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['filter']._serialized_options = b'\340A\001'
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['order_by']._options = None
  _LISTQUOTAPREFERENCESREQUEST.fields_by_name['order_by']._serialized_options = b'\340A\001'
  _GETQUOTAPREFERENCEREQUEST.fields_by_name['name']._options = None
  _GETQUOTAPREFERENCEREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A,\n*cloudquotas.googleapis.com/QuotaPreference'
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['parent']._options = None
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A,\022*cloudquotas.googleapis.com/QuotaPreference'
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference_id']._options = None
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference_id']._serialized_options = b'\340A\001'
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference']._options = None
  _CREATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference']._serialized_options = b'\340A\002'
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['update_mask']._options = None
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\001'
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference']._options = None
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['quota_preference']._serialized_options = b'\340A\002'
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['allow_missing']._options = None
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['allow_missing']._serialized_options = b'\340A\001'
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['validate_only']._options = None
  _UPDATEQUOTAPREFERENCEREQUEST.fields_by_name['validate_only']._serialized_options = b'\340A\001'
  _CLOUDQUOTAS._options = None
  _CLOUDQUOTAS._serialized_options = b'\312A\032cloudquotas.googleapis.com\322A.https://www.googleapis.com/auth/cloud-platform'
  _CLOUDQUOTAS.methods_by_name['ListQuotaInfos']._options = None
  _CLOUDQUOTAS.methods_by_name['ListQuotaInfos']._serialized_options = b'\332A\006parent\202\323\344\223\002\271\001\0229/v1/{parent=projects/*/locations/*/services/*}/quotaInfosZ@\022>/v1/{parent=organizations/*/locations/*/services/*}/quotaInfosZ:\0228/v1/{parent=folders/*/locations/*/services/*}/quotaInfos'
  _CLOUDQUOTAS.methods_by_name['GetQuotaInfo']._options = None
  _CLOUDQUOTAS.methods_by_name['GetQuotaInfo']._serialized_options = b'\332A\004name\202\323\344\223\002\271\001\0229/v1/{name=projects/*/locations/*/services/*/quotaInfos/*}Z@\022>/v1/{name=organizations/*/locations/*/services/*/quotaInfos/*}Z:\0228/v1/{name=folders/*/locations/*/services/*/quotaInfos/*}'
  _CLOUDQUOTAS.methods_by_name['ListQuotaPreferences']._options = None
  _CLOUDQUOTAS.methods_by_name['ListQuotaPreferences']._serialized_options = b'\332A\006parent\202\323\344\223\002\252\001\0224/v1/{parent=projects/*/locations/*}/quotaPreferencesZ5\0223/v1/{parent=folders/*/locations/*}/quotaPreferencesZ;\0229/v1/{parent=organizations/*/locations/*}/quotaPreferences'
  _CLOUDQUOTAS.methods_by_name['GetQuotaPreference']._options = None
  _CLOUDQUOTAS.methods_by_name['GetQuotaPreference']._serialized_options = b'\332A\004name\202\323\344\223\002\252\001\0224/v1/{name=projects/*/locations/*/quotaPreferences/*}Z;\0229/v1/{name=organizations/*/locations/*/quotaPreferences/*}Z5\0223/v1/{name=folders/*/locations/*/quotaPreferences/*}'
  _CLOUDQUOTAS.methods_by_name['CreateQuotaPreference']._options = None
  _CLOUDQUOTAS.methods_by_name['CreateQuotaPreference']._serialized_options = b'\332A+parent,quota_preference,quota_preference_id\332A\027parent,quota_preference\202\323\344\223\002\340\001\"4/v1/{parent=projects/*/locations/*}/quotaPreferences:\020quota_preferenceZG\"3/v1/{parent=folders/*/locations/*}/quotaPreferences:\020quota_preferenceZM\"9/v1/{parent=organizations/*/locations/*}/quotaPreferences:\020quota_preference'
  _CLOUDQUOTAS.methods_by_name['UpdateQuotaPreference']._options = None
  _CLOUDQUOTAS.methods_by_name['UpdateQuotaPreference']._serialized_options = b'\332A\034quota_preference,update_mask\202\323\344\223\002\223\0022E/v1/{quota_preference.name=projects/*/locations/*/quotaPreferences/*}:\020quota_preferenceZX2D/v1/{quota_preference.name=folders/*/locations/*/quotaPreferences/*}:\020quota_preferenceZ^2J/v1/{quota_preference.name=organizations/*/locations/*/quotaPreferences/*}:\020quota_preference'
  _globals['_LISTQUOTAINFOSREQUEST']._serialized_start=267
  _globals['_LISTQUOTAINFOSREQUEST']._serialized_end=401
  _globals['_LISTQUOTAINFOSRESPONSE']._serialized_start=403
  _globals['_LISTQUOTAINFOSRESPONSE']._serialized_end=511
  _globals['_GETQUOTAINFOREQUEST']._serialized_start=513
  _globals['_GETQUOTAINFOREQUEST']._serialized_end=594
  _globals['_LISTQUOTAPREFERENCESREQUEST']._serialized_start=597
  _globals['_LISTQUOTAPREFERENCESREQUEST']._serialized_end=787
  _globals['_LISTQUOTAPREFERENCESRESPONSE']._serialized_start=790
  _globals['_LISTQUOTAPREFERENCESRESPONSE']._serialized_end=937
  _globals['_GETQUOTAPREFERENCEREQUEST']._serialized_start=939
  _globals['_GETQUOTAPREFERENCEREQUEST']._serialized_end=1032
  _globals['_CREATEQUOTAPREFERENCEREQUEST']._serialized_start=1035
  _globals['_CREATEQUOTAPREFERENCEREQUEST']._serialized_end=1317
  _globals['_UPDATEQUOTAPREFERENCEREQUEST']._serialized_start=1320
  _globals['_UPDATEQUOTAPREFERENCEREQUEST']._serialized_end=1610
  _globals['_CLOUDQUOTAS']._serialized_start=1613
  _globals['_CLOUDQUOTAS']._serialized_end=3846
