
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

class NullErrorCollector : public google::protobuf::DescriptorPool::ErrorCollector {
  void RecordError(absl::string_view filename, absl::string_view element_name,
                   const google::protobuf::Message* descriptor, ErrorLocation location,
                   absl::string_view message) override {}
  void RecordWarning(absl::string_view filename, absl::string_view element_name,
                     const google::protobuf::Message* descriptor, ErrorLocation location,
                     absl::string_view message) override {}
};

static void AddFile(google::protobuf::FileDescriptorProto& file, upb::DefPool* pool,
                    google::protobuf::DescriptorPool* desc_pool) {
  NullErrorCollector collector;
  const google::protobuf::FileDescriptor* file_desc =
      desc_pool->BuildFileCollectingErrors(file, &collector);

  if (file_desc != nullptr) {

    google::protobuf::FileDescriptorProto normalized_file;
    file_desc->CopyTo(&normalized_file);
    std::string serialized;
    normalized_file.SerializeToString(&serialized);
    upb::Arena arena;
    upb::Status status;
    google_protobuf_FileDescriptorProto* proto = google_protobuf_FileDescriptorProto_parse(
        serialized.data(), serialized.size(), arena.ptr());
    ASSERT_NE(proto, nullptr);
    upb::FileDefPtr file_def = pool->AddFile(proto, &status);

    if (!file_def) return;

    ASSERT_TRUE(status.ok()) << status.error_message();
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

inline void RoundTripDescriptor(const google::protobuf::FileDescriptorSet& set) {
  upb::DefPool defpool;
  google::protobuf::DescriptorPool desc_pool;
  desc_pool.EnforceWeakDependencies(true);
  for (const auto& file : set.file()) {
    google::protobuf::FileDescriptorProto mutable_file(file);
    AddFile(mutable_file, &defpool, &desc_pool);
  }
}

}

#endif
