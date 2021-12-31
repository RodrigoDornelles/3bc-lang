require 'ffi'
# The 3bc FFI Library
class RawLib3bc
  extend FFI::Library
  def initialize(path)
    ffi_lib path
  end
  attach_method :driver_power_init, %i[int pointer], :pointer
  attach_method :ds_program_fifo_line_add, [:pointer], :zero
end
