Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Required dependencies
require 'etc'
require 'mkmf'
require_relative '../../lib/grpc/version.rb'

# Platform detection flags
windows = RUBY_PLATFORM =~ /mingw|mswin/
windows_ucrt = RUBY_PLATFORM =~ /(mingw|mswin).*ucrt/
bsd = RUBY_PLATFORM =~ /bsd/
darwin = RUBY_PLATFORM =~ /darwin/
linux = RUBY_PLATFORM =~ /linux/
cross_compiling = ENV['RCD_HOST_RUBY_VERSION']

# Special case for Apple toolchain (excluding truffleruby)
apple_toolchain = darwin && RUBY_ENGINE != 'truffleruby'

# Determine grpc root directory
grpc_root = File.expand_path(File.join(File.dirname(__FILE__), '../../../..'))

# Set build configuration (defaults to 'opt')
grpc_config = ENV['GRPC_CONFIG'] || 'opt'

# Set macOS deployment target
ENV['MACOSX_DEPLOYMENT_TARGET'] = '11.0'

# Returns debug symbols output directory if specified in environment
def debug_symbols_output_dir
  d = ENV['GRPC_RUBY_DEBUG_SYMBOLS_OUTPUT_DIR']
  return nil if d.nil? or d.size == 0
  d
end

# Removes '-s' linker flag if debug symbols output is enabled
def maybe_remove_strip_all_linker_flag(flags)
  if debug_symbols_output_dir
    flags = flags.split(' ')
    flags = flags.reject {|flag| flag == '-s'}
    flags = flags.join(' ')
  end
  flags
end

# Checks if an environment variable is unset or empty
def env_unset?(name)
  ENV[name].nil? || ENV[name].size == 0
end

# Inherits environment variable from rbconfig if not set
def inherit_env_or_rbconfig(name)
  ENV[name] = inherit_rbconfig(name) if env_unset?(name)
end

# Gets configuration value from RbConfig, optionally handling linker flags
def inherit_rbconfig(name, linker_flag: false)
  value = RbConfig::CONFIG[name] || ''
  if linker_flag
    value = maybe_remove_strip_all_linker_flag(value)
  end
  p "extconf.rb setting ENV[#{name}] = #{value}"
  ENV[name] = value
end

# Appends string to environment variable
def env_append(name, string)
  ENV[name] += ' ' + string
end

# Inherit build tool configurations
inherit_env_or_rbconfig 'AR'
inherit_env_or_rbconfig 'CC'
inherit_env_or_rbconfig 'CXX'
inherit_env_or_rbconfig 'RANLIB'
inherit_env_or_rbconfig 'STRIP'
inherit_rbconfig 'CPPFLAGS'
inherit_rbconfig('LDFLAGS', linker_flag: true)

# Set linker variables if not defined
ENV['LD'] = ENV['CC'] if env_unset?('LD')
ENV['LDXX'] = ENV['CXX'] if env_unset?('LDXX')

# Special handling for truffleruby
if RUBY_ENGINE == 'truffleruby'
  env_append 'CPPFLAGS', RbConfig::CONFIG['cppflags']
end

# Apple toolchain specific settings
if apple_toolchain && !cross_compiling
  ENV['AR'] = 'libtool'
  ENV['ARFLAGS'] = '-o'
end

# Set embedding flags
ENV['EMBED_OPENSSL'] = (RUBY_ENGINE != 'truffleruby').to_s
ENV['EMBED_ZLIB'] = (RUBY_ENGINE != 'truffleruby').to_s

# Set architecture flags
ENV['ARCH_FLAGS'] = RbConfig::CONFIG['ARCH_FLAG']
if apple_toolchain && !cross_compiling
  if RUBY_PLATFORM =~ /arm64/
    ENV['ARCH_FLAGS'] = '-arch arm64'
  else
    ENV['ARCH_FLAGS'] = '-arch i386 -arch x86_64'
  end
end

# Add gRPC-specific compiler flags
env_append 'CPPFLAGS', '-DGRPC_XDS_USER_AGENT_NAME_SUFFIX="\"RUBY\""'
require_relative '../../lib/grpc/version'
env_append 'CPPFLAGS', '-DGRPC_XDS_USER_AGENT_VERSION_SUFFIX="\"' + GRPC::VERSION + '\""'
env_append 'CPPFLAGS', '-DGRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK=1'

# Set output directories
output_dir = File.expand_path(RbConfig::CONFIG['topdir'])
grpc_lib_dir = File.join(output_dir, 'libs', grpc_config)
ENV['BUILDDIR'] = output_dir

# Configure strip tool with additional flags for Apple
strip_tool = RbConfig::CONFIG['STRIP']
strip_tool += ' -x' if apple_toolchain

# Build gRPC native library (non-Windows platforms)
unless windows
  puts 'Building internal gRPC into ' + grpc_lib_dir
  # Determine number of processors for parallel build
  nproc = 4
  nproc = Etc.nprocessors if Etc.respond_to? :nprocessors
  nproc_override = ENV['GRPC_RUBY_BUILD_PROCS']
  unless nproc_override.nil? or nproc_override.size == 0
    nproc = nproc_override
    puts "Overriding make parallelism to #{nproc}"
  end
  # Use gmake on BSD systems
  make = bsd ? 'gmake' : 'make'
  cmd = "#{make} -j#{nproc} -C #{grpc_root} #{grpc_lib_dir}/libgrpc.a CONFIG=#{grpc_config} Q="
  puts "Building grpc native library: #{cmd}"
  system(cmd)
  exit 1 unless $? == 0
end

# Process linker flags
$LDFLAGS = maybe_remove_strip_all_linker_flag($LDFLAGS)
$DLDFLAGS = maybe_remove_strip_all_linker_flag($DLDFLAGS)

# Set compiler flags
$CFLAGS << ' -DGRPC_RUBY_WINDOWS_UCRT' if windows_ucrt
$CFLAGS << ' -I' + File.join(grpc_root, 'include')
$CFLAGS << ' -g'

# Checks if Ruby ABI version is available
def have_ruby_abi_version()
  return true if RUBY_ENGINE == 'truffleruby'

  return false if RUBY_PATCHLEVEL >= 0

  m = /(\d+)\.(\d+)/.match(RUBY_VERSION)
  if m.nil?
    puts "Failed to parse ruby version: #{RUBY_VERSION}. Assuming ruby_abi_version symbol is NOT present."
    return false
  end
  major = m[1].to_i
  minor = m[2].to_i
  if major >= 3 and minor >= 2
    puts "Ruby version #{RUBY_VERSION} >= 3.2. Assuming ruby_abi_version symbol is present."
    return true
  end
  puts "Ruby version #{RUBY_VERSION} < 3.2. Assuming ruby_abi_version symbol is NOT present."
  false
end

# Generates export filename based on platform and Ruby version
def ext_export_filename()
  name = 'ext-export'
  name += '-truffleruby' if RUBY_ENGINE == 'truffleruby'
  name += '-with-ruby-abi-version' if have_ruby_abi_version()
  name
end

# Configure linker flags for different platforms
ext_export_file = File.join(grpc_root, 'src', 'ruby', 'ext', 'grpc', ext_export_filename())
$LDFLAGS << ' -Wl,--version-script="' + ext_export_file + '.gcc"' if linux
if apple_toolchain
  $LDFLAGS << ' -weak_framework CoreFoundation'
  $LDFLAGS << ' -Wl,-exported_symbols_list,"' + ext_export_file + '.clang"'
end

# Link with gRPC library and handle special build configurations
$LDFLAGS << ' ' + File.join(grpc_lib_dir, 'libgrpc.a') unless windows
if grpc_config == 'gcov'
  $CFLAGS << ' -O0 -fprofile-arcs -ftest-coverage'
  $LDFLAGS << ' -fprofile-arcs -ftest-coverage -rdynamic'
end

if grpc_config == 'dbg'
  $CFLAGS << ' -O0'
end

# Additional platform-specific linker flags
if linux && RUBY_ENGINE != 'truffleruby'
  $LDFLAGS << ' -static-libgcc -static-libstdc++'
end
$LDFLAGS << ' -static' if windows

# Set standard compiler flags
$CFLAGS << ' -std=c11 '
$CFLAGS << ' -Wall '
$CFLAGS << ' -Wextra '
$CFLAGS << ' -pedantic '

# Generate Makefile
output = File.join('grpc', 'grpc_c')
puts "extconf.rb $LDFLAGS: #{$LDFLAGS}"
puts "extconf.rb $DLDFLAGS: #{$DLDFLAGS}"
puts "extconf.rb $CFLAGS: #{$CFLAGS}"
puts 'Generating Makefile for ' + output
create_makefile(output)

# Prepare debug symbols filename
ruby_major_minor = /(\d+\.\d+)/.match(RUBY_VERSION).to_s
debug_symbols = "grpc-#{GRPC::VERSION}-#{RUBY_PLATFORM}-ruby-#{ruby_major_minor}.dbg"

# Modify Makefile to include cleanup targets
File.open('Makefile.new', 'w') do |o|
  o.puts 'hijack_remove_unused_artifacts: all remove_unused_artifacts'
  o.puts
  o.write(File.read('Makefile'))
  o.puts
  o.puts 'remove_unused_artifacts: $(DLLIB)'

  rm_obj_cmd = "rm -rf #{File.join(output_dir, 'objs')}"
  o.puts "\t$(ECHO) Removing unused object artifacts: #{rm_obj_cmd}"
  o.puts "\t$(Q) #{rm_obj_cmd}"
  rm_grpc_core_libs = "rm -f #{grpc_lib_dir}/*.a"
  o.puts "\t$(ECHO) Removing unused grpc core libraries: #{rm_grpc_core_libs}"
  o.puts "\t$(Q) #{rm_grpc_core_libs}"
end
File.rename('Makefile.new', 'Makefile')

# For optimized builds, add stripping step
if grpc_config == 'opt'
  File.open('Makefile.new', 'w') do |o|
    o.puts 'hijack: all strip remove_unused_artifacts'
    o.puts
    o.write(File.read('Makefile'))
    o.puts
    o.puts 'strip: $(DLLIB)'
    if debug_symbols_output_dir
      o.puts "\t$(ECHO) Saving debug symbols in #{debug_symbols_output_dir}/#{debug_symbols}"
      o.puts "\t$(Q) objcopy --only-keep-debug $(DLLIB) #{debug_symbols_output_dir}/#{debug_symbols}"
    end
    o.puts "\t$(ECHO) Stripping $(DLLIB)"
    o.puts "\t$(Q) #{strip_tool} $(DLLIB)"
  end
  File.rename('Makefile.new', 'Makefile')
end

# Workaround for make install bug if specified
if ENV['GRPC_RUBY_TEST_ONLY_WORKAROUND_MAKE_INSTALL_BUG']
  puts 'Overriding the generated Makefile install target to use cp'
  File.open('Makefile.new', 'w') do |o|
    File.foreach('Makefile') do |i|
      if i.start_with?('INSTALL_PROG = ')
        override = 'INSTALL_PROG = cp'
        puts "Replacing generated Makefile line: |#{i}|, with: |#{override}|"
        o.puts override
      else
        o.puts i
      end
    end
  end
  File.rename('Makefile.new', 'Makefile')
end
```