
/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef ADDRESS_SORTING_H
#define ADDRESS_SORTING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct address_sorting_address {
  char addr[128];
  size_t len;
} address_sorting_address;

typedef struct address_sorting_sortable {

  address_sorting_address dest_addr;

  void* user_data;

  address_sorting_address source_addr;
  bool source_addr_exists;
  size_t original_index;
} address_sorting_sortable;

void address_sorting_rfc_6724_sort(address_sorting_sortable* sortables,
                                   size_t sortables_len);

void address_sorting_init();
void address_sorting_shutdown();

struct address_sorting_source_addr_factory;

typedef struct {

  bool (*get_source_addr)(struct address_sorting_source_addr_factory* factory,
                          const address_sorting_address* dest_addr,
                          address_sorting_address* source_addr);
  void (*destroy)(struct address_sorting_source_addr_factory* factory);
} address_sorting_source_addr_factory_vtable;

typedef struct address_sorting_source_addr_factory {
  const address_sorting_source_addr_factory_vtable* vtable;
} address_sorting_source_addr_factory;

typedef enum {
  ADDRESS_SORTING_AF_INET,
  ADDRESS_SORTING_AF_INET6,
  ADDRESS_SORTING_UNKNOWN_FAMILY,
} address_sorting_family;

address_sorting_family address_sorting_abstract_get_family(
    const address_sorting_address* address);

void address_sorting_override_source_addr_factory_for_testing(
    address_sorting_source_addr_factory* factory);

bool address_sorting_get_source_addr_for_testing(
    const address_sorting_address* dest, address_sorting_address* source);

#ifdef __cplusplus
}
#endif

#endif
