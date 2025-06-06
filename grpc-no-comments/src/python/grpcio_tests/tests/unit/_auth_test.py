# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests of standard AuthMetadataPlugins."""

import collections
import logging
import threading
import unittest

from grpc import _auth

class MockGoogleCreds(object):
    def get_access_token(self):
        token = collections.namedtuple(
            "MockAccessTokenInfo", ("access_token", "expires_in")
        )
        token.access_token = "token"
        return token

class MockExceptionGoogleCreds(object):
    def get_access_token(self):
        raise Exception()

class GoogleCallCredentialsTest(unittest.TestCase):
    def test_google_call_credentials_success(self):
        callback_event = threading.Event()

        def mock_callback(metadata, error):
            self.assertEqual(metadata, (("authorization", "Bearer token"),))
            self.assertIsNone(error)
            callback_event.set()

        call_creds = _auth.GoogleCallCredentials(MockGoogleCreds())
        call_creds(None, mock_callback)
        self.assertTrue(callback_event.wait(1.0))

    def test_google_call_credentials_error(self):
        callback_event = threading.Event()

        def mock_callback(metadata, error):
            self.assertIsNotNone(error)
            callback_event.set()

        call_creds = _auth.GoogleCallCredentials(MockExceptionGoogleCreds())
        call_creds(None, mock_callback)
        self.assertTrue(callback_event.wait(1.0))

class AccessTokenAuthMetadataPluginTest(unittest.TestCase):
    def test_google_call_credentials_success(self):
        callback_event = threading.Event()

        def mock_callback(metadata, error):
            self.assertEqual(metadata, (("authorization", "Bearer token"),))
            self.assertIsNone(error)
            callback_event.set()

        metadata_plugin = _auth.AccessTokenAuthMetadataPlugin("token")
        metadata_plugin(None, mock_callback)
        self.assertTrue(callback_event.wait(1.0))

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
