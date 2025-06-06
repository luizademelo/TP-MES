
// Copyright 2022 gRPC authors.

#include "src/core/credentials/transport/channel_creds_registry.h"

#include <grpc/grpc.h>
#include <gtest/gtest.h>

#include <optional>

#include "gmock/gmock.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/composite/composite_channel_credentials.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/credentials/transport/insecure/insecure_credentials.h"
#include "src/core/credentials/transport/tls/tls_credentials.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class TestChannelCredsFactory : public ChannelCredsFactory<> {
 public:
  absl::string_view type() const override { return Type(); }
  RefCountedPtr<ChannelCredsConfig> ParseConfig(
      const Json& , const JsonArgs& ,
      ValidationErrors* ) const override {
    return MakeRefCounted<Config>();
  }
  RefCountedPtr<grpc_channel_credentials> CreateChannelCreds(
      RefCountedPtr<ChannelCredsConfig> ) const override {
    return RefCountedPtr<grpc_channel_credentials>(
        grpc_fake_transport_security_credentials_create());
  }

 private:
  class Config : public ChannelCredsConfig {
   public:
    absl::string_view type() const override { return Type(); }
    bool Equals(const ChannelCredsConfig&) const override { return true; }
    std::string ToString() const override { return "{}"; }
  };

  static absl::string_view Type() { return "test"; }
};

class ChannelCredsRegistryTest : public ::testing::Test {
 protected:
  void SetUp() override { CoreConfiguration::Reset(); }

  void TestCreds(absl::string_view type,
                 std::optional<UniqueTypeName> credential_type,
                 Json json = Json::FromObject({})) {
    EXPECT_TRUE(
        CoreConfiguration::Get().channel_creds_registry().IsSupported(type));
    ValidationErrors errors;
    auto config = CoreConfiguration::Get().channel_creds_registry().ParseConfig(
        type, json, JsonArgs(), &errors);
    EXPECT_TRUE(errors.ok()) << errors.message("unexpected errors");
    ASSERT_NE(config, nullptr);
    EXPECT_EQ(config->type(), type);
    if (credential_type.has_value()) {
      auto creds =
          CoreConfiguration::Get().channel_creds_registry().CreateChannelCreds(
              std::move(config));
      ASSERT_NE(creds, nullptr);
      UniqueTypeName actual_type = creds->type();

      if (creds->type() == grpc_composite_channel_credentials::Type()) {
        actual_type =
            static_cast<grpc_composite_channel_credentials*>(creds.get())
                ->inner_creds()
                ->type();
      }
      EXPECT_EQ(actual_type, *credential_type)
          << "Actual: " << actual_type.name()
          << "\nExpected: " << credential_type->name();
    }
  }
};

TEST_F(ChannelCredsRegistryTest, GoogleDefaultCreds) {

  TestCreds("google_default", std::nullopt);
}

TEST_F(ChannelCredsRegistryTest, InsecureCreds) {
  TestCreds("insecure", InsecureCredentials::Type());
}

TEST_F(ChannelCredsRegistryTest, FakeCreds) {
  TestCreds("fake", grpc_fake_channel_credentials::Type());
}

TEST_F(ChannelCredsRegistryTest, TlsCredsNoConfig) {
  TestCreds("tls", TlsCredentials::Type());
}

TEST_F(ChannelCredsRegistryTest, TlsCredsFullConfig) {
  Json json = Json::FromObject({
      {"certificate_file", Json::FromString("/path/to/cert_file")},
      {"private_key_file", Json::FromString("/path/to/private_key_file")},
      {"ca_certificate_file", Json::FromString("/path/to/ca_cert_file")},
      {"refresh_interval", Json::FromString("1s")},
  });
  TestCreds("tls", TlsCredentials::Type(), json);
}

TEST_F(ChannelCredsRegistryTest, TlsCredsConfigInvalid) {
  Json json = Json::FromObject({
      {"certificate_file", Json::FromObject({})},
      {"private_key_file", Json::FromArray({})},
      {"ca_certificate_file", Json::FromBool(true)},
      {"refresh_interval", Json::FromNumber(1)},
  });
  ValidationErrors errors;
  auto config = CoreConfiguration::Get().channel_creds_registry().ParseConfig(
      "tls", json, JsonArgs(), &errors);
  EXPECT_EQ(errors.message("errors"),
            "errors: ["
            "field:ca_certificate_file error:is not a string; "
            "field:certificate_file error:is not a string; "
            "field:private_key_file error:is not a string; "
            "field:refresh_interval error:is not a string]");
}

TEST_F(ChannelCredsRegistryTest, Register) {

  EXPECT_FALSE(
      CoreConfiguration::Get().channel_creds_registry().IsSupported("test"));
  ValidationErrors errors;
  auto config = CoreConfiguration::Get().channel_creds_registry().ParseConfig(
      "test", Json::FromObject({}), JsonArgs(), &errors);
  EXPECT_TRUE(errors.ok()) << errors.message("unexpected errors");
  EXPECT_EQ(config, nullptr);
  auto creds =
      CoreConfiguration::Get().channel_creds_registry().CreateChannelCreds(
          std::move(config));
  EXPECT_EQ(creds, nullptr);

  CoreConfiguration::WithSubstituteBuilder builder(
      [](CoreConfiguration::Builder* builder) {
        BuildCoreConfiguration(builder);
        builder->channel_creds_registry()->RegisterChannelCredsFactory(
            std::make_unique<TestChannelCredsFactory>());
      });

  EXPECT_TRUE(
      CoreConfiguration::Get().channel_creds_registry().IsSupported("test"));
  config = CoreConfiguration::Get().channel_creds_registry().ParseConfig(
      "test", Json::FromObject({}), JsonArgs(), &errors);
  EXPECT_TRUE(errors.ok()) << errors.message("unexpected errors");
  EXPECT_NE(config, nullptr);
  EXPECT_EQ(config->type(), "test");
  creds = CoreConfiguration::Get().channel_creds_registry().CreateChannelCreds(
      std::move(config));
  ASSERT_NE(creds, nullptr);
  EXPECT_EQ(creds->type(), grpc_fake_channel_credentials::Type());
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
