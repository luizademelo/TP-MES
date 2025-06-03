Here's the commented version of the code:

```c++
/*
 *
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
 *
 */

// Include necessary gRPC and standard library headers
#include <grpc/grpc.h>
#include <grpcpp/alarm.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>

// Include ABSL and protobuf related headers
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "helper.h"
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif

// Using declarations for gRPC and route guide protobuf types
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using routeguide::Feature;
using routeguide::Point;
using routeguide::Rectangle;
using routeguide::RouteGuide;
using routeguide::RouteNote;
using routeguide::RouteSummary;

// Helper function to create a Point with given latitude and longitude
Point MakePoint(long latitude, long longitude) {
  Point p;
  p.set_latitude(latitude);
  p.set_longitude(longitude);
  return p;
}

// Helper function to create a Feature with given name and coordinates
Feature MakeFeature(const std::string& name, long latitude, long longitude) {
  Feature f;
  f.set_name(name);
  f.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
  return f;
}

// Helper function to create a RouteNote with given message and coordinates
RouteNote MakeRouteNote(const std::string& message, long latitude,
                        long longitude) {
  RouteNote n;
  n.set_message(message);
  n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
  return n;
}

// Client class for RouteGuide service
class RouteGuideClient {
 public:
  // Constructor initializes the stub and parses the feature database
  RouteGuideClient(std::shared_ptr<Channel> channel, const std::string& db)
      : stub_(RouteGuide::NewStub(channel)) {
    routeguide::ParseDb(db, &feature_list_);
  }

  // Gets a single feature at hardcoded coordinates
  void GetFeature() {
    Point point;
    Feature feature;
    point = MakePoint(409146138, -746188906);
    GetOneFeature(point, &feature);
    point = MakePoint(0, 0);
    GetOneFeature(point, &feature);
  }

  // Lists features within a specified rectangular area
  void ListFeatures() {
    routeguide::Rectangle rect;
    Feature feature;

    // Set rectangle boundaries
    rect.mutable_lo()->set_latitude(400000000);
    rect.mutable_lo()->set_longitude(-750000000);
    rect.mutable_hi()->set_latitude(420000000);
    rect.mutable_hi()->set_longitude(-730000000);
    std::cout << "Looking for features between 40, -75 and 42, -73"
              << std::endl;

    // Nested class for handling streaming read of features
    class Reader : public grpc::ClientReadReactor<Feature> {
     public:
      Reader(RouteGuide::Stub* stub, float coord_factor,
             const routeguide::Rectangle& rect)
          : coord_factor_(coord_factor) {
        stub->async()->ListFeatures(&context_, &rect, this);
        StartRead(&feature_);
        StartCall();
      }
      // Called when a read operation completes
      void OnReadDone(bool ok) override {
        if (ok) {
          std::cout << "Found feature called " << feature_.name() << " at "
                    << feature_.location().latitude() / coord_factor_ << ", "
                    << feature_.location().longitude() / coord_factor_
                    << std::endl;
          StartRead(&feature_);
        }
      }
      // Called when the RPC is done
      void OnDone(const Status& s) override {
        std::unique_lock<std::mutex> l(mu_);
        status_ = s;
        done_ = true;
        cv_.notify_one();
      }
      // Waits for the RPC to complete and returns the status
      Status Await() {
        std::unique_lock<std::mutex> l(mu_);
        cv_.wait(l, [this] { return done_; });
        return std::move(status_);
      }

     private:
      ClientContext context_;
      float coord_factor_;  // Factor to convert coordinates to degrees
      Feature feature_;     // Current feature being read
      std::mutex mu_;       // Mutex for thread synchronization
      std::condition_variable cv_;  // Condition variable for waiting
      Status status_;        // Final status of the RPC
      bool done_ = false;    // Flag indicating RPC completion
    };
    
    Reader reader(stub_.get(), kCoordFactor_, rect);
    Status status = reader.Await();
    if (status.ok()) {
      std::cout << "ListFeatures rpc succeeded." << std::endl;
    } else {
      std::cout << "ListFeatures rpc failed." << std::endl;
    }
  }

  // Records a route by visiting random features with random delays
  void RecordRoute() {
    // Nested class for handling streaming write of points
    class Recorder : public grpc::ClientWriteReactor<Point> {
     public:
      Recorder(RouteGuide::Stub* stub, float coord_factor,
               const std::vector<Feature>* feature_list)
          : coord_factor_(coord_factor),
            feature_list_(feature_list),
            generator_(
                std::chrono::system_clock::now().time_since_epoch().count()),
            feature_distribution_(0, feature_list->size() - 1),
            delay_distribution_(500, 1500) {
        stub->async()->RecordRoute(&context_, &stats_, this);
        AddHold();
        NextWrite();
        StartCall();
      }
      // Called when a write operation completes
      void OnWriteDone(bool ok) override {
        // Schedule next write after random delay
        alarm_.Set(
            std::chrono::system_clock::now() +
                std::chrono::milliseconds(delay_distribution_(generator_)),
            [this](bool ) { NextWrite(); });
      }
      // Called when the RPC is done
      void OnDone(const Status& s) override {
        std::unique_lock<std::mutex> l(mu_);
        status_ = s;
        done_ = true;
        cv_.notify_one();
      }
      // Waits for RPC completion and returns route statistics
      Status Await(RouteSummary* stats) {
        std::unique_lock<std::mutex> l(mu_);
        cv_.wait(l, [this] { return done_; });
        *stats = stats_;
        return std::move(status_);
      }

     private:
      // Performs the next write operation
      void NextWrite() {
        if (points_remaining_ != 0) {
          // Select random feature and write its location
          const Feature& f =
              (*feature_list_)[feature_distribution_(generator_)];
          std::cout << "Visiting point "
                    << f.location().latitude() / coord_factor_ << ", "
                    << f.location().longitude() / coord_factor_ << std::endl;
          StartWrite(&f.location());
          points_remaining_--;
        } else {
          StartWritesDone();
          RemoveHold();
        }
      }
      ClientContext context_;
      float coord_factor_;  // Coordinate conversion factor
      int points_remaining_ = 10;  // Number of points remaining to visit
      Point point_;
      RouteSummary stats_;  // Accumulated route statistics
      const std::vector<Feature>* feature_list_;  // List of available features
      std::default_random_engine generator_;  // Random number generator
      std::uniform_int_distribution<int> feature_distribution_;  // Feature selection distribution
      std::uniform_int_distribution<int> delay_distribution_;  // Delay distribution
      grpc::Alarm alarm_;  // For scheduling delayed writes
      std::mutex mu_;      // For thread synchronization
      std::condition_variable cv_;  // For waiting on RPC completion
      Status status_;      // Final RPC status
      bool done_ = false;  // RPC completion flag
    };
    
    Recorder recorder(stub_.get(), kCoordFactor_, &feature_list_);
    RouteSummary stats;
    Status status = recorder.Await(&stats);
    if (status.ok()) {
      std::cout << "Finished trip with " << stats.point_count() << " points\n"
                << "Passed " << stats.feature_count() << " features\n"
                << "Travelled " << stats.distance() << " meters\n"
                << "It took " << stats.elapsed_time() << " seconds"
                << std::endl;
    } else {
      std::cout << "RecordRoute rpc failed." << std::endl;
    }
  }

  // Conducts a bidirectional chat sending and receiving route notes
  void RouteChat() {
    // Nested class for handling bidirectional streaming
    class Chatter : public grpc::ClientBidiReactor<RouteNote, RouteNote> {
     public:
      explicit Chatter(RouteGuide::Stub* stub)
          : notes_{MakeRouteNote("First message", 0, 0),
                   MakeRouteNote("Second message", 0, 1),
                   MakeRouteNote("Third message", 1, 0),
                   MakeRouteNote("Fourth message", 0, 0)},
            notes_iterator_(notes_.begin()) {
        stub->async()->RouteChat(&context_, this);
        NextWrite();
        StartRead(&server_note_);
        StartCall();
      }
      // Called when a write operation completes
      void OnWriteDone(bool ok) override {
        if (ok) {
          NextWrite();
        }
      }
      // Called when a read operation completes
      void OnReadDone(bool ok) override {
        if (ok) {
          std::cout << "Got message " << server_note_.message() << " at "
                    << server_note_.location().latitude() << ", "
                    << server_note_.location().longitude() << std::endl;
          StartRead(&server_note_);
        }
      }
      // Called when the RPC is done
      void OnDone(const Status& s) override {
        std::unique_lock<std::mutex> l(mu_);
        status_ = s;
        done_ = true;
        cv_.notify_one();
      }
      // Waits for RPC completion and returns status
      Status Await() {
        std::unique_lock<std::mutex> l(mu_);
        cv_.wait(l, [this] { return done_; });
        return std::move(status_);
      }

     private:
      // Performs the next write operation
      void NextWrite() {
        if (notes_iterator_ != notes_.end()) {
          const auto& note = *notes_iterator_;
          std::cout << "Sending message " << note.message() << " at "
                    << note.location().latitude() << ", "
                    << note.location().longitude() << std::endl;
          StartWrite(&note);
          notes_iterator_++;
        } else {
          StartWritesDone();
        }
      }
      ClientContext context_;
      const std::vector<RouteNote> notes_;  // Predefined notes to send
      std::vector<RouteNote>::const_iterator notes_iterator_;  // Current note position
      RouteNote server_note_;  // Note received from server
      std::mutex mu_;         // For thread synchronization
      std::condition_variable cv_;  // For waiting on RPC completion
      Status status_;         // Final RPC status
      bool done_ = false;     // RPC completion flag
    };

    Chatter chatter(stub_.get());
    Status status = chatter.Await();
    if (!status.ok()) {
      std::cout << "RouteChat rpc failed." << std::endl;
    }
  }

 private:
  // Gets a single feature at the specified point
  bool GetOneFeature(const Point& point, Feature* feature) {
    ClientContext context;
    bool result;
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    stub_->async()->GetFeature(
        &context, &point, feature,
        [&result, &mu, &cv, &done, feature, this](Status status) {
          bool ret;
          if (!status.ok()) {
            std::cout << "GetFeature rpc failed." << std::endl;
            ret = false;
          } else if (!feature->has_location()) {
            std::cout << "Server returns incomplete feature." << std::endl;
            ret = false;
          } else if (feature->name().empty()) {
            std::cout << "Found no feature at "
                      << feature->location().latitude() / kCoordFactor_ << ", "
                      << feature->location().longitude() / kCoordFactor_
                      << std::endl;
            ret = true;
          } else {
            std::cout << "Found feature called " << feature->name() << " at "
                      << feature->location().latitude() / kCoordFactor_ << ", "
                      << feature->location().longitude() / kCoordFactor_
                      << std::endl;
            ret = true;
          }
          std::lock_guard<std::mutex> lock(mu);
          result = ret;
          done = true;
          cv.notify_one();
        });
    std::unique_lock<std::mutex> lock(mu);
    cv.wait(lock, [&done] { return done; });
    return result;
  }

  const float kCoordFactor_ = 10000000.0;  // Conversion factor for coordinates
  std::unique_ptr<RouteGuide::Stub> stub_;  // gRPC service stub
  std::vector<Feature> feature_list_;       // List of available features
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get database content and create client
  std::string db = routeguide::GetDbFileContent(argc, argv);
  RouteGuideClient guide(
      grpc::CreateChannel("localhost:50051",
                          grpc::InsecureChannelCredentials()),
      db);

  // Execute all client methods
  std::cout << "-------------- GetFeature --------------" << std::endl;
  guide.GetFeature();
  std::cout << "-------------- ListFeatures --------------" << std::endl;
  guide.ListFeatures();
  std::cout << "-------------- RecordRoute --------------" << std::endl;
  guide.RecordRoute();
  std::cout << "-------------- RouteChat --------------" << std::endl;
  guide.RouteChat();

  return 0;
}
```

The comments provide:
1. File-level documentation about the license
2. Explanation of include statements
3. Documentation for each helper function
4. Detailed class and method documentation for the RouteGuideClient
5. Explanation of all nested reactor classes
6. Documentation for member variables
7. Main function documentation
8. Explanations of key implementation details and threading logic

The comments are designed to help future developers understand:
- The overall structure of the code
- The purpose of each component
- How the gRPC streaming operations work
- The threading and synchronization mechanisms
- The data flow through the system