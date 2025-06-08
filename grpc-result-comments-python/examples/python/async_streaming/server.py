Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import necessary libraries
from concurrent.futures import ThreadPoolExecutor
import logging
import threading
import time
from typing import Iterable

from google.protobuf.json_format import MessageToJson
import grpc

# Import protocol buffer definitions
import phone_pb2
import phone_pb2_grpc

def create_state_response(
    call_state: phone_pb2.CallState.State,
) -> phone_pb2.StreamCallResponse:
    """Creates a response message with the given call state.
    
    Args:
        call_state: The state of the call to include in the response.
        
    Returns:
        A StreamCallResponse message containing the specified call state.
    """
    response = phone_pb2.StreamCallResponse()
    response.call_state.state = call_state
    return response

class Phone(phone_pb2_grpc.PhoneServicer):
    """Implementation of the Phone service defined in phone.proto."""
    
    def __init__(self):
        """Initialize the Phone service with a thread-safe ID counter."""
        self._id_counter = 0  # Counter for generating unique session IDs
        self._lock = threading.RLock()  # Reentrant lock for thread safety

    def _create_call_session(self) -> phone_pb2.CallInfo:
        """Creates a new call session with a unique ID and media URL.
        
        Returns:
            A CallInfo message containing the session details.
        """
        call_info = phone_pb2.CallInfo()
        with self._lock:
            call_info.session_id = str(self._id_counter)
            self._id_counter += 1
        call_info.media = "https://link.to.audio.resources"
        logging.info("Created a call session [%s]", MessageToJson(call_info))
        return call_info

    def _clean_call_session(self, call_info: phone_pb2.CallInfo) -> None:
        """Logs the cleanup of a call session.
        
        Args:
            call_info: The CallInfo message of the session being cleaned.
        """
        logging.info("Call session cleaned [%s]", MessageToJson(call_info))

    def StreamCall(
        self,
        request_iterator: Iterable[phone_pb2.StreamCallRequest],
        context: grpc.ServicerContext,
    ) -> Iterable[phone_pb2.StreamCallResponse]:
        """Implements the streaming RPC for phone calls.
        
        Handles the call lifecycle: NEW -> ACTIVE -> ENDED states.
        
        Args:
            request_iterator: Iterator of incoming call requests.
            context: gRPC servicer context.
            
        Yields:
            A series of StreamCallResponse messages representing call state changes.
            
        Raises:
            RuntimeError: If no call request is received.
        """
        try:
            # Get the first request from the iterator
            request = next(request_iterator)
            logging.info(
                "Received a phone call request for number [%s]",
                request.phone_number,
            )
        except StopIteration:
            raise RuntimeError("Failed to receive call request")

        # Simulate call setup delay
        time.sleep(1)
        yield create_state_response(phone_pb2.CallState.NEW)

        # Create call session and set cleanup callback
        time.sleep(1)
        call_info = self._create_call_session()
        context.add_callback(lambda: self._clean_call_session(call_info))
        response = phone_pb2.StreamCallResponse()
        response.call_info.session_id = call_info.session_id
        response.call_info.media = call_info.media
        yield response
        yield create_state_response(phone_pb2.CallState.ACTIVE)

        # Simulate call duration and end the call
        time.sleep(2)
        yield create_state_response(phone_pb2.CallState.ENDED)
        logging.info("Call finished [%s]", request.phone_number)

def serve(address: str) -> None:
    """Starts the gRPC server and listens for incoming connections.
    
    Args:
        address: The network address to bind the server to.
    """
    server = grpc.server(ThreadPoolExecutor())
    phone_pb2_grpc.add_PhoneServicer_to_server(Phone(), server)
    server.add_insecure_port(address)
    server.start()
    logging.info("Server serving at %s", address)
    server.wait_for_termination()

if __name__ == "__main__":
    # Configure logging and start the server
    logging.basicConfig(level=logging.INFO)
    serve("[::]:50051")  # Listen on all IPv6 interfaces on port 50051
```