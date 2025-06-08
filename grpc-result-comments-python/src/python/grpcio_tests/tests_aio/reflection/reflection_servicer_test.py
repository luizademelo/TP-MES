Here's the commented version of the code:

```python
# Copyright 2016 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Tests for gRPC reflection functionality in the v1alpha API version."""

import logging
import unittest

from google.protobuf import descriptor_pb2
import grpc
from grpc.experimental import aio
from grpc_reflection.v1alpha import reflection
from grpc_reflection.v1alpha import reflection_pb2
from grpc_reflection.v1alpha import reflection_pb2_grpc

from src.proto.grpc.testing import empty_pb2
from src.proto.grpc.testing.proto2 import empty2_extensions_pb2
from src.proto.grpc.testing.proto2 import empty2_pb2
from tests_aio.unit._test_base import AioTestBase

# Constants for test file names and symbols
_EMPTY_PROTO_FILE_NAME = "src/proto/grpc/testing/empty.proto"
_EMPTY_PROTO_SYMBOL_NAME = "grpc.testing.Empty"
# List of test service names (famous scientists)
_SERVICE_NAMES = (
    "Angstrom",
    "Bohr",
    "Curie",
    "Dyson",
    "Einstein",
    "Feynman",
    "Galilei",
)
_EMPTY_EXTENSIONS_SYMBOL_NAME = "grpc.testing.proto2.EmptyWithExtensions"
# Extension numbers for testing
_EMPTY_EXTENSIONS_NUMBERS = (
    124,
    125,
    126,
    127,
    128,
)

def _file_descriptor_to_proto(descriptor):
    """Convert a file descriptor to its protocol buffer representation.
    
    Args:
        descriptor: A file descriptor object.
        
    Returns:
        bytes: Serialized FileDescriptorProto message.
    """
    proto = descriptor_pb2.FileDescriptorProto()
    descriptor.CopyToProto(proto)
    return proto.SerializeToString()

class ReflectionServicerTest(AioTestBase):
    """Test cases for gRPC reflection service implementation."""
    
    async def setUp(self):
        """Set up test environment before each test method."""
        # Create and configure test server with reflection service
        self._server = aio.server()
        reflection.enable_server_reflection(_SERVICE_NAMES, self._server)
        port = self._server.add_insecure_port("[::]:0")
        await self._server.start()

        # Create client channel and stub for testing
        self._channel = aio.insecure_channel("localhost:%d" % port)
        self._stub = reflection_pb2_grpc.ServerReflectionStub(self._channel)

    async def tearDown(self):
        """Clean up test environment after each test method."""
        await self._server.stop(None)
        await self._channel.close()

    async def test_file_by_name(self):
        """Test getting file descriptor by filename."""
        requests = (
            reflection_pb2.ServerReflectionRequest(
                file_by_filename=_EMPTY_PROTO_FILE_NAME
            ),
            reflection_pb2.ServerReflectionRequest(
                file_by_filename="i-donut-exist"  # Non-existent file test case
            ),
        )
        
        # Collect responses from the server
        responses = []
        async for response in self._stub.ServerReflectionInfo(iter(requests)):
            responses.append(response)
            
        # Define expected responses for comparison
        expected_responses = (
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                file_descriptor_response=reflection_pb2.FileDescriptorResponse(
                    file_descriptor_proto=(
                        _file_descriptor_to_proto(empty_pb2.DESCRIPTOR),
                    )
                ),
                original_request=requests[0],
            ),
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                error_response=reflection_pb2.ErrorResponse(
                    error_code=grpc.StatusCode.NOT_FOUND.value[0],
                    error_message=grpc.StatusCode.NOT_FOUND.value[1].encode(),
                ),
                original_request=requests[1],
            ),
        )
        self.assertSequenceEqual(expected_responses, responses)

    async def test_file_by_symbol(self):
        """Test getting file descriptor containing a specific symbol."""
        requests = (
            reflection_pb2.ServerReflectionRequest(
                file_containing_symbol=_EMPTY_PROTO_SYMBOL_NAME
            ),
            reflection_pb2.ServerReflectionRequest(
                file_containing_symbol="i.donut.exist.co.uk.org.net.me.name.foo"  # Non-existent symbol
            ),
        )
        responses = []
        async for response in self._stub.ServerReflectionInfo(iter(requests)):
            responses.append(response)
            
        expected_responses = (
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                file_descriptor_response=reflection_pb2.FileDescriptorResponse(
                    file_descriptor_proto=(
                        _file_descriptor_to_proto(empty_pb2.DESCRIPTOR),
                    )
                ),
                original_request=requests[0],
            ),
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                error_response=reflection_pb2.ErrorResponse(
                    error_code=grpc.StatusCode.NOT_FOUND.value[0],
                    error_message=grpc.StatusCode.NOT_FOUND.value[1].encode(),
                ),
                original_request=requests[1],
            ),
        )
        self.assertSequenceEqual(expected_responses, responses)

    async def test_file_containing_extension(self):
        """Test getting file descriptor containing a specific extension."""
        requests = (
            reflection_pb2.ServerReflectionRequest(
                file_containing_extension=reflection_pb2.ExtensionRequest(
                    containing_type=_EMPTY_EXTENSIONS_SYMBOL_NAME,
                    extension_number=125,
                ),
            ),
            reflection_pb2.ServerReflectionRequest(
                file_containing_extension=reflection_pb2.ExtensionRequest(
                    containing_type="i.donut.exist.co.uk.org.net.me.name.foo",
                    extension_number=55,
                ),
            ),
        )
        responses = []
        async for response in self._stub.ServerReflectionInfo(iter(requests)):
            responses.append(response)
            
        expected_responses = (
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                file_descriptor_response=reflection_pb2.FileDescriptorResponse(
                    file_descriptor_proto=(
                        _file_descriptor_to_proto(
                            empty2_extensions_pb2.DESCRIPTOR
                        ),
                        _file_descriptor_to_proto(empty2_pb2.DESCRIPTOR),
                    )
                ),
                original_request=requests[0],
            ),
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                error_response=reflection_pb2.ErrorResponse(
                    error_code=grpc.StatusCode.NOT_FOUND.value[0],
                    error_message=grpc.StatusCode.NOT_FOUND.value[1].encode(),
                ),
                original_request=requests[1],
            ),
        )
        self.assertSequenceEqual(expected_responses, responses)

    async def test_extension_numbers_of_type(self):
        """Test getting all extension numbers for a given type."""
        requests = (
            reflection_pb2.ServerReflectionRequest(
                all_extension_numbers_of_type=_EMPTY_EXTENSIONS_SYMBOL_NAME
            ),
            reflection_pb2.ServerReflectionRequest(
                all_extension_numbers_of_type="i.donut.exist.co.uk.net.name.foo"  # Non-existent type
            ),
        )
        responses = []
        async for response in self._stub.ServerReflectionInfo(iter(requests)):
            responses.append(response)
            
        expected_responses = (
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                all_extension_numbers_response=reflection_pb2.ExtensionNumberResponse(
                    base_type_name=_EMPTY_EXTENSIONS_SYMBOL_NAME,
                    extension_number=_EMPTY_EXTENSIONS_NUMBERS,
                ),
                original_request=requests[0],
            ),
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                error_response=reflection_pb2.ErrorResponse(
                    error_code=grpc.StatusCode.NOT_FOUND.value[0],
                    error_message=grpc.StatusCode.NOT_FOUND.value[1].encode(),
                ),
                original_request=requests[1],
            ),
        )
        self.assertSequenceEqual(expected_responses, responses)

    async def test_list_services(self):
        """Test listing all services available on the server."""
        requests = (
            reflection_pb2.ServerReflectionRequest(
                list_services="",
            ),
        )
        responses = []
        async for response in self._stub.ServerReflectionInfo(iter(requests)):
            responses.append(response)
            
        expected_responses = (
            reflection_pb2.ServerReflectionResponse(
                valid_host="",
                list_services_response=reflection_pb2.ListServiceResponse(
                    service=tuple(
                        reflection_pb2.ServiceResponse(name=name)
                        for name in _SERVICE_NAMES
                    )
                ),
                original_request=requests[0],
            ),
        )
        self.assertSequenceEqual(expected_responses, responses)

    def test_reflection_service_name(self):
        """Test that the reflection service name is correct."""
        self.assertEqual(
            reflection.SERVICE_NAME, "grpc.reflection.v1alpha.ServerReflection"
        )

if __name__ == "__main__":
    # Configure logging and run tests
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```