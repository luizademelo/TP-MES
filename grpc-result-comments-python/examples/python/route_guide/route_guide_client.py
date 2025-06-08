Here's the commented version of the code:

```python
# Copyright 2015 gRPC authors.
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
"""The Python implementation of the gRPC route guide client."""

from __future__ import print_function

import logging
import random

import grpc
import route_guide_pb2
import route_guide_pb2_grpc
import route_guide_resources


def make_route_note(message, latitude, longitude):
    """Creates a RouteNote message with the given message and coordinates.
    
    Args:
        message: The text message for the RouteNote
        latitude: Latitude coordinate
        longitude: Longitude coordinate
    
    Returns:
        A RouteNote protobuf message
    """
    return route_guide_pb2.RouteNote(
        message=message,
        location=route_guide_pb2.Point(latitude=latitude, longitude=longitude),
    )


def format_point(point):
    """Formats a Point message into a human-readable string.
    
    Args:
        point: A Point protobuf message
        
    Returns:
        Formatted string with latitude and longitude
    """
    return "latitude: %d, longitude: %d" % (point.latitude, point.longitude)


def guide_get_one_feature(stub, point):
    """Requests a single feature from the server at the given point.
    
    Args:
        stub: The gRPC client stub
        point: Point protobuf message with coordinates to check
    """
    feature = stub.GetFeature(point)
    if not feature.location:
        print("Server returned incomplete feature")
        return

    if feature.name:
        print(
            "Feature called %r at %s"
            % (feature.name, format_point(feature.location))
        )
    else:
        print("Found no feature at %s" % format_point(feature.location))


def guide_get_feature(stub):
    """Demonstrates getting features by checking two specific points."""
    guide_get_one_feature(
        stub, route_guide_pb2.Point(latitude=409146138, longitude=-746188906)
    )
    guide_get_one_feature(stub, route_guide_pb2.Point(latitude=0, longitude=0))


def guide_list_features(stub):
    """Lists features within a rectangular area defined by lo and hi points.
    
    Args:
        stub: The gRPC client stub
    """
    rectangle = route_guide_pb2.Rectangle(
        lo=route_guide_pb2.Point(latitude=400000000, longitude=-750000000),
        hi=route_guide_pb2.Point(latitude=420000000, longitude=-730000000),
    )
    print("Looking for features between 40, -75 and 42, -73")

    features = stub.ListFeatures(rectangle)

    for feature in features:
        print(
            "Feature called %r at %s"
            % (feature.name, format_point(feature.location))
        )


def generate_route(feature_list):
    """Generates a sequence of random points from the feature database.
    
    Args:
        feature_list: List of features to choose from
        
    Yields:
        Point messages for the route
    """
    for _ in range(0, 10):
        random_feature = random.choice(feature_list)
        print("Visiting point %s" % format_point(random_feature.location))
        yield random_feature.location


def guide_record_route(stub):
    """Records a route by sending a sequence of points to the server.
    
    Args:
        stub: The gRPC client stub
    """
    feature_list = route_guide_resources.read_route_guide_database()

    route_iterator = generate_route(feature_list)
    route_summary = stub.RecordRoute(route_iterator)
    print("Finished trip with %s points " % route_summary.point_count)
    print("Passed %s features " % route_summary.feature_count)
    print("Travelled %s meters " % route_summary.distance)
    print("It took %s seconds " % route_summary.elapsed_time)


def generate_messages():
    """Generates a sequence of RouteNote messages with predefined content.
    
    Yields:
        RouteNote messages with different locations
    """
    messages = [
        make_route_note("First message", 0, 0),
        make_route_note("Second message", 0, 1),
        make_route_note("Third message", 1, 0),
        make_route_note("Fourth message", 0, 0),
        make_route_note("Fifth message", 1, 0),
    ]
    for msg in messages:
        print("Sending %s at %s" % (msg.message, format_point(msg.location)))
        yield msg


def guide_route_chat(stub):
    """Demonstrates bidirectional streaming by sending and receiving RouteNotes.
    
    Args:
        stub: The gRPC client stub
    """
    responses = stub.RouteChat(generate_messages())
    for response in responses:
        print(
            "Received message %s at %s"
            % (response.message, format_point(response.location))
        )


def run():
    """Main function that runs all the gRPC client demonstrations."""
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = route_guide_pb2_grpc.RouteGuideStub(channel)
        print("-------------- GetFeature --------------")
        guide_get_feature(stub)
        print("-------------- ListFeatures --------------")
        guide_list_features(stub)
        print("-------------- RecordRoute --------------")
        guide_record_route(stub)
        print("-------------- RouteChat --------------")
        guide_route_chat(stub)


if __name__ == "__main__":
    logging.basicConfig()
    run()
```

Key improvements made:
1. Added detailed docstrings for each function explaining purpose, arguments, and return values
2. Added comments explaining the overall flow and purpose of each section
3. Maintained consistent formatting and style
4. Added clarification about streaming operations and protocol buffer messages
5. Documented the main execution flow in the run() function

The comments now provide comprehensive documentation while maintaining readability and following Python conventions.