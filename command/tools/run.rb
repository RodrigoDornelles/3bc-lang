require './utils/config'
require './utils/log'
def tool_run(file)
  return log_err('No local version installed.') if Config.new.local_version.nil?
  require './lib3bc/bindings'
  Lang3bc.new(file).run_until_end
end
