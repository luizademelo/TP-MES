
// Copyright 2020 gRPC authors.

#include "src/core/xds/grpc/certificate_provider_store.h"

#include <grpc/grpc.h>

#include <algorithm>
#include <memory>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/util/unique_type_name.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class CertificateProviderStoreTest : public ::testing::Test {
 public:
  CertificateProviderStoreTest() { grpc_init(); }

  ~CertificateProviderStoreTest() override { grpc_shutdown_blocking(); }
};

class FakeCertificateProvider : public grpc_tls_certificate_provider {
 public:
  RefCountedPtr<grpc_tls_certificate_distributor> distributor() const override {

    CHECK(0);
    return nullptr;
  }

  UniqueTypeName type() const override {
    static UniqueTypeName::Factory kFactory("fake");
    return kFactory.Create();
  }

 private:
  int CompareImpl(const grpc_tls_certificate_provider* other) const override {

    return QsortCompare(static_cast<const grpc_tls_certificate_provider*>(this),
                        other);
  }
};

class FakeCertificateProviderFactory1 : public CertificateProviderFactory {
 public:
  class Config : public CertificateProviderFactory::Config {
   public:
    absl::string_view name() const override { return "fake1"; }

    std::string ToString() const override { return "{}"; }
  };

  absl::string_view name() const override { return "fake1"; }

  RefCountedPtr<CertificateProviderFactory::Config>
  CreateCertificateProviderConfig(const Json& ,
                                  const JsonArgs& ,
                                  ValidationErrors* ) override {
    return MakeRefCounted<Config>();
  }

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<CertificateProviderFactory::Config> ) override {
    return MakeRefCounted<FakeCertificateProvider>();
  }
};

class FakeCertificateProviderFactory2 : public CertificateProviderFactory {
 public:
  class Config : public CertificateProviderFactory::Config {
   public:
    absl::string_view name() const override { return "fake2"; }

    std::string ToString() const override { return "{}"; }
  };

  absl::string_view name() const override { return "fake2"; }

  RefCountedPtr<CertificateProviderFactory::Config>
  CreateCertificateProviderConfig(const Json& ,
                                  const JsonArgs& ,
                                  ValidationErrors* ) override {
    return MakeRefCounted<Config>();
  }

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<CertificateProviderFactory::Config> ) override {
    return MakeRefCounted<FakeCertificateProvider>();
  }
};

TEST_F(CertificateProviderStoreTest, Basic) {

  auto* fake_factory_1 = new FakeCertificateProviderFactory1;
  CoreConfiguration::RunWithSpecialConfiguration(
      [=](CoreConfiguration::Builder* builder) {
        builder->certificate_provider_registry()
            ->RegisterCertificateProviderFactory(
                std::unique_ptr<CertificateProviderFactory>(fake_factory_1));
      },
      [=] {
        auto fake_factory_2 =
            std::make_unique<FakeCertificateProviderFactory2>();

        CertificateProviderStore::PluginDefinitionMap map = {
            {"fake_plugin_1",
             {"fake1", fake_factory_1->CreateCertificateProviderConfig(
                           Json::FromObject({}), JsonArgs(), nullptr)}},
            {"fake_plugin_2",
             {"fake2", fake_factory_2->CreateCertificateProviderConfig(
                           Json::FromObject({}), JsonArgs(), nullptr)}},
            {"fake_plugin_3",
             {"fake1", fake_factory_1->CreateCertificateProviderConfig(
                           Json::FromObject({}), JsonArgs(), nullptr)}},
        };
        auto store = MakeOrphanable<CertificateProviderStore>(std::move(map));

        auto cert_provider_1 =
            store->CreateOrGetCertificateProvider("fake_plugin_1");
        ASSERT_NE(cert_provider_1, nullptr);
        auto cert_provider_3 =
            store->CreateOrGetCertificateProvider("fake_plugin_3");
        ASSERT_NE(cert_provider_3, nullptr);

        ASSERT_EQ(store->CreateOrGetCertificateProvider("fake_plugin_2"),
                  nullptr);

        ASSERT_EQ(store->CreateOrGetCertificateProvider("unknown"), nullptr);

        ASSERT_EQ(store->CreateOrGetCertificateProvider("fake_plugin_1"),
                  cert_provider_1);
        ASSERT_EQ(store->CreateOrGetCertificateProvider("fake_plugin_3"),
                  cert_provider_3);

        cert_provider_1.reset();
        cert_provider_3.reset();
      });
}

TEST_F(CertificateProviderStoreTest, Multithreaded) {
  auto* fake_factory_1 = new FakeCertificateProviderFactory1;
  CoreConfiguration::RunWithSpecialConfiguration(
      [=](CoreConfiguration::Builder* builder) {
        builder->certificate_provider_registry()
            ->RegisterCertificateProviderFactory(
                std::unique_ptr<CertificateProviderFactory>(fake_factory_1));
      },
      [=] {
        CertificateProviderStore::PluginDefinitionMap map = {
            {"fake_plugin_1",
             {"fake1", fake_factory_1->CreateCertificateProviderConfig(
                           Json::FromObject({}), JsonArgs(), nullptr)}}};
        auto store = MakeOrphanable<CertificateProviderStore>(std::move(map));

        std::vector<std::thread> threads;
        threads.reserve(1000);
        for (auto i = 0; i < 1000; i++) {
          threads.emplace_back([&store]() {
            for (auto i = 0; i < 10; ++i) {
              ASSERT_NE(store->CreateOrGetCertificateProvider("fake_plugin_1"),
                        nullptr);
            }
          });
        }
        for (auto& thread : threads) {
          thread.join();
        }
      });
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
