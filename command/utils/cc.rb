# C Compiler
class CC
  def initialize(file, flags, path, out)
    @file = file
    @flags = flags
    @path = path
    @out = out
  end

  def find_compiler
    if File.exist?('/usr/bin/clang')
      'clang'
    elsif File.exist?('/usr/bin/gcc')
      'gcc'
    else
      'cc'
    end
  end

  def compile
    compiler = find_compiler
    command = "#{compiler} #{@flags} #{@file} -o #{@out}"
    Open3.capture3(command, chdir: @path)
  end
end
