Here's the commented version of the code:

```python
# Copyright 2023 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import logging
import threading
import time
from typing import Any, AnyStr, Dict, Iterable, List, Optional, Set, Union

import grpc

# Import observability related modules
from grpc_observability import _cyobservability
from grpc_observability import _observability
from grpc_observability import _open_telemetry_measures
from grpc_observability._cyobservability import MetricsName
from grpc_observability._cyobservability import PLUGIN_IDENTIFIER_SEP
from grpc_observability._observability import OptionalLabelType
from grpc_observability._observability import StatsData
from opentelemetry.metrics import Counter
from opentelemetry.metrics import Histogram
from opentelemetry.metrics import Meter

# Logger for this module
_LOGGER = logging.getLogger(__name__)

# Type aliases for better code readability
ClientCallTracerCapsule = Any
ServerCallTracerFactoryCapsule = Any
grpc_observability = Any
OpenTelemetryPlugin = Any
OpenTelemetryPluginOption = Any

# Constants for gRPC metrics and labels
GRPC_METHOD_LABEL = "grpc.method"
GRPC_TARGET_LABEL = "grpc.target"
GRPC_CLIENT_METRIC_PREFIX = "grpc.client"
GRPC_OTHER_LABEL_VALUE = "other"

# Thread-safe lock for observability operations
_observability_lock: threading.RLock = threading.RLock()
# Global instance of OpenTelemetry observability
_OPEN_TELEMETRY_OBSERVABILITY: Optional["OpenTelemetryObservability"] = None

# Mapping of gRPC status codes to their string representations
GRPC_STATUS_CODE_TO_STRING = {
    grpc.StatusCode.OK: "OK",
    grpc.StatusCode.CANCELLED: "CANCELLED",
    grpc.StatusCode.UNKNOWN: "UNKNOWN",
    grpc.StatusCode.INVALID_ARGUMENT: "INVALID_ARGUMENT",
    grpc.StatusCode.DEADLINE_EXCEEDED: "DEADLINE_EXCEEDED",
    grpc.StatusCode.NOT_FOUND: "NOT_FOUND",
    grpc.StatusCode.ALREADY_EXISTS: "ALREADY_EXISTS",
    grpc.StatusCode.PERMISSION_DENIED: "PERMISSION_DENIED",
    grpc.StatusCode.UNAUTHENTICATED: "UNAUTHENTICATED",
    grpc.StatusCode.RESOURCE_EXHAUSTED: "RESOURCE_EXHAUSTED",
    grpc.StatusCode.FAILED_PRECONDITION: "FAILED_PRECONDITION",
    grpc.StatusCode.ABORTED: "ABORTED",
    grpc.StatusCode.OUT_OF_RANGE: "OUT_OF_RANGE",
    grpc.StatusCode.UNIMPLEMENTED: "UNIMPLEMENTED",
    grpc.StatusCode.INTERNAL: "INTERNAL",
    grpc.StatusCode.UNAVAILABLE: "UNAVAILABLE",
    grpc.StatusCode.DATA_LOSS: "DATA_LOSS",
}

class _OpenTelemetryPlugin:
    """Class representing an OpenTelemetry plugin for gRPC observability."""
    
    _plugin: OpenTelemetryPlugin
    _metric_to_recorder: Dict[MetricsName, Union[Counter, Histogram]]
    _enabled_client_plugin_options: Optional[List[OpenTelemetryPluginOption]]
    _enabled_server_plugin_options: Optional[List[OpenTelemetryPluginOption]]
    identifier: str

    def __init__(self, plugin: OpenTelemetryPlugin):
        """Initialize the OpenTelemetry plugin with the given plugin configuration."""
        self._plugin = plugin
        self._metric_to_recorder = dict()
        self.identifier = str(id(self))  # Unique identifier for this plugin
        self._enabled_client_plugin_options = None
        self._enabled_server_plugin_options = None

        # Set up metrics recording if meter provider is available
        meter_provider = self._plugin.meter_provider
        if meter_provider:
            meter = meter_provider.get_meter("grpc-python", grpc.__version__)
            enabled_metrics = _open_telemetry_measures.base_metrics()
            self._metric_to_recorder = self._register_metrics(
                meter, enabled_metrics
            )

    def _should_record(self, stats_data: StatsData) -> bool:
        """Check if the given stats data should be recorded by this plugin."""
        return stats_data.name in self._metric_to_recorder.keys()

    def _record_stats_data(self, stats_data: StatsData) -> None:
        """Record the given stats data using the appropriate metric recorder."""
        recorder = self._metric_to_recorder[stats_data.name]
        enabled_plugin_options = []
        if GRPC_CLIENT_METRIC_PREFIX in recorder.name:
            enabled_plugin_options = self._enabled_client_plugin_options
        else:
            enabled_plugin_options = self._enabled_server_plugin_options

        # Process labels based on whether exchange labels should be included
        if stats_data.include_exchange_labels:
            deserialized_labels = self._deserialize_labels(
                stats_data.labels, enabled_plugin_options
            )
        else:
            deserialized_labels = stats_data.labels
        labels = self._maybe_add_labels(
            stats_data.include_exchange_labels,
            deserialized_labels,
            enabled_plugin_options,
        )
        decoded_labels = self.decode_labels(labels)

        # Apply filters to target and method labels
        target = decoded_labels.get(GRPC_TARGET_LABEL, "")
        if not self._plugin.target_attribute_filter(target):
            decoded_labels[GRPC_TARGET_LABEL] = GRPC_OTHER_LABEL_VALUE

        method = decoded_labels.get(GRPC_METHOD_LABEL, "")
        if not (
            stats_data.registered_method
            or self._plugin.generic_method_attribute_filter(method)
        ):
            decoded_labels[GRPC_METHOD_LABEL] = GRPC_OTHER_LABEL_VALUE

        # Record the metric value
        value = 0
        if stats_data.measure_double:
            value = stats_data.value_float
        else:
            value = stats_data.value_int
        if isinstance(recorder, Counter):
            recorder.add(value, attributes=decoded_labels)
        elif isinstance(recorder, Histogram):
            recorder.record(value, attributes=decoded_labels)

    def maybe_record_stats_data(self, stats_data: List[StatsData]) -> None:
        """Conditionally record stats data if it should be recorded by this plugin."""
        if self._should_record(stats_data):
            self._record_stats_data(stats_data)

    def get_client_exchange_labels(self) -> Dict[str, AnyStr]:
        """Get labels used for client side Metadata Exchange."""
        labels_for_exchange = {}
        for plugin_option in self._enabled_client_plugin_options:
            if hasattr(plugin_option, "get_label_injector") and hasattr(
                plugin_option.get_label_injector(), "get_labels_for_exchange"
            ):
                labels_for_exchange.update(
                    plugin_option.get_label_injector().get_labels_for_exchange()
                )
        return labels_for_exchange

    def get_server_exchange_labels(self) -> Dict[str, str]:
        """Get labels used for server side Metadata Exchange."""
        labels_for_exchange = {}
        for plugin_option in self._enabled_server_plugin_options:
            if hasattr(plugin_option, "get_label_injector") and hasattr(
                plugin_option.get_label_injector(), "get_labels_for_exchange"
            ):
                labels_for_exchange.update(
                    plugin_option.get_label_injector().get_labels_for_exchange()
                )
        return labels_for_exchange

    def activate_client_plugin_options(self, target: bytes) -> None:
        """Activate client plugin options based on the target channel."""
        target_str = target.decode("utf-8", "replace")
        if not self._enabled_client_plugin_options:
            self._enabled_client_plugin_options = []
            for plugin_option in self._plugin.plugin_options:
                if hasattr(
                    plugin_option, "is_active_on_client_channel"
                ) and plugin_option.is_active_on_client_channel(target_str):
                    self._enabled_client_plugin_options.append(plugin_option)

    def activate_server_plugin_options(self, xds: bool) -> None:
        """Activate server plugin options based on whether XDS is enabled."""
        if not self._enabled_server_plugin_options:
            self._enabled_server_plugin_options = []
            for plugin_option in self._plugin.plugin_options:
                if hasattr(
                    plugin_option, "is_active_on_server"
                ) and plugin_option.is_active_on_server(xds):
                    self._enabled_server_plugin_options.append(plugin_option)

    @staticmethod
    def _deserialize_labels(
        labels: Dict[str, AnyStr],
        enabled_plugin_options: List[OpenTelemetryPluginOption],
    ) -> Dict[str, AnyStr]:
        """Deserialize labels using the enabled plugin options."""
        for plugin_option in enabled_plugin_options:
            if all(
                [
                    hasattr(plugin_option, "get_label_injector"),
                    hasattr(
                        plugin_option.get_label_injector(), "deserialize_labels"
                    ),
                ]
            ):
                labels = plugin_option.get_label_injector().deserialize_labels(
                    labels
                )
        return labels

    @staticmethod
    def _maybe_add_labels(
        include_exchange_labels: bool,
        labels: Dict[str, str],
        enabled_plugin_options: List[OpenTelemetryPluginOption],
    ) -> Dict[str, AnyStr]:
        """Add additional labels if needed using the enabled plugin options."""
        for plugin_option in enabled_plugin_options:
            if all(
                [
                    hasattr(plugin_option, "get_label_injector"),
                    hasattr(
                        plugin_option.get_label_injector(),
                        "get_additional_labels",
                    ),
                ]
            ):
                labels.update(
                    plugin_option.get_label_injector().get_additional_labels(
                        include_exchange_labels
                    )
                )
        return labels

    def get_enabled_optional_labels(self) -> List[OptionalLabelType]:
        """Get the list of enabled optional labels for this plugin."""
        return self._plugin._get_enabled_optional_labels()

    @staticmethod
    def _register_metrics(
        meter: Meter, metrics: List[_open_telemetry_measures.Metric]
    ) -> Dict[MetricsName, Union[Counter, Histogram]]:
        """Register all gRPC metrics with the OpenTelemetry meter."""
        metric_to_recorder_map = {}
        recorder = None
        for metric in metrics:
            if metric == _open_telemetry_measures.CLIENT_ATTEMPT_STARTED:
                recorder = meter.create_counter(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.CLIENT_ATTEMPT_DURATION:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.CLIENT_RPC_DURATION:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.CLIENT_ATTEMPT_SEND_BYTES:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif (
                metric == _open_telemetry_measures.CLIENT_ATTEMPT_RECEIVED_BYTES
            ):
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.SERVER_STARTED_RPCS:
                recorder = meter.create_counter(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.SERVER_RPC_DURATION:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.SERVER_RPC_SEND_BYTES:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            elif metric == _open_telemetry_measures.SERVER_RPC_RECEIVED_BYTES:
                recorder = meter.create_histogram(
                    name=metric.name,
                    unit=metric.unit,
                    description=metric.description,
                )
            metric_to_recorder_map[metric.cyname] = recorder
        return metric_to_recorder_map

    @staticmethod
    def decode_labels(labels: Dict[str, AnyStr]) -> Dict[str, str]:
        """Decode label values from bytes to strings if necessary."""
        decoded_labels = {}
        for key, value in labels.items():
            if isinstance(value, bytes):
                value = value.decode()
            decoded_labels[key] = value
        return decoded_labels

def start_open_telemetry_observability(
    *,
    plugins: Iterable[_OpenTelemetryPlugin],
) -> None:
    """Start OpenTelemetry observability with the given plugins."""
    _start_open_telemetry_observability(
        OpenTelemetryObservability(plugins=plugins)
    )

def end_open_telemetry_observability() -> None:
    """End OpenTelemetry observability."""
    _end_open_telemetry_observability()

class _OpenTelemetryExporterDelegator(_observability.Exporter):
    """Delegates observability data export to multiple OpenTelemetry plugins."""
    
    _plugins: Iterable[_OpenTelemetryPlugin]

    def __init__(self, plugins: Iterable[_OpenTelemetryPlugin]):
        """Initialize with the given plugins."""
        self._plugins = plugins

    def export_stats_data(
        self, stats_data: List[_observability.StatsData]
    ) -> None:
        """Export stats data to all registered plugins."""
        for data in stats_data:
            for plugin in self._plugins:
                plugin.maybe_record_stats_data(data)

    def export_tracing_data(
        self, tracing_data: List[_observability.TracingData]
    ) -> None:
        """Export tracing data (currently not implemented)."""
        pass

class OpenTelemetryObservability(grpc._observability.ObservabilityPlugin):
    """OpenTelemetry based plugin implementation for gRPC observability.

    This is class is part of an EXPERIMENTAL API.

    Args:
      plugins: _OpenTelemetryPlugins to enable.
    """

    _exporter: "grpc_observability.Exporter"
    _plugins: List[_OpenTelemetryPlugin]
    _registered_method: Set[bytes]
    _client_option_activated: bool
    _server_option_activated: bool

    def __init__(
        self,
        *,
        plugins: Optional[Iterable[_OpenTelemetryPlugin]],
    ):
        """Initialize the OpenTelemetry observability plugin."""
        self._exporter = _OpenTelemetryExporterDelegator(plugins)
        self._registered_methods = set()
        self._plugins = plugins
        self._client_option_activated = False
        self._server_option_activated = False

    def observability_init(self):
        """Initialize observability features."""
        try:
            _cyobservability.activate_stats()
            self.set_stats(True)
        except Exception as e:
            raise ValueError(f"Activate observability metrics failed with: {e}")

        try:
            _cyobservability.cyobservability_init(self._exporter)
        except Exception as e:
            _LOGGER.exception("Initiate observability failed with: %s", e)

        grpc._observability.observability_init(self)

    def observability_deinit(self) -> None:
        """Deinitialize observability features."""
        time.sleep(_cyobservability.CENSUS_EXPORT_BATCH_INTERVAL_SECS)
        self.set_tracing(False)
        self.set_stats(False)
        _cyobservability.observability_deinit()
        grpc._observability.observability_deinit()

    def create_client_call_tracer(
        self, method_name: bytes, target: bytes
    ) -> ClientCallTracerCapsule:
        """Create a client call tracer for the given method and target."""
        trace_id = b"TRACE_ID"
        self._maybe_activate_client_plugin_options(target)
        exchange_labels = self._get_client_exchange_labels()
        enabled_optional_labels = set()
        for plugin in self._plugins:
            enabled_optional_labels.update(plugin.get_enabled_optional_labels())

        capsule = _cyobservability.create_client_call_tracer(
            method_name,
            target,
            trace_id,
            self._get_identifier(),
            exchange_labels,
            enabled_optional_labels,
            method_name in self._registered_methods,
        )
        return capsule

    def create_server_call_tracer_factory(
        self,
        *,
        xds: bool = False,
    ) -> Optional[ServerCallTracerFactoryCapsule]:
        """Create a server call tracer factory."""
        capsule = None
        self._maybe_activate_server_plugin_options(xds)
        exchange_labels = self._get_server_exchange_labels()
        capsule = _cyobservability.create_server_call_tracer_factory_capsule(
            exchange_labels, self._get_identifier()
        )
        return capsule

    def save_trace_context(
        self, trace_id: str, span_id: str, is_sampled: bool
    ) -> None:
        """Save trace context (currently not implemented)."""
        pass

    def record_rpc_latency(
        self,
        method: str,
        target: str,
        rpc_latency: float,
        status_code: grpc.StatusCode,
    ) -> None:
        """Record RPC latency metrics."""
        status_code = GRPC_STATUS_CODE_TO_STRING.get(status_code, "UNKNOWN")