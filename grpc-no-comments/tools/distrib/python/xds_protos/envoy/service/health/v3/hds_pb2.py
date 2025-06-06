
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.cluster.v3 import cluster_pb2 as envoy_dot_config_dot_cluster_dot_v3_dot_cluster__pb2
from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.core.v3 import health_check_pb2 as envoy_dot_config_dot_core_dot_v3_dot_health__check__pb2
from envoy.config.endpoint.v3 import endpoint_components_pb2 as envoy_dot_config_dot_endpoint_dot_v3_dot_endpoint__components__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/service/health/v3/hds.proto\x12\x17\x65nvoy.service.health.v3\x1a%envoy/config/cluster/v3/cluster.proto\x1a\"envoy/config/core/v3/address.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\'envoy/config/core/v3/health_check.proto\x1a\x32\x65nvoy/config/endpoint/v3/endpoint_components.proto\x1a\x1cgoogle/api/annotations.proto\x1a\x1egoogle/protobuf/duration.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xb2\x01\n\nCapability\x12L\n\x16health_check_protocols\x18\x01 \x03(\x0e\x32,.envoy.service.health.v3.Capability.Protocol\"(\n\x08Protocol\x12\x08\n\x04HTTP\x10\x00\x12\x07\n\x03TCP\x10\x01\x12\t\n\x05REDIS\x10\x02:,\x9a\xc5\x88\x1e\'\n%envoy.service.discovery.v2.Capability\"\xad\x01\n\x12HealthCheckRequest\x12(\n\x04node\x18\x01 \x01(\x0b\x32\x1a.envoy.config.core.v3.Node\x12\x37\n\ncapability\x18\x02 \x01(\x0b\x32#.envoy.service.health.v3.Capability:4\x9a\xc5\x88\x1e/\n-envoy.service.discovery.v2.HealthCheckRequest\"\xb3\x01\n\x0e\x45ndpointHealth\x12\x34\n\x08\x65ndpoint\x18\x01 \x01(\x0b\x32\".envoy.config.endpoint.v3.Endpoint\x12\x39\n\rhealth_status\x18\x02 \x01(\x0e\x32\".envoy.config.core.v3.HealthStatus:0\x9a\xc5\x88\x1e+\n)envoy.service.discovery.v2.EndpointHealth\"\x8e\x01\n\x17LocalityEndpointsHealth\x12\x30\n\x08locality\x18\x01 \x01(\x0b\x32\x1e.envoy.config.core.v3.Locality\x12\x41\n\x10\x65ndpoints_health\x18\x02 \x03(\x0b\x32\'.envoy.service.health.v3.EndpointHealth\"\x83\x01\n\x16\x43lusterEndpointsHealth\x12\x14\n\x0c\x63luster_name\x18\x01 \x01(\t\x12S\n\x19locality_endpoints_health\x18\x02 \x03(\x0b\x32\x30.envoy.service.health.v3.LocalityEndpointsHealth\"\xf5\x01\n\x16\x45ndpointHealthResponse\x12N\n\x10\x65ndpoints_health\x18\x01 \x03(\x0b\x32\'.envoy.service.health.v3.EndpointHealthB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12Q\n\x18\x63luster_endpoints_health\x18\x02 \x03(\x0b\x32/.envoy.service.health.v3.ClusterEndpointsHealth:8\x9a\xc5\x88\x1e\x33\n1envoy.service.discovery.v2.EndpointHealthResponse\"\xac\x02\n*HealthCheckRequestOrEndpointHealthResponse\x12K\n\x14health_check_request\x18\x01 \x01(\x0b\x32+.envoy.service.health.v3.HealthCheckRequestH\x00\x12S\n\x18\x65ndpoint_health_response\x18\x02 \x01(\x0b\x32/.envoy.service.health.v3.EndpointHealthResponseH\x00:L\x9a\xc5\x88\x1eG\nEenvoy.service.discovery.v2.HealthCheckRequestOrEndpointHealthResponseB\x0e\n\x0crequest_type\"\xb1\x01\n\x11LocalityEndpoints\x12\x30\n\x08locality\x18\x01 \x01(\x0b\x32\x1e.envoy.config.core.v3.Locality\x12\x35\n\tendpoints\x18\x02 \x03(\x0b\x32\".envoy.config.endpoint.v3.Endpoint:3\x9a\xc5\x88\x1e.\n,envoy.service.discovery.v2.LocalityEndpoints\"\xfb\x02\n\x12\x43lusterHealthCheck\x12\x14\n\x0c\x63luster_name\x18\x01 \x01(\t\x12\x38\n\rhealth_checks\x18\x02 \x03(\x0b\x32!.envoy.config.core.v3.HealthCheck\x12\x46\n\x12locality_endpoints\x18\x03 \x03(\x0b\x32*.envoy.service.health.v3.LocalityEndpoints\x12W\n\x18transport_socket_matches\x18\x04 \x03(\x0b\x32\x35.envoy.config.cluster.v3.Cluster.TransportSocketMatch\x12>\n\x14upstream_bind_config\x18\x05 \x01(\x0b\x32 .envoy.config.core.v3.BindConfig:4\x9a\xc5\x88\x1e/\n-envoy.service.discovery.v2.ClusterHealthCheck\"\xc7\x01\n\x14HealthCheckSpecifier\x12J\n\x15\x63luster_health_checks\x18\x01 \x03(\x0b\x32+.envoy.service.health.v3.ClusterHealthCheck\x12+\n\x08interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration:6\x9a\xc5\x88\x1e\x31\n/envoy.service.discovery.v2.HealthCheckSpecifier\"\n\n\x08HdsDummy2\xd8\x02\n\x16HealthDiscoveryService\x12\x8d\x01\n\x11StreamHealthCheck\x12\x43.envoy.service.health.v3.HealthCheckRequestOrEndpointHealthResponse\x1a-.envoy.service.health.v3.HealthCheckSpecifier\"\x00(\x01\x30\x01\x12\xad\x01\n\x10\x46\x65tchHealthCheck\x12\x43.envoy.service.health.v3.HealthCheckRequestOrEndpointHealthResponse\x1a-.envoy.service.health.v3.HealthCheckSpecifier\"%\x82\xd3\xe4\x93\x02\x1f\"\x1a/v3/discovery:health_check:\x01*B\x84\x01\n%io.envoyproxy.envoy.service.health.v3B\x08HdsProtoP\x01ZGgithub.com/envoyproxy/go-control-plane/envoy/service/health/v3;healthv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.health.v3.hds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.service.health.v3B\010HdsProtoP\001ZGgithub.com/envoyproxy/go-control-plane/envoy/service/health/v3;healthv3\272\200\310\321\006\002\020\002'
  _CAPABILITY._options = None
  _CAPABILITY._serialized_options = b'\232\305\210\036\'\n%envoy.service.discovery.v2.Capability'
  _HEALTHCHECKREQUEST._options = None
  _HEALTHCHECKREQUEST._serialized_options = b'\232\305\210\036/\n-envoy.service.discovery.v2.HealthCheckRequest'
  _ENDPOINTHEALTH._options = None
  _ENDPOINTHEALTH._serialized_options = b'\232\305\210\036+\n)envoy.service.discovery.v2.EndpointHealth'
  _ENDPOINTHEALTHRESPONSE.fields_by_name['endpoints_health']._options = None
  _ENDPOINTHEALTHRESPONSE.fields_by_name['endpoints_health']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _ENDPOINTHEALTHRESPONSE._options = None
  _ENDPOINTHEALTHRESPONSE._serialized_options = b'\232\305\210\0363\n1envoy.service.discovery.v2.EndpointHealthResponse'
  _HEALTHCHECKREQUESTORENDPOINTHEALTHRESPONSE._options = None
  _HEALTHCHECKREQUESTORENDPOINTHEALTHRESPONSE._serialized_options = b'\232\305\210\036G\nEenvoy.service.discovery.v2.HealthCheckRequestOrEndpointHealthResponse'
  _LOCALITYENDPOINTS._options = None
  _LOCALITYENDPOINTS._serialized_options = b'\232\305\210\036.\n,envoy.service.discovery.v2.LocalityEndpoints'
  _CLUSTERHEALTHCHECK._options = None
  _CLUSTERHEALTHCHECK._serialized_options = b'\232\305\210\036/\n-envoy.service.discovery.v2.ClusterHealthCheck'
  _HEALTHCHECKSPECIFIER._options = None
  _HEALTHCHECKSPECIFIER._serialized_options = b'\232\305\210\0361\n/envoy.service.discovery.v2.HealthCheckSpecifier'
  _HEALTHDISCOVERYSERVICE.methods_by_name['FetchHealthCheck']._options = None
  _HEALTHDISCOVERYSERVICE.methods_by_name['FetchHealthCheck']._serialized_options = b'\202\323\344\223\002\037\"\032/v3/discovery:health_check:\001*'
  _globals['_CAPABILITY']._serialized_start=429
  _globals['_CAPABILITY']._serialized_end=607
  _globals['_CAPABILITY_PROTOCOL']._serialized_start=521
  _globals['_CAPABILITY_PROTOCOL']._serialized_end=561
  _globals['_HEALTHCHECKREQUEST']._serialized_start=610
  _globals['_HEALTHCHECKREQUEST']._serialized_end=783
  _globals['_ENDPOINTHEALTH']._serialized_start=786
  _globals['_ENDPOINTHEALTH']._serialized_end=965
  _globals['_LOCALITYENDPOINTSHEALTH']._serialized_start=968
  _globals['_LOCALITYENDPOINTSHEALTH']._serialized_end=1110
  _globals['_CLUSTERENDPOINTSHEALTH']._serialized_start=1113
  _globals['_CLUSTERENDPOINTSHEALTH']._serialized_end=1244
  _globals['_ENDPOINTHEALTHRESPONSE']._serialized_start=1247
  _globals['_ENDPOINTHEALTHRESPONSE']._serialized_end=1492
  _globals['_HEALTHCHECKREQUESTORENDPOINTHEALTHRESPONSE']._serialized_start=1495
  _globals['_HEALTHCHECKREQUESTORENDPOINTHEALTHRESPONSE']._serialized_end=1795
  _globals['_LOCALITYENDPOINTS']._serialized_start=1798
  _globals['_LOCALITYENDPOINTS']._serialized_end=1975
  _globals['_CLUSTERHEALTHCHECK']._serialized_start=1978
  _globals['_CLUSTERHEALTHCHECK']._serialized_end=2357
  _globals['_HEALTHCHECKSPECIFIER']._serialized_start=2360
  _globals['_HEALTHCHECKSPECIFIER']._serialized_end=2559
  _globals['_HDSDUMMY']._serialized_start=2561
  _globals['_HDSDUMMY']._serialized_end=2571
  _globals['_HEALTHDISCOVERYSERVICE']._serialized_start=2574
  _globals['_HEALTHDISCOVERYSERVICE']._serialized_end=2918
