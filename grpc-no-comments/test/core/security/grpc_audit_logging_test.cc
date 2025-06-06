
// Copyright 2023 gRPC authors.

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/security/authorization/audit_logging.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

namespace grpc_core {
namespace testing {

constexpr absl::string_view kName = "test_logger";

using experimental::AuditContext;
using experimental::AuditLogger;
using experimental::AuditLoggerFactory;
using experimental::AuditLoggerRegistry;
using experimental::RegisterAuditLoggerFactory;

namespace {

class TestAuditLogger : public AuditLogger {
 public:
  absl::string_view name() const override { return "test_logger"; }
  void Log(const AuditContext&) override {}
};

class TestAuditLoggerFactory : public AuditLoggerFactory {
 public:
  class TestConfig : public Config {
   public:
    absl::string_view name() const override { return kName; }
    std::string ToString() const override { return "test_config"; }
  };

  absl::string_view name() const override { return kName; }
  std::unique_ptr<AuditLogger> CreateAuditLogger(
      std::unique_ptr<AuditLoggerFactory::Config>) override {
    return std::make_unique<TestAuditLogger>();
  }
  absl::StatusOr<std::unique_ptr<Config>> ParseAuditLoggerConfig(
      const Json&) override {
    return std::make_unique<TestConfig>();
  }
};

class AuditLoggerRegistryTest : public ::testing::Test {
 protected:
  void SetUp() override {
    RegisterAuditLoggerFactory(std::make_unique<TestAuditLoggerFactory>());
  }
  void TearDown() override { AuditLoggerRegistry::TestOnlyResetRegistry(); }
};

}

TEST_F(AuditLoggerRegistryTest, SuccessfulLoggerCreation) {
  auto result = AuditLoggerRegistry::ParseConfig(kName, Json());
  ASSERT_TRUE(result.ok());
  ASSERT_NE(AuditLoggerRegistry::CreateAuditLogger(std::move(result.value())),
            nullptr);
}

TEST_F(AuditLoggerRegistryTest, UnknownLogger) {
  auto result = AuditLoggerRegistry::ParseConfig("unknown_logger", Json());
  EXPECT_EQ(result.status().code(), absl::StatusCode::kNotFound);
  EXPECT_EQ(result.status().message(),
            "audit logger factory for unknown_logger does not exist")
      << result.status();
}

TEST_F(AuditLoggerRegistryTest, LoggerFactoryExistenceChecks) {
  EXPECT_TRUE(AuditLoggerRegistry::FactoryExists(kName));
  EXPECT_FALSE(AuditLoggerRegistry::FactoryExists("unknown_logger"));
}

TEST(StdoutLoggerTest, LoggerFactoryExistenceChecks) {
  EXPECT_TRUE(AuditLoggerRegistry::FactoryExists("stdout_logger"));
}

TEST(StdoutLoggerTest, StdoutLoggerCreationAndLogInvocation) {
  auto result =
      AuditLoggerRegistry::ParseConfig("stdout_logger", Json::FromObject({}));
  ASSERT_TRUE(result.ok());
  auto logger =
      AuditLoggerRegistry::CreateAuditLogger(std::move(result.value()));
  AuditContext context("method", "spiffe", "policy", "rule", true);
  ::testing::internal::CaptureStdout();
  absl::Time time_before_log = absl::Now();
  logger->Log(context);
  absl::Time time_after_log = absl::Now();
  auto log_or = JsonParse(::testing::internal::GetCapturedStdout());
  ASSERT_TRUE(log_or.ok());
  ASSERT_EQ(log_or->type(), Json::Type::kObject);
  auto it = log_or->object().find("grpc_audit_log");
  ASSERT_NE(it, log_or->object().end());
  ASSERT_EQ(it->second.type(), Json::Type::kObject);
  auto& object = it->second.object();
  ASSERT_NE(object.find("timestamp"), object.end());
  EXPECT_EQ(object.find("timestamp")->second.type(), Json::Type::kString);
  absl::Time time_at_log;
  ASSERT_TRUE(absl::ParseTime(absl::RFC3339_full,
                              object.find("timestamp")->second.string(),
                              &time_at_log, nullptr));

  EXPECT_GE(time_at_log, time_before_log);
  EXPECT_LE(time_at_log, time_after_log);

  Json::Object json_object = object;
  json_object.erase("timestamp");
  EXPECT_EQ(JsonDump(Json::FromObject(json_object)),
            "{\"authorized\":true,\"matched_rule\":\"rule\",\"policy_name\":"
            "\"policy\",\"principal\":\"spiffe\",\"rpc_method\":\"method\"}");
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
