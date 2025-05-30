// Copyright 2021 gRPC authors.

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>

#include <list>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/lib/security/authorization/matchers.h"
#include "test/core/test_util/evaluate_args_test_util.h"

namespace grpc_core {

class AuthorizationMatchersTest : public ::testing::Test {
 protected:
  EvaluateArgsTestUtil args_;
};

TEST_F(AuthorizationMatchersTest, AlwaysAuthorizationMatcher) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AlwaysAuthorizationMatcher matcher;
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AndAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata("foo", "bar");
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeDestPortPermission(123)));
  auto matcher = AuthorizationMatcher::Create(
      Rbac::Permission::MakeAndPermission(std::move(rules)));
  EXPECT_TRUE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, AndAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata("foo", "not_bar");
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeDestPortPermission(123)));
  auto matcher = AuthorizationMatcher::Create(
      Rbac::Permission(Rbac::Permission::MakeAndPermission(std::move(rules))));

  EXPECT_FALSE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, OrAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata("foo", "bar");
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeDestPortPermission(456)));
  auto matcher = AuthorizationMatcher::Create(
      Rbac::Permission(Rbac::Permission::MakeOrPermission(std::move(rules))));

  EXPECT_TRUE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, OrAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata("foo", "not_bar");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  auto matcher = AuthorizationMatcher::Create(
      Rbac::Permission(Rbac::Permission::MakeOrPermission(std::move(rules))));

  EXPECT_FALSE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, NotAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata(":path", "/different/foo");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  auto matcher = AuthorizationMatcher::Create(Rbac::Principal(
      Rbac::Principal::MakeNotPrincipal(Rbac::Principal::MakePathPrincipal(
          StringMatcher::Create(StringMatcher::Type::kExact,
                                "/expected/foo",
                                false)
              .value()))));
  EXPECT_TRUE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, NotAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata(":path", "/expected/foo");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  auto matcher = AuthorizationMatcher::Create(Rbac::Principal(
      Rbac::Principal::MakeNotPrincipal(Rbac::Principal::MakePathPrincipal(
          StringMatcher::Create(StringMatcher::Type::kExact,
                                "/expected/foo",
                                false)
              .value()))));
  EXPECT_FALSE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, HybridAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata("foo", "bar");
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> sub_and_rules;
  sub_and_rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  std::vector<std::unique_ptr<Rbac::Permission>> sub_or_rules;
  sub_or_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeDestPortPermission(123)));
  std::vector<std::unique_ptr<Rbac::Permission>> and_rules;
  and_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeAndPermission(std::move(sub_and_rules))));
  and_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeOrPermission(std::move(std::move(sub_or_rules)))));
  auto matcher = AuthorizationMatcher::Create(Rbac::Permission(
      Rbac::Permission::MakeAndPermission(std::move(and_rules))));
  EXPECT_TRUE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest, HybridAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata("foo", "bar");
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> sub_and_rules;
  sub_and_rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("foo", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  sub_and_rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("absent_key",
                                HeaderMatcher::Type::kExact,
                                "some_value")
              .value())));
  std::vector<std::unique_ptr<Rbac::Permission>> sub_or_rules;
  sub_or_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeDestPortPermission(123)));
  std::vector<std::unique_ptr<Rbac::Permission>> and_rules;
  and_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeAndPermission(std::move(sub_and_rules))));
  and_rules.push_back(std::make_unique<Rbac::Permission>(
      Rbac::Permission::MakeOrPermission(std::move(std::move(sub_or_rules)))));
  auto matcher = AuthorizationMatcher::Create(Rbac::Permission(
      Rbac::Permission::MakeAndPermission(std::move(and_rules))));

  EXPECT_FALSE(matcher->Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       ReqServerNameAuthorizationMatcherSuccessfulMatch) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  ReqServerNameAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       ReqServerNameAuthorizationMatcherFailedMatch) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  ReqServerNameAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "server1")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PathAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata(":path", "expected/path");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  PathAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "expected/path",
                            false)
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PathAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata(":path", "different/path");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  PathAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "expected/path",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       PathAuthorizationMatcherFailedMatchMissingPath) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  PathAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "expected/path",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, MetadataAuthorizationMatcherSuccessfulMatch) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  MetadataAuthorizationMatcher matcher(true);
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, MetadataAuthorizationMatcherFailedMatch) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  MetadataAuthorizationMatcher matcher(false);
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata("key123", "foo_xxx");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create("key123", HeaderMatcher::Type::kPrefix,
                            "foo")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata("key123", "foo");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create("key123", HeaderMatcher::Type::kExact,
                            "bar")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherMethodSuccess) {
  args_.AddPairToMetadata(":method", "GET");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":method", HeaderMatcher::Type::kExact,
                            "GET")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherMethodFail) {
  args_.AddPairToMetadata(":method", "GET");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":method", HeaderMatcher::Type::kExact,
                            "PUT")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherAuthoritySuccess) {
  args_.AddPairToMetadata(":authority", "localhost");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":authority", HeaderMatcher::Type::kExact,
                            "localhost")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherAuthorityFail) {
  args_.AddPairToMetadata(":authority", "localhost");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":authority", HeaderMatcher::Type::kExact,
                            "bad_authority")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherPathSuccess) {
  args_.AddPairToMetadata(":path", "/expected/path");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":path", HeaderMatcher::Type::kExact,
                            "/expected/path")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, HeaderAuthorizationMatcherPathFail) {
  args_.AddPairToMetadata(":path", "/expected/path");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create(":path", HeaderMatcher::Type::kExact,
                            "/unexpected/path")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       HeaderAuthorizationMatcherFailedMatchMultivaluedHeader) {
  args_.AddPairToMetadata("key123", "foo");
  args_.AddPairToMetadata("key123", "bar");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create("key123", HeaderMatcher::Type::kExact,
                            "foo")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       HeaderAuthorizationMatcherFailedMatchMissingHeader) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  HeaderAuthorizationMatcher matcher(
      HeaderMatcher::Create("key123", HeaderMatcher::Type::kSuffix,
                            "foo")
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, IpAuthorizationMatcherDestIpSuccessfulMatch) {
  args_.SetLocalEndpoint("ipv4:1.2.3.4:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kDestIp,
      Rbac::CidrRange("1.7.8.9", 8));
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, IpAuthorizationMatcherDestIpFailedMatch) {
  args_.SetLocalEndpoint("ipv4:1.2.3.4:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kDestIp,
      Rbac::CidrRange("1.2.3.9", 32));
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       IpAuthorizationMatcherSourceIpSuccessfulMatch) {
  args_.SetPeerEndpoint("ipv6:[1:2:3::]:456");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kSourceIp,
      Rbac::CidrRange("1:3:4::", 16));
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, IpAuthorizationMatcherSourceIpFailedMatch) {
  args_.SetPeerEndpoint("ipv6:[1:2::3::]:456");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kSourceIp,
      Rbac::CidrRange("1:3::", 48));
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       IpAuthorizationMatcherRemoteIpSuccessfulMatch) {
  args_.SetPeerEndpoint("ipv6:[1:2:3::]:456");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kRemoteIp,
      Rbac::CidrRange("1:2:4::", 32));
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, IpAuthorizationMatcherRemoteIpFailedMatch) {
  args_.SetPeerEndpoint("ipv6:[1:2::]:456");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kRemoteIp,
      Rbac::CidrRange("1:3::", 32));
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       IpAuthorizationMatcherDirectRemoteIpSuccessfulMatch) {
  args_.SetPeerEndpoint("ipv4:1.2.3.4:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kDirectRemoteIp,
      Rbac::CidrRange("1.7.8.9", 8));
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       IpAuthorizationMatcherDirectRemoteIpFailedMatch) {
  args_.SetPeerEndpoint("ipv4:1.2.3.4:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  IpAuthorizationMatcher matcher(
      IpAuthorizationMatcher::Type::kDirectRemoteIp,
      Rbac::CidrRange("1.7.8.9", 16));
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PortAuthorizationMatcherSuccessfulMatch) {
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  PortAuthorizationMatcher matcher(123);
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PortAuthorizationMatcherFailedMatch) {
  args_.SetLocalEndpoint("ipv4:255.255.255.255:123");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  PortAuthorizationMatcher matcher(456);
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       AuthenticatedMatcherUnAuthenticatedConnection) {
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "foo.com",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       AuthenticatedMatcherAuthenticatedConnectionMatcherUnset) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(std::nullopt);
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherSuccessfulUriSanMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_TLS_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_PEER_URI_PROPERTY_NAME,
                                 "spiffe://foo.abc");
  args_.AddPropertyToAuthContext(GRPC_PEER_URI_PROPERTY_NAME,
                                 "https://foo.domain.com");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "spiffe://foo.abc",
                            false)
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherFailedUriSanMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_TLS_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_PEER_URI_PROPERTY_NAME,
                                 "spiffe://bar.abc");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "spiffe://foo.abc",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherSuccessfulDnsSanMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_PEER_URI_PROPERTY_NAME,
                                 "spiffe://bar.abc");
  args_.AddPropertyToAuthContext(GRPC_PEER_DNS_PROPERTY_NAME,
                                 "foo.test.domain.com");
  args_.AddPropertyToAuthContext(GRPC_PEER_DNS_PROPERTY_NAME,
                                 "bar.test.domain.com");
  EvaluateArgs args = args_.MakeEvaluateArgs();

  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "bar.test.domain.com",
                            false)
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherFailedDnsSanMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_PEER_DNS_PROPERTY_NAME,
                                 "foo.test.domain.com");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "bar.test.domain.com",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest,
       AuthenticatedMatcherSuccessfulSubjectMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_TLS_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_X509_SUBJECT_PROPERTY_NAME,
                                 "CN=abc,OU=Google");
  EvaluateArgs args = args_.MakeEvaluateArgs();

  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "CN=abc,OU=Google",
                            false)
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherFailedSubjectMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  args_.AddPropertyToAuthContext(GRPC_X509_SUBJECT_PROPERTY_NAME,
                                 "CN=abc,OU=Google");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "CN=def,OU=Google",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(
    AuthorizationMatchersTest,
    AuthenticatedMatcherWithoutClientCertMatchesSuccessfullyOnEmptyPrincipal) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_TLS_TRANSPORT_SECURITY_TYPE);
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "")
          .value());
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, AuthenticatedMatcherFailedNothingMatches) {
  args_.AddPropertyToAuthContext(GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
                                 GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  EvaluateArgs args = args_.MakeEvaluateArgs();
  AuthenticatedAuthorizationMatcher matcher(
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "foo",
                            false)
          .value());
  EXPECT_FALSE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PolicyAuthorizationMatcherSuccessfulMatch) {
  args_.AddPairToMetadata("key123", "foo");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("key123", HeaderMatcher::Type::kExact,
                                "foo")
              .value())));
  PolicyAuthorizationMatcher matcher(Rbac::Policy(
      Rbac::Permission(Rbac::Permission::MakeOrPermission(std::move(rules))),
      Rbac::Principal::MakeAnyPrincipal()));
  EXPECT_TRUE(matcher.Matches(args));
}

TEST_F(AuthorizationMatchersTest, PolicyAuthorizationMatcherFailedMatch) {
  args_.AddPairToMetadata("key123", "foo");
  EvaluateArgs args = args_.MakeEvaluateArgs();
  std::vector<std::unique_ptr<Rbac::Permission>> rules;
  rules.push_back(
      std::make_unique<Rbac::Permission>(Rbac::Permission::MakeHeaderPermission(
          HeaderMatcher::Create("key123", HeaderMatcher::Type::kExact,
                                "bar")
              .value())));
  PolicyAuthorizationMatcher matcher(Rbac::Policy(
      Rbac::Permission(Rbac::Permission::MakeOrPermission(std::move(rules))),
      Rbac::Principal::MakeAnyPrincipal()));
  EXPECT_FALSE(matcher.Matches(args));
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
