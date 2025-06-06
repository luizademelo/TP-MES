
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.longrunning import operations_pb2 as google_dot_longrunning_dot_operations__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.protobuf import field_mask_pb2 as google_dot_protobuf_dot_field__mask__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&google/logging/v2/logging_config.proto\x12\x11google.logging.v2\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a\x19google/api/resource.proto\x1a#google/longrunning/operations.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a google/protobuf/field_mask.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\x8d\x01\n\x0bIndexConfig\x12\x17\n\nfield_path\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12/\n\x04type\x18\x02 \x01(\x0e\x32\x1c.google.logging.v2.IndexTypeB\x03\xe0\x41\x02\x12\x34\n\x0b\x63reate_time\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\"\xd5\x05\n\tLogBucket\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x03\x12\x13\n\x0b\x64\x65scription\x18\x03 \x01(\t\x12\x34\n\x0b\x63reate_time\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x16\n\x0eretention_days\x18\x0b \x01(\x05\x12\x0e\n\x06locked\x18\t \x01(\x08\x12?\n\x0flifecycle_state\x18\x0c \x01(\x0e\x32!.google.logging.v2.LifecycleStateB\x03\xe0\x41\x03\x12\x19\n\x11\x61nalytics_enabled\x18\x0e \x01(\x08\x12\x19\n\x11restricted_fields\x18\x0f \x03(\t\x12\x35\n\rindex_configs\x18\x11 \x03(\x0b\x32\x1e.google.logging.v2.IndexConfig\x12\x36\n\rcmek_settings\x18\x13 \x01(\x0b\x32\x1f.google.logging.v2.CmekSettings:\xa5\x02\xea\x41\xa1\x02\n logging.googleapis.com/LogBucket\x12\x38projects/{project}/locations/{location}/buckets/{bucket}\x12\x42organizations/{organization}/locations/{location}/buckets/{bucket}\x12\x36\x66olders/{folder}/locations/{location}/buckets/{bucket}\x12GbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}\"\x82\x04\n\x07LogView\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x03 \x01(\t\x12\x34\n\x0b\x63reate_time\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x0e\n\x06\x66ilter\x18\x07 \x01(\t:\xd7\x02\xea\x41\xd3\x02\n\x1elogging.googleapis.com/LogView\x12\x45projects/{project}/locations/{location}/buckets/{bucket}/views/{view}\x12Oorganizations/{organization}/locations/{location}/buckets/{bucket}/views/{view}\x12\x43\x66olders/{folder}/locations/{location}/buckets/{bucket}/views/{view}\x12TbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}/views/{view}\"\x85\x06\n\x07LogSink\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x1e\n\x0b\x64\x65stination\x18\x03 \x01(\tB\t\xe0\x41\x02\xfa\x41\x03\n\x01*\x12\x13\n\x06\x66ilter\x18\x05 \x01(\tB\x03\xe0\x41\x01\x12\x18\n\x0b\x64\x65scription\x18\x12 \x01(\tB\x03\xe0\x41\x01\x12\x15\n\x08\x64isabled\x18\x13 \x01(\x08\x42\x03\xe0\x41\x01\x12\x38\n\nexclusions\x18\x10 \x03(\x0b\x32\x1f.google.logging.v2.LogExclusionB\x03\xe0\x41\x01\x12K\n\x15output_version_format\x18\x06 \x01(\x0e\x32(.google.logging.v2.LogSink.VersionFormatB\x02\x18\x01\x12\x1c\n\x0fwriter_identity\x18\x08 \x01(\tB\x03\xe0\x41\x03\x12\x1d\n\x10include_children\x18\t \x01(\x08\x42\x03\xe0\x41\x01\x12\x43\n\x10\x62igquery_options\x18\x0c \x01(\x0b\x32\".google.logging.v2.BigQueryOptionsB\x03\xe0\x41\x01H\x00\x12\x34\n\x0b\x63reate_time\x18\r \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\x0e \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\"?\n\rVersionFormat\x12\x1e\n\x1aVERSION_FORMAT_UNSPECIFIED\x10\x00\x12\x06\n\x02V2\x10\x01\x12\x06\n\x02V1\x10\x02:\xbf\x01\xea\x41\xbb\x01\n\x1elogging.googleapis.com/LogSink\x12\x1fprojects/{project}/sinks/{sink}\x12)organizations/{organization}/sinks/{sink}\x12\x1d\x66olders/{folder}/sinks/{sink}\x12.billingAccounts/{billing_account}/sinks/{sink}B\t\n\x07options\"*\n\x0f\x42igQueryDataset\x12\x17\n\ndataset_id\x18\x01 \x01(\tB\x03\xe0\x41\x03\"\xb5\x04\n\x04Link\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\x12\x34\n\x0b\x63reate_time\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12?\n\x0flifecycle_state\x18\x04 \x01(\x0e\x32!.google.logging.v2.LifecycleStateB\x03\xe0\x41\x03\x12<\n\x10\x62igquery_dataset\x18\x05 \x01(\x0b\x32\".google.logging.v2.BigQueryDataset:\xd4\x02\xea\x41\xd0\x02\n\x1blogging.googleapis.com/Link\x12\x45projects/{project}/locations/{location}/buckets/{bucket}/links/{link}\x12Oorganizations/{organization}/locations/{location}/buckets/{bucket}/links/{link}\x12\x43\x66olders/{folder}/locations/{location}/buckets/{bucket}/links/{link}\x12TbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}/links/{link}\"g\n\x0f\x42igQueryOptions\x12#\n\x16use_partitioned_tables\x18\x01 \x01(\x08\x42\x03\xe0\x41\x01\x12/\n\"uses_timestamp_column_partitioning\x18\x03 \x01(\x08\x42\x03\xe0\x41\x03\"\x7f\n\x12ListBucketsRequest\x12\x38\n\x06parent\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\x12 logging.googleapis.com/LogBucket\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"]\n\x13ListBucketsResponse\x12-\n\x07\x62uckets\x18\x01 \x03(\x0b\x32\x1c.google.logging.v2.LogBucket\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"\x9a\x01\n\x13\x43reateBucketRequest\x12\x38\n\x06parent\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\x12 logging.googleapis.com/LogBucket\x12\x16\n\tbucket_id\x18\x02 \x01(\tB\x03\xe0\x41\x02\x12\x31\n\x06\x62ucket\x18\x03 \x01(\x0b\x32\x1c.google.logging.v2.LogBucketB\x03\xe0\x41\x02\"\xb6\x01\n\x13UpdateBucketRequest\x12\x36\n\x04name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogBucket\x12\x31\n\x06\x62ucket\x18\x02 \x01(\x0b\x32\x1c.google.logging.v2.LogBucketB\x03\xe0\x41\x02\x12\x34\n\x0bupdate_mask\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x02\"J\n\x10GetBucketRequest\x12\x36\n\x04name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogBucket\"M\n\x13\x44\x65leteBucketRequest\x12\x36\n\x04name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogBucket\"O\n\x15UndeleteBucketRequest\x12\x36\n\x04name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogBucket\"X\n\x10ListViewsRequest\x12\x13\n\x06parent\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"W\n\x11ListViewsResponse\x12)\n\x05views\x18\x01 \x03(\x0b\x32\x1a.google.logging.v2.LogView\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"m\n\x11\x43reateViewRequest\x12\x13\n\x06parent\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x14\n\x07view_id\x18\x02 \x01(\tB\x03\xe0\x41\x02\x12-\n\x04view\x18\x03 \x01(\x0b\x32\x1a.google.logging.v2.LogViewB\x03\xe0\x41\x02\"\x8b\x01\n\x11UpdateViewRequest\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12-\n\x04view\x18\x02 \x01(\x0b\x32\x1a.google.logging.v2.LogViewB\x03\xe0\x41\x02\x12\x34\n\x0bupdate_mask\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x01\"F\n\x0eGetViewRequest\x12\x34\n\x04name\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \n\x1elogging.googleapis.com/LogView\"I\n\x11\x44\x65leteViewRequest\x12\x34\n\x04name\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \n\x1elogging.googleapis.com/LogView\"{\n\x10ListSinksRequest\x12\x36\n\x06parent\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \x12\x1elogging.googleapis.com/LogSink\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"W\n\x11ListSinksResponse\x12)\n\x05sinks\x18\x01 \x03(\x0b\x32\x1a.google.logging.v2.LogSink\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"K\n\x0eGetSinkRequest\x12\x39\n\tsink_name\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \n\x1elogging.googleapis.com/LogSink\"\x9f\x01\n\x11\x43reateSinkRequest\x12\x36\n\x06parent\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \x12\x1elogging.googleapis.com/LogSink\x12-\n\x04sink\x18\x02 \x01(\x0b\x32\x1a.google.logging.v2.LogSinkB\x03\xe0\x41\x02\x12#\n\x16unique_writer_identity\x18\x03 \x01(\x08\x42\x03\xe0\x41\x01\"\xd8\x01\n\x11UpdateSinkRequest\x12\x39\n\tsink_name\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \n\x1elogging.googleapis.com/LogSink\x12-\n\x04sink\x18\x02 \x01(\x0b\x32\x1a.google.logging.v2.LogSinkB\x03\xe0\x41\x02\x12#\n\x16unique_writer_identity\x18\x03 \x01(\x08\x42\x03\xe0\x41\x01\x12\x34\n\x0bupdate_mask\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x01\"N\n\x11\x44\x65leteSinkRequest\x12\x39\n\tsink_name\x18\x01 \x01(\tB&\xe0\x41\x02\xfa\x41 \n\x1elogging.googleapis.com/LogSink\"\x8a\x01\n\x11\x43reateLinkRequest\x12\x33\n\x06parent\x18\x01 \x01(\tB#\xe0\x41\x02\xfa\x41\x1d\x12\x1blogging.googleapis.com/Link\x12*\n\x04link\x18\x02 \x01(\x0b\x32\x17.google.logging.v2.LinkB\x03\xe0\x41\x02\x12\x14\n\x07link_id\x18\x03 \x01(\tB\x03\xe0\x41\x02\"F\n\x11\x44\x65leteLinkRequest\x12\x31\n\x04name\x18\x01 \x01(\tB#\xe0\x41\x02\xfa\x41\x1d\n\x1blogging.googleapis.com/Link\"x\n\x10ListLinksRequest\x12\x33\n\x06parent\x18\x01 \x01(\tB#\xe0\x41\x02\xfa\x41\x1d\x12\x1blogging.googleapis.com/Link\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"T\n\x11ListLinksResponse\x12&\n\x05links\x18\x01 \x03(\x0b\x32\x17.google.logging.v2.Link\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"C\n\x0eGetLinkRequest\x12\x31\n\x04name\x18\x01 \x01(\tB#\xe0\x41\x02\xfa\x41\x1d\n\x1blogging.googleapis.com/Link\"\xc2\x03\n\x0cLogExclusion\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x18\n\x0b\x64\x65scription\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x13\n\x06\x66ilter\x18\x03 \x01(\tB\x03\xe0\x41\x02\x12\x15\n\x08\x64isabled\x18\x04 \x01(\x08\x42\x03\xe0\x41\x01\x12\x34\n\x0b\x63reate_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\x06 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03:\xec\x01\xea\x41\xe8\x01\n#logging.googleapis.com/LogExclusion\x12)projects/{project}/exclusions/{exclusion}\x12\x33organizations/{organization}/exclusions/{exclusion}\x12\'folders/{folder}/exclusions/{exclusion}\x12\x38\x62illingAccounts/{billing_account}/exclusions/{exclusion}\"\x85\x01\n\x15ListExclusionsRequest\x12;\n\x06parent\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\x12#logging.googleapis.com/LogExclusion\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"f\n\x16ListExclusionsResponse\x12\x33\n\nexclusions\x18\x01 \x03(\x0b\x32\x1f.google.logging.v2.LogExclusion\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"P\n\x13GetExclusionRequest\x12\x39\n\x04name\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\n#logging.googleapis.com/LogExclusion\"\x8e\x01\n\x16\x43reateExclusionRequest\x12;\n\x06parent\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\x12#logging.googleapis.com/LogExclusion\x12\x37\n\texclusion\x18\x02 \x01(\x0b\x32\x1f.google.logging.v2.LogExclusionB\x03\xe0\x41\x02\"\xc2\x01\n\x16UpdateExclusionRequest\x12\x39\n\x04name\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\n#logging.googleapis.com/LogExclusion\x12\x37\n\texclusion\x18\x02 \x01(\x0b\x32\x1f.google.logging.v2.LogExclusionB\x03\xe0\x41\x02\x12\x34\n\x0bupdate_mask\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x02\"S\n\x16\x44\x65leteExclusionRequest\x12\x39\n\x04name\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\n#logging.googleapis.com/LogExclusion\"S\n\x16GetCmekSettingsRequest\x12\x39\n\x04name\x18\x01 \x01(\tB+\xe0\x41\x02\xfa\x41%\n#logging.googleapis.com/CmekSettings\"\xa1\x01\n\x19UpdateCmekSettingsRequest\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12;\n\rcmek_settings\x18\x02 \x01(\x0b\x32\x1f.google.logging.v2.CmekSettingsB\x03\xe0\x41\x02\x12\x34\n\x0bupdate_mask\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x01\"\xbd\x02\n\x0c\x43mekSettings\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x03\x12\x14\n\x0ckms_key_name\x18\x02 \x01(\t\x12\x1c\n\x14kms_key_version_name\x18\x04 \x01(\t\x12\x1f\n\x12service_account_id\x18\x03 \x01(\tB\x03\xe0\x41\x03:\xc4\x01\xea\x41\xc0\x01\n#logging.googleapis.com/CmekSettings\x12\x1fprojects/{project}/cmekSettings\x12)organizations/{organization}/cmekSettings\x12\x1d\x66olders/{folder}/cmekSettings\x12.billingAccounts/{billing_account}/cmekSettings\"K\n\x12GetSettingsRequest\x12\x35\n\x04name\x18\x01 \x01(\tB\'\xe0\x41\x02\xfa\x41!\n\x1flogging.googleapis.com/Settings\"\x94\x01\n\x15UpdateSettingsRequest\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x32\n\x08settings\x18\x02 \x01(\x0b\x32\x1b.google.logging.v2.SettingsB\x03\xe0\x41\x02\x12\x34\n\x0bupdate_mask\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.FieldMaskB\x03\xe0\x41\x01\"\xd2\x02\n\x08Settings\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x03\x12\x19\n\x0ckms_key_name\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12#\n\x16kms_service_account_id\x18\x03 \x01(\tB\x03\xe0\x41\x03\x12\x1d\n\x10storage_location\x18\x04 \x01(\tB\x03\xe0\x41\x01\x12!\n\x14\x64isable_default_sink\x18\x05 \x01(\x08\x42\x03\xe0\x41\x01:\xb0\x01\xea\x41\xac\x01\n\x1flogging.googleapis.com/Settings\x12\x1bprojects/{project}/settings\x12%organizations/{organization}/settings\x12\x19\x66olders/{folder}/settings\x12*billingAccounts/{billing_account}/settings\"Y\n\x15\x43opyLogEntriesRequest\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x13\n\x06\x66ilter\x18\x03 \x01(\tB\x03\xe0\x41\x01\x12\x18\n\x0b\x64\x65stination\x18\x04 \x01(\tB\x03\xe0\x41\x02\"\xae\x02\n\x16\x43opyLogEntriesMetadata\x12.\n\nstart_time\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12,\n\x08\x65nd_time\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x30\n\x05state\x18\x03 \x01(\x0e\x32!.google.logging.v2.OperationState\x12\x1e\n\x16\x63\x61ncellation_requested\x18\x04 \x01(\x08\x12\x39\n\x07request\x18\x05 \x01(\x0b\x32(.google.logging.v2.CopyLogEntriesRequest\x12\x10\n\x08progress\x18\x06 \x01(\x05\x12\x17\n\x0fwriter_identity\x18\x07 \x01(\t\":\n\x16\x43opyLogEntriesResponse\x12 \n\x18log_entries_copied_count\x18\x01 \x01(\x03\"\xbd\x02\n\x0e\x42ucketMetadata\x12.\n\nstart_time\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12,\n\x08\x65nd_time\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x30\n\x05state\x18\x03 \x01(\x0e\x32!.google.logging.v2.OperationState\x12G\n\x15\x63reate_bucket_request\x18\x04 \x01(\x0b\x32&.google.logging.v2.CreateBucketRequestH\x00\x12G\n\x15update_bucket_request\x18\x05 \x01(\x0b\x32&.google.logging.v2.UpdateBucketRequestH\x00\x42\t\n\x07request\"\xb3\x02\n\x0cLinkMetadata\x12.\n\nstart_time\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12,\n\x08\x65nd_time\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x30\n\x05state\x18\x03 \x01(\x0e\x32!.google.logging.v2.OperationState\x12\x43\n\x13\x63reate_link_request\x18\x04 \x01(\x0b\x32$.google.logging.v2.CreateLinkRequestH\x00\x12\x43\n\x13\x64\x65lete_link_request\x18\x05 \x01(\x0b\x32$.google.logging.v2.DeleteLinkRequestH\x00\x42\t\n\x07request\"1\n\x10LocationMetadata\x12\x1d\n\x15log_analytics_enabled\x18\x01 \x01(\x08*\xf4\x01\n\x0eOperationState\x12\x1f\n\x1bOPERATION_STATE_UNSPECIFIED\x10\x00\x12\x1d\n\x19OPERATION_STATE_SCHEDULED\x10\x01\x12+\n\'OPERATION_STATE_WAITING_FOR_PERMISSIONS\x10\x02\x12\x1b\n\x17OPERATION_STATE_RUNNING\x10\x03\x12\x1d\n\x19OPERATION_STATE_SUCCEEDED\x10\x04\x12\x1a\n\x16OPERATION_STATE_FAILED\x10\x05\x12\x1d\n\x19OPERATION_STATE_CANCELLED\x10\x06*{\n\x0eLifecycleState\x12\x1f\n\x1bLIFECYCLE_STATE_UNSPECIFIED\x10\x00\x12\n\n\x06\x41\x43TIVE\x10\x01\x12\x14\n\x10\x44\x45LETE_REQUESTED\x10\x02\x12\x0c\n\x08UPDATING\x10\x03\x12\x0c\n\x08\x43REATING\x10\x04\x12\n\n\x06\x46\x41ILED\x10\x05*V\n\tIndexType\x12\x1a\n\x16INDEX_TYPE_UNSPECIFIED\x10\x00\x12\x15\n\x11INDEX_TYPE_STRING\x10\x01\x12\x16\n\x12INDEX_TYPE_INTEGER\x10\x02\x32\x9fY\n\x0f\x43onfigServiceV2\x12\xdc\x02\n\x0bListBuckets\x12%.google.logging.v2.ListBucketsRequest\x1a&.google.logging.v2.ListBucketsResponse\"\xfd\x01\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xed\x01\x12$/v2/{parent=*/*/locations/*}/bucketsZ-\x12+/v2/{parent=projects/*/locations/*}/bucketsZ2\x12\x30/v2/{parent=organizations/*/locations/*}/bucketsZ,\x12*/v2/{parent=folders/*/locations/*}/bucketsZ4\x12\x32/v2/{parent=billingAccounts/*/locations/*}/buckets\x12\xc5\x02\n\tGetBucket\x12#.google.logging.v2.GetBucketRequest\x1a\x1c.google.logging.v2.LogBucket\"\xf4\x01\x82\xd3\xe4\x93\x02\xed\x01\x12$/v2/{name=*/*/locations/*/buckets/*}Z-\x12+/v2/{name=projects/*/locations/*/buckets/*}Z2\x12\x30/v2/{name=organizations/*/locations/*/buckets/*}Z,\x12*/v2/{name=folders/*/locations/*/buckets/*}Z4\x12\x32/v2/{name=billingAccounts/*/locations/*/buckets/*}\x12\xd3\x03\n\x11\x43reateBucketAsync\x12&.google.logging.v2.CreateBucketRequest\x1a\x1d.google.longrunning.Operation\"\xf6\x02\xca\x41\x1b\n\tLogBucket\x12\x0e\x42ucketMetadata\x82\xd3\xe4\x93\x02\xd1\x02\"0/v2/{parent=*/*/locations/*}/buckets:createAsync:\x06\x62ucketZA\"7/v2/{parent=projects/*/locations/*}/buckets:createAsync:\x06\x62ucketZF\"</v2/{parent=organizations/*/locations/*}/buckets:createAsync:\x06\x62ucketZ@\"6/v2/{parent=folders/*/locations/*}/buckets:createAsync:\x06\x62ucketZH\">/v2/{parent=billingAccounts/*/locations/*}/buckets:createAsync:\x06\x62ucket\x12\xd3\x03\n\x11UpdateBucketAsync\x12&.google.logging.v2.UpdateBucketRequest\x1a\x1d.google.longrunning.Operation\"\xf6\x02\xca\x41\x1b\n\tLogBucket\x12\x0e\x42ucketMetadata\x82\xd3\xe4\x93\x02\xd1\x02\"0/v2/{name=*/*/locations/*/buckets/*}:updateAsync:\x06\x62ucketZA\"7/v2/{name=projects/*/locations/*/buckets/*}:updateAsync:\x06\x62ucketZF\"</v2/{name=organizations/*/locations/*/buckets/*}:updateAsync:\x06\x62ucketZ@\"6/v2/{name=folders/*/locations/*/buckets/*}:updateAsync:\x06\x62ucketZH\">/v2/{name=billingAccounts/*/locations/*/buckets/*}:updateAsync:\x06\x62ucket\x12\xf3\x02\n\x0c\x43reateBucket\x12&.google.logging.v2.CreateBucketRequest\x1a\x1c.google.logging.v2.LogBucket\"\x9c\x02\x82\xd3\xe4\x93\x02\x95\x02\"$/v2/{parent=*/*/locations/*}/buckets:\x06\x62ucketZ5\"+/v2/{parent=projects/*/locations/*}/buckets:\x06\x62ucketZ:\"0/v2/{parent=organizations/*/locations/*}/buckets:\x06\x62ucketZ4\"*/v2/{parent=folders/*/locations/*}/buckets:\x06\x62ucketZ<\"2/v2/{parent=billingAccounts/*/locations/*}/buckets:\x06\x62ucket\x12\xf3\x02\n\x0cUpdateBucket\x12&.google.logging.v2.UpdateBucketRequest\x1a\x1c.google.logging.v2.LogBucket\"\x9c\x02\x82\xd3\xe4\x93\x02\x95\x02\x32$/v2/{name=*/*/locations/*/buckets/*}:\x06\x62ucketZ52+/v2/{name=projects/*/locations/*/buckets/*}:\x06\x62ucketZ:20/v2/{name=organizations/*/locations/*/buckets/*}:\x06\x62ucketZ42*/v2/{name=folders/*/locations/*/buckets/*}:\x06\x62ucketZ<22/v2/{name=billingAccounts/*/locations/*/buckets/*}:\x06\x62ucket\x12\xc5\x02\n\x0c\x44\x65leteBucket\x12&.google.logging.v2.DeleteBucketRequest\x1a\x16.google.protobuf.Empty\"\xf4\x01\x82\xd3\xe4\x93\x02\xed\x01*$/v2/{name=*/*/locations/*/buckets/*}Z-*+/v2/{name=projects/*/locations/*/buckets/*}Z2*0/v2/{name=organizations/*/locations/*/buckets/*}Z,**/v2/{name=folders/*/locations/*/buckets/*}Z4*2/v2/{name=billingAccounts/*/locations/*/buckets/*}\x12\x85\x03\n\x0eUndeleteBucket\x12(.google.logging.v2.UndeleteBucketRequest\x1a\x16.google.protobuf.Empty\"\xb0\x02\x82\xd3\xe4\x93\x02\xa9\x02\"-/v2/{name=*/*/locations/*/buckets/*}:undelete:\x01*Z9\"4/v2/{name=projects/*/locations/*/buckets/*}:undelete:\x01*Z>\"9/v2/{name=organizations/*/locations/*/buckets/*}:undelete:\x01*Z8\"3/v2/{name=folders/*/locations/*/buckets/*}:undelete:\x01*Z@\";/v2/{name=billingAccounts/*/locations/*/buckets/*}:undelete:\x01*\x12\xfe\x02\n\tListViews\x12#.google.logging.v2.ListViewsRequest\x1a$.google.logging.v2.ListViewsResponse\"\xa5\x02\xda\x41\x06parent\x82\xd3\xe4\x93\x02\x95\x02\x12,/v2/{parent=*/*/locations/*/buckets/*}/viewsZ5\x12\x33/v2/{parent=projects/*/locations/*/buckets/*}/viewsZ:\x12\x38/v2/{parent=organizations/*/locations/*/buckets/*}/viewsZ4\x12\x32/v2/{parent=folders/*/locations/*/buckets/*}/viewsZ<\x12:/v2/{parent=billingAccounts/*/locations/*/buckets/*}/views\x12\xe7\x02\n\x07GetView\x12!.google.logging.v2.GetViewRequest\x1a\x1a.google.logging.v2.LogView\"\x9c\x02\x82\xd3\xe4\x93\x02\x95\x02\x12,/v2/{name=*/*/locations/*/buckets/*/views/*}Z5\x12\x33/v2/{name=projects/*/locations/*/buckets/*/views/*}Z:\x12\x38/v2/{name=organizations/*/locations/*/buckets/*/views/*}Z4\x12\x32/v2/{name=folders/*/locations/*/buckets/*/views/*}Z<\x12:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}\x12\x8b\x03\n\nCreateView\x12$.google.logging.v2.CreateViewRequest\x1a\x1a.google.logging.v2.LogView\"\xba\x02\x82\xd3\xe4\x93\x02\xb3\x02\",/v2/{parent=*/*/locations/*/buckets/*}/views:\x04viewZ;\"3/v2/{parent=projects/*/locations/*/buckets/*}/views:\x04viewZ@\"8/v2/{parent=organizations/*/locations/*/buckets/*}/views:\x04viewZ:\"2/v2/{parent=folders/*/locations/*/buckets/*}/views:\x04viewZB\":/v2/{parent=billingAccounts/*/locations/*/buckets/*}/views:\x04view\x12\x8b\x03\n\nUpdateView\x12$.google.logging.v2.UpdateViewRequest\x1a\x1a.google.logging.v2.LogView\"\xba\x02\x82\xd3\xe4\x93\x02\xb3\x02\x32,/v2/{name=*/*/locations/*/buckets/*/views/*}:\x04viewZ;23/v2/{name=projects/*/locations/*/buckets/*/views/*}:\x04viewZ@28/v2/{name=organizations/*/locations/*/buckets/*/views/*}:\x04viewZ:22/v2/{name=folders/*/locations/*/buckets/*/views/*}:\x04viewZB2:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}:\x04view\x12\xe9\x02\n\nDeleteView\x12$.google.logging.v2.DeleteViewRequest\x1a\x16.google.protobuf.Empty\"\x9c\x02\x82\xd3\xe4\x93\x02\x95\x02*,/v2/{name=*/*/locations/*/buckets/*/views/*}Z5*3/v2/{name=projects/*/locations/*/buckets/*/views/*}Z:*8/v2/{name=organizations/*/locations/*/buckets/*/views/*}Z4*2/v2/{name=folders/*/locations/*/buckets/*/views/*}Z<*:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}\x12\x90\x02\n\tListSinks\x12#.google.logging.v2.ListSinksRequest\x1a$.google.logging.v2.ListSinksResponse\"\xb7\x01\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xa7\x01\x12\x16/v2/{parent=*/*}/sinksZ\x1f\x12\x1d/v2/{parent=projects/*}/sinksZ$\x12\"/v2/{parent=organizations/*}/sinksZ\x1e\x12\x1c/v2/{parent=folders/*}/sinksZ&\x12$/v2/{parent=billingAccounts/*}/sinks\x12\x9e\x02\n\x07GetSink\x12!.google.logging.v2.GetSinkRequest\x1a\x1a.google.logging.v2.LogSink\"\xd3\x01\xda\x41\tsink_name\x82\xd3\xe4\x93\x02\xc0\x01\x12\x1b/v2/{sink_name=*/*/sinks/*}Z$\x12\"/v2/{sink_name=projects/*/sinks/*}Z)\x12\'/v2/{sink_name=organizations/*/sinks/*}Z#\x12!/v2/{sink_name=folders/*/sinks/*}Z+\x12)/v2/{sink_name=billingAccounts/*/sinks/*}\x12\xab\x02\n\nCreateSink\x12$.google.logging.v2.CreateSinkRequest\x1a\x1a.google.logging.v2.LogSink\"\xda\x01\xda\x41\x0bparent,sink\x82\xd3\xe4\x93\x02\xc5\x01\"\x16/v2/{parent=*/*}/sinks:\x04sinkZ%\"\x1d/v2/{parent=projects/*}/sinks:\x04sinkZ*\"\"/v2/{parent=organizations/*}/sinks:\x04sinkZ$\"\x1c/v2/{parent=folders/*}/sinks:\x04sinkZ,\"$/v2/{parent=billingAccounts/*}/sinks:\x04sink\x12\x9f\x04\n\nUpdateSink\x12$.google.logging.v2.UpdateSinkRequest\x1a\x1a.google.logging.v2.LogSink\"\xce\x03\xda\x41\x1asink_name,sink,update_mask\xda\x41\x0esink_name,sink\x82\xd3\xe4\x93\x02\x99\x03\x1a\x1b/v2/{sink_name=*/*/sinks/*}:\x04sinkZ*\x1a\"/v2/{sink_name=projects/*/sinks/*}:\x04sinkZ/\x1a\'/v2/{sink_name=organizations/*/sinks/*}:\x04sinkZ)\x1a!/v2/{sink_name=folders/*/sinks/*}:\x04sinkZ1\x1a)/v2/{sink_name=billingAccounts/*/sinks/*}:\x04sinkZ*2\"/v2/{sink_name=projects/*/sinks/*}:\x04sinkZ/2\'/v2/{sink_name=organizations/*/sinks/*}:\x04sinkZ)2!/v2/{sink_name=folders/*/sinks/*}:\x04sinkZ12)/v2/{sink_name=billingAccounts/*/sinks/*}:\x04sink\x12\xa0\x02\n\nDeleteSink\x12$.google.logging.v2.DeleteSinkRequest\x1a\x16.google.protobuf.Empty\"\xd3\x01\xda\x41\tsink_name\x82\xd3\xe4\x93\x02\xc0\x01*\x1b/v2/{sink_name=*/*/sinks/*}Z$*\"/v2/{sink_name=projects/*/sinks/*}Z)*\'/v2/{sink_name=organizations/*/sinks/*}Z#*!/v2/{sink_name=folders/*/sinks/*}Z+*)/v2/{sink_name=billingAccounts/*/sinks/*}\x12\xbb\x03\n\nCreateLink\x12$.google.logging.v2.CreateLinkRequest\x1a\x1d.google.longrunning.Operation\"\xe7\x02\xca\x41\x14\n\x04Link\x12\x0cLinkMetadata\xda\x41\x13parent,link,link_id\x82\xd3\xe4\x93\x02\xb3\x02\",/v2/{parent=*/*/locations/*/buckets/*}/links:\x04linkZ;\"3/v2/{parent=projects/*/locations/*/buckets/*}/links:\x04linkZ@\"8/v2/{parent=organizations/*/locations/*/buckets/*}/links:\x04linkZ:\"2/v2/{parent=folders/*/locations/*/buckets/*}/links:\x04linkZB\":/v2/{parent=billingAccounts/*/locations/*/buckets/*}/links:\x04link\x12\x9f\x03\n\nDeleteLink\x12$.google.logging.v2.DeleteLinkRequest\x1a\x1d.google.longrunning.Operation\"\xcb\x02\xca\x41%\n\x15google.protobuf.Empty\x12\x0cLinkMetadata\xda\x41\x04name\x82\xd3\xe4\x93\x02\x95\x02*,/v2/{name=*/*/locations/*/buckets/*/links/*}Z5*3/v2/{name=projects/*/locations/*/buckets/*/links/*}Z:*8/v2/{name=organizations/*/locations/*/buckets/*/links/*}Z4*2/v2/{name=folders/*/locations/*/buckets/*/links/*}Z<*:/v2/{name=billingAccounts/*/locations/*/buckets/*/links/*}\x12\xfe\x02\n\tListLinks\x12#.google.logging.v2.ListLinksRequest\x1a$.google.logging.v2.ListLinksResponse\"\xa5\x02\xda\x41\x06parent\x82\xd3\xe4\x93\x02\x95\x02\x12,/v2/{parent=*/*/locations/*/buckets/*}/linksZ5\x12\x33/v2/{parent=projects/*/locations/*/buckets/*}/linksZ:\x12\x38/v2/{parent=organizations/*/locations/*/buckets/*}/linksZ4\x12\x32/v2/{parent=folders/*/locations/*/buckets/*}/linksZ<\x12:/v2/{parent=billingAccounts/*/locations/*/buckets/*}/links\x12\xeb\x02\n\x07GetLink\x12!.google.logging.v2.GetLinkRequest\x1a\x17.google.logging.v2.Link\"\xa3\x02\xda\x41\x04name\x82\xd3\xe4\x93\x02\x95\x02\x12,/v2/{name=*/*/locations/*/buckets/*/links/*}Z5\x12\x33/v2/{name=projects/*/locations/*/buckets/*/links/*}Z:\x12\x38/v2/{name=organizations/*/locations/*/buckets/*/links/*}Z4\x12\x32/v2/{name=folders/*/locations/*/buckets/*/links/*}Z<\x12:/v2/{name=billingAccounts/*/locations/*/buckets/*/links/*}\x12\xb8\x02\n\x0eListExclusions\x12(.google.logging.v2.ListExclusionsRequest\x1a).google.logging.v2.ListExclusionsResponse\"\xd0\x01\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xc0\x01\x12\x1b/v2/{parent=*/*}/exclusionsZ$\x12\"/v2/{parent=projects/*}/exclusionsZ)\x12\'/v2/{parent=organizations/*}/exclusionsZ#\x12!/v2/{parent=folders/*}/exclusionsZ+\x12)/v2/{parent=billingAccounts/*}/exclusions\x12\xa8\x02\n\x0cGetExclusion\x12&.google.logging.v2.GetExclusionRequest\x1a\x1f.google.logging.v2.LogExclusion\"\xce\x01\xda\x41\x04name\x82\xd3\xe4\x93\x02\xc0\x01\x12\x1b/v2/{name=*/*/exclusions/*}Z$\x12\"/v2/{name=projects/*/exclusions/*}Z)\x12\'/v2/{name=organizations/*/exclusions/*}Z#\x12!/v2/{name=folders/*/exclusions/*}Z+\x12)/v2/{name=billingAccounts/*/exclusions/*}\x12\xf1\x02\n\x0f\x43reateExclusion\x12).google.logging.v2.CreateExclusionRequest\x1a\x1f.google.logging.v2.LogExclusion\"\x91\x02\xda\x41\x10parent,exclusion\x82\xd3\xe4\x93\x02\xf7\x01\"\x1b/v2/{parent=*/*}/exclusions:\texclusionZ/\"\"/v2/{parent=projects/*}/exclusions:\texclusionZ4\"\'/v2/{parent=organizations/*}/exclusions:\texclusionZ.\"!/v2/{parent=folders/*}/exclusions:\texclusionZ6\")/v2/{parent=billingAccounts/*}/exclusions:\texclusion\x12\xfb\x02\n\x0fUpdateExclusion\x12).google.logging.v2.UpdateExclusionRequest\x1a\x1f.google.logging.v2.LogExclusion\"\x9b\x02\xda\x41\x1aname,exclusion,update_mask\x82\xd3\xe4\x93\x02\xf7\x01\x32\x1b/v2/{name=*/*/exclusions/*}:\texclusionZ/2\"/v2/{name=projects/*/exclusions/*}:\texclusionZ42\'/v2/{name=organizations/*/exclusions/*}:\texclusionZ.2!/v2/{name=folders/*/exclusions/*}:\texclusionZ62)/v2/{name=billingAccounts/*/exclusions/*}:\texclusion\x12\xa5\x02\n\x0f\x44\x65leteExclusion\x12).google.logging.v2.DeleteExclusionRequest\x1a\x16.google.protobuf.Empty\"\xce\x01\xda\x41\x04name\x82\xd3\xe4\x93\x02\xc0\x01*\x1b/v2/{name=*/*/exclusions/*}Z$*\"/v2/{name=projects/*/exclusions/*}Z)*\'/v2/{name=organizations/*/exclusions/*}Z#*!/v2/{name=folders/*/exclusions/*}Z+*)/v2/{name=billingAccounts/*/exclusions/*}\x12\xa7\x02\n\x0fGetCmekSettings\x12).google.logging.v2.GetCmekSettingsRequest\x1a\x1f.google.logging.v2.CmekSettings\"\xc7\x01\x82\xd3\xe4\x93\x02\xc0\x01\x12\x1b/v2/{name=*/*}/cmekSettingsZ$\x12\"/v2/{name=projects/*}/cmekSettingsZ)\x12\'/v2/{name=organizations/*}/cmekSettingsZ#\x12!/v2/{name=folders/*}/cmekSettingsZ+\x12)/v2/{name=billingAccounts/*}/cmekSettings\x12\xd1\x01\n\x12UpdateCmekSettings\x12,.google.logging.v2.UpdateCmekSettingsRequest\x1a\x1f.google.logging.v2.CmekSettings\"l\x82\xd3\xe4\x93\x02\x66\x32\x1b/v2/{name=*/*}/cmekSettings:\rcmek_settingsZ82\'/v2/{name=organizations/*}/cmekSettings:\rcmek_settings\x12\x8e\x02\n\x0bGetSettings\x12%.google.logging.v2.GetSettingsRequest\x1a\x1b.google.logging.v2.Settings\"\xba\x01\xda\x41\x04name\x82\xd3\xe4\x93\x02\xac\x01\x12\x17/v2/{name=*/*}/settingsZ \x12\x1e/v2/{name=projects/*}/settingsZ%\x12#/v2/{name=organizations/*}/settingsZ\x1f\x12\x1d/v2/{name=folders/*}/settingsZ\'\x12%/v2/{name=billingAccounts/*}/settings\x12\xf6\x01\n\x0eUpdateSettings\x12(.google.logging.v2.UpdateSettingsRequest\x1a\x1b.google.logging.v2.Settings\"\x9c\x01\xda\x41\x14settings,update_mask\x82\xd3\xe4\x93\x02\x7f\x32\x17/v2/{name=*/*}/settings:\x08settingsZ/2#/v2/{name=organizations/*}/settings:\x08settingsZ)2\x1d/v2/{name=folders/*}/settings:\x08settings\x12\xa9\x01\n\x0e\x43opyLogEntries\x12(.google.logging.v2.CopyLogEntriesRequest\x1a\x1d.google.longrunning.Operation\"N\xca\x41\x30\n\x16\x43opyLogEntriesResponse\x12\x16\x43opyLogEntriesMetadata\x82\xd3\xe4\x93\x02\x15\"\x10/v2/entries:copy:\x01*\x1a\xdf\x01\xca\x41\x16logging.googleapis.com\xd2\x41\xc2\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.readB\xd6\x03\n\x15\x63om.google.logging.v2B\x12LoggingConfigProtoP\x01Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\xf8\x01\x01\xaa\x02\x17Google.Cloud.Logging.V2\xca\x02\x17Google\\Cloud\\Logging\\V2\xea\x02\x1aGoogle::Cloud::Logging::V2\xea\x41`\n+logging.googleapis.com/OrganizationLocation\x12\x31organizations/{organization}/locations/{location}\xea\x41N\n%logging.googleapis.com/FolderLocation\x12%folders/{folder}/locations/{location}\xea\x41g\n-logging.googleapis.com/BillingAccountLocation\x12\x36\x62illingAccounts/{billing_account}/locations/{location}b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.logging.v2.logging_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\025com.google.logging.v2B\022LoggingConfigProtoP\001Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\370\001\001\252\002\027Google.Cloud.Logging.V2\312\002\027Google\\Cloud\\Logging\\V2\352\002\032Google::Cloud::Logging::V2\352A`\n+logging.googleapis.com/OrganizationLocation\0221organizations/{organization}/locations/{location}\352AN\n%logging.googleapis.com/FolderLocation\022%folders/{folder}/locations/{location}\352Ag\n-logging.googleapis.com/BillingAccountLocation\0226billingAccounts/{billing_account}/locations/{location}'
  _INDEXCONFIG.fields_by_name['field_path']._options = None
  _INDEXCONFIG.fields_by_name['field_path']._serialized_options = b'\340A\002'
  _INDEXCONFIG.fields_by_name['type']._options = None
  _INDEXCONFIG.fields_by_name['type']._serialized_options = b'\340A\002'
  _INDEXCONFIG.fields_by_name['create_time']._options = None
  _INDEXCONFIG.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGBUCKET.fields_by_name['name']._options = None
  _LOGBUCKET.fields_by_name['name']._serialized_options = b'\340A\003'
  _LOGBUCKET.fields_by_name['create_time']._options = None
  _LOGBUCKET.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGBUCKET.fields_by_name['update_time']._options = None
  _LOGBUCKET.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _LOGBUCKET.fields_by_name['lifecycle_state']._options = None
  _LOGBUCKET.fields_by_name['lifecycle_state']._serialized_options = b'\340A\003'
  _LOGBUCKET._options = None
  _LOGBUCKET._serialized_options = b'\352A\241\002\n logging.googleapis.com/LogBucket\0228projects/{project}/locations/{location}/buckets/{bucket}\022Borganizations/{organization}/locations/{location}/buckets/{bucket}\0226folders/{folder}/locations/{location}/buckets/{bucket}\022GbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}'
  _LOGVIEW.fields_by_name['create_time']._options = None
  _LOGVIEW.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGVIEW.fields_by_name['update_time']._options = None
  _LOGVIEW.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _LOGVIEW._options = None
  _LOGVIEW._serialized_options = b'\352A\323\002\n\036logging.googleapis.com/LogView\022Eprojects/{project}/locations/{location}/buckets/{bucket}/views/{view}\022Oorganizations/{organization}/locations/{location}/buckets/{bucket}/views/{view}\022Cfolders/{folder}/locations/{location}/buckets/{bucket}/views/{view}\022TbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}/views/{view}'
  _LOGSINK.fields_by_name['name']._options = None
  _LOGSINK.fields_by_name['name']._serialized_options = b'\340A\002'
  _LOGSINK.fields_by_name['destination']._options = None
  _LOGSINK.fields_by_name['destination']._serialized_options = b'\340A\002\372A\003\n\001*'
  _LOGSINK.fields_by_name['filter']._options = None
  _LOGSINK.fields_by_name['filter']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['description']._options = None
  _LOGSINK.fields_by_name['description']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['disabled']._options = None
  _LOGSINK.fields_by_name['disabled']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['exclusions']._options = None
  _LOGSINK.fields_by_name['exclusions']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['output_version_format']._options = None
  _LOGSINK.fields_by_name['output_version_format']._serialized_options = b'\030\001'
  _LOGSINK.fields_by_name['writer_identity']._options = None
  _LOGSINK.fields_by_name['writer_identity']._serialized_options = b'\340A\003'
  _LOGSINK.fields_by_name['include_children']._options = None
  _LOGSINK.fields_by_name['include_children']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['bigquery_options']._options = None
  _LOGSINK.fields_by_name['bigquery_options']._serialized_options = b'\340A\001'
  _LOGSINK.fields_by_name['create_time']._options = None
  _LOGSINK.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGSINK.fields_by_name['update_time']._options = None
  _LOGSINK.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _LOGSINK._options = None
  _LOGSINK._serialized_options = b'\352A\273\001\n\036logging.googleapis.com/LogSink\022\037projects/{project}/sinks/{sink}\022)organizations/{organization}/sinks/{sink}\022\035folders/{folder}/sinks/{sink}\022.billingAccounts/{billing_account}/sinks/{sink}'
  _BIGQUERYDATASET.fields_by_name['dataset_id']._options = None
  _BIGQUERYDATASET.fields_by_name['dataset_id']._serialized_options = b'\340A\003'
  _LINK.fields_by_name['create_time']._options = None
  _LINK.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LINK.fields_by_name['lifecycle_state']._options = None
  _LINK.fields_by_name['lifecycle_state']._serialized_options = b'\340A\003'
  _LINK._options = None
  _LINK._serialized_options = b'\352A\320\002\n\033logging.googleapis.com/Link\022Eprojects/{project}/locations/{location}/buckets/{bucket}/links/{link}\022Oorganizations/{organization}/locations/{location}/buckets/{bucket}/links/{link}\022Cfolders/{folder}/locations/{location}/buckets/{bucket}/links/{link}\022TbillingAccounts/{billing_account}/locations/{location}/buckets/{bucket}/links/{link}'
  _BIGQUERYOPTIONS.fields_by_name['use_partitioned_tables']._options = None
  _BIGQUERYOPTIONS.fields_by_name['use_partitioned_tables']._serialized_options = b'\340A\001'
  _BIGQUERYOPTIONS.fields_by_name['uses_timestamp_column_partitioning']._options = None
  _BIGQUERYOPTIONS.fields_by_name['uses_timestamp_column_partitioning']._serialized_options = b'\340A\003'
  _LISTBUCKETSREQUEST.fields_by_name['parent']._options = None
  _LISTBUCKETSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\"\022 logging.googleapis.com/LogBucket'
  _LISTBUCKETSREQUEST.fields_by_name['page_token']._options = None
  _LISTBUCKETSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTBUCKETSREQUEST.fields_by_name['page_size']._options = None
  _LISTBUCKETSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _CREATEBUCKETREQUEST.fields_by_name['parent']._options = None
  _CREATEBUCKETREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\"\022 logging.googleapis.com/LogBucket'
  _CREATEBUCKETREQUEST.fields_by_name['bucket_id']._options = None
  _CREATEBUCKETREQUEST.fields_by_name['bucket_id']._serialized_options = b'\340A\002'
  _CREATEBUCKETREQUEST.fields_by_name['bucket']._options = None
  _CREATEBUCKETREQUEST.fields_by_name['bucket']._serialized_options = b'\340A\002'
  _UPDATEBUCKETREQUEST.fields_by_name['name']._options = None
  _UPDATEBUCKETREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogBucket'
  _UPDATEBUCKETREQUEST.fields_by_name['bucket']._options = None
  _UPDATEBUCKETREQUEST.fields_by_name['bucket']._serialized_options = b'\340A\002'
  _UPDATEBUCKETREQUEST.fields_by_name['update_mask']._options = None
  _UPDATEBUCKETREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\002'
  _GETBUCKETREQUEST.fields_by_name['name']._options = None
  _GETBUCKETREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogBucket'
  _DELETEBUCKETREQUEST.fields_by_name['name']._options = None
  _DELETEBUCKETREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogBucket'
  _UNDELETEBUCKETREQUEST.fields_by_name['name']._options = None
  _UNDELETEBUCKETREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogBucket'
  _LISTVIEWSREQUEST.fields_by_name['parent']._options = None
  _LISTVIEWSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002'
  _LISTVIEWSREQUEST.fields_by_name['page_token']._options = None
  _LISTVIEWSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTVIEWSREQUEST.fields_by_name['page_size']._options = None
  _LISTVIEWSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _CREATEVIEWREQUEST.fields_by_name['parent']._options = None
  _CREATEVIEWREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002'
  _CREATEVIEWREQUEST.fields_by_name['view_id']._options = None
  _CREATEVIEWREQUEST.fields_by_name['view_id']._serialized_options = b'\340A\002'
  _CREATEVIEWREQUEST.fields_by_name['view']._options = None
  _CREATEVIEWREQUEST.fields_by_name['view']._serialized_options = b'\340A\002'
  _UPDATEVIEWREQUEST.fields_by_name['name']._options = None
  _UPDATEVIEWREQUEST.fields_by_name['name']._serialized_options = b'\340A\002'
  _UPDATEVIEWREQUEST.fields_by_name['view']._options = None
  _UPDATEVIEWREQUEST.fields_by_name['view']._serialized_options = b'\340A\002'
  _UPDATEVIEWREQUEST.fields_by_name['update_mask']._options = None
  _UPDATEVIEWREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\001'
  _GETVIEWREQUEST.fields_by_name['name']._options = None
  _GETVIEWREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A \n\036logging.googleapis.com/LogView'
  _DELETEVIEWREQUEST.fields_by_name['name']._options = None
  _DELETEVIEWREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A \n\036logging.googleapis.com/LogView'
  _LISTSINKSREQUEST.fields_by_name['parent']._options = None
  _LISTSINKSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A \022\036logging.googleapis.com/LogSink'
  _LISTSINKSREQUEST.fields_by_name['page_token']._options = None
  _LISTSINKSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTSINKSREQUEST.fields_by_name['page_size']._options = None
  _LISTSINKSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _GETSINKREQUEST.fields_by_name['sink_name']._options = None
  _GETSINKREQUEST.fields_by_name['sink_name']._serialized_options = b'\340A\002\372A \n\036logging.googleapis.com/LogSink'
  _CREATESINKREQUEST.fields_by_name['parent']._options = None
  _CREATESINKREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A \022\036logging.googleapis.com/LogSink'
  _CREATESINKREQUEST.fields_by_name['sink']._options = None
  _CREATESINKREQUEST.fields_by_name['sink']._serialized_options = b'\340A\002'
  _CREATESINKREQUEST.fields_by_name['unique_writer_identity']._options = None
  _CREATESINKREQUEST.fields_by_name['unique_writer_identity']._serialized_options = b'\340A\001'
  _UPDATESINKREQUEST.fields_by_name['sink_name']._options = None
  _UPDATESINKREQUEST.fields_by_name['sink_name']._serialized_options = b'\340A\002\372A \n\036logging.googleapis.com/LogSink'
  _UPDATESINKREQUEST.fields_by_name['sink']._options = None
  _UPDATESINKREQUEST.fields_by_name['sink']._serialized_options = b'\340A\002'
  _UPDATESINKREQUEST.fields_by_name['unique_writer_identity']._options = None
  _UPDATESINKREQUEST.fields_by_name['unique_writer_identity']._serialized_options = b'\340A\001'
  _UPDATESINKREQUEST.fields_by_name['update_mask']._options = None
  _UPDATESINKREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\001'
  _DELETESINKREQUEST.fields_by_name['sink_name']._options = None
  _DELETESINKREQUEST.fields_by_name['sink_name']._serialized_options = b'\340A\002\372A \n\036logging.googleapis.com/LogSink'
  _CREATELINKREQUEST.fields_by_name['parent']._options = None
  _CREATELINKREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\035\022\033logging.googleapis.com/Link'
  _CREATELINKREQUEST.fields_by_name['link']._options = None
  _CREATELINKREQUEST.fields_by_name['link']._serialized_options = b'\340A\002'
  _CREATELINKREQUEST.fields_by_name['link_id']._options = None
  _CREATELINKREQUEST.fields_by_name['link_id']._serialized_options = b'\340A\002'
  _DELETELINKREQUEST.fields_by_name['name']._options = None
  _DELETELINKREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\035\n\033logging.googleapis.com/Link'
  _LISTLINKSREQUEST.fields_by_name['parent']._options = None
  _LISTLINKSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\035\022\033logging.googleapis.com/Link'
  _LISTLINKSREQUEST.fields_by_name['page_token']._options = None
  _LISTLINKSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTLINKSREQUEST.fields_by_name['page_size']._options = None
  _LISTLINKSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _GETLINKREQUEST.fields_by_name['name']._options = None
  _GETLINKREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A\035\n\033logging.googleapis.com/Link'
  _LOGEXCLUSION.fields_by_name['name']._options = None
  _LOGEXCLUSION.fields_by_name['name']._serialized_options = b'\340A\002'
  _LOGEXCLUSION.fields_by_name['description']._options = None
  _LOGEXCLUSION.fields_by_name['description']._serialized_options = b'\340A\001'
  _LOGEXCLUSION.fields_by_name['filter']._options = None
  _LOGEXCLUSION.fields_by_name['filter']._serialized_options = b'\340A\002'
  _LOGEXCLUSION.fields_by_name['disabled']._options = None
  _LOGEXCLUSION.fields_by_name['disabled']._serialized_options = b'\340A\001'
  _LOGEXCLUSION.fields_by_name['create_time']._options = None
  _LOGEXCLUSION.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGEXCLUSION.fields_by_name['update_time']._options = None
  _LOGEXCLUSION.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _LOGEXCLUSION._options = None
  _LOGEXCLUSION._serialized_options = b'\352A\350\001\n#logging.googleapis.com/LogExclusion\022)projects/{project}/exclusions/{exclusion}\0223organizations/{organization}/exclusions/{exclusion}\022\'folders/{folder}/exclusions/{exclusion}\0228billingAccounts/{billing_account}/exclusions/{exclusion}'
  _LISTEXCLUSIONSREQUEST.fields_by_name['parent']._options = None
  _LISTEXCLUSIONSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A%\022#logging.googleapis.com/LogExclusion'
  _LISTEXCLUSIONSREQUEST.fields_by_name['page_token']._options = None
  _LISTEXCLUSIONSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTEXCLUSIONSREQUEST.fields_by_name['page_size']._options = None
  _LISTEXCLUSIONSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _GETEXCLUSIONREQUEST.fields_by_name['name']._options = None
  _GETEXCLUSIONREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A%\n#logging.googleapis.com/LogExclusion'
  _CREATEEXCLUSIONREQUEST.fields_by_name['parent']._options = None
  _CREATEEXCLUSIONREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A%\022#logging.googleapis.com/LogExclusion'
  _CREATEEXCLUSIONREQUEST.fields_by_name['exclusion']._options = None
  _CREATEEXCLUSIONREQUEST.fields_by_name['exclusion']._serialized_options = b'\340A\002'
  _UPDATEEXCLUSIONREQUEST.fields_by_name['name']._options = None
  _UPDATEEXCLUSIONREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A%\n#logging.googleapis.com/LogExclusion'
  _UPDATEEXCLUSIONREQUEST.fields_by_name['exclusion']._options = None
  _UPDATEEXCLUSIONREQUEST.fields_by_name['exclusion']._serialized_options = b'\340A\002'
  _UPDATEEXCLUSIONREQUEST.fields_by_name['update_mask']._options = None
  _UPDATEEXCLUSIONREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\002'
  _DELETEEXCLUSIONREQUEST.fields_by_name['name']._options = None
  _DELETEEXCLUSIONREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A%\n#logging.googleapis.com/LogExclusion'
  _GETCMEKSETTINGSREQUEST.fields_by_name['name']._options = None
  _GETCMEKSETTINGSREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A%\n#logging.googleapis.com/CmekSettings'
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['name']._options = None
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['name']._serialized_options = b'\340A\002'
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['cmek_settings']._options = None
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['cmek_settings']._serialized_options = b'\340A\002'
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['update_mask']._options = None
  _UPDATECMEKSETTINGSREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\001'
  _CMEKSETTINGS.fields_by_name['name']._options = None
  _CMEKSETTINGS.fields_by_name['name']._serialized_options = b'\340A\003'
  _CMEKSETTINGS.fields_by_name['service_account_id']._options = None
  _CMEKSETTINGS.fields_by_name['service_account_id']._serialized_options = b'\340A\003'
  _CMEKSETTINGS._options = None
  _CMEKSETTINGS._serialized_options = b'\352A\300\001\n#logging.googleapis.com/CmekSettings\022\037projects/{project}/cmekSettings\022)organizations/{organization}/cmekSettings\022\035folders/{folder}/cmekSettings\022.billingAccounts/{billing_account}/cmekSettings'
  _GETSETTINGSREQUEST.fields_by_name['name']._options = None
  _GETSETTINGSREQUEST.fields_by_name['name']._serialized_options = b'\340A\002\372A!\n\037logging.googleapis.com/Settings'
  _UPDATESETTINGSREQUEST.fields_by_name['name']._options = None
  _UPDATESETTINGSREQUEST.fields_by_name['name']._serialized_options = b'\340A\002'
  _UPDATESETTINGSREQUEST.fields_by_name['settings']._options = None
  _UPDATESETTINGSREQUEST.fields_by_name['settings']._serialized_options = b'\340A\002'
  _UPDATESETTINGSREQUEST.fields_by_name['update_mask']._options = None
  _UPDATESETTINGSREQUEST.fields_by_name['update_mask']._serialized_options = b'\340A\001'
  _SETTINGS.fields_by_name['name']._options = None
  _SETTINGS.fields_by_name['name']._serialized_options = b'\340A\003'
  _SETTINGS.fields_by_name['kms_key_name']._options = None
  _SETTINGS.fields_by_name['kms_key_name']._serialized_options = b'\340A\001'
  _SETTINGS.fields_by_name['kms_service_account_id']._options = None
  _SETTINGS.fields_by_name['kms_service_account_id']._serialized_options = b'\340A\003'
  _SETTINGS.fields_by_name['storage_location']._options = None
  _SETTINGS.fields_by_name['storage_location']._serialized_options = b'\340A\001'
  _SETTINGS.fields_by_name['disable_default_sink']._options = None
  _SETTINGS.fields_by_name['disable_default_sink']._serialized_options = b'\340A\001'
  _SETTINGS._options = None
  _SETTINGS._serialized_options = b'\352A\254\001\n\037logging.googleapis.com/Settings\022\033projects/{project}/settings\022%organizations/{organization}/settings\022\031folders/{folder}/settings\022*billingAccounts/{billing_account}/settings'
  _COPYLOGENTRIESREQUEST.fields_by_name['name']._options = None
  _COPYLOGENTRIESREQUEST.fields_by_name['name']._serialized_options = b'\340A\002'
  _COPYLOGENTRIESREQUEST.fields_by_name['filter']._options = None
  _COPYLOGENTRIESREQUEST.fields_by_name['filter']._serialized_options = b'\340A\001'
  _COPYLOGENTRIESREQUEST.fields_by_name['destination']._options = None
  _COPYLOGENTRIESREQUEST.fields_by_name['destination']._serialized_options = b'\340A\002'
  _CONFIGSERVICEV2._options = None
  _CONFIGSERVICEV2._serialized_options = b'\312A\026logging.googleapis.com\322A\302\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.read'
  _CONFIGSERVICEV2.methods_by_name['ListBuckets']._options = None
  _CONFIGSERVICEV2.methods_by_name['ListBuckets']._serialized_options = b'\332A\006parent\202\323\344\223\002\355\001\022$/v2/{parent=*/*/locations/*}/bucketsZ-\022+/v2/{parent=projects/*/locations/*}/bucketsZ2\0220/v2/{parent=organizations/*/locations/*}/bucketsZ,\022*/v2/{parent=folders/*/locations/*}/bucketsZ4\0222/v2/{parent=billingAccounts/*/locations/*}/buckets'
  _CONFIGSERVICEV2.methods_by_name['GetBucket']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetBucket']._serialized_options = b'\202\323\344\223\002\355\001\022$/v2/{name=*/*/locations/*/buckets/*}Z-\022+/v2/{name=projects/*/locations/*/buckets/*}Z2\0220/v2/{name=organizations/*/locations/*/buckets/*}Z,\022*/v2/{name=folders/*/locations/*/buckets/*}Z4\0222/v2/{name=billingAccounts/*/locations/*/buckets/*}'
  _CONFIGSERVICEV2.methods_by_name['CreateBucketAsync']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateBucketAsync']._serialized_options = b'\312A\033\n\tLogBucket\022\016BucketMetadata\202\323\344\223\002\321\002\"0/v2/{parent=*/*/locations/*}/buckets:createAsync:\006bucketZA\"7/v2/{parent=projects/*/locations/*}/buckets:createAsync:\006bucketZF\"</v2/{parent=organizations/*/locations/*}/buckets:createAsync:\006bucketZ@\"6/v2/{parent=folders/*/locations/*}/buckets:createAsync:\006bucketZH\">/v2/{parent=billingAccounts/*/locations/*}/buckets:createAsync:\006bucket'
  _CONFIGSERVICEV2.methods_by_name['UpdateBucketAsync']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateBucketAsync']._serialized_options = b'\312A\033\n\tLogBucket\022\016BucketMetadata\202\323\344\223\002\321\002\"0/v2/{name=*/*/locations/*/buckets/*}:updateAsync:\006bucketZA\"7/v2/{name=projects/*/locations/*/buckets/*}:updateAsync:\006bucketZF\"</v2/{name=organizations/*/locations/*/buckets/*}:updateAsync:\006bucketZ@\"6/v2/{name=folders/*/locations/*/buckets/*}:updateAsync:\006bucketZH\">/v2/{name=billingAccounts/*/locations/*/buckets/*}:updateAsync:\006bucket'
  _CONFIGSERVICEV2.methods_by_name['CreateBucket']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateBucket']._serialized_options = b'\202\323\344\223\002\225\002\"$/v2/{parent=*/*/locations/*}/buckets:\006bucketZ5\"+/v2/{parent=projects/*/locations/*}/buckets:\006bucketZ:\"0/v2/{parent=organizations/*/locations/*}/buckets:\006bucketZ4\"*/v2/{parent=folders/*/locations/*}/buckets:\006bucketZ<\"2/v2/{parent=billingAccounts/*/locations/*}/buckets:\006bucket'
  _CONFIGSERVICEV2.methods_by_name['UpdateBucket']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateBucket']._serialized_options = b'\202\323\344\223\002\225\0022$/v2/{name=*/*/locations/*/buckets/*}:\006bucketZ52+/v2/{name=projects/*/locations/*/buckets/*}:\006bucketZ:20/v2/{name=organizations/*/locations/*/buckets/*}:\006bucketZ42*/v2/{name=folders/*/locations/*/buckets/*}:\006bucketZ<22/v2/{name=billingAccounts/*/locations/*/buckets/*}:\006bucket'
  _CONFIGSERVICEV2.methods_by_name['DeleteBucket']._options = None
  _CONFIGSERVICEV2.methods_by_name['DeleteBucket']._serialized_options = b'\202\323\344\223\002\355\001*$/v2/{name=*/*/locations/*/buckets/*}Z-*+/v2/{name=projects/*/locations/*/buckets/*}Z2*0/v2/{name=organizations/*/locations/*/buckets/*}Z,**/v2/{name=folders/*/locations/*/buckets/*}Z4*2/v2/{name=billingAccounts/*/locations/*/buckets/*}'
  _CONFIGSERVICEV2.methods_by_name['UndeleteBucket']._options = None
  _CONFIGSERVICEV2.methods_by_name['UndeleteBucket']._serialized_options = b'\202\323\344\223\002\251\002\"-/v2/{name=*/*/locations/*/buckets/*}:undelete:\001*Z9\"4/v2/{name=projects/*/locations/*/buckets/*}:undelete:\001*Z>\"9/v2/{name=organizations/*/locations/*/buckets/*}:undelete:\001*Z8\"3/v2/{name=folders/*/locations/*/buckets/*}:undelete:\001*Z@\";/v2/{name=billingAccounts/*/locations/*/buckets/*}:undelete:\001*'
  _CONFIGSERVICEV2.methods_by_name['ListViews']._options = None
  _CONFIGSERVICEV2.methods_by_name['ListViews']._serialized_options = b'\332A\006parent\202\323\344\223\002\225\002\022,/v2/{parent=*/*/locations/*/buckets/*}/viewsZ5\0223/v2/{parent=projects/*/locations/*/buckets/*}/viewsZ:\0228/v2/{parent=organizations/*/locations/*/buckets/*}/viewsZ4\0222/v2/{parent=folders/*/locations/*/buckets/*}/viewsZ<\022:/v2/{parent=billingAccounts/*/locations/*/buckets/*}/views'
  _CONFIGSERVICEV2.methods_by_name['GetView']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetView']._serialized_options = b'\202\323\344\223\002\225\002\022,/v2/{name=*/*/locations/*/buckets/*/views/*}Z5\0223/v2/{name=projects/*/locations/*/buckets/*/views/*}Z:\0228/v2/{name=organizations/*/locations/*/buckets/*/views/*}Z4\0222/v2/{name=folders/*/locations/*/buckets/*/views/*}Z<\022:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}'
  _CONFIGSERVICEV2.methods_by_name['CreateView']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateView']._serialized_options = b'\202\323\344\223\002\263\002\",/v2/{parent=*/*/locations/*/buckets/*}/views:\004viewZ;\"3/v2/{parent=projects/*/locations/*/buckets/*}/views:\004viewZ@\"8/v2/{parent=organizations/*/locations/*/buckets/*}/views:\004viewZ:\"2/v2/{parent=folders/*/locations/*/buckets/*}/views:\004viewZB\":/v2/{parent=billingAccounts/*/locations/*/buckets/*}/views:\004view'
  _CONFIGSERVICEV2.methods_by_name['UpdateView']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateView']._serialized_options = b'\202\323\344\223\002\263\0022,/v2/{name=*/*/locations/*/buckets/*/views/*}:\004viewZ;23/v2/{name=projects/*/locations/*/buckets/*/views/*}:\004viewZ@28/v2/{name=organizations/*/locations/*/buckets/*/views/*}:\004viewZ:22/v2/{name=folders/*/locations/*/buckets/*/views/*}:\004viewZB2:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}:\004view'
  _CONFIGSERVICEV2.methods_by_name['DeleteView']._options = None
  _CONFIGSERVICEV2.methods_by_name['DeleteView']._serialized_options = b'\202\323\344\223\002\225\002*,/v2/{name=*/*/locations/*/buckets/*/views/*}Z5*3/v2/{name=projects/*/locations/*/buckets/*/views/*}Z:*8/v2/{name=organizations/*/locations/*/buckets/*/views/*}Z4*2/v2/{name=folders/*/locations/*/buckets/*/views/*}Z<*:/v2/{name=billingAccounts/*/locations/*/buckets/*/views/*}'
  _CONFIGSERVICEV2.methods_by_name['ListSinks']._options = None
  _CONFIGSERVICEV2.methods_by_name['ListSinks']._serialized_options = b'\332A\006parent\202\323\344\223\002\247\001\022\026/v2/{parent=*/*}/sinksZ\037\022\035/v2/{parent=projects/*}/sinksZ$\022\"/v2/{parent=organizations/*}/sinksZ\036\022\034/v2/{parent=folders/*}/sinksZ&\022$/v2/{parent=billingAccounts/*}/sinks'
  _CONFIGSERVICEV2.methods_by_name['GetSink']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetSink']._serialized_options = b'\332A\tsink_name\202\323\344\223\002\300\001\022\033/v2/{sink_name=*/*/sinks/*}Z$\022\"/v2/{sink_name=projects/*/sinks/*}Z)\022\'/v2/{sink_name=organizations/*/sinks/*}Z#\022!/v2/{sink_name=folders/*/sinks/*}Z+\022)/v2/{sink_name=billingAccounts/*/sinks/*}'
  _CONFIGSERVICEV2.methods_by_name['CreateSink']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateSink']._serialized_options = b'\332A\013parent,sink\202\323\344\223\002\305\001\"\026/v2/{parent=*/*}/sinks:\004sinkZ%\"\035/v2/{parent=projects/*}/sinks:\004sinkZ*\"\"/v2/{parent=organizations/*}/sinks:\004sinkZ$\"\034/v2/{parent=folders/*}/sinks:\004sinkZ,\"$/v2/{parent=billingAccounts/*}/sinks:\004sink'
  _CONFIGSERVICEV2.methods_by_name['UpdateSink']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateSink']._serialized_options = b'\332A\032sink_name,sink,update_mask\332A\016sink_name,sink\202\323\344\223\002\231\003\032\033/v2/{sink_name=*/*/sinks/*}:\004sinkZ*\032\"/v2/{sink_name=projects/*/sinks/*}:\004sinkZ/\032\'/v2/{sink_name=organizations/*/sinks/*}:\004sinkZ)\032!/v2/{sink_name=folders/*/sinks/*}:\004sinkZ1\032)/v2/{sink_name=billingAccounts/*/sinks/*}:\004sinkZ*2\"/v2/{sink_name=projects/*/sinks/*}:\004sinkZ/2\'/v2/{sink_name=organizations/*/sinks/*}:\004sinkZ)2!/v2/{sink_name=folders/*/sinks/*}:\004sinkZ12)/v2/{sink_name=billingAccounts/*/sinks/*}:\004sink'
  _CONFIGSERVICEV2.methods_by_name['DeleteSink']._options = None
  _CONFIGSERVICEV2.methods_by_name['DeleteSink']._serialized_options = b'\332A\tsink_name\202\323\344\223\002\300\001*\033/v2/{sink_name=*/*/sinks/*}Z$*\"/v2/{sink_name=projects/*/sinks/*}Z)*\'/v2/{sink_name=organizations/*/sinks/*}Z#*!/v2/{sink_name=folders/*/sinks/*}Z+*)/v2/{sink_name=billingAccounts/*/sinks/*}'
  _CONFIGSERVICEV2.methods_by_name['CreateLink']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateLink']._serialized_options = b'\312A\024\n\004Link\022\014LinkMetadata\332A\023parent,link,link_id\202\323\344\223\002\263\002\",/v2/{parent=*/*/locations/*/buckets/*}/links:\004linkZ;\"3/v2/{parent=projects/*/locations/*/buckets/*}/links:\004linkZ@\"8/v2/{parent=organizations/*/locations/*/buckets/*}/links:\004linkZ:\"2/v2/{parent=folders/*/locations/*/buckets/*}/links:\004linkZB\":/v2/{parent=billingAccounts/*/locations/*/buckets/*}/links:\004link'
  _CONFIGSERVICEV2.methods_by_name['DeleteLink']._options = None
  _CONFIGSERVICEV2.methods_by_name['DeleteLink']._serialized_options = b'\312A%\n\025google.protobuf.Empty\022\014LinkMetadata\332A\004name\202\323\344\223\002\225\002*,/v2/{name=*/*/locations/*/buckets/*/links/*}Z5*3/v2/{name=projects/*/locations/*/buckets/*/links/*}Z:*8/v2/{name=organizations/*/locations/*/buckets/*/links/*}Z4*2/v2/{name=folders/*/locations/*/buckets/*/links/*}Z<*:/v2/{name=billingAccounts/*/locations/*/buckets/*/links/*}'
  _CONFIGSERVICEV2.methods_by_name['ListLinks']._options = None
  _CONFIGSERVICEV2.methods_by_name['ListLinks']._serialized_options = b'\332A\006parent\202\323\344\223\002\225\002\022,/v2/{parent=*/*/locations/*/buckets/*}/linksZ5\0223/v2/{parent=projects/*/locations/*/buckets/*}/linksZ:\0228/v2/{parent=organizations/*/locations/*/buckets/*}/linksZ4\0222/v2/{parent=folders/*/locations/*/buckets/*}/linksZ<\022:/v2/{parent=billingAccounts/*/locations/*/buckets/*}/links'
  _CONFIGSERVICEV2.methods_by_name['GetLink']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetLink']._serialized_options = b'\332A\004name\202\323\344\223\002\225\002\022,/v2/{name=*/*/locations/*/buckets/*/links/*}Z5\0223/v2/{name=projects/*/locations/*/buckets/*/links/*}Z:\0228/v2/{name=organizations/*/locations/*/buckets/*/links/*}Z4\0222/v2/{name=folders/*/locations/*/buckets/*/links/*}Z<\022:/v2/{name=billingAccounts/*/locations/*/buckets/*/links/*}'
  _CONFIGSERVICEV2.methods_by_name['ListExclusions']._options = None
  _CONFIGSERVICEV2.methods_by_name['ListExclusions']._serialized_options = b'\332A\006parent\202\323\344\223\002\300\001\022\033/v2/{parent=*/*}/exclusionsZ$\022\"/v2/{parent=projects/*}/exclusionsZ)\022\'/v2/{parent=organizations/*}/exclusionsZ#\022!/v2/{parent=folders/*}/exclusionsZ+\022)/v2/{parent=billingAccounts/*}/exclusions'
  _CONFIGSERVICEV2.methods_by_name['GetExclusion']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetExclusion']._serialized_options = b'\332A\004name\202\323\344\223\002\300\001\022\033/v2/{name=*/*/exclusions/*}Z$\022\"/v2/{name=projects/*/exclusions/*}Z)\022\'/v2/{name=organizations/*/exclusions/*}Z#\022!/v2/{name=folders/*/exclusions/*}Z+\022)/v2/{name=billingAccounts/*/exclusions/*}'
  _CONFIGSERVICEV2.methods_by_name['CreateExclusion']._options = None
  _CONFIGSERVICEV2.methods_by_name['CreateExclusion']._serialized_options = b'\332A\020parent,exclusion\202\323\344\223\002\367\001\"\033/v2/{parent=*/*}/exclusions:\texclusionZ/\"\"/v2/{parent=projects/*}/exclusions:\texclusionZ4\"\'/v2/{parent=organizations/*}/exclusions:\texclusionZ.\"!/v2/{parent=folders/*}/exclusions:\texclusionZ6\")/v2/{parent=billingAccounts/*}/exclusions:\texclusion'
  _CONFIGSERVICEV2.methods_by_name['UpdateExclusion']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateExclusion']._serialized_options = b'\332A\032name,exclusion,update_mask\202\323\344\223\002\367\0012\033/v2/{name=*/*/exclusions/*}:\texclusionZ/2\"/v2/{name=projects/*/exclusions/*}:\texclusionZ42\'/v2/{name=organizations/*/exclusions/*}:\texclusionZ.2!/v2/{name=folders/*/exclusions/*}:\texclusionZ62)/v2/{name=billingAccounts/*/exclusions/*}:\texclusion'
  _CONFIGSERVICEV2.methods_by_name['DeleteExclusion']._options = None
  _CONFIGSERVICEV2.methods_by_name['DeleteExclusion']._serialized_options = b'\332A\004name\202\323\344\223\002\300\001*\033/v2/{name=*/*/exclusions/*}Z$*\"/v2/{name=projects/*/exclusions/*}Z)*\'/v2/{name=organizations/*/exclusions/*}Z#*!/v2/{name=folders/*/exclusions/*}Z+*)/v2/{name=billingAccounts/*/exclusions/*}'
  _CONFIGSERVICEV2.methods_by_name['GetCmekSettings']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetCmekSettings']._serialized_options = b'\202\323\344\223\002\300\001\022\033/v2/{name=*/*}/cmekSettingsZ$\022\"/v2/{name=projects/*}/cmekSettingsZ)\022\'/v2/{name=organizations/*}/cmekSettingsZ#\022!/v2/{name=folders/*}/cmekSettingsZ+\022)/v2/{name=billingAccounts/*}/cmekSettings'
  _CONFIGSERVICEV2.methods_by_name['UpdateCmekSettings']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateCmekSettings']._serialized_options = b'\202\323\344\223\002f2\033/v2/{name=*/*}/cmekSettings:\rcmek_settingsZ82\'/v2/{name=organizations/*}/cmekSettings:\rcmek_settings'
  _CONFIGSERVICEV2.methods_by_name['GetSettings']._options = None
  _CONFIGSERVICEV2.methods_by_name['GetSettings']._serialized_options = b'\332A\004name\202\323\344\223\002\254\001\022\027/v2/{name=*/*}/settingsZ \022\036/v2/{name=projects/*}/settingsZ%\022#/v2/{name=organizations/*}/settingsZ\037\022\035/v2/{name=folders/*}/settingsZ\'\022%/v2/{name=billingAccounts/*}/settings'
  _CONFIGSERVICEV2.methods_by_name['UpdateSettings']._options = None
  _CONFIGSERVICEV2.methods_by_name['UpdateSettings']._serialized_options = b'\332A\024settings,update_mask\202\323\344\223\002\1772\027/v2/{name=*/*}/settings:\010settingsZ/2#/v2/{name=organizations/*}/settings:\010settingsZ)2\035/v2/{name=folders/*}/settings:\010settings'
  _CONFIGSERVICEV2.methods_by_name['CopyLogEntries']._options = None
  _CONFIGSERVICEV2.methods_by_name['CopyLogEntries']._serialized_options = b'\312A0\n\026CopyLogEntriesResponse\022\026CopyLogEntriesMetadata\202\323\344\223\002\025\"\020/v2/entries:copy:\001*'
  _globals['_OPERATIONSTATE']._serialized_start=9292
  _globals['_OPERATIONSTATE']._serialized_end=9536
  _globals['_LIFECYCLESTATE']._serialized_start=9538
  _globals['_LIFECYCLESTATE']._serialized_end=9661
  _globals['_INDEXTYPE']._serialized_start=9663
  _globals['_INDEXTYPE']._serialized_end=9749
  _globals['_INDEXCONFIG']._serialized_start=310
  _globals['_INDEXCONFIG']._serialized_end=451
  _globals['_LOGBUCKET']._serialized_start=454
  _globals['_LOGBUCKET']._serialized_end=1179
  _globals['_LOGVIEW']._serialized_start=1182
  _globals['_LOGVIEW']._serialized_end=1696
  _globals['_LOGSINK']._serialized_start=1699
  _globals['_LOGSINK']._serialized_end=2472
  _globals['_LOGSINK_VERSIONFORMAT']._serialized_start=2204
  _globals['_LOGSINK_VERSIONFORMAT']._serialized_end=2267
  _globals['_BIGQUERYDATASET']._serialized_start=2474
  _globals['_BIGQUERYDATASET']._serialized_end=2516
  _globals['_LINK']._serialized_start=2519
  _globals['_LINK']._serialized_end=3084
  _globals['_BIGQUERYOPTIONS']._serialized_start=3086
  _globals['_BIGQUERYOPTIONS']._serialized_end=3189
  _globals['_LISTBUCKETSREQUEST']._serialized_start=3191
  _globals['_LISTBUCKETSREQUEST']._serialized_end=3318
  _globals['_LISTBUCKETSRESPONSE']._serialized_start=3320
  _globals['_LISTBUCKETSRESPONSE']._serialized_end=3413
  _globals['_CREATEBUCKETREQUEST']._serialized_start=3416
  _globals['_CREATEBUCKETREQUEST']._serialized_end=3570
  _globals['_UPDATEBUCKETREQUEST']._serialized_start=3573
  _globals['_UPDATEBUCKETREQUEST']._serialized_end=3755
  _globals['_GETBUCKETREQUEST']._serialized_start=3757
  _globals['_GETBUCKETREQUEST']._serialized_end=3831
  _globals['_DELETEBUCKETREQUEST']._serialized_start=3833
  _globals['_DELETEBUCKETREQUEST']._serialized_end=3910
  _globals['_UNDELETEBUCKETREQUEST']._serialized_start=3912
  _globals['_UNDELETEBUCKETREQUEST']._serialized_end=3991
  _globals['_LISTVIEWSREQUEST']._serialized_start=3993
  _globals['_LISTVIEWSREQUEST']._serialized_end=4081
  _globals['_LISTVIEWSRESPONSE']._serialized_start=4083
  _globals['_LISTVIEWSRESPONSE']._serialized_end=4170
  _globals['_CREATEVIEWREQUEST']._serialized_start=4172
  _globals['_CREATEVIEWREQUEST']._serialized_end=4281
  _globals['_UPDATEVIEWREQUEST']._serialized_start=4284
  _globals['_UPDATEVIEWREQUEST']._serialized_end=4423
  _globals['_GETVIEWREQUEST']._serialized_start=4425
  _globals['_GETVIEWREQUEST']._serialized_end=4495
  _globals['_DELETEVIEWREQUEST']._serialized_start=4497
  _globals['_DELETEVIEWREQUEST']._serialized_end=4570
  _globals['_LISTSINKSREQUEST']._serialized_start=4572
  _globals['_LISTSINKSREQUEST']._serialized_end=4695
  _globals['_LISTSINKSRESPONSE']._serialized_start=4697
  _globals['_LISTSINKSRESPONSE']._serialized_end=4784
  _globals['_GETSINKREQUEST']._serialized_start=4786
  _globals['_GETSINKREQUEST']._serialized_end=4861
  _globals['_CREATESINKREQUEST']._serialized_start=4864
  _globals['_CREATESINKREQUEST']._serialized_end=5023
  _globals['_UPDATESINKREQUEST']._serialized_start=5026
  _globals['_UPDATESINKREQUEST']._serialized_end=5242
  _globals['_DELETESINKREQUEST']._serialized_start=5244
  _globals['_DELETESINKREQUEST']._serialized_end=5322
  _globals['_CREATELINKREQUEST']._serialized_start=5325
  _globals['_CREATELINKREQUEST']._serialized_end=5463
  _globals['_DELETELINKREQUEST']._serialized_start=5465
  _globals['_DELETELINKREQUEST']._serialized_end=5535
  _globals['_LISTLINKSREQUEST']._serialized_start=5537
  _globals['_LISTLINKSREQUEST']._serialized_end=5657
  _globals['_LISTLINKSRESPONSE']._serialized_start=5659
  _globals['_LISTLINKSRESPONSE']._serialized_end=5743
  _globals['_GETLINKREQUEST']._serialized_start=5745
  _globals['_GETLINKREQUEST']._serialized_end=5812
  _globals['_LOGEXCLUSION']._serialized_start=5815
  _globals['_LOGEXCLUSION']._serialized_end=6265
  _globals['_LISTEXCLUSIONSREQUEST']._serialized_start=6268
  _globals['_LISTEXCLUSIONSREQUEST']._serialized_end=6401
  _globals['_LISTEXCLUSIONSRESPONSE']._serialized_start=6403
  _globals['_LISTEXCLUSIONSRESPONSE']._serialized_end=6505
  _globals['_GETEXCLUSIONREQUEST']._serialized_start=6507
  _globals['_GETEXCLUSIONREQUEST']._serialized_end=6587
  _globals['_CREATEEXCLUSIONREQUEST']._serialized_start=6590
  _globals['_CREATEEXCLUSIONREQUEST']._serialized_end=6732
  _globals['_UPDATEEXCLUSIONREQUEST']._serialized_start=6735
  _globals['_UPDATEEXCLUSIONREQUEST']._serialized_end=6929
  _globals['_DELETEEXCLUSIONREQUEST']._serialized_start=6931
  _globals['_DELETEEXCLUSIONREQUEST']._serialized_end=7014
  _globals['_GETCMEKSETTINGSREQUEST']._serialized_start=7016
  _globals['_GETCMEKSETTINGSREQUEST']._serialized_end=7099
  _globals['_UPDATECMEKSETTINGSREQUEST']._serialized_start=7102
  _globals['_UPDATECMEKSETTINGSREQUEST']._serialized_end=7263
  _globals['_CMEKSETTINGS']._serialized_start=7266
  _globals['_CMEKSETTINGS']._serialized_end=7583
  _globals['_GETSETTINGSREQUEST']._serialized_start=7585
  _globals['_GETSETTINGSREQUEST']._serialized_end=7660
  _globals['_UPDATESETTINGSREQUEST']._serialized_start=7663
  _globals['_UPDATESETTINGSREQUEST']._serialized_end=7811
  _globals['_SETTINGS']._serialized_start=7814
  _globals['_SETTINGS']._serialized_end=8152
  _globals['_COPYLOGENTRIESREQUEST']._serialized_start=8154
  _globals['_COPYLOGENTRIESREQUEST']._serialized_end=8243
  _globals['_COPYLOGENTRIESMETADATA']._serialized_start=8246
  _globals['_COPYLOGENTRIESMETADATA']._serialized_end=8548
  _globals['_COPYLOGENTRIESRESPONSE']._serialized_start=8550
  _globals['_COPYLOGENTRIESRESPONSE']._serialized_end=8608
  _globals['_BUCKETMETADATA']._serialized_start=8611
  _globals['_BUCKETMETADATA']._serialized_end=8928
  _globals['_LINKMETADATA']._serialized_start=8931
  _globals['_LINKMETADATA']._serialized_end=9238
  _globals['_LOCATIONMETADATA']._serialized_start=9240
  _globals['_LOCATIONMETADATA']._serialized_end=9289
  _globals['_CONFIGSERVICEV2']._serialized_start=9752
  _globals['_CONFIGSERVICEV2']._serialized_end=21175
