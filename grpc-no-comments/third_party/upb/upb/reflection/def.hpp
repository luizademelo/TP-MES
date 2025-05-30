
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_DEF_HPP_
#define UPB_REFLECTION_DEF_HPP_

#include <stdint.h>

#include <cstring>
#include <memory>
#include <string>

#include "upb/base/descriptor_constants.h"
#include "upb/base/status.hpp"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"
#include "upb/message/value.h"
#include "upb/mini_descriptor/decode.h"
#include "upb/mini_table/enum.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"
#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"
#include "upb/reflection/internal/enum_def.h"
#include "upb/reflection/message.h"

#include "upb/port/def.inc"

namespace upb {

typedef upb_MessageValue MessageValue;

class EnumDefPtr;
class FileDefPtr;
class MessageDefPtr;
class OneofDefPtr;

class FieldDefPtr {
 public:
  FieldDefPtr() : ptr_(nullptr) {}
  explicit FieldDefPtr(const upb_FieldDef* ptr) : ptr_(ptr) {}

  const upb_FieldDef* ptr() const { return ptr_; }

  typedef upb_FieldType Type;
  typedef upb_CType CType;
  typedef upb_Label Label;

  FileDefPtr file() const;
  const char* full_name() const { return upb_FieldDef_FullName(ptr_); }

  const upb_MiniTableField* mini_table() const {
    return upb_FieldDef_MiniTable(ptr_);
  }

  std::string MiniDescriptorEncode() const {
    upb::Arena arena;
    upb_StringView md;
    upb_FieldDef_MiniDescriptorEncode(ptr_, arena.ptr(), &md);
    return std::string(md.data, md.size);
  }

  const UPB_DESC(FieldOptions) * options() const {
    return upb_FieldDef_Options(ptr_);
  }

  Type type() const { return upb_FieldDef_Type(ptr_); }
  CType ctype() const { return upb_FieldDef_CType(ptr_); }
  Label label() const { return upb_FieldDef_Label(ptr_); }
  const char* name() const { return upb_FieldDef_Name(ptr_); }
  const char* json_name() const { return upb_FieldDef_JsonName(ptr_); }
  uint32_t number() const { return upb_FieldDef_Number(ptr_); }
  bool is_extension() const { return upb_FieldDef_IsExtension(ptr_); }
  bool is_required() const { return upb_FieldDef_IsRequired(ptr_); }
  bool has_presence() const { return upb_FieldDef_HasPresence(ptr_); }

  // Note: this accessor reflects the fact that "packed" has different defaults

  bool packed() const { return upb_FieldDef_IsPacked(ptr_); }

  uint32_t index() const { return upb_FieldDef_Index(ptr_); }

  uint32_t layout_index() const { return upb_FieldDef_LayoutIndex(ptr_); }

  MessageDefPtr containing_type() const;

  MessageDefPtr extension_scope() const;

  OneofDefPtr containing_oneof() const;
  OneofDefPtr real_containing_oneof() const;

  bool IsEnum() const { return upb_FieldDef_IsEnum(ptr_); }
  bool IsSubMessage() const { return upb_FieldDef_IsSubMessage(ptr_); }
  bool IsString() const { return upb_FieldDef_IsString(ptr_); }
  bool IsSequence() const { return upb_FieldDef_IsRepeated(ptr_); }
  bool IsPrimitive() const { return upb_FieldDef_IsPrimitive(ptr_); }
  bool IsMap() const { return upb_FieldDef_IsMap(ptr_); }

  MessageValue default_value() const { return upb_FieldDef_Default(ptr_); }

  EnumDefPtr enum_subdef() const;
  MessageDefPtr message_type() const;

  explicit operator bool() const { return ptr_ != nullptr; }

  friend bool operator==(FieldDefPtr lhs, FieldDefPtr rhs) {
    return lhs.ptr_ == rhs.ptr_;
  }

  friend bool operator!=(FieldDefPtr lhs, FieldDefPtr rhs) {
    return !(lhs == rhs);
  }

 private:
  const upb_FieldDef* ptr_;
};

class OneofDefPtr {
 public:
  OneofDefPtr() : ptr_(nullptr) {}
  explicit OneofDefPtr(const upb_OneofDef* ptr) : ptr_(ptr) {}

  const upb_OneofDef* ptr() const { return ptr_; }
  explicit operator bool() const { return ptr_ != nullptr; }

  const UPB_DESC(OneofOptions) * options() const {
    return upb_OneofDef_Options(ptr_);
  }

  MessageDefPtr containing_type() const;

  const char* name() const { return upb_OneofDef_Name(ptr_); }
  const char* full_name() const { return upb_OneofDef_FullName(ptr_); }

  int field_count() const { return upb_OneofDef_FieldCount(ptr_); }
  FieldDefPtr field(int i) const {
    return FieldDefPtr(upb_OneofDef_Field(ptr_, i));
  }

  FieldDefPtr FindFieldByName(const char* name, size_t len) const {
    return FieldDefPtr(upb_OneofDef_LookupNameWithSize(ptr_, name, len));
  }
  FieldDefPtr FindFieldByName(const char* name) const {
    return FieldDefPtr(upb_OneofDef_LookupName(ptr_, name));
  }

  template <class T>
  FieldDefPtr FindFieldByName(const T& str) const {
    return FindFieldByName(str.c_str(), str.size());
  }

  FieldDefPtr FindFieldByNumber(uint32_t num) const {
    return FieldDefPtr(upb_OneofDef_LookupNumber(ptr_, num));
  }

 private:
  const upb_OneofDef* ptr_;
};

class MessageDefPtr {
 public:
  MessageDefPtr() : ptr_(nullptr) {}
  explicit MessageDefPtr(const upb_MessageDef* ptr) : ptr_(ptr) {}

  const UPB_DESC(MessageOptions) * options() const {
    return upb_MessageDef_Options(ptr_);
  }

  std::string MiniDescriptorEncode() const {
    upb::Arena arena;
    upb_StringView md;
    upb_MessageDef_MiniDescriptorEncode(ptr_, arena.ptr(), &md);
    return std::string(md.data, md.size);
  }

  const upb_MessageDef* ptr() const { return ptr_; }

  FileDefPtr file() const;

  const char* full_name() const { return upb_MessageDef_FullName(ptr_); }
  const char* name() const { return upb_MessageDef_Name(ptr_); }

  MessageDefPtr containing_type() const;

  const upb_MiniTable* mini_table() const {
    return upb_MessageDef_MiniTable(ptr_);
  }

  int field_count() const { return upb_MessageDef_FieldCount(ptr_); }
  FieldDefPtr field(int i) const {
    return FieldDefPtr(upb_MessageDef_Field(ptr_, i));
  }

  int oneof_count() const { return upb_MessageDef_OneofCount(ptr_); }
  int real_oneof_count() const { return upb_MessageDef_RealOneofCount(ptr_); }
  OneofDefPtr oneof(int i) const {
    return OneofDefPtr(upb_MessageDef_Oneof(ptr_, i));
  }

  int enum_type_count() const { return upb_MessageDef_NestedEnumCount(ptr_); }
  EnumDefPtr enum_type(int i) const;

  int nested_message_count() const {
    return upb_MessageDef_NestedMessageCount(ptr_);
  }
  MessageDefPtr nested_message(int i) const {
    return MessageDefPtr(upb_MessageDef_NestedMessage(ptr_, i));
  }

  int nested_extension_count() const {
    return upb_MessageDef_NestedExtensionCount(ptr_);
  }
  FieldDefPtr nested_extension(int i) const {
    return FieldDefPtr(upb_MessageDef_NestedExtension(ptr_, i));
  }

  int extension_range_count() const {
    return upb_MessageDef_ExtensionRangeCount(ptr_);
  }

  upb_Syntax syntax() const { return upb_MessageDef_Syntax(ptr_); }

  FieldDefPtr FindFieldByNumber(uint32_t number) const {
    return FieldDefPtr(upb_MessageDef_FindFieldByNumber(ptr_, number));
  }
  FieldDefPtr FindFieldByName(const char* name, size_t len) const {
    return FieldDefPtr(upb_MessageDef_FindFieldByNameWithSize(ptr_, name, len));
  }
  FieldDefPtr FindFieldByName(const char* name) const {
    return FieldDefPtr(upb_MessageDef_FindFieldByName(ptr_, name));
  }

  template <class T>
  FieldDefPtr FindFieldByName(const T& str) const {
    return FindFieldByName(str.c_str(), str.size());
  }

  OneofDefPtr FindOneofByName(const char* name, size_t len) const {
    return OneofDefPtr(upb_MessageDef_FindOneofByNameWithSize(ptr_, name, len));
  }

  OneofDefPtr FindOneofByName(const char* name) const {
    return OneofDefPtr(upb_MessageDef_FindOneofByName(ptr_, name));
  }

  template <class T>
  OneofDefPtr FindOneofByName(const T& str) const {
    return FindOneofByName(str.c_str(), str.size());
  }

  bool mapentry() const { return upb_MessageDef_IsMapEntry(ptr_); }

  FieldDefPtr map_key() const {
    if (!mapentry()) return FieldDefPtr();
    return FieldDefPtr(upb_MessageDef_Field(ptr_, 0));
  }

  FieldDefPtr map_value() const {
    if (!mapentry()) return FieldDefPtr();
    return FieldDefPtr(upb_MessageDef_Field(ptr_, 1));
  }

  upb_WellKnown wellknowntype() const {
    return upb_MessageDef_WellKnownType(ptr_);
  }

  explicit operator bool() const { return ptr_ != nullptr; }

  friend bool operator==(MessageDefPtr lhs, MessageDefPtr rhs) {
    return lhs.ptr_ == rhs.ptr_;
  }

  friend bool operator!=(MessageDefPtr lhs, MessageDefPtr rhs) {
    return !(lhs == rhs);
  }

 private:
  class FieldIter {
   public:
    explicit FieldIter(const upb_MessageDef* m, int i) : m_(m), i_(i) {}
    void operator++() { i_++; }

    FieldDefPtr operator*() {
      return FieldDefPtr(upb_MessageDef_Field(m_, i_));
    }

    friend bool operator==(FieldIter lhs, FieldIter rhs) {
      return lhs.i_ == rhs.i_;
    }

    friend bool operator!=(FieldIter lhs, FieldIter rhs) {
      return !(lhs == rhs);
    }

   private:
    const upb_MessageDef* m_;
    int i_;
  };

  class FieldAccessor {
   public:
    explicit FieldAccessor(const upb_MessageDef* md) : md_(md) {}
    FieldIter begin() { return FieldIter(md_, 0); }
    FieldIter end() { return FieldIter(md_, upb_MessageDef_FieldCount(md_)); }

   private:
    const upb_MessageDef* md_;
  };

  class OneofIter {
   public:
    explicit OneofIter(const upb_MessageDef* m, int i) : m_(m), i_(i) {}
    void operator++() { i_++; }

    OneofDefPtr operator*() {
      return OneofDefPtr(upb_MessageDef_Oneof(m_, i_));
    }

    friend bool operator==(OneofIter lhs, OneofIter rhs) {
      return lhs.i_ == rhs.i_;
    }

    friend bool operator!=(OneofIter lhs, OneofIter rhs) {
      return !(lhs == rhs);
    }

   private:
    const upb_MessageDef* m_;
    int i_;
  };

  class OneofAccessor {
   public:
    explicit OneofAccessor(const upb_MessageDef* md) : md_(md) {}
    OneofIter begin() { return OneofIter(md_, 0); }
    OneofIter end() { return OneofIter(md_, upb_MessageDef_OneofCount(md_)); }

   private:
    const upb_MessageDef* md_;
  };

 public:
  FieldAccessor fields() const { return FieldAccessor(ptr()); }
  OneofAccessor oneofs() const { return OneofAccessor(ptr()); }

 private:
  const upb_MessageDef* ptr_;
};

class EnumValDefPtr {
 public:
  EnumValDefPtr() : ptr_(nullptr) {}
  explicit EnumValDefPtr(const upb_EnumValueDef* ptr) : ptr_(ptr) {}

  const UPB_DESC(EnumValueOptions) * options() const {
    return upb_EnumValueDef_Options(ptr_);
  }

  int32_t number() const { return upb_EnumValueDef_Number(ptr_); }
  const char* full_name() const { return upb_EnumValueDef_FullName(ptr_); }
  const char* name() const { return upb_EnumValueDef_Name(ptr_); }

 private:
  const upb_EnumValueDef* ptr_;
};

class EnumDefPtr {
 public:
  EnumDefPtr() : ptr_(nullptr) {}
  explicit EnumDefPtr(const upb_EnumDef* ptr) : ptr_(ptr) {}

  const UPB_DESC(EnumOptions) * options() const {
    return upb_EnumDef_Options(ptr_);
  }

  const upb_MiniTableEnum* mini_table() const {
    return _upb_EnumDef_MiniTable(ptr_);
  }

  std::string MiniDescriptorEncode() const {
    upb::Arena arena;
    upb_StringView md;
    upb_EnumDef_MiniDescriptorEncode(ptr_, arena.ptr(), &md);
    return std::string(md.data, md.size);
  }

  const upb_EnumDef* ptr() const { return ptr_; }
  explicit operator bool() const { return ptr_ != nullptr; }

  FileDefPtr file() const;
  const char* full_name() const { return upb_EnumDef_FullName(ptr_); }
  const char* name() const { return upb_EnumDef_Name(ptr_); }
  bool is_closed() const { return upb_EnumDef_IsClosed(ptr_); }

  MessageDefPtr containing_type() const;

  int32_t default_value() const { return upb_EnumDef_Default(ptr_); }

  int value_count() const { return upb_EnumDef_ValueCount(ptr_); }
  EnumValDefPtr value(int i) const {
    return EnumValDefPtr(upb_EnumDef_Value(ptr_, i));
  }

  EnumValDefPtr FindValueByName(const char* name) const {
    return EnumValDefPtr(upb_EnumDef_FindValueByName(ptr_, name));
  }

  EnumValDefPtr FindValueByNumber(int32_t num) const {
    return EnumValDefPtr(upb_EnumDef_FindValueByNumber(ptr_, num));
  }

 private:
  const upb_EnumDef* ptr_;
};

class FileDefPtr {
 public:
  explicit FileDefPtr(const upb_FileDef* ptr) : ptr_(ptr) {}

  const UPB_DESC(FileOptions) * options() const {
    return upb_FileDef_Options(ptr_);
  }

  const upb_FileDef* ptr() const { return ptr_; }

  const char* name() const { return upb_FileDef_Name(ptr_); }

  const char* package() const { return upb_FileDef_Package(ptr_); }

  upb_Syntax syntax() const { return upb_FileDef_Syntax(ptr_); }

  int dependency_count() const { return upb_FileDef_DependencyCount(ptr_); }
  FileDefPtr dependency(int index) const {
    return FileDefPtr(upb_FileDef_Dependency(ptr_, index));
  }

  int public_dependency_count() const {
    return upb_FileDef_PublicDependencyCount(ptr_);
  }
  FileDefPtr public_dependency(int index) const {
    return FileDefPtr(upb_FileDef_PublicDependency(ptr_, index));
  }

  int toplevel_enum_count() const {
    return upb_FileDef_TopLevelEnumCount(ptr_);
  }
  EnumDefPtr toplevel_enum(int index) const {
    return EnumDefPtr(upb_FileDef_TopLevelEnum(ptr_, index));
  }

  int toplevel_message_count() const {
    return upb_FileDef_TopLevelMessageCount(ptr_);
  }
  MessageDefPtr toplevel_message(int index) const {
    return MessageDefPtr(upb_FileDef_TopLevelMessage(ptr_, index));
  }

  int toplevel_extension_count() const {
    return upb_FileDef_TopLevelExtensionCount(ptr_);
  }
  FieldDefPtr toplevel_extension(int index) const {
    return FieldDefPtr(upb_FileDef_TopLevelExtension(ptr_, index));
  }

  bool resolves(const char* path) const {
    return upb_FileDef_Resolves(ptr_, path);
  }

  explicit operator bool() const { return ptr_ != nullptr; }

  friend bool operator==(FileDefPtr lhs, FileDefPtr rhs) {
    return lhs.ptr_ == rhs.ptr_;
  }

  friend bool operator!=(FileDefPtr lhs, FileDefPtr rhs) {
    return !(lhs == rhs);
  }

 private:
  const upb_FileDef* ptr_;
};

class DefPool {
 public:
  DefPool() : ptr_(upb_DefPool_New(), upb_DefPool_Free) {}
  explicit DefPool(upb_DefPool* s) : ptr_(s, upb_DefPool_Free) {}

  const upb_DefPool* ptr() const { return ptr_.get(); }
  upb_DefPool* ptr() { return ptr_.get(); }

  MessageDefPtr FindMessageByName(const char* sym) const {
    return MessageDefPtr(upb_DefPool_FindMessageByName(ptr_.get(), sym));
  }

  EnumDefPtr FindEnumByName(const char* sym) const {
    return EnumDefPtr(upb_DefPool_FindEnumByName(ptr_.get(), sym));
  }

  FileDefPtr FindFileByName(const char* name) const {
    return FileDefPtr(upb_DefPool_FindFileByName(ptr_.get(), name));
  }

  FieldDefPtr FindExtensionByName(const char* name) const {
    return FieldDefPtr(upb_DefPool_FindExtensionByName(ptr_.get(), name));
  }

  void _SetPlatform(upb_MiniTablePlatform platform) {
    _upb_DefPool_SetPlatform(ptr_.get(), platform);
  }

  // TODO: iteration?

  FileDefPtr AddFile(const UPB_DESC(FileDescriptorProto) * file_proto,
                     Status* status) {
    return FileDefPtr(
        upb_DefPool_AddFile(ptr_.get(), file_proto, status->ptr()));
  }

 private:
  std::unique_ptr<upb_DefPool, decltype(&upb_DefPool_Free)> ptr_;
};

inline FileDefPtr EnumDefPtr::file() const {
  return FileDefPtr(upb_EnumDef_File(ptr_));
}

inline FileDefPtr FieldDefPtr::file() const {
  return FileDefPtr(upb_FieldDef_File(ptr_));
}

inline FileDefPtr MessageDefPtr::file() const {
  return FileDefPtr(upb_MessageDef_File(ptr_));
}

inline MessageDefPtr MessageDefPtr::containing_type() const {
  return MessageDefPtr(upb_MessageDef_ContainingType(ptr_));
}

inline MessageDefPtr EnumDefPtr::containing_type() const {
  return MessageDefPtr(upb_EnumDef_ContainingType(ptr_));
}

inline EnumDefPtr MessageDefPtr::enum_type(int i) const {
  return EnumDefPtr(upb_MessageDef_NestedEnum(ptr_, i));
}

inline MessageDefPtr FieldDefPtr::message_type() const {
  return MessageDefPtr(upb_FieldDef_MessageSubDef(ptr_));
}

inline MessageDefPtr FieldDefPtr::containing_type() const {
  return MessageDefPtr(upb_FieldDef_ContainingType(ptr_));
}

inline MessageDefPtr FieldDefPtr::extension_scope() const {
  return MessageDefPtr(upb_FieldDef_ExtensionScope(ptr_));
}

inline MessageDefPtr OneofDefPtr::containing_type() const {
  return MessageDefPtr(upb_OneofDef_ContainingType(ptr_));
}

inline OneofDefPtr FieldDefPtr::containing_oneof() const {
  return OneofDefPtr(upb_FieldDef_ContainingOneof(ptr_));
}

inline OneofDefPtr FieldDefPtr::real_containing_oneof() const {
  return OneofDefPtr(upb_FieldDef_RealContainingOneof(ptr_));
}

inline EnumDefPtr FieldDefPtr::enum_subdef() const {
  return EnumDefPtr(upb_FieldDef_EnumSubDef(ptr_));
}

}

#include "upb/port/undef.inc"

#endif
