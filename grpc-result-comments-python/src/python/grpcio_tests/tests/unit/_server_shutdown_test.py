Here's the commented version of the code:

```c++
# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# distributed under the License is distributed on an "AS IS" BASIS,
#
# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests clean shutdown of server on various interpreter exit conditions.

The tests in this module spawn a subprocess for each test case, the
test is considered successful if it doesn't freeze/timeout.
"""

import atexit
import logging
import os
import subprocess
import sys
import threading
import unittest

from tests.unit import _server_shutdown_scenarios

# Absolute path to the scenario file containing test scenarios
SCENARIO_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(os.path.realpath(__file__)),
        "_server_shutdown_scenarios.py",
    )
)
# Path to the current Python interpreter
INTERPRETER = sys.executable
# Base command to run the scenario file with the current interpreter
BASE_COMMAND = [INTERPRETER, SCENARIO_FILE]

# List to keep track of spawned processes
processes = []
# Lock for thread-safe access to the processes list
process_lock = threading.Lock()

def cleanup_processes():
    """Cleanup function to kill all spawned processes at exit.
    
    This function is registered with atexit to ensure all test processes
    are terminated when the main process exits.
    """
    with process_lock:
        for process in processes:
            try:
                process.kill()
            except Exception:
                pass  # Ignore any errors during process termination

# Register cleanup function to run at program exit
atexit.register(cleanup_processes)

def wait(process):
    """Wait for a process to complete while tracking it in the processes list.
    
    Args:
        process: The subprocess.Popen object to wait for.
    """
    with process_lock:
        processes.append(process)
    process.wait()

class ServerShutdown(unittest.TestCase):
    """Test class for verifying server shutdown behavior under different conditions."""

    def test_deallocated_server_stops(self):
        """Test that server shuts down cleanly when deallocated."""
        process = subprocess.Popen(
            BASE_COMMAND + [_server_shutdown_scenarios.SERVER_DEALLOCATED],
            stdout=sys.stdout,
            stderr=sys.stderr,
        )
        wait(process)

    def test_server_exception_exits(self):
        """Test that server process exits when server raises an exception."""
        process = subprocess.Popen(
            BASE_COMMAND + [_server_shutdown_scenarios.SERVER_RAISES_EXCEPTION],
            stdout=sys.stdout,
            stderr=sys.stderr,
        )
        wait(process)

    @unittest.skipIf(os.name == "nt", "fork not supported on windows")
    def test_server_fork_can_exit(self):
        """Test that forked server process can exit cleanly (skipped on Windows)."""
        process = subprocess.Popen(
            BASE_COMMAND + [_server_shutdown_scenarios.SERVER_FORK_CAN_EXIT],
            stdout=sys.stdout,
            stderr=sys.stderr,
        )
        wait(process)

if __name__ == "__main__":
    # Configure basic logging and run tests with verbose output
    logging.basicConfig()
    unittest.main(verbosity=2)
```

Key improvements made:
1. Added module-level docstring explaining the purpose of the tests
2. Added comments explaining the purpose of each constant and variable
3. Added detailed docstrings for all functions explaining their purpose and behavior
4. Added class-level docstring for the test class
5. Added method-level docstrings for each test case explaining what they verify
6. Added comments for the main execution block
7. Maintained all existing functionality while making the code more understandable

The comments follow Python docstring conventions and provide clear explanations of the code's purpose and behavior without being overly verbose.