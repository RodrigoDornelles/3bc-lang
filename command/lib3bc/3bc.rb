require 'ffi'
class RawLang3bc 
    extend FFI::Library
    def new(path)
        ffi_lib path
    end
end