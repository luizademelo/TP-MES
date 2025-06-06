// Copyright 2022 gRPC authors.

#include "src/core/util/unique_type_name.h"

#include <iosfwd>
#include <map>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::Pair;
using testing::UnorderedElementsAre;

namespace grpc_core {

std::ostream& operator<<(std::ostream& os, const UniqueTypeName& name) {
  return os << absl::StrFormat("%s (%p)", name.name(), name.name().data());
}

namespace {

class Interface {
 public:
  virtual ~Interface() = default;
  virtual UniqueTypeName type() const = 0;
};

class Foo : public Interface {
 public:
  UniqueTypeName type() const override {
    static UniqueTypeName::Factory kFactory("Foo");
    return kFactory.Create();
  }
};

class Bar : public Interface {
 public:
  UniqueTypeName type() const override {
    static UniqueTypeName::Factory kFactory("Bar");
    return kFactory.Create();
  }
};

class Foo2 : public Interface {
 public:
  UniqueTypeName type() const override {
    static UniqueTypeName::Factory kFactory("Foo");
    return kFactory.Create();
  }
};

TEST(UniqueTypeNameTest, MultipleInstancesShareName) {
  Foo foo1;
  Foo foo2;
  EXPECT_EQ(foo1.type(), foo2.type());
  EXPECT_EQ(0, foo1.type().Compare(foo2.type()));
}

TEST(UniqueTypeNameTest, DifferentImplsDoNotShareName) {
  Foo foo;
  Bar bar;
  EXPECT_NE(foo.type(), bar.type());
  EXPECT_NE(0, foo.type().Compare(bar.type()));
}

TEST(UniqueTypeNameTest, MultipleInstancesOfSameStringAreNotEqual) {
  Foo foo1;
  Foo2 foo2;
  EXPECT_NE(foo1.type(), foo2.type());
  EXPECT_NE(0, foo1.type().Compare(foo2.type()));
}

TEST(UniqueTypeNameTest, CanUseAsMapKey) {
  Foo foo;
  Bar bar;
  std::map<UniqueTypeName, int> m;
  m[foo.type()] = 1;
  m[bar.type()] = 2;
  EXPECT_THAT(m,
              ::testing::UnorderedElementsAre(::testing::Pair(foo.type(), 1),
                                              ::testing::Pair(bar.type(), 2)));
}

struct Filter1 {
  static absl::string_view TypeName() { return "Filter1"; }
};

struct Filter2 {
  static absl::string_view TypeName() { return "Filter2"; }
};

TEST(UniqueTypeNameTest, UniqueTypeNameFor) {
  EXPECT_EQ(UniqueTypeNameFor<Filter1>(), UniqueTypeNameFor<Filter1>());
  EXPECT_NE(UniqueTypeNameFor<Filter1>(), UniqueTypeNameFor<Filter2>());
}

TEST(UniqueTypeNameTest, UniqueTypeNameHere) {
  auto name1 = GRPC_UNIQUE_TYPE_NAME_HERE("name");
  auto name2 = GRPC_UNIQUE_TYPE_NAME_HERE("name");
  EXPECT_EQ(name1.name(), name2.name());
  EXPECT_NE(name1, name2);
}

TEST(UniqueTypenameTest, Stringify) {
  auto name = GRPC_UNIQUE_TYPE_NAME_HERE("bob");
  EXPECT_EQ("bob", absl::StrFormat("%v", name));
}

TEST(UniqueTypeNameTest, Hash) {
  auto name1 = GRPC_UNIQUE_TYPE_NAME_HERE("name");
  auto name2 = GRPC_UNIQUE_TYPE_NAME_HERE("name");
  auto name3 = GRPC_UNIQUE_TYPE_NAME_HERE("other");
  absl::flat_hash_map<UniqueTypeName, int> m;
  m[name1] = 1;
  m[name2] = 2;
  m[name3] = 3;
  EXPECT_THAT(
      m, UnorderedElementsAre(Pair(name1, 1), Pair(name2, 2), Pair(name3, 3)));
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
