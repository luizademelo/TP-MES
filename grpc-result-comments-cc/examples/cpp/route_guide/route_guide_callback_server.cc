Here's the commented version of the code:

```c++
/*
 * Copyright 2021 gRPC authors.
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
 */

// Standard library includes
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

// gRPC related includes
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

// Abseil (Google's utility library) includes
#include "absl/flags/parse.h"
#include "absl/log/globals.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "helper.h"

// Protocol buffer generated headers
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif

// Using declarations for cleaner code
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
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
  const float kCoordFactor = 10000000.0;  // Conversion factor for coordinates
  float lat_1 = start.latitude() / kCoordFactor;
  float lat_2 = end.latitude() / kCoordFactor;
  float lon_1 = start.longitude() / kCoordFactor;
  float lon_2 = end.longitude() / kCoordFactor;
  float lat_rad_1 = ConvertToRadians(lat_1);
  float lat_rad_2 = ConvertToRadians(lat_2);
  float delta_lat_rad = ConvertToRadians(lat_2 - lat_1);
  float delta_lon_rad = ConvertToRadians(lon_2 - lon_1);

  // Haversine formula implementation
  float a = pow(sin(delta_lat_rad / 2), 2) +
            cos(lat_rad_1) * cos(lat_rad_2) * pow(sin(delta_lon_rad / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int R = 6371000;  // Earth's radius in meters

  return R * c;
}

/**
 * Finds the name of a feature at a given point from a list of features.
 * @param point The point to search for
 * @param feature_list List of features to search through
 * @return Name of the feature if found, empty string otherwise
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
 * Provides four RPC methods for route guidance functionality.
 */
class RouteGuideImpl final : public RouteGuide::CallbackService {
 public:
  /**
   * Constructor that loads the feature database.
   * @param db Path to the database file
   */
  explicit RouteGuideImpl(const std::string& db) {
    routeguide::ParseDb(db, &feature_list_);
  }

  /**
   * RPC method to get a feature at a given point.
   * @param context Server context
   * @param point The point to check
   * @param feature Output parameter for the found feature
   * @return Server reactor for handling the RPC
   */
  grpc::ServerUnaryReactor* GetFeature(grpc::CallbackServerContext* context,
                                       const Point* point,
                                       Feature* feature) override {
    class Reactor : public grpc::ServerUnaryReactor {
     public:
      Reactor(const Point& point, const std::vector<Feature>& feature_list,
              Feature* feature) {
        feature->set_name(GetFeatureName(point, feature_list));
        *feature->mutable_location() = point;
        Finish(grpc::Status::OK);
      }

     private:
      void OnDone() override {
        LOG(INFO) << "RPC Completed";
        delete this;
      }

      void OnCancel() override { LOG(ERROR) << "RPC Cancelled"; }
    };
    return new Reactor(*point, feature_list_, feature);
  }

  /**
   * RPC method to list features within a given rectangle.
   * @param context Server context
   * @param rectangle The area to search within
   * @return Server reactor for handling the RPC
   */
  grpc::ServerWriteReactor<Feature>* ListFeatures(
      CallbackServerContext* context,
      const routeguide::Rectangle* rectangle) override {
    class Lister : public grpc::ServerWriteReactor<Feature> {
     public:
      Lister(const routeguide::Rectangle* rectangle,
             const std::vector<Feature>* feature_list)
          : left_((std::min)(rectangle->lo().longitude(),
                             rectangle->hi().longitude())),
            right_((std::max)(rectangle->lo().longitude(),
                              rectangle->hi().longitude())),
            top_((std::max)(rectangle->lo().latitude(),
                            rectangle->hi().latitude())),
            bottom_((std::min)(rectangle->lo().latitude(),
                               rectangle->hi().latitude())),
            feature_list_(feature_list),
            next_feature_(feature_list_->begin()) {
        NextWrite();
      }

      void OnWriteDone(bool ok) override {
        if (!ok) {
          Finish(Status(grpc::StatusCode::UNKNOWN, "Unexpected Failure"));
        }
        NextWrite();
      }

      void OnDone() override {
        LOG(INFO) << "RPC Completed";
        delete this;
      }

      void OnCancel() override { LOG(ERROR) << "RPC Cancelled"; }

     private:
      /**
       * Finds and writes the next feature within the rectangle bounds.
       */
      void NextWrite() {
        while (next_feature_ != feature_list_->end()) {
          const Feature& f = *next_feature_;
          next_feature_++;
          if (f.location().longitude() >= left_ &&
              f.location().longitude() <= right_ &&
              f.location().latitude() >= bottom_ &&
              f.location().latitude() <= top_) {
            StartWrite(&f);
            return;
          }
        }

        Finish(Status::OK);
      }
      const long left_;
      const long right_;
      const long top_;
      const long bottom_;
      const std::vector<Feature>* feature_list_;
      std::vector<Feature>::const_iterator next_feature_;
    };
    return new Lister(rectangle, &feature_list_);
  }

  /**
   * RPC method to record a route and return statistics.
   * @param context Server context
   * @param summary Output parameter for route statistics
   * @return Server reactor for handling the RPC
   */
  grpc::ServerReadReactor<Point>* RecordRoute(CallbackServerContext* context,
                                              RouteSummary* summary) override {
    class Recorder : public grpc::ServerReadReactor<Point> {
     public:
      Recorder(RouteSummary* summary, const std::vector<Feature>* feature_list)
          : start_time_(system_clock::now()),
            summary_(summary),
            feature_list_(feature_list) {
        StartRead(&point_);
      }

      void OnReadDone(bool ok) override {
        if (ok) {
          point_count_++;
          if (!GetFeatureName(point_, *feature_list_).empty()) {
            feature_count_++;
          }
          if (point_count_ != 1) {
            distance_ += GetDistance(previous_, point_);
          }
          previous_ = point_;
          StartRead(&point_);
        } else {
          summary_->set_point_count(point_count_);
          summary_->set_feature_count(feature_count_);
          summary_->set_distance(static_cast<long>(distance_));
          auto secs = std::chrono::duration_cast<std::chrono::seconds>(
              system_clock::now() - start_time_);
          summary_->set_elapsed_time(secs.count());
          Finish(Status::OK);
        }
      }

      void OnDone() override {
        LOG(INFO) << "RPC Completed";
        delete this;
      }

      void OnCancel() override { LOG(ERROR) << "RPC Cancelled"; }

     private:
      system_clock::time_point start_time_;
      RouteSummary* summary_;
      const std::vector<Feature>* feature_list_;
      Point point_;
      int point_count_ = 0;
      int feature_count_ = 0;
      float distance_ = 0.0;
      Point previous_;
    };
    return new Recorder(summary, &feature_list_);
  }

  /**
   * RPC method for bidirectional streaming of route notes.
   * @param context Server context
   * @return Server reactor for handling the RPC
   */
  grpc::ServerBidiReactor<RouteNote, RouteNote>* RouteChat(
      CallbackServerContext* context) override {
    class Chatter : public grpc::ServerBidiReactor<RouteNote, RouteNote> {
     public:
      Chatter(absl::Mutex* mu, std::vector<RouteNote>* received_notes)
          : mu_(mu), received_notes_(received_notes) {
        StartRead(&note_);
      }

      void OnReadDone(bool ok) override {
        if (ok) {
          mu_->Lock();
          std::copy_if(received_notes_->begin(), received_notes_->end(),
                       std::back_inserter(to_send_notes_),
                       [this](const RouteNote& note) {
                         return note.location().latitude() ==
                                    note_.location().latitude() &&
                                note.location().longitude() ==
                                    note_.location().longitude();
                       });
          mu_->Unlock();
          notes_iterator_ = to_send_notes_.begin();
          NextWrite();
        } else {
          Finish(Status::OK);
        }
      }
      void OnWriteDone(bool ) override { NextWrite(); }

      void OnDone() override {
        LOG(INFO) << "RPC Completed";
        delete this;
      }

      void OnCancel() override { LOG(ERROR) << "RPC Cancelled"; }

     private:
      /**
       * Handles the next write operation in the bidirectional stream.
       */
      void NextWrite() {
        if (notes_iterator_ != to_send_notes_.end()) {
          StartWrite(&*notes_iterator_);
          notes_iterator_++;
        } else {
          mu_->Lock();
          received_notes_->push_back(note_);
          mu_->Unlock();
          StartRead(&note_);
        }
      }

      RouteNote note_;
      absl::Mutex* mu_;
      std::vector<RouteNote>* received_notes_ ABSL_GUARDED_BY(mu_);
      std::vector<RouteNote> to_send_notes_;
      std::vector<RouteNote>::iterator notes_iterator_;
    };
    return new Chatter(&mu_, &received_notes_);
  }

 private:
  std::vector<Feature> feature_list_;  // Database of geographic features
  absl::Mutex mu_;  // Mutex for thread-safe access to received_notes_
  std::vector<RouteNote> received_notes_ ABSL_GUARDED_BY(mu_);  // Stored route notes
};

/**
 * Runs the gRPC server with the RouteGuide service.
 * @param db_path Path to the feature database file
 */
void RunServer(const std::string& db_path) {
  std::string server_address("0.0.0.0:50051");
  RouteGuideImpl service(db_path);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address;
  server->Wait();
}

int main(int argc, char** argv) {
  // Initialize logging and command line parsing
  absl::ParseCommandLine(argc, argv);
  absl::SetStderrThreshold(absl::LogSeverityAtLeast::kInfo);
  absl::InitializeLog();

  // Load the route guide database and start the server
  std::string db = routeguide::GetDbFileContent(argc, argv);
  RunServer(db);

  return 0;
}
```

The comments added explain:
1. File-level documentation for the license and purpose
2. Function-level documentation for all major functions
3. Class-level documentation for the RouteGuide implementation
4. Method-level documentation for all RPC handlers
5. Important implementation details like the Haversine formula
6. Thread-safety considerations with mutex usage
7. Parameter and return value documentation
8. Important variables and their purposes

The comments are designed to help future developers understand:
- The overall architecture
- The purpose of each component
- Important implementation details
- Threading considerations
- The flow of data through the system