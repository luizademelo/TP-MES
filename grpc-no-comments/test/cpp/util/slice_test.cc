
// Copyright 2015 gRPC authors.

#include <grpc++/support/slice.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpcpp/impl/grpc_library.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc {

namespace {

const char* kContent = "hello xxxxxxxxxxxxxxxxxxxx world";

class SliceTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() { grpc_init(); }

  static void TearDownTestSuite() { grpc_shutdown(); }

  void CheckSliceSize(const Slice& s, const std::string& content) {
    EXPECT_EQ(content.size(), s.size());
  }
  void CheckSlice(const Slice& s, const std::string& content) {
    EXPECT_EQ(content.size(), s.size());
    EXPECT_EQ(content,
              std::string(reinterpret_cast<const char*>(s.begin()), s.size()));
  }
};

TEST_F(SliceTest, Empty) {
  Slice empty_slice;
  CheckSlice(empty_slice, "");
}

TEST_F(SliceTest, Sized) {
  Slice sized_slice(strlen(kContent));
  CheckSliceSize(sized_slice, kContent);
}

TEST_F(SliceTest, String) {
  Slice spp(kContent);
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, Buf) {
  Slice spp(kContent, strlen(kContent));
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, StaticBuf) {
  Slice spp(kContent, strlen(kContent), Slice::STATIC_SLICE);
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, SliceNew) {
  char* x = new char[strlen(kContent) + 1];
  strcpy(x, kContent);
  Slice spp(x, strlen(x), [](void* p) { delete[] static_cast<char*>(p); });
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, SliceNewDoNothing) {
  Slice spp(const_cast<char*>(kContent), strlen(kContent), [](void* ) {});
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, SliceNewWithUserData) {
  struct stest {
    char* x;
    int y;
  };
  auto* t = new stest;
  t->x = new char[strlen(kContent) + 1];
  strcpy(t->x, kContent);
  Slice spp(
      t->x, strlen(t->x),
      [](void* p) {
        auto* t = static_cast<stest*>(p);
        delete[] t->x;
        delete t;
      },
      t);
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, SliceNewLen) {
  Slice spp(const_cast<char*>(kContent), strlen(kContent),
            [](void* , size_t l) { EXPECT_EQ(l, strlen(kContent)); });
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, Steal) {
  grpc_slice s = grpc_slice_from_copied_string(kContent);
  Slice spp(s, Slice::STEAL_REF);
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, Add) {
  grpc_slice s = grpc_slice_from_copied_string(kContent);
  Slice spp(s, Slice::ADD_REF);
  grpc_slice_unref(s);
  CheckSlice(spp, kContent);
}

TEST_F(SliceTest, Sub) {
  Slice spp("0123456789");
  Slice sub = spp.sub(1, 9);
  CheckSlice(sub, "12345678");
}

TEST_F(SliceTest, Cslice) {
  grpc_slice s = grpc_slice_from_copied_string(kContent);
  Slice spp(s, Slice::STEAL_REF);
  CheckSlice(spp, kContent);
  grpc_slice c_slice = spp.c_slice();
  EXPECT_EQ(GRPC_SLICE_START_PTR(s), GRPC_SLICE_START_PTR(c_slice));
  EXPECT_EQ(GRPC_SLICE_END_PTR(s), GRPC_SLICE_END_PTR(c_slice));
  grpc_slice_unref(c_slice);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
