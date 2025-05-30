
// Copyright 2022 gRPC authors.

#include "src/cpp/ext/gcp/observability_config.h"

#include <grpc/support/alloc.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/tmpfile.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace internal {
namespace {

TEST(GcpObservabilityConfigJsonParsingTest, Basic) {
  const char* json_str = R"json({
      "cloud_logging": {
        "client_rpc_events": [
          {
            "methods": ["google.pubsub.v1.Subscriber/Acknowledge", "google.pubsub.v1.Publisher/CreateTopic"],
            "exclude": true
          },
          {
            "methods": ["google.pubsub.v1.Subscriber

method", "service

method' not allowed"),
          ::testing::HasSubstr(
              "field:cloud_logging.client_rpc_events[1].methods[1] "
              "error:Wildcard specified for method in incorrect manner")));
}

TEST(GcpObservabilityConfigJsonParsingTest, SamplingRateDefaults) {
  const char* json_str = R"json({
      "cloud_trace": {
        "sampling_rate": 0.05
      }
    })json";
  auto json = grpc_core::JsonParse(json_str);
  ASSERT_TRUE(json.ok()) << json.status();
  grpc_core::ValidationErrors errors;
  auto config = grpc_core::LoadFromJson<GcpObservabilityConfig>(
      *json, grpc_core::JsonArgs(), &errors);
  ASSERT_TRUE(errors.ok()) << errors.status(absl::StatusCode::kInvalidArgument,
                                            "unexpected errors");
  ASSERT_TRUE(config.cloud_trace.has_value());
  EXPECT_FLOAT_EQ(config.cloud_trace->sampling_rate, 0.05);
}

TEST(GcpEnvParsingTest, NoEnvironmentVariableSet) {
  auto config = GcpObservabilityConfig::ReadFromEnv();
  EXPECT_EQ(config.status(),
            absl::FailedPreconditionError(
                "Environment variables GRPC_GCP_OBSERVABILITY_CONFIG_FILE or "
                "GRPC_GCP_OBSERVABILITY_CONFIG "
                "not defined"));
}

TEST(GcpEnvParsingTest, ConfigFileDoesNotExist) {
  const char* kPath = "/tmp/gcp_observability_config_does_not_exist";
  grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG_FILE", kPath);

  auto config = GcpObservabilityConfig::ReadFromEnv();

  EXPECT_EQ(config.status().code(), absl::StatusCode::kFailedPrecondition);
  EXPECT_THAT(
      std::string(config.status().message()),
      ::testing::StartsWith(absl::StrCat("error loading file ", kPath)));

  grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG_FILE");
}

TEST(GcpEnvParsingTest, ProjectIdNotSet) {
  grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG", "{}");

  auto config = GcpObservabilityConfig::ReadFromEnv();
  EXPECT_EQ(config.status(),
            absl::FailedPreconditionError("GCP Project ID not found."));

  grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
  grpc_core::CoreConfiguration::Reset();
}

TEST(GcpEnvParsingTest, ProjectIdFromGcpProjectEnvVar) {
  grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG", "{}");
  grpc_core::SetEnv("GCP_PROJECT", "gcp_project");

  auto config = GcpObservabilityConfig::ReadFromEnv();
  EXPECT_TRUE(config.ok());
  EXPECT_EQ(config->project_id, "gcp_project");

  grpc_core::UnsetEnv("GCP_PROJECT");
  grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
  grpc_core::CoreConfiguration::Reset();
}

TEST(GcpEnvParsingTest, ProjectIdFromGcloudProjectEnvVar) {
  grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG", "{}");
  grpc_core::SetEnv("GCLOUD_PROJECT", "gcloud_project");

  auto config = GcpObservabilityConfig::ReadFromEnv();
  EXPECT_TRUE(config.ok());
  EXPECT_EQ(config->project_id, "gcloud_project");

  grpc_core::UnsetEnv("GCLOUD_PROJECT");
  grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
  grpc_core::CoreConfiguration::Reset();
}

TEST(GcpEnvParsingTest, ProjectIdFromGoogleCloudProjectEnvVar) {
  grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG", "{}");
  grpc_core::SetEnv("GOOGLE_CLOUD_PROJECT", "google_cloud_project");

  auto config = GcpObservabilityConfig::ReadFromEnv();
  EXPECT_TRUE(config.ok());
  EXPECT_EQ(config->project_id, "google_cloud_project");

  grpc_core::UnsetEnv("GOOGLE_CLOUD_PROJECT");
  grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
  grpc_core::CoreConfiguration::Reset();
}

class EnvParsingTestType {
 public:
  enum class ConfigSource {
    kFile,
    kEnvVar,
  };

  EnvParsingTestType& set_config_source(ConfigSource config_source) {
    config_source_ = config_source;
    return *this;
  }

  ConfigSource config_source() const { return config_source_; }

  std::string ToString() const {
    std::string ret_val;
    if (config_source_ == ConfigSource::kFile) {
      absl::StrAppend(&ret_val, "ConfigFromFile");
    } else if (config_source_ == ConfigSource::kEnvVar) {
      absl::StrAppend(&ret_val, "ConfigFromEnvVar");
    }
    return ret_val;
  }

  static std::string Name(
      const ::testing::TestParamInfo<EnvParsingTestType>& info) {
    return info.param.ToString();
  }

 private:
  ConfigSource config_source_;
};

class EnvParsingTest : public ::testing::TestWithParam<EnvParsingTestType> {
 protected:
  ~EnvParsingTest() override {
    if (GetParam().config_source() == EnvParsingTestType::ConfigSource::kFile) {
      if (tmp_file_name != nullptr) {
        grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG_FILE");
        remove(tmp_file_name);
        gpr_free(tmp_file_name);
      }
    } else if (GetParam().config_source() ==
               EnvParsingTestType::ConfigSource::kEnvVar) {
      grpc_core::UnsetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
    }
  }

  void SetConfig(const char* json) {
    if (GetParam().config_source() == EnvParsingTestType::ConfigSource::kFile) {
      ASSERT_EQ(tmp_file_name, nullptr);
      FILE* tmp_config_file =
          gpr_tmpfile("gcp_observability_config", &tmp_file_name);
      fputs(json, tmp_config_file);
      fclose(tmp_config_file);
      grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG_FILE", tmp_file_name);
    } else if (GetParam().config_source() ==
               EnvParsingTestType::ConfigSource::kEnvVar) {
      grpc_core::SetEnv("GRPC_GCP_OBSERVABILITY_CONFIG", json);
    }
  }

 private:
  char* tmp_file_name = nullptr;
};

TEST_P(EnvParsingTest, Basic) {
  SetConfig(R"json({
      "project_id": "project"
    })json");
  auto config = GcpObservabilityConfig::ReadFromEnv();

  ASSERT_TRUE(config.ok());
  EXPECT_EQ(config->project_id, "project");
}

// Test that JSON parsing errors are propagated as expected.
TEST_P(EnvParsingTest, BadJson) {
  SetConfig("{");
  auto config = GcpObservabilityConfig::ReadFromEnv();

  EXPECT_EQ(config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(config.status().message(),
              ::testing::HasSubstr("JSON parsing failed"))
      << config.status().message();
}

TEST_P(EnvParsingTest, BadJsonEmptyString) {
  SetConfig("");
  auto config = GcpObservabilityConfig::ReadFromEnv();
  if (GetParam().config_source() == EnvParsingTestType::ConfigSource::kFile) {
    EXPECT_EQ(config.status().code(), absl::StatusCode::kInvalidArgument);
    EXPECT_THAT(config.status().message(),
                ::testing::HasSubstr("JSON parsing failed"))
        << config.status().message();
  } else {
    EXPECT_EQ(config.status(),
              absl::FailedPreconditionError(
                  "Environment variables GRPC_GCP_OBSERVABILITY_CONFIG_FILE or "
                  "GRPC_GCP_OBSERVABILITY_CONFIG not defined"));
  }
}

// Make sure that GCP config errors are propagated as expected.
TEST_P(EnvParsingTest, BadGcpConfig) {
  SetConfig(R"json({
      "project_id": 123
    })json");
  auto config = GcpObservabilityConfig::ReadFromEnv();

  EXPECT_EQ(config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(config.status().message(),
              ::testing::HasSubstr("field:project_id error:is not a string"))
      << config.status().message();
}

INSTANTIATE_TEST_SUITE_P(
    GcpObservabilityConfigTest, EnvParsingTest,
    ::testing::Values(EnvParsingTestType().set_config_source(
                          EnvParsingTestType::ConfigSource::kFile),
                      EnvParsingTestType().set_config_source(
                          EnvParsingTestType::ConfigSource::kEnvVar)),
    &EnvParsingTestType::Name);

}  // namespace
}  // namespace internal
}  // namespace grpc

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
