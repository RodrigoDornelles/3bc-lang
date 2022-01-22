# frozen_string_literal: true

require 'colorize'
def log_err(content)
  puts "#{'error'.colorize(:red)}: #{content}"
end
