Here's the commented version of the code:

```c++
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Loading SSL credentials for gRPC Python authentication example."""

import os

def _load_credential_from_file(filepath):
    """Loads and returns the content of a credential file from the given path.
    
    Args:
        filepath: Relative path to the credential file from this script's directory.
        
    Returns:
        bytes: The raw content of the credential file.
        
    Note:
        The function constructs an absolute path by joining the script's directory
        with the provided relative path before reading the file.
    """
    # Construct absolute path by joining script's directory with relative path
    real_path = os.path.join(os.path.dirname(__file__), filepath)
    # Read and return file content in binary mode
    with open(real_path, "rb") as f:
        return f.read()

# Load server SSL certificate from file
SERVER_CERTIFICATE = _load_credential_from_file("credentials/localhost.crt")
# Load server SSL private key from file
SERVER_CERTIFICATE_KEY = _load_credential_from_file("credentials/localhost.key")
# Load root CA certificate from file for client verification
ROOT_CERTIFICATE = _load_credential_from_file("credentials/root.crt")
```

The comments explain:
1. The purpose and behavior of the `_load_credential_from_file` function
2. The arguments and return value of the function
3. The file reading operation
4. The purpose of each credential being loaded
5. The relative paths used for each credential file

The comments are concise yet informative, helping future developers understand both the implementation details and the broader context of how these credentials are used in the gRPC authentication system.