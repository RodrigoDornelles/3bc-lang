require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestFails < Minitest::Test
    def test_cpu_zero
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "strc 0 0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC000)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_cpu_reserved
        for cpu_mode in (20..40).step(10)
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 #{cpu_mode}\n1 0 0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC001)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_invalid_register
        for console_input in ["baaz 0 0", "7.0.11,2.0.0"]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC002)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_invalid_address
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode e nill")
        assert_match /ERROR CODE\:(\t| )?(0x3BC003)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_constant
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode nill e")
        assert_match /ERROR CODE\:(\t| )?(0x3BC004)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_cpu_mode
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode nill full")
        assert_match /ERROR CODE\:(\t| )?(0x3BC005)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_label
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "nill nill 1\nnill nill 1")
        assert_match /ERROR CODE\:(\t| )?(0x3BC006)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_return
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.41,back.0.0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC007)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_ambiguous
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 2\nstri 1 1")
        assert_match /ERROR CODE\:(\t| )?(0x3BC008)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_required_any
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.43,fake.0.0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC009)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_required_value
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 9\ngoto 0 0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00A)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_required_address
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 6\nfree 0 0")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00B)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_blocked_value
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 6\nfree 1 1")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00C)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_param_blocked_address
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 9\ngoto 1 1")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00D)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_no_digits
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 --")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00E)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_underflow
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.2,strx.0.-0xFFFFFFFFFFFFFFFF")
        assert_match /ERROR CODE\:(\t| )?(0x3BC00F)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_number_overflow
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.2,strx.0.0xFFFFFFFFFFFFFFFF")
        assert_match /ERROR CODE\:(\t| )?(0x3BC010)/, stderr
        assert_equal 15, status.exitstatus
    end
    
    def test_number_wrong_base
        for console_input in ["mode.0.0o8", "0.0.0k0"]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC011)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_number_negative
        for console_input in ['mode.0.32,math.0.-1', 'mode.0.6,aloc.1.-1,mode.0.7,pull.1.0']
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC012)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_number_zero
        for console_input in ['mode.0.14,math.0.0,', 'mode.0.38,math.0.2', 'mode.0.39,math.0.0']
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC013)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_invalid_memory_config
        for console_input in ['mode.0.6,muse.1.48','mode.0.6,muse.1.20','mode.0.6,muse.1.12','mode.0.6,muse.1.32']
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC017)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_no_such_file
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "none.3bc")
        assert_match /ERROR CODE\:(\t| )?(0x3BC018)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_null_pointer_exception
        for console_input in [
            "mode 0 7\naloc 'p' nill", "mode 0 7\nfree 'p' nill", "mode 0 7\npull 'p' nill", "mode 0 7\nspin 'p' nill", "mode 0 7\npush 'p' nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC019)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_invalid_char_scape
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "0.0.'\\N'")
        assert_match /ERROR CODE\:(\t| )?(0x3BC01A)/, stderr
        assert_equal 15, status.exitstatus
    end

    def test_invalid_char_size
        for console_input in ["0.0.'aaa'", "0.0.'aa"]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC01B)/, stderr
        assert_equal 15, status.exitstatus
        end
    end

    def test_columns
        for console_input in [
            "nill", "nill nill", "nill nill nill nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_match /ERROR CODE\:(\t| )?(0x3BC01C)/, stderr
        assert_equal 15, status.exitstatus
        end
    end
end
