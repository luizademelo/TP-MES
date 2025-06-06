# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'google/protobuf'

require 'google/protobuf/empty'
Google::Protobuf::DescriptorPool.generated_pool.build do
  add_message "tech.pubsub.Topic" do
    optional :name, :string, 1
  end
  add_message "tech.pubsub.PubsubMessage" do
    optional :data, :string, 1
    optional :message_id, :string, 3
  end
  add_message "tech.pubsub.GetTopicRequest" do
    optional :topic, :string, 1
  end
  add_message "tech.pubsub.PublishRequest" do
    optional :topic, :string, 1
    optional :message, :message, 2, "tech.pubsub.PubsubMessage"
  end
  add_message "tech.pubsub.PublishBatchRequest" do
    optional :topic, :string, 1
    repeated :messages, :message, 2, "tech.pubsub.PubsubMessage"
  end
  add_message "tech.pubsub.PublishBatchResponse" do
    repeated :message_ids, :string, 1
  end
  add_message "tech.pubsub.ListTopicsRequest" do
    optional :query, :string, 1
    optional :max_results, :int32, 2
    optional :page_token, :string, 3
  end
  add_message "tech.pubsub.ListTopicsResponse" do
    repeated :topic, :message, 1, "tech.pubsub.Topic"
    optional :next_page_token, :string, 2
  end
  add_message "tech.pubsub.DeleteTopicRequest" do
    optional :topic, :string, 1
  end
  add_message "tech.pubsub.Subscription" do
    optional :name, :string, 1
    optional :topic, :string, 2
    optional :query, :string, 3
    optional :truncation_policy, :message, 4, "tech.pubsub.Subscription.TruncationPolicy"
    optional :push_config, :message, 5, "tech.pubsub.PushConfig"
    optional :ack_deadline_seconds, :int32, 6
    optional :garbage_collect_seconds, :int64, 7
  end
  add_message "tech.pubsub.Subscription.TruncationPolicy" do
    optional :max_bytes, :int64, 1
    optional :max_age_seconds, :int64, 2
  end
  add_message "tech.pubsub.PushConfig" do
    optional :push_endpoint, :string, 1
  end
  add_message "tech.pubsub.PubsubEvent" do
    optional :subscription, :string, 1
    optional :message, :message, 2, "tech.pubsub.PubsubMessage"
    optional :truncated, :bool, 3
    optional :deleted, :bool, 4
  end
  add_message "tech.pubsub.GetSubscriptionRequest" do
    optional :subscription, :string, 1
  end
  add_message "tech.pubsub.ListSubscriptionsRequest" do
    optional :query, :string, 1
    optional :max_results, :int32, 3
    optional :page_token, :string, 4
  end
  add_message "tech.pubsub.ListSubscriptionsResponse" do
    repeated :subscription, :message, 1, "tech.pubsub.Subscription"
    optional :next_page_token, :string, 2
  end
  add_message "tech.pubsub.TruncateSubscriptionRequest" do
    optional :subscription, :string, 1
  end
  add_message "tech.pubsub.DeleteSubscriptionRequest" do
    optional :subscription, :string, 1
  end
  add_message "tech.pubsub.ModifyPushConfigRequest" do
    optional :subscription, :string, 1
    optional :push_config, :message, 2, "tech.pubsub.PushConfig"
  end
  add_message "tech.pubsub.PullRequest" do
    optional :subscription, :string, 1
    optional :return_immediately, :bool, 2
  end
  add_message "tech.pubsub.PullResponse" do
    optional :ack_id, :string, 1
    optional :pubsub_event, :message, 2, "tech.pubsub.PubsubEvent"
  end
  add_message "tech.pubsub.PullBatchRequest" do
    optional :subscription, :string, 1
    optional :return_immediately, :bool, 2
    optional :max_events, :int32, 3
  end
  add_message "tech.pubsub.PullBatchResponse" do
    repeated :pull_responses, :message, 2, "tech.pubsub.PullResponse"
  end
  add_message "tech.pubsub.ModifyAckDeadlineRequest" do
    optional :subscription, :string, 1
    optional :ack_id, :string, 2
    optional :ack_deadline_seconds, :int32, 3
  end
  add_message "tech.pubsub.AcknowledgeRequest" do
    optional :subscription, :string, 1
    repeated :ack_id, :string, 2
  end
  add_message "tech.pubsub.NackRequest" do
    optional :subscription, :string, 1
    repeated :ack_id, :string, 2
  end
end

module Tech
  module Pubsub
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
