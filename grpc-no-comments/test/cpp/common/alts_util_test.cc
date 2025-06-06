
// Copyright 2019 gRPC authors.

#include <grpcpp/security/alts_context.h>
#include <grpcpp/security/alts_util.h>
#include <grpcpp/security/auth_context.h>

#include "gtest/gtest.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"
#include "src/cpp/common/secure_auth_context.h"
#include "src/proto/grpc/gcp/altscontext.upb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/string_ref_helper.h"
#include "upb/mem/arena.hpp"

namespace grpc {
namespace {

TEST(AltsUtilTest, NullAuthContext) {
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(nullptr);
  EXPECT_EQ(alts_context, nullptr);
}

TEST(AltsUtilTest, EmptyAuthContext) {
  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(auth_context);
  EXPECT_EQ(alts_context, nullptr);
}

TEST(AltsUtilTest, AuthContextWithMoreThanOneAltsContext) {
  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  ctx.reset();
  auth_context->AddProperty(TSI_ALTS_CONTEXT, "context1");
  auth_context->AddProperty(TSI_ALTS_CONTEXT, "context2");
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(auth_context);
  EXPECT_EQ(alts_context, nullptr);
}

TEST(AltsUtilTest, AuthContextWithBadAltsContext) {
  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  ctx.reset();
  auth_context->AddProperty(TSI_ALTS_CONTEXT,
                            "bad context string serialization");
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(auth_context);
  EXPECT_EQ(alts_context, nullptr);
}

TEST(AltsUtilTest, AuthContextWithGoodAltsContextWithoutRpcVersions) {
  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  ctx.reset();
  std::string expected_ap("application protocol");
  std::string expected_rp("record protocol");
  std::string expected_peer("peer");
  std::string expected_local("local");
  std::string expected_peer_attributes_key("peer");
  std::string expected_peer_attributes_value("attributes");
  grpc_security_level expected_sl = GRPC_INTEGRITY_ONLY;
  upb::Arena context_arena;
  grpc_gcp_AltsContext* context = grpc_gcp_AltsContext_new(context_arena.ptr());
  grpc_gcp_AltsContext_set_application_protocol(
      context,
      upb_StringView_FromDataAndSize(expected_ap.data(), expected_ap.length()));
  grpc_gcp_AltsContext_set_record_protocol(
      context,
      upb_StringView_FromDataAndSize(expected_rp.data(), expected_rp.length()));
  grpc_gcp_AltsContext_set_security_level(context, expected_sl);
  grpc_gcp_AltsContext_set_peer_service_account(
      context, upb_StringView_FromDataAndSize(expected_peer.data(),
                                              expected_peer.length()));
  grpc_gcp_AltsContext_set_local_service_account(
      context, upb_StringView_FromDataAndSize(expected_local.data(),
                                              expected_local.length()));
  grpc_gcp_AltsContext_peer_attributes_set(
      context,
      upb_StringView_FromDataAndSize(expected_peer_attributes_key.data(),
                                     expected_peer_attributes_key.length()),
      upb_StringView_FromDataAndSize(expected_peer_attributes_value.data(),
                                     expected_peer_attributes_value.length()),
      context_arena.ptr());
  size_t serialized_ctx_length;
  char* serialized_ctx = grpc_gcp_AltsContext_serialize(
      context, context_arena.ptr(), &serialized_ctx_length);
  EXPECT_NE(serialized_ctx, nullptr);
  auth_context->AddProperty(TSI_ALTS_CONTEXT,
                            string(serialized_ctx, serialized_ctx_length));
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(auth_context);
  EXPECT_NE(alts_context, nullptr);
  EXPECT_EQ(expected_ap, alts_context->application_protocol());
  EXPECT_EQ(expected_rp, alts_context->record_protocol());
  EXPECT_EQ(expected_peer, alts_context->peer_service_account());
  EXPECT_EQ(expected_local, alts_context->local_service_account());
  EXPECT_EQ(expected_sl, alts_context->security_level());

  experimental::AltsContext::RpcProtocolVersions rpc_protocol_versions =
      alts_context->peer_rpc_versions();
  EXPECT_EQ(0, rpc_protocol_versions.max_rpc_version.major_version);
  EXPECT_EQ(0, rpc_protocol_versions.max_rpc_version.minor_version);
  EXPECT_EQ(0, rpc_protocol_versions.min_rpc_version.major_version);
  EXPECT_EQ(0, rpc_protocol_versions.min_rpc_version.minor_version);
  EXPECT_EQ(expected_peer_attributes_value,
            alts_context->peer_attributes().at(expected_peer_attributes_key));
}

TEST(AltsUtilTest, AuthContextWithGoodAltsContext) {
  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  ctx.reset();
  upb::Arena context_arena;
  grpc_gcp_AltsContext* context = grpc_gcp_AltsContext_new(context_arena.ptr());
  upb::Arena versions_arena;
  grpc_gcp_RpcProtocolVersions* versions =
      grpc_gcp_RpcProtocolVersions_new(versions_arena.ptr());
  upb::Arena max_major_version_arena;
  grpc_gcp_RpcProtocolVersions_Version* version =
      grpc_gcp_RpcProtocolVersions_Version_new(max_major_version_arena.ptr());
  grpc_gcp_RpcProtocolVersions_Version_set_major(version, 10);
  grpc_gcp_RpcProtocolVersions_set_max_rpc_version(versions, version);
  grpc_gcp_AltsContext_set_peer_rpc_versions(context, versions);
  size_t serialized_ctx_length;
  char* serialized_ctx = grpc_gcp_AltsContext_serialize(
      context, context_arena.ptr(), &serialized_ctx_length);
  EXPECT_NE(serialized_ctx, nullptr);
  auth_context->AddProperty(TSI_ALTS_CONTEXT,
                            string(serialized_ctx, serialized_ctx_length));
  std::unique_ptr<experimental::AltsContext> alts_context =
      experimental::GetAltsContextFromAuthContext(auth_context);
  EXPECT_NE(alts_context, nullptr);
  EXPECT_EQ("", alts_context->application_protocol());
  EXPECT_EQ("", alts_context->record_protocol());
  EXPECT_EQ("", alts_context->peer_service_account());
  EXPECT_EQ("", alts_context->local_service_account());
  EXPECT_EQ(GRPC_SECURITY_NONE, alts_context->security_level());
  experimental::AltsContext::RpcProtocolVersions rpc_protocol_versions =
      alts_context->peer_rpc_versions();
  EXPECT_EQ(10, rpc_protocol_versions.max_rpc_version.major_version);
  EXPECT_EQ(0, rpc_protocol_versions.max_rpc_version.minor_version);
  EXPECT_EQ(0, rpc_protocol_versions.min_rpc_version.major_version);
  EXPECT_EQ(0, rpc_protocol_versions.min_rpc_version.minor_version);
}

TEST(AltsUtilTest, AltsClientAuthzCheck) {

  const std::shared_ptr<AuthContext> bad_auth_context(
      new SecureAuthContext(nullptr));
  std::vector<std::string> service_accounts{"client"};
  grpc::Status status =
      experimental::AltsClientAuthzCheck(bad_auth_context, service_accounts);
  EXPECT_EQ(grpc::StatusCode::PERMISSION_DENIED, status.error_code());

  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  const std::shared_ptr<AuthContext> auth_context(
      new SecureAuthContext(ctx.get()));
  ctx.reset();
  std::string peer("good_client");
  std::vector<std::string> good_service_accounts{"good_client",
                                                 "good_client_1"};
  std::vector<std::string> bad_service_accounts{"bad_client", "bad_client_1"};
  upb::Arena context_arena;
  grpc_gcp_AltsContext* context = grpc_gcp_AltsContext_new(context_arena.ptr());
  grpc_gcp_AltsContext_set_peer_service_account(
      context, upb_StringView_FromDataAndSize(peer.data(), peer.length()));
  size_t serialized_ctx_length;
  char* serialized_ctx = grpc_gcp_AltsContext_serialize(
      context, context_arena.ptr(), &serialized_ctx_length);
  EXPECT_NE(serialized_ctx, nullptr);
  auth_context->AddProperty(TSI_ALTS_CONTEXT,
                            string(serialized_ctx, serialized_ctx_length));
  grpc::Status good_status =
      experimental::AltsClientAuthzCheck(auth_context, good_service_accounts);
  EXPECT_TRUE(good_status.ok());
  grpc::Status bad_status =
      experimental::AltsClientAuthzCheck(auth_context, bad_service_accounts);
  EXPECT_EQ(grpc::StatusCode::PERMISSION_DENIED, bad_status.error_code());
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
