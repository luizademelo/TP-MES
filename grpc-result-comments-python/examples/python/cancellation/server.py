Here's the commented version of the code:

```c++
# Copyright 2019 the gRPC authors.
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
"""An example of cancelling requests in gRPC."""

# Future imports to ensure Python 2/3 compatibility
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
from concurrent import futures
import logging
import threading

import grpc
import search

# Import generated gRPC protocol buffer definitions
from examples.python.cancellation import hash_name_pb2
from examples.python.cancellation import hash_name_pb2_grpc

# Initialize logger for this module
_LOGGER = logging.getLogger(__name__)
# Server host address
_SERVER_HOST = "localhost"
# Server description
_DESCRIPTION = "A server for finding hashes similar to names."

class HashFinder(hash_name_pb2_grpc.HashFinderServicer):
    """gRPC servicer class for finding hashes similar to names."""

    def __init__(self, maximum_hashes):
        """Initialize the HashFinder with a maximum hash limit.
        
        Args:
            maximum_hashes: Maximum number of hashes to search before cancelling.
        """
        super(HashFinder, self).__init__()
        self._maximum_hashes = maximum_hashes

    def Find(self, request, context):
        """RPC method to find a single hash matching the criteria.
        
        Args:
            request: The gRPC request containing search parameters.
            context: gRPC context for RPC cancellation and metadata.
            
        Returns:
            A single HashNameResponse with the best matching hash, or empty if none found.
        """
        # Event to signal when RPC is done/cancelled
        stop_event = threading.Event()

        def on_rpc_done():
            """Callback function triggered when RPC completes or is cancelled."""
            _LOGGER.debug("Attempting to regain servicer thread.")
            stop_event.set()

        # Register the callback for RPC completion
        context.add_callback(on_rpc_done)
        candidates = []
        try:
            # Search for matching hashes
            candidates = list(
                search.search(
                    request.desired_name,
                    request.ideal_hamming_distance,
                    stop_event,
                    self._maximum_hashes,
                )
            )
        except search.ResourceLimitExceededError:
            # Handle resource exhaustion by cancelling RPC
            _LOGGER.info("Cancelling RPC due to exhausted resources.")
            context.cancel()
        _LOGGER.debug("Servicer thread returning.")
        # Return the best candidate or empty response if none found
        if not candidates:
            return hash_name_pb2.HashNameResponse()
        return candidates[-1]

    def FindRange(self, request, context):
        """RPC method to stream multiple hashes matching the criteria.
        
        Args:
            request: The gRPC request containing search parameters.
            context: gRPC context for RPC cancellation and metadata.
            
        Yields:
            A stream of HashNameResponse messages with matching hashes.
        """
        # Event to signal when RPC is done/cancelled
        stop_event = threading.Event()

        def on_rpc_done():
            """Callback function triggered when RPC completes or is cancelled."""
            _LOGGER.debug("Attempting to regain servicer thread.")
            stop_event.set()

        # Register the callback for RPC completion
        context.add_callback(on_rpc_done)
        # Create generator for search results
        secret_generator = search.search(
            request.desired_name,
            request.ideal_hamming_distance,
            stop_event,
            self._maximum_hashes,
            interesting_hamming_distance=request.interesting_hamming_distance,
        )
        try:
            # Stream results as they are found
            for candidate in secret_generator:
                yield candidate
        except search.ResourceLimitExceededError:
            # Handle resource exhaustion by cancelling RPC
            _LOGGER.info("Cancelling RPC due to exhausted resources.")
            context.cancel()
        _LOGGER.debug("Regained servicer thread.")

def _running_server(port, maximum_hashes):
    """Start and run the gRPC server.
    
    Args:
        port: Port number to listen on.
        maximum_hashes: Maximum hash limit to pass to HashFinder.
        
    Returns:
        The running gRPC server instance.
    """
    # Create gRPC server with single worker thread
    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=1), maximum_concurrent_rpcs=1
    )
    # Register HashFinder service with the server
    hash_name_pb2_grpc.add_HashFinderServicer_to_server(
        HashFinder(maximum_hashes), server
    )
    # Start server on specified port
    address = "{}:{}".format(_SERVER_HOST, port)
    actual_port = server.add_insecure_port(address)
    server.start()
    print("Server listening at '{}'".format(address))
    return server

def main():
    """Main function to parse arguments and run the server."""
    # Set up argument parser
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    parser.add_argument(
        "--port",
        type=int,
        default=50051,
        nargs="?",
        help="The port on which the server will listen.",
    )
    parser.add_argument(
        "--maximum-hashes",
        type=int,
        default=1000000,
        nargs="?",
        help="The maximum number of hashes to search before cancelling.",
    )
    # Parse command line arguments
    args = parser.parse_args()
    # Start and run the server
    server = _running_server(args.port, args.maximum_hashes)
    server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start main function
    logging.basicConfig()
    main()
```