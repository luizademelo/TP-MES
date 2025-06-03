Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_UTIL_DEF_TO_PROTO_TEST_H_
#define UPB_UTIL_DEF_TO_PROTO_TEST_H_

#include <string>

#include "google/protobuf/descriptor.pb.h"
#include "google/protobuf/descriptor.upb.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "google/protobuf/descriptor.h"
#include "google/protobuf/dynamic_message.h"
#include "google/protobuf/util/field_comparator.h"
#include "upb/base/status.hpp"
#include "upb/mem/arena.hpp"
#include "upb/reflection/def.hpp"
#include "upb/util/def_to_proto.h"

namespace upb_test {

// Custom gtest matcher for comparing protocol buffer messages while treating NaN values as equal
// Args:
//   proto: The expected protocol buffer message
// Returns:
//   A matcher that compares protocol buffer messages with NaN equality
MATCHER_P(EqualsProtoTreatNansAsEqual, proto,
          negation ? "are not equal" : "are equal") {
  upb::DefPool defpool;
  google::protobuf::DescriptorPool pool;
  google::protobuf::DynamicMessageFactory factory;
  std::string differences;
  google::protobuf::util::DefaultFieldComparator comparator;
  comparator.set_treat_nan_as_equal(true);
  google::protobuf::util::MessageDifferencer differencer;
  differencer.set_field_comparator(&comparator);
  differencer.ReportDifferencesToString(&differences);
  bool eq = differencer.Compare(proto, arg);
  if (!eq) {
    *result_listener << differences;
  }
  return eq;
}

// A no-op implementation of ErrorCollector that ignores all errors and warnings
// Used when building descriptor pools where we don't want to handle errors
class NullErrorCollector : public google::protobuf::DescriptorPool::ErrorCollector {
  void RecordError(absl::string_view filename, absl::string_view element_name,
                   const google::protobuf::Message* descriptor, ErrorLocation location,
                   absl::string_view message) override {}
  void RecordWarning(absl::string_view filename, absl::string_view element_name,
                     const google::protobuf::Message* descriptor, ErrorLocation location,
                     absl::string_view message) override {}
};

// Adds a file descriptor to both upb and protobuf descriptor pools and verifies they match
// Args:
//   file: The file descriptor proto to add
//   pool: The upb definition pool to add to
//   desc_pool: The protobuf descriptor pool to add to
static void AddFile(google::protobuf::FileDescriptorProto& file, upb::DefPool* pool,
                    google::protobuf::DescriptorPool* desc_pool) {
  NullErrorCollector collector;
  // Build the file descriptor in the protobuf pool
  const google::protobuf::FileDescriptor* file_desc =
      desc_pool->BuildFileCollectingErrors(file, &collector);

  if (file_desc != nullptr) {
    // If building succeeded, normalize the descriptor and convert to upb format
    google::protobuf::FileDescriptorProto normalized_file;
    file_desc->CopyTo(&normalized_file);
    std::string serialized;
    normalized_file.SerializeToString(&serialized);
    upb::Arena arena;
    upb::Status status;
    google_protobuf_FileDescriptorProto* proto = google_protobuf_FileDescriptorProto_parse(
        serialized.data(), serialized.size(), arena.ptr());
    ASSERT_NE(proto, nullptr);
    
    // Add the file to the upb pool
    upb::FileDefPtr file_def = pool->AddFile(proto, &status);

    if (!file_def) return;

    ASSERT_TRUE(status.ok()) << status.error_message();
    
    // Convert back to protobuf format and verify it matches the original
    google_protobuf_FileDescriptorProto* upb_proto =
        upb_FileDef_ToProto(file_def.ptr(), arena.ptr());
    size_t size;
    const char* buf =
        google_protobuf_FileDescriptorProto_serialize(upb_proto, arena.ptr(), &size);
    google::protobuf::FileDescriptorProto google_proto;
    bool ok = google_proto.ParseFromArray(buf, size);
    ASSERT_TRUE(ok);
    EXPECT_THAT(google_proto, EqualsProtoTreatNansAsEqual(normalized_file));
  } else {
    // If building failed, just try to add the raw file to the upb pool
    std::string serialized;
    file.SerializeToString(&serialized);
    upb::Arena arena;
    upb::Status status;
    google_protobuf_FileDescriptorProto* proto = google_protobuf_FileDescriptorProto_parse(
        serialized.data(), serialized.size(), arena.ptr());
    ASSERT_NE(proto, nullptr);
    pool->AddFile(proto, &status);
  }
}

// Performs a round-trip conversion of a FileDescriptorSet between upb and protobuf formats
// Args:
//   set: The FileDescriptorSet containing file descriptors to convert
inline void RoundTripDescriptor(const google::protobuf::FileDescriptorSet& set) {
  upb::DefPool defpool;
  google::protobuf::DescriptorPool desc_pool;
  desc_pool.EnforceWeakDependencies(true);
  // Process each file in the descriptor set
  for (const auto& file : set.file()) {
    google::protobuf::FileDescriptorProto mutable_file(file);
    AddFile(mutable_file, &defpool, &desc_pool);
  }
}

}

#endif
```