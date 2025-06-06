
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_RESOURCE_TYPE_IMPL_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_RESOURCE_TYPE_IMPL_H

#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

template <typename Subclass, typename ResourceTypeStruct>
class XdsResourceTypeImpl : public XdsResourceType {
 public:
  using ResourceType = ResourceTypeStruct;

  class WatcherInterface : public XdsClient::ResourceWatcherInterface {
   public:
    virtual void OnResourceChanged(
        absl::StatusOr<std::shared_ptr<const ResourceType>> resource,
        RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) = 0;

   private:

    void OnGenericResourceChanged(
        absl::StatusOr<std::shared_ptr<const XdsResourceType::ResourceData>>
            resource,
        RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
      if (!resource.ok()) {
        OnResourceChanged(resource.status(), std::move(read_delay_handle));
      } else {
        OnResourceChanged(
            std::static_pointer_cast<const ResourceType>(std::move(*resource)),
            std::move(read_delay_handle));
      }
    }
  };

  static const Subclass* Get() {
    static const Subclass* g_instance = new Subclass();
    return g_instance;
  }

  static void StartWatch(XdsClient* xds_client, absl::string_view resource_name,
                         RefCountedPtr<WatcherInterface> watcher) {
    xds_client->WatchResource(Get(), resource_name, std::move(watcher));
  }
  static void CancelWatch(XdsClient* xds_client,
                          absl::string_view resource_name,
                          WatcherInterface* watcher,
                          bool delay_unsubscription = false) {
    xds_client->CancelResourceWatch(Get(), resource_name, watcher,
                                    delay_unsubscription);
  }

  bool ResourcesEqual(const ResourceData* r1,
                      const ResourceData* r2) const override {
    return *DownCast<const ResourceType*>(r1) ==
           *DownCast<const ResourceType*>(r2);
  }
};

}

#endif
