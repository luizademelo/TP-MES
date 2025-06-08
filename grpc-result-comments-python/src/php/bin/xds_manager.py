Here's the commented version of the code:

```python
#!/usr/bin/env python
# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Manage PHP child processes for the main PHP xDS Interop client"""

import argparse
import fcntl
import os
import subprocess

if __name__ == "__main__":
    # Initialize argument parser to handle command line arguments
    parser = argparse.ArgumentParser()
    # Add arguments for temporary files and bootstrap path
    parser.add_argument("--tmp_file1", nargs="?", default="")  # File for reading RPC requests
    parser.add_argument("--tmp_file2", nargs="?", default="")  # File for writing RPC results
    parser.add_argument("--bootstrap_path", nargs="?", default="")  # Path to gRPC bootstrap config
    args = parser.parse_args()

    # Initialize variables for managing RPCs
    server_address = ""  # Stores the server address obtained from tmp_file1
    rpcs_started = []    # Tracks which RPCs have been initiated to avoid duplicates
    open_processes = {}   # Dictionary to track running child processes

    # Prepare environment for PHP child processes
    client_env = dict(os.environ)
    client_env["GRPC_XDS_BOOTSTRAP"] = args.bootstrap_path  # Set bootstrap config path

    # Main processing loop
    while True:
        # Process tmp_file1 to start new RPCs
        f1 = open(args.tmp_file1, "r+")
        fcntl.flock(f1, fcntl.LOCK_EX)  # Acquire exclusive lock on file
        
        # Read file line by line
        while True:
            key = f1.readline()
            if not key:  # End of file
                break
            key = key.strip()
            
            # Handle server address line
            if key.startswith("server_address"):
                if not server_address:  # Only set once
                    server_address = key[15:]
            # Handle RPC request line (format: "num|RPCType|metadata|timeout_sec")
            elif not key in rpcs_started:  # Prevent duplicate RPCs
                items = key.split("|")
                num = items[0]          # RPC number/ID
                metadata = items[2]     # Metadata for the RPC
                timeout_sec = items[3]   # Timeout setting
                
                # Start appropriate PHP process based on RPC type
                if items[1] == "UnaryCall":
                    p = subprocess.Popen(
                        [
                            "php",
                            "-d", "extension=grpc.so",
                            "-d", "extension=pthreads.so",
                            "src/php/tests/interop/xds_unary_call.php",
                            "--server=" + server_address,
                            "--num=" + str(num),
                            "--metadata=" + metadata,
                            "--timeout_sec=" + timeout_sec,
                        ],
                        env=client_env,
                    )
                elif items[1] == "EmptyCall":
                    p = subprocess.Popen(
                        [
                            "php",
                            "-d", "extension=grpc.so",
                            "-d", "extension=pthreads.so",
                            "src/php/tests/interop/xds_empty_call.php",
                            "--server=" + server_address,
                            "--num=" + str(num),
                            "--metadata=" + metadata,
                            "--timeout_sec=" + timeout_sec,
                        ],
                        env=client_env,
                    )
                else:
                    continue  # Skip unknown RPC types
                
                # Track started RPCs
                rpcs_started.append(key)
                open_processes[key] = p
        
        # Clear processed requests and release lock
        f1.truncate(0)
        fcntl.flock(f1, fcntl.LOCK_UN)
        f1.close()

        # Process tmp_file2 to record completed RPCs
        f2 = open(args.tmp_file2, "a")
        fcntl.flock(f2, fcntl.LOCK_EX)  # Acquire exclusive lock
        
        # Check for completed processes
        keys_to_delete = []
        for key, process in open_processes.items():
            result = process.poll()  # Check if process has finished
            if result is not None:   # Process completed
                # Write result to file (format: "key,returncode")
                f2.write(key + "," + str(process.returncode) + "\n")
                keys_to_delete.append(key)
        
        # Clean up completed processes
        for key in keys_to_delete:
            del open_processes[key]
        
        # Release lock and close file
        fcntl.flock(f2, fcntl.LOCK_UN)
        f2.close()
```