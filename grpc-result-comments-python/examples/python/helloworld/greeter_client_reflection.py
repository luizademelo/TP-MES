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
"""The Python implementation of the GRPC helloworld.Greeter client with reflection."""

import logging

from google.protobuf.descriptor_pool import DescriptorPool
import grpc
from grpc_reflection.v1alpha.proto_reflection_descriptor_database import (
    ProtoReflectionDescriptorDatabase,
)

def run():
    """Main function to demonstrate gRPC reflection client functionality.
    
    Connects to a gRPC server, uses reflection to discover services and methods,
    and prints information about the Greeter service and its methods.
    """
    print("Will try to greet world ...")
    
    # Create an insecure channel to localhost on port 50051
    with grpc.insecure_channel("localhost:50051") as channel:
        # Initialize reflection database using the channel
        reflection_db = ProtoReflectionDescriptorDatabase(channel)
        
        # Get list of available services from the server
        services = reflection_db.get_services()
        print(f"found services: {services}")

        # Create a descriptor pool using the reflection database
        desc_pool = DescriptorPool(reflection_db)
        
        # Find the Greeter service descriptor by name
        service_desc = desc_pool.FindServiceByName("helloworld.Greeter")
        print(f"found Greeter service with name: {service_desc.full_name}")
        
        # Iterate through all methods in the Greeter service
        for methods in service_desc.methods:
            print(f"found method name: {methods.full_name}")
            
            # Get and print the input type for each method
            input_type = methods.input_type
            print(f"input type for this method: {input_type.full_name}")

        # Find the HelloRequest message type descriptor
        request_desc = desc_pool.FindMessageTypeByName(
            "helloworld.HelloRequest"
        )
        print(f"found request name: {request_desc.full_name}")

if __name__ == "__main__":
    # Configure basic logging and run the main function
    logging.basicConfig()
    run()
```

Key additions:
1. Added a docstring for the `run()` function explaining its purpose
2. Added comments explaining each major step in the process:
   - Channel creation
   - Reflection database setup
   - Service discovery
   - Descriptor pool usage
   - Service and method inspection
   - Message type lookup
3. Added comment for the main block execution
4. Maintained all existing functionality while making the code more understandable

The comments explain the gRPC reflection workflow where the client dynamically discovers service information from the server rather than having static protocol buffer definitions.