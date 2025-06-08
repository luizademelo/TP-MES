Here's the commented version of the code:

```python
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""A gRPC server servicing both Greeter and RouteGuide RPCs."""

from concurrent import futures
import logging
import math
import time

import grpc
import helloworld_pb2
import helloworld_pb2_grpc
import route_guide_pb2
import route_guide_pb2_grpc
import route_guide_resources

def _get_feature(feature_db, point):
    """Returns Feature at given location or None.
    
    Args:
        feature_db: Database of features to search through
        point: Location point to find feature for
    
    Returns:
        The Feature object if found, None otherwise
    """
    for feature in feature_db:
        if feature.location == point:
            return feature
    return None

def _get_distance(start, end):
    """Calculate the distance between two points using the Haversine formula.
    
    Args:
        start: First point with latitude/longitude
        end: Second point with latitude/longitude
    
    Returns:
        Distance between the points in meters
    """
    coord_factor = 10000000.0  # Conversion factor for coordinates
    # Convert coordinates from fixed-point to floating-point
    lat_1 = start.latitude / coord_factor
    lat_2 = end.latitude / coord_factor
    lon_1 = start.longitude / coord_factor
    lon_2 = end.longitude / coord_factor
    
    # Convert to radians
    lat_rad_1 = math.radians(lat_1)
    lat_rad_2 = math.radians(lat_2)
    delta_lat_rad = math.radians(lat_2 - lat_1)
    delta_lon_rad = math.radians(lon_2 - lon_1)

    # Haversine formula implementation
    a = pow(math.sin(delta_lat_rad / 2), 2) + (
        math.cos(lat_rad_1)
        * math.cos(lat_rad_2)
        * pow(math.sin(delta_lon_rad / 2), 2)
    )
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    R = 6371000  # Earth radius in meters

    return R * c

class _GreeterServicer(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of Greeter service."""
    
    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: HelloRequest containing the name
            context: RPC context
            
        Returns:
            HelloReply with a greeting message
        """
        return helloworld_pb2.HelloReply(
            message="Hello, {}!".format(request.name)
        )

class _RouteGuideServicer(route_guide_pb2_grpc.RouteGuideServicer):
    """Provides methods that implement functionality of route guide server."""

    def __init__(self):
        """Initializes the servicer with route guide database."""
        self.db = route_guide_resources.read_route_guide_database()

    def GetFeature(self, request, context):
        """Gets the Feature at given Point.
        
        If no feature exists at the point, returns an empty feature.
        """
        feature = _get_feature(self.db, request)
        if feature is None:
            return route_guide_pb2.Feature(name="", location=request)
        else:
            return feature

    def ListFeatures(self, request, context):
        """Lists all features within the given bounding Rectangle.
        
        Results are streamed rather than returned at once.
        """
        # Determine the bounding box coordinates
        left = min(request.lo.longitude, request.hi.longitude)
        right = max(request.lo.longitude, request.hi.longitude)
        top = max(request.lo.latitude, request.hi.latitude)
        bottom = min(request.lo.latitude, request.hi.latitude)
        
        # Stream all features within the bounding box
        for feature in self.db:
            if (
                feature.location.longitude >= left
                and feature.location.longitude <= right
                and feature.location.latitude >= bottom
                and feature.location.latitude <= top
            ):
                yield feature

    def RecordRoute(self, request_iterator, context):
        """Records a route and returns a RouteSummary.
        
        Receives a stream of Points, and responds with statistics about the route.
        """
        point_count = 0
        feature_count = 0
        distance = 0.0
        prev_point = None

        start_time = time.time()
        for point in request_iterator:
            point_count += 1
            if _get_feature(self.db, point):
                feature_count += 1
            if prev_point:
                distance += _get_distance(prev_point, point)
            prev_point = point

        elapsed_time = time.time() - start_time
        return route_guide_pb2.RouteSummary(
            point_count=point_count,
            feature_count=feature_count,
            distance=int(distance),
            elapsed_time=int(elapsed_time),
        )

    def RouteChat(self, request_iterator, context):
        """Receives a stream of RouteNotes while sending previous notes at same locations.
        
        Implements a bidirectional streaming RPC.
        """
        prev_notes = []
        for new_note in request_iterator:
            # Send all previous notes at this location first
            for prev_note in prev_notes:
                if prev_note.location == new_note.location:
                    yield prev_note
            # Add new note to history
            prev_notes.append(new_note)

def serve():
    """Starts the gRPC server and listens for incoming connections.
    
    Configures and starts both Greeter and RouteGuide services.
    """
    # Create a thread pool for handling requests
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Add both services to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(
        _GreeterServicer(), server
    )
    route_guide_pb2_grpc.add_RouteGuideServicer_to_server(
        _RouteGuideServicer(), server
    )
    
    # Start listening on port 50051
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()

if __name__ == "__main__":
    logging.basicConfig()
    serve()
```

The comments added:
1. Added detailed docstrings for all functions and methods
2. Explained the purpose of each class and method
3. Documented parameters and return values
4. Added explanations for key algorithms (like the Haversine formula in _get_distance)
5. Clarified the streaming behavior in ListFeatures and RouteChat
6. Explained the server setup process in serve()
7. Added context about the overall purpose of each component

The comments maintain a consistent style while providing useful information for future maintainers without being overly verbose. They explain both what the code does and why it does it in key places.