
// Copyright 2017 gRPC authors.

#include "test/cpp/microbenchmarks/helpers.h"

#include <string.h>

#include "absl/log/check.h"

static LibraryInitializer* g_libraryInitializer;

LibraryInitializer::LibraryInitializer() {
  CHECK_EQ(g_libraryInitializer, nullptr);
  g_libraryInitializer = this;
}

LibraryInitializer::~LibraryInitializer() { g_libraryInitializer = nullptr; }

LibraryInitializer& LibraryInitializer::get() {
  CHECK_NE(g_libraryInitializer, nullptr);
  return *g_libraryInitializer;
}
