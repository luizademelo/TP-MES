Here's the commented version of the code:

```python
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python AsyncIO implementation of the gRPC route guide server."""

import asyncio
import logging
import math
import time
from typing import AsyncIterable, Iterable

import grpc
import route_guide_pb2
import route_guide_pb2_grpc
import route_guide_resources

def get_feature(
    feature_db: Iterable[route_guide_pb2.Feature], point: route_guide_pb2.Point
) -> route_guide_pb2.Feature:
    """
    Returns Feature at given location or None if not found.
    
    Args:
        feature_db: An iterable collection of Feature objects to search through
        point: The Point location to search for in the feature database
    
    Returns:
        The Feature object at the given location, or None if not found
    """
    for feature in feature_db:
        if feature.location == point:
            return feature
    return None

def get_distance(
    start: route_guide_pb2.Point, end: route_guide_pb2.Point
) -> float:
    """
    Calculate the distance between two geographic points using the Haversine formula.
    
    Args:
        start: The starting Point (latitude/longitude)
        end: The ending Point (latitude/longitude)
    
    Returns:
        The distance between the points in meters
    """
    coord_factor = 10000000.0  # Conversion factor from proto units to degrees
    lat_1 = start.latitude / coord_factor
    lat_2 = end.latitude / coord_factor
    lon_1 = start.longitude / coord_factor
    lon_2 = end.longitude / coord_factor
    
    # Convert to radians
    lat_rad_1 = math.radians(lat_1)
    lat_rad_2 = math.radians(lat_2)
    delta_lat_rad = math.radians(lat_2 - lat_1)
    delta_lon_rad = math.radians(lon_2 - lon_1)

    # Haversine formula components
    a = pow(math.sin(delta_lat_rad / 2), 2) + (
        math.cos(lat_rad_1)
        * math.cos(lat_rad_2)
        * pow(math.sin(delta_lon_rad / 2), 2)
    )
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    R = 6371000  # Earth radius in meters

    return R * c

class RouteGuideServicer(route_guide_pb2_grpc.RouteGuideServicer):
    """Provides methods that implement functionality of route guide server."""

    def __init__(self) -> None:
        """Initializes the servicer by loading the route guide database."""
        self.db = route_guide_resources.read_route_guide_database()

    def GetFeature(
        self, request: route_guide_pb2.Point, unused_context
    ) -> route_guide_pb2.Feature:
        """
        Gets the Feature at the requested Point.
        
        Args:
            request: The Point location to find features for
            unused_context: gRPC context (unused in this implementation)
        
        Returns:
            Feature at the given location. Returns an empty Feature if not found.
        """
        feature = get_feature(self.db, request)
        if feature is None:
            return route_guide_pb2.Feature(name="", location=request)
        else:
            return feature

    async def ListFeatures(
        self, request: route_guide_pb2.Rectangle, unused_context
    ) -> AsyncIterable[route_guide_pb2.Feature]:
        """
        Lists all Features within the given Rectangle.
        
        Args:
            request: The Rectangle defining the search area
            unused_context: gRPC context (unused in this implementation)
        
        Yields:
            All Features that fall within the given Rectangle
        """
        # Determine the bounding box coordinates
        left = min(request.lo.longitude, request.hi.longitude)
        right = max(request.lo.longitude, request.hi.longitude)
        top = max(request.lo.latitude, request.hi.latitude)
        bottom = min(request.lo.latitude, request.hi.latitude)
        
        # Yield all features within the bounding box
        for feature in self.db:
            if (
                feature.location.longitude >= left
                and feature.location.longitude <= right
                and feature.location.latitude >= bottom
                and feature.location.latitude <= top
            ):
                yield feature

    async def RecordRoute(
        self,
        request_iterator: AsyncIterable[route_guide_pb2.Point],
        unused_context,
    ) -> route_guide_pb2.RouteSummary:
        """
        Records a route composed of a sequence of Points.
        
        Args:
            request_iterator: Async iterator of Points along the route
            unused_context: gRPC context (unused in this implementation)
        
        Returns:
            RouteSummary containing statistics about the traversed route
        """
        point_count = 0
        feature_count = 0
        distance = 0.0
        prev_point = None

        start_time = time.time()
        async for point in request_iterator:
            point_count += 1
            if get_feature(self.db, point):
                feature_count += 1
            if prev_point:
                distance += get_distance(prev_point, point)
            prev_point = point

        elapsed_time = time.time() - start_time
        return route_guide_pb2.RouteSummary(
            point_count=point_count,
            feature_count=feature_count,
            distance=int(distance),
            elapsed_time=int(elapsed_time),
        )

    async def RouteChat(
        self,
        request_iterator: AsyncIterable[route_guide_pb2.RouteNote],
        unused_context,
    ) -> AsyncIterable[route_guide_pb2.RouteNote]:
        """
        Receives a stream of RouteNotes and returns a stream of all previous
        RouteNotes at each of those locations (bidirectional streaming RPC).
        
        Args:
            request_iterator: Async iterator of incoming RouteNotes
            unused_context: gRPC context (unused in this implementation)
        
        Yields:
            All previous RouteNotes that were received at the same locations
            as each new RouteNote
        """
        prev_notes = []
        async for new_note in request_iterator:
            # Check all previous notes for matches with current location
            for prev_note in prev_notes:
                if prev_note.location == new_note.location:
                    yield prev_note
            prev_notes.append(new_note)

async def serve() -> None:
    """
    Starts the gRPC server and listens for incoming requests.
    """
    server = grpc.aio.server()
    route_guide_pb2_grpc.add_RouteGuideServicer_to_server(
        RouteGuideServicer(), server
    )
    server.add_insecure_port("[::]:50051")  # Listen on port 50051
    await server.start()
    await server.wait_for_termination()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    asyncio.get_event_loop().run_until_complete(serve())
```