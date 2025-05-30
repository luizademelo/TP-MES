
// Copyright 2024 gRPC authors.

#include "src/core/util/lru_cache.h"

#include "absl/log/check.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace grpc_core {

TEST(LruCache, Basic) {
  std::vector<int> created_list;
  auto create = [&](const std::string& key) {
    int value;
    CHECK(absl::SimpleAtoi(key, &value));
    created_list.push_back(value);
    return value;
  };

  LruCache<std::string, int> cache(5);

  const std::array<int, 5> kOrder = {3, 1, 2, 0, 4};
  for (int i : kOrder) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(std::nullopt, cache.Get(key));
    EXPECT_EQ(i, cache.GetOrInsert(key, create));
    EXPECT_EQ(i, cache.Get(key));
  }
  EXPECT_THAT(created_list, ::testing::ElementsAreArray(kOrder));
  created_list.clear();

  for (int i : kOrder) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(i, cache.GetOrInsert(key, create));
  }
  EXPECT_THAT(created_list, ::testing::ElementsAre());

  const std::array<int, 5> kOrder2 = {7, 6, 8, 5, 9};
  for (size_t i = 0; i < kOrder2.size(); ++i) {
    int value2 = kOrder2[i];
    std::string key2 = absl::StrCat(value2);
    EXPECT_EQ(std::nullopt, cache.Get(key2));
    EXPECT_EQ(value2, cache.GetOrInsert(key2, create));
    EXPECT_EQ(value2, cache.Get(key2));
    int value1 = kOrder[i];
    std::string key1 = absl::StrCat(value1);
    EXPECT_EQ(std::nullopt, cache.Get(key1));
  }
  EXPECT_THAT(created_list, ::testing::ElementsAreArray(kOrder2));
}

TEST(LruCache, SetMaxSize) {
  auto create = [&](const std::string& key) {
    int value;
    CHECK(absl::SimpleAtoi(key, &value));
    return value;
  };

  LruCache<std::string, int> cache(10);

  for (int i = 1; i <= 10; ++i) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(std::nullopt, cache.Get(key));
    EXPECT_EQ(i, cache.GetOrInsert(key, create));
    EXPECT_EQ(i, cache.Get(key));
  }

  cache.SetMaxSize(15);
  for (int i = 1; i <= 10; ++i) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(i, cache.Get(key));
  }

  cache.SetMaxSize(6);
  for (int i = 1; i <= 4; ++i) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(std::nullopt, cache.Get(key)) << i;
  }
  for (int i = 5; i <= 10; ++i) {
    std::string key = absl::StrCat(i);
    EXPECT_EQ(i, cache.Get(key));
  }
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
