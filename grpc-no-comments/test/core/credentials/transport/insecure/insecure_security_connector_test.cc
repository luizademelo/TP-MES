
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/insecure/insecure_security_connector.h"

#include <grpc/grpc_security.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/transport_security.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

TEST(InsecureSecurityConnector, MakeAuthContextTest) {
  auto auth_context = TestOnlyMakeInsecureAuthContext();

  EXPECT_EQ(auth_context->is_authenticated(), false);

  auto it = grpc_auth_context_find_properties_by_name(
      auth_context.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  ASSERT_NE(prop, nullptr);
  EXPECT_STREQ(prop->name, GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME);
  EXPECT_STREQ(prop->value, kInsecureTransportSecurityType);

  it = grpc_auth_context_find_properties_by_name(
      auth_context.get(), GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME);
  prop = grpc_auth_property_iterator_next(&it);
  ASSERT_NE(prop, nullptr);
  EXPECT_STREQ(prop->value, tsi_security_level_to_string(TSI_SECURITY_NONE));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  const auto result = RUN_ALL_TESTS();
  return result;
}
