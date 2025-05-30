
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TRANSPORT_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TRANSPORT_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>

#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"

#define GRPC_FAKE_TRANSPORT_SECURITY_TYPE "fake"

#define GRPC_ARG_CHANNEL_CREDENTIALS "grpc.internal.channel_credentials"

struct grpc_channel_credentials
    : grpc_core::RefCounted<grpc_channel_credentials> {
 public:
  static absl::string_view ChannelArgName() {
    return GRPC_ARG_CHANNEL_CREDENTIALS;
  }

  static int ChannelArgsCompare(const grpc_channel_credentials* args1,
                                const grpc_channel_credentials* args2) {
    return args1->cmp(args2);
  }

  virtual grpc_core::RefCountedPtr<grpc_channel_security_connector>
  create_security_connector(
      grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
      const char* target, grpc_core::ChannelArgs* args) = 0;

  virtual grpc_core::RefCountedPtr<grpc_channel_credentials>
  duplicate_without_call_credentials() {

    return Ref();
  }

  virtual grpc_core::ChannelArgs update_arguments(grpc_core::ChannelArgs args) {
    return args;
  }

  int cmp(const grpc_channel_credentials* other) const {
    CHECK_NE(other, nullptr);
    int r = type().Compare(other->type());
    if (r != 0) return r;
    return cmp_impl(other);
  }

  virtual grpc_core::UniqueTypeName type() const = 0;

 private:

  virtual int cmp_impl(const grpc_channel_credentials* other) const = 0;
};

grpc_arg grpc_channel_credentials_to_arg(grpc_channel_credentials* credentials);

grpc_channel_credentials* grpc_channel_credentials_from_arg(
    const grpc_arg* arg);

grpc_channel_credentials* grpc_channel_credentials_find_in_args(
    const grpc_channel_args* args);

#define GRPC_SERVER_CREDENTIALS_ARG "grpc.internal.server_credentials"

struct grpc_server_credentials
    : public grpc_core::RefCounted<grpc_server_credentials> {
 public:
  ~grpc_server_credentials() override { DestroyProcessor(); }

  static absl::string_view ChannelArgName() {
    return GRPC_SERVER_CREDENTIALS_ARG;
  }

  static int ChannelArgsCompare(const grpc_server_credentials* a,
                                const grpc_server_credentials* b) {
    return grpc_core::QsortCompare(a, b);
  }

  virtual grpc_core::RefCountedPtr<grpc_server_security_connector>
  create_security_connector(const grpc_core::ChannelArgs& args) = 0;

  virtual grpc_core::UniqueTypeName type() const = 0;

  const grpc_auth_metadata_processor& auth_metadata_processor() const {
    return processor_;
  }
  void set_auth_metadata_processor(
      const grpc_auth_metadata_processor& processor);

 private:
  void DestroyProcessor() {
    if (processor_.destroy != nullptr && processor_.state != nullptr) {
      processor_.destroy(processor_.state);
    }
  }

  grpc_auth_metadata_processor processor_ =
      grpc_auth_metadata_processor();
};

grpc_arg grpc_server_credentials_to_arg(grpc_server_credentials* c);
grpc_server_credentials* grpc_server_credentials_from_arg(const grpc_arg* arg);
grpc_server_credentials* grpc_find_server_credentials_in_args(
    const grpc_channel_args* args);

#endif
