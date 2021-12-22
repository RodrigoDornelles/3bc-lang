require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestFails < Minitest::Test
    def test_error_unkown
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.10,5.0.0")
        assert_match /ERROR CODE\:(\t| )?(0x000000)/, stderr
        assert_equal 0, status.exitstatus
    end

    def test_seg_fault
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "7.0.10,1.0.11")
        assert_match /ERROR CODE\:(\t| )?(0x00000B)/, stderr
        assert_equal 11, status.exitstatus
    end

    def test_none_tty
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.10,2.0.0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC015)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_unsupported
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.10,3.0.0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC016)/, stderr
        assert_equal 15, status.exitstatus
    end
end
