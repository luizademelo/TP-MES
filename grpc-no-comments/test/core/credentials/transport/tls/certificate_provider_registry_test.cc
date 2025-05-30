
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/certificate_provider_registry.h"

#include <grpc/support/port_platform.h>

#include "gmock/gmock.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class FakeCertificateProviderFactory1 : public CertificateProviderFactory {
 public:
  absl::string_view name() const override { return "fake1"; }

  RefCountedPtr<Config> CreateCertificateProviderConfig(
      const Json& , const JsonArgs& ,
      ValidationErrors* ) override {
    return nullptr;
  }

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<Config> ) override {
    return nullptr;
  }
};

class FakeCertificateProviderFactory2 : public CertificateProviderFactory {
 public:
  absl::string_view name() const override { return "fake2"; }

  RefCountedPtr<Config> CreateCertificateProviderConfig(
      const Json& , const JsonArgs& ,
      ValidationErrors* ) override {
    return nullptr;
  }

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<Config> ) override {
    return nullptr;
  }
};

TEST(CertificateProviderRegistryTest, Basic) {
  CertificateProviderRegistry::Builder b;
  auto* fake_factory_1 = new FakeCertificateProviderFactory1;
  auto* fake_factory_2 = new FakeCertificateProviderFactory2;
  b.RegisterCertificateProviderFactory(
      std::unique_ptr<CertificateProviderFactory>(fake_factory_1));
  b.RegisterCertificateProviderFactory(
      std::unique_ptr<CertificateProviderFactory>(fake_factory_2));
  auto r = b.Build();
  EXPECT_EQ(r.LookupCertificateProviderFactory("fake1"), fake_factory_1);
  EXPECT_EQ(r.LookupCertificateProviderFactory("fake2"), fake_factory_2);
  EXPECT_EQ(r.LookupCertificateProviderFactory("fake3"), nullptr);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
