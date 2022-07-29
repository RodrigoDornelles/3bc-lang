#!/usr/bin/env ruby
# Cross compiler dynamic libaries
for target in ENV["TARGETS"].split(" ") do
    done, error = "\u{2705}", "\u{274c}"
    name = target.split("-").slice(0,2).reverse.join("-").concat("-libary-dynamic")
    ext = {"windows" => ".dll", "macos" => ".dylib", "linux" => ".so"}
    ext = ext[name.split("-").first]
    zip = target["windows"]? "ZIP": "TAR"
    cmd = <<-BASH.strip.delete "\n"
        make build
        CC_OUTPUT="3bc#{ext}"
        CC_SOURCES="programs/libary.c"
        CC_FLAGS="-fPIC -Os -lm"
        CC_LD_TARGET="#{target}"
        LD_FLAGS="-shared"
        #{zip}="#{name}-3bc"
    BASH
    cmd = system cmd, :out => File::NULL, :err => (open "#{name}.log", 'a')
    puts "#{(cmd)? done: error} #{name}"
end
