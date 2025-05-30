
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_ARGS_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_ARGS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/meta/type_traits.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/avl.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/ref_counted_string.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

#define GRPC_INTERNAL_ARG_EVENT_ENGINE "grpc.internal.event_engine"

namespace grpc_core {

template <typename T, typename Ignored = void >
struct ChannelArgTypeTraits;

namespace channel_args_detail {
inline int PointerCompare(void* a_ptr, const grpc_arg_pointer_vtable* a_vtable,
                          void* b_ptr,
                          const grpc_arg_pointer_vtable* b_vtable) {
  int c = QsortCompare(a_ptr, b_ptr);
  if (c == 0) return 0;
  c = QsortCompare(a_vtable, b_vtable);
  if (c != 0) return c;
  return a_vtable->cmp(a_ptr, b_ptr);
}

template <typename T>
using RefType = absl::remove_cvref_t<decltype(*std::declval<T>().Ref())>;

template <typename T, typename Ignored = void >
struct IsRawPointerTagged {
  static constexpr bool kValue = false;
};
template <typename T>
struct IsRawPointerTagged<T,
                          absl::void_t<typename T::RawPointerChannelArgTag>> {
  static constexpr bool kValue = true;
};

template <typename T>
struct SupportedSharedPtrType
    : std::integral_constant<
          bool, std::is_base_of<std::enable_shared_from_this<T>, T>::value> {};
template <>
struct SupportedSharedPtrType<grpc_event_engine::experimental::EventEngine>
    : std::true_type {};

template <typename T>
struct is_shared_ptr : std::false_type {};
template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

template <typename T, typename = void>
struct has_channel_args_compare : std::false_type {};
template <typename T>
struct has_channel_args_compare<
    T, absl::void_t<decltype(T::ChannelArgsCompare(std::declval<const T*>(),
                                                   std::declval<const T*>()))>>
    : std::true_type {};
}

template <typename T>
struct ChannelArgTypeTraits<
    T, absl::enable_if_t<
           !channel_args_detail::IsRawPointerTagged<T>::kValue &&
               (std::is_base_of<RefCounted<channel_args_detail::RefType<T>>,
                                channel_args_detail::RefType<T>>::value ||
                std::is_base_of<RefCounted<channel_args_detail::RefType<T>,
                                           NonPolymorphicRefCount>,
                                channel_args_detail::RefType<T>>::value ||
                std::is_base_of<DualRefCounted<channel_args_detail::RefType<T>>,
                                channel_args_detail::RefType<T>>::value),
           void>> {
  static const grpc_arg_pointer_vtable* VTable() {
    static const grpc_arg_pointer_vtable tbl = {

        [](void* p) -> void* {
          return p == nullptr ? nullptr
                              : static_cast<T*>(p)
                                    ->Ref(DEBUG_LOCATION, "ChannelArgs copy")
                                    .release();
        },

        [](void* p) {
          if (p != nullptr) {
            static_cast<T*>(p)->Unref(DEBUG_LOCATION, "ChannelArgs destroy");
          }
        },

        [](void* p1, void* p2) {
          return T::ChannelArgsCompare(static_cast<const T*>(p1),
                                       static_cast<const T*>(p2));
        },
    };
    return &tbl;
  };
};

template <typename T>
struct ChannelArgTypeTraits<
    T, absl::enable_if_t<channel_args_detail::is_shared_ptr<T>::value, void>> {
  static void* TakeUnownedPointer(T* p) { return p; }
  static const grpc_arg_pointer_vtable* VTable() {
    static const grpc_arg_pointer_vtable tbl = {

        [](void* p) -> void* { return new T(*static_cast<T*>(p)); },

        [](void* p) { delete static_cast<T*>(p); },

        [](void* p1, void* p2) {
          if constexpr (channel_args_detail::has_channel_args_compare<
                            typename T::element_type>::value) {
            return T::element_type::ChannelArgsCompare(
                static_cast<const T*>(p1)->get(),
                static_cast<const T*>(p2)->get());
          } else {
            return QsortCompare(static_cast<const T*>(p1)->get(),
                                static_cast<const T*>(p2)->get());
          }
        },
    };
    return &tbl;
  };
};

template <typename T>
struct ChannelArgTypeTraits<T,
                            absl::void_t<typename T::RawPointerChannelArgTag>> {
  static void* TakeUnownedPointer(T* p) { return p; }
  static const grpc_arg_pointer_vtable* VTable() {
    static const grpc_arg_pointer_vtable tbl = {

        [](void* p) -> void* { return p; },

        [](void*) {},

        [](void* p1, void* p2) { return QsortCompare(p1, p2); },
    };
    return &tbl;
  };
};

template <typename T, typename SfinaeVoid = void>
struct ChannelArgPointerShouldBeConst {
  static constexpr bool kValue = false;
};

template <typename T>
struct ChannelArgPointerShouldBeConst<
    T, absl::void_t<decltype(T::ChannelArgUseConstPtr())>> {
  static constexpr bool kValue = T::ChannelArgUseConstPtr();
};

template <typename T, typename Ignored = void >
struct GetObjectImpl;

template <typename T>
struct GetObjectImpl<
    T,
    absl::enable_if_t<!ChannelArgPointerShouldBeConst<T>::kValue &&
                          channel_args_detail::SupportedSharedPtrType<T>::value,
                      void>> {
  using Result = T*;
  using ReffedResult = std::shared_ptr<T>;
  using StoredType = std::shared_ptr<T>*;
  static Result Get(StoredType p) {
    if (p == nullptr) return nullptr;
    return p->get();
  };
  static ReffedResult GetReffed(StoredType p) {
    if (p == nullptr) return nullptr;
    return ReffedResult(*p);
  };
  static ReffedResult GetReffed(StoredType p,
                                const DebugLocation& ,
                                const char* ) {
    return GetReffed(*p);
  };
};

template <typename T>
struct GetObjectImpl<
    T, absl::enable_if_t<
           !ChannelArgPointerShouldBeConst<T>::kValue &&
               !channel_args_detail::SupportedSharedPtrType<T>::value,
           void>> {
  using Result = T*;
  using ReffedResult = RefCountedPtr<T>;
  using StoredType = Result;
  static Result Get(StoredType p) { return p; };
  static ReffedResult GetReffed(StoredType p) {
    if (p == nullptr) return nullptr;
    return p->template RefAsSubclass<T>();
  };
  static ReffedResult GetReffed(StoredType p, const DebugLocation& location,
                                const char* reason) {
    if (p == nullptr) return nullptr;
    return p->template RefAsSubclass<T>(location, reason);
  };
};

template <typename T>
struct GetObjectImpl<
    T, absl::enable_if_t<
           ChannelArgPointerShouldBeConst<T>::kValue &&
               !channel_args_detail::SupportedSharedPtrType<T>::value,
           void>> {
  using Result = const T*;
  using ReffedResult = RefCountedPtr<const T>;
  using StoredType = Result;
  static Result Get(StoredType p) { return p; };
  static ReffedResult GetReffed(StoredType p) {
    if (p == nullptr) return nullptr;
    return p->Ref();
  };
  static ReffedResult GetReffed(StoredType p, const DebugLocation& location,
                                const char* reason) {
    if (p == nullptr) return nullptr;
    return p->Ref(location, reason);
  };
};

template <typename T>
struct ChannelArgNameTraits {
  static absl::string_view ChannelArgName() { return T::ChannelArgName(); }
};
template <typename T>
struct ChannelArgNameTraits<std::shared_ptr<T>> {
  static absl::string_view ChannelArgName() { return T::ChannelArgName(); }
};

template <>
struct ChannelArgNameTraits<grpc_event_engine::experimental::EventEngine> {
  static absl::string_view ChannelArgName() {
    return GRPC_INTERNAL_ARG_EVENT_ENGINE;
  }
};

class ChannelArgs {
 public:
  class Pointer {
   public:
    Pointer(void* p, const grpc_arg_pointer_vtable* vtable);
    ~Pointer() { vtable_->destroy(p_); }

    Pointer(const Pointer& other);
    Pointer& operator=(Pointer other) {
      std::swap(p_, other.p_);
      std::swap(vtable_, other.vtable_);
      return *this;
    }
    Pointer(Pointer&& other) noexcept;
    Pointer& operator=(Pointer&& other) noexcept {
      std::swap(p_, other.p_);
      std::swap(vtable_, other.vtable_);
      return *this;
    }

    friend int QsortCompare(const Pointer& a, const Pointer& b) {
      return channel_args_detail::PointerCompare(a.p_, a.vtable_, b.p_,
                                                 b.vtable_);
    }

    bool operator==(const Pointer& rhs) const {
      return QsortCompare(*this, rhs) == 0;
    }
    bool operator<(const Pointer& rhs) const {
      return QsortCompare(*this, rhs) < 0;
    }
    bool operator!=(const Pointer& rhs) const {
      return QsortCompare(*this, rhs) != 0;
    }

    void* c_pointer() const { return p_; }
    const grpc_arg_pointer_vtable* c_vtable() const { return vtable_; }

   private:
    static const grpc_arg_pointer_vtable* EmptyVTable();

    void* p_;
    const grpc_arg_pointer_vtable* vtable_;
  };

  template <typename T>
  static Pointer UnownedPointer(T* p) {
    static const grpc_arg_pointer_vtable vtable = {
        [](void* p) -> void* { return p; },
        [](void*) {},
        [](void* p, void* q) { return QsortCompare(p, q); },
    };
    return Pointer(p, &vtable);
  }

  class Value {
   public:
    explicit Value(int n)
        : rep_(reinterpret_cast<void*>(static_cast<intptr_t>(n)),
               &int_vtable_) {}
    explicit Value(std::string s)
        : rep_(RefCountedString::Make(s).release(), &string_vtable_) {}
    explicit Value(Pointer p) : rep_(std::move(p)) {}

    std::optional<int> GetIfInt() const {
      if (rep_.c_vtable() != &int_vtable_) return std::nullopt;
      return reinterpret_cast<intptr_t>(rep_.c_pointer());
    }
    RefCountedPtr<RefCountedString> GetIfString() const {
      if (rep_.c_vtable() != &string_vtable_) return nullptr;
      return static_cast<RefCountedString*>(rep_.c_pointer())->Ref();
    }
    const Pointer* GetIfPointer() const {
      if (rep_.c_vtable() == &int_vtable_) return nullptr;
      if (rep_.c_vtable() == &string_vtable_) return nullptr;
      return &rep_;
    }

    absl::string_view ToString(std::list<std::string>& backing) const;

    grpc_arg MakeCArg(const char* name) const;

    bool operator<(const Value& rhs) const { return rep_ < rhs.rep_; }
    bool operator==(const Value& rhs) const { return rep_ == rhs.rep_; }
    bool operator!=(const Value& rhs) const { return !this->operator==(rhs); }
    bool operator==(absl::string_view rhs) const {
      auto str = GetIfString();
      if (str == nullptr) return false;
      return str->as_string_view() == rhs;
    }

   private:
    static const grpc_arg_pointer_vtable int_vtable_;
    static const grpc_arg_pointer_vtable string_vtable_;

    Pointer rep_;
  };

  struct ChannelArgsDeleter {
    void operator()(const grpc_channel_args* p) const;
  };
  using CPtr =
      std::unique_ptr<const grpc_channel_args, ChannelArgs::ChannelArgsDeleter>;

  ChannelArgs();
  ~ChannelArgs();
  ChannelArgs(const ChannelArgs&);
  ChannelArgs& operator=(const ChannelArgs&);
  ChannelArgs(ChannelArgs&&) noexcept;
  ChannelArgs& operator=(ChannelArgs&&) noexcept;

  static ChannelArgs FromC(const grpc_channel_args* args);
  static ChannelArgs FromC(const grpc_channel_args& args) {
    return FromC(&args);
  }

  CPtr ToC() const;

  GRPC_MUST_USE_RESULT ChannelArgs UnionWith(ChannelArgs other) const;

  GRPC_MUST_USE_RESULT ChannelArgs
  FuzzingReferenceUnionWith(ChannelArgs other) const;

  const Value* Get(absl::string_view name) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name,
                                       Pointer value) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name, int value) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name,
                                       absl::string_view value) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name,
                                       std::string value) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name,
                                       const char* value) const;
  GRPC_MUST_USE_RESULT ChannelArgs Set(grpc_arg arg) const;
  template <typename T>
  GRPC_MUST_USE_RESULT absl::enable_if_t<
      std::is_same<const grpc_arg_pointer_vtable*,
                   decltype(ChannelArgTypeTraits<T>::VTable())>::value,
      ChannelArgs>
  Set(absl::string_view name, T* value) const {
    return Set(name, Pointer(ChannelArgTypeTraits<T>::TakeUnownedPointer(value),
                             ChannelArgTypeTraits<T>::VTable()));
  }
  template <typename T>
  GRPC_MUST_USE_RESULT auto Set(absl::string_view name,
                                RefCountedPtr<T> value) const
      -> absl::enable_if_t<
          !ChannelArgPointerShouldBeConst<T>::kValue &&
              std::is_same<const grpc_arg_pointer_vtable*,
                           decltype(ChannelArgTypeTraits<
                                    absl::remove_cvref_t<T>>::VTable())>::value,
          ChannelArgs> {
    return Set(
        name, Pointer(value.release(),
                      ChannelArgTypeTraits<absl::remove_cvref_t<T>>::VTable()));
  }
  template <typename T>
  GRPC_MUST_USE_RESULT auto Set(absl::string_view name,
                                RefCountedPtr<const T> value) const
      -> absl::enable_if_t<
          ChannelArgPointerShouldBeConst<T>::kValue &&
              std::is_same<const grpc_arg_pointer_vtable*,
                           decltype(ChannelArgTypeTraits<
                                    absl::remove_cvref_t<T>>::VTable())>::value,
          ChannelArgs> {
    return Set(
        name, Pointer(const_cast<T*>(value.release()),
                      ChannelArgTypeTraits<absl::remove_cvref_t<T>>::VTable()));
  }
  template <typename T>
  GRPC_MUST_USE_RESULT absl::enable_if_t<
      std::is_same<
          const grpc_arg_pointer_vtable*,
          decltype(ChannelArgTypeTraits<std::shared_ptr<T>>::VTable())>::value,
      ChannelArgs>
  Set(absl::string_view name, std::shared_ptr<T> value) const {
    static_assert(channel_args_detail::SupportedSharedPtrType<T>::value,
                  "Type T must extend std::enable_shared_from_this to be added "
                  "into ChannelArgs as a shared_ptr<T>");
    auto* store_value = new std::shared_ptr<T>(value);
    return Set(
        name,
        Pointer(ChannelArgTypeTraits<std::shared_ptr<T>>::TakeUnownedPointer(
                    store_value),
                ChannelArgTypeTraits<std::shared_ptr<T>>::VTable()));
  }
  template <typename T>
  GRPC_MUST_USE_RESULT ChannelArgs SetIfUnset(absl::string_view name,
                                              T value) const {
    if (Contains(name)) return *this;
    return Set(name, std::move(value));
  }
  GRPC_MUST_USE_RESULT ChannelArgs Remove(absl::string_view name) const;
  bool Contains(absl::string_view name) const;

  GRPC_MUST_USE_RESULT ChannelArgs
  RemoveAllKeysWithPrefix(absl::string_view prefix) const;

  template <typename T>
  bool ContainsObject() const {
    return Get(ChannelArgNameTraits<T>::ChannelArgName()) != nullptr;
  }

  std::optional<int> GetInt(absl::string_view name) const;
  std::optional<absl::string_view> GetString(absl::string_view name) const;
  std::optional<std::string> GetOwnedString(absl::string_view name) const;

  void* GetVoidPointer(absl::string_view name) const;
  template <typename T>
  typename GetObjectImpl<T>::StoredType GetPointer(
      absl::string_view name) const {
    return static_cast<typename GetObjectImpl<T>::StoredType>(
        GetVoidPointer(name));
  }
  std::optional<Duration> GetDurationFromIntMillis(
      absl::string_view name) const;
  std::optional<bool> GetBool(absl::string_view name) const;

  template <typename T>
  GRPC_MUST_USE_RESULT ChannelArgs SetObject(T* p) const {
    return Set(T::ChannelArgName(), p);
  }
  template <typename T>
  GRPC_MUST_USE_RESULT ChannelArgs SetObject(RefCountedPtr<T> p) const {
    return Set(T::ChannelArgName(), std::move(p));
  }
  template <typename T>
  GRPC_MUST_USE_RESULT ChannelArgs SetObject(std::shared_ptr<T> p) const {
    return Set(ChannelArgNameTraits<T>::ChannelArgName(), std::move(p));
  }
  template <typename T>
  typename GetObjectImpl<T>::Result GetObject() const {
    return GetObjectImpl<T>::Get(
        GetPointer<T>(ChannelArgNameTraits<T>::ChannelArgName()));
  }
  template <typename T>
  typename GetObjectImpl<T>::ReffedResult GetObjectRef() const {
    return GetObjectImpl<T>::GetReffed(
        GetPointer<T>(ChannelArgNameTraits<T>::ChannelArgName()));
  }
  template <typename T>
  typename GetObjectImpl<T>::ReffedResult GetObjectRef(
      const DebugLocation& location, const char* reason) const {
    return GetObjectImpl<T>::GetReffed(
        GetPointer<T>(ChannelArgNameTraits<T>::ChannelArgName()), location,
        reason);
  }

  bool operator!=(const ChannelArgs& other) const;
  bool operator<(const ChannelArgs& other) const;
  bool operator==(const ChannelArgs& other) const;

  friend int QsortCompare(const ChannelArgs& lhs, const ChannelArgs& rhs) {
    return QsortCompare(lhs.args_, rhs.args_);
  }

  bool WantMinimalStack() const;
  std::string ToString() const;

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const ChannelArgs& args) {
    sink.Append(args.ToString());
  }

 private:
  explicit ChannelArgs(AVL<RefCountedStringValue, Value> args);

  GRPC_MUST_USE_RESULT ChannelArgs Set(absl::string_view name,
                                       Value value) const;

  AVL<RefCountedStringValue, Value> args_;
};

std::ostream& operator<<(std::ostream& out, const ChannelArgs& args);

}

grpc_channel_args* grpc_channel_args_copy(const grpc_channel_args* src);

grpc_channel_args* grpc_channel_args_normalize(const grpc_channel_args* src);

grpc_channel_args* grpc_channel_args_copy_and_add(const grpc_channel_args* src,
                                                  const grpc_arg* to_add,
                                                  size_t num_to_add);

grpc_channel_args* grpc_channel_args_copy_and_remove(
    const grpc_channel_args* src, const char** to_remove, size_t num_to_remove);

grpc_channel_args* grpc_channel_args_copy_and_add_and_remove(
    const grpc_channel_args* src, const char** to_remove, size_t num_to_remove,
    const grpc_arg* to_add, size_t num_to_add);

grpc_channel_args* grpc_channel_args_union(const grpc_channel_args* a,
                                           const grpc_channel_args* b);

void grpc_channel_args_destroy(grpc_channel_args* a);
inline void grpc_channel_args_destroy(const grpc_channel_args* a) {
  grpc_channel_args_destroy(const_cast<grpc_channel_args*>(a));
}

int grpc_channel_args_compare(const grpc_channel_args* a,
                              const grpc_channel_args* b);

const grpc_arg* grpc_channel_args_find(const grpc_channel_args* args,
                                       const char* name);

bool grpc_channel_args_want_minimal_stack(const grpc_channel_args* args);

typedef struct grpc_integer_options {
  int default_value;
  int min_value;
  int max_value;
} grpc_integer_options;

int grpc_channel_arg_get_integer(const grpc_arg* arg,
                                 const grpc_integer_options options);

int grpc_channel_args_find_integer(const grpc_channel_args* args,
                                   const char* name,
                                   const grpc_integer_options options);

char* grpc_channel_arg_get_string(const grpc_arg* arg);

char* grpc_channel_args_find_string(const grpc_channel_args* args,
                                    const char* name);

bool grpc_channel_arg_get_bool(const grpc_arg* arg, bool default_value);

bool grpc_channel_args_find_bool(const grpc_channel_args* args,
                                 const char* name, bool default_value);

template <typename T>
T* grpc_channel_args_find_pointer(const grpc_channel_args* args,
                                  const char* name) {
  const grpc_arg* arg = grpc_channel_args_find(args, name);
  if (arg == nullptr || arg->type != GRPC_ARG_POINTER) return nullptr;
  return static_cast<T*>(arg->value.pointer.p);
}

grpc_arg grpc_channel_arg_string_create(char* name, char* value);
grpc_arg grpc_channel_arg_integer_create(char* name, int value);
grpc_arg grpc_channel_arg_pointer_create(char* name, void* value,
                                         const grpc_arg_pointer_vtable* vtable);

std::string grpc_channel_args_string(const grpc_channel_args* args);

namespace grpc_core {

ChannelArgs ChannelArgsBuiltinPrecondition(const grpc_channel_args* src);
}

typedef grpc_core::ChannelArgs (
    *grpc_channel_args_client_channel_creation_mutator)(
    const char* target, const grpc_core::ChannelArgs& old_args,
    grpc_channel_stack_type type);

void grpc_channel_args_set_client_channel_creation_mutator(
    grpc_channel_args_client_channel_creation_mutator cb);

grpc_channel_args_client_channel_creation_mutator
grpc_channel_args_get_client_channel_creation_mutator();

#endif
