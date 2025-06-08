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
"""The Python implementation of the gRPC route guide server."""

from concurrent import futures
import logging
import math
import time

import grpc
import route_guide_pb2
import route_guide_pb2_grpc
import route_guide_resources

def get_feature(feature_db, point):
    """
    Returns the Feature at the given location point from the feature database.
    
    Args:
        feature_db: Database of features to search through
        point: Location point to find feature for
        
    Returns:
        The matching Feature if found, None otherwise
    """
    for feature in feature_db:
        if feature.location == point:
            return feature
    return None

def get_distance(start, end):
    """
    Calculates the distance between two geographic points using the Haversine formula.
    
    Args:
        start: Starting location point
        end: Ending location point
        
    Returns:
        Distance between points in meters
    """
    coord_factor = 10000000.0  # Conversion factor for coordinates
    # Convert coordinates from fixed-point to degrees
    lat_1 = start.latitude / coord_factor
    lat_2 = end.latitude / coord_factor
    lon_1 = start.longitude / coord_factor
    lon_2 = end.longitude / coord_factor
    
    # Convert degrees to radians
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
    R = 6371000  # Earth's radius in meters

    return R * c

class RouteGuideServicer(route_guide_pb2_grpc.RouteGuideServicer):
    """Implements the RouteGuide service methods."""

    def __init__(self):
        """Initializes the servicer with the route guide database."""
        self.db = route_guide_resources.read_route_guide_database()

    def GetFeature(self, request, context):
        """
        Gets the Feature at the requested point.
        
        Args:
            request: Point message containing location coordinates
            context: gRPC context
            
        Returns:
            Feature at the requested location or an empty Feature if not found
        """
        feature = get_feature(self.db, request)
        if feature is None:
            return route_guide_pb2.Feature(name="", location=request)
        else:
            return feature

    def ListFeatures(self, request, context):
        """
        Lists all Features within a given rectangular area.
        
        Args:
            request: Rectangle message defining search area boundaries
            context: gRPC context
            
        Yields:
            Features that fall within the requested area
        """
        # Determine the area boundaries
        left = min(request.lo.longitude, request.hi.longitude)
        right = max(request.lo.longitude, request.hi.longitude)
        top = max(request.lo.latitude, request.hi.latitude)
        bottom = min(request.lo.latitude, request.hi.latitude)
        
        # Yield all features that fall within the boundaries
        for feature in self.db:
            if (
                feature.location.longitude >= left
                and feature.location.longitude <= right
                and feature.location.latitude >= bottom
                and feature.location.latitude <= top
            ):
                yield feature

    def RecordRoute(self, request_iterator, context):
        """
        Records a route and computes statistics about the trip.
        
        Args:
            request_iterator: Stream of Points representing the route
            context: gRPC context
            
        Returns:
            RouteSummary containing statistics about the trip
        """
        point_count = 0
        feature_count = 0
        distance = 0.0
        prev_point = None

        start_time = time.time()
        for point in request_iterator:
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

    def RouteChat(self, request_iterator, context):
        """
        Receives a stream of route notes, while sending back previous notes
        for locations that match incoming notes.
        
        Args:
            request_iterator: Stream of RouteNote messages
            context: gRPC context
            
        Yields:
            Previous notes for locations that match incoming notes
        """
        prev_notes = []
        for new_note in request_iterator:
            # Check if any previous notes match the new note's location
            for prev_note in prev_notes:
                if prev_note.location == new_note.location:
                    yield prev_note
            # Add the new note to the history
            prev_notes.append(new_note)

def serve():
    """
    Starts the gRPC server and listens for incoming requests.
    """
    # Create a thread pool for handling requests
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    # Add the RouteGuide service implementation
    route_guide_pb2_grpc.add_RouteGuideServicer_to_server(
        RouteGuideServicer(), server
    )
    # Listen on port 50051
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()

if __name__ == "__main__":
    logging.basicConfig()
    serve()
```