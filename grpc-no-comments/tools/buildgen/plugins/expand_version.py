# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Buildgen package version plugin

This parses the list of targets from the yaml build file, and creates
a custom version string for each language's package.

"""

import re

LANGUAGES = [
    "core",
    "cpp",
    "csharp",
    "node",
    "objc",
    "php",
    "python",
    "ruby",
]

class Version:
    def __init__(self, version_str, override_major=None):
        self.tag = None
        if "-" in version_str:
            version_str, self.tag = version_str.split("-")
        self.major, self.minor, self.patch = [
            int(x) for x in version_str.split(".")
        ]
        if override_major:
            self.major = override_major

    def __str__(self):
        """Version string in a somewhat idiomatic style for most languages"""
        version_str = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:
            version_str += "-%s" % self.tag
        return version_str

    def pep440(self):
        """Version string in Python PEP440 style"""
        s = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:

            if self.tag == "dev":
                s += ".dev0"
            elif len(self.tag) >= 3 and self.tag[0:3] == "pre":
                s += "rc%d" % int(self.tag[3:])
            else:
                raise Exception(
                    'Don\'t know how to translate version tag "%s" to pep440'
                    % self.tag
                )
        return s

    def ruby(self):
        """Version string in Ruby style"""
        if self.tag:
            return "%d.%d.%d.%s" % (
                self.major,
                self.minor,
                self.patch,
                self.tag,
            )
        else:
            return "%d.%d.%d" % (self.major, self.minor, self.patch)

    def php(self):
        """Version string for PHP PECL package"""
        s = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:
            if self.tag == "dev":
                s += "dev"
            elif len(self.tag) >= 3 and self.tag[0:3] == "pre":
                s += "RC%d" % int(self.tag[3:])
            else:
                raise Exception(
                    'Don\'t know how to translate version tag "%s" to PECL'
                    " version" % self.tag
                )
        return s

    def php_stability(self):
        """stability string for PHP PECL package.xml file"""
        if self.tag:
            return "beta"
        else:
            return "stable"

    def php_composer(self):
        """Version string for PHP Composer package"""
        return "%d.%d.%d" % (self.major, self.minor, self.patch)

    def php_current_version(self):
        return "8.1"

    def php_debian_version(self):
        return "buster"

def mako_plugin(dictionary):
    """Expand version numbers:
    - for each language, ensure there's a language_version tag in
      settings (defaulting to the master version tag)
    - expand version strings to major, minor, patch, and tag
    """

    settings = dictionary["settings"]
    version_str = settings["version"]
    master_version = Version(version_str)
    settings["version"] = master_version
    for language in LANGUAGES:
        version_tag = "%s_version" % language
        override_major = settings.get("%s_major_version" % language, None)
        if version_tag in settings:
            settings[version_tag] = Version(
                settings[version_tag], override_major=override_major
            )
        else:
            settings[version_tag] = Version(
                version_str, override_major=override_major
            )
