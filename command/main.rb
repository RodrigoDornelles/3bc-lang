# frozen_string_literal: true

require './utils/path'

make_dirs

require 'thor'
require './tools/install'
require './tools/list'
require './tools/run'
require './utils/log'
require './utils/config'
require 'fileutils'

def version_exists?(ver)
  Dir.entries(BIN_DIR).include?(ver)
end

# The Config commands
class ConfigCommands < Thor
  desc 'global-get', 'get current global version'
  def global_set(version)
    return log_error("version #{version} is not installed.") unless version_exists?(version)

    config = Config.new
    config.global_version = version
  end
  desc 'global-get', 'set global version'
  def global_get
    config = Config.new
    puts(config.global_version)
  end
  desc 'local-set [VERSION]', 'set local version'
  def local_set(version)
    return log_error("version #{version} is not installed.") unless version_exists?(version)

    config = Config.new
    config.local_version = version
  end
  desc 'local-get', 'get current local version'
  def local_get
    config = Config.new
    puts(config.local_version)
  end
end

# The Virtual Machine commands
class VMCommands < Thor
  desc 'install <VERSION>', 'install a version of 3bc'
  long_desc <<-LONGDESC
    `install` will install a version of 3bc.
    The version can be specified as a version number or a tag.
    If a tag is specified, the latest version of the tag will be installed.
    If a version number is specified, the exact version will be installed.
    Examples of valid version numbers:
        3.0.0
        3.0.0-rc1
        +git#1234567
  LONGDESC
  option :from_src, type: :boolean, default: true, aliases: '-s'
  def install(version)
    raise 'Binary installation not supported yet' unless options[:from_src]

    tool_install(version)
  end

  desc 'list', 'list versions'
  option :installed, type: :boolean, default: false, aliases: '-i'
  def list
    if options[:installed]
      list_installed_versions
    else
      list_versions
    end
  end
end

# The 3bc app
class App < Thor
  def self.exit_on_failure?
    true
  end
  desc 'clean', 'clean the 3bc installation'
  def clean
    FileUtils.remove_dir(ROOT_DIR, true)
  end
  desc 'run <FILE>', 'run a 3bc file'
  def run_(filename)
    tool_run(filename)
  end
  desc 'vm', 'the virtual machine commands'
  subcommand 'vm', VMCommands
  desc 'config', 'the config options'
  subcommand 'config', ConfigCommands
end
App.start(ARGV)
