require './lib3bc/raw'
require 'ffi'
# The 3bc Driver Class
class Lang3bc
  def initialize(filename = nil)
    @raw = RawLib3bc.new
    ptr = FFI::MemoryPointer.new(:pointer, 3)
    @vm_ptr = if filename.nil?
                ptr.write_array_of_type :string, :put_pointer, [FFI::MemoryPointer.from_string('<RUBY>')]
                @raw.driver_power_init(1, ptr)
              else
                ptr.write_array_of_type :string, :put_pointer, [FFI::MemoryPointer.from_string('<RUBY>'),
                                                                FFI::MemoryPointer.from_string(filename)]
                @raw.driver_power_init(2, ptr)
              end
    @vm = RawLib3bc::Lang3bcVM.new(@vm_ptr)
  end

  def update
    !@raw.driver_interrupt(@vm).zero?
  end

  def state
    @vm[:state]
  end

  def run_until_end
    loop do
      break unless update
    end
  end
end

module AppState
  # TODO: VM State
  FSM_3BC_DEFAULT = 0
  FSM_3BC_READING = 1
  FSM_3BC_RUNNING = 2
  FSM_3BC_WAITING = 3
  FSM_3BC_IO_READ = 4
  FSM_3BC_IO_SEND = 6
  FSM_3BC_EXITING = 7
  FSM_3BC_STOPED  = 8
end

# TODO.
module Lang3bcLine
  # TODO
end
