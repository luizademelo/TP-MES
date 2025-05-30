# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'
require 'logger'

describe GRPC do
  describe '.logger=' do
    it 'sets logger' do
      noop_logger = GRPC::DefaultLogger::NoopLogger.new
      GRPC.logger = noop_logger
      expect(GRPC.logger).to be(noop_logger)

      custom_logger = Logger.new(STDOUT)
      GRPC.logger = custom_logger
      expect(GRPC.logger).to be(custom_logger)
    end
  end
end
