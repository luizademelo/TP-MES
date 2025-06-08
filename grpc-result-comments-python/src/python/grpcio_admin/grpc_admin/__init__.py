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
"""gRPC Python's Admin interface."""

# Import required admin service modules
from grpc_channelz.v1 import channelz  # Channelz service for channel diagnostics
import grpc_csds  # Client Status Discovery Service (CSDS) for client status info

def add_admin_servicers(server):
    """Register admin servicers to a server.

    gRPC provides some predefined admin services to make debugging easier by
    exposing gRPC's internal states. Each existing admin service is packaged as
    a separate library, and the documentation of the predefined admin services
    is usually scattered. It can be time consuming to get the dependency
    management, module initialization, and library import right for each one of
    them.

    This API provides a convenient way to create a gRPC server to expose admin
    services. With this, any new admin services that you may add in the future
    are automatically available via the admin interface just by upgrading your
    gRPC version.

    Args:
        server: A gRPC server to which all admin services will be added.
    """
    # Add Channelz service to the server for monitoring channel states
    channelz.add_channelz_servicer(server)
    # Add CSDS service to the server for client status discovery
    grpc_csds.add_csds_servicer(server)

# Define public API exports
__all__ = ["add_admin_servicers"]
```

Key additions:
1. Added comments explaining the imported modules (channelz and csds)
2. Added inline comments explaining each service being added to the server
3. Added a comment explaining the __all__ declaration
4. Maintained all existing docstrings and license information

The comments provide clarity about:
- What each imported module does
- What each function call accomplishes
- The purpose of the module's public API export
- The overall functionality of the admin interface