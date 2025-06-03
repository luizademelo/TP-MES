Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include platform-specific headers
#include <grpc/support/port_platform.h>

// Only compile this code on Windows platforms
#if defined(GPR_WINDOWS)

// Link with the Windows Cryptography API library
#pragma comment(lib, "crypt32")

// Include necessary headers
#include <esent.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <wincrypt.h>

#include <vector>

// Include project-specific headers
#include "src/core/credentials/transport/tls/load_system_roots.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace {

// Helper function to convert a wide string (UTF-16) to UTF-8 encoded string
// Parameters:
//   wstr - The wide string to convert
// Returns:
//   UTF-8 encoded string representation of the input
std::string Utf8Encode(const std::wstring& wstr) {
  if (wstr.empty()) return "";

  // First call to WideCharToMultiByte determines the required buffer size
  int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                                        NULL, 0, NULL, NULL);
  // Create output string with the required size
  std::string str_to(size_needed, 0);
  // Perform the actual conversion
  WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str_to[0],
                      size_needed, NULL, NULL);
  return str_to;
}

}  // namespace

// Function to load system root certificates on Windows
// Returns:
//   A grpc_slice containing all system root certificates in PEM format,
//   or an empty slice if no certificates were found or an error occurred
grpc_slice LoadSystemRootCerts() {
  std::string bundle_string;  // Will accumulate all certificates in PEM format

  // Open the system certificate store containing root certificates
  HANDLE root_cert_store = CertOpenSystemStoreW(NULL, L"ROOT");
  if (!root_cert_store) {
    // Return empty slice if we couldn't open the certificate store
    return grpc_empty_slice();
  }

  // Iterate through all certificates in the store
  PCCERT_CONTEXT cert = NULL;
  while ((cert = CertEnumCertificatesInStore(root_cert_store, cert)) != NULL) {
    // Determine required buffer size for base64 encoding
    DWORD size = 0;
    CryptBinaryToStringW(cert->pbCertEncoded, cert->cbCertEncoded,
                         CRYPT_STRING_BASE64HEADER, NULL, &size);
    
    // Create buffer and perform base64 encoding
    std::vector<WCHAR> pem(size);
    CryptBinaryToStringW(cert->pbCertEncoded, cert->cbCertEncoded,
                         CRYPT_STRING_BASE64HEADER, pem.data(), &size);
    
    // Convert to UTF-8 and add to the bundle
    bundle_string += Utf8Encode(pem.data());
  }

  // Clean up certificate store handle
  CertCloseStore(root_cert_store, 0);
  
  // Return empty slice if no certificates were found
  if (bundle_string.size() == 0) {
    return grpc_empty_slice();
  }

  // Convert the accumulated certificates to a grpc_slice and return
  return grpc_slice_from_cpp_string(std::move(bundle_string));
}

}  // namespace grpc_core

#endif  // GPR_WINDOWS
```