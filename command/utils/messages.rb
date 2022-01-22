# frozen_string_literal: true

# Messages for App(TODO)
class Message
  require 'colorize'

  def _ok
    '✅'
  end

  def _not_ok
   '❌'
  end

  def _wait
    '⏱️ '
  end

  def cant_clone
    puts "#{_not_ok} failed to clone version 3bc v#{version}"
    puts "#{_not_ok}: #{err}"
  end

  def install_pull(version)
    puts "#{_wait} Updating 3bc v#{version}"
  end

  def install_clone(version)
    puts "#{_ok} Downloading 3bc v#{version}"
  end

  def compile(version)
    puts "#{_wait} Building 3bc v#{version}"
  end

  def compiled(_version)
    puts "#{_ok} Finished Building."
  end

  def compile_error(error, version)
    puts "#{_not_ok} Error building 3bc v#{version}: #{error}"
  end

  def installing(version)
    puts "🔍 Installing 3bc v#{version}"
  end

  def cant_find(version)
    puts "#{_not_ok} Can't find 3bc v#{version}"
  end
  
  
end
