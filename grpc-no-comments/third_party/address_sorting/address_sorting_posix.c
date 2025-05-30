
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

#include "address_sorting_internal.h"

#if defined(ADDRESS_SORTING_POSIX)

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static bool posix_source_addr_factory_get_source_addr(
    address_sorting_source_addr_factory* factory,
    const address_sorting_address* dest_addr,
    address_sorting_address* source_addr) {
  (void)factory;
  bool source_addr_exists = false;

  int s = socket(((struct sockaddr*)dest_addr)->sa_family, SOCK_DGRAM, 0);
  if (s != -1) {
    if (connect(s, (const struct sockaddr*)&dest_addr->addr,
                (socklen_t)dest_addr->len) != -1) {
      address_sorting_address found_source_addr;
      memset(&found_source_addr, 0, sizeof(found_source_addr));
      found_source_addr.len = sizeof(found_source_addr.addr);
      if (getsockname(s, (struct sockaddr*)&found_source_addr.addr,
                      (socklen_t*)&found_source_addr.len) != -1) {
        source_addr_exists = true;
        *source_addr = found_source_addr;
      }
    }
  }
  close(s);
  return source_addr_exists;
}

static void posix_source_addr_factory_destroy(
    address_sorting_source_addr_factory* self) {
  free(self);
}

static const address_sorting_source_addr_factory_vtable
    posix_source_addr_factory_vtable = {
        posix_source_addr_factory_get_source_addr,
        posix_source_addr_factory_destroy,
};

address_sorting_source_addr_factory*
address_sorting_create_source_addr_factory_for_current_platform() {
  address_sorting_source_addr_factory* factory =
      malloc(sizeof(address_sorting_source_addr_factory));
  memset(factory, 0, sizeof(address_sorting_source_addr_factory));
  factory->vtable = &posix_source_addr_factory_vtable;
  return factory;
}

#endif
