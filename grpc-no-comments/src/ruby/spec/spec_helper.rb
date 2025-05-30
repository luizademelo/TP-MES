# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

spec_dir = File.expand_path(File.dirname(__FILE__))
root_dir = File.expand_path(File.join(spec_dir, '..'))
lib_dir = File.expand_path(File.join(root_dir, 'lib'))

$LOAD_PATH.unshift(spec_dir)
$LOAD_PATH.unshift(lib_dir)
$LOAD_PATH.uniq!

require 'simplecov'
SimpleCov.start do
  add_filter 'spec'
  add_filter 'bin'
  SimpleCov.command_name ENV['COVERAGE_NAME']
end if ENV['COVERAGE_NAME']

require 'rspec'
require 'logging'
require 'rspec/logging_helper'
require 'grpc'

require_relative 'support/services'
require_relative 'support/helpers'

module GRPC
  extend Logging.globally
end
Logging.logger.root.appenders = Logging.appenders.stdout
Logging.logger.root.level = :info
Logging.logger['GRPC'].level = :info
Logging.logger['GRPC::ActiveCall'].level = :info
Logging.logger['GRPC::BidiCall'].level = :info

RSpec.configure do |config|
  include RSpec::LoggingHelper
  config.capture_log_messages
  include GRPC::Spec::Helpers
end

RSpec::Expectations.configuration.warn_about_potential_false_positives = false

Thread.abort_on_exception = true
