require 'colorize'
require 'fileutils'
require './utils/api/github'
require './utils/git'
require './utils/path'
require './utils/cc'
require './utils/config'
def tool_install(version)
  puts "   #{'Installing'.colorize(:green)} version #{version}"
  puts "   #{'Searching'.colorize(:cyan)} for version #{version}"
  gh = Github.new('RodrigoDornelles', '3bc-lang')
  git = Git.new("#{SRC_DIR}/#{version}")
  ok = false
  gh.fetch_releases.each do |release|
    next unless release['tag_name'] == version

    puts "      #{'Found'.colorize(:green)} version #{version}"
    puts "   #{'Clone'.colorize(:cyan)} version #{version}"
    _out, err, status = git.clone(gh.repo_url)
    if status.success?
      puts "      #{'Cloned'.colorize(:green)} version #{version}"
    elsif err.include?('already exists and is not an empty directory')
      puts "      #{'Pull'.colorize(:green)} version #{version}"
      git.pull
    else
      puts "   #{'Failed to clone'.colorize(:red)} version #{version}"
      puts "   #{'Error'.colorize(:red)}: #{err}"
    end
    ok = true
  end
  if ok
    puts "   #{'Checkout'.colorize(:cyan)} version #{version}"
    git.checkout(version)
    puts "      #{'Checked out'.colorize(:green)} version #{version}"
  else
    puts "   #{'Failed to find'.colorize(:red)} version #{version}"
    return
  end
  FileUtils.copy("#{SRC_DIR}/#{version}/src/3bc.h", "#{SRC_DIR}/#{version}/src/3bc.c")
  begin
    Dir.mkdir("#{BIN_DIR}/#{version}")
  rescue StandardError
    nil
  end
  puts "   #{'Compile'.colorize(:cyan)} version #{version}"
  _, err, status = CC.new('./src/3bc.c', '-shared -fPIC -O2', "#{SRC_DIR}/#{version}",
                          "#{BIN_DIR}/#{version}/lib3bc.so").compile
  if status.success?
    puts "      #{'Compiled'.colorize(:green)} version #{version}"
  else
    puts "      #{'Failed to compile'.colorize(:red)} version #{version}"
    puts "      #{'Error'.colorize(:red)}: #{err}"
  end
  config = Config.new

  config.global_version = version if config.global_version.nil?
end
