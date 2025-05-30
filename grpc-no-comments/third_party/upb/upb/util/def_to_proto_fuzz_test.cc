
// Copyright 2023 Google LLC.  All rights reserved.

#include <string>

#include "google/protobuf/descriptor.pb.h"
#include <gtest/gtest.h>
#include "testing/fuzzing/fuzztest.h"
#include "upb/util/def_to_proto_test.h"

namespace upb_test {

FUZZ_TEST(FuzzTest, RoundTripDescriptor)
    .WithDomains(
        ::fuzztest::Arbitrary<google::protobuf::FileDescriptorSet>().WithProtobufField(
            "file",
            ::fuzztest::Arbitrary<google::protobuf::FileDescriptorProto>()

                .WithFieldUnset("source_code_info")
                .WithProtobufField(
                    "service",
                    ::fuzztest::Arbitrary<google::protobuf::ServiceDescriptorProto>()

                        .WithFieldUnset("stream"))));

}
