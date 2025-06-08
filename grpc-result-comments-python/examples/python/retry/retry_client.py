Here's the commented version of the code:

```c++
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the gRPC client-side retry example."""

import json
import logging

import grpc

# Load protocol buffer definitions and gRPC services from helloworld.proto
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

def run():
    """
    Main function to demonstrate gRPC client with retry functionality.
    Configures retry policy and makes a call to the Greeter service.
    """
    
    # Define service configuration with retry policy in JSON format
    service_config_json = json.dumps(
        {
            "methodConfig": [
                {
                    # Apply this configuration to the SayHello method of Greeter service
                    "name": [
                        {"service": "helloworld.Greeter", "method": "SayHello"}
                    ],
                    # Retry policy configuration
                    "retryPolicy": {
                        "maxAttempts": 5,           # Maximum number of retry attempts
                        "initialBackoff": "0.1s",    # Initial backoff duration
                        "maxBackoff": "1s",          # Maximum backoff duration
                        "backoffMultiplier": 2,      # Backoff multiplier factor
                        # List of status codes that should trigger retries
                        "retryableStatusCodes": ["UNAVAILABLE"],
                    },
                }
            ]
        }
    )
    
    # Configure gRPC channel options
    options = []
    # Enable retries feature (enabled by default in gRPC >=v1.40.0)
    options.append(("grpc.enable_retries", 1))
    # Set the service configuration for the channel
    options.append(("grpc.service_config", service_config_json))
    
    # Create an insecure channel to localhost on port 50051 with the configured options
    with grpc.insecure_channel("localhost:50051", options=options) as channel:
        # Create a stub (client) for the Greeter service
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        # Call the SayHello method with a HelloRequest containing name "you"
        response = stub.SayHello(helloworld_pb2.HelloRequest(name="you"))
    
    # Print the response received from the server
    print("Greeter client received: " + response.message)

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    # Run the main function
    run()
```