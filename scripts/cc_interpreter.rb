#!/usr/bin/env ruby
# Cross compiler interpreter's binaries
for target in ENV["TARGETS"].split(" ") do
    done, error = "\u{2705}", "\u{274c}"
    name = target.split("-").slice(0,2).reverse.join("-").concat("-interpreter")
    ext = target["windows"]? ".exe": ""
    zip = target["windows"]? "ZIP": "TAR"
    cmd = <<-BASH.strip.delete "\n"
        make build
        CC_OUTPUT="3bc#{ext}"
        CC_LD_TARGET="#{target}"
        #{zip}="#{name}-3bc"
    BASH
    cmd = system cmd, :out => File::NULL, :err => (open "#{name}.log", 'a')
    puts "#{(cmd)? done: error} #{name}"
end
