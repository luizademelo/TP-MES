
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_SESSION_CACHE_SSL_SESSION_CACHE_H
#define GRPC_SRC_CORE_TSI_SSL_SESSION_CACHE_SSL_SESSION_CACHE_H

#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <openssl/ssl.h>

#include <map>

#include "src/core/tsi/ssl/session_cache/ssl_session.h"
#include "src/core/util/cpp_impl_of.h"
#include "src/core/util/memory.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"

namespace tsi {

class SslSessionLRUCache
    : public grpc_core::CppImplOf<SslSessionLRUCache,
                                  struct tsi_ssl_session_cache>,
      public grpc_core::RefCounted<SslSessionLRUCache> {
 public:

  static grpc_core::RefCountedPtr<SslSessionLRUCache> Create(size_t capacity) {
    return grpc_core::MakeRefCounted<SslSessionLRUCache>(capacity);
  }

  explicit SslSessionLRUCache(size_t capacity);
  ~SslSessionLRUCache() override;

  SslSessionLRUCache(const SslSessionLRUCache&) = delete;
  SslSessionLRUCache& operator=(const SslSessionLRUCache&) = delete;

  static absl::string_view ChannelArgName() {
    return GRPC_SSL_SESSION_CACHE_ARG;
  }

  size_t Size();

  void Put(const char* key, SslSessionPtr session);

  SslSessionPtr Get(const char* key);

 private:
  class Node;

  Node* FindLocked(const std::string& key);
  void Remove(Node* node);
  void PushFront(Node* node);
  void AssertInvariants();

  grpc_core::Mutex lock_;
  size_t capacity_;

  Node* use_order_list_head_ = nullptr;
  Node* use_order_list_tail_ = nullptr;
  size_t use_order_list_size_ = 0;
  std::map<std::string, Node*> entry_by_key_;
};

}

#endif
