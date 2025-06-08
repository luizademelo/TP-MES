Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up directory paths for the spec, root, and lib directories
spec_dir = File.expand_path(File.dirname(__FILE__))
root_dir = File.expand_path(File.join(spec_dir, '..'))
lib_dir = File.expand_path(File.join(root_dir, 'lib'))

# Add the spec and lib directories to the load path and remove duplicates
$LOAD_PATH.unshift(spec_dir)
$LOAD_PATH.unshift(lib_dir)
$LOAD_PATH.uniq!

# Initialize SimpleCov for code coverage if COVERAGE_NAME environment variable is set
require 'simplecov'
SimpleCov.start do
  # Exclude spec and bin directories from coverage
  add_filter 'spec'
  add_filter 'bin'
  # Set the command name for coverage report
  SimpleCov.command_name ENV['COVERAGE_NAME']
end if ENV['COVERAGE_NAME']

# Load required testing and logging libraries
require 'rspec'
require 'logging'
require 'rspec/logging_helper'
require 'grpc'

# Load local support files
require_relative 'support/services'
require_relative 'support/helpers'

# Extend GRPC module with global logging functionality
module GRPC
  extend Logging.globally
end

# Configure root logger to output to stdout with info level
Logging.logger.root.appenders = Logging.appenders.stdout
Logging.logger.root.level = :info

# Set specific log levels for GRPC components
Logging.logger['GRPC'].level = :info
Logging.logger['GRPC::ActiveCall'].level = :info
Logging.logger['GRPC::BidiCall'].level = :info

# Configure RSpec to capture log messages and include helper methods
RSpec.configure do |config|
  include RSpec::LoggingHelper
  config.capture_log_messages
  include GRPC::Spec::Helpers
end

# Disable RSpec warnings about potential false positives
RSpec::Expectations.configuration.warn_about_potential_false_positives = false

# Make threads abort on exceptions to fail tests immediately when background threads fail
Thread.abort_on_exception = true
```

The comments explain:
1. The directory path setup for the test environment
2. The code coverage configuration using SimpleCov
3. The required library imports
4. The logging configuration for both general and GRPC-specific logging
5. The RSpec test configuration including log capturing and helper inclusion
6. The thread exception handling configuration

Each comment provides context about why certain operations are performed and what their purpose is in the test setup.