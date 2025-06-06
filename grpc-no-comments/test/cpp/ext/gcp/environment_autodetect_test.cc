
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/gcp/environment_autodetect.h"

#include <grpc/grpc.h>

#include <string>
#include <thread>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/synchronization/notification.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/env.h"
#include "src/core/util/notification.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {

namespace {

class EnvironmentAutoDetectTest : public ::testing::Test {
 protected:
  void GetNotifiedOnEnvironmentDetection(
      grpc::internal::EnvironmentAutoDetect* env,
      grpc_core::Notification* notify) {
    env->NotifyOnDone([notify]() { notify->Notify(); });
  }
};

TEST_F(EnvironmentAutoDetectTest, Basic) {
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify;
  GetNotifiedOnEnvironmentDetection(&env, &notify);
  notify.WaitForNotification();

  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
}

TEST_F(EnvironmentAutoDetectTest, GkeEnvironment) {
  grpc_core::SetEnv("KUBERNETES_SERVICE_HOST", "k8s_service_host");
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify;
  GetNotifiedOnEnvironmentDetection(&env, &notify);
  notify.WaitForNotification();

  EXPECT_EQ(env.resource()->resource_type, "k8s_container");
  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
  grpc_core::UnsetEnv("KUBERNETES_SERVICE_HOST");
}

TEST_F(EnvironmentAutoDetectTest, CloudFunctions) {
  grpc_core::SetEnv("FUNCTION_NAME", "function_name");
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify;
  GetNotifiedOnEnvironmentDetection(&env, &notify);
  notify.WaitForNotification();

  EXPECT_EQ(env.resource()->resource_type, "cloud_function");
  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
  grpc_core::UnsetEnv("FUNCTION_NAME");
}

TEST_F(EnvironmentAutoDetectTest, CloudRun) {
  grpc_core::SetEnv("K_CONFIGURATION", "config");
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify;
  GetNotifiedOnEnvironmentDetection(&env, &notify);
  notify.WaitForNotification();

  EXPECT_EQ(env.resource()->resource_type, "cloud_run_revision");
  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
  grpc_core::UnsetEnv("K_CONFIGURATION");
}

TEST_F(EnvironmentAutoDetectTest, AppEngine) {
  grpc_core::SetEnv("K_CONFIGURATION", "config");
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify;
  GetNotifiedOnEnvironmentDetection(&env, &notify);
  notify.WaitForNotification();

  EXPECT_EQ(env.resource()->resource_type, "cloud_run_revision");
  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
  grpc_core::UnsetEnv("K_CONFIGURATION");
}

TEST_F(EnvironmentAutoDetectTest, MultipleNotifyWaiters) {
  grpc::internal::EnvironmentAutoDetect env("project");

  grpc_core::Notification notify[10];
  for (int i = 0; i < 10; ++i) {
    GetNotifiedOnEnvironmentDetection(&env, &notify[i]);
  }
  for (int i = 0; i < 10; ++i) {
    notify[i].WaitForNotification();
  }

  EXPECT_EQ((env.resource()->labels).at("project_id"), "project");
}

}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret_val = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret_val;
}
