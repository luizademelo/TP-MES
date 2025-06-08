Here's the commented version of the code:

```ruby
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

# Required Google Protocol Buffers library
require 'google/protobuf'

# Required empty message type from Google Protocol Buffers
require 'google/protobuf/empty'

# Build the Protocol Buffer message definitions for the Pub/Sub service
Google::Protobuf::DescriptorPool.generated_pool.build do
  # Definition for a Topic message
  add_message "tech.pubsub.Topic" do
    optional :name, :string, 1  # Name of the topic (string)
  end

  # Definition for a PubsubMessage message
  add_message "tech.pubsub.PubsubMessage" do
    optional :data, :string, 1      # The message data payload
    optional :message_id, :string, 3 # Unique ID for the message
  end

  # Request message to get a topic
  add_message "tech.pubsub.GetTopicRequest" do
    optional :topic, :string, 1  # Name of the topic to retrieve
  end

  # Request message to publish a single message
  add_message "tech.pubsub.PublishRequest" do
    optional :topic, :string, 1                     # Topic to publish to
    optional :message, :message, 2, "tech.pubsub.PubsubMessage"  # Message to publish
  end

  # Request message to publish a batch of messages
  add_message "tech.pubsub.PublishBatchRequest" do
    optional :topic, :string, 1                              # Topic to publish to
    repeated :messages, :message, 2, "tech.pubsub.PubsubMessage"  # List of messages to publish
  end

  # Response message for batch publish
  add_message "tech.pubsub.PublishBatchResponse" do
    repeated :message_ids, :string, 1  # List of message IDs for published messages
  end

  # Request message to list topics
  add_message "tech.pubsub.ListTopicsRequest" do
    optional :query, :string, 1        # Query filter for topics
    optional :max_results, :int32, 2    # Maximum number of results to return
    optional :page_token, :string, 3    # Pagination token
  end

  # Response message for listing topics
  add_message "tech.pubsub.ListTopicsResponse" do
    repeated :topic, :message, 1, "tech.pubsub.Topic"  # List of topics
    optional :next_page_token, :string, 2              # Pagination token for next page
  end

  # Request message to delete a topic
  add_message "tech.pubsub.DeleteTopicRequest" do
    optional :topic, :string, 1  # Name of the topic to delete
  end

  # Definition for a Subscription message
  add_message "tech.pubsub.Subscription" do
    optional :name, :string, 1                                 # Name of the subscription
    optional :topic, :string, 2                                # Topic this subscription belongs to
    optional :query, :string, 3                                # Filter query for messages
    optional :truncation_policy, :message, 4, "tech.pubsub.Subscription.TruncationPolicy"  # Policy for message truncation
    optional :push_config, :message, 5, "tech.pubsub.PushConfig"  # Configuration for push delivery
    optional :ack_deadline_seconds, :int32, 6                   # Deadline for acknowledging messages
    optional :garbage_collect_seconds, :int64, 7                # Time before unacknowledged messages are garbage collected
  end

  # Definition for TruncationPolicy nested message
  add_message "tech.pubsub.Subscription.TruncationPolicy" do
    optional :max_bytes, :int64, 1       # Maximum size in bytes before truncation
    optional :max_age_seconds, :int64, 2 # Maximum age in seconds before truncation
  end

  # Definition for PushConfig message
  add_message "tech.pubsub.PushConfig" do
    optional :push_endpoint, :string, 1  # Endpoint URL for push notifications
  end

  # Definition for PubsubEvent message
  add_message "tech.pubsub.PubsubEvent" do
    optional :subscription, :string, 1                         # Subscription name
    optional :message, :message, 2, "tech.pubsub.PubsubMessage"  # The message content
    optional :truncated, :bool, 3                              # Whether message was truncated
    optional :deleted, :bool, 4                                # Whether message was deleted
  end

  # Request message to get a subscription
  add_message "tech.pubsub.GetSubscriptionRequest" do
    optional :subscription, :string, 1  # Name of the subscription to retrieve
  end

  # Request message to list subscriptions
  add_message "tech.pubsub.ListSubscriptionsRequest" do
    optional :query, :string, 1        # Query filter for subscriptions
    optional :max_results, :int32, 3    # Maximum number of results to return
    optional :page_token, :string, 4    # Pagination token
  end

  # Response message for listing subscriptions
  add_message "tech.pubsub.ListSubscriptionsResponse" do
    repeated :subscription, :message, 1, "tech.pubsub.Subscription"  # List of subscriptions
    optional :next_page_token, :string, 2                            # Pagination token for next page
  end

  # Request message to truncate a subscription
  add_message "tech.pubsub.TruncateSubscriptionRequest" do
    optional :subscription, :string, 1  # Name of the subscription to truncate
  end

  # Request message to delete a subscription
  add_message "tech.pubsub.DeleteSubscriptionRequest" do
    optional :subscription, :string, 1  # Name of the subscription to delete
  end

  # Request message to modify push configuration
  add_message "tech.pubsub.ModifyPushConfigRequest" do
    optional :subscription, :string, 1                      # Subscription name
    optional :push_config, :message, 2, "tech.pubsub.PushConfig"  # New push configuration
  end

  # Request message to pull messages
  add_message "tech.pubsub.PullRequest" do
    optional :subscription, :string, 1        # Subscription to pull from
    optional :return_immediately, :bool, 2    # Whether to return immediately if no messages
  end

  # Response message for pull operation
  add_message "tech.pubsub.PullResponse" do
    optional :ack_id, :string, 1                          # Acknowledgment ID
    optional :pubsub_event, :message, 2, "tech.pubsub.PubsubEvent"  # The received event
  end

  # Request message to pull a batch of messages
  add_message "tech.pubsub.PullBatchRequest" do
    optional :subscription, :string, 1        # Subscription to pull from
    optional :return_immediately, :bool, 2    # Whether to return immediately if no messages
    optional :max_events, :int32, 3           # Maximum number of events to return
  end

  # Response message for batch pull operation
  add_message "tech.pubsub.PullBatchResponse" do
    repeated :pull_responses, :message, 2, "tech.pubsub.PullResponse"  # List of pull responses
  end

  # Request message to modify acknowledgment deadline
  add_message "tech.pubsub.ModifyAckDeadlineRequest" do
    optional :subscription, :string, 1        # Subscription name
    optional :ack_id, :string, 2              # Acknowledgment ID
    optional :ack_deadline_seconds, :int32, 3 # New acknowledgment deadline in seconds
  end

  # Request message to acknowledge messages
  add_message "tech.pubsub.AcknowledgeRequest" do
    optional :subscription, :string, 1  # Subscription name
    repeated :ack_id, :string, 2        # List of acknowledgment IDs
  end

  # Request message to negatively acknowledge messages (NACK)
  add_message "tech.pubsub.NackRequest" do
    optional :subscription, :string, 1  # Subscription name
    repeated :ack_id, :string, 2        # List of acknowledgment IDs to NACK
  end
end

# Module containing all the generated Protocol Buffer message classes
module Tech
  module Pubsub
    # Define message classes by looking up each message type in the descriptor pool
    Topic = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.Topic").msgclass
    PubsubMessage = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PubsubMessage").msgclass
    GetTopicRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.GetTopicRequest").msgclass
    PublishRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PublishRequest").msgclass
    PublishBatchRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PublishBatchRequest").msgclass
    PublishBatchResponse = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PublishBatchResponse").msgclass
    ListTopicsRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ListTopicsRequest").msgclass
    ListTopicsResponse = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ListTopicsResponse").msgclass
    DeleteTopicRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.DeleteTopicRequest").msgclass
    Subscription = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.Subscription").msgclass
    Subscription::TruncationPolicy = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.Subscription.TruncationPolicy").msgclass
    PushConfig = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PushConfig").msgclass
    PubsubEvent = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PubsubEvent").msgclass
    GetSubscriptionRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.GetSubscriptionRequest").msgclass
    ListSubscriptionsRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ListSubscriptionsRequest").msgclass
    ListSubscriptionsResponse = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ListSubscriptionsResponse").msgclass
    TruncateSubscriptionRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.TruncateSubscriptionRequest").msgclass
    DeleteSubscriptionRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.DeleteSubscriptionRequest").msgclass
    ModifyPushConfigRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ModifyPushConfigRequest").msgclass
    PullRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PullRequest").msgclass
    PullResponse = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PullResponse").msgclass
    PullBatchRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PullBatchRequest").msgclass
    PullBatchResponse = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.PullBatchResponse").msgclass
    ModifyAckDeadlineRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.ModifyAckDeadlineRequest").msgclass
    AcknowledgeRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.AcknowledgeRequest").msgclass
    NackRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("tech.pubsub.NackRequest").msgclass
  end
end
```