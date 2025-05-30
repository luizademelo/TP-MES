// Copyright 2021 gRPC authors.

#include "src/core/util/table.h"

#include <optional>
#include <string>
#include <tuple>
#include <variant>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {

TEST(Table, InstantiateEmpty) { Table<>(); }

TEST(Table, NoOp) {
  Table<int, double, std::string> t;
  EXPECT_EQ(t.get<int>(), nullptr);
  EXPECT_EQ(t.get<double>(), nullptr);
  EXPECT_EQ(t.get<std::string>(), nullptr);
  EXPECT_EQ(t.get<0>(), nullptr);
  EXPECT_EQ(t.get<1>(), nullptr);
  EXPECT_EQ(t.get<2>(), nullptr);
}

TEST(Table, SetTheThings) {
  Table<int, double, std::string> t;
  t.set<int>(3);
  t.set<double>(2.9);
  t.set<std::string>("Hello world!");
  EXPECT_EQ(*t.get<int>(), 3);
  EXPECT_EQ(*t.get<double>(), 2.9);
  EXPECT_EQ(*t.get<std::string>(), "Hello world!");
  EXPECT_EQ(*t.get<0>(), 3);
  EXPECT_EQ(*t.get<1>(), 2.9);
  EXPECT_EQ(*t.get<2>(), "Hello world!");
}

TEST(Table, GetDefault) {
  Table<int, double, std::string> t;
  EXPECT_EQ(*t.get_or_create<std::string>(), "");
  EXPECT_EQ(*t.get_or_create<double>(), 0.0);
  EXPECT_EQ(*t.get_or_create<int>(), 0);
}

TEST(Table, GetDefaultIndexed) {
  Table<int, double, std::string> t;
  EXPECT_EQ(*t.get_or_create<2>(), "");
  EXPECT_EQ(*t.get_or_create<1>(), 0.0);
  EXPECT_EQ(*t.get_or_create<0>(), 0);
}

TEST(Table, Copy) {
  Table<int, std::string> t;
  t.set<std::string>("abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(*t.get<std::string>(), "abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(t.get<int>(), nullptr);
  Table<int, std::string> u(t);
  EXPECT_EQ(*u.get<std::string>(), "abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(*t.get<std::string>(), "abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(t.get<int>(), nullptr);
  EXPECT_EQ(u.get<int>(), nullptr);
  u.set<std::string>("hello");
  EXPECT_EQ(*u.get<1>(), "hello");
  EXPECT_EQ(*t.get<1>(), "abcdefghijklmnopqrstuvwxyz");
  t = u;
  EXPECT_EQ(*u.get<std::string>(), "hello");
  EXPECT_EQ(*t.get<std::string>(), "hello");
}

TEST(Table, Move) {
  Table<int, std::string> t;
  t.set<std::string>("abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(*t.get<std::string>(), "abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(t.get<int>(), nullptr);
  Table<int, std::string> u(std::move(t));
  EXPECT_NE(t.get<std::string>(), nullptr);
  EXPECT_EQ(*u.get<std::string>(), "abcdefghijklmnopqrstuvwxyz");
  EXPECT_EQ(t.get<int>(), nullptr);
  EXPECT_EQ(u.get<int>(), nullptr);
  u.set<std::string>("hello");
  EXPECT_EQ(*u.get<1>(), "hello");
  t = std::move(u);
  EXPECT_NE(u.get<std::string>(), nullptr);
  EXPECT_EQ(*t.get<std::string>(), "hello");
}

TEST(Table, SameTypes) {
  Table<std::string, std::string, std::string> t;

  EXPECT_EQ(t.get<0>(), nullptr);
  EXPECT_EQ(t.get<1>(), nullptr);
  EXPECT_EQ(t.get<2>(), nullptr);
  t.set<1>("Hello!");
  EXPECT_EQ(t.get<0>(), nullptr);
  EXPECT_EQ(*t.get<1>(), "Hello!");
  EXPECT_EQ(t.get<2>(), nullptr);
}

TEST(Table, ForEach) {
  Table<int, int, int> t;
  t.set<0>(1);
  t.set<1>(2);
  t.set<2>(3);
  int i = 1;
  t.ForEach([&i](int x) {
    EXPECT_EQ(x, i);
    i++;
  });
}

#if !defined(_MSC_VER)

template <typename T>
struct TableSizeTest : public ::testing::Test {};

using SizeTests = ::testing::Types<
    std::tuple<char>, std::tuple<char, char>, std::tuple<char, char, char>,
    std::tuple<int>, std::tuple<std::string>,
    std::tuple<int, int, int, int, int, int, int, int, int, int>>;

TYPED_TEST_SUITE(TableSizeTest, SizeTests);

template <typename... Ts>
int sizeof_tuple_of_optionals(std::tuple<Ts...>*) {
  return sizeof(std::tuple<std::optional<Ts>...>);
}

template <typename... Ts>
int sizeof_table(std::tuple<Ts...>*) {
  return sizeof(Table<Ts...>);
}

TYPED_TEST(TableSizeTest, SmallerThanTupleOfOptionals) {
  EXPECT_GE(sizeof_tuple_of_optionals(static_cast<TypeParam*>(nullptr)),
            sizeof_table(static_cast<TypeParam*>(nullptr)));
}
#endif

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
