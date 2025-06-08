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

from typing import Dict, List

from opentelemetry.sdk.metrics.export import AggregationTemporality
from opentelemetry.sdk.metrics.export import MetricExportResult
from opentelemetry.sdk.metrics.export import MetricExporter
from opentelemetry.sdk.metrics.export import MetricsData

class OTelMetricExporter(MetricExporter):
    """Implementation of :class:`MetricExporter` that export metrics to the
    provided metric_list.

    Attributes:
        all_metrics: A dict whose keys are grpc_observability._opentelemetry_measures.Metric.name,
            value is a list of labels recorded for that metric.
            An example item of this dict:
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
        print_live: bool = False,
    ):
        """Initialize the OTelMetricExporter.

        Args:
            all_metrics: Dictionary to store metric data where keys are metric names
                        and values are lists of label dictionaries.
            preferred_temporality: Optional dictionary specifying preferred aggregation
                                  temporality for different metric types.
            preferred_aggregation: Optional dictionary specifying preferred aggregation
                                  methods for different metric types.
            print_live: If True, prints metrics as they are received.
        """
        super().__init__(
            preferred_temporality=preferred_temporality,
            preferred_aggregation=preferred_aggregation,
        )
        self._all_metrics = all_metrics  # Stores all collected metrics
        self._print_live = print_live  # Flag for live metric printing

    def export(
        self,
        metrics_data: MetricsData,
        timeout_millis: float = 10_000,
        **kwargs,
    ) -> MetricExportResult:
        """Export the given metrics and return the result.

        Args:
            metrics_data: The MetricsData to be exported.
            timeout_millis: Maximum time to wait for export to complete (default: 10000ms).
            **kwargs: Additional arguments that might be needed.

        Returns:
            Always returns MetricExportResult.SUCCESS as this exporter doesn't fail.
        """
        self.record_metric(metrics_data)
        return MetricExportResult.SUCCESS

    def shutdown(self, timeout_millis: float = 30_000, **kwargs) -> None:
        """Shutdown the exporter.

        Args:
            timeout_millis: Maximum time to wait for shutdown to complete (default: 30000ms).
            **kwargs: Additional arguments that might be needed.
        """
        # No cleanup needed for this exporter
        pass

    def force_flush(self, timeout_millis: float = 10_000) -> bool:
        """Force flush any pending metrics.

        Args:
            timeout_millis: Maximum time to wait for flush to complete (default: 10000ms).

        Returns:
            Always returns True as this exporter doesn't buffer metrics.
        """
        return True

    def record_metric(self, metrics_data: MetricsData) -> None:
        """Record metrics from MetricsData into the internal storage.

        Args:
            metrics_data: The MetricsData containing metrics to be recorded.
        """
        # Iterate through the hierarchical structure of MetricsData:
        # ResourceMetrics -> ScopeMetrics -> Metric -> DataPoints
        for resource_metric in metrics_data.resource_metrics:
            for scope_metric in resource_metric.scope_metrics:
                for metric in scope_metric.metrics:
                    for data_point in metric.data.data_points:
                        # Append the metric's attributes to its corresponding list
                        self._all_metrics[metric.name].append(
                            data_point.attributes
                        )
                        # Print the metric if live printing is enabled
                        if self._print_live:
                            print(f"Metric exporter received: {metric.name}")
```