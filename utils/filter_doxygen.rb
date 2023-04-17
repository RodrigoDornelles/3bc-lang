#!/usr/bin/env ruby
File.open ARGV.first do |f|
    return puts "/**@file %s\n@code{.cpp}\n%s\n@endcode*/" % [ARGV.first, f.read] if ARGV.first.end_with? '.ino'
    return puts "/**@file %s\n@code{.txt}\n%s\n@endcode*/" % [ARGV.first, f.read] if ARGV.first.end_with? '.3bc'
    return puts f.read.gsub(/```c/, "@code{.c}").gsub(/```/, "@endcode") if ARGV.first.end_with? '.md'
    return puts f.read
end