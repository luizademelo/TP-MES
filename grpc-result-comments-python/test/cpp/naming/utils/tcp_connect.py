Here's the commented version of the code:

```python
#!/usr/bin/env python3
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Opens a TCP connection to a specified server and then exits."""

# Import necessary modules
import argparse  # For parsing command line arguments
import socket    # For socket operations (TCP connection)
import sys       # For system-specific parameters and functions
import threading # For threading operations (though not used in this script)
import time      # For time-related functions (though not used in this script)

def main():
    """Main function that sets up and executes the TCP connection test."""
    
    # Set up argument parser with description
    argp = argparse.ArgumentParser(
        description="Open a TCP handshake to a server"
    )
    
    # Add command line arguments:
    
    # Server host argument (string)
    argp.add_argument(
        "-s",
        "--server_host",
        default=None,
        type=str,
        help="Server host name or IP.",
    )
    
    # Server port argument (integer)
    argp.add_argument(
        "-p",
        "--server_port",
        default=0,
        type=int,
        help="Port that the server is listening on.",
    )
    
    # Timeout argument (integer, in seconds)
    argp.add_argument(
        "-t",
        "--timeout",
        default=1,
        type=int,
        help="Force process exit after this number of seconds.",
    )
    
    # Parse the command line arguments
    args = argp.parse_args()
    
    # Attempt to establish a TCP connection to the specified server:port
    # with the given timeout. This will raise an exception if connection fails.
    socket.create_connection(
        [args.server_host, args.server_port], timeout=args.timeout
    )

# Standard Python idiom to execute main() when run as a script
if __name__ == "__main__":
    main()
```

Key improvements in the comments:
1. Added module import explanations
2. Added docstring for the main() function
3. Added comments explaining each argument definition
4. Explained the socket.create_connection call
5. Added clarification about the standard Python script execution idiom
6. Maintained all existing license and header information

The comments now provide clear context about:
- What the script does
- How to use it (via the argument help texts)
- The flow of execution
- Important operations being performed