// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TCHAR_H
#define GRPC_SRC_CORE_UTIL_TCHAR_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS
#include <string>

namespace grpc_core {

using TcharString = std::basic_string<TCHAR>;

TcharString CharToTchar(std::string input);
std::string TcharToChar(TcharString input);

}
#endif

#endif
