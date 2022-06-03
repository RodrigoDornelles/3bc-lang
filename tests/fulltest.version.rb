require 'json'
require 'net/http'
require 'minitest/spec'
require 'minitest/autorun'

class TestVersion < Minitest::Test
    def setup
        @npm = File.read('./package.json').scan(/\"version\"\: \"(\d+\.\d+\.\d+)\"/).first.first rescue nil
        @arduino = File.read('./library.properties').scan(/version = (\d+\.\d+\.\d+)/).first.first rescue nil
        @pkgbuild = File.read('./PKGBUILD').scan(/pkgver\=\"(\d+.\d+.\d+)\"/).first.first rescue nil
        @oficial = File.read('./src/3bc.h').scan(/\#define VERSION_3BC \"(\d+\.\d+\.\d+)\"/).first.first rescue nil
        @oficial_major = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_MAJOR (\d+)/).first.first rescue nil
        @oficial_minor = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_MINOR (\d+)/).first.first rescue nil
        @oficial_patch = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_PATCH (\d+)/).first.first rescue nil
    end

    def test_verify_version
        refute_equal @npm, nil, "Invalid npm version"
        refute_equal @arduino, nil, "Invalid arduino version"
        refute_equal @pkgbuild, nil, "Invalid pkgbuild version"
        refute_equal @oficial, nil, "Invalid oficial version" 
        refute_equal @oficial_major, nil, "Invalid oficial major version" 
        refute_equal @oficial_minor, nil, "Invalid oficial minor version" 
        refute_equal @oficial_patch, nil, "Invalid oficial patch version" 
    end

    def test_some_version
        assert_equal @oficial, @npm, "Wrong npm version"
        assert_equal @oficial, @arduino, "Wrong arduino version"
        assert_equal @oficial, @pkgbuild, "Wrong pkgbuild version"
        assert_equal @oficial, "#{@oficial_major}.#{@oficial_minor}.#{@oficial_patch}", "Wrong oficial version"
    end

    def test_newer_version
        for release in (JSON.parse Net::HTTP.get URI 'https://api.github.com/repos/rodrigodornelles/3bc-lang/releases').collect {|value|value['tag_name']}
            refute_equal release, @oficial, "Github tag '#{@oficial}' already exist."
        end rescue skip warn "Skiped:\nGithub API is not available.\n\n"

        for release in (JSON.parse Net::HTTP.get URI 'https://registry.npmjs.org/3bc-lang')['versions'].collect {|key,_|key}
            refute_equal release, @oficial, "NPM tag '#{@oficial}' already exist."
        end rescue skip warn "Skiped:\nNPM API is not available.\n\n"
    end
end
