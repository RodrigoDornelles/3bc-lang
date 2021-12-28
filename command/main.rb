require "thor"
require "./utils/path"
require "./tools/install"
require 'fileutils'

# The Virtual Machine commands
class VM < Thor
  desc "install <VERSION>", "install a version of 3bc"
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
  option :from_src, type: :boolean, default: true, aliases: "-s"
  def install(version)
    raise "Binary installation not supported yet" unless options[:from_src]

    tool_install(version)
  end
end

# The 3bc app
class App < Thor
  def self.exit_on_failure?
    true
  end
  desc "clean", "clean the 3bc installation"
  def clean
    FileUtils.remove_dir(ROOT_DIR, true)
  end
  desc "vm", "the virtual machine commands"
  subcommand "vm", VM
end
make_dirs
App.start(ARGV)
