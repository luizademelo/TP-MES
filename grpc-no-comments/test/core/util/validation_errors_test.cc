
// Copyright 2022 gRPC authors.

#include "src/core/util/validation_errors.h"

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

TEST(ValidationErrors, NoErrors) {
  ValidationErrors errors;
  EXPECT_TRUE(errors.ok());
  EXPECT_EQ(errors.size(), 0);
  {
    ValidationErrors::ScopedField field(&errors, "foo");
    {
      ValidationErrors::ScopedField field(&errors, ".bar");
    }
  }
  EXPECT_TRUE(errors.ok());
  EXPECT_EQ(errors.size(), 0);
  absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                      "errors validating config");
  EXPECT_TRUE(status.ok()) << status;
}

TEST(ValidationErrors, OneError) {
  ValidationErrors errors;
  {
    ValidationErrors::ScopedField field(&errors, "foo");
    {
      ValidationErrors::ScopedField field(&errors, ".bar");
      errors.AddError("value smells funny");
    }
  }
  EXPECT_FALSE(errors.ok());
  EXPECT_EQ(errors.size(), 1);
  absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                      "errors validating config");
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(
      status.message(),
      "errors validating config: [field:foo.bar error:value smells funny]")
      << status;
}

TEST(ValidationErrors, MultipleErrorsForSameField) {
  ValidationErrors errors;
  {
    ValidationErrors::ScopedField field(&errors, "foo");
    {
      ValidationErrors::ScopedField field(&errors, ".bar");
      errors.AddError("value smells funny");
      errors.AddError("value is ugly");
    }
  }
  EXPECT_FALSE(errors.ok());
  EXPECT_EQ(errors.size(), 1);
  absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                      "errors validating config");
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.message(),
            "errors validating config: [field:foo.bar errors:["
            "value smells funny; value is ugly]]")
      << status;
}

TEST(ValidationErrors, ErrorsForMultipleFields) {
  ValidationErrors errors;
  {
    ValidationErrors::ScopedField field(&errors, "foo");
    {
      ValidationErrors::ScopedField field(&errors, ".bar");
      errors.AddError("value smells funny");
    }
    errors.AddError("too hot");
  }
  EXPECT_FALSE(errors.ok());
  EXPECT_EQ(errors.size(), 2);
  absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                      "errors validating config");
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.message(),
            "errors validating config: ["
            "field:foo error:too hot; field:foo.bar error:value smells funny]")
      << status;
}

TEST(ValidationErrors, MessageMatchesStatusMessage) {
  ValidationErrors errors;
  {
    ValidationErrors::ScopedField field(&errors, "foo");
    {
      ValidationErrors::ScopedField field(&errors, ".bar");
      errors.AddError("value smells funny");
    }
    errors.AddError("too hot");
  }
  EXPECT_FALSE(errors.ok());
  EXPECT_EQ(errors.size(), 2);
  absl::Status status = errors.status(absl::StatusCode::kInvalidArgument,
                                      "errors validating config");
  std::string message = errors.message("errors validating config");
  EXPECT_EQ(status.message(), message)
      << status << " does not match " << message;
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
