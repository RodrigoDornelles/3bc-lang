require 'open3'

# The GIT Abstrations
class Git
  def initialize(path)
    @path = path
  end

  def checkout(tag)
    command = "git checkout #{tag}"
    Open3.capture3(command, chdir: @path)
  end

  def pull
    command = 'git pull --rebase'
    Open3.capture3(command, chdir: @path)
  end

  def clone(repo)
    command = "git clone #{repo} #{@path}"
    Open3.capture3(command)
  end
end
