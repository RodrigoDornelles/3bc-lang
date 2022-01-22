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
    git.checkout(version)
    true
  else
    Message.new.cant_find(version)
    false
  end
end

def compile(version)
  Message.new.compile(version)
  _, err, status = CC.new('./src/3bc.c', '-shared -fPIC -O2', "#{SRC_DIR}/#{version}",
                          "#{BIN_DIR}/#{version}/lib3bc.so").compile
  if status.success?
    Message.new.compiled(version)
  else
    Message.new.compile_error(err, version)
  end
end

def fetch(git, gh_, version)
  gh_.fetch_releases.each do |release|
    next unless release['tag_name'] == version

    fetch_release(git, gh_, version)
    return true
  end
  false
end

def tool_install(version)
  Message.new.installing(version)
  gh = Github.new('RodrigoDornelles', '3bc-lang')
  git = Git.new("#{SRC_DIR}/#{version}")
  ok = fetch(git, gh, version)

  return unless checkout(ok, git, version)

  copy(version)
  compile(version)
  config = Config.new
  config.global_version = version if config.global_version.nil?
end
