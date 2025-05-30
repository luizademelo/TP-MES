# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Patches the spawn() command for windows compilers.

Windows has an 8191 character command line limit, but some compilers
support an @command_file directive where command_file is a file
containing the full command line.
"""

from distutils import ccompiler
import os
import os.path
import shutil
import sys
import tempfile

MAX_COMMAND_LENGTH = 8191

_classic_spawn = ccompiler.CCompiler.spawn

def _commandfile_spawn(self, command, **kwargs):
    if os.name == "nt":
        if any(arg.startswith("/Tc") for arg in command):

            command = [arg for arg in command if arg != "/std:c++17"]
        elif any(arg.startswith("/Tp") for arg in command):

            command = [arg for arg in command if arg != "/std:c11"]

    command_length = sum([len(arg) for arg in command])
    if os.name == "nt" and command_length > MAX_COMMAND_LENGTH:

        print("Command line length exceeded, using command file")
        print(" ".join(command))
        temporary_directory = tempfile.mkdtemp()
        command_filename = os.path.abspath(
            os.path.join(temporary_directory, "command")
        )
        with open(command_filename, "w") as command_file:
            escaped_args = [
                '"' + arg.replace("\\", "\\\\") + '"' for arg in command[1:]
            ]

            command_file.write(" \n".join(escaped_args))
        modified_command = command[:1] + ["@{}".format(command_filename)]
        try:
            _classic_spawn(self, modified_command, **kwargs)
        finally:
            shutil.rmtree(temporary_directory)
    else:
        _classic_spawn(self, command, **kwargs)

def monkeypatch_spawn():
    """Monkeypatching is dumb, but it's either that or we become maintainers of
    something much, much bigger."""
    ccompiler.CCompiler.spawn = _commandfile_spawn
