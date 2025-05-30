
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CORE_HANDSHAKE_SERVER_SSL_COMMON_H
#define GRPC_TEST_CORE_HANDSHAKE_SERVER_SSL_COMMON_H

bool server_ssl_test(const char* alpn_list[], unsigned int alpn_list_len,
                     const char* alpn_expected);

void CleanupSslLibrary();

#endif
