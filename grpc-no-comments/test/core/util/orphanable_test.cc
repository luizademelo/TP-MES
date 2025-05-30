
// Copyright 2017 gRPC authors.

#include "src/core/util/orphanable.h"

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class Foo : public Orphanable {
 public:
  Foo() : Foo(0) {}
  explicit Foo(int value) : value_(value) {}
  void Orphan() override { delete this; }
  int value() const { return value_; }

 private:
  int value_;
};

TEST(Orphanable, Basic) {
  Foo* foo = new Foo();
  foo->Orphan();
}

TEST(OrphanablePtr, Basic) {
  OrphanablePtr<Foo> foo(new Foo());
  EXPECT_EQ(0, foo->value());
}

TEST(MakeOrphanable, DefaultConstructor) {
  auto foo = MakeOrphanable<Foo>();
  EXPECT_EQ(0, foo->value());
}

TEST(MakeOrphanable, WithParameters) {
  auto foo = MakeOrphanable<Foo>(5);
  EXPECT_EQ(5, foo->value());
}

class Bar : public InternallyRefCounted<Bar> {
 public:
  Bar() : Bar(0) {}
  explicit Bar(int value) : value_(value) {}
  void Orphan() override { Unref(); }
  int value() const { return value_; }

  void StartWork() { self_ref_ = Ref(); }
  void FinishWork() { self_ref_.reset(); }

 private:
  int value_;
  RefCountedPtr<Bar> self_ref_;
};

TEST(OrphanablePtr, InternallyRefCounted) {
  auto bar = MakeOrphanable<Bar>();
  bar->StartWork();
  bar->FinishWork();
}

TEST(OrphanablePtr, InternallyRefCountedRefAsSubclass) {
  class Subclass : public Bar {
   public:
    void StartWork() { self_ref_ = RefAsSubclass<Subclass>(); }
    void FinishWork() { self_ref_.reset(); }

   private:
    RefCountedPtr<Subclass> self_ref_;
  };
  auto bar = MakeOrphanable<Subclass>();
  bar->StartWork();
  bar->FinishWork();
}

class Baz : public InternallyRefCounted<Baz> {
 public:
  Baz() : Baz(0) {}
  explicit Baz(int value) : InternallyRefCounted<Baz>("Baz"), value_(value) {}
  void Orphan() override { Unref(); }
  int value() const { return value_; }

  void StartWork() { self_ref_ = Ref(DEBUG_LOCATION, "work"); }
  void FinishWork() {

    self_ref_.release();
    Unref(DEBUG_LOCATION, "work");
  }

 private:
  int value_;
  RefCountedPtr<Baz> self_ref_;
};

TEST(OrphanablePtr, InternallyRefCountedWithTracing) {
  auto baz = MakeOrphanable<Baz>();
  baz->StartWork();
  baz->FinishWork();
}

class Qux : public InternallyRefCounted<Qux> {
 public:
  Qux() : Qux(0) {}
  explicit Qux(int value) : InternallyRefCounted<Qux>("Qux"), value_(value) {}
  ~Qux() override { self_ref_ = RefIfNonZero(DEBUG_LOCATION, "extra_work"); }
  void Orphan() override { Unref(); }
  int value() const { return value_; }

  void StartWork() { self_ref_ = RefIfNonZero(DEBUG_LOCATION, "work"); }
  void FinishWork() {

    self_ref_.release();
    Unref(DEBUG_LOCATION, "work");
  }

 private:
  int value_;
  RefCountedPtr<Qux> self_ref_;
};

TEST(OrphanablePtr, InternallyRefCountedIfNonZero) {
  auto qux = MakeOrphanable<Qux>();
  qux->StartWork();
  qux->FinishWork();
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
