Here's the commented version of the code:

```python
# Copyright 2024 gRPC authors.
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

# Import required modules
from collections import defaultdict
import datetime
import logging
import os
import sys
import time
from typing import Any, AnyStr, Callable, Dict, List, Optional, Set
import unittest

from google.protobuf import struct_pb2
import grpc_observability
from grpc_observability import _open_telemetry_measures
from grpc_observability._open_telemetry_plugin import OpenTelemetryLabelInjector
from grpc_observability._open_telemetry_plugin import OpenTelemetryPluginOption
from opentelemetry.sdk.metrics import MeterProvider
from opentelemetry.sdk.metrics.export import AggregationTemporality
from opentelemetry.sdk.metrics.export import MetricExportResult
from opentelemetry.sdk.metrics.export import MetricExporter
from opentelemetry.sdk.metrics.export import MetricsData
from opentelemetry.sdk.metrics.export import PeriodicExportingMetricReader

from tests.observability import _test_server

# Initialize logger
logger = logging.getLogger(__name__)

# Constants
STREAM_LENGTH = 5  # Length of stream for testing
OTEL_EXPORT_INTERVAL_S = 0.5  # Interval for exporting metrics in seconds
CSM_METADATA_EXCHANGE_LABEL_KEY = "exchange_labels_key"  # Key for exchange labels

# List of metric names that can have optional labels
METRIC_NAME_WITH_OPTIONAL_LABEL = [
    "grpc.client.attempt.duration"
    "grpc.client.attempt.sent_total_compressed_message_size",
    "grpc.client.attempt.rcvd_total_compressed_message_size",
]

# List of optional label keys for CSM (Cloud Service Monitoring)
CSM_OPTIONAL_LABEL_KEYS = ["csm.service_name", "csm.service_namespace_name"]

# List of metric names that can have exchange labels
METRIC_NAME_WITH_EXCHANGE_LABEL = [
    "grpc.client.attempt.duration"
    "grpc.client.attempt.sent_total_compressed_message_size",
    "grpc.client.attempt.rcvd_total_compressed_message_size",
    "grpc.server.call.duration",
    "grpc.server.call.sent_total_compressed_message_size",
    "grpc.server.call.rcvd_total_compressed_message_size",
]

class OTelMetricExporter(MetricExporter):
    """Implementation of :class:`MetricExporter` that export metrics to the
    provided metric_list.

    Attributes:
        all_metrics: A dictionary where:
            - Key is the metric name (grpc_observability._opentelemetry_measures.Metric.name)
            - Value is a list of labels recorded for that metric
            Example:
                {"grpc.client.attempt.started":
                  [{'grpc.method': 'test/UnaryUnary', 'grpc.target': 'localhost:42517'},
                   {'grpc.method': 'other', 'grpc.target': 'localhost:42517'}]}
    """

    def __init__(
        self,
        all_metrics: Dict[str, List],
        preferred_temporality: Dict[type, AggregationTemporality] = None,
        preferred_aggregation: Dict[
            type, "opentelemetry.sdk.metrics.view.Aggregation"
        ] = None,
    ):
        """Initialize the OTelMetricExporter.

        Args:
            all_metrics: Dictionary to store exported metrics
            preferred_temporality: Preferred temporality for aggregation
            preferred_aggregation: Preferred aggregation type
        """
        super().__init__(
            preferred_temporality=preferred_temporality,
            preferred_aggregation=preferred_aggregation,
        )
        self.all_metrics = all_metrics

    def export(
        self,
        metrics_data: MetricsData,
        timeout_millis: float = 10_000,
        **kwargs,
    ) -> MetricExportResult:
        """Export metrics data.

        Args:
            metrics_data: The metrics data to export
            timeout_millis: Maximum time to wait for export to complete
            **kwargs: Additional arguments

        Returns:
            MetricExportResult.SUCCESS always
        """
        self.record_metric(metrics_data)
        return MetricExportResult.SUCCESS

    def shutdown(self, timeout_millis: float = 30_000, **kwargs) -> None:
        """Shutdown the exporter."""
        pass

    def force_flush(self, timeout_millis: float = 10_000) -> bool:
        """Force flush any pending metrics.

        Returns:
            True always
        """
        return True

    def record_metric(self, metrics_data: MetricsData) -> None:
        """Record metrics from metrics_data into all_metrics.

        Args:
            metrics_data: The metrics data to record
        """
        for resource_metric in metrics_data.resource_metrics:
            for scope_metric in resource_metric.scope_metrics:
                for metric in scope_metric.metrics:
                    for data_point in metric.data.data_points:
                        self.all_metrics[metric.name].append(
                            data_point.attributes
                        )


class TestLabelInjector(OpenTelemetryLabelInjector):
    """Test implementation of OpenTelemetryLabelInjector for testing purposes.

    Attributes:
        _exchange_labels: Dictionary of labels to be exchanged between services
        _local_labels: Dictionary of local labels to be added to metrics
    """

    _exchange_labels: Dict[str, AnyStr]
    _local_labels: Dict[str, str]

    def __init__(
        self, local_labels: Dict[str, str], exchange_labels: Dict[str, str]
    ):
        """Initialize the TestLabelInjector.

        Args:
            local_labels: Local labels to add to metrics
            exchange_labels: Labels to exchange between services
        """
        self._exchange_labels = exchange_labels
        self._local_labels = local_labels

    def get_labels_for_exchange(self) -> Dict[str, AnyStr]:
        """Get labels to be exchanged with other services.

        Returns:
            Dictionary of exchange labels
        """
        return self._exchange_labels

    def get_additional_labels(
        self, include_exchange_labels: bool
    ) -> Dict[str, str]:
        """Get additional labels to be added to metrics.

        Args:
            include_exchange_labels: Whether to include exchange labels

        Returns:
            Dictionary of local labels
        """
        return self._local_labels

    def deserialize_labels(
        self, labels: Dict[str, AnyStr]
    ) -> Dict[str, AnyStr]:
        """Deserialize labels received from other services.

        Args:
            labels: Serialized labels to deserialize

        Returns:
            Dictionary of deserialized labels
        """
        deserialized_labels = {}
        for key, value in labels.items():
            if "XEnvoyPeerMetadata" == key:
                struct = struct_pb2.Struct()
                struct.ParseFromString(value)

                exchange_labels_value = self._get_value_from_struct(
                    CSM_METADATA_EXCHANGE_LABEL_KEY, struct
                )
                deserialized_labels[
                    CSM_METADATA_EXCHANGE_LABEL_KEY
                ] = exchange_labels_value
            else:
                deserialized_labels[key] = value

        return deserialized_labels

    def _get_value_from_struct(
        self, key: str, struct: struct_pb2.Struct
    ) -> str:
        """Get a value from a protobuf Struct by key.

        Args:
            key: The key to look up in the struct
            struct: The protobuf Struct to search

        Returns:
            The string value if found, "unknown" otherwise
        """
        value = struct.fields.get(key)
        if not value:
            return "unknown"
        return value.string_value


class TestOpenTelemetryPluginOption(OpenTelemetryPluginOption):
    """Test implementation of OpenTelemetryPluginOption for testing purposes.

    Attributes:
        _label_injector: The label injector to use
        _active_on_client: Whether the plugin is active on client side
        _active_on_server: Whether the plugin is active on server side
    """

    _label_injector: OpenTelemetryLabelInjector
    _active_on_client: bool
    _active_on_server: bool

    def __init__(
        self,
        label_injector: OpenTelemetryLabelInjector,
        active_on_client: Optional[bool] = True,
        active_on_server: Optional[bool] = True,
    ):
        """Initialize the TestOpenTelemetryPluginOption.

        Args:
            label_injector: The label injector to use
            active_on_client: Whether to activate on client side
            active_on_server: Whether to activate on server side
        """
        self._label_injector = label_injector
        self._active_on_client = active_on_client
        self._active_on_server = active_on_server

    def is_active_on_client_channel(self, target: str) -> bool:
        """Check if plugin is active on client channel.

        Args:
            target: The target address

        Returns:
            True if active on client, False otherwise
        """
        return self._active_on_client

    def is_active_on_server(self, xds: bool) -> bool:
        """Check if plugin is active on server.

        Args:
            xds: Whether XDS is enabled

        Returns:
            True if active on server, False otherwise
        """
        return self._active_on_server

    def get_label_injector(self) -> OpenTelemetryLabelInjector:
        """Get the label injector.

        Returns:
            The configured label injector
        """
        return self._label_injector


@unittest.skipIf(
    os.name == "nt" or "darwin" in sys.platform,
    "Observability is not supported in Windows and MacOS",
)
class ObservabilityPluginTest(unittest.TestCase):
    """Test case for gRPC observability plugin functionality."""

    def setUp(self):
        """Set up test fixtures."""
        self.all_metrics = defaultdict(list)
        otel_exporter = OTelMetricExporter(self.all_metrics)
        reader = PeriodicExportingMetricReader(
            exporter=otel_exporter,
            export_interval_millis=OTEL_EXPORT_INTERVAL_S * 1000,
        )
        self._provider = MeterProvider(metric_readers=[reader])
        self._server = None
        self._port = None

    def tearDown(self):
        """Tear down test fixtures."""
        if self._server:
            self._server.stop(0)

    def testLabelInjectorWithLocalLabels(self):
        """Test that local labels in label injector are added to all metrics."""
        label_injector = TestLabelInjector(
            local_labels={"local_labels_key": "local_labels_value"},
            exchange_labels={},
        )
        plugin_option = TestOpenTelemetryPluginOption(
            label_injector=label_injector
        )
        otel_plugin = grpc_observability.OpenTelemetryPlugin(
            meter_provider=self._provider, plugin_options=[plugin_option]
        )

        otel_plugin.register_global()
        self._server, port = _test_server.start_server()
        _test_server.unary_unary_call(port=port)
        otel_plugin.deregister_global()

        self._validate_metrics_exist(self.all_metrics)
        for name, label_list in self.all_metrics.items():
            self._validate_label_exist(name, label_list, ["local_labels_key"])

    def testClientSidePluginOption(self):
        """Test plugin option when only active on client side."""
        label_injector = TestLabelInjector(
            local_labels={"local_labels_key": "local_labels_value"},
            exchange_labels={},
        )
        plugin_option = TestOpenTelemetryPluginOption(
            label_injector=label_injector, active_on_server=False
        )
        otel_plugin = grpc_observability.OpenTelemetryPlugin(
            meter_provider=self._provider, plugin_options=[plugin_option]
        )

        otel_plugin.register_global()
        server, port = _test_server.start_server()
        self._server = server
        _test_server.unary_unary_call(port=port)
        otel_plugin.deregister_global()

        self._validate_metrics_exist(self.all_metrics)
        for name, label_list in self.all_metrics.items():
            if "grpc.client" in name:
                self._validate_label_exist(
                    name, label_list, ["local_labels_key"]
                )
        for name, label_list in self.all_metrics.items():
            if "grpc.server" in name:
                self._validate_label_not_exist(
                    name, label_list, ["local_labels_key"]
                )

    def testServerSidePluginOption(self):
        """Test plugin option when only active on server side."""
        label_injector = TestLabelInjector(
            local_labels={"local_labels_key": "local_labels_value"},
            exchange_labels={},
        )
        plugin_option = TestOpenTelemetryPluginOption(
            label_injector=label_injector, active_on_client=False
        )
        otel_plugin = grpc_observability.OpenTelemetryPlugin(
            meter_provider=self._provider, plugin_options=[plugin_option]
        )

        otel_plugin.register_global()
        server, port = _test_server.start_server()
        self._server = server
        _test_server.unary_unary_call(port=port)
        otel_plugin.deregister_global()

        self._validate_metrics_exist(self.all_metrics)
        for name, label_list in self.all_metrics.items():
            if "grpc.client" in name:
                self._validate_label_not_exist(
                    name, label_list, ["local_labels_key"]
                )
        for name, label_list in self.all_metrics.items():
            if "grpc.server" in name:
                self._validate_label_exist(
                    name, label_list, ["local_labels_key"]
                )

    def assert_eventually(
        self,
        predicate: Callable[[], bool],
        *,
        timeout: Optional[datetime.timedelta] = None,
        message: Optional[Callable[[], str]] = None,
    ) -> None:
        """Assert that a condition eventually becomes true within timeout.

        Args:
            predicate: Callable that returns a boolean
            timeout: Maximum time to wait (default: 5 seconds)
            message: Optional error message generator
        """
        message = message or (lambda: "Proposition did not evaluate to true")
        timeout = timeout or datetime.timedelta(seconds=5)
        end = datetime.datetime.now() + timeout
        while datetime.datetime.now() < end:
            if predicate():
                break
            time.sleep(0.5)
        else:
            self.fail(message() + " after " + str(timeout))

    def _validate_metrics_exist(self, all_metrics: Dict[str, Any]) -> None:
        """Validate that metrics have been exported.

        Args:
            all_metrics: Dictionary of exported metrics
        """
        self.assert_eventually(
            lambda: len(all_metrics.keys()) > 1,
            message=lambda: f"No metrics was exported",
        )

    def _validate_all_metrics_names(self, metric_names: Set[str]) -> None:
        """Validate that all expected metric names are present.

        Args:
            metric_names: Set of metric names to validate
        """
        self._validate_server_metrics_names(metric_names)
        self._validate_client_metrics_names(metric_names)

    def _validate_server_metrics_names(self, metric_names: Set[str]) -> None:
        """Validate that all expected server metric names are present.

        Args:
            metric_names: Set of metric names to validate
        """
        for base_metric in _open_telemetry_measures.base_metrics():
            if "grpc.server" in base_metric.name:
                self.assertTrue(
                    base_metric.name in metric_names,
                    msg=f"metric {base_metric.name} not found in exported metrics: {metric_names}!",
                )

    def _validate_client_metrics_names(self, metric_names: Set[str]) -> None:
        """Validate that all expected client metric names are present.

        Args:
            metric_names: Set of metric names to validate
        """
        for base_metric in _open_telemetry_measures.base_metrics():
            if "grpc.client" in base_metric.name:
                self.assertTrue(
                    base_metric.name in metric_names,
                    msg=f"metric {base_metric.name} not found in exported metrics: {metric_names}!",
                )

    def _validate_label_exist(
        self,
        metric_name: str,
        metric_label_list: List[str],
        labels_to_check: List[str],
    ) -> None:
        """Validate that specified labels exist in the metric labels.

        Args:
            metric_name: Name of the metric being checked
            metric_label_list: List of label dictionaries for the metric
            labels_to_check: List of label keys to check for
        """
        for metric_label in metric_label_list:
            for label in labels_to_check:
                self.assertTrue(
                    label in metric_label,
                    msg=f"label with key {label} not found in metric {metric_name}, found label list: {metric_label}",
                )

    def _validate_label_not_exist(
        self,
        metric_name: str,
        metric_label_list: List[str],
        labels_to_check: List[str],
    ) -> None:
        """Validate that specified labels do not exist in the metric labels.

        Args:
            metric_name: Name of the metric being checked
            metric_label_list: List of label dictionaries for the metric
            labels_to_check: List of label keys to check for absence
        """
        for metric_label in metric_label_list:
            for label in labels_to_check:
                self.assertFalse(
                    label in metric_label,
                    msg=f"found unexpected label with key {label} in metric {metric_name}, found label list: {metric_label}",
                )


if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
```