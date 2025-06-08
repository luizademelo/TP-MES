Here's the commented version of the code:

```c++
# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import re
from typing import AnyStr, Callable, Dict, Iterable, List, Optional, Union

from google.protobuf import struct_pb2
from grpc_observability._observability import OptionalLabelType
from grpc_observability._open_telemetry_plugin import OpenTelemetryLabelInjector
from grpc_observability._open_telemetry_plugin import OpenTelemetryPlugin
from grpc_observability._open_telemetry_plugin import OpenTelemetryPluginOption

from opentelemetry.metrics import MeterProvider
from opentelemetry.resourcedetector.gcp_resource_detector import (
    GoogleCloudResourceDetector,
)
from opentelemetry.sdk.resources import Resource
from opentelemetry.semconv.resource import ResourceAttributes

# Constants for CSM (Cloud Service Mesh) configuration
TRAFFIC_DIRECTOR_AUTHORITY = "traffic-director-global.xds.googleapis.com"
UNKNOWN_VALUE = "unknown"
TYPE_GCE = "gcp_compute_engine"  # Google Compute Engine resource type
TYPE_GKE = "gcp_kubernetes_engine"  # Google Kubernetes Engine resource type
MESH_ID_PREFIX = "mesh:"  # Prefix for mesh IDs

# Mapping of fixed metadata exchange keys between local and remote labels
METADATA_EXCHANGE_KEY_FIXED_MAP = {
    "type": "csm.remote_workload_type",
    "canonical_service": "csm.remote_workload_canonical_service",
}

# Mapping of GKE-specific metadata exchange keys
METADATA_EXCHANGE_KEY_GKE_MAP = {
    "workload_name": "csm.remote_workload_name",
    "namespace_name": "csm.remote_workload_namespace_name",
    "cluster_name": "csm.remote_workload_cluster_name",
    "location": "csm.remote_workload_location",
    "project_id": "csm.remote_workload_project_id",
}

# Mapping of GCE-specific metadata exchange keys
METADATA_EXCHANGE_KEY_GCE_MAP = {
    "workload_name": "csm.remote_workload_name",
    "location": "csm.remote_workload_location",
    "project_id": "csm.remote_workload_project_id",
}

class CSMOpenTelemetryLabelInjector(OpenTelemetryLabelInjector):
    """
    An implementation of OpenTelemetryLabelInjector for CSM (Cloud Service Mesh).
    
    This injector:
    - Fetches labels from GCP resource detector and environment variables
    - Handles serialization and deserialization of metadata exchange labels
    - Manages additional labels for CSM observability
    """

    _exchange_labels: Dict[str, AnyStr]  # Labels for metadata exchange
    _additional_exchange_labels: Dict[str, str]  # Additional CSM-specific labels

    def __init__(self):
        """Initializes the label injector by gathering resource information and setting up labels."""
        fields = {}
        self._exchange_labels = {}
        self._additional_exchange_labels = {}

        # Get values from environment variables with fallback to UNKNOWN_VALUE
        canonical_service_value = os.getenv(
            "CSM_CANONICAL_SERVICE_NAME", UNKNOWN_VALUE
        )
        workload_name_value = os.getenv("CSM_WORKLOAD_NAME", UNKNOWN_VALUE)
        mesh_id = os.getenv("CSM_MESH_ID", UNKNOWN_VALUE)

        # Detect GCP resource information
        gcp_resource = GoogleCloudResourceDetector().detect()
        resource_type_value = get_resource_type(gcp_resource)
        namespace_value = get_str_value_from_resource(
            ResourceAttributes.K8S_NAMESPACE_NAME, gcp_resource
        )
        cluster_name_value = get_str_value_from_resource(
            ResourceAttributes.K8S_CLUSTER_NAME, gcp_resource
        )

        # Get location (zone or region) and project ID
        location_value = get_str_value_from_resource("cloud.zone", gcp_resource)
        if UNKNOWN_VALUE == location_value:
            location_value = get_str_value_from_resource(
                ResourceAttributes.CLOUD_REGION, gcp_resource
            )
        project_id_value = get_str_value_from_resource(
            ResourceAttributes.CLOUD_ACCOUNT_ID, gcp_resource
        )

        # Populate fields based on resource type
        fields["type"] = struct_pb2.Value(string_value=resource_type_value)
        fields["canonical_service"] = struct_pb2.Value(
            string_value=canonical_service_value
        )
        
        # Add GKE-specific fields if resource is GKE
        if resource_type_value == TYPE_GKE:
            fields["workload_name"] = struct_pb2.Value(
                string_value=workload_name_value
            )
            fields["namespace_name"] = struct_pb2.Value(
                string_value=namespace_value
            )
            fields["cluster_name"] = struct_pb2.Value(
                string_value=cluster_name_value
            )
            fields["location"] = struct_pb2.Value(string_value=location_value)
            fields["project_id"] = struct_pb2.Value(
                string_value=project_id_value
            )
        # Add GCE-specific fields if resource is GCE
        elif resource_type_value == TYPE_GCE:
            fields["workload_name"] = struct_pb2.Value(
                string_value=workload_name_value
            )
            fields["location"] = struct_pb2.Value(string_value=location_value)
            fields["project_id"] = struct_pb2.Value(
                string_value=project_id_value
            )

        # Serialize the metadata for exchange
        serialized_struct = struct_pb2.Struct(fields=fields)
        serialized_str = serialized_struct.SerializeToString()

        self._exchange_labels = {"XEnvoyPeerMetadata": serialized_str}
        self._additional_exchange_labels[
            "csm.workload_canonical_service"
        ] = canonical_service_value
        self._additional_exchange_labels["csm.mesh_id"] = mesh_id

    def get_labels_for_exchange(self) -> Dict[str, AnyStr]:
        """Returns the labels to be exchanged with peers."""
        return self._exchange_labels

    def get_additional_labels(
        self, include_exchange_labels: bool
    ) -> Dict[str, str]:
        """
        Returns additional CSM-specific labels.
        
        Args:
            include_exchange_labels: Whether to include exchange labels in the output
            
        Returns:
            Dictionary of additional labels, optionally including exchange labels
        """
        if include_exchange_labels:
            return self._additional_exchange_labels
        else:
            return {}

    @staticmethod
    def deserialize_labels(labels: Dict[str, AnyStr]) -> Dict[str, AnyStr]:
        """
        Deserializes labels received from a peer into CSM-specific labels.
        
        Args:
            labels: Raw labels received from a peer
            
        Returns:
            Dictionary of deserialized CSM labels
        """
        deserialized_labels = {}
        for key, value in labels.items():
            if "XEnvoyPeerMetadata" == key:
                pb_struct = struct_pb2.Struct()
                pb_struct.ParseFromString(value)

                remote_type = get_value_from_struct("type", pb_struct)

                # Process fixed metadata fields
                for (
                    local_key,
                    remote_key,
                ) in METADATA_EXCHANGE_KEY_FIXED_MAP.items():
                    deserialized_labels[remote_key] = get_value_from_struct(
                        local_key, pb_struct
                    )
                
                # Process GKE-specific fields if remote is GKE
                if remote_type == TYPE_GKE:
                    for (
                        local_key,
                        remote_key,
                    ) in METADATA_EXCHANGE_KEY_GKE_MAP.items():
                        deserialized_labels[remote_key] = get_value_from_struct(
                            local_key, pb_struct
                        )
                # Process GCE-specific fields if remote is GCE
                elif remote_type == TYPE_GCE:
                    for (
                        local_key,
                        remote_key,
                    ) in METADATA_EXCHANGE_KEY_GCE_MAP.items():
                        deserialized_labels[remote_key] = get_value_from_struct(
                            local_key, pb_struct
                        )
            else:
                # Set unknown values for fixed fields if not present
                for _, remote_key in METADATA_EXCHANGE_KEY_FIXED_MAP.items():
                    deserialized_labels[remote_key] = UNKNOWN_VALUE
                deserialized_labels[key] = value

        return deserialized_labels

class CsmOpenTelemetryPluginOption(OpenTelemetryPluginOption):
    """
    An implementation of OpenTelemetryPluginOption for CSM observability.
    
    This plugin option determines when CSM observability should be active
    and provides the label injector for CSM-specific labels.
    """

    _label_injector: CSMOpenTelemetryLabelInjector

    def __init__(self):
        """Initializes the plugin option with a CSM label injector."""
        self._label_injector = CSMOpenTelemetryLabelInjector()

    @staticmethod
    def is_active_on_client_channel(target: str) -> bool:
        """Determines whether this plugin option is active on a client channel.
        
        Args:
            target: The target for the RPC (e.g., "xds:///service")
            
        Returns:
            True if this plugin option should be active on the channel, False otherwise
        """
        if not target.startswith("xds:"):
            return False
        # Check if the authority matches Traffic Director
        authority_pattern = r"^xds:\/\/([^/]+)"
        match = re.search(authority_pattern, target)
        if match:
            return TRAFFIC_DIRECTOR_AUTHORITY in match.group(1)
        else:
            # Active if authority doesn't exist (default case)
            return True

    @staticmethod
    def is_active_on_server(
        xds: bool,
    ) -> bool:
        """Determines whether this plugin option is active on a server.
        
        Note: Always returns True since servers can be part of the mesh even if not xDS-enabled.
        
        Args:
            xds: Whether the server is xDS-enabled
            
        Returns:
            Always returns True for CSM observability
        """
        return True

    def get_label_injector(self) -> OpenTelemetryLabelInjector:
        """Returns the CSM label injector for this plugin option."""
        return self._label_injector

class CsmOpenTelemetryPlugin(OpenTelemetryPlugin):
    """Implementation of OpenTelemetryPlugin for CSM observability.
    
    This plugin integrates CSM observability into gRPC's OpenTelemetry instrumentation.
    Note: This is part of an EXPERIMENTAL API.
    """

    plugin_options: Iterable[OpenTelemetryPluginOption]
    meter_provider: Optional[MeterProvider]
    generic_method_attribute_filter: Callable[[str], bool]

    def __init__(
        self,
        *,
        plugin_options: Iterable[OpenTelemetryPluginOption] = [],
        meter_provider: Optional[MeterProvider] = None,
        generic_method_attribute_filter: Optional[Callable[[str], bool]] = None,
    ):
        """Initializes the CSM OpenTelemetry plugin.
        
        Args:
            plugin_options: Existing plugin options to combine with CSM options
            meter_provider: OpenTelemetry MeterProvider for metrics
            generic_method_attribute_filter: Filter for method attributes
        """
        new_options = list(plugin_options) + [CsmOpenTelemetryPluginOption()]
        super().__init__(
            plugin_options=new_options,
            meter_provider=meter_provider,
            generic_method_attribute_filter=generic_method_attribute_filter,
        )

    def _get_enabled_optional_labels(self) -> List[OptionalLabelType]:
        """Returns the list of optional labels enabled for CSM observability."""
        return [OptionalLabelType.XDS_SERVICE_LABELS]

def get_value_from_struct(key: str, struct: struct_pb2.Struct) -> str:
    """Extracts a string value from a protobuf Struct.
    
    Args:
        key: The key to look up in the struct
        struct: The protobuf Struct to search
        
    Returns:
        The string value or UNKNOWN_VALUE if not found
    """
    value = struct.fields.get(key)
    if not value:
        return UNKNOWN_VALUE
    return value.string_value

def get_str_value_from_resource(
    attribute: Union[ResourceAttributes, str], resource: Resource
) -> str:
    """Extracts a string value from a resource's attributes.
    
    Args:
        attribute: The attribute key to look up
        resource: The Resource object to search
        
    Returns:
        The string value or UNKNOWN_VALUE if not found
    """
    value = resource.attributes.get(attribute, UNKNOWN_VALUE)
    return str(value)

def get_resource_type(gcp_resource: Resource) -> str:
    """Determines the resource type from GCP resource attributes.
    
    Args:
        gcp_resource: The detected GCP resource
        
    Returns:
        The resource type (TYPE_GKE, TYPE_GCE, or the raw gcp.resource_type value)
    """
    gcp_resource_type = get_str_value_from_resource(
        "gcp.resource_type", gcp_resource
    )
    if gcp_resource_type == "gke_container":
        return TYPE_GKE
    elif gcp_resource_type == "gce_instance":
        return TYPE_GCE
    else:
        return gcp_resource_type
```