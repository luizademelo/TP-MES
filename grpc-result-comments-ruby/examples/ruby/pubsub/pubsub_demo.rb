Here's the commented version of the code:

```ruby
#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up load paths to include local and library directories
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(File.dirname(this_dir)), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries
require 'optparse'  # For command-line option parsing
require 'grpc'      # gRPC library
require 'googleauth' # Google authentication library
require 'google/protobuf' # Protocol Buffers library

# Require protocol buffer definitions
require 'google/protobuf/empty'
require 'tech/pubsub/proto/pubsub'
require 'tech/pubsub/proto/pubsub_services'

# Returns SSL credentials for gRPC channel
def ssl_creds
  GRPC::Core::ChannelCredentials.new()
end

# Returns an authentication proc using Google Application Default Credentials
def auth_proc(opts)
  auth_creds = Google::Auth.get_application_default
  return auth_creds.updater_proc
end

# Creates and returns a PublisherService stub with authentication
def publisher_stub(opts)
  address = "#{opts.host}:#{opts.port}"
  stub_clz = Tech::Pubsub::PublisherService::Stub
  GRPC.logger.info("... access PublisherService at #{address}")
  call_creds = GRPC::Core::CallCredentials.new(auth_proc(opts))
  combined_creds = ssl_creds.compose(call_creds)
  stub_clz.new(address, creds: combined_creds,
               GRPC::Core::Channel::SSL_TARGET => opts.host)
end

# Creates and returns a SubscriberService stub with authentication
def subscriber_stub(opts)
  address = "#{opts.host}:#{opts.port}"
  stub_clz = Tech::Pubsub::SubscriberService::Stub
  GRPC.logger.info("... access SubscriberService at #{address}")
  call_creds = GRPC::Core::CallCredentials.new(auth_proc(opts))
  combined_creds = ssl_creds.compose(call_creds)
  stub_clz.new(address, creds: combined_creds,
               GRPC::Core::Channel::SSL_TARGET => opts.host)
end

# Class containing various Pub/Sub operations
class NamedActions
  include Tech::Pubsub

  def initialize(pub, sub, args)
    @pub = pub  # Publisher client
    @sub = sub  # Subscriber client
    @args = args # Command line arguments
  end

  # Deletes a topic
  def remove_topic
    name = test_topic_name
    p "... removing Topic #{name}"
    @pub.delete_topic(DeleteTopicRequest.new(topic: name))
    p "removed Topic: #{name} OK"
  rescue GRPC::BadStatus => e
    p "Could not delete a topics: rpc failed with '#{e}'"
  end

  # Creates a new topic
  def create_topic
    name = test_topic_name
    p "... creating Topic #{name}"
    resp = @pub.create_topic(Topic.new(name: name))
    p "created Topic: #{resp.name} OK"
  rescue GRPC::BadStatus => e
    p "Could not create a topics: rpc failed with '#{e}'"
  end

  # Lists topics in the project
  def list_some_topics
    p 'Listing topics'
    p '-------------_'
    list_project_topics.topic.each { |t| p t.name }
  rescue GRPC::BadStatus => e
    p "Could not list topics: rpc failed with '#{e}'"
  end

  # Checks if a topic exists
  def check_exists
    name = test_topic_name
    p "... checking for topic #{name}"
    exists = topic_exists?(name)
    p "#{name} is a topic" if exists
    p "#{name} is not a topic" unless exists
  rescue GRPC::BadStatus => e
    p "Could not check for a topics: rpc failed with '#{e}'"
  end

  # Performs a random publish-subscribe test:
  # 1. Creates a topic if needed
  # 2. Creates a subscription
  # 3. Publishes random messages
  # 4. Pulls and acknowledges messages
  # 5. Deletes the subscription
  def random_pub_sub
    topic_name, sub_name = test_topic_name, test_sub_name
    create_topic_if_needed(topic_name)
    @sub.create_subscription(Subscription.new(name: sub_name,
                                              topic: topic_name))
    msg_count = rand(10..30)
    msg_count.times do |x|
      msg = PubsubMessage.new(data: "message #{x}")
      @pub.publish(PublishRequest.new(topic: topic_name, message: msg))
    end
    p "Sent #{msg_count} messages to #{topic_name}, checking for them now."
    batch = @sub.pull_batch(PullBatchRequest.new(subscription: sub_name,
                                                 max_events: msg_count))
    ack_ids = batch.pull_responses.map { |x| x.ack_id }
    p "Got #{ack_ids.size} messages; acknowledging them.."
    @sub.acknowledge(AcknowledgeRequest.new(subscription: sub_name,
                                            ack_id: ack_ids))
    p "Test messages were acknowledged OK, deleting the subscription"
    del_req = DeleteSubscriptionRequest.new(subscription: sub_name)
    @sub.delete_subscription(del_req)
  rescue GRPC::BadStatus => e
    p "Could not do random pub sub: rpc failed with '#{e}'"
  end

  private

  # Generates a test topic name based on either provided args or current time
  def test_topic_name
    unless @args.topic_name.nil?
      return "/topics/#{@args.project_id}/#{@args.topic_name}"
    end
    now_text = Time.now.utc.strftime('%Y%m%d%H%M%S%L')
    "/topics/#{@args.project_id}/#{ENV['USER']}-#{now_text}"
  end

  # Generates a test subscription name based on either provided args or current time
  def test_sub_name
    unless @args.sub_name.nil?
      return "/subscriptions/#{@args.project_id}/#{@args.sub_name}"
    end
    now_text = Time.now.utc.strftime('%Y%m%d%H%M%S%L')
    "/subscriptions/#{@args.project_id}/#{ENV['USER']}-#{now_text}"
  end

  # Checks if a topic exists in the project
  def topic_exists?(name)
    topics = list_project_topics.topic.map { |t| t.name }
    topics.include?(name)
  end

  # Creates a topic if it doesn't already exist
  def create_topic_if_needed(name)
    return if topic_exists?(name)
    @pub.create_topic(Topic.new(name: name))
  end

  # Lists all topics in the project
  def list_project_topics
    q = "cloud.googleapis.com/project in (/projects/#{@args.project_id})"
    @pub.list_topics(ListTopicsRequest.new(query: q))
  end
end

# Struct to hold command line arguments
Args = Struct.new(:host, :port, :action, :project_id, :topic_name,
                  :sub_name)

# Parses command line arguments
def parse_args
  # Set default values
  args = Args.new('pubsub-staging.googleapis.com',
                   443, 'list_some_topics', 'stoked-keyword-656')
  OptionParser.new do |opts|
    opts.on('--server_host SERVER_HOST', 'server hostname') do |v|
      args.host = v
    end
    opts.on('--server_port SERVER_PORT', 'server port') do |v|
      args.port = v
    end

    # Get available actions from NamedActions class
    scenes = NamedActions.instance_methods(false).map { |t| t.to_s }
    scene_list = scenes.join(',')
    opts.on("--action CODE", scenes, {}, 'pick a demo action',
            "  (#{scene_list})") do |v|
      args.action = v
    end

    # Handle other optional arguments
    %w(project_id topic_name sub_name).each do |o|
      opts.on("--#{o} VALUE", "#{o}") do |v|
        args[o] = v
      end
    end
  end.parse!
  _check_args(args)
end

# Validates that required arguments are present
def _check_args(args)
  %w(host port action).each do |a|
    if args[a].nil?
      raise OptionParser::MissingArgument.new("please specify --#{a}")
    end
  end
  args
end

# Main execution function
def main
  args = parse_args
  pub, sub = publisher_stub(args), subscriber_stub(args)
  NamedActions.new(pub, sub, args).method(args.action).call
end

main
```

Key improvements in the comments:
1. Added explanations for each major function and class
2. Documented the purpose of private methods
3. Explained the overall flow of operations
4. Added details about error handling
5. Clarified the command-line argument parsing
6. Noted the default values for arguments
7. Explained the authentication flow
8. Documented the Pub/Sub operations in the NamedActions class

The comments now provide a clear understanding of what each part of the code does while maintaining readability.