
// Copyright 2015 gRPC authors.

#include "src/core/lib/channel/channel_args.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {

using ::grpc_event_engine::experimental::CreateEventEngine;
using ::grpc_event_engine::experimental::EventEngine;

TEST(ChannelArgsTest, Noop) { ChannelArgs(); }

TEST(ChannelArgsTest, SetGetRemove) {
  const grpc_arg_pointer_vtable malloc_vtable = {

      [](void* p) { return p; },

      [](void*) {},

      [](void* p1, void* p2) { return QsortCompare(p1, p2); },
  };
  void* ptr = gpr_malloc(42);

  ChannelArgs a;
  ChannelArgs b = a.Set("answer", 42);
  ChannelArgs c = b.Set("foo", "bar");
  ChannelArgs d = c.Set("ptr", ChannelArgs::Pointer(ptr, &malloc_vtable));
  ChannelArgs e = d.Set("alpha", "beta");
  ChannelArgs f = e.Remove("answer");
  EXPECT_EQ(a.Get("answer"), nullptr);
  EXPECT_EQ(*b.Get("answer"), ChannelArgs::Value(42));
  EXPECT_EQ(*c.Get("answer"), ChannelArgs::Value(42));
  EXPECT_EQ(c.GetInt("answer"), 42);
  EXPECT_EQ(c.GetString("answer"), std::nullopt);
  EXPECT_EQ(f.Get("answer"), nullptr);
  EXPECT_EQ(*c.Get("foo"), ChannelArgs::Value("bar"));
  EXPECT_EQ(c.GetString("foo"), "bar");
  EXPECT_EQ(c.GetString("answer"), std::nullopt);
  EXPECT_EQ(*d.Get("ptr"),
            ChannelArgs::Value(ChannelArgs::Pointer(ptr, &malloc_vtable)));
  EXPECT_EQ(*e.Get("alpha"), ChannelArgs::Value("beta"));
  gpr_free(ptr);
}

TEST(ChannelArgsTest, RemoveAllKeysWithPrefix) {
  ChannelArgs args;
  args = args.Set("foo", 1);
  args = args.Set("foo.bar", 2);
  args = args.Set("foo.baz", 3);
  args = args.Set("bar", 4);
  ChannelArgs modified = args.RemoveAllKeysWithPrefix("foo.");
  EXPECT_EQ(modified.GetInt("foo"), 1);
  EXPECT_EQ(modified.GetInt("foo.bar"), std::nullopt);
  EXPECT_EQ(modified.GetInt("foo.baz"), std::nullopt);
  EXPECT_EQ(modified.GetInt("bar"), 4);
}

TEST(ChannelArgsTest, StoreRefCountedPtr) {
  struct Test : public RefCounted<Test> {
    explicit Test(int n) : n(n) {}
    int n;
    static int ChannelArgsCompare(const Test* a, const Test* b) {
      return a->n - b->n;
    }
  };
  auto p = MakeRefCounted<Test>(123);

  ChannelArgs a;
  a = a.Set("test", p);
  EXPECT_EQ(a.GetPointer<Test>("test")->n, 123);
}

TEST(ChannelArgsTest, ObjectApi) {
  struct MyFancyObject : public RefCounted<MyFancyObject> {
    explicit MyFancyObject(int n) : n(n) {}
    static absl::string_view ChannelArgName() {
      return "grpc.internal.my-fancy-object";
    }
    int n;
    static int ChannelArgsCompare(const MyFancyObject* a,
                                  const MyFancyObject* b) {
      return a->n - b->n;
    }
  };
  auto p = MakeRefCounted<MyFancyObject>(42);
  ChannelArgs a;
  a = a.SetObject(std::move(p));
  EXPECT_EQ(a.GetObject<MyFancyObject>()->n, 42);
}

TEST(ChannelArgsTest, ToAndFromC) {
  const grpc_arg_pointer_vtable malloc_vtable = {

      [](void* p) { return p; },

      [](void*) {},

      [](void* p1, void* p2) { return QsortCompare(p1, p2); },
  };
  void* ptr = gpr_malloc(42);
  ChannelArgs a = ChannelArgs()
                      .Set("answer", 42)
                      .Set("foo", "bar")
                      .Set("ptr", ChannelArgs::Pointer(ptr, &malloc_vtable))
                      .Set("alpha", "beta");
  ChannelArgs b = ChannelArgs::FromC(a.ToC().get());
  EXPECT_EQ(a, b);
  gpr_free(ptr);
}

class ShareableObject : public std::enable_shared_from_this<ShareableObject> {
 public:
  explicit ShareableObject(int n) : n(n) {}
  int n;
  static int ChannelArgsCompare(const ShareableObject* a,
                                const ShareableObject* b) {
    return a->n - b->n;
  }
  static absl::string_view ChannelArgName() { return "grpc.test"; }
};

TEST(ChannelArgsTest, StoreAndRetrieveSharedPtr) {
  std::shared_ptr<ShareableObject> copied_obj;
  {
    ChannelArgs channel_args;
    auto shared_obj = std::make_shared<ShareableObject>(42);
    EXPECT_TRUE(shared_obj.unique());
    channel_args = channel_args.SetObject(shared_obj);
    EXPECT_FALSE(shared_obj.unique());
    copied_obj = channel_args.GetObjectRef<ShareableObject>();
    EXPECT_EQ(copied_obj->n, 42);

    EXPECT_EQ(3, copied_obj.use_count());
  }

  EXPECT_TRUE(copied_obj.unique());
  EXPECT_EQ(copied_obj->n, 42);
}

TEST(ChannelArgsTest, RetrieveRawPointerFromStoredSharedPtr) {
  ChannelArgs channel_args;
  auto shared_obj = std::make_shared<ShareableObject>(42);
  EXPECT_TRUE(shared_obj.unique());
  channel_args = channel_args.SetObject(shared_obj);
  EXPECT_FALSE(shared_obj.unique());
  ShareableObject* raw_obj = channel_args.GetObject<ShareableObject>();
  EXPECT_EQ(raw_obj->n, 42);

  EXPECT_EQ(2, shared_obj.use_count());
}

TEST(ChannelArgsTest, StoreSharedPtrEventEngine) {
  auto p = std::shared_ptr<EventEngine>(CreateEventEngine());
  ChannelArgs a;
  a = a.SetObject(p);
  Notification signal;
  bool triggered = false;
  a.GetObjectRef<EventEngine>()->Run([&triggered, &signal] {
    triggered = true;
    signal.Notify();
  });
  signal.WaitForNotification();
  ASSERT_TRUE(triggered);
}

TEST(ChannelArgsTest, GetNonOwningEventEngine) {
  auto p = std::shared_ptr<EventEngine>(CreateEventEngine());
  ASSERT_TRUE(p.unique());
  ChannelArgs a;
  a = a.SetObject(p);
  ASSERT_FALSE(p.unique());
  ASSERT_EQ(p.use_count(), 2);
  EventEngine* engine = a.GetObject<EventEngine>();
  (void)engine;

  ASSERT_EQ(p.use_count(), 2);
}

struct MutableValue : public RefCounted<MutableValue> {
  static constexpr absl::string_view ChannelArgName() {
    return "grpc.test.mutable_value";
  }
  static int ChannelArgsCompare(const MutableValue* a, const MutableValue* b) {
    return a->i - b->i;
  }
  int i = 42;
};

struct ConstValue : public RefCounted<ConstValue> {
  static constexpr absl::string_view ChannelArgName() {
    return "grpc.test.const_value";
  }
  static constexpr bool ChannelArgUseConstPtr() { return true; };
  static int ChannelArgsCompare(const ConstValue* a, const ConstValue* b) {
    return a->i - b->i;
  }
  int i = 42;
};

TEST(ChannelArgsTest, SetObjectRespectsMutabilityConstraints) {
  auto m = MakeRefCounted<MutableValue>();
  auto c = MakeRefCounted<const ConstValue>();
  auto args = ChannelArgs().SetObject(m).SetObject(c);
  RefCountedPtr<MutableValue> m1 = args.GetObjectRef<MutableValue>();
  RefCountedPtr<const ConstValue> c1 = args.GetObjectRef<ConstValue>();
  EXPECT_EQ(m1.get(), m.get());
  EXPECT_EQ(c1.get(), c.get());
}

}

TEST(GrpcChannelArgsTest, Create) {
  grpc_core::ExecCtx exec_ctx;
  grpc_arg to_add[2];
  grpc_channel_args* ch_args;

  to_add[0] =
      grpc_channel_arg_integer_create(const_cast<char*>("int_arg"), 123);
  to_add[1] = grpc_channel_arg_string_create(const_cast<char*>("str key"),
                                             const_cast<char*>("str value"));
  ch_args = grpc_channel_args_copy_and_add(nullptr, to_add, 2);

  CHECK_EQ(ch_args->num_args, 2);
  CHECK_EQ(strcmp(ch_args->args[0].key, to_add[0].key), 0);
  CHECK(ch_args->args[0].type == to_add[0].type);
  CHECK(ch_args->args[0].value.integer == to_add[0].value.integer);

  CHECK_EQ(strcmp(ch_args->args[1].key, to_add[1].key), 0);
  CHECK(ch_args->args[1].type == to_add[1].type);
  CHECK(strcmp(ch_args->args[1].value.string, to_add[1].value.string) == 0);

  grpc_channel_args_destroy(ch_args);
}

struct fake_class {
  int foo;
};

static void* fake_pointer_arg_copy(void* arg) {
  VLOG(2) << "fake_pointer_arg_copy";
  fake_class* fc = static_cast<fake_class*>(arg);
  fake_class* new_fc = static_cast<fake_class*>(gpr_malloc(sizeof(fake_class)));
  new_fc->foo = fc->foo;
  return new_fc;
}

static void fake_pointer_arg_destroy(void* arg) {
  VLOG(2) << "fake_pointer_arg_destroy";
  fake_class* fc = static_cast<fake_class*>(arg);
  gpr_free(fc);
}

static int fake_pointer_cmp(void* a, void* b) {
  return grpc_core::QsortCompare(a, b);
}

static const grpc_arg_pointer_vtable fake_pointer_arg_vtable = {
    fake_pointer_arg_copy, fake_pointer_arg_destroy, fake_pointer_cmp};

TEST(GrpcChannelArgsTest, ChannelCreateWithArgs) {
  grpc_arg client_a[3];

  client_a[0] =
      grpc_channel_arg_integer_create(const_cast<char*>("arg_int"), 0);
  client_a[1] = grpc_channel_arg_string_create(
      const_cast<char*>("arg_str"), const_cast<char*>("arg_str_val"));

  fake_class* fc = static_cast<fake_class*>(gpr_malloc(sizeof(fake_class)));
  fc->foo = 42;
  client_a[2] = grpc_channel_arg_pointer_create(
      const_cast<char*>("arg_pointer"), fc, &fake_pointer_arg_vtable);

  grpc_channel_args client_args = {GPR_ARRAY_SIZE(client_a), client_a};
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* c = grpc_channel_create("fake_target", creds, &client_args);
  grpc_channel_credentials_release(creds);

  gpr_free(fc);
  grpc_channel_destroy(c);
}

grpc_channel_args* mutate_channel_args(const char* target,
                                       grpc_channel_args* old_args,
                                       grpc_channel_stack_type ) {
  CHECK_NE(old_args, nullptr);
  CHECK_EQ(grpc_channel_args_find(old_args, "arg_int")->value.integer, 0);
  CHECK(strcmp(grpc_channel_args_find(old_args, "arg_str")->value.string,
               "arg_str_val") == 0);
  CHECK(grpc_channel_args_find(old_args, "arg_pointer")->value.pointer.vtable ==
        &fake_pointer_arg_vtable);

  if (strcmp(target, "no_op_mutator") == 0) {
    return old_args;
  }

  CHECK_EQ(strcmp(target, "minimal_stack_mutator"), 0);
  const char* args_to_remove[] = {"arg_int", "arg_str", "arg_pointer"};

  grpc_arg no_deadline_filter_arg = grpc_channel_arg_integer_create(
      const_cast<char*>(GRPC_ARG_MINIMAL_STACK), 1);
  grpc_channel_args* new_args = nullptr;
  new_args = grpc_channel_args_copy_and_add_and_remove(
      old_args, args_to_remove, GPR_ARRAY_SIZE(args_to_remove),
      &no_deadline_filter_arg, 1);
  grpc_channel_args_destroy(old_args);
  return new_args;
}

TEST(GrpcChannelArgsTest, TestServerCreateWithArgs) {
  grpc_arg server_a[3];

  server_a[0].type = GRPC_ARG_INTEGER;
  server_a[0].key = const_cast<char*>("arg_int");
  server_a[0].value.integer = 0;

  server_a[1].type = GRPC_ARG_STRING;
  server_a[1].key = const_cast<char*>("arg_str");
  server_a[1].value.string = const_cast<char*>("arg_str_val");

  fake_class* fc = static_cast<fake_class*>(gpr_malloc(sizeof(fake_class)));
  fc->foo = 42;
  server_a[2].type = GRPC_ARG_POINTER;
  server_a[2].key = const_cast<char*>("arg_pointer");
  server_a[2].value.pointer.vtable = &fake_pointer_arg_vtable;
  server_a[2].value.pointer.p = fc;

  grpc_channel_args server_args = {GPR_ARRAY_SIZE(server_a), server_a};
  grpc_server* s = grpc_server_create(&server_args, nullptr);

  gpr_free(fc);
  grpc_server_destroy(s);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
