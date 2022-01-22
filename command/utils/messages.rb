# frozen_string_literal: true

# Messages for App(TODO)
class Message
  require 'colorize'

  def cant_clone
    puts "   #{'Failed to clone'.colorize(:red)} version #{version}"
    puts "   #{'Error'.colorize(:red)}: #{err}"
  end

  def install_pull(version)
    puts "      #{'Pull'.colorize(:green)} version #{version}"
  end

  def install_clone(version)
    puts "      #{'Found'.colorize(:green)} version #{version}"
    puts "   #{'Clone'.colorize(:cyan)} version #{version}"
  end
end
