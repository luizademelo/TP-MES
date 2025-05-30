
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CPP_MICROBENCHMARKS_FULLSTACK_CONTEXT_MUTATORS_H
#define GRPC_TEST_CPP_MICROBENCHMARKS_FULLSTACK_CONTEXT_MUTATORS_H

#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "src/core/util/crash.h"
#include "test/cpp/microbenchmarks/helpers.h"

namespace grpc {
namespace testing {

static const int kPregenerateKeyCount = 100000;

template <class F>
auto MakeVector(size_t length, F f) -> std::vector<decltype(f())> {
  std::vector<decltype(f())> out;
  out.reserve(length);
  for (size_t i = 0; i < length; i++) {
    out.push_back(f());
  }
  return out;
}

class NoOpMutator {
 public:
  template <class ContextType>
  explicit NoOpMutator(ContextType* ) {}
};

template <int length>
class RandomBinaryMetadata {
 public:
  static const std::string& Key() { return kKey; }

  static const std::string& Value() { return kValues[rand() % kValues.size()]; }

 private:
  static const std::string kKey;
  static const std::vector<std::string> kValues;

  static std::string GenerateOneString() {
    std::string s;
    s.reserve(length + 1);
    for (int i = 0; i < length; i++) {
      s += static_cast<char>(rand());
    }
    return s;
  }
};

template <int length>
class RandomAsciiMetadata {
 public:
  static const std::string& Key() { return kKey; }

  static const std::string& Value() { return kValues[rand() % kValues.size()]; }

 private:
  static const std::string kKey;
  static const std::vector<std::string> kValues;

  static std::string GenerateOneString() {
    std::string s;
    s.reserve(length + 1);
    for (int i = 0; i < length; i++) {
      s += static_cast<char>((rand() % 26) + 'a');
    }
    return s;
  }
};

template <class Generator, int kNumKeys>
class Client_AddMetadata : public NoOpMutator {
 public:
  explicit Client_AddMetadata(ClientContext* context) : NoOpMutator(context) {
    for (int i = 0; i < kNumKeys; i++) {
      context->AddMetadata(Generator::Key(), Generator::Value());
    }
  }
};

template <class Generator, int kNumKeys>
class Server_AddInitialMetadata : public NoOpMutator {
 public:
  explicit Server_AddInitialMetadata(ServerContext* context)
      : NoOpMutator(context) {
    for (int i = 0; i < kNumKeys; i++) {
      context->AddInitialMetadata(Generator::Key(), Generator::Value());
    }
  }
};

template <int length>
const std::string RandomBinaryMetadata<length>::kKey = "foo-bin";

template <int length>
const std::vector<std::string> RandomBinaryMetadata<length>::kValues =
    MakeVector(kPregenerateKeyCount, GenerateOneString);

template <int length>
const std::string RandomAsciiMetadata<length>::kKey = "foo";

template <int length>
const std::vector<std::string> RandomAsciiMetadata<length>::kValues =
    MakeVector(kPregenerateKeyCount, GenerateOneString);

}
}

#endif
