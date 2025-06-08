Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""API metadata conversion utilities."""

import collections

# Define a named tuple for metadata key-value pairs
_Metadatum = collections.namedtuple(
    "_Metadatum",
    (
        "key",    # The metadata key
        "value",  # The metadata value
    ),
)

def _beta_metadatum(key, value):
    """Convert metadata key-value pair to beta (binary) format.
    
    Args:
        key: The metadata key (string or bytes)
        value: The metadata value (string or bytes)
    
    Returns:
        _Metadatum: A named tuple with key and value converted to bytes
    """
    # Convert key to bytes if it's not already
    beta_key = key if isinstance(key, (bytes,)) else key.encode("ascii")
    # Convert value to bytes if it's not already
    beta_value = value if isinstance(value, (bytes,)) else value.encode("ascii")
    return _Metadatum(beta_key, beta_value)

def _metadatum(beta_key, beta_value):
    """Convert beta (binary) metadata back to regular string format.
    
    Args:
        beta_key: The metadata key in bytes format
        beta_value: The metadata value in bytes format
    
    Returns:
        _Metadatum: A named tuple with decoded key and value
    """
    # Convert key to string if it's not already
    key = beta_key if isinstance(beta_key, (str,)) else beta_key.decode("utf8")
    
    # Handle value conversion:
    # - Keep as is if it's already a string or if key ends with "-bin"
    # - Otherwise decode from bytes to string
    if isinstance(beta_value, (str,)) or key[-4:] == "-bin":
        value = beta_value
    else:
        value = beta_value.decode("utf8")
    return _Metadatum(key, value)

def beta(metadata):
    """Convert a metadata collection to beta (binary) format.
    
    Args:
        metadata: Collection of metadata key-value pairs (can be None)
    
    Returns:
        tuple: Of _Metadatum objects in beta format, or empty tuple if None
    """
    if metadata is None:
        return ()
    else:
        return tuple(_beta_metadatum(key, value) for key, value in metadata)

def unbeta(beta_metadata):
    """Convert beta (binary) metadata back to regular string format.
    
    Args:
        beta_metadata: Collection of beta metadata key-value pairs (can be None)
    
    Returns:
        tuple: Of _Metadatum objects in string format, or empty tuple if None
    """
    if beta_metadata is None:
        return ()
    else:
        return tuple(
            _metadatum(beta_key, beta_value)
            for beta_key, beta_value in beta_metadata
        )
```