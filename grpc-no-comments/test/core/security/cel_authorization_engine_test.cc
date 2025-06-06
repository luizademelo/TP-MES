// Copyright 2020 gRPC authors.

#include "src/core/lib/security/authorization/cel_authorization_engine.h"

#include "gtest/gtest.h"

namespace grpc_core {

class CelAuthorizationEngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    deny_policy_ = envoy_config_rbac_v3_RBAC_new(arena_.ptr());
    envoy_config_rbac_v3_RBAC_set_action(deny_policy_, 1);
    allow_policy_ = envoy_config_rbac_v3_RBAC_new(arena_.ptr());
    envoy_config_rbac_v3_RBAC_set_action(allow_policy_, 0);
  }
  upb::Arena arena_;
  envoy_config_rbac_v3_RBAC* deny_policy_;
  envoy_config_rbac_v3_RBAC* allow_policy_;
};

TEST_F(CelAuthorizationEngineTest, CreateEngineSuccessOnePolicy) {
  std::vector<envoy_config_rbac_v3_RBAC*> policies{allow_policy_};
  std::unique_ptr<CelAuthorizationEngine> engine =
      CelAuthorizationEngine::CreateCelAuthorizationEngine(policies);
  EXPECT_NE(engine, nullptr)
      << "Error: Failed to create CelAuthorizationEngine with one policy.";
}

TEST_F(CelAuthorizationEngineTest, CreateEngineSuccessTwoPolicies) {
  std::vector<envoy_config_rbac_v3_RBAC*> policies{deny_policy_, allow_policy_};
  std::unique_ptr<CelAuthorizationEngine> engine =
      CelAuthorizationEngine::CreateCelAuthorizationEngine(policies);
  EXPECT_NE(engine, nullptr)
      << "Error: Failed to create CelAuthorizationEngine with two policies.";
}

TEST_F(CelAuthorizationEngineTest, CreateEngineFailNoPolicies) {
  std::vector<envoy_config_rbac_v3_RBAC*> policies{};
  std::unique_ptr<CelAuthorizationEngine> engine =
      CelAuthorizationEngine::CreateCelAuthorizationEngine(policies);
  EXPECT_EQ(engine, nullptr)
      << "Error: Created CelAuthorizationEngine without policies.";
}

TEST_F(CelAuthorizationEngineTest, CreateEngineFailTooManyPolicies) {
  std::vector<envoy_config_rbac_v3_RBAC*> policies{deny_policy_, allow_policy_,
                                                   deny_policy_};
  std::unique_ptr<CelAuthorizationEngine> engine =
      CelAuthorizationEngine::CreateCelAuthorizationEngine(policies);
  EXPECT_EQ(engine, nullptr)
      << "Error: Created CelAuthorizationEngine with more than two policies.";
}

TEST_F(CelAuthorizationEngineTest, CreateEngineFailWrongPolicyOrder) {
  std::vector<envoy_config_rbac_v3_RBAC*> policies{allow_policy_, deny_policy_};
  std::unique_ptr<CelAuthorizationEngine> engine =
      CelAuthorizationEngine::CreateCelAuthorizationEngine(policies);
  EXPECT_EQ(engine, nullptr) << "Error: Created CelAuthorizationEngine with "
                                "policies in the wrong order.";
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
