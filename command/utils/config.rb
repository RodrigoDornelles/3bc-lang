require './utils/path'
require 'toml'
require 'fileutils'
require 'base64'

# The `Config` Class.
class Config
  def initialize(path = "#{ROOT_DIR}/Config.toml")
    FileUtils.touch(path) unless File.exist?(path)
    @path = path
  end

  def global_version=(version)
    cfg = parse
    (cfg['global'] = {}) if cfg[:global].nil?
    cfg['global']['version'] = version
    write(cfg)
  end

  def global_version
    cfg = parse
    return nil if cfg['global'].nil?

    cfg['global']['version']
  end

  def local_version=(version, path = FileUtils.pwd)
    cfg = parse
    (cfg['versions'] = {}) if cfg[:versions].nil?
    path = Base64.encode64(path).strip
    cfg['versions'][path] = version

    write(cfg)
  end

  def local_version
    cfg = parse
    return global_version if cfg['versions'].nil?

    path = Base64.encode64(FileUtils.pwd).strip
    cfg['versions'][path]
  end

  def write(cfg)
    File.new(@path, 'w').write(TOML::Generator.new(cfg).body)
  end

  def parse
    TOML.load_file(@path)
  end
end
