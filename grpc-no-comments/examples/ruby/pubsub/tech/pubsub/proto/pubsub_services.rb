# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'google/protobuf/empty'
require 'tech/pubsub/proto/pubsub'

module Tech
  module Pubsub
    module PublisherService

      # TODO: add proto service documentation here
      class Service

        include GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'tech.pubsub.PublisherService'

        rpc :CreateTopic, Topic, Topic
        rpc :Publish, PublishRequest, Google::Protobuf::Empty
        rpc :PublishBatch, PublishBatchRequest, PublishBatchResponse
        rpc :GetTopic, GetTopicRequest, Topic
        rpc :ListTopics, ListTopicsRequest, ListTopicsResponse
        rpc :DeleteTopic, DeleteTopicRequest, Google::Protobuf::Empty
      end

      Stub = Service.rpc_stub_class
    end
    module SubscriberService

      # TODO: add proto service documentation here
      class Service

        include GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'tech.pubsub.SubscriberService'

        rpc :CreateSubscription, Subscription, Subscription
        rpc :GetSubscription, GetSubscriptionRequest, Subscription
        rpc :ListSubscriptions, ListSubscriptionsRequest, ListSubscriptionsResponse
        rpc :DeleteSubscription, DeleteSubscriptionRequest, Google::Protobuf::Empty
        rpc :TruncateSubscription, TruncateSubscriptionRequest, Google::Protobuf::Empty
        rpc :ModifyPushConfig, ModifyPushConfigRequest, Google::Protobuf::Empty
        rpc :Pull, PullRequest, PullResponse
        rpc :PullBatch, PullBatchRequest, PullBatchResponse
        rpc :ModifyAckDeadline, ModifyAckDeadlineRequest, Google::Protobuf::Empty
        rpc :Acknowledge, AcknowledgeRequest, Google::Protobuf::Empty
        rpc :Nack, NackRequest, Google::Protobuf::Empty
      end

      Stub = Service.rpc_stub_class
    end
    module PushEndpointService

      # TODO: add proto service documentation here
      class Service

        include GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'tech.pubsub.PushEndpointService'

        rpc :HandlePubsubEvent, PubsubEvent, Google::Protobuf::Empty
      end

      Stub = Service.rpc_stub_class
    end
  end
end
