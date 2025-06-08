Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Require necessary libraries for gRPC and Protocol Buffers
require 'grpc'
require 'google/protobuf/empty'
require 'tech/pubsub/proto/pubsub'

module Tech
  module Pubsub
    # PublisherService module defines the gRPC service for topic management and message publishing
    module PublisherService
      # Service class implementing the PublisherService RPC methods
      class Service
        include GRPC::GenericService  # Include GRPC generic service functionality

        # Configuration for message serialization/deserialization
        self.marshal_class_method = :encode  # Method used to encode messages
        self.unmarshal_class_method = :decode  # Method used to decode messages
        self.service_name = 'tech.pubsub.PublisherService'  # Full service name for gRPC

        # RPC method definitions:
        # Each rpc defines a method name, input type, and output type
        
        # Creates a new topic
        rpc :CreateTopic, Topic, Topic
        
        # Publishes a message to a topic
        rpc :Publish, PublishRequest, Google::Protobuf::Empty
        
        # Publishes multiple messages to a topic in a single batch
        rpc :PublishBatch, PublishBatchRequest, PublishBatchResponse
        
        # Retrieves information about a specific topic
        rpc :GetTopic, GetTopicRequest, Topic
        
        # Lists topics in the system
        rpc :ListTopics, ListTopicsRequest, ListTopicsResponse
        
        # Deletes a topic
        rpc :DeleteTopic, DeleteTopicRequest, Google::Protobuf::Empty
      end

      # Stub class for client-side communication with the PublisherService
      Stub = Service.rpc_stub_class
    end

    # SubscriberService module defines the gRPC service for subscription management
    module SubscriberService
      # Service class implementing the SubscriberService RPC methods
      class Service
        include GRPC::GenericService  # Include GRPC generic service functionality

        # Configuration for message serialization/deserialization
        self.marshal_class_method = :encode  # Method used to encode messages
        self.unmarshal_class_method = :decode  # Method used to decode messages
        self.service_name = 'tech.pubsub.SubscriberService'  # Full service name for gRPC

        # RPC method definitions:
        # Each rpc defines a method name, input type, and output type
        
        # Creates a new subscription
        rpc :CreateSubscription, Subscription, Subscription
        
        # Retrieves information about a specific subscription
        rpc :GetSubscription, GetSubscriptionRequest, Subscription
        
        # Lists subscriptions in the system
        rpc :ListSubscriptions, ListSubscriptionsRequest, ListSubscriptionsResponse
        
        # Deletes a subscription
        rpc :DeleteSubscription, DeleteSubscriptionRequest, Google::Protobuf::Empty
        
        # Truncates all messages in a subscription
        rpc :TruncateSubscription, TruncateSubscriptionRequest, Google::Protobuf::Empty
        
        # Modifies the push configuration for a subscription
        rpc :ModifyPushConfig, ModifyPushConfigRequest, Google::Protobuf::Empty
        
        # Pulls a single message from a subscription
        rpc :Pull, PullRequest, PullResponse
        
        # Pulls multiple messages from a subscription in a single batch
        rpc :PullBatch, PullBatchRequest, PullBatchResponse
        
        # Modifies the acknowledgment deadline for messages
        rpc :ModifyAckDeadline, ModifyAckDeadlineRequest, Google::Protobuf::Empty
        
        # Acknowledges receipt of messages
        rpc :Acknowledge, AcknowledgeRequest, Google::Protobuf::Empty
        
        # Negative acknowledgment of messages (NACK)
        rpc :Nack, NackRequest, Google::Protobuf::Empty
      end

      # Stub class for client-side communication with the SubscriberService
      Stub = Service.rpc_stub_class
    end

    # PushEndpointService module defines the gRPC service for handling push notifications
    module PushEndpointService
      # Service class implementing the PushEndpointService RPC method
      class Service
        include GRPC::GenericService  # Include GRPC generic service functionality

        # Configuration for message serialization/deserialization
        self.marshal_class_method = :encode  # Method used to encode messages
        self.unmarshal_class_method = :decode  # Method used to decode messages
        self.service_name = 'tech.pubsub.PushEndpointService'  # Full service name for gRPC

        # Handles incoming pubsub events (push notifications)
        rpc :HandlePubsubEvent, PubsubEvent, Google::Protobuf::Empty
      end

      # Stub class for client-side communication with the PushEndpointService
      Stub = Service.rpc_stub_class
    end
  end
end
```