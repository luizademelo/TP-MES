Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""MetricsService for publishing stress test qps data."""

import time

from src.proto.grpc.testing import metrics_pb2
from src.proto.grpc.testing import metrics_pb2_grpc

# Constant defining the name of the gauge that will track overall QPS (Queries Per Second)
GAUGE_NAME = "python_overall_qps"

class MetricsServer(metrics_pb2_grpc.MetricsServiceServicer):
    """Implementation of gRPC MetricsService for collecting and serving performance metrics."""
    
    def __init__(self, histogram):
        """
        Initialize the MetricsServer with a histogram for tracking metrics.
        
        Args:
            histogram: A histogram object that will track and store metric data.
        """
        self._start_time = time.time()  # Record server start time for QPS calculation
        self._histogram = histogram    # Histogram for storing metric data

    def _get_qps(self):
        """
        Calculate and return the current Queries Per Second (QPS) rate.
        
        Returns:
            int: The calculated QPS (rounded to nearest integer)
        """
        count = self._histogram.get_data().count  # Get total count from histogram
        delta = time.time() - self._start_time    # Calculate time elapsed since last reset
        self._histogram.reset()                   # Reset histogram for new measurements
        self._start_time = time.time()           # Reset timer for next interval
        return int(count / delta)                # Calculate and return QPS

    def GetAllGauges(self, request, context):
        """
        gRPC service method to return all available gauge metrics.
        
        Args:
            request: The gRPC request object (unused in this implementation)
            context: gRPC context object for handling RPC metadata
            
        Returns:
            List[metrics_pb2.GaugeResponse]: List containing the QPS gauge response
        """
        qps = self._get_qps()
        return [metrics_pb2.GaugeResponse(name=GAUGE_NAME, long_value=qps)]

    def GetGauge(self, request, context):
        """
        gRPC service method to return a specific gauge metric by name.
        
        Args:
            request: The gRPC request object containing the gauge name
            context: gRPC context object for handling RPC metadata
            
        Returns:
            metrics_pb2.GaugeResponse: The QPS gauge response if requested gauge exists
            
        Raises:
            Exception: If the requested gauge name doesn't exist
        """
        if request.name != GAUGE_NAME:
            raise Exception("Gauge {} does not exist".format(request.name))
        qps = self._get_qps()
        return metrics_pb2.GaugeResponse(name=GAUGE_NAME, long_value=qps)
```