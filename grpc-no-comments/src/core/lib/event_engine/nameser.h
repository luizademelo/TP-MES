// Copyright 2023 The gRPC Authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_NAMESER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_NAMESER_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_HAVE_ARPA_NAMESER

#include <arpa/nameser.h>

#else

typedef enum __ns_class {
  ns_c_invalid = 0,
  ns_c_in = 1,
  ns_c_2 = 2,
  ns_c_chaos = 3,
  ns_c_hs = 4,

  ns_c_none = 254,
  ns_c_any = 255,
  ns_c_max = 65536
} ns_class;

typedef enum __ns_type {
  ns_t_invalid = 0,
  ns_t_a = 1,
  ns_t_ns = 2,
  ns_t_md = 3,
  ns_t_mf = 4,
  ns_t_cname = 5,
  ns_t_soa = 6,
  ns_t_mb = 7,
  ns_t_mg = 8,
  ns_t_mr = 9,
  ns_t_null = 10,
  ns_t_wks = 11,
  ns_t_ptr = 12,
  ns_t_hinfo = 13,
  ns_t_minfo = 14,
  ns_t_mx = 15,
  ns_t_txt = 16,
  ns_t_rp = 17,
  ns_t_afsdb = 18,
  ns_t_x25 = 19,
  ns_t_isdn = 20,
  ns_t_rt = 21,
  ns_t_nsap = 22,
  ns_t_nsap_ptr = 23,
  ns_t_sig = 24,
  ns_t_key = 25,
  ns_t_px = 26,
  ns_t_gpos = 27,
  ns_t_aaaa = 28,
  ns_t_loc = 29,
  ns_t_nxt = 30,
  ns_t_eid = 31,
  ns_t_nimloc = 32,
  ns_t_srv = 33,
  ns_t_atma = 34,
  ns_t_naptr = 35,
  ns_t_kx = 36,
  ns_t_cert = 37,
  ns_t_a6 = 38,
  ns_t_dname = 39,
  ns_t_sink = 40,
  ns_t_opt = 41,
  ns_t_apl = 42,
  ns_t_ds = 43,
  ns_t_sshfp = 44,
  ns_t_rrsig = 46,
  ns_t_nsec = 47,
  ns_t_dnskey = 48,
  ns_t_tkey = 249,
  ns_t_tsig = 250,
  ns_t_ixfr = 251,
  ns_t_axfr = 252,
  ns_t_mailb = 253,
  ns_t_maila = 254,
  ns_t_any = 255,
  ns_t_zxfr = 256,
  ns_t_max = 65536
} ns_type;

#endif

#endif
