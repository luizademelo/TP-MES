Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""GRPCAuthMetadataPlugins for standard authentication."""

import inspect
from typing import Any, Optional

import grpc

def _sign_request(
    callback: grpc.AuthMetadataPluginCallback,
    token: Optional[str],
    error: Optional[Exception],
):
    """Helper function to construct and return authentication metadata.
    
    Args:
        callback: The gRPC callback to return the metadata or error to
        token: The access token to use for authentication (None if error occurred)
        error: Exception if authentication failed (None if successful)
    """
    # Construct metadata with Bearer token format
    metadata = (("authorization", "Bearer {}".format(token)),)
    # Invoke callback with the generated metadata or error
    callback(metadata, error)

class GoogleCallCredentials(grpc.AuthMetadataPlugin):
    """Metadata wrapper for GoogleCredentials from the oauth2client library.
    
    This plugin handles both JWT and non-JWT type Google credentials.
    """

    _is_jwt: bool
    _credentials: Any

    def __init__(self, credentials: Any):
        """Initialize the plugin with Google credentials.
        
        Args:
            credentials: Google credentials object from oauth2client library
        """
        self._credentials = credentials

        # Determine if the credentials are JWT type by checking method signature
        self._is_jwt = (
            "additional_claims"
            in inspect.getfullargspec(credentials.get_access_token).args
        )

    def __call__(
        self,
        context: grpc.AuthMetadataContext,
        callback: grpc.AuthMetadataPluginCallback,
    ):
        """Invoked by gRPC to add authentication metadata to requests.
        
        Args:
            context: Contains metadata about the RPC being invoked
            callback: Callback to return the authentication metadata or error
        """
        try:
            if self._is_jwt:
                # For JWT credentials, include service URL as audience claim
                access_token = self._credentials.get_access_token(
                    additional_claims={
                        "aud": context.service_url
                    }
                ).access_token
            else:
                # For non-JWT credentials, simply get the access token
                access_token = self._credentials.get_access_token().access_token
        except Exception as exception:
            # If token retrieval fails, return error through callback
            _sign_request(callback, None, exception)
        else:
            # If successful, return the access token through callback
            _sign_request(callback, access_token, None)

class AccessTokenAuthMetadataPlugin(grpc.AuthMetadataPlugin):
    """Metadata wrapper for raw access token credentials.
    
    This plugin is used when you already have a valid access token.
    """

    _access_token: str

    def __init__(self, access_token: str):
        """Initialize the plugin with an existing access token.
        
        Args:
            access_token: Pre-existing valid access token
        """
        self._access_token = access_token

    def __call__(
        self,
        context: grpc.AuthMetadataContext,
        callback: grpc.AuthMetadataPluginCallback,
    ):
        """Invoked by gRPC to add authentication metadata to requests.
        
        Args:
            context: Contains metadata about the RPC being invoked
            callback: Callback to return the authentication metadata
        """
        # Simply return the pre-existing access token through callback
        _sign_request(callback, self._access_token, None)
```