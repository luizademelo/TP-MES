# Copyright (c) 2009-2021, Google LLC

# license that can be found in the LICENSE file or at
# https://developers.google.com/open-source/licenses/bsd

"""Internal rules for building upb."""

_DEFAULT_CPPOPTS = []
_DEFAULT_COPTS = [

    "-Werror=incompatible-pointer-types",

    "-Wno-error=attributes",
]

_DEFAULT_CPPOPTS.extend([
    "-Wextra",

    "-Wno-unused-parameter",
    "-Wno-long-long",
])
_DEFAULT_COPTS.extend([
    "-std=c99",
    "-Wall",
    "-Wstrict-prototypes",

])

UPB_DEFAULT_CPPOPTS = select({
    "//upb:windows": [],
    "//conditions:default": _DEFAULT_CPPOPTS,
})

UPB_DEFAULT_COPTS = select({
    "//upb:windows": [],
    "//upb:fasttable_enabled_setting": ["-std=gnu99", "-DUPB_ENABLE_FASTTABLE"],
    "//conditions:default": _DEFAULT_COPTS,
})

runfiles_init = """\
# --- begin runfiles.bash initialization v2 ---
# Copy-pasted from the Bazel Bash runfiles library v2.
set -uo pipefail; f=bazel_tools/tools/bash/runfiles/runfiles.bash
source "${RUNFILES_DIR:-/dev/null}/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "${RUNFILES_MANIFEST_FILE:-/dev/null}" | cut -f2- -d' ')" 2>/dev/null || \
  source "$0.runfiles/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.exe.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  { echo>&2 "ERROR: cannot find $f"; exit 1; }; f=; set -e
# --- end runfiles.bash initialization v2 ---
"""

def _get_real_short_path(file):

    short_path = file.short_path
    if short_path.startswith("../"):
        second_slash = short_path.index("/", 3)
        short_path = short_path[second_slash + 1:]
    return short_path

def _get_real_root(file):
    real_short_path = _get_real_short_path(file)
    return file.path[:-len(real_short_path) - 1]

def _get_real_roots(files):
    roots = {}
    for file in files:
        real_root = _get_real_root(file)
        if real_root:
            roots[real_root] = True
    return roots.keys()

def make_shell_script(name, contents, out):
    contents = contents.replace("$", "$$")
    native.genrule(
        name = "gen_" + name,
        outs = [out],
        cmd = "(cat <<'HEREDOC'\n%s\nHEREDOC\n) > $@" % contents,
    )
