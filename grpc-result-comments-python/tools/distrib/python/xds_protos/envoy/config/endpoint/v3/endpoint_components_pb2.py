Here's the commented version of the code:

```python
"""Generated protocol buffer code."""
# Import necessary Protocol Buffer modules and dependencies
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

# Initialize the symbol database for Protocol Buffers
_sym_db = _symbol_database.Default()

# Import dependent Protocol Buffer definitions
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import config_source_pb2 as envoy_dot_config_dot_core_dot_v3_dot_config__source__pb2
from envoy.config.core.v3 import health_check_pb2 as envoy_dot_config_dot_core_dot_v3_dot_health__check__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

# Define the Protocol Buffer descriptor by adding the serialized file
# This contains all the message definitions and their fields
DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2envoy/config/endpoint/v3/endpoint_components.proto\x12\x18\x65nvoy.config.endpoint.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a(envoy/config/core/v3/config_source.proto\x1a\'envoy/config/core/v3/health_check.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xb4\x04\n\x08\x45ndpoint\x12.\n\x07\x61\x64\x64ress\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12Q\n\x13health_check_config\x18\x02 \x01(\x0b\x32\x34.envoy.config.endpoint.v3.Endpoint.HealthCheckConfig\x12\x10\n\x08hostname\x18\x03 \x01(\t\x12R\n\x14\x61\x64\x64itional_addresses\x18\x04 \x03(\x0b\x32\x34.envoy.config.endpoint.v3.Endpoint.AdditionalAddress\x1a\xd2\x01\n\x11HealthCheckConfig\x12\x1d\n\nport_value\x18\x01 \x01(\rB\t\xfa\x42\x06*\x04\x18\xff\xff\x03\x12\x10\n\x08hostname\x18\x02 \x01(\t\x12.\n\x07\x61\x64\x64ress\x18\x03 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12#\n\x1b\x64isable_active_health_check\x18\x04 \x01(\x08:7\x9a\xc5\x88\x1e\x32\n0envoy.api.v2.endpoint.Endpoint.HealthCheckConfig\x1a\x43\n\x11\x41\x64\x64itionalAddress\x12.\n\x07\x61\x64\x64ress\x18\x01 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.api.v2.endpoint.Endpoint\"\xcc\x02\n\nLbEndpoint\x12\x36\n\x08\x65ndpoint\x18\x01 \x01(\x0b\x32\".envoy.config.endpoint.v3.EndpointH\x00\x12\x17\n\rendpoint_name\x18\x05 \x01(\tH\x00\x12\x39\n\rhealth_status\x18\x02 \x01(\x0e\x32\".envoy.config.core.v3.HealthStatus\x12\x30\n\x08metadata\x18\x03 \x01(\x0b\x32\x1e.envoy.config.core.v3.Metadata\x12\x44\n\x15load_balancing_weight\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(\x01:\'\x9a\xc5\x88\x1e\"\n envoy.api.v2.endpoint.LbEndpointB\x11\n\x0fhost_identifier\"r\n\x19LedsClusterLocalityConfig\x12\x37\n\x0bleds_config\x18\x01 \x01(\x0b\x32\".envoy.config.core.v3.ConfigSource\x12\x1c\n\x14leds_collection_name\x18\x02 \x01(\t\"\x93\x05\n\x13LocalityLbEndpoints\x12\x30\n\x08locality\x18\x01 \x01(\x0b\x32\x1e.envoy.config.core.v3.Locality\x12\x30\n\x08metadata\x18\t \x01(\x0b\x32\x1e.envoy.config.core.v3.Metadata\x12:\n\x0clb_endpoints\x18\x02 \x03(\x0b\x32$.envoy.config.endpoint.v3.LbEndpoint\x12_\n\x17load_balancer_endpoints\x18\x07 \x01(\x0b\x32<.envoy.config.endpoint.v3.LocalityLbEndpoints.LbEndpointListH\x00\x12[\n\x1cleds_cluster_locality_config\x18\x08 \x01(\x0b\x32\x33.envoy.config.endpoint.v3.LedsClusterLocalityConfigH\x00\x12\x44\n\x15load_balancing_weight\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(\x01\x12\x1a\n\x08priority\x18\x05 \x01(\rB\x08\xfa\x42\x05*\x03\x18\x80\x01\x12/\n\tproximity\x18\x06 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x1aL\n\x0eLbEndpointList\x12:\n\x0clb_endpoints\x18\x01 \x03(\x0b\x32$.envoy.config.endpoint.v3.LbEndpoint:0\x9a\xc5\x88\x1e+\n)envoy.api.v2.endpoint.LocalityLbEndpointsB\x0b\n\tlb_configB\x97\x01\n&io.envoyproxy.envoy.config.endpoint.v3B\x17\x45ndpointComponentsProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/config/endpoint/v3;endpointv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

# Build message and enum descriptors from the descriptor
_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.endpoint.v3.endpoint_components_pb2', _globals)

# Set descriptor options if not using C++ descriptors
if _descriptor._USE_C_DESCRIPTORS == False:
    # Set package and import path options
    DESCRIPTOR._options = None
    DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.config.endpoint.v3B\027EndpointComponentsProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/config/endpoint/v3;endpointv3\272\200\310\321\006\002\020\002'
    
    # Set field options for various messages
    _ENDPOINT_HEALTHCHECKCONFIG.fields_by_name['port_value']._options = None
    _ENDPOINT_HEALTHCHECKCONFIG.fields_by_name['port_value']._serialized_options = b'\372B\006*\004\030\377\377\003'
    _ENDPOINT_HEALTHCHECKCONFIG._options = None
    _ENDPOINT_HEALTHCHECKCONFIG._serialized_options = b'\232\305\210\0362\n0envoy.api.v2.endpoint.Endpoint.HealthCheckConfig'
    
    _ENDPOINT._options = None
    _ENDPOINT._serialized_options = b'\232\305\210\036 \n\036envoy.api.v2.endpoint.Endpoint'
    
    _LBENDPOINT.fields_by_name['load_balancing_weight']._options = None
    _LBENDPOINT.fields_by_name['load_balancing_weight']._serialized_options = b'\372B\004*\002(\001'
    _LBENDPOINT._options = None
    _LBENDPOINT._serialized_options = b'\232\305\210\036\"\n envoy.api.v2.endpoint.LbEndpoint'
    
    _LOCALITYLBENDPOINTS.fields_by_name['load_balancing_weight']._options = None
    _LOCALITYLBENDPOINTS.fields_by_name['load_balancing_weight']._serialized_options = b'\372B\004*\002(\001'
    _LOCALITYLBENDPOINTS.fields_by_name['priority']._options = None
    _LOCALITYLBENDPOINTS.fields_by_name['priority']._serialized_options = b'\372B\005*\003\030\200\001'
    _LOCALITYLBENDPOINTS._options = None
    _LOCALITYLBENDPOINTS._serialized_options = b'\232\305\210\036+\n)envoy.api.v2.endpoint.LocalityLbEndpoints'
    
    # Define serialized start and end positions for each message
    _globals['_ENDPOINT']._serialized_start=356
    _globals['_ENDPOINT']._serialized_end=920
    _globals['_ENDPOINT_HEALTHCHECKCONFIG']._serialized_start=602
    _globals['_ENDPOINT_HEALTHCHECKCONFIG']._serialized_end=812
    _globals['_ENDPOINT_ADDITIONALADDRESS']._serialized_start=814
    _globals['_ENDPOINT_ADDITIONALADDRESS']._serialized_end=881
    _globals['_LBENDPOINT']._serialized_start=923
    _globals['_LBENDPOINT']._serialized_end=1255
    _globals['_LEDSCLUSTERLOCALITYCONFIG']._serialized_start=1257
    _globals['_LEDSCLUSTERLOCALITYCONFIG']._serialized_end=1371
    _globals['_LOCALITYLBENDPOINTS']._serialized_start=1374
    _globals['_LOCALITYLBENDPOINTS']._serialized_end=2033
    _globals['_LOCALITYLBENDPOINTS_LBENDPOINTLIST']._serialized_start=1894
    _globals['_LOCALITYLBENDPOINTS_LBENDPOINTLIST']._serialized_end=1970
```