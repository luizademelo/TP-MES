Here's the commented version of the code:

```c++
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependencies from other proto files
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

# Define the protocol buffer descriptor by adding the serialized file
# This contains the binary representation of the proto file and its messages
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n envoy/admin/v3/server_info.proto\x12\x0e\x65nvoy.admin.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xb6\x03\n\nServerInfo\x12\x0f\n\x07version\x18\x01 \x01(\t\x12/\n\x05state\x18\x02 \x01(\x0e\x32 .envoy.admin.v3.ServerInfo.State\x12\x37\n\x14uptime_current_epoch\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x34\n\x11uptime_all_epochs\x18\x04 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x1b\n\x13hot_restart_version\x18\x05 \x01(\t\x12@\n\x14\x63ommand_line_options\x18\x06 \x01(\x0b\x32\".envoy.admin.v3.CommandLineOptions\x12(\n\x04node\x18\x07 \x01(\x0b\x32\x1a.envoy.config.core.v3.Node\"G\n\x05State\x12\x08\n\x04LIVE\x10\x00\x12\x0c\n\x08\x44RAINING\x10\x01\x12\x14\n\x10PRE_INITIALIZING\x10\x02\x12\x10\n\x0cINITIALIZING\x10\x03:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.admin.v2alpha.ServerInfo\"\xab\x0b\n\x12\x43ommandLineOptions\x12\x0f\n\x07\x62\x61se_id\x18\x01 \x01(\x04\x12\x1b\n\x13use_dynamic_base_id\x18\x1f \x01(\x08\x12%\n\x1dskip_hot_restart_on_no_parent\x18\' \x01(\x08\x12%\n\x1dskip_hot_restart_parent_stats\x18( \x01(\x08\x12\x14\n\x0c\x62\x61se_id_path\x18  \x01(\t\x12\x13\n\x0b\x63oncurrency\x18\x02 \x01(\r\x12\x13\n\x0b\x63onfig_path\x18\x03 \x01(\t\x12\x13\n\x0b\x63onfig_yaml\x18\x04 \x01(\t\x12#\n\x1b\x61llow_unknown_static_fields\x18\x05 \x01(\x08\x12%\n\x1dreject_unknown_dynamic_fields\x18\x1a \x01(\x08\x12%\n\x1dignore_unknown_dynamic_fields\x18\x1e \x01(\x08\x12\x1c\n\x14skip_deprecated_logs\x18) \x01(\x08\x12\x1a\n\x12\x61\x64min_address_path\x18\x06 \x01(\t\x12N\n\x18local_address_ip_version\x18\x07 \x01(\x0e\x32,.envoy.admin.v3.CommandLineOptions.IpVersion\x12\x11\n\tlog_level\x18\x08 \x01(\t\x12\x1b\n\x13\x63omponent_log_level\x18\t \x01(\t\x12\x12\n\nlog_format\x18\n \x01(\t\x12\x1a\n\x12log_format_escaped\x18\x1b \x01(\x08\x12\x10\n\x08log_path\x18\x0b \x01(\t\x12\x17\n\x0fservice_cluster\x18\r \x01(\t\x12\x14\n\x0cservice_node\x18\x0e \x01(\t\x12\x14\n\x0cservice_zone\x18\x0f \x01(\t\x12\x36\n\x13\x66ile_flush_interval\x18\x10 \x01(\x0b\x32\x19.google.protobuf.Duration\x12-\n\ndrain_time\x18\x11 \x01(\x0b\x32\x19.google.protobuf.Duration\x12H\n\x0e\x64rain_strategy\x18! \x01(\x0e\x32\x30.envoy.admin.v3.CommandLineOptions.DrainStrategy\x12\x37\n\x14parent_shutdown_time\x18\x12 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x35\n\x04mode\x18\x13 \x01(\x0e\x32\'.envoy.admin.v3.CommandLineOptions.Mode\x12\x1b\n\x13\x64isable_hot_restart\x18\x16 \x01(\x08\x12\x1c\n\x14\x65nable_mutex_tracing\x�\x17 \x01(\x08\x12\x15\n\rrestart_epoch\x18\x18 \x01(\r\x12\x16\n\x0e\x63puset_threads\x18\x19 \x01(\x08\x12\x1b\n\x13\x64isabled_extensions\x18\x1c \x03(\t\x12!\n\x19\x65nable_fine_grain_logging\x18\" \x01(\x08\x12\x13\n\x0bsocket_path\x18# \x01(\t\x12\x13\n\x0bsocket_mode\x18$ \x01(\r\x12\x18\n\x10\x65nable_core_dump\x18% \x01(\x08\x12\x11\n\tstats_tag\x18& \x03(\t\"\x1b\n\tIpVersion\x12\x06\n\x02v4\x10\x00\x12\x06\n\x02v6\x10\x01\"-\n\x04Mode\x12\t\n\x05Serve\x10\x00\x12\x0c\n\x08Validate\x10\x01\x12\x0c\n\x08InitOnly\x10\x02\"+\n\rDrainStrategy\x12\x0b\n\x07Gradual\x10\x00\x12\r\n\tImmediate\x10\x01:-\x9a\xc5\x88\x1e(\n&envoy.admin.v2alpha.CommandLineOptionsJ\x04\x08\x0c\x10\rJ\x04\x08\x14\x10\x15J\x04\x08\x15\x10\x16J\x04\x08\x1d\x10\x1eR\tmax_statsR\x10max_obj_name_lenR\x11\x62ootstrap_versionBx\n\x1cio.envoyproxy.envoy.admin.v3B\x0fServerInfoProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build the message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.server_info_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\017ServerInfoProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
  _SERVERINFO._options = None
  _SERVERINFO._serialized_options = b'\232\305\210\036 \n\036envoy.admin.v2alpha.ServerInfo'
  _COMMANDLINEOPTIONS._options = None
  _COMMANDLINEOPTIONS._serialized_options = b'\232\305\210\036(\n&envoy.admin.v2alpha.CommandLineOptions'
  
  # Define serialized start and end positions for each message and enum
  _globals['_SERVERINFO']._serialized_start=184
  _globals['_SERVERINFO']._serialized_end=622
  _globals['_SERVERINFO_STATE']._serialized_start=512
  _globals['_SERVERINFO_STATE']._serialized_end=583
  _globals['_COMMANDLINEOPTIONS']._serialized_start=625
  _globals['_COMMANDLINEOPTIONS']._serialized_end=2076
  _globals['_COMMANDLINEOPTIONS_IPVERSION']._serialized_start=1838
  _globals['_COMMANDLINEOPTIONS_IPVERSION']._serialized_end=1865
  _globals['_COMMANDLINEOPTIONS_MODE']._serialized_start=1867
  _globals['_COMMANDLINEOPTIONS_MODE']._serialized_end=1912
  _globals['_COMMANDLINEOPTIONS_DRAINSTRATEGY']._serialized_start=1914
  _globals['_COMMANDLINEOPTIONS_DRAINSTRATEGY']._serialized_end=1957
```