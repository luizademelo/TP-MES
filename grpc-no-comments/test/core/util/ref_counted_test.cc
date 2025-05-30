
// Copyright 2017 gRPC authors.

#include "src/core/util/ref_counted.h"

#include <memory>
#include <new>
#include <set>
#include <type_traits>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class Foo : public RefCounted<Foo> {
 public:
  Foo() {
    static_assert(std::has_virtual_destructor<Foo>::value,
                  "PolymorphicRefCount doesn't have a virtual dtor");
  }
};

TEST(RefCounted, Basic) {
  Foo* foo = new Foo();
  foo->Unref();
}

TEST(RefCounted, ExtraRef) {
  Foo* foo = new Foo();
  RefCountedPtr<Foo> foop = foo->Ref();
  foop.release();
  foo->Unref();
  foo->Unref();
}

TEST(RefCounted, Const) {
  const Foo* foo = new Foo();
  RefCountedPtr<const Foo> foop = foo->Ref();
  foop.release();
  foop = foo->RefIfNonZero();
  foop.release();
  foo->Unref();
  foo->Unref();
  foo->Unref();
}

TEST(RefCounted, SubclassOfRefCountedType) {
  class Bar : public Foo {};
  Bar* bar = new Bar();
  RefCountedPtr<Bar> barp = bar->RefAsSubclass<Bar>();
  barp.release();
  barp = bar->RefAsSubclass<Bar>(DEBUG_LOCATION, "whee");
  barp.release();
  bar->Unref();
  bar->Unref();
  bar->Unref();
}

class Value : public RefCounted<Value, PolymorphicRefCount, UnrefNoDelete> {
 public:
  Value(int value, std::set<std::unique_ptr<Value>>* registry) : value_(value) {
    registry->emplace(this);
  }

  int value() const { return value_; }

 private:
  int value_;
};

void GarbageCollectRegistry(std::set<std::unique_ptr<Value>>* registry) {
  for (auto it = registry->begin(); it != registry->end();) {
    RefCountedPtr<Value> v = (*it)->RefIfNonZero();

    if (v != nullptr) {

      ++it;
    } else {

      it = registry->erase(it);
    }
  }
}

TEST(RefCounted, NoDeleteUponUnref) {
  std::set<std::unique_ptr<Value>> registry;

  auto v1 = MakeRefCounted<Value>(1, &registry);
  auto v2 = MakeRefCounted<Value>(2, &registry);
  EXPECT_THAT(registry,
              ::testing::UnorderedElementsAre(
                  ::testing::Pointee(::testing::Property(&Value::value, 1)),
                  ::testing::Pointee(::testing::Property(&Value::value, 2))));

  GarbageCollectRegistry(&registry);
  EXPECT_THAT(registry,
              ::testing::UnorderedElementsAre(
                  ::testing::Pointee(::testing::Property(&Value::value, 1)),
                  ::testing::Pointee(::testing::Property(&Value::value, 2))));

  v2.reset();
  GarbageCollectRegistry(&registry);
  EXPECT_THAT(registry, ::testing::UnorderedElementsAre(::testing::Pointee(
                            ::testing::Property(&Value::value, 1))));

  v1.reset();
  GarbageCollectRegistry(&registry);
  EXPECT_THAT(registry, ::testing::UnorderedElementsAre());
}

class ValueInExternalAllocation
    : public RefCounted<ValueInExternalAllocation, PolymorphicRefCount,
                        UnrefCallDtor> {
 public:
  explicit ValueInExternalAllocation(int value) : value_(value) {}

  int value() const { return value_; }

 private:
  int value_;
};

TEST(RefCounted, CallDtorUponUnref) {
  alignas(ValueInExternalAllocation) char
      storage[sizeof(ValueInExternalAllocation)];
  RefCountedPtr<ValueInExternalAllocation> value(
      new (&storage) ValueInExternalAllocation(5));
  EXPECT_EQ(value->value(), 5);
}

class FooNonPolymorphic
    : public RefCounted<FooNonPolymorphic, NonPolymorphicRefCount> {
 public:
  FooNonPolymorphic() {
    static_assert(!std::has_virtual_destructor<FooNonPolymorphic>::value,
                  "NonPolymorphicRefCount has a virtual dtor");
  }
};

TEST(RefCountedNonPolymorphic, Basic) {
  FooNonPolymorphic* foo = new FooNonPolymorphic();
  foo->Unref();
}

TEST(RefCountedNonPolymorphic, ExtraRef) {
  FooNonPolymorphic* foo = new FooNonPolymorphic();
  RefCountedPtr<FooNonPolymorphic> foop = foo->Ref();
  foop.release();
  foo->Unref();
  foo->Unref();
}

class FooWithTracing : public RefCounted<FooWithTracing> {
 public:
  FooWithTracing() : RefCounted("Foo") {}
};

TEST(RefCountedWithTracing, Basic) {
  FooWithTracing* foo = new FooWithTracing();
  RefCountedPtr<FooWithTracing> foop = foo->Ref(DEBUG_LOCATION, "extra_ref");
  foop.release();
  foo->Unref(DEBUG_LOCATION, "extra_ref");

  foop = foo->Ref();
  foop.release();
  foo->Unref();
  foo->Unref(DEBUG_LOCATION, "original_ref");
}

class FooNonPolymorphicWithTracing
    : public RefCounted<FooNonPolymorphicWithTracing, NonPolymorphicRefCount> {
 public:
  FooNonPolymorphicWithTracing() : RefCounted("FooNonPolymorphicWithTracing") {}
};

TEST(RefCountedNonPolymorphicWithTracing, Basic) {
  FooNonPolymorphicWithTracing* foo = new FooNonPolymorphicWithTracing();
  RefCountedPtr<FooNonPolymorphicWithTracing> foop =
      foo->Ref(DEBUG_LOCATION, "extra_ref");
  foop.release();
  foo->Unref(DEBUG_LOCATION, "extra_ref");

  foop = foo->Ref();
  foop.release();
  foo->Unref();
  foo->Unref(DEBUG_LOCATION, "original_ref");
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
