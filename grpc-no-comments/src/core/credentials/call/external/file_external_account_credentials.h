
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_EXTERNAL_FILE_EXTERNAL_ACCOUNT_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_EXTERNAL_FILE_EXTERNAL_ACCOUNT_CREDENTIALS_H

#include <grpc/support/port_platform.h>

#include <functional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/credentials/call/external/external_account_credentials.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class FileExternalAccountCredentials final : public ExternalAccountCredentials {
 public:
  static absl::StatusOr<RefCountedPtr<FileExternalAccountCredentials>> Create(
      Options options, std::vector<std::string> scopes,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine = nullptr);

  FileExternalAccountCredentials(
      Options options, std::vector<std::string> scopes,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine,
      grpc_error_handle* error);

  std::string debug_string() override;

  static UniqueTypeName Type();

  UniqueTypeName type() const override { return Type(); }

 private:
  class FileFetchBody final : public FetchBody {
   public:
    FileFetchBody(absl::AnyInvocable<void(absl::StatusOr<std::string>)> on_done,
                  FileExternalAccountCredentials* creds);

   private:
    void Shutdown() override {}

    void ReadFile();

    FileExternalAccountCredentials* creds_;
  };

  OrphanablePtr<FetchBody> RetrieveSubjectToken(
      Timestamp deadline,
      absl::AnyInvocable<void(absl::StatusOr<std::string>)> on_done) override;

  absl::string_view CredentialSourceType() override;

  std::string file_;
  std::string format_type_;
  std::string format_subject_token_field_name_;
};

}

#endif
