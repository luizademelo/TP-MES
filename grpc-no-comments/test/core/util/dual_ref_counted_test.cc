
// Copyright 2020 gRPC authors.

#include "src/core/util/dual_ref_counted.h"

#include <memory>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/util/manual_constructor.h"
#include "src/core/util/ref_counted.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class Foo : public DualRefCounted<Foo> {
 public:
  Foo() = default;
  ~Foo() override { CHECK(shutting_down_); }

  void Orphaned() override { shutting_down_ = true; }

 private:
  bool shutting_down_ = false;
};

TEST(DualRefCounted, Basic) {
  Foo* foo = new Foo();
  foo->Unref();
}

TEST(DualRefCounted, ExtraRef) {
  Foo* foo = new Foo();
  foo->Ref().release();
  foo->Unref();
  foo->Unref();
}

TEST(DualRefCounted, ExtraWeakRef) {
  Foo* foo = new Foo();
  foo->WeakRef().release();
  foo->Unref();
  foo->WeakUnref();
}

TEST(DualRefCounted, RefIfNonZero) {
  Foo* foo = new Foo();
  foo->WeakRef().release();
  {
    RefCountedPtr<Foo> foop = foo->RefIfNonZero();
    EXPECT_NE(foop.get(), nullptr);
  }
  foo->Unref();
  {
    RefCountedPtr<Foo> foop = foo->RefIfNonZero();
    EXPECT_EQ(foop.get(), nullptr);
  }
  foo->WeakUnref();
}

TEST(DualRefCounted, WeakRefIfNonZero) {
  Foo* foo = new Foo();
  foo->WeakRef().release();
  {
    WeakRefCountedPtr<Foo> foop = foo->WeakRefIfNonZero();
    EXPECT_NE(foop.get(), nullptr);
  }
  foo->Unref();
  {
    WeakRefCountedPtr<Foo> foop = foo->WeakRefIfNonZero();
    EXPECT_NE(foop.get(), nullptr);
  }
  foo->WeakUnref();
}

TEST(DualRefCounted, RefAndWeakRefAsSubclass) {
  class Bar : public Foo {};
  Foo* foo = new Bar();
  RefCountedPtr<Bar> barp = foo->RefAsSubclass<Bar>();
  barp.release();
  barp = foo->RefAsSubclass<Bar>(DEBUG_LOCATION, "test");
  barp.release();
  WeakRefCountedPtr<Bar> weak_barp = foo->WeakRefAsSubclass<Bar>();
  weak_barp.release();
  weak_barp = foo->WeakRefAsSubclass<Bar>(DEBUG_LOCATION, "test");
  weak_barp.release();
  foo->WeakUnref();
  foo->WeakUnref();
  foo->Unref();
  foo->Unref();
  foo->Unref();
}

class FooWithTracing : public DualRefCounted<FooWithTracing> {
 public:
  FooWithTracing() : DualRefCounted("FooWithTracing") {}
  ~FooWithTracing() override { CHECK(shutting_down_); }

  void Orphaned() override { shutting_down_ = true; }

 private:
  bool shutting_down_ = false;
};

TEST(DualRefCountedWithTracing, Basic) {
  FooWithTracing* foo = new FooWithTracing();
  foo->Ref(DEBUG_LOCATION, "extra_ref").release();
  foo->Unref(DEBUG_LOCATION, "extra_ref");
  foo->WeakRef(DEBUG_LOCATION, "extra_ref").release();
  foo->WeakUnref(DEBUG_LOCATION, "extra_ref");

  foo->Ref().release();
  foo->Unref();
  foo->WeakRef().release();
  foo->WeakUnref();
  foo->Unref(DEBUG_LOCATION, "original_ref");
}

class FooWithNoDelete final
    : public DualRefCounted<FooWithNoDelete, NonPolymorphicRefCount,
                            UnrefCallDtor> {
 public:
  FooWithNoDelete(bool* orphaned_called, bool* destructor_called)
      : DualRefCounted<FooWithNoDelete, NonPolymorphicRefCount, UnrefCallDtor>(
            "FooWithNoDelete"),
        orphaned_called_(orphaned_called),
        destructor_called_(destructor_called) {}
  ~FooWithNoDelete() { *destructor_called_ = true; }

  void Orphaned() override { *orphaned_called_ = true; }

 private:
  bool* const orphaned_called_;
  bool* const destructor_called_;
};

TEST(DualRefCountedWithNoDelete, Basic) {
  ManualConstructor<FooWithNoDelete> foo;
  bool destructor_called = false;
  bool orphaned_called = false;
  foo.Init(&orphaned_called, &destructor_called);
  EXPECT_FALSE(orphaned_called);
  EXPECT_FALSE(destructor_called);
  foo->WeakRef().release();
  EXPECT_FALSE(orphaned_called);
  EXPECT_FALSE(destructor_called);
  foo->Unref();
  EXPECT_TRUE(orphaned_called);
  EXPECT_FALSE(destructor_called);
  foo->WeakUnref();
  EXPECT_TRUE(orphaned_called);
  EXPECT_TRUE(destructor_called);
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
