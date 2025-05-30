
// Copyright 2015 gRPC authors.

#include "src/core/tsi/transport_security.h"

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <openssl/crypto.h>
#include <string.h>

#include <string>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/tsi/fake_transport_security.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "src/core/util/useful.h"
#include "test/core/test_util/test_config.h"

typedef struct {

  int expected;

  const char* host_name;

  const char* common_name;

  const char* dns_names;

  const char* ip_names;
} cert_name_test_entry;

const cert_name_test_entry cert_name_test_entries[] = {
    {1, "foo.com", "foo.com", nullptr, nullptr},
    {1, "f", "f", nullptr, nullptr},
    {0, "h", "i", nullptr, nullptr},
    {1, "bar.foo.com", "*.foo.com", nullptr, nullptr},
    {1, "www.test.fr", "common.name",
     "*.test.com,*.test.co.uk,*.test.de,*.test.fr", nullptr},

    {0, "f.uk", ".uk", nullptr, nullptr},
    {0, "w.bar.foo.com", "?.bar.foo.com", nullptr, nullptr},
    {0, "www.foo.com", "(www|ftp).foo.com", nullptr, nullptr},
    {0, "www.foo.com", "www.foo.com#", nullptr, nullptr},
    {0, "www.foo.com", "", "www.foo.com#*.foo.com,#,#", nullptr},
    {0, "www.house.example", "ww.house.example", nullptr, nullptr},
    {0, "test.org", "", "www.test.org,*.test.org,*.org", nullptr},
    {0, "w.bar.foo.com", "w*.bar.foo.com", nullptr, nullptr},
    {0, "www.bar.foo.com", "ww*ww.bar.foo.com", nullptr, nullptr},
    {0, "wwww.bar.foo.com", "ww*ww.bar.foo.com", nullptr, nullptr},
    {0, "wwww.bar.foo.com", "w*w.bar.foo.com", nullptr, nullptr},
    {0, "wwww.bar.foo.com", "w*w.bar.foo.c0m", nullptr, nullptr},
    {0, "WALLY.bar.foo.com", "wa*.bar.foo.com", nullptr, nullptr},
    {0, "wally.bar.foo.com", "*Ly.bar.foo.com", nullptr, nullptr},

    {0, "www.test.co.jp", "www.test.co.jp",
     "*.test.de,*.jp,www.test.co.uk,www.*.co.jp", nullptr},
    {0, "www.bar.foo.com", "www.bar.foo.com",
     "*.foo.com,*.*.foo.com,*.*.bar.foo.com,*..bar.foo.com,", nullptr},

    {1, "xn--poema-9qae5a.com.br", "xn--poema-9qae5a.com.br", nullptr, nullptr},
    {1, "www.xn--poema-9qae5a.com.br", "*.xn--poema-9qae5a.com.br", nullptr,
     nullptr},
    {0, "xn--poema-9qae5a.com.br", "",
     "*.xn--poema-9qae5a.com.br,"
     "xn--poema-*.com.br,"
     "xn--*-9qae5a.com.br,"
     "*--poema-9qae5a.com.br",
     nullptr},

    {1, "foo.example.com", "*.example.com", nullptr, nullptr},
    {0, "bar.foo.example.com", "*.example.com", nullptr, nullptr},
    {0, "example.com", "*.example.com", nullptr, nullptr},

    {0, "baz1.example.net", "baz*.example.net", nullptr, nullptr},
    {0, "foobaz.example.net", "*baz.example.net", nullptr, nullptr},
    {0, "buzz.example.net", "b*z.example.net", nullptr, nullptr},
    {0, "www.test.example.net", "www.*.example.net", nullptr, nullptr},

    {1, "www.test.example", "*.test.example", nullptr, nullptr},
    {1, "test.example.co.uk", "*.example.co.uk", nullptr, nullptr},
    {0, "test.example", "*.example", nullptr, nullptr},

    {0, "foo.com", "*.com", nullptr, nullptr},
    {0, "foo.us", "*.us", nullptr, nullptr},
    {0, "foo", "*", nullptr, nullptr},

    {1, "www.xn--poema-9qae5a.com.br", "*.xn--poema-9qae5a.com.br", nullptr,
     nullptr},
    {1, "test.example.xn--mgbaam7a8h", "*.example.xn--mgbaam7a8h", nullptr,
     nullptr},

    {0, "example.xn--mgbaam7a8h", "*.xn--mgbaam7a8h", nullptr, nullptr},

    {1, "www.appspot.com", "*.appspot.com", nullptr, nullptr},
    {1, "foo.s3.amazonaws.com", "*.s3.amazonaws.com", nullptr, nullptr},

    {0, "foo.example.com", "*.*.com", nullptr, nullptr},
    {0, "foo.bar.example.com", "*.bar.*.com", nullptr, nullptr},

    {1, "foo.com", "foo.com.", nullptr, nullptr},
    {1, "foo.com.", "foo.com", nullptr, nullptr},
    {1, "foo.com.", "foo.com.", nullptr, nullptr},
    {1, "f", "f.", nullptr, nullptr},
    {1, "f.", "f", nullptr, nullptr},
    {1, "f.", "f.", nullptr, nullptr},
    {1, "www-3.bar.foo.com", "*.bar.foo.com.", nullptr, nullptr},
    {1, "www-3.bar.foo.com.", "*.bar.foo.com", nullptr, nullptr},
    {1, "www-3.bar.foo.com.", "*.bar.foo.com.", nullptr, nullptr},
    {0, ".", ".", nullptr, nullptr},
    {0, "example.com", "*.com.", nullptr, nullptr},
    {0, "example.com.", "*.com", nullptr, nullptr},
    {0, "example.com.", "*.com.", nullptr, nullptr},
    {0, "foo.", "*.", nullptr, nullptr},
    {0, "foo", "*.", nullptr, nullptr},

    {1, "test.foo.com", "", "test.foo.com", nullptr},

    {0, "173.194.195.139", "173.194.195.139", nullptr, nullptr},

    {1, "173.194.195.139", "foo.example.com", nullptr, "173.194.195.139"},
    {0, "173.194.195.139", "foo.example.com", nullptr, "8.8.8.8"},
    {0, "173.194.195.139", "foo.example.com", nullptr, "8.8.8.8,8.8.4.4"},
    {1, "173.194.195.139", "foo.example.com", nullptr,
     "8.8.8.8,173.194.195.139"},
    {0, "173.194.195.139", "foo.example.com", nullptr, "173.194.195.13"},
    {0, "2001:db8:a0b:12f0::1", "foo.example.com", nullptr, "173.194.195.13"},
    {1, "2001:db8:a0b:12f0::1", "foo.example.com", nullptr,
     "2001:db8:a0b:12f0::1"},
    {0, "2001:db8:a0b:12f0::1", "foo.example.com", nullptr,
     "2001:db8:a0b:12f0::2"},
    {1, "2001:db8:a0b:12f0::1", "foo.example.com", nullptr,
     "2001:db8:a0b:12f0::2,2001:db8:a0b:12f0::1,8.8.8.8"},
};

typedef struct name_list {
  const char* name;
  struct name_list* next;
} name_list;

typedef struct {
  size_t name_count;
  char* buffer;
  name_list* names;
} parsed_names;

name_list* name_list_add(const char* n) {
  name_list* result = static_cast<name_list*>(gpr_malloc(sizeof(name_list)));
  result->name = n;
  result->next = nullptr;
  return result;
}

static parsed_names parse_names(const char* names_str) {
  parsed_names result;
  name_list* current_nl;
  size_t i;
  memset(&result, 0, sizeof(parsed_names));
  if (names_str == nullptr) return result;
  result.name_count = 1;
  result.buffer = gpr_strdup(names_str);
  result.names = name_list_add(result.buffer);
  current_nl = result.names;
  for (i = 0; i < strlen(names_str); i++) {
    if (names_str[i] == ',') {
      result.buffer[i] = '\0';
      result.name_count++;
      i++;
      current_nl->next = name_list_add(result.buffer + i);
      current_nl = current_nl->next;
    }
  }
  return result;
}

static void destruct_parsed_names(parsed_names* pdn) {
  name_list* nl = pdn->names;
  if (pdn->buffer != nullptr) gpr_free(pdn->buffer);
  while (nl != nullptr) {
    name_list* to_be_free = nl;
    nl = nl->next;
    gpr_free(to_be_free);
  }
}

static char* processed_name(const char* name) {
  char* result = gpr_strdup(name);
  size_t i;
  for (i = 0; i < strlen(result); i++) {
    if (result[i] == '#') {
      result[i] = '\0';
    }
  }
  return result;
}

static tsi_peer peer_from_cert_name_test_entry(
    const cert_name_test_entry* entry) {
  size_t i;
  tsi_peer peer;
  name_list* nl;
  parsed_names dns_entries = parse_names(entry->dns_names);
  parsed_names ip_entries = parse_names(entry->ip_names);
  nl = dns_entries.names;
  EXPECT_EQ(tsi_construct_peer(
                1 + dns_entries.name_count + ip_entries.name_count, &peer),
            TSI_OK);
  EXPECT_EQ(tsi_construct_string_peer_property_from_cstring(
                TSI_X509_SUBJECT_COMMON_NAME_PEER_PROPERTY, entry->common_name,
                &peer.properties[0]),
            TSI_OK);
  i = 1;
  while (nl != nullptr) {
    char* processed = processed_name(nl->name);
    EXPECT_EQ(tsi_construct_string_peer_property(
                  TSI_X509_SUBJECT_ALTERNATIVE_NAME_PEER_PROPERTY, processed,
                  strlen(nl->name), &peer.properties[i++]),
              TSI_OK);
    nl = nl->next;
    gpr_free(processed);
  }

  nl = ip_entries.names;
  while (nl != nullptr) {
    char* processed = processed_name(nl->name);
    EXPECT_EQ(tsi_construct_string_peer_property(
                  TSI_X509_SUBJECT_ALTERNATIVE_NAME_PEER_PROPERTY, processed,
                  strlen(nl->name), &peer.properties[i++]),
              TSI_OK);
    nl = nl->next;
    gpr_free(processed);
  }
  destruct_parsed_names(&dns_entries);
  destruct_parsed_names(&ip_entries);
  return peer;
}

std::string cert_name_test_entry_to_string(const cert_name_test_entry* entry) {
  return absl::StrFormat(
      "{ success = %s, host_name = %s, common_name = %s, dns_names = "
      "%s, ip_names = %s}",
      entry->expected ? "true" : "false", entry->host_name, entry->common_name,
      entry->dns_names != nullptr ? entry->dns_names : "",
      entry->ip_names != nullptr ? entry->ip_names : "");
}

TEST(TransportSecurityTest, TestPeerMatchesName) {
  size_t i = 0;
  for (i = 0; i < GPR_ARRAY_SIZE(cert_name_test_entries); i++) {
    const cert_name_test_entry* entry = &cert_name_test_entries[i];
    tsi_peer peer = peer_from_cert_name_test_entry(entry);
    int result = tsi_ssl_peer_matches_name(&peer, entry->host_name);
    if (result != entry->expected) {
      LOG(ERROR) << cert_name_test_entry_to_string(entry);
      ASSERT_TRUE(0);
    }
    tsi_peer_destruct(&peer);
  }
}

typedef struct {
  tsi_result res;
  const char* str;
} tsi_result_string_pair;

TEST(TransportSecurityTest, TestResultStrings) {
  const tsi_result_string_pair results[] = {
      {TSI_OK, "TSI_OK"},
      {TSI_UNKNOWN_ERROR, "TSI_UNKNOWN_ERROR"},
      {TSI_INVALID_ARGUMENT, "TSI_INVALID_ARGUMENT"},
      {TSI_PERMISSION_DENIED, "TSI_PERMISSION_DENIED"},
      {TSI_INCOMPLETE_DATA, "TSI_INCOMPLETE_DATA"},
      {TSI_FAILED_PRECONDITION, "TSI_FAILED_PRECONDITION"},
      {TSI_UNIMPLEMENTED, "TSI_UNIMPLEMENTED"},
      {TSI_INTERNAL_ERROR, "TSI_INTERNAL_ERROR"},
      {TSI_DATA_CORRUPTED, "TSI_DATA_CORRUPTED"},
      {TSI_NOT_FOUND, "TSI_NOT_FOUND"},
      {TSI_PROTOCOL_FAILURE, "TSI_PROTOCOL_FAILURE"},
      {TSI_HANDSHAKE_IN_PROGRESS, "TSI_HANDSHAKE_IN_PROGRESS"},
      {TSI_OUT_OF_RESOURCES, "TSI_OUT_OF_RESOURCES"}};
  size_t i;
  for (i = 0; i < GPR_ARRAY_SIZE(results); i++) {
    ASSERT_STREQ(results[i].str, tsi_result_to_string(results[i].res));
  }
}

TEST(TransportSecurityTest, TestProtectorInvalidArgs) {
  ASSERT_EQ(
      tsi_frame_protector_protect(nullptr, nullptr, nullptr, nullptr, nullptr),
      TSI_INVALID_ARGUMENT);
  ASSERT_EQ(
      tsi_frame_protector_protect_flush(nullptr, nullptr, nullptr, nullptr),
      TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_frame_protector_unprotect(nullptr, nullptr, nullptr, nullptr,
                                          nullptr),
            TSI_INVALID_ARGUMENT);
}

TEST(TransportSecurityTest, TestHandshakerInvalidArgs) {
  ASSERT_EQ(tsi_handshaker_get_result(nullptr), TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_handshaker_extract_peer(nullptr, nullptr),
            TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_handshaker_create_frame_protector(nullptr, nullptr, nullptr),
            TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_handshaker_process_bytes_from_peer(nullptr, nullptr, nullptr),
            TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_handshaker_get_bytes_to_send_to_peer(nullptr, nullptr, nullptr),
            TSI_INVALID_ARGUMENT);
  ASSERT_EQ(tsi_handshaker_next(nullptr, nullptr, 0, nullptr, nullptr, nullptr,
                                nullptr, nullptr),
            TSI_INVALID_ARGUMENT);
}

TEST(TransportSecurityTest, TestHandshakerInvalidState) {
  tsi_handshaker* h = tsi_create_fake_handshaker(0);
  tsi_peer peer;
  tsi_frame_protector* p;
  ASSERT_EQ(tsi_handshaker_extract_peer(h, &peer), TSI_FAILED_PRECONDITION);
  ASSERT_EQ(tsi_handshaker_create_frame_protector(h, nullptr, &p),
            TSI_FAILED_PRECONDITION);
  tsi_handshaker_destroy(h);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
