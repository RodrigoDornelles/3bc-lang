require 'json'
require 'net/http'
include Net
# A Tiny Github lib.
class Github
  def initialize(user, repo)
    @user = user
    @repo = repo
  end

  def repo_url
    "https://github.com/#{@user}/#{@repo}"
  end

  def fetch_releases
    uri = URI("https://api.github.com/repos/#{@user}/#{@repo}/releases")
    response = HTTP.get(uri)
    JSON.parse(response)
  end
end
