require 'open3'
require 'benchmark'
require 'minitest/spec'
require 'minitest/autorun'
require 'minitest/parallel'

class TestSleep < Minitest::Test
    def test_sleep_seconds
        skip "dont work correctly :/"
        exectuion = Benchmark.measure do
            stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => 'mode.0.43,seco.0.1,mode.0.2,stri.0.0')
            assert_equal "0", stdout
            assert_equal 0, status
        end
        assert_in_delta 1, exectuion.real, 0.05, 'minimum 50 millisecond precision'
    end

    def test_sleep_miliseconds
        exectuion = Benchmark.measure do
            stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => 'mode.0.43,mili.0.100,mode.0.2,stri.0.0')
            assert_equal "0", stdout
            assert_equal 0, status
        end
        assert_in_delta 0.1, exectuion.real, 0.04, 'minimum 40 millisecond precision'
    end

    def test_sleep_microseconds
        exectuion = Benchmark.measure do
            stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => 'mode.0.6,aloc.1.200,mode.0.8,0.0.1,push.1.0,mode.0.12,math.0.1,mode.0.8,pull.1.0,mode.0.43,micro.0.100,mode.0.9,fgto.0.1,mode.0.2,stri.0.0')
            assert_equal "0", stdout
            assert_equal 0, status
        end
        assert_in_delta 0.02, exectuion.real, 0.02, 'minimum 20 millisecond precision'
    end
end
