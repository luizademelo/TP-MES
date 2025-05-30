
// Copyright 2022 gRPC authors.

#include "src/core/xds/xds_client/xds_client.h"

#include <google/protobuf/any.pb.h>
#include <google/protobuf/struct.pb.h>
#include <grpc/grpc.h>
#include <grpc/support/json.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <stdint.h>

#include <algorithm>
#include <deque>
#include <fstream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/time/time.h"
#include "envoy/config/core/v3/base.pb.h"
#include "envoy/service/discovery/v3/discovery.pb.h"
#include "envoy/service/status/v3/csds.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/match.h"
#include "src/core/util/sync.h"
#include "src/core/util/wait_for_single_owner.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "src/core/xds/xds_client/xds_resource_type_impl.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/core/test_util/test_config.h"
#include "test/core/xds/xds_client_test_peer.h"
#include "test/core/xds/xds_transport_fake.h"
#include "upb/reflection/def.h"

using envoy::admin::v3::ClientResourceStatus;
using envoy::service::discovery::v3::DiscoveryRequest;
using envoy::service::discovery::v3::DiscoveryResponse;
using envoy::service::status::v3::ClientConfig;
using grpc_event_engine::experimental::FuzzingEventEngine;

namespace grpc_core {
namespace testing {
namespace {

constexpr absl::string_view kDefaultXdsServerUrl = "default_xds_server";

constexpr Timestamp kTime0 =
    Timestamp::FromMillisecondsAfterProcessEpoch(10000);
constexpr Timestamp kTime1 =
    Timestamp::FromMillisecondsAfterProcessEpoch(15000);
constexpr Timestamp kTime2 =
    Timestamp::FromMillisecondsAfterProcessEpoch(20000);

class XdsClientTest : public ::testing::Test {
 protected:

  class FakeXdsBootstrap : public XdsBootstrap {
   public:
    class FakeNode : public Node {
     public:
      FakeNode() : id_("xds_client_test") {}
      const std::string& id() const override { return id_; }
      const std::string& cluster() const override { return cluster_; }
      const std::string& locality_region() const override {
        return locality_region_;
      }
      const std::string& locality_zone() const override {
        return locality_zone_;
      }
      const std::string& locality_sub_zone() const override {
        return locality_sub_zone_;
      }
      const Json::Object& metadata() const override { return metadata_; }

      void set_id(std::string id) { id_ = std::move(id); }
      void set_cluster(std::string cluster) { cluster_ = std::move(cluster); }
      void set_locality_region(std::string locality_region) {
        locality_region_ = std::move(locality_region);
      }
      void set_locality_zone(std::string locality_zone) {
        locality_zone_ = std::move(locality_zone);
      }
      void set_locality_sub_zone(std::string locality_sub_zone) {
        locality_sub_zone_ = std::move(locality_sub_zone);
      }
      void set_metadata(Json::Object metadata) {
        metadata_ = std::move(metadata);
      }

     private:
      std::string id_;
      std::string cluster_;
      std::string locality_region_;
      std::string locality_zone_;
      std::string locality_sub_zone_;
      Json::Object metadata_;
    };

    class FakeXdsServerTarget : public XdsServerTarget {
     public:
      explicit FakeXdsServerTarget(std::string server_uri)
          : server_uri_(std::move(server_uri)) {}
      const std::string& server_uri() const override { return server_uri_; }
      std::string Key() const override { return server_uri_; }
      bool Equals(const XdsServerTarget& other) const override {
        const auto& o = DownCast<const FakeXdsServerTarget&>(other);
        return server_uri_ == o.server_uri_;
      }

     private:
      std::string server_uri_;
    };

    class FakeXdsServer : public XdsServer {
     public:
      explicit FakeXdsServer(
          absl::string_view server_uri = kDefaultXdsServerUrl,
          bool fail_on_data_errors = false,
          bool resource_timer_is_transient_failure = false)
          : server_target_(
                std::make_shared<FakeXdsServerTarget>(std::string(server_uri))),
            fail_on_data_errors_(fail_on_data_errors),
            resource_timer_is_transient_failure_(
                resource_timer_is_transient_failure) {}
      bool IgnoreResourceDeletion() const override {
        return !fail_on_data_errors_;
      }
      bool FailOnDataErrors() const override { return fail_on_data_errors_; }
      bool ResourceTimerIsTransientFailure() const override {
        return resource_timer_is_transient_failure_;
      }
      bool Equals(const XdsServer& other) const override {
        const auto& o = static_cast<const FakeXdsServer&>(other);
        return *server_target_ == *o.server_target_ &&
               fail_on_data_errors_ == o.fail_on_data_errors_;
      }
      std::string Key() const override {
        return absl::StrCat(server_target_->server_uri(), "#",
                            fail_on_data_errors_);
      }
      std::shared_ptr<const XdsServerTarget> target() const override {
        return server_target_;
      }

     private:
      std::shared_ptr<FakeXdsServerTarget> server_target_;
      bool fail_on_data_errors_ = false;
      bool resource_timer_is_transient_failure_ = false;
    };

    class FakeAuthority : public Authority {
     public:
      std::vector<const XdsServer*> servers() const override {
        if (server_.has_value()) {
          return {&*server_};
        } else {
          return {};
        };
      }

      void set_server(std::optional<FakeXdsServer> server) {
        server_ = std::move(server);
      }

     private:
      std::optional<FakeXdsServer> server_;
    };

    class Builder {
     public:
      Builder() { node_.emplace(); }
      Builder& set_node_id(std::string id) {
        if (!node_.has_value()) node_.emplace();
        node_->set_id(std::move(id));
        return *this;
      }
      Builder& AddAuthority(std::string name, FakeAuthority authority) {
        authorities_[std::move(name)] = std::move(authority);
        return *this;
      }
      Builder& SetServers(absl::Span<const FakeXdsServer> servers) {
        servers_.assign(servers.begin(), servers.end());
        return *this;
      }
      std::unique_ptr<XdsBootstrap> Build() {
        auto bootstrap = std::make_unique<FakeXdsBootstrap>();
        bootstrap->servers_ = std::move(servers_);
        bootstrap->node_ = std::move(node_);
        bootstrap->authorities_ = std::move(authorities_);
        return bootstrap;
      }

     private:
      std::vector<FakeXdsServer> servers_ = {FakeXdsServer()};
      std::optional<FakeNode> node_;
      std::map<std::string, FakeAuthority> authorities_;
    };

    std::string ToString() const override { return "<fake>"; }

    std::vector<const XdsServer*> servers() const override {
      std::vector<const XdsServer*> result;
      result.reserve(servers_.size());
      for (size_t i = 0; i < servers_.size(); ++i) {
        result.emplace_back(&servers_[i]);
      }
      return result;
    }

    const Node* node() const override {
      return node_.has_value() ? &*node_ : nullptr;
    }
    const Authority* LookupAuthority(const std::string& name) const override {
      auto it = authorities_.find(name);
      if (it == authorities_.end()) return nullptr;
      return &it->second;
    }

   private:
    std::vector<FakeXdsServer> servers_;
    std::optional<FakeNode> node_;
    std::map<std::string, FakeAuthority> authorities_;
  };

  template <typename ResourceStruct, bool all_resources_required_in_sotw>
  class XdsTestResourceType
      : public XdsResourceTypeImpl<
            XdsTestResourceType<ResourceStruct, all_resources_required_in_sotw>,
            ResourceStruct> {
   public:

    class Watcher : public XdsResourceTypeImpl<
                        XdsTestResourceType<ResourceStruct,
                                            all_resources_required_in_sotw>,
                        ResourceStruct>::WatcherInterface {
     public:
      explicit Watcher(std::shared_ptr<FuzzingEventEngine> event_engine)
          : event_engine_(std::move(event_engine)) {}

      ~Watcher() override {
        MutexLock lock(&mu_);
        EXPECT_THAT(queue_, ::testing::IsEmpty())
            << this << " " << queue_[0].ToString();
      }

      bool HasEvent() {
        MutexLock lock(&mu_);
        return !queue_.empty();
      }

      bool ExpectNoEvent() {
        event_engine_->TickUntilIdle();
        return !HasEvent();
      }

      struct ResourceAndReadDelayHandle {
        std::shared_ptr<const ResourceStruct> resource;
        RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle;
      };
      std::optional<ResourceAndReadDelayHandle> WaitForNextResourceAndHandle(
          SourceLocation location = SourceLocation()) {
        auto event = WaitForNextOnResourceChangedEvent(location);
        if (!event.has_value()) return std::nullopt;
        EXPECT_TRUE(event->resource.ok())
            << "got unexpected error: " << event->resource.status() << " at "
            << location.file() << ":" << location.line();
        if (!event->resource.ok()) return std::nullopt;
        return ResourceAndReadDelayHandle{std::move(*event->resource),
                                          std::move(event->read_delay_handle)};
      }

      std::shared_ptr<const ResourceStruct> WaitForNextResource(
          SourceLocation location = SourceLocation()) {
        auto resource_and_handle = WaitForNextResourceAndHandle(location);
        if (!resource_and_handle.has_value()) return nullptr;
        return std::move(resource_and_handle->resource);
      }

      std::optional<absl::Status> WaitForNextError(
          SourceLocation location = SourceLocation()) {
        auto event = WaitForNextOnResourceChangedEvent(location);
        if (!event.has_value()) return std::nullopt;
        EXPECT_FALSE(event->resource.ok())
            << "got unexpected resource: " << (*event->resource)->name << " at "
            << location.file() << ":" << location.line();
        if (event->resource.ok()) return std::nullopt;
        return event->resource.status();
      }

      bool WaitForDoesNotExist(SourceLocation location = SourceLocation()) {
        auto status = WaitForNextError(location);
        if (!status.has_value()) return false;
        EXPECT_EQ(status->code(), absl::StatusCode::kNotFound)
            << "unexpected status: " << *status << " at " << location.file()
            << ":" << location.line();
        return status->code() == absl::StatusCode::kNotFound;
      }

      std::optional<absl::Status> WaitForNextAmbientError(
          SourceLocation location = SourceLocation()) {
        auto event = WaitForNextEvent();
        if (!event.has_value()) return std::nullopt;
        return Match(
            event->payload,
            [&](const absl::StatusOr<std::shared_ptr<const ResourceStruct>>&
                    resource) -> std::optional<absl::Status> {
              EXPECT_TRUE(false)
                  << "got unexpected resource: " << event->ToString() << " at "
                  << location.file() << ":" << location.line();
              return std::nullopt;
            },
            [&](const absl::Status& status) -> std::optional<absl::Status> {
              return status;
            });
      }

     private:

      struct Event {
        std::variant<

            absl::StatusOr<std::shared_ptr<const ResourceStruct>>,

            absl::Status>
            payload;
        RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle;

        std::string ToString() const {
          return Match(
              payload,
              [&](const absl::StatusOr<std::shared_ptr<const ResourceStruct>>&
                      resource) {
                return absl::StrCat(
                    "{resource=",
                    resource.ok() ? (*resource)->name
                                  : resource.status().ToString(),
                    ", read_delay_handle=", (read_delay_handle == nullptr),
                    "}");
              },
              [&](const absl::Status& status) {
                return absl::StrCat("{ambient_error=", status.ToString(),
                                    ", read_delay_handle=",
                                    (read_delay_handle == nullptr), "}");
              });
        }
      };

      std::optional<Event> WaitForNextEvent() {
        while (true) {
          {
            MutexLock lock(&mu_);
            if (!queue_.empty()) {
              Event event = std::move(queue_.front());
              queue_.pop_front();
              return event;
            }
            if (event_engine_->IsIdle()) return std::nullopt;
          }
          event_engine_->Tick();
        }
      }

      struct OnResourceChangedEvent {
        absl::StatusOr<std::shared_ptr<const ResourceStruct>> resource;
        RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle;
      };
      std::optional<OnResourceChangedEvent> WaitForNextOnResourceChangedEvent(
          SourceLocation location = SourceLocation()) {
        auto event = WaitForNextEvent();
        if (!event.has_value()) return std::nullopt;
        return MatchMutable(
            &event->payload,
            [&](absl::StatusOr<std::shared_ptr<const ResourceStruct>>* resource)
                -> std::optional<OnResourceChangedEvent> {
              return OnResourceChangedEvent{
                  std::move(*resource), std::move(event->read_delay_handle)};
            },
            [&](absl::Status* status) -> std::optional<OnResourceChangedEvent> {
              EXPECT_TRUE(false)
                  << "got unexpected ambient error: " << status->ToString()
                  << " at " << location.file() << ":" << location.line();
              return std::nullopt;
            });
      }

      void OnResourceChanged(
          absl::StatusOr<std::shared_ptr<const ResourceStruct>> resource,
          RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle)
          override {
        MutexLock lock(&mu_);
        queue_.emplace_back(
            Event{std::move(resource), std::move(read_delay_handle)});
      }

      void OnAmbientError(absl::Status status,
                          RefCountedPtr<XdsClient::ReadDelayHandle>
                              read_delay_handle) override {
        MutexLock lock(&mu_);
        queue_.push_back(
            Event{std::move(status), std::move(read_delay_handle)});
      }

      std::shared_ptr<FuzzingEventEngine> event_engine_;

      Mutex mu_;
      std::deque<Event> queue_ ABSL_GUARDED_BY(&mu_);
    };

    absl::string_view type_url() const override {
      return ResourceStruct::TypeUrl();
    }
    XdsResourceType::DecodeResult Decode(
        const XdsResourceType::DecodeContext& ,
        absl::string_view serialized_resource) const override {
      auto json = JsonParse(serialized_resource);
      XdsResourceType::DecodeResult result;
      if (!json.ok()) {
        result.resource = json.status();
      } else if (auto resource = LoadFromJson<ResourceStruct>(*json);
                 !resource.ok()) {
        if (auto it = json->object().find("name"); it != json->object().end()) {
          result.name = it->second.string();
        }
        result.resource = resource.status();
      } else {
        result.name = resource->name;
        result.resource =
            std::make_unique<ResourceStruct>(std::move(*resource));
      }
      return result;
    }
    bool AllResourcesRequiredInSotW() const override {
      return all_resources_required_in_sotw;
    }
    void InitUpbSymtab(XdsClient*, upb_DefPool* ) const override {}

    static google::protobuf::Any EncodeAsAny(const ResourceStruct& resource) {
      google::protobuf::Any any;
      any.set_type_url(
          absl::StrCat("type.googleapis.com/", ResourceStruct::TypeUrl()));
      any.set_value(resource.AsJsonString());
      return any;
    }
  };

  struct XdsFooResource : public XdsResourceType::ResourceData {
    std::string name;
    uint32_t value;

    XdsFooResource() = default;
    XdsFooResource(std::string name, uint32_t value)
        : name(std::move(name)), value(value) {}

    bool operator==(const XdsFooResource& other) const {
      return name == other.name && value == other.value;
    }

    std::string AsJsonString() const {
      return absl::StrCat("{\"name\":\"", name, "\",\"value\":", value, "}");
    }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<XdsFooResource>()
                                      .Field("name", &XdsFooResource::name)
                                      .Field("value", &XdsFooResource::value)
                                      .Finish();
      return loader;
    }

    static absl::string_view TypeUrl() { return "test.v3.foo"; }
  };
  using XdsFooResourceType = XdsTestResourceType<XdsFooResource, false>;

  struct XdsBarResource : public XdsResourceType::ResourceData {
    std::string name;
    std::string value;

    XdsBarResource() = default;
    XdsBarResource(std::string name, std::string value)
        : name(std::move(name)), value(std::move(value)) {}

    bool operator==(const XdsBarResource& other) const {
      return name == other.name && value == other.value;
    }

    std::string AsJsonString() const {
      return absl::StrCat("{\"name\":\"", name, "\",\"value\":\"", value,
                          "\"}");
    }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<XdsBarResource>()
                                      .Field("name", &XdsBarResource::name)
                                      .Field("value", &XdsBarResource::value)
                                      .Finish();
      return loader;
    }

    static absl::string_view TypeUrl() { return "test.v3.bar"; }
  };
  using XdsBarResourceType = XdsTestResourceType<XdsBarResource, false>;

  struct XdsWildcardCapableResource : public XdsResourceType::ResourceData {
    std::string name;
    uint32_t value;

    XdsWildcardCapableResource() = default;
    XdsWildcardCapableResource(std::string name, uint32_t value)
        : name(std::move(name)), value(value) {}

    bool operator==(const XdsWildcardCapableResource& other) const {
      return name == other.name && value == other.value;
    }

    std::string AsJsonString() const {
      return absl::StrCat("{\"name\":\"", name, "\",\"value\":\"", value,
                          "\"}");
    }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<XdsWildcardCapableResource>()
              .Field("name", &XdsWildcardCapableResource::name)
              .Field("value", &XdsWildcardCapableResource::value)
              .Finish();
      return loader;
    }

    static absl::string_view TypeUrl() { return "test.v3.wildcard_capable"; }
  };
  using XdsWildcardCapableResourceType =
      XdsTestResourceType<XdsWildcardCapableResource,
                          true>;

  class ResponseBuilder {
   public:
    explicit ResponseBuilder(absl::string_view type_url) {
      response_.set_type_url(absl::StrCat("type.googleapis.com/", type_url));
    }

    ResponseBuilder& set_version_info(absl::string_view version_info) {
      response_.set_version_info(std::string(version_info));
      return *this;
    }
    ResponseBuilder& set_nonce(absl::string_view nonce) {
      response_.set_nonce(std::string(nonce));
      return *this;
    }

    template <typename ResourceType>
    ResponseBuilder& AddResource(
        const typename ResourceType::ResourceType& resource,
        bool in_resource_wrapper = false) {
      auto* res = response_.add_resources();
      *res = ResourceType::EncodeAsAny(resource);
      if (in_resource_wrapper) {
        envoy::service::discovery::v3::Resource resource_wrapper;
        resource_wrapper.set_name(resource.name);
        *resource_wrapper.mutable_resource() = std::move(*res);
        res->PackFrom(resource_wrapper);
      }
      return *this;
    }

    ResponseBuilder& AddFooResource(const XdsFooResource& resource,
                                    bool in_resource_wrapper = false) {
      return AddResource<XdsFooResourceType>(resource, in_resource_wrapper);
    }

    ResponseBuilder& AddBarResource(const XdsBarResource& resource,
                                    bool in_resource_wrapper = false) {
      return AddResource<XdsBarResourceType>(resource, in_resource_wrapper);
    }

    ResponseBuilder& AddWildcardCapableResource(
        const XdsWildcardCapableResource& resource,
        bool in_resource_wrapper = false) {
      return AddResource<XdsWildcardCapableResourceType>(resource,
                                                         in_resource_wrapper);
    }

    ResponseBuilder& AddInvalidResource(
        absl::string_view type_url, absl::string_view value,
        absl::string_view resource_wrapper_name = "") {
      auto* res = response_.add_resources();
      res->set_type_url(absl::StrCat("type.googleapis.com/", type_url));
      res->set_value(std::string(value));
      if (!resource_wrapper_name.empty()) {
        envoy::service::discovery::v3::Resource resource_wrapper;
        resource_wrapper.set_name(std::string(resource_wrapper_name));
        *resource_wrapper.mutable_resource() = std::move(*res);
        res->PackFrom(resource_wrapper);
      }
      return *this;
    }

    ResponseBuilder& AddInvalidResourceWrapper() {
      auto* res = response_.add_resources();
      res->set_type_url(
          "type.googleapis.com/envoy.service.discovery.v3.Resource");
      res->set_value(std::string("\0", 1));
      return *this;
    }

    ResponseBuilder& AddEmptyResource() {
      response_.add_resources();
      return *this;
    }

    ResponseBuilder& AddResourceError(absl::string_view name,
                                      absl::Status status) {
      auto* error = response_.add_resource_errors();
      error->mutable_resource_name()->set_name(std::string(name));
      auto* status_proto = error->mutable_error_detail();
      status_proto->set_code(static_cast<uint32_t>(status.code()));
      status_proto->set_message(std::string(status.message()));
      return *this;
    }

    std::string Serialize() {
      std::string serialized_response;
      EXPECT_TRUE(response_.SerializeToString(&serialized_response));
      return serialized_response;
    }

   private:
    DiscoveryResponse response_;
  };

  class MetricsReporter : public XdsMetricsReporter {
   public:
    using ResourceUpdateMap = std::map<
        std::pair<std::string , std::string >,
        uint64_t>;
    using ServerFailureMap = std::map<std::string , uint64_t>;

    explicit MetricsReporter(std::shared_ptr<FuzzingEventEngine> event_engine)
        : event_engine_(std::move(event_engine)) {}

    ResourceUpdateMap resource_updates_valid() const {
      MutexLock lock(&mu_);
      return resource_updates_valid_;
    }
    ResourceUpdateMap resource_updates_invalid() const {
      MutexLock lock(&mu_);
      return resource_updates_invalid_;
    }
    const ServerFailureMap& server_failures() const { return server_failures_; }

    bool WaitForMetricsReporterData(
        ::testing::Matcher<ResourceUpdateMap> resource_updates_valid_matcher,
        ::testing::Matcher<ResourceUpdateMap> resource_updates_invalid_matcher,
        ::testing::Matcher<ServerFailureMap> server_failures_matcher,
        SourceLocation location = SourceLocation()) {
      while (true) {
        {
          MutexLock lock(&mu_);
          if (::testing::Matches(resource_updates_valid_matcher)(
                  resource_updates_valid_) &&
              ::testing::Matches(resource_updates_invalid_matcher)(
                  resource_updates_invalid_) &&
              ::testing::Matches(server_failures_matcher)(server_failures_)) {
            return true;
          }
          if (event_engine_->IsIdle()) {
            EXPECT_THAT(resource_updates_valid_, resource_updates_valid_matcher)
                << location.file() << ":" << location.line();
            EXPECT_THAT(resource_updates_invalid_,
                        resource_updates_invalid_matcher)
                << location.file() << ":" << location.line();
            EXPECT_THAT(server_failures_, server_failures_matcher)
                << location.file() << ":" << location.line();
            return false;
          }
        }
        event_engine_->Tick();
      }
    }

   private:
    void ReportResourceUpdates(absl::string_view xds_server,
                               absl::string_view resource_type,
                               uint64_t num_resources_valid,
                               uint64_t num_resources_invalid) override {
      MutexLock lock(&mu_);
      auto key = std::pair(std::string(xds_server), std::string(resource_type));
      if (num_resources_valid > 0) {
        resource_updates_valid_[key] += num_resources_valid;
      }
      if (num_resources_invalid > 0) {
        resource_updates_invalid_[key] += num_resources_invalid;
      }
      cond_.SignalAll();
    }

    void ReportServerFailure(absl::string_view xds_server) override {
      MutexLock lock(&mu_);
      ++server_failures_[std::string(xds_server)];
      cond_.SignalAll();
    }

    std::shared_ptr<FuzzingEventEngine> event_engine_;

    mutable Mutex mu_;
    ResourceUpdateMap resource_updates_valid_ ABSL_GUARDED_BY(mu_);
    ResourceUpdateMap resource_updates_invalid_ ABSL_GUARDED_BY(mu_);
    ServerFailureMap server_failures_ ABSL_GUARDED_BY(mu_);
    CondVar cond_;
  };

  using ResourceCounts =
      std::vector<std::pair<XdsClientTestPeer::ResourceCountLabels, uint64_t>>;
  ResourceCounts GetResourceCounts() {
    ResourceCounts resource_counts;
    XdsClientTestPeer(xds_client_.get())
        .TestReportResourceCounts(
            [&](const XdsClientTestPeer::ResourceCountLabels& labels,
                uint64_t count) {
              resource_counts.emplace_back(labels, count);
            });
    return resource_counts;
  }

  using ServerConnectionMap = std::map<std::string, bool>;
  ServerConnectionMap GetServerConnections() {
    ServerConnectionMap server_connection_map;
    XdsClientTestPeer(xds_client_.get())
        .TestReportServerConnections(
            [&](absl::string_view xds_server, bool connected) {
              std::string server(xds_server);
              EXPECT_EQ(server_connection_map.find(server),
                        server_connection_map.end());
              server_connection_map[std::move(server)] = connected;
            });
    return server_connection_map;
  }

  void SetUp() override {
    time_cache_.TestOnlySetNow(kTime0);
    event_engine_ = std::make_shared<FuzzingEventEngine>(
        FuzzingEventEngine::Options(), fuzzing_event_engine::Actions());
    grpc_timer_manager_set_start_threaded(false);
    grpc_init();
  }

  void TearDown() override {
    transport_factory_.reset();
    xds_client_.reset();
    event_engine_->FuzzingDone();
    event_engine_->TickUntilIdle();
    event_engine_->UnsetGlobalHooks();
    WaitForSingleOwner(std::move(event_engine_));
    grpc_shutdown_blocking();
  }

  void InitXdsClient(FakeXdsBootstrap::Builder bootstrap_builder =
                         FakeXdsBootstrap::Builder()) {
    transport_factory_ = MakeRefCounted<FakeXdsTransportFactory>(
        []() { FAIL() << "Multiple concurrent reads"; }, event_engine_);
    auto metrics_reporter = std::make_unique<MetricsReporter>(event_engine_);
    metrics_reporter_ = metrics_reporter.get();
    xds_client_ = MakeRefCounted<XdsClient>(
        bootstrap_builder.Build(), transport_factory_, event_engine_,
        std::move(metrics_reporter), "foo agent", "foo version");
  }

  RefCountedPtr<XdsFooResourceType::Watcher> StartFooWatch(
      absl::string_view resource_name) {
    auto watcher = MakeRefCounted<XdsFooResourceType::Watcher>(event_engine_);
    XdsFooResourceType::StartWatch(xds_client_.get(), resource_name, watcher);
    return watcher;
  }
  void CancelFooWatch(XdsFooResourceType::Watcher* watcher,
                      absl::string_view resource_name,
                      bool delay_unsubscription = false) {
    XdsFooResourceType::CancelWatch(xds_client_.get(), resource_name, watcher,
                                    delay_unsubscription);
  }

  RefCountedPtr<XdsBarResourceType::Watcher> StartBarWatch(
      absl::string_view resource_name) {
    auto watcher = MakeRefCounted<XdsBarResourceType::Watcher>(event_engine_);
    XdsBarResourceType::StartWatch(xds_client_.get(), resource_name, watcher);
    return watcher;
  }
  void CancelBarWatch(XdsBarResourceType::Watcher* watcher,
                      absl::string_view resource_name,
                      bool delay_unsubscription = false) {
    XdsBarResourceType::CancelWatch(xds_client_.get(), resource_name, watcher,
                                    delay_unsubscription);
  }

  RefCountedPtr<XdsWildcardCapableResourceType::Watcher>
  StartWildcardCapableWatch(absl::string_view resource_name) {
    auto watcher =
        MakeRefCounted<XdsWildcardCapableResourceType::Watcher>(event_engine_);
    XdsWildcardCapableResourceType::StartWatch(xds_client_.get(), resource_name,
                                               watcher);
    return watcher;
  }
  void CancelWildcardCapableWatch(
      XdsWildcardCapableResourceType::Watcher* watcher,
      absl::string_view resource_name, bool delay_unsubscription = false) {
    XdsWildcardCapableResourceType::CancelWatch(
        xds_client_.get(), resource_name, watcher, delay_unsubscription);
  }

  RefCountedPtr<FakeXdsTransportFactory::FakeStreamingCall> WaitForAdsStream(
      const XdsBootstrap::XdsServer& xds_server) {
    return transport_factory_->WaitForStream(
        *xds_server.target(), FakeXdsTransportFactory::kAdsMethod);
  }

  RefCountedPtr<FakeXdsTransportFactory::FakeStreamingCall> WaitForAdsStream() {
    return WaitForAdsStream(*xds_client_->bootstrap().servers().front());
  }

  void TriggerConnectionFailure(const XdsBootstrap::XdsServer& xds_server,
                                absl::Status status) {
    transport_factory_->TriggerConnectionFailure(*xds_server.target(),
                                                 std::move(status));
  }

  std::optional<DiscoveryRequest> WaitForRequest(
      FakeXdsTransportFactory::FakeStreamingCall* stream,
      SourceLocation location = SourceLocation()) {
    auto message = stream->WaitForMessageFromClient();
    if (!message.has_value()) return std::nullopt;
    DiscoveryRequest request;
    bool success = request.ParseFromString(*message);
    EXPECT_TRUE(success) << "Failed to deserialize DiscoveryRequest at "
                         << location.file() << ":" << location.line();
    if (!success) return std::nullopt;
    return std::move(request);
  }

  void CheckRequest(const DiscoveryRequest& request, absl::string_view type_url,
                    absl::string_view version_info,
                    absl::string_view response_nonce,
                    const absl::Status& error_detail,
                    const std::set<absl::string_view>& resource_names,
                    SourceLocation location = SourceLocation()) {
    EXPECT_EQ(request.type_url(),
              absl::StrCat("type.googleapis.com/", type_url))
        << location.file() << ":" << location.line();
    EXPECT_EQ(request.version_info(), version_info)
        << location.file() << ":" << location.line();
    EXPECT_EQ(request.response_nonce(), response_nonce)
        << location.file() << ":" << location.line();
    if (error_detail.ok()) {
      EXPECT_FALSE(request.has_error_detail())
          << location.file() << ":" << location.line();
    } else {
      EXPECT_EQ(request.error_detail().code(),
                static_cast<int>(error_detail.code()))
          << location.file() << ":" << location.line();
      EXPECT_EQ(request.error_detail().message(), error_detail.message())
          << location.file() << ":" << location.line();
    }
    EXPECT_THAT(request.resource_names(),
                ::testing::UnorderedElementsAreArray(resource_names))
        << location.file() << ":" << location.line();
  }

  void CheckRequestNode(const DiscoveryRequest& request,
                        SourceLocation location = SourceLocation()) {
    return CheckNode(request.node(), location);
  }

  void CheckNode(const envoy::config::core::v3::Node& node,
                 SourceLocation location = SourceLocation()) {

    EXPECT_EQ(node.id(), xds_client_->bootstrap().node()->id())
        << location.file() << ":" << location.line();
    EXPECT_EQ(node.cluster(), xds_client_->bootstrap().node()->cluster())
        << location.file() << ":" << location.line();
    EXPECT_EQ(node.locality().region(),
              xds_client_->bootstrap().node()->locality_region())
        << location.file() << ":" << location.line();
    EXPECT_EQ(node.locality().zone(),
              xds_client_->bootstrap().node()->locality_zone())
        << location.file() << ":" << location.line();
    EXPECT_EQ(node.locality().sub_zone(),
              xds_client_->bootstrap().node()->locality_sub_zone())
        << location.file() << ":" << location.line();
    if (xds_client_->bootstrap().node()->metadata().empty()) {
      EXPECT_FALSE(node.has_metadata())
          << location.file() << ":" << location.line();
    } else {
      std::string metadata_json_str;
      auto status =
          MessageToJsonString(node.metadata(), &metadata_json_str,
                              GRPC_CUSTOM_JSONUTIL::JsonPrintOptions());
      ASSERT_TRUE(status.ok())
          << status << " on " << location.file() << ":" << location.line();
      auto metadata_json = JsonParse(metadata_json_str);
      ASSERT_TRUE(metadata_json.ok())
          << metadata_json.status() << " on " << location.file() << ":"
          << location.line();
      Json expected =
          Json::FromObject(xds_client_->bootstrap().node()->metadata());
      EXPECT_EQ(*metadata_json, expected)
          << location.file() << ":" << location.line()
          << ":\nexpected: " << JsonDump(expected)
          << "\nactual: " << JsonDump(*metadata_json);
    }
    EXPECT_EQ(node.user_agent_name(), "foo agent")
        << location.file() << ":" << location.line();
    EXPECT_EQ(node.user_agent_version(), "foo version")
        << location.file() << ":" << location.line();
  }

  ClientConfig DumpCsds(SourceLocation location = SourceLocation()) {
    std::string client_config_serialized =
        XdsClientTestPeer(xds_client_.get()).TestDumpClientConfig();
    ClientConfig client_config_proto;
    CHECK(client_config_proto.ParseFromString(client_config_serialized))
        << "at " << location.file() << ":" << location.line();
    CheckNode(client_config_proto.node(), location);
    return client_config_proto;
  }

  ScopedTimeCache time_cache_;
  std::shared_ptr<FuzzingEventEngine> event_engine_;
  RefCountedPtr<FakeXdsTransportFactory> transport_factory_;
  RefCountedPtr<XdsClient> xds_client_;
  MetricsReporter* metrics_reporter_ = nullptr;
};

MATCHER_P3(ResourceCountLabelsEq, xds_authority, resource_type, cache_state,
           "equals ResourceCountLabels") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(xds_authority, arg.xds_authority,
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(resource_type, arg.resource_type,
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(cache_state, arg.cache_state,
                                      result_listener);
  return ok;
}

MATCHER_P(TimestampProtoEq, timestamp, "equals timestamp") {
  gpr_timespec ts = {arg.seconds(), arg.nanos(), GPR_CLOCK_REALTIME};
  return ::testing::ExplainMatchResult(
      timestamp, Timestamp::FromTimespecRoundDown(ts), result_listener);
}

MATCHER_P5(CsdsResourceEq, client_status, type_url, name, resource_fields,
           error_fields, "equals CSDS resource") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(arg.client_status(), client_status,
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(
      absl::StrCat("type.googleapis.com/", type_url), arg.type_url(),
      result_listener);
  ok &= ::testing::ExplainMatchResult(name, arg.name(), result_listener);
  ok &= ::testing::ExplainMatchResult(resource_fields, arg, result_listener);
  ok &= ::testing::ExplainMatchResult(error_fields, arg, result_listener);
  return ok;
}

MATCHER_P3(CsdsResourceFields, resource, version, last_updated,
           "CSDS resource fields") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(resource, arg.xds_config().value(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(version, arg.version_info(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(last_updated, arg.last_updated(),
                                      result_listener);
  return ok;
}

MATCHER(CsdsNoResourceFields, "CSDS has no resource fields") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(::testing::IsFalse(),
                                      arg.has_xds_config(), result_listener);
  ok &= ::testing::ExplainMatchResult("", arg.version_info(), result_listener);
  ok &= ::testing::ExplainMatchResult(::testing::IsFalse(),
                                      arg.has_last_updated(), result_listener);
  return ok;
}

MATCHER_P3(CsdsErrorFields, error_details, error_version, error_time,
           "CSDS error fields") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(
      error_details, arg.error_state().details(), result_listener);
  ok &= ::testing::ExplainMatchResult(
      error_version, arg.error_state().version_info(), result_listener);
  ok &= ::testing::ExplainMatchResult(
      error_time, arg.error_state().last_update_attempt(), result_listener);
  return ok;
}

MATCHER_P(CsdsErrorDetailsOnly, error_details, "CSDS error details only") {
  bool ok = true;
  ok &= ::testing::ExplainMatchResult(
      error_details, arg.error_state().details(), result_listener);
  ok &= ::testing::ExplainMatchResult("", arg.error_state().version_info(),
                                      result_listener);
  ok &= ::testing::ExplainMatchResult(
      ::testing::IsFalse(), arg.error_state().has_last_update_attempt(),
      result_listener);
  return ok;
}

MATCHER(CsdsNoErrorFields, "CSDS has no error fields") {
  return ::testing::ExplainMatchResult(::testing::IsFalse(),
                                       arg.has_error_state(), result_listener);
}

MATCHER_P5(CsdsResourceAcked, type_url, name, resource, version, last_updated,
           "equals CSDS ACKED resource") {
  return ::testing::ExplainMatchResult(
      CsdsResourceEq(ClientResourceStatus::ACKED, type_url, name,
                     CsdsResourceFields(resource, version, last_updated),
                     CsdsNoErrorFields()),
      arg, result_listener);
}

MATCHER_P2(CsdsResourceRequested, type_url, name,
           "equals CSDS requested resource") {
  return ::testing::ExplainMatchResult(
      CsdsResourceEq(ClientResourceStatus::REQUESTED, type_url, name,
                     CsdsNoResourceFields(), CsdsNoErrorFields()),
      arg, result_listener);
}

MATCHER_P2(CsdsResourceDoesNotExistOnTimeout, type_url, name,
           "equals CSDS does-not-exist-on-timeout resource") {
  return ::testing::ExplainMatchResult(
      CsdsResourceEq(ClientResourceStatus::DOES_NOT_EXIST, type_url, name,
                     CsdsNoResourceFields(),
                     CsdsErrorDetailsOnly("does not exist")),
      arg, result_listener);
}

TEST_F(XdsClientTest, BasicWatch) {
  InitXdsClient();

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->server_failures(), ::testing::ElementsAre());

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(), ::testing::ElementsAre());
}

TEST_F(XdsClientTest, UpdateFromServer) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 9))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, MultipleWatchersForSameResource) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch("foo1");

  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  ASSERT_FALSE(stream->HaveMessageFromClient());

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 9))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");

  ASSERT_FALSE(WaitForRequest(stream.get()));

  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, SubscribeToMultipleResources) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch("foo2");

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                    XdsFooResourceType::Get()->type_url(),
                                    "requested"),
              1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                        "foo2")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo2", 7))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});

  CancelFooWatch(watcher.get(), "foo1");

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo2",
                  resource2->AsJsonString(), "1", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(), {"foo2"});

  CancelFooWatch(watcher2.get(), "foo2");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, UpdateContainsOnlyChangedResource) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch("foo2");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo2", 7))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("C")
          .AddFooResource(XdsFooResource("foo1", 9))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          3)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "2",
                                    TimestampProtoEq(kTime2)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "C",
               absl::OkStatus(),
               {"foo1", "foo2"});

  CancelFooWatch(watcher.get(), "foo1");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "C",
               absl::OkStatus(), {"foo2"});

  CancelFooWatch(watcher2.get(), "foo2");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceValidationFailure) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo1\",\"value\":[]}")
          .Serialize());

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "nacked"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::ElementsAre(CsdsResourceEq(
          ClientResourceStatus::NACKED, XdsFooResourceType::Get()->type_url(),
          "foo1", CsdsNoResourceFields(),
          CsdsErrorFields("invalid resource: errors validating JSON: "
                          "[field:value error:is not a number]",
                          "1", TimestampProtoEq(kTime0)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(
      *request, XdsFooResourceType::Get()->type_url(),
      "", "A",

      absl::InvalidArgumentError(
          "xDS response validation errors: ["
          "resource index 0: foo1: INVALID_ARGUMENT: errors validating JSON: "
          "[field:value error:is not a number]]"),
      {"foo1"});

  auto watcher2 = StartFooWatch("foo1");
  error = watcher2->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 9))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 9);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceValidationFailureMultipleResources) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  auto watcher2 = StartFooWatch("foo2");

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  2)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::ElementsAre(
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo1"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                "foo2")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1", "foo2"});

  auto watcher3 = StartFooWatch("foo3");

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  3)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo1"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo2"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                "foo3")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1", "foo2", "foo3"});

  auto watcher4 = StartFooWatch("foo4");

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  4)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo1"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo2"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo3"),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                "foo4")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1", "foo2", "foo3", "foo4"});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")

          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo1\",\"value\":[]}")

          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo2,\"value\":6}")

          .AddEmptyResource()

          .AddInvalidResourceWrapper()

          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo3,\"value\":6}",
                              "foo3")

          .AddFooResource(XdsFooResource("foo4", 5))
          .Serialize());

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;
  error = watcher3->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: JSON parsing failed: "
            "[JSON parse error at index 15] (node ID:xds_client_test)")
      << *error;

  EXPECT_FALSE(watcher2->HasEvent());

  auto resource = watcher4->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo4");
  EXPECT_EQ(resource->value, 5);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          5)),
      ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(

          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),

          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "nacked"),
                          2),

          ::testing::Pair(
              ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                    XdsFooResourceType::Get()->type_url(),
                                    "requested"),
              1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceEq(
              ClientResourceStatus::NACKED,
              XdsFooResourceType::Get()->type_url(), "foo1",
              CsdsNoResourceFields(),
              CsdsErrorFields("invalid resource: errors validating JSON: "
                              "[field:value error:is not a number]",
                              "1", TimestampProtoEq(kTime0))),
          CsdsResourceRequested(XdsFooResourceType::Get()->type_url(), "foo2"),
          CsdsResourceEq(
              ClientResourceStatus::NACKED,
              XdsFooResourceType::Get()->type_url(), "foo3",
              CsdsNoResourceFields(),
              CsdsErrorFields("invalid resource: JSON parsing failed: "
                              "[JSON parse error at index 15]",
                              "1", TimestampProtoEq(kTime0))),
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(), "foo4",
                            resource->AsJsonString(), "1",
                            TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",

               absl::InvalidArgumentError(absl::StrCat(
                   "xDS response validation errors: ["

                   "resource index 0: foo1: "
                   "INVALID_ARGUMENT: errors validating JSON: "
                   "[field:value error:is not a number]; "

                   "resource index 1: INVALID_ARGUMENT: JSON parsing failed: "
                   "[JSON parse error at index 15]; "

                   "resource index 2: incorrect resource type \"\" "
                   "(should be \"",
                   XdsFooResourceType::Get()->type_url(),
                   "\"); "

                   "resource index 3: Can't decode Resource proto wrapper; "

                   "resource index 4: foo3: "
                   "INVALID_ARGUMENT: JSON parsing failed: "
                   "[JSON parse error at index 15]]")),
               {"foo1", "foo2", "foo3", "foo4"});

  CancelFooWatch(watcher.get(), "foo1", true);
  CancelFooWatch(watcher2.get(), "foo2", true);
  CancelFooWatch(watcher3.get(), "foo3", true);
  CancelFooWatch(watcher4.get(), "foo4");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceValidationFailureForCachedResource) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo1\",\"value\":[]}")
          .Serialize());

  auto error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "nacked_but_cached"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceEq(
                  ClientResourceStatus::NACKED,
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  CsdsResourceFields(resource->AsJsonString(), "1",
                                     TimestampProtoEq(kTime0)),
                  CsdsErrorFields("invalid resource: errors validating JSON: "
                                  "[field:value error:is not a number]",
                                  "2", TimestampProtoEq(kTime1)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(
      *request, XdsFooResourceType::Get()->type_url(),
      "1", "B",

      absl::InvalidArgumentError(
          "xDS response validation errors: ["
          "resource index 0: foo1: INVALID_ARGUMENT: errors validating JSON: "
          "[field:value error:is not a number]]"),
      {"foo1"});

  auto watcher2 = StartFooWatch("foo1");
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(
      *error,
      absl::InvalidArgumentError(
          "invalid resource: errors validating JSON: "
          "[field:value error:is not a number] (node ID:xds_client_test)"));

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest,
       ResourceValidationFailureForCachedResourceWithFailOnDataErrors) {
  testing::ScopedExperimentalEnvVar env_var(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, true)}));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo1\",\"value\":[]}")
          .Serialize());

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "nacked"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::ElementsAre(CsdsResourceEq(
          ClientResourceStatus::NACKED, XdsFooResourceType::Get()->type_url(),
          "foo1", CsdsNoResourceFields(),
          CsdsErrorFields("invalid resource: errors validating JSON: "
                          "[field:value error:is not a number]",
                          "2", TimestampProtoEq(kTime1)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(
      *request, XdsFooResourceType::Get()->type_url(),
      "1", "B",

      absl::InvalidArgumentError(
          "xDS response validation errors: ["
          "resource index 0: foo1: INVALID_ARGUMENT: errors validating JSON: "
          "[field:value error:is not a number]]"),
      {"foo1"});

  auto watcher2 = StartFooWatch("foo1");
  error = watcher2->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest,
       ResourceValidationFailureForCachedResourceWithFailOnDataErrorsDisabled) {
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, true)}));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddInvalidResource(XdsFooResourceType::Get()->type_url(),
                              "{\"name\":\"foo1\",\"value\":[]}")
          .Serialize());

  auto error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "invalid resource: errors validating JSON: "
            "[field:value error:is not a number] (node ID:xds_client_test)")
      << *error;

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "nacked_but_cached"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceEq(
                  ClientResourceStatus::NACKED,
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  CsdsResourceFields(resource->AsJsonString(), "1",
                                     TimestampProtoEq(kTime0)),
                  CsdsErrorFields("invalid resource: errors validating JSON: "
                                  "[field:value error:is not a number]",
                                  "2", TimestampProtoEq(kTime1)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(
      *request, XdsFooResourceType::Get()->type_url(),
      "1", "B",

      absl::InvalidArgumentError(
          "xDS response validation errors: ["
          "resource index 0: foo1: INVALID_ARGUMENT: errors validating JSON: "
          "[field:value error:is not a number]]"),
      {"foo1"});

  auto watcher2 = StartFooWatch("foo1");
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(
      *error,
      absl::InvalidArgumentError(
          "invalid resource: errors validating JSON: "
          "[field:value error:is not a number] (node ID:xds_client_test)"));

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceErrorFromServer) {
  testing::ScopedExperimentalEnvVar env_var(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitXdsClient();

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddResourceError("foo1", absl::PermissionDeniedError("nope"))
          .Serialize());

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::PermissionDeniedError("nope (node ID:xds_client_test)"));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "received_error"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::RECEIVED_ERROR,
          XdsFooResourceType::Get()->type_url(), "foo1", CsdsNoResourceFields(),
          CsdsErrorFields("nope", "1", TimestampProtoEq(kTime0)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("3")
          .set_nonce("C")
          .AddResourceError("foo1", absl::PermissionDeniedError("bzzt"))
          .Serialize());

  error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::PermissionDeniedError("bzzt (node ID:xds_client_test)"));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "received_error_but_cached"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceEq(
                  ClientResourceStatus::RECEIVED_ERROR,
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  CsdsResourceFields(resource->AsJsonString(), "2",
                                     TimestampProtoEq(kTime1)),
                  CsdsErrorFields("bzzt", "3", TimestampProtoEq(kTime2)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "3", "C",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
}

TEST_F(XdsClientTest, ResourceErrorFromServerWithFailOnDataErrors) {
  testing::ScopedExperimentalEnvVar env_var(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, true)}));

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddResourceError("foo1", absl::PermissionDeniedError("nope"))
          .Serialize());

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::PermissionDeniedError("nope (node ID:xds_client_test)"));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "received_error"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::RECEIVED_ERROR,
          XdsFooResourceType::Get()->type_url(), "foo1", CsdsNoResourceFields(),
          CsdsErrorFields("nope", "1", TimestampProtoEq(kTime0)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("3")
          .set_nonce("C")
          .AddResourceError("foo1", absl::PermissionDeniedError("bzzt"))
          .Serialize());

  error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::PermissionDeniedError("bzzt (node ID:xds_client_test)"));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "received_error"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::RECEIVED_ERROR,
          XdsFooResourceType::Get()->type_url(), "foo1", CsdsNoResourceFields(),
          CsdsErrorFields("bzzt", "3", TimestampProtoEq(kTime2)))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "3", "C",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::_));
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
}

TEST_F(XdsClientTest, ResourceErrorFromServerIgnoredIfNotEnabled) {
  InitXdsClient();

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddResourceError("foo1", absl::PermissionDeniedError("nope"))
          .Serialize());

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "2", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
}

TEST_F(XdsClientTest, WildcardCapableResponseWithEmptyResource) {
  InitXdsClient();

  auto watcher = StartWildcardCapableWatch("wc1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"wc1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddWildcardCapableResource(XdsWildcardCapableResource("wc1", 6))
          .AddEmptyResource()
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(
              XdsClient::kOldStyleAuthority,
              XdsWildcardCapableResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "1", "A",

               absl::InvalidArgumentError(absl::StrCat(
                   "xDS response validation errors: ["
                   "resource index 1: incorrect resource type \"\" "
                   "(should be \"",
                   XdsWildcardCapableResourceType::Get()->type_url(), "\")]")),
               {"wc1"});

  CancelWildcardCapableWatch(watcher.get(), "wc1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceDeletionWithFailOnDataErrors) {
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, true)}));

  auto watcher = StartWildcardCapableWatch("wc1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"wc1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddWildcardCapableResource(XdsWildcardCapableResource("wc1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(
              XdsClient::kOldStyleAuthority,
              XdsWildcardCapableResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"wc1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .Serialize());

  EXPECT_TRUE(watcher->WaitForDoesNotExist());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(
                      XdsClient::kOldStyleAuthority,
                      XdsWildcardCapableResourceType::Get()->type_url(),
                      "does_not_exist"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::DOES_NOT_EXIST,
          XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
          CsdsNoResourceFields(),
          CsdsErrorFields("does not exist", "2", TimestampProtoEq(kTime1)))));

  auto watcher2 = StartWildcardCapableWatch("wc1");
  EXPECT_TRUE(watcher2->WaitForDoesNotExist());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"wc1"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("3")
          .set_nonce("C")
          .AddWildcardCapableResource(XdsWildcardCapableResource("wc1", 7))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 7);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(
              XdsClient::kOldStyleAuthority,
              XdsWildcardCapableResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
                  resource->AsJsonString(), "3", TimestampProtoEq(kTime2))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "3", "C",
               absl::OkStatus(),
               {"wc1"});

  CancelWildcardCapableWatch(watcher.get(), "wc1");
  CancelWildcardCapableWatch(watcher2.get(), "wc1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceDeletionIgnoredByDefault) {
  InitXdsClient();

  auto watcher = StartWildcardCapableWatch("wc1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"wc1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddWildcardCapableResource(XdsWildcardCapableResource("wc1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(
              XdsClient::kOldStyleAuthority,
              XdsWildcardCapableResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"wc1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .Serialize());

  auto error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::NotFoundError("does not exist (node ID:xds_client_test)"));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(
                      XdsClient::kOldStyleAuthority,
                      XdsWildcardCapableResourceType::Get()->type_url(),
                      "does_not_exist_but_cached"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::DOES_NOT_EXIST,
          XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
          CsdsResourceFields(resource->AsJsonString(), "1",
                             TimestampProtoEq(kTime0)),
          CsdsErrorFields("does not exist", "2", TimestampProtoEq(kTime1)))));

  auto watcher2 = StartWildcardCapableWatch("wc1");
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 6);
  error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error,
            absl::NotFoundError("does not exist (node ID:xds_client_test)"));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"wc1"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsWildcardCapableResourceType::Get()->type_url())
          .set_version_info("3")
          .set_nonce("C")
          .AddWildcardCapableResource(XdsWildcardCapableResource("wc1", 7))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 7);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "wc1");
  EXPECT_EQ(resource->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsWildcardCapableResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(
              XdsClient::kOldStyleAuthority,
              XdsWildcardCapableResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsWildcardCapableResourceType::Get()->type_url(), "wc1",
                  resource->AsJsonString(), "3", TimestampProtoEq(kTime2))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsWildcardCapableResourceType::Get()->type_url(),
               "3", "C",
               absl::OkStatus(),
               {"wc1"});

  CancelWildcardCapableWatch(watcher.get(), "wc1");
  CancelWildcardCapableWatch(watcher2.get(), "wc1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, StreamClosedByServer) {
  InitXdsClient();

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  stream->MaybeSendStatusToClient(absl::OkStatus());

  EXPECT_TRUE(stream->IsOrphaned());

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  auto watcher2 = StartFooWatch("foo1");
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  EXPECT_FALSE(watcher->WaitForNextResource());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, StreamClosedByServerWithoutSeeingResponse) {
  InitXdsClient();

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));
  EXPECT_THAT(metrics_reporter_->server_failures(), ::testing::ElementsAre());

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->MaybeSendStatusToClient(absl::UnavailableError("ugh"));

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: xDS call failed "
            "with no responses received; status: UNAVAILABLE: ugh "
            "(node ID:xds_client_test)")
      << *error;

  stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ConnectionFails) {
  InitXdsClient();

  transport_factory_->SetAutoCompleteMessagesFromClient(false);

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->server_failures(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  TriggerConnectionFailure(*xds_client_->bootstrap().servers().front(),
                           absl::UnavailableError("connection failed"));

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: "
            "connection failed (node ID:xds_client_test)")
      << *error;

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  EXPECT_TRUE(watcher->ExpectNoEvent());

  auto watcher2 = StartFooWatch("foo1");
  error = watcher2->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: "
            "connection failed (node ID:xds_client_test)")
      << *error;

  EXPECT_FALSE(watcher2->HasEvent());

  stream->CompleteSendMessageFromClient();

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});
  stream->CompleteSendMessageFromClient();

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ConnectionFailsWithCachedResource) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  TriggerConnectionFailure(*xds_client_->bootstrap().servers().front(),
                           absl::UnavailableError("connection failed"));

  auto error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: "
            "connection failed (node ID:xds_client_test)")
      << *error;

  stream->MaybeSendStatusToClient(absl::UnavailableError("ugh"));

  stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  auto watcher2 = StartFooWatch("foo1");
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: "
            "connection failed (node ID:xds_client_test)")
      << *error;

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error, absl::OkStatus());
  error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(*error, absl::OkStatus());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceDoesNotExistUponTimeout) {
  event_engine_->SetRunAfterDurationCallback(
      [&](grpc_event_engine::experimental::EventEngine::Duration duration) {
        grpc_event_engine::experimental::EventEngine::Duration expected =
            std::chrono::seconds(15);
        EXPECT_EQ(duration, expected) << "Expected: " << expected.count()
                                      << "\nActual:   " << duration.count();
      });
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  EXPECT_TRUE(watcher->WaitForDoesNotExist());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "does_not_exist"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceDoesNotExistOnTimeout(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto watcher2 = StartFooWatch("foo1");
  EXPECT_TRUE(watcher2->WaitForDoesNotExist());

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceTimerIsTransientErrorIgnoredUnlessEnabled) {
  event_engine_->SetRunAfterDurationCallback(
      [&](grpc_event_engine::experimental::EventEngine::Duration duration) {
        grpc_event_engine::experimental::EventEngine::Duration expected =
            std::chrono::seconds(15);
        EXPECT_EQ(duration, expected) << "Expected: " << expected.count()
                                      << "\nActual:   " << duration.count();
      });
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, false, true)}));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  EXPECT_TRUE(watcher->WaitForDoesNotExist());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "does_not_exist"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceDoesNotExistOnTimeout(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto watcher2 = StartFooWatch("foo1");
  EXPECT_TRUE(watcher2->WaitForDoesNotExist());

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceTimerIsTransientFailure) {
  testing::ScopedExperimentalEnvVar env_var(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  event_engine_->SetRunAfterDurationCallback(
      [&](grpc_event_engine::experimental::EventEngine::Duration duration) {
        grpc_event_engine::experimental::EventEngine::Duration expected =
            std::chrono::seconds(30);
        EXPECT_EQ(duration, expected) << "Expected: " << expected.count()
                                      << "\nActual:   " << duration.count();
      });
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {FakeXdsBootstrap::FakeXdsServer(kDefaultXdsServerUrl, false, true)}));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error, absl::UnavailableError(absl::StrCat(
                       "timeout obtaining resource from xDS server ",
                       kDefaultXdsServerUrl, " (node ID:xds_client_test)")));

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "timeout"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(CsdsResourceEq(
          ClientResourceStatus::TIMEOUT, XdsFooResourceType::Get()->type_url(),
          "foo1", CsdsNoResourceFields(),
          CsdsErrorDetailsOnly(
              absl::StrCat("timeout obtaining resource from xDS server ",
                           kDefaultXdsServerUrl)))));

  auto watcher2 = StartFooWatch("foo1");
  error = watcher2->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error, absl::UnavailableError(absl::StrCat(
                       "timeout obtaining resource from xDS server ",
                       kDefaultXdsServerUrl, " (node ID:xds_client_test)")));

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  resource = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  CancelFooWatch(watcher2.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceDoesNotExistAfterStreamRestart) {
  InitXdsClient();

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->MaybeSendStatusToClient(absl::UnavailableError("ugh"));

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: xDS call failed "
            "with no responses received; status: UNAVAILABLE: ugh "
            "(node ID:xds_client_test)")
      << *error;

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  ASSERT_TRUE(watcher->WaitForDoesNotExist());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(), ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "does_not_exist"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceDoesNotExistOnTimeout(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, DoesNotExistTimerNotStartedUntilSendCompletes) {
  InitXdsClient();

  transport_factory_->SetAutoCompleteMessagesFromClient(false);

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  EXPECT_TRUE(watcher->ExpectNoEvent());

  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  stream->CompleteSendMessageFromClient();

  EXPECT_TRUE(watcher->WaitForDoesNotExist());

  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "does_not_exist"),
                  1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceDoesNotExistOnTimeout(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});
  stream->CompleteSendMessageFromClient();

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest,
       ResourceDoesNotExistUnsubscribeAndResubscribeWhileSendMessagePending) {
  InitXdsClient();

  transport_factory_->SetAutoCompleteMessagesFromClient(false);

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);
  stream->CompleteSendMessageFromClient();

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});
  stream->CompleteSendMessageFromClient();

  auto watcher2 = StartFooWatch("foo2");

  EXPECT_FALSE(watcher2->HasEvent());

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                    XdsFooResourceType::Get()->type_url(),
                                    "requested"),
              1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                        "foo2")));

  // NOTE: We do NOT yet tell the XdsClient that the send_message op is

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));
  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo2")));

  watcher = StartFooWatch("foo1");
  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                    XdsFooResourceType::Get()->type_url(),
                                    "requested"),
              1)));
  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                        "foo2")));

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .AddFooResource(XdsFooResource("foo2", 7))
          .Serialize());

  EXPECT_TRUE(watcher->ExpectNoEvent());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          3)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  stream->CompleteSendMessageFromClient();

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});
  stream->CompleteSendMessageFromClient();

  EXPECT_TRUE(watcher->ExpectNoEvent());

  CancelFooWatch(watcher.get(), "foo1", true);
  CancelFooWatch(watcher2.get(), "foo2");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, DoNotSendDoesNotExistForCachedResource) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  stream->MaybeSendStatusToClient(absl::UnavailableError("connection failed"));

  stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  EXPECT_TRUE(watcher->ExpectNoEvent());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  EXPECT_TRUE(watcher->ExpectNoEvent());

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, UnsubscribeAndResubscribeRace) {
  InitXdsClient();

  transport_factory_->SetAutoCompleteMessagesFromClient(false);

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);
  stream->CompleteSendMessageFromClient();

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});
  stream->CompleteSendMessageFromClient();

  auto watcher2 = StartFooWatch("foo2");

  EXPECT_FALSE(watcher2->HasEvent());

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                    XdsFooResourceType::Get()->type_url(),
                                    "requested"),
              1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                        "foo2")));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});
  stream->CompleteSendMessageFromClient();

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 6))
          .AddFooResource(XdsFooResource("foo2", 7))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 7);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          3)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  // NOTE: We do NOT yet tell the XdsClient that the send_message op is

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo2",
                  resource2->AsJsonString(), "1", TimestampProtoEq(kTime1))));

  watcher = StartFooWatch("foo1");
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));
  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "1",
                                    TimestampProtoEq(kTime1))));

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  stream->CompleteSendMessageFromClient();

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});
  stream->CompleteSendMessageFromClient();

  EXPECT_TRUE(watcher->ExpectNoEvent());

  CancelFooWatch(watcher.get(), "foo1", true);
  CancelFooWatch(watcher2.get(), "foo2");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, ResourceWrappedInResourceMessage) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6),
                          true)
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, MultipleResourceTypes) {
  InitXdsClient();

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartBarWatch("bar1");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsBarResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"bar1"});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsBarResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddBarResource(XdsBarResource("bar1", "whee"))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource2->name, "bar1");
  EXPECT_EQ(resource2->value, "whee");

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsBarResourceType::Get()->type_url()),
              1),
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsFooResourceType::Get()->type_url()),
              1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::UnorderedElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsBarResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceAcked(XdsBarResourceType::Get()->type_url(),
                                    "bar1", resource2->AsJsonString(), "2",
                                    TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsBarResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"bar1"});

  CancelFooWatch(watcher.get(), "foo1");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(), {});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("C")
          .Serialize());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "C",
               absl::OkStatus(), {});

  watcher = StartFooWatch("foo2");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "C",
               absl::OkStatus(), {"foo2"});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("D")
          .AddFooResource(XdsFooResource("foo2", 8))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo2");
  EXPECT_EQ(resource->value, 8);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "D",
               absl::OkStatus(), {"foo2"});

  CancelFooWatch(watcher.get(), "foo2", true);
  CancelBarWatch(watcher2.get(), "bar1");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, Federation) {
  constexpr char kAuthority[] = "xds.example.com";
  const std::string kXdstpResourceName = absl::StrCat(
      "xdstp://", kAuthority, "/", XdsFooResource::TypeUrl(), "/foo2");
  FakeXdsBootstrap::FakeXdsServer authority_server("other_xds_server");
  FakeXdsBootstrap::FakeAuthority authority;
  authority.set_server(authority_server);
  InitXdsClient(
      FakeXdsBootstrap::Builder().AddAuthority(kAuthority, authority));

  EXPECT_THAT(metrics_reporter_->resource_updates_valid(),
              ::testing::ElementsAre());
  EXPECT_THAT(metrics_reporter_->resource_updates_invalid(),
              ::testing::ElementsAre());
  EXPECT_THAT(GetResourceCounts(), ::testing::ElementsAre());
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre());

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream(*xds_client_->bootstrap().servers().front());
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch(kXdstpResourceName);

  EXPECT_FALSE(watcher2->HasEvent());

  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(ResourceCountLabelsEq(
                              kAuthority, XdsFooResourceType::Get()->type_url(),
                              "requested"),
                          1)));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, true),
          ::testing::Pair(authority_server.target()->server_uri(), true)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "1",
                                    TimestampProtoEq(kTime0)),
                  CsdsResourceRequested(XdsFooResourceType::Get()->type_url(),
                                        kXdstpResourceName)));

  auto stream2 = WaitForAdsStream(authority_server);
  ASSERT_TRUE(stream2 != nullptr);

  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {kXdstpResourceName});
  CheckRequestNode(*request);

  time_cache_.TestOnlySetNow(kTime1);
  stream2->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource(kXdstpResourceName, 3))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, kXdstpResourceName);
  EXPECT_EQ(resource2->value, 3);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsFooResourceType::Get()->type_url()),
              1),
          ::testing::Pair(
              ::testing::Pair(authority_server.target()->server_uri(),
                              XdsFooResourceType::Get()->type_url()),
              1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(
                  kAuthority, XdsFooResourceType::Get()->type_url(), "acked"),
              1)));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, true),
          ::testing::Pair(authority_server.target()->server_uri(), true)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(), "foo1",
                            resource->AsJsonString(), "1",
                            TimestampProtoEq(kTime0)),
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                            kXdstpResourceName, resource2->AsJsonString(), "2",
                            TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {kXdstpResourceName});

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  CancelFooWatch(watcher2.get(), kXdstpResourceName);
  EXPECT_TRUE(stream2->IsOrphaned());
}

TEST_F(XdsClientTest, FederationAuthorityDefaultsToTopLevelXdsServer) {
  constexpr char kAuthority[] = "xds.example.com";
  const std::string kXdstpResourceName = absl::StrCat(
      "xdstp://", kAuthority, "/", XdsFooResource::TypeUrl(), "/foo2");

  InitXdsClient(FakeXdsBootstrap::Builder().AddAuthority(
      kAuthority, FakeXdsBootstrap::FakeAuthority()));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream(*xds_client_->bootstrap().servers().front());
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch(kXdstpResourceName);

  EXPECT_FALSE(watcher2->HasEvent());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", kXdstpResourceName});

  time_cache_.TestOnlySetNow(kTime1);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource(kXdstpResourceName, 3))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, kXdstpResourceName);
  EXPECT_EQ(resource2->value, 3);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          2)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(
                  kAuthority, XdsFooResourceType::Get()->type_url(), "acked"),
              1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(), "foo1",
                            resource->AsJsonString(), "1",
                            TimestampProtoEq(kTime0)),
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                            kXdstpResourceName, resource2->AsJsonString(), "2",
                            TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1", kXdstpResourceName});

  CancelFooWatch(watcher.get(), "foo1");

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {kXdstpResourceName});

  CancelFooWatch(watcher2.get(), kXdstpResourceName);
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, FederationWithUnknownAuthority) {
  constexpr char kAuthority[] = "xds.example.com";
  const std::string kXdstpResourceName = absl::StrCat(
      "xdstp://", kAuthority, "/", XdsFooResource::TypeUrl(), "/foo2");
  // Note: Not adding authority to bootstrap config.
  InitXdsClient();

  auto watcher = StartFooWatch(kXdstpResourceName);

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kFailedPrecondition);
  EXPECT_EQ(error->message(),
            "authority \"xds.example.com\" not present in bootstrap config "
            "(node ID:xds_client_test)")
      << *error;
}

TEST_F(XdsClientTest, FederationWithUnparseableXdstpResourceName) {
  // Note: Not adding authority to bootstrap config.
  InitXdsClient();

  auto watcher = StartFooWatch("xdstp://x");

  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(error->message(),
            "Unable to parse resource name xdstp://x "
            "(node ID:xds_client_test)")
      << *error;
}

TEST_F(XdsClientTest, FederationDisabledWithNewStyleName) {
  testing::ScopedEnvVar env_var("GRPC_EXPERIMENTAL_XDS_FEDERATION", "false");

  constexpr char kXdstpResourceName[] =
      "xdstp://xds.example.com/test.v3.foo/foo1";
  InitXdsClient();

  auto watcher = StartFooWatch(kXdstpResourceName);

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {kXdstpResourceName});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource(kXdstpResourceName, 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, kXdstpResourceName);
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {kXdstpResourceName});

  CancelFooWatch(watcher.get(), kXdstpResourceName);
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, FederationChannelFailureReportedToWatchers) {
  constexpr char kAuthority[] = "xds.example.com";
  const std::string kXdstpResourceName = absl::StrCat(
      "xdstp://", kAuthority, "/", XdsFooResource::TypeUrl(), "/foo2");
  FakeXdsBootstrap::FakeXdsServer authority_server("other_xds_server");
  FakeXdsBootstrap::FakeAuthority authority;
  authority.set_server(authority_server);
  InitXdsClient(
      FakeXdsBootstrap::Builder().AddAuthority(kAuthority, authority));

  auto watcher = StartFooWatch("foo1");

  EXPECT_FALSE(watcher->HasEvent());

  auto stream = WaitForAdsStream(*xds_client_->bootstrap().servers().front());
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  CheckRequestNode(*request);

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "1", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  auto watcher2 = StartFooWatch(kXdstpResourceName);

  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, true),
          ::testing::Pair(authority_server.target()->server_uri(), true)));

  EXPECT_FALSE(watcher2->HasEvent());

  auto stream2 = WaitForAdsStream(authority_server);
  ASSERT_TRUE(stream2 != nullptr);

  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {kXdstpResourceName});
  CheckRequestNode(*request);

  time_cache_.TestOnlySetNow(kTime1);
  stream2->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource(kXdstpResourceName, 3))
          .Serialize());

  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, kXdstpResourceName);
  EXPECT_EQ(resource2->value, 3);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsFooResourceType::Get()->type_url()),
              1),
          ::testing::Pair(
              ::testing::Pair(authority_server.target()->server_uri(),
                              XdsFooResourceType::Get()->type_url()),
              1)),
      ::testing::ElementsAre(), ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(
          ::testing::Pair(ResourceCountLabelsEq(
                              XdsClient::kOldStyleAuthority,
                              XdsFooResourceType::Get()->type_url(), "acked"),
                          1),
          ::testing::Pair(
              ResourceCountLabelsEq(
                  kAuthority, XdsFooResourceType::Get()->type_url(), "acked"),
              1)));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, true),
          ::testing::Pair(authority_server.target()->server_uri(), true)));

  csds = DumpCsds();
  EXPECT_THAT(
      csds.generic_xds_configs(),
      ::testing::UnorderedElementsAre(
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(), "foo1",
                            resource->AsJsonString(), "1",
                            TimestampProtoEq(kTime0)),
          CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                            kXdstpResourceName, resource2->AsJsonString(), "2",
                            TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {kXdstpResourceName});

  TriggerConnectionFailure(authority_server,
                           absl::UnavailableError("connection failed"));

  auto error = watcher2->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server other_xds_server: connection failed "
            "(node ID:xds_client_test)")
      << *error;

  EXPECT_FALSE(watcher->HasEvent());

  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, true),
          ::testing::Pair(authority_server.target()->server_uri(), false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(
          ::testing::Pair(authority_server.target()->server_uri(), 1))));

  CancelFooWatch(watcher.get(), "foo1");
  EXPECT_TRUE(stream->IsOrphaned());

  CancelFooWatch(watcher2.get(), kXdstpResourceName);
  EXPECT_TRUE(stream2->IsOrphaned());
}

TEST_F(XdsClientTest, AdsReadWaitsForHandleRelease) {
  InitXdsClient();

  auto watcher1 = StartFooWatch("foo1");

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  auto watcher2 = StartFooWatch("foo2");
  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1", "foo2"});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .AddFooResource(XdsFooResource("foo2", 10))
          .Serialize());

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("2")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 8))
          .Serialize());

  auto resource1 = watcher1->WaitForNextResourceAndHandle();
  ASSERT_NE(resource1, std::nullopt);
  EXPECT_EQ(resource1->resource->name, "foo1");
  EXPECT_EQ(resource1->resource->value, 6);
  auto resource2 = watcher2->WaitForNextResourceAndHandle();
  ASSERT_NE(resource2, std::nullopt);
  EXPECT_EQ(resource2->resource->name, "foo2");
  EXPECT_EQ(resource2->resource->value, 10);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});
  EXPECT_TRUE(stream->WaitForReadsStarted(1));
  resource1->read_delay_handle.reset();
  EXPECT_TRUE(stream->WaitForReadsStarted(1));
  resource2->read_delay_handle.reset();
  EXPECT_TRUE(stream->WaitForReadsStarted(2));
  resource1 = watcher1->WaitForNextResourceAndHandle();
  ASSERT_NE(resource1, std::nullopt);
  EXPECT_EQ(resource1->resource->name, "foo1");
  EXPECT_EQ(resource1->resource->value, 8);
  EXPECT_EQ(watcher2->WaitForNextResourceAndHandle(), std::nullopt);

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});
  EXPECT_TRUE(stream->WaitForReadsStarted(2));
  resource1->read_delay_handle.reset();
  EXPECT_TRUE(stream->WaitForReadsStarted(3));

  CancelFooWatch(watcher1.get(), "foo1");
  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "2", "B",
               absl::OkStatus(),
               {"foo2"});
  CancelFooWatch(watcher2.get(), "foo2");
  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, FallbackAndRecover) {
  FakeXdsBootstrap::FakeXdsServer primary_server(kDefaultXdsServerUrl);
  FakeXdsBootstrap::FakeXdsServer fallback_server("fallback_xds_server");

  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {primary_server, fallback_server}));

  auto watcher = StartFooWatch("foo1");
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::IsEmpty(), ::testing::_, ::testing::ElementsAre()));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});

  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("20")
          .set_nonce("O")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(::testing::Pair(
          ::testing::Pair(kDefaultXdsServerUrl,
                          XdsFooResourceType::Get()->type_url()),
          1)),
      ::testing::_, ::testing::_));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          1)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(CsdsResourceAcked(
                  XdsFooResourceType::Get()->type_url(), "foo1",
                  resource->AsJsonString(), "20", TimestampProtoEq(kTime0))));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "20", "O",
               absl::OkStatus(),
               {"foo1"});

  TriggerConnectionFailure(primary_server,
                           absl::UnavailableError("Server down"));

  auto error = watcher->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: Server down (node "
            "ID:xds_client_test)");

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  stream->MaybeSendStatusToClient(absl::UnavailableError("Stream failure"));

  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  stream = WaitForAdsStream();
  ASSERT_NE(stream, nullptr);
  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "20", "",
               absl::OkStatus(),
               {"foo1"});

  auto watcher_cached = StartFooWatch("foo1");

  resource = watcher_cached->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  error = watcher_cached->WaitForNextAmbientError();
  ASSERT_TRUE(error.has_value());
  EXPECT_EQ(error->message(),
            "xDS channel for server default_xds_server: Server down (node "
            "ID:xds_client_test)")
      << error->message();
  CancelFooWatch(watcher_cached.get(), "foo1");

  auto watcher2 = StartFooWatch("foo2");

  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, false),
          ::testing::Pair(fallback_server.target()->server_uri(), true)));

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "20", "",
               absl::OkStatus(),
               {"foo1", "foo2"});

  auto stream2 = WaitForAdsStream(fallback_server);
  ASSERT_TRUE(stream2 != nullptr);
  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1", "foo2"});

  time_cache_.TestOnlySetNow(kTime1);
  stream2->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("5")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 20))
          .AddFooResource(XdsFooResource("foo2", 30))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 20);
  auto resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 30);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsFooResourceType::Get()->type_url()),
              1),
          ::testing::Pair(
              ::testing::Pair(fallback_server.target()->server_uri(),
                              XdsFooResourceType::Get()->type_url()),
              2)),
      ::testing::_, ::testing::_));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, false),
          ::testing::Pair(fallback_server.target()->server_uri(), true)));
  EXPECT_THAT(
      GetResourceCounts(),
      ::testing::ElementsAre(::testing::Pair(
          ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                XdsFooResourceType::Get()->type_url(), "acked"),
          2)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "5",
                                    TimestampProtoEq(kTime1)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "5",
                                    TimestampProtoEq(kTime1))));

  request = WaitForRequest(stream2.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "5", "A",
               absl::OkStatus(),
               {"foo1", "foo2"});

  time_cache_.TestOnlySetNow(kTime2);
  stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("15")
          .set_nonce("B")
          .AddFooResource(XdsFooResource("foo1", 35))
          .AddFooResource(XdsFooResource("foo2", 25))
          .Serialize());

  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 35);
  resource2 = watcher2->WaitForNextResource();
  ASSERT_NE(resource2, nullptr);
  EXPECT_EQ(resource2->name, "foo2");
  EXPECT_EQ(resource2->value, 25);

  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::ElementsAre(
          ::testing::Pair(
              ::testing::Pair(kDefaultXdsServerUrl,
                              XdsFooResourceType::Get()->type_url()),
              3),
          ::testing::Pair(
              ::testing::Pair(fallback_server.target()->server_uri(),
                              XdsFooResourceType::Get()->type_url()),
              2)),
      ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));

  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::UnorderedElementsAre(
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo1", resource->AsJsonString(), "15",
                                    TimestampProtoEq(kTime2)),
                  CsdsResourceAcked(XdsFooResourceType::Get()->type_url(),
                                    "foo2", resource2->AsJsonString(), "15",
                                    TimestampProtoEq(kTime2))));

  EXPECT_TRUE(stream2->IsOrphaned());

  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "15", "B",
               absl::OkStatus(),
               {"foo1", "foo2"});

  CancelFooWatch(watcher.get(), "foo1", true);
  CancelFooWatch(watcher2.get(), "foo2");

  EXPECT_TRUE(stream->IsOrphaned());
}

TEST_F(XdsClientTest, FallbackReportsError) {
  FakeXdsBootstrap::FakeXdsServer primary_server(kDefaultXdsServerUrl);
  FakeXdsBootstrap::FakeXdsServer fallback_server("fallback_xds_server");
  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {primary_server, fallback_server}));
  auto watcher = StartFooWatch("foo1");
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));
  auto stream = WaitForAdsStream();
  ASSERT_TRUE(stream != nullptr);

  auto request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  EXPECT_THAT(GetResourceCounts(),
              ::testing::ElementsAre(::testing::Pair(
                  ResourceCountLabelsEq(XdsClient::kOldStyleAuthority,
                                        XdsFooResourceType::Get()->type_url(),
                                        "requested"),
                  1)));
  TriggerConnectionFailure(primary_server,
                           absl::UnavailableError("Server down"));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, false),
          ::testing::Pair(fallback_server.target()->server_uri(), true)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  ClientConfig csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));

  stream = WaitForAdsStream(fallback_server);
  ASSERT_NE(stream, nullptr);
  request = WaitForRequest(stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  TriggerConnectionFailure(fallback_server,
                           absl::UnavailableError("Another server down"));
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, false),
          ::testing::Pair(fallback_server.target()->server_uri(), false)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, 1),
          ::testing::Pair(fallback_server.target()->server_uri(), 1))));
  csds = DumpCsds();
  EXPECT_THAT(csds.generic_xds_configs(),
              ::testing::ElementsAre(CsdsResourceRequested(
                  XdsFooResourceType::Get()->type_url(), "foo1")));
  auto error = watcher->WaitForNextError();
  ASSERT_TRUE(error.has_value());
  EXPECT_THAT(error->code(), absl::StatusCode::kUnavailable);
  EXPECT_EQ(error->message(),
            "xDS channel for server fallback_xds_server: Another server down "
            "(node ID:xds_client_test)")
      << error->message();
}

TEST_F(XdsClientTest, FallbackOnStartup) {
  FakeXdsBootstrap::FakeXdsServer primary_server;
  FakeXdsBootstrap::FakeXdsServer fallback_server("fallback_xds_server");

  InitXdsClient(FakeXdsBootstrap::Builder().SetServers(
      {primary_server, fallback_server}));

  auto watcher = StartFooWatch("foo1");
  auto primary_stream = WaitForAdsStream(primary_server);
  ASSERT_NE(primary_stream, nullptr);

  auto request = WaitForRequest(primary_stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});
  TriggerConnectionFailure(primary_server,
                           absl::UnavailableError("Primary server is down"));

  auto fallback_stream = WaitForAdsStream(fallback_server);
  ASSERT_NE(fallback_stream, nullptr);

  request = WaitForRequest(fallback_stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "", "",
               absl::OkStatus(),
               {"foo1"});

  fallback_stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("1")
          .set_nonce("A")
          .AddFooResource(XdsFooResource("foo1", 6))
          .Serialize());
  EXPECT_THAT(
      GetServerConnections(),
      ::testing::ElementsAre(
          ::testing::Pair(kDefaultXdsServerUrl, false),
          ::testing::Pair(fallback_server.target()->server_uri(), true)));
  EXPECT_TRUE(metrics_reporter_->WaitForMetricsReporterData(
      ::testing::_, ::testing::_,
      ::testing::ElementsAre(::testing::Pair(kDefaultXdsServerUrl, 1))));

  auto resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 6);

  request = WaitForRequest(fallback_stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "1", "A",
               absl::OkStatus(),
               {"foo1"});

  primary_stream->SendMessageToClient(
      ResponseBuilder(XdsFooResourceType::Get()->type_url())
          .set_version_info("5")
          .set_nonce("D")
          .AddFooResource(XdsFooResource("foo1", 42))
          .Serialize());
  EXPECT_TRUE(fallback_stream->IsOrphaned());
  resource = watcher->WaitForNextResource();
  ASSERT_NE(resource, nullptr);
  EXPECT_EQ(resource->name, "foo1");
  EXPECT_EQ(resource->value, 42);
  EXPECT_THAT(GetServerConnections(), ::testing::ElementsAre(::testing::Pair(
                                          kDefaultXdsServerUrl, true)));
  request = WaitForRequest(primary_stream.get());
  ASSERT_TRUE(request.has_value());
  CheckRequest(*request, XdsFooResourceType::Get()->type_url(),
               "5", "D",
               absl::OkStatus(),
               {"foo1"});
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
