Here's the commented version of the code:

```c++
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""An example of multiprocessing concurrency with gRPC."""

# Import future features for Python 2/3 compatibility
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

# Standard library imports
import argparse  # For command-line argument parsing
import atexit    # For registering shutdown functions
import logging   # For logging functionality
import multiprocessing  # For parallel processing
import operator  # For attribute access operations
import sys       # For system-specific functions

# gRPC and generated protocol buffer imports
import grpc
import prime_pb2
import prime_pb2_grpc

# Constants defining process count and maximum number to check for primality
_PROCESS_COUNT = 8          # Number of worker processes to spawn
_MAXIMUM_CANDIDATE = 10000   # Upper bound for prime number checking

# Global variables for worker process communication
_worker_channel_singleton = None  # gRPC channel for worker communication
_worker_stub_singleton = None     # gRPC stub for making requests

# Logger instance for the module
_LOGGER = logging.getLogger(__name__)

def _shutdown_worker():
    """Cleanup function to shutdown worker process gracefully.
    Closes the gRPC channel if it exists.
    """
    _LOGGER.info("Shutting worker process down.")
    if _worker_channel_singleton is not None:
        _worker_channel_singleton.close()

def _initialize_worker(server_address):
    """Initialize worker process with gRPC channel and stub.
    
    Args:
        server_address: Address of the gRPC server to connect to
    """
    global _worker_channel_singleton
    global _worker_stub_singleton
    _LOGGER.info("Initializing worker process.")
    # Create insecure channel to gRPC server
    _worker_channel_singleton = grpc.insecure_channel(server_address)
    # Create stub for PrimeChecker service
    _worker_stub_singleton = prime_pb2_grpc.PrimeCheckerStub(
        _worker_channel_singleton
    )
    # Register shutdown handler to be called at exit
    atexit.register(_shutdown_worker)

def _run_worker_query(primality_candidate):
    """Query the gRPC server to check if a number is prime.
    
    Args:
        primality_candidate: Number to check for primality
        
    Returns:
        Response from the gRPC server
    """
    _LOGGER.info("Checking primality of %s.", primality_candidate)
    return _worker_stub_singleton.check(
        prime_pb2.PrimeCandidate(candidate=primality_candidate)
    )

def _calculate_primes(server_address):
    """Main function to calculate primes using multiprocessing.
    
    Args:
        server_address: Address of the gRPC server to connect to
        
    Returns:
        Tuple of (number, is_prime) pairs for all checked numbers
    """
    # Create worker pool with initialization function
    worker_pool = multiprocessing.Pool(
        processes=_PROCESS_COUNT,
        initializer=_initialize_worker,
        initargs=(server_address,),
    )
    # Range of numbers to check for primality
    check_range = range(2, _MAXIMUM_CANDIDATE)
    # Distribute work across processes
    primality = worker_pool.map(_run_worker_query, check_range)
    # Combine results with original numbers
    primes = zip(check_range, map(operator.attrgetter("isPrime"), primality))
    return tuple(primes)

def main():
    """Main entry point for the script."""
    # Set up command line argument parser
    msg = "Determine the primality of the first {} integers.".format(
        _MAXIMUM_CANDIDATE
    )
    parser = argparse.ArgumentParser(description=msg)
    parser.add_argument(
        "server_address",
        help="The address of the server (e.g. localhost:50051)",
    )
    
    # Parse arguments and calculate primes
    args = parser.parse_args()
    primes = _calculate_primes(args.server_address)
    print(primes)

if __name__ == "__main__":
    # Configure logging to show process ID and messages
    handler = logging.StreamHandler(sys.stdout)
    formatter = logging.Formatter("[PID %(process)d] %(message)s")
    handler.setFormatter(formatter)
    _LOGGER.addHandler(handler)
    _LOGGER.setLevel(logging.INFO)
    
    # Run main function
    main()
```