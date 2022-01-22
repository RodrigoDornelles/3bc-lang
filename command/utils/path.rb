# frozen_string_literal: true

def root_directory
  home = Dir.home
  "#{home}/.3bc"
end

def make_dirs
  root_dir = root_directory
  Dir.mkdir(root_dir) unless File.exist?(root_dir)
  Dir.mkdir("#{root_dir}/lib") unless File.exist?("#{root_dir}/lib")
  Dir.mkdir("#{root_dir}/bin") unless File.exist?("#{root_dir}/bin")
  Dir.mkdir("#{root_dir}/src") unless File.exist?("#{root_dir}/src")
end

ROOT_DIR = root_directory.freeze
CONFIG_DIR = "#{ROOT_DIR}/config.toml"
LIB_DIR = "#{ROOT_DIR}/lib"
BIN_DIR = "#{ROOT_DIR}/bin"
SRC_DIR = "#{ROOT_DIR}/src"
