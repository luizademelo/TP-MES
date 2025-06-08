Here's the commented version of the code:

```c++
# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Base implementation of reflection servicer."""

from google.protobuf import descriptor_pb2
from google.protobuf import descriptor_pool
import grpc
from grpc_reflection.v1alpha import reflection_pb2 as _reflection_pb2
from grpc_reflection.v1alpha import reflection_pb2_grpc as _reflection_pb2_grpc

# Global descriptor pool instance
_POOL = descriptor_pool.Default()

def _not_found_error(original_request):
    """Create a NOT_FOUND error response for reflection requests.
    
    Args:
        original_request: The original reflection request that triggered the error.
    
    Returns:
        ServerReflectionResponse: Response containing NOT_FOUND error details.
    """
    return _reflection_pb2.ServerReflectionResponse(
        error_response=_reflection_pb2.ErrorResponse(
            error_code=grpc.StatusCode.NOT_FOUND.value[0],
            error_message=grpc.StatusCode.NOT_FOUND.value[1].encode(),
        ),
        original_request=original_request,
    )

def _collect_transitive_dependencies(descriptor, seen_files):
    """Recursively collect all file descriptor dependencies.
    
    Args:
        descriptor: The starting file descriptor to collect dependencies from.
        seen_files: Dictionary to store collected descriptors (name -> descriptor).
    """
    seen_files.update({descriptor.name: descriptor})
    for dependency in descriptor.dependencies:
        if not dependency.name in seen_files:
            _collect_transitive_dependencies(dependency, seen_files)

def _file_descriptor_response(descriptor, original_request):
    """Create a response containing file descriptor and its dependencies.
    
    Args:
        descriptor: The main file descriptor to include in the response.
        original_request: The original reflection request.
    
    Returns:
        ServerReflectionResponse: Response containing serialized file descriptors.
    """
    descriptors = {}
    _collect_transitive_dependencies(descriptor, descriptors)

    serialized_proto_list = []
    for d_key in descriptors:
        proto = descriptor_pb2.FileDescriptorProto()
        descriptors[d_key].CopyToProto(proto)
        serialized_proto_list.append(proto.SerializeToString())

    return _reflection_pb2.ServerReflectionResponse(
        file_descriptor_response=_reflection_pb2.FileDescriptorResponse(
            file_descriptor_proto=(serialized_proto_list)
        ),
        original_request=original_request,
    )

class BaseReflectionServicer(_reflection_pb2_grpc.ServerReflectionServicer):
    """Base class for reflection servicer."""

    def __init__(self, service_names, pool=None):
        """Constructor.

        Args:
            service_names: Iterable of fully-qualified service names available.
            pool: An optional DescriptorPool instance.
        """
        self._service_names = tuple(sorted(service_names))
        self._pool = _POOL if pool is None else pool

    def _file_by_filename(self, request, filename):
        """Handle file_by_filename reflection request.
        
        Args:
            request: The original reflection request.
            filename: The filename to look up in the descriptor pool.
            
        Returns:
            ServerReflectionResponse: Either file descriptors or NOT_FOUND error.
        """
        try:
            descriptor = self._pool.FindFileByName(filename)
        except KeyError:
            return _not_found_error(request)
        else:
            return _file_descriptor_response(descriptor, request)

    def _file_containing_symbol(self, request, fully_qualified_name):
        """Handle file_containing_symbol reflection request.
        
        Args:
            request: The original reflection request.
            fully_qualified_name: The fully qualified symbol name to look up.
            
        Returns:
            ServerReflectionResponse: Either file descriptors or NOT_FOUND error.
        """
        try:
            descriptor = self._pool.FindFileContainingSymbol(
                fully_qualified_name
            )
        except KeyError:
            return _not_found_error(request)
        else:
            return _file_descriptor_response(descriptor, request)

    def _file_containing_extension(
        self, request, containing_type, extension_number
    ):
        """Handle file_containing_extension reflection request.
        
        Args:
            request: The original reflection request.
            containing_type: The message type containing the extension.
            extension_number: The extension field number to look up.
            
        Returns:
            ServerReflectionResponse: Either file descriptors or NOT_FOUND error.
        """
        try:
            message_descriptor = self._pool.FindMessageTypeByName(
                containing_type
            )
            extension_descriptor = self._pool.FindExtensionByNumber(
                message_descriptor, extension_number
            )
            descriptor = self._pool.FindFileContainingSymbol(
                extension_descriptor.full_name
            )
        except KeyError:
            return _not_found_error(request)
        else:
            return _file_descriptor_response(descriptor, request)

    def _all_extension_numbers_of_type(self, request, containing_type):
        """Handle all_extension_numbers_of_type reflection request.
        
        Args:
            request: The original reflection request.
            containing_type: The message type to find extensions for.
            
        Returns:
            ServerReflectionResponse: Either extension numbers or NOT_FOUND error.
        """
        try:
            message_descriptor = self._pool.FindMessageTypeByName(
                containing_type
            )
            extension_numbers = tuple(
                sorted(
                    extension.number
                    for extension in self._pool.FindAllExtensions(
                        message_descriptor
                    )
                )
            )
        except KeyError:
            return _not_found_error(request)
        else:
            return _reflection_pb2.ServerReflectionResponse(
                all_extension_numbers_response=_reflection_pb2.ExtensionNumberResponse(
                    base_type_name=message_descriptor.full_name,
                    extension_number=extension_numbers,
                ),
                original_request=request,
            )

    def _list_services(self, request):
        """Handle list_services reflection request.
        
        Args:
            request: The original reflection request.
            
        Returns:
            ServerReflectionResponse: List of available service names.
        """
        return _reflection_pb2.ServerReflectionResponse(
            list_services_response=_reflection_pb2.ListServiceResponse(
                service=[
                    _reflection_pb2.ServiceResponse(name=service_name)
                    for service_name in self._service_names
                ]
            ),
            original_request=request,
        )

__all__ = ["BaseReflectionServicer"]
```

The comments added:
1. Documented all functions and methods with their purpose, parameters, and return values
2. Added explanation for the global descriptor pool
3. Clarified the recursive nature of _collect_transitive_dependencies
4. Explained each reflection request handler method in the BaseReflectionServicer class
5. Maintained consistent documentation style throughout
6. Added type information where appropriate (though Python is dynamically typed)
7. Explained error handling patterns used in the code

The comments aim to help future developers understand both the high-level purpose and implementation details of each component.