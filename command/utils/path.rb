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

def rmdir_all(dir)
  until Dir.glob("#{dir}/**/*").select { |d| File.directory?(d) }.select { |d| Dir.empty?(d) }.empty?
    Dir.glob("#{dir}/**/*").select do |d|
      File.directory?(d)
    end.sort.reverse.select { |d| Dir.empty?(d) }.each { |d| Dir.rmdir(d) }
  end
end
ROOT_DIR = root_directory.freeze
CONFIG_DIR = "#{ROOT_DIR}/config.toml".freeze
LIB_DIR = "#{ROOT_DIR}/lib".freeze
BIN_DIR = "#{ROOT_DIR}/bin".freeze
SRC_DIR = "#{ROOT_DIR}/src".freeze
