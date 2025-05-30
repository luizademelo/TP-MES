
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_ENDPOINT_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_ENDPOINT_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/random/random.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/xds/xds_client/xds_locality.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"

#define GRPC_ARG_XDS_HTTP_PROXY "grpc.internal.xds_http_proxy"

namespace grpc_core {

struct XdsEndpointResource : public XdsResourceType::ResourceData {
  struct Priority {
    struct Locality {
      RefCountedPtr<XdsLocalityName> name;
      uint32_t lb_weight;
      EndpointAddressesList endpoints;

      bool operator==(const Locality& other) const {
        return *name == *other.name && lb_weight == other.lb_weight &&
               endpoints == other.endpoints;
      }
      bool operator!=(const Locality& other) const { return !(*this == other); }
      std::string ToString() const;
    };

    std::map<XdsLocalityName*, Locality, XdsLocalityName::Less> localities;

    bool operator==(const Priority& other) const;
    bool operator!=(const Priority& other) const { return !(*this == other); }
    std::string ToString() const;
  };
  using PriorityList = std::vector<Priority>;

  class DropConfig final : public RefCounted<DropConfig> {
   public:
    struct DropCategory {
      bool operator==(const DropCategory& other) const {
        return name == other.name &&
               parts_per_million == other.parts_per_million;
      }

      std::string name;
      const uint32_t parts_per_million;
    };

    using DropCategoryList = std::vector<DropCategory>;

    void AddCategory(std::string name, uint32_t parts_per_million) {
      drop_category_list_.emplace_back(
          DropCategory{std::move(name), parts_per_million});
      if (parts_per_million == 1000000) drop_all_ = true;
    }

    bool ShouldDrop(const std::string** category_name);

    const DropCategoryList& drop_category_list() const {
      return drop_category_list_;
    }

    bool drop_all() const { return drop_all_; }

    bool operator==(const DropConfig& other) const {
      return drop_category_list_ == other.drop_category_list_;
    }
    bool operator!=(const DropConfig& other) const { return !(*this == other); }

    std::string ToString() const;

   private:
    DropCategoryList drop_category_list_;
    bool drop_all_ = false;

    Mutex mu_;
    absl::BitGen bit_gen_ ABSL_GUARDED_BY(&mu_);
  };

  PriorityList priorities;
  RefCountedPtr<DropConfig> drop_config;

  bool operator==(const XdsEndpointResource& other) const {
    if (priorities != other.priorities) return false;
    if (drop_config == nullptr) return other.drop_config == nullptr;
    if (other.drop_config == nullptr) return false;
    return *drop_config == *other.drop_config;
  }
  std::string ToString() const;
};

}

#endif
