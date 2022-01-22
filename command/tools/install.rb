# frozen_string_literal: true

require 'fileutils'
require './utils/api/github'
require './utils/git'
require './utils/path'
require './utils/cc'
require './utils/config'
require './utils/messages'

def fetch_release(git, gth, version)
  Message.new.install_clone(version)
  _out, err, status = git.clone(gth.repo_url)
  if status.success?
    puts "      #{'Cloned'.colorize(:green)} version #{version}"
  elsif err.include?('already exists and is not an empty directory')
    Message.new.install_pull version
    git.pull
  else
    Message.new.cant_clone
  end
end

def copy(version)
  FileUtils.copy("#{SRC_DIR}/#{version}/src/3bc.h", "#{SRC_DIR}/#{version}/src/3bc.c")
  begin
    Dir.mkdir("#{BIN_DIR}/#{version}")
  rescue StandardError
    nil
  end
end

def checkout(ok_, git, version)
  if ok_
    puts "   #{'Checkout'.colorize(:cyan)} version #{version}"
    git.checkout(version)
    puts "      #{'Checked out'.colorize(:green)} version #{version}"
    true
  else
    puts "   #{'Failed to find'.colorize(:red)} version #{version}"
    false
  end
end

def compile(version)
  puts "   #{'Compile'.colorize(:cyan)} version #{version}"
  _, err, status = CC.new('./src/3bc.c', '-shared -fPIC -O2', "#{SRC_DIR}/#{version}",
                          "#{BIN_DIR}/#{version}/lib3bc.so").compile
  if status.success?
    puts "      #{'Compiled'.colorize(:green)} version #{version}"
  else
    puts "      #{'Failed to compile'.colorize(:red)} version #{version}"
    puts "      #{'Error'.colorize(:red)}: #{err}"
  end
end

def fetch(git, gh_, version)
  gh_.fetch_releases.each do |release|
    next unless release['tag_name'] == version

    fetch_release(git, gh_, version)
    return true
  end
end

def tool_install(version)
  puts "   #{'Installing'.colorize(:green)} version #{version}"
  puts "   #{'Searching'.colorize(:cyan)} for version #{version}"
  gh = Github.new('RodrigoDornelles', '3bc-lang')
  git = Git.new("#{SRC_DIR}/#{version}")
  ok = fetch(git, gh, version)

  return unless checkout(ok, git, version)

  copy(version)
  compile(version)
  config = Config.new
  config.global_version = version if config.global_version.nil?
end
