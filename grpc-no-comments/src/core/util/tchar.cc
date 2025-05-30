// Copyright 2022 gRPC authors.

#include "src/core/util/tchar.h"

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

namespace grpc_core {

#if defined UNICODE || defined _UNICODE
TcharString CharToTchar(std::string input) {
  int needed = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
  if (needed <= 0) return TcharString();
  TcharString ret(needed, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1,
                      const_cast<LPTSTR>(ret.data()), needed);
  return ret;
}

std::string TcharToChar(TcharString input) {
  int needed =
      WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, NULL);
  if (needed <= 0) return std::string();
  std::string ret(needed, '\0');
  WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1,
                      const_cast<LPSTR>(ret.data()), needed, NULL, NULL);
  return ret;
}
#else
TcharString CharToTchar(std::string input) { return input; }
std::string TcharToChar(TcharString input) { return input; }
#endif

}

#endif
