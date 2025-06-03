Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// Include necessary headers for gRPC server functionality
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

// Standard library includes
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

// Abseil flags and logging
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "helper.h"

// Protocol buffer generated headers
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif

// Using declarations for gRPC and routeguide protobuf classes
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using routeguide::Feature;
using routeguide::Point;
using routeguide::Rectangle;
using routeguide::RouteGuide;
using routeguide::RouteNote;
using routeguide::RouteSummary;
using std::chrono::system_clock;

/**
 * Converts degrees to radians.
 * @param num Angle in degrees
 * @return Angle in radians
 */
float ConvertToRadians(float num) { return num * 3.1415926 / 180; }

/**
 * Calculates the distance between two geographic points using the Haversine formula.
 * @param start Starting point
 * @param end Ending point
 * @return Distance in meters between the points
 */
float GetDistance(const Point& start, const Point& end) {
  const float kCoordFactor = 10000000.0;  // Scaling factor for coordinates
  float lat_1 = start.latitude() / kCoordFactor;
  float lat_2 = end.latitude() / kCoordFactor;
  float lon_1 = start.longitude() / kCoordFactor;
  float lon_2 = end.longitude() / kCoordFactor;
  float lat_rad_1 = ConvertToRadians(lat_1);
  float lat_rad_2 = ConvertToRadians(lat_2);
  float delta_lat_rad = ConvertToRadians(lat_2 - lat_1);
  float delta_lon_rad = ConvertToRadians(lon_2 - lon_1);

  // Haversine formula components
  float a = pow(sin(delta_lat_rad / 2), 2) +
            cos(lat_rad_1) * cos(lat_rad_2) * pow(sin(delta_lon_rad / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int R = 6371000;  // Earth's radius in meters

  return R * c;
}

/**
 * Finds the name of a feature at a given point.
 * @param point The point to check
 * @param feature_list List of available features
 * @return Feature name if found, empty string otherwise
 */
std::string GetFeatureName(const Point& point,
                           const std::vector<Feature>& feature_list) {
  for (const Feature& f : feature_list) {
    if (f.location().latitude() == point.latitude() &&
        f.location().longitude() == point.longitude()) {
      return f.name();
    }
  }
  return "";
}

/**
 * Implementation of the RouteGuide service.
 */
class RouteGuideImpl final : public RouteGuide::Service {
 public:
  /**
   * Constructor that loads feature database.
   * @param db Path to the feature database file
   */
  explicit RouteGuideImpl(const std::string& db) {
    routeguide::ParseDb(db, &feature_list_);
  }

  /**
   * Gets the feature at the given point.
   * Implements the GetFeature RPC method.
   */
  Status GetFeature(ServerContext* context, const Point* point,
                    Feature* feature) override {
    feature->set_name(GetFeatureName(*point, feature_list_));
    feature->mutable_location()->CopyFrom(*point);
    return Status::OK;
  }

  /**
   * Lists all features within the given rectangle.
   * Implements the ListFeatures RPC method.
   */
  Status ListFeatures(ServerContext* context,
                      const routeguide::Rectangle* rectangle,
                      ServerWriter<Feature>* writer) override {
    auto lo = rectangle->lo();
    auto hi = rectangle->hi();
    // Determine the bounding box coordinates
    long left = (std::min)(lo.longitude(), hi.longitude());
    long right = (std::max)(lo.longitude(), hi.longitude());
    long top = (std::max)(lo.latitude(), hi.latitude());
    long bottom = (std::min)(lo.latitude(), hi.latitude());
    
    // Write all features within the bounding box to the stream
    for (const Feature& f : feature_list_) {
      if (f.location().longitude() >= left &&
          f.location().longitude() <= right &&
          f.location().latitude() >= bottom && f.location().latitude() <= top) {
        writer->Write(f);
      }
    }
    return Status::OK;
  }

  /**
   * Records a route composed of a sequence of points.
   * Implements the RecordRoute RPC method.
   */
  Status RecordRoute(ServerContext* context, ServerReader<Point>* reader,
                     RouteSummary* summary) override {
    Point point;
    int point_count = 0;
    int feature_count = 0;
    float distance = 0.0;
    Point previous;

    system_clock::time_point start_time = system_clock::now();
    // Process each point in the stream
    while (reader->Read(&point)) {
      point_count++;
      if (!GetFeatureName(point, feature_list_).empty()) {
        feature_count++;
      }
      if (point_count != 1) {
        distance += GetDistance(previous, point);
      }
      previous = point;
    }
    
    // Calculate and set summary statistics
    system_clock::time_point end_time = system_clock::now();
    summary->set_point_count(point_count);
    summary->set_feature_count(feature_count);
    summary->set_distance(static_cast<long>(distance));
    auto secs =
        std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    summary->set_elapsed_time(secs.count());

    return Status::OK;
  }

  /**
   * Receives a stream of route notes, and sends back previous notes for locations.
   * Implements the RouteChat RPC method.
   */
  Status RouteChat(ServerContext* context,
                   ServerReaderWriter<RouteNote, RouteNote>* stream) override {
    RouteNote note;
    while (stream->Read(&note)) {
      std::unique_lock<std::mutex> lock(mu_);
      // Send back all previous notes for this location
      for (const RouteNote& n : received_notes_) {
        if (n.location().latitude() == note.location().latitude() &&
            n.location().longitude() == note.location().longitude()) {
          stream->Write(n);
        }
      }
      // Store the new note
      received_notes_.push_back(note);
    }

    return Status::OK;
  }

 private:
  std::vector<Feature> feature_list_;      // List of available features
  std::mutex mu_;                          // Mutex for thread safety
  std::vector<RouteNote> received_notes_;  // History of received route notes
};

/**
 * Runs the RouteGuide server.
 * @param db_path Path to the feature database file
 */
void RunServer(const std::string& db_path) {
  std::string server_address("0.0.0.0:50051");
  RouteGuideImpl service(db_path);

  // Set up and start the gRPC server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get database content and start the server
  std::string db = routeguide::GetDbFileContent(argc, argv);
  RunServer(db);

  return 0;
}
```

The comments added explain:
1. The purpose of each function and method
2. Key algorithms (like the Haversine formula in GetDistance)
3. The flow of data in RPC methods
4. Important implementation details
5. Thread safety considerations
6. The overall structure and purpose of the service

The comments are designed to help future developers understand the code quickly while maintaining it or adding new features. They explain both what the code does and why it does it that way.