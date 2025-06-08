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
"""A client that makes both Greeter and RouteGuide RPCs."""

from __future__ import print_function

import logging
import random
import time

import grpc
import helloworld_pb2
import helloworld_pb2_grpc
import route_guide_pb2
import route_guide_pb2_grpc
import route_guide_resources

def make_route_note(message, latitude, longitude):
    """Create and return a RouteNote message with the given message and location.
    
    Args:
        message: The text message for the RouteNote
        latitude: Latitude coordinate of the location
        longitude: Longitude coordinate of the location
        
    Returns:
        A RouteNote protobuf message
    """
    return route_guide_pb2.RouteNote(
        message=message,
        location=route_guide_pb2.Point(latitude=latitude, longitude=longitude),
    )

def guide_get_one_feature(route_guide_stub, point):
    """Get and print a single feature from the RouteGuide service at the given point.
    
    Args:
        route_guide_stub: The RouteGuide service stub
        point: Point protobuf message containing latitude/longitude coordinates
    """
    feature = route_guide_stub.GetFeature(point)
    if not feature.location:
        print("Server returned incomplete feature")
        return

    if feature.name:
        print("Feature called %s at %s" % (feature.name, feature.location))
    else:
        print("Found no feature at %s" % feature.location)

def guide_get_feature(route_guide_stub):
    """Get and print features for two specific points."""
    guide_get_one_feature(
        route_guide_stub,
        route_guide_pb2.Point(latitude=409146138, longitude=-746188906),
    )
    guide_get_one_feature(
        route_guide_stub, route_guide_pb2.Point(latitude=0, longitude=0)
    )

def guide_list_features(route_guide_stub):
    """List and print all features within a rectangular area.
    
    Args:
        route_guide_stub: The RouteGuide service stub
    """
    rectangle = route_guide_pb2.Rectangle(
        lo=route_guide_pb2.Point(latitude=400000000, longitude=-750000000),
        hi=route_guide_pb2.Point(latitude=420000000, longitude=-730000000),
    )
    print("Looking for features between 40, -75 and 42, -73")

    features = route_guide_stub.ListFeatures(rectangle)

    for feature in features:
        print("Feature called %s at %s" % (feature.name, feature.location))

def generate_route(feature_list):
    """Generate a stream of random points from the feature list.
    
    Args:
        feature_list: List of available features
        
    Yields:
        Point protobuf messages with random locations from the feature list
    """
    for _ in range(0, 10):
        random_feature = feature_list[random.randint(0, len(feature_list) - 1)]
        print("Visiting point %s" % random_feature.location)
        yield random_feature.location
        time.sleep(random.uniform(0.5, 1.5))

def guide_record_route(route_guide_stub):
    """Record a route by sending a stream of points and print the summary.
    
    Args:
        route_guide_stub: The RouteGuide service stub
    """
    feature_list = route_guide_resources.read_route_guide_database()

    route_iterator = generate_route(feature_list)
    route_summary = route_guide_stub.RecordRoute(route_iterator)
    print("Finished trip with %s points " % route_summary.point_count)
    print("Passed %s features " % route_summary.feature_count)
    print("Travelled %s meters " % route_summary.distance)
    print("It took %s seconds " % route_summary.elapsed_time)

def generate_messages():
    """Generate a stream of predefined route chat messages.
    
    Yields:
        RouteNote protobuf messages with predefined content
    """
    messages = [
        make_route_note("First message", 0, 0),
        make_route_note("Second message", 0, 1),
        make_route_note("Third message", 1, 0),
        make_route_note("Fourth message", 0, 0),
        make_route_note("Fifth message", 1, 0),
    ]
    for msg in messages:
        print("Sending %s at %s" % (msg.message, msg.location))
        yield msg
        time.sleep(random.uniform(0.5, 1.0))

def guide_route_chat(route_guide_stub):
    """Conduct a route chat by sending messages and printing responses.
    
    Args:
        route_guide_stub: The RouteGuide service stub
    """
    responses = route_guide_stub.RouteChat(generate_messages())
    for response in responses:
        print(
            "Received message %s at %s" % (response.message, response.location)
        )

def run():
    """Main function that runs all the RouteGuide and Greeter client operations."""
    # Create an insecure channel to the server
    with grpc.insecure_channel("localhost:50051") as channel:
        # Create stubs for both services
        greeter_stub = helloworld_pb2_grpc.GreeterStub(channel)
        route_guide_stub = route_guide_pb2_grpc.RouteGuideStub(channel)
        
        # Make a simple Greeter call
        greeter_response = greeter_stub.SayHello(
            helloworld_pb2.HelloRequest(name="you")
        )
        print("Greeter client received: " + greeter_response.message)
        
        # Execute all RouteGuide service demonstrations
        print("-------------- GetFeature --------------")
        guide_get_feature(route_guide_stub)
        print("-------------- ListFeatures --------------")
        guide_list_features(route_guide_stub)
        print("-------------- RecordRoute --------------")
        guide_record_route(route_guide_stub)
        print("-------------- RouteChat --------------")
        guide_route_chat(route_guide_stub)

if __name__ == "__main__":
    logging.basicConfig()
    run()
```

Key improvements made:
1. Added detailed docstrings for each function explaining purpose, arguments, and return values
2. Added comments for important blocks of code
3. Improved the license header formatting
4. Added explanation for the main execution flow
5. Clarified the purpose of generator functions
6. Added context about gRPC stubs and channel usage

The comments maintain a consistent style and provide enough detail to understand the code's functionality without being overly verbose.