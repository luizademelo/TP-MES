
// Copyright 2015-2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_CREATE_TEST_CHANNEL_H
#define GRPC_TEST_CPP_UTIL_CREATE_TEST_CHANNEL_H

#include <grpcpp/channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>

namespace grpc {
class Channel;

namespace testing {

typedef enum { INSECURE = 0, TLS, ALTS } transport_security;

}

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, testing::transport_security security_type);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& override_hostname,
    testing::transport_security security_type, bool use_prod_roots);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& override_hostname,
    testing::transport_security security_type, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& override_hostname,
    testing::transport_security security_type, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds,
    const ChannelArguments& args);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& cred_type,
    const std::string& override_hostname, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds,
    const ChannelArguments& args);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& credential_type,
    const std::shared_ptr<CallCredentials>& creds);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& override_hostname,
    testing::transport_security security_type, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& override_hostname,
    testing::transport_security security_type, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds, const ChannelArguments& args,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& cred_type,
    const std::string& override_hostname, bool use_prod_roots,
    const std::shared_ptr<CallCredentials>& creds, const ChannelArguments& args,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& credential_type,
    const std::shared_ptr<CallCredentials>& creds,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

std::shared_ptr<Channel> CreateTestChannel(
    const std::string& server, const std::string& credential_type,
    const std::shared_ptr<CallCredentials>& creds,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators,
    ChannelArguments channel_args);

}

#endif
