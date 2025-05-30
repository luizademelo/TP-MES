
// Copyright 2023 gRPC authors.

#include <grpc/support/port_platform.h>

#if defined(GPR_WINDOWS)

#pragma comment(lib, "crypt32")

#include <esent.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <wincrypt.h>

#include <vector>

#include "src/core/credentials/transport/tls/load_system_roots.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace {

std::string Utf8Encode(const std::wstring& wstr) {
  if (wstr.empty()) return "";

  int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                                        NULL, 0, NULL, NULL);
  std::string str_to(size_needed, 0);
  WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str_to[0],
                      size_needed, NULL, NULL);
  return str_to;
}

}

grpc_slice LoadSystemRootCerts() {
  std::string bundle_string;

  HANDLE root_cert_store = CertOpenSystemStoreW(NULL, L"ROOT");
  if (!root_cert_store) {
    return grpc_empty_slice();
  }

  PCCERT_CONTEXT cert = NULL;
  while ((cert = CertEnumCertificatesInStore(root_cert_store, cert)) != NULL) {

    DWORD size = 0;
    CryptBinaryToStringW(cert->pbCertEncoded, cert->cbCertEncoded,
                         CRYPT_STRING_BASE64HEADER, NULL, &size);
    std::vector<WCHAR> pem(size);
    CryptBinaryToStringW(cert->pbCertEncoded, cert->cbCertEncoded,
                         CRYPT_STRING_BASE64HEADER, pem.data(), &size);
    bundle_string += Utf8Encode(pem.data());
  }

  CertCloseStore(root_cert_store, 0);
  if (bundle_string.size() == 0) {
    return grpc_empty_slice();
  }

  return grpc_slice_from_cpp_string(std::move(bundle_string));
}

}

#endif
