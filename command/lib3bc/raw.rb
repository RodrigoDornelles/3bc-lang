require 'ffi'
require './utils/config'
require './utils/path'
# The 3bc FFI Library
class RawLib3bc
  extend FFI::Library

  ffi_lib "#{BIN_DIR}/#{Config.new.local_version}/lib3bc.so"
  class Lang3bcVM < FFI::Struct
    layout \
      :state, :int
  end
  attach_function :driver_power_init, %i[int pointer], :pointer
  attach_function :driver_interrupt, [:pointer], :int
end
