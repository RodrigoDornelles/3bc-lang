# frozen_string_literal: true

require './utils/api/github'
require './utils/path'
require 'colorize'
def list_versions
  gh = Github.new('RodrigoDornelles', '3bc-lang')
  gh.fetch_releases.each do |version|
    puts("    #{'Found'.colorize(:green)} #{version['tag_name']}")
  end
end

def list_installed_versions
  Dir.entries(SRC_DIR).each do |path|
    next if ['.', '..'].include?(path)

    puts("    #{'Found'.colorize(:green)} #{path}")
  end
end
