
// Copyright 2021 gRPC authors.

#include "src/core/lib/transport/error_utils.h"

#include <stdint.h>

#include <vector>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/status_helper.h"
#include "test/core/test_util/test_config.h"

namespace {

TEST(ErrorUtilsTest, GetErrorGetStatusNone) {
  grpc_error_handle error;
  grpc_status_code code;
  std::string message;
  grpc_error_get_status(error, grpc_core::Timestamp(), &code, &message, nullptr,
                        nullptr);
  ASSERT_EQ(code, GRPC_STATUS_OK);
  ASSERT_EQ(message, "");
}

TEST(ErrorUtilsTest, GetErrorGetStatusFlat) {
  grpc_error_handle error = grpc_error_set_int(
      GRPC_ERROR_CREATE("Msg"), grpc_core::StatusIntProperty::kRpcStatus,
      GRPC_STATUS_CANCELLED);
  grpc_status_code code;
  std::string message;
  grpc_error_get_status(error, grpc_core::Timestamp(), &code, &message, nullptr,
                        nullptr);
  ASSERT_EQ(code, GRPC_STATUS_CANCELLED);
  ASSERT_EQ(message, "Msg");
}

TEST(ErrorUtilsTest, GetErrorGetStatusChild) {
  std::vector<grpc_error_handle> children = {
      GRPC_ERROR_CREATE("Child1"),
      grpc_error_set_int(GRPC_ERROR_CREATE("Child2"),
                         grpc_core::StatusIntProperty::kRpcStatus,
                         GRPC_STATUS_RESOURCE_EXHAUSTED),
  };
  grpc_error_handle error = GRPC_ERROR_CREATE_FROM_VECTOR("Parent", &children);
  grpc_status_code code;
  std::string message;
  grpc_error_get_status(error, grpc_core::Timestamp(), &code, &message, nullptr,
                        nullptr);
  ASSERT_EQ(code, GRPC_STATUS_RESOURCE_EXHAUSTED);
  ASSERT_EQ(message, grpc_core::IsErrorFlattenEnabled()
                         ? "Parent (Child1) (Child2)"
                         : "Child2");
}

TEST(ErrorUtilsTest, AbslOkToGrpcError) {
  grpc_error_handle error = absl_status_to_grpc_error(absl::OkStatus());
  ASSERT_EQ(absl::OkStatus(), error);
}

TEST(ErrorUtilsTest, GrpcSpecialErrorNoneToAbslStatus) {
  absl::Status status = grpc_error_to_absl_status(absl::OkStatus());
  ASSERT_TRUE(status.ok());
  ASSERT_EQ(status.message(), "");
}

TEST(ErrorUtilsTest, AbslStatusToGrpcErrorDoesNotReturnSpecialVariables) {
  grpc_error_handle error =
      absl_status_to_grpc_error(absl::CancelledError("CANCELLED"));
  ASSERT_NE(error, absl::CancelledError());
}

TEST(ErrorUtilsTest, GrpcSpecialErrorCancelledToAbslStatus) {
  if (grpc_core::IsErrorFlattenEnabled()) {
    GTEST_SKIP() << "This functionality not available with this experiment";
  }
  absl::Status status = grpc_error_to_absl_status(absl::CancelledError());
  ASSERT_TRUE(absl::IsCancelled(status));
  ASSERT_EQ(status.message(), "CANCELLED");
}

TEST(ErrorUtilsTest, GrpcSpecialErrorOOMToAbslStatus) {
  if (grpc_core::IsErrorFlattenEnabled()) {
    GTEST_SKIP() << "This functionality not available with this experiment";
  }
  absl::Status status =
      grpc_error_to_absl_status(absl::ResourceExhaustedError(""));
  ASSERT_TRUE(absl::IsResourceExhausted(status));
  ASSERT_EQ(status.message(), "RESOURCE_EXHAUSTED");
}

TEST(ErrorUtilsTest, AbslUnavailableToGrpcError) {
  grpc_error_handle error =
      absl_status_to_grpc_error(absl::UnavailableError("Making tea"));

  intptr_t code;
  ASSERT_TRUE(grpc_error_get_int(
      error, grpc_core::StatusIntProperty::kRpcStatus, &code));
  ASSERT_EQ(static_cast<grpc_status_code>(code), GRPC_STATUS_UNAVAILABLE);

  ASSERT_EQ(error.message(), "Making tea");
}

TEST(ErrorUtilsTest, GrpcErrorUnavailableToAbslStatus) {
  grpc_error_handle error = grpc_error_set_int(
      GRPC_ERROR_CREATE(
          "weighted_target: all children report state TRANSIENT_FAILURE"),
      grpc_core::StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE);
  absl::Status status = grpc_error_to_absl_status(error);
  ASSERT_TRUE(absl::IsUnavailable(status));
  ASSERT_EQ(status.message(),
            "weighted_target: all children report state TRANSIENT_FAILURE");
}

}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
};
