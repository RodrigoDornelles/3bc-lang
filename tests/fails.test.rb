require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestFails < Minitest::Test
    def test_cpu_zero
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "strc 0 0")
        assert_match /ERROR CODE\: (0x3BC000)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_cpu_protected
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 7\nstrc 0 0")
        assert_match /ERROR CODE\: (0x3BC001)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_cpu_reserved
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 10\nstrc 0 0")
        assert_match /ERROR CODE\: (0x3BC002)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_register
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 11\naloc 0 0")
        assert_match /ERROR CODE\: (0x3BC003)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_address
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode e nill")
        assert_match /ERROR CODE\: (0x3BC004)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_constant
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode nill e")
        assert_match /ERROR CODE\: (0x3BC005)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_cpu
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode nill full")
        assert_match /ERROR CODE\: (0x3BC006)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_label
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "nill nill 1\nnill nill 1")
        assert_match /ERROR CODE\: (0x3BC007)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_ambiguous
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 2\nstri 1 1")
        assert_match /ERROR CODE\: (0x3BC008)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_required_value
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 9\ngoto 0 0")
        assert_match /ERROR CODE\: (0x3BC009)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_required_address
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 6\nfree 0 0")
        assert_match /ERROR CODE\: (0x3BC010)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_no_digits
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 --")
        assert_match /ERROR CODE\: (0x3BC013)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_wrong_base
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 0o8")
        assert_match /ERROR CODE\: (0x3BC016|0x3BC017|0x3BC018)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_dirty
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 2i")
        assert_match /ERROR CODE\: (0x3BC018)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_memory_config
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 6\ntcfg 8 8")
        assert_match /ERROR CODE\: (0x3BC023)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_memory_clamp
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 6\ntmin 1 2\ntmax 1 1")
        assert_match /ERROR CODE\: (0x3BC0024)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_void_helper_max_min
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 23\nmode 0 23")
        assert_match /ERROR CODE\: (0x3BC025)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_no_such_file
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "none.3bc")
        assert_match /ERROR CODE\: (0x3BC026)/, stderr
        assert_equal 15, status.exitstatus
    end
end