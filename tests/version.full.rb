require 'json'
require 'net/http'
require 'minitest/spec'
require 'minitest/autorun'

class TestVersion < Minitest::Test
    def setup
        @npm = File.read('./package.json').scan(/\"version\"\: \"(\d+\.\d+\.\d+)\"/)[0][0] rescue nil
        @arduino = File.read('./library.properties').scan(/version = (\d+\.\d+\.\d+)/)[0][0] rescue nil
        @oficial = File.read('./src/3bc.h').scan(/\#define VERSION_3BC \"(\d+\.\d+\.\d+)\"/)[0][0] rescue nil
        @oficial_major = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_MAJOR (\d+)/)[0][0] rescue nil
        @oficial_minor = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_MINOR (\d+)/)[0][0] rescue nil
        @oficial_patch = File.read('./src/3bc.h').scan(/\#define VERSION_3BC_PATCH (\d+)/)[0][0] rescue nil
    end

    def test_verify_version
        assert @npm != nil, "Invalid npm version"
        assert @arduino != nil, "Invalid arduino version"
        assert @oficial != nil, "Invalid oficial version" 
        assert @oficial_major != nil, "Invalid oficial major version" 
        assert @oficial_minor != nil, "Invalid oficial minor version" 
        assert @oficial_patch != nil, "Invalid oficial patch version" 
    end

    def test_some_version
        assert_equal @oficial, @npm, "Wrong npm version"
        assert_equal @oficial, @arduino, "Wrong arduino version"
        assert_equal @oficial, "#{@oficial_major}.#{@oficial_minor}.#{@oficial_patch}", "Wrong oficial version"
    end

    def test_newer_version
        for release in JSON.parse Net::HTTP.get URI 'https://api.github.com/repos/rodrigodornelles/3bc-lang/releases'
            assert release['tag_name'] != @oficial, "Github tag '#{@oficial}' already exist."
        end
    end
end
