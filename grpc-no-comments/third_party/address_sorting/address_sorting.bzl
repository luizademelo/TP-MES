
# Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.

# 1. Redistributions of source code must retain the above copyright

# 2. Redistributions in binary form must reproduce the above copyright

#    without specific prior written permission.

def address_sorting_cc_library(name, srcs, hdrs, copts, includes, linkopts=[]):
    native.cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        copts = copts,
        includes = includes,
        linkopts = linkopts,
    )
