Here's the commented version of the code:

```c++
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

from opencensus.stats import measure

# Define standard units for measurements
UNIT_BYTES = "By"         # Bytes unit for data size measurements
UNIT_MILLISECONDS = "ms"  # Milliseconds unit for time measurements
UNIT_COUNT = "1"          # Dimensionless unit for counting items

# Client-side RPC metrics
CLIENT_STARTED_RPCS_MEASURE = measure.MeasureInt(
    "grpc.io/client/started_rpcs",
    "The total number of client RPCs ever opened, including those that have not been completed.",
    UNIT_COUNT,
)

CLIENT_COMPLETED_RPCS_MEASURE = measure.MeasureInt(
    "grpc.io/client/completed_rpcs",
    "The total number of completed client RPCs",
    UNIT_COUNT,
)

CLIENT_ROUNDTRIP_LATENCY_MEASURE = measure.MeasureFloat(
    "grpc.io/client/roundtrip_latency",
    "Time between first byte of request sent to last byte of response received, or terminal error",
    UNIT_MILLISECONDS,
)

CLIENT_API_LATENCY_MEASURE = measure.MeasureInt(
    "grpc.io/client/api_latency",
    "End-to-end time taken to complete an RPC",
    UNIT_MILLISECONDS,
)

CLIENT_SEND_BYTES_PER_RPC_MEASURE = measure.MeasureFloat(
    "grpc.io/client/sent_bytes_per_rpc",
    "Total bytes sent across all request messages per RPC",
    UNIT_BYTES,
)

CLIENT_RECEIVED_BYTES_PER_RPC_MEASURE = measure.MeasureFloat(
    "grpc.io/client/received_bytes_per_rpc",
    "Total bytes received across all response messages per RPC",
    UNIT_BYTES,
)

# Server-side RPC metrics
SERVER_STARTED_RPCS_MEASURE = measure.MeasureInt(
    "grpc.io/server/started_rpcs",
    "Total bytes sent across all request messages per RPC",
    UNIT_COUNT,
)

SERVER_COMPLETED_RPCS_MEASURE = measure.MeasureInt(
    "grpc.io/server/completed_rpcs",
    "The total number of completed server RPCs",
    UNIT_COUNT,
)

SERVER_SENT_BYTES_PER_RPC_MEASURE = measure.MeasureFloat(
    "grpc.io/server/sent_bytes_per_rpc",
    "Total bytes sent across all messages per RPC",
    UNIT_BYTES,
)

SERVER_RECEIVED_BYTES_PER_RPC_MEASURE = measure.MeasureFloat(
    "grpc.io/server/received_bytes_per_rpc",
    "Total bytes received across all messages per RPC",
    UNIT_BYTES,
)

SERVER_SERVER_LATENCY_MEASURE = measure.MeasureFloat(
    "grpc.io/server/server_latency",
    "Time between first byte of request received to last byte of response sent, or terminal error",
    UNIT_MILLISECONDS,
)
```

Key improvements made:
1. Added section headers for better organization (Client-side RPC metrics / Server-side RPC metrics)
2. Added comments explaining the standard units
3. Fixed the license header formatting (added missing # on blank lines)
4. Maintained all original functionality while making the code more understandable
5. Kept all existing docstrings as they provide good descriptions of each metric

The comments now provide clear context about what each section of metrics represents and how the units are defined, making it easier for future developers to understand and maintain this monitoring configuration.