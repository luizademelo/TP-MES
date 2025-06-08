Here's the commented version of the code:

```c++
# Copyright 2019 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import contextlib
import errno
import os
import socket

# Default socket options - REUSEADDR and REUSEPORT on non-Windows systems,
# just REUSEADDR on Windows (since Windows doesn't support SO_REUSEPORT)
_DEFAULT_SOCK_OPTIONS = (
    (socket.SO_REUSEADDR, socket.SO_REUSEPORT)
    if os.name != "nt"
    else (socket.SO_REUSEADDR,)
)

# Error numbers that indicate unrecoverable socket binding errors
_UNRECOVERABLE_ERRNOS = (errno.EADDRINUSE, errno.ENOSR)

def get_socket(
    bind_address="localhost",
    port=0,
    listen=True,
    sock_options=_DEFAULT_SOCK_OPTIONS,
):
    """Opens a socket.

    Useful for reserving a port for a system-under-test.

    Args:
      bind_address: The host to which to bind.
      port: The port to which to bind. 0 means let OS choose.
      listen: A boolean value indicating whether or not to listen on the socket.
      sock_options: A sequence of socket options to apply to the socket.

    Returns:
      A tuple containing:
        - the address to which the socket is bound
        - the port to which the socket is bound
        - the socket object itself

    Raises:
      RuntimeError: If binding fails for all address families.
      OSError: For unrecoverable errors (EADDRINUSE, ENOSR).
    """
    # Handle empty sock_options case
    _sock_options = sock_options if sock_options else []
    
    # Prefer IPv6 if available, fall back to IPv4
    if socket.has_ipv6:
        address_families = (socket.AF_INET6, socket.AF_INET)
    else:
        address_families = socket.AF_INET
    
    # Try each address family in order
    for address_family in address_families:
        try:
            # Create TCP socket
            sock = socket.socket(address_family, socket.SOCK_STREAM)
            
            # Apply all requested socket options
            for sock_option in _sock_options:
                sock.setsockopt(socket.SOL_SOCKET, sock_option, 1)
            
            # Bind to requested address and port
            sock.bind((bind_address, port))
            
            # Start listening if requested
            if listen:
                sock.listen(1)
            
            # Return (address, port, socket) tuple
            return bind_address, sock.getsockname()[1], sock
        
        except OSError as os_error:
            # Clean up socket on error
            sock.close()
            # Re-raise unrecoverable errors
            if os_error.errno in _UNRECOVERABLE_ERRNOS:
                raise
            # For other errors, try next address family
            else:
                continue

        except socket.error:
            # Clean up socket on error and try next address family
            sock.close()
            continue
    
    # If all address families failed, raise runtime error
    raise RuntimeError(
        "Failed to bind to {} with sock_options {}".format(
            bind_address, sock_options
        )
    )

@contextlib.contextmanager
def bound_socket(
    bind_address="localhost",
    port=0,
    listen=True,
    sock_options=_DEFAULT_SOCK_OPTIONS,
):
    """Context manager for a bound socket.

    Opens a socket bound to an arbitrary port and ensures it's closed when done.
    Useful for reserving a port for a system-under-test.

    Args:
      bind_address: The host to which to bind.
      port: The port to which to bind. 0 means let OS choose.
      listen: A boolean value indicating whether or not to listen on the socket.
      sock_options: A sequence of socket options to apply to the socket.

    Yields:
      A tuple containing:
        - the address to which the socket is bound
        - the port to which the socket is bound

    Example:
        with bound_socket() as (host, port):
            # Use the reserved port here
            print(f"Using port {port}")
    """
    # Get a bound socket
    host, port, sock = get_socket(
        bind_address=bind_address,
        port=port,
        listen=listen,
        sock_options=sock_options,
    )
    try:
        # Yield the address and port to the context
        yield host, port
    finally:
        # Ensure socket is closed when context exits
        sock.close()
```