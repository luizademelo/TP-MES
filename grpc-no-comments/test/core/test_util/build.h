// Copyright 2021 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_BUILD_H
#define GRPC_TEST_CORE_TEST_UTIL_BUILD_H

bool BuiltUnderValgrind();

bool BuiltUnderTsan();

bool BuiltUnderAsan();

bool BuiltUnderMsan();

bool BuiltUnderUbsan();

void AsanAssertNoLeaks();

#endif
