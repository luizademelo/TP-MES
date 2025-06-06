// Copyright 2021 gRPC authors.

#include <stdlib.h>

#include <algorithm>
#include <functional>
#include <map>
#include <utility>

#include "fuzztest/fuzztest.h"
#include "src/core/util/avl.h"
#include "test/core/util/avl_fuzzer.pb.h"

bool squelch = true;
bool leak_check = true;

namespace grpc_core {

class Fuzzer {
 public:
  Fuzzer() { CheckEqual(); }
  ~Fuzzer() { CheckEqual(); }
  void Run(const avl_fuzzer::Action& action) {
    switch (action.action_case()) {
      case avl_fuzzer::Action::kSet:
        avl_ = avl_.Add(action.key(), action.set());
        map_[action.key()] = action.set();
        break;
      case avl_fuzzer::Action::kDel:
        avl_ = avl_.Remove(action.key());
        map_.erase(action.key());
        break;
      case avl_fuzzer::Action::kGet: {
        auto* p = avl_.Lookup(action.key());
        auto it = map_.find(action.key());
        if (it == map_.end() && p != nullptr) abort();
        if (it != map_.end() && p == nullptr) abort();
        if (it != map_.end() && it->second != *p) abort();
      } break;
      case avl_fuzzer::Action::ACTION_NOT_SET:
        break;
    }
  }

 private:
  void CheckEqual() {
    auto it = map_.begin();
    avl_.ForEach([&](int key, int value) {
      if (it == map_.end()) abort();
      if (it->first != key) abort();
      if (it->second != value) abort();
      ++it;
    });
    if (it != map_.end()) abort();
  }

  AVL<int, int> avl_;
  std::map<int, int> map_;
};

template <typename RepeatedField>
AVL<int, int> AvlFromProto(const RepeatedField& p) {
  AVL<int, int> a;
  for (const auto& kv : p) {
    a = a.Add(kv.key(), kv.value());
  }
  return a;
}

template <typename RepeatedField>
std::map<int, int> MapFromProto(const RepeatedField& p) {
  std::map<int, int> a;
  for (const auto& kv : p) {
    a[kv.key()] = kv.value();
  }
  return a;
}

void SameAsMap(const avl_fuzzer::Msg& msg) {
  Fuzzer fuzzer;
  for (const auto& action : msg.actions()) {
    Fuzzer().Run(action);
  }

  for (const auto& cmp : msg.compares()) {
    auto left_avl = AvlFromProto(cmp.left());
    auto left_map = MapFromProto(cmp.left());
    auto right_avl = AvlFromProto(cmp.right());
    auto right_map = MapFromProto(cmp.right());
    if ((left_avl == right_avl) != (left_map == right_map)) abort();
    if ((left_avl < right_avl) != (left_map < right_map)) abort();
  }
}
FUZZ_TEST(AvlFuzzer, SameAsMap);

}
