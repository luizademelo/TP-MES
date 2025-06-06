#!/usr/bin/python

# Copyright 2023 Google LLC.  All rights reserved.

#     * Redistributions of source code must retain the above copyright

# copyright notice, this list of conditions and the following disclaimer

# this software without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS

# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT

import sys
import re
import os

INCLUDE_RE = re.compile('^#include "([^"]*)"')

def parse_include(line):
  match = INCLUDE_RE.match(line)
  return match.groups()[0] if match else None

class Amalgamator:
  def __init__(self, h_out, c_out):
    self.include_paths = ["."]
    self.included = set()
    self.output_h = open(h_out, "w")
    self.output_c = open(c_out, "w")
    self.h_out = h_out.split("/")[-1]

  def amalgamate(self, h_files, c_files):
    self.h_files = set(h_files)
    self.output_c.write("/* Amalgamated source file */\n")
    self.output_c.write('#include "%s"\n' % (self.h_out))
    if self.h_out == "ruby-upb.h":
      self.output_h.write("// Ruby is still using proto3 enum semantics for proto2\n")
      self.output_h.write("#define UPB_DISABLE_CLOSED_ENUM_CHECKING\n")

    self.output_h.write("/* Amalgamated source file */\n")

    port_def = self._find_include_file("upb/port/def.inc")
    port_undef = self._find_include_file("upb/port/undef.inc")
    self._process_file(port_def, self.output_h)
    self._process_file(port_def, self.output_c)

    for file in c_files:
      self._process_file(file, self.output_c)

    self._process_file(port_undef, self.output_h)
    self._process_file(port_undef, self.output_c)

  def _process_file(self, infile_name, outfile):
    lines = open(infile_name).readlines()

    has_copyright = lines[0].startswith(
        "// Protocol Buffers - Google's data interchange format"
    )
    if has_copyright:
      while not lines[0].startswith(
          "// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH"
          " DAMAGE"
      ) and not lines[0].startswith(
          "// https://developers.google.com/open-source/licenses/bsd"
      ):
        lines.pop(0)
      lines.pop(0)

    for line in lines:
      if not self._process_include(line):
        outfile.write(line)

  def _find_include_file(self, name):
    for h_file in self.h_files:
      if h_file.endswith(name):
        return h_file

  def _process_include(self, line):
    include = parse_include(line)
    if not include:
      return False
    if not (
        include.startswith("upb")
        or include.startswith("google")
    ):
      return False
    if include and (include.endswith("port/def.inc") or include.endswith("port/undef.inc")):

      return True
    if include.endswith("hpp"):

      return True
    if re.search(r"stage\d/", include):
      return True
    elif include in self.included:
      return True
    else:

      h_file = self._find_include_file(include)
      if h_file:
        self.h_files.remove(h_file)
        self.included.add(include)
        self._process_file(h_file, self.output_h)
        return True
      raise RuntimeError("Couldn't find include: " + include + ", h_files=" + repr(self.h_files))

c_out = sys.argv[1]
h_out = sys.argv[2]
amalgamator = Amalgamator(h_out, c_out)
c_files = []
h_files = []

for arg in sys.argv[3:]:
  arg = arg.strip()
  if arg.endswith(".h") or arg.endswith(".inc"):
    h_files.append(arg)
  else:
    c_files.append(arg)

amalgamator.amalgamate(h_files, c_files)
