require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestSleep < Minitest::Test
    # TODO: test interrupt accuracy.
    def test_mode_43
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => 'mode.0.43,real.0.2,fake.0.2,micr.0.2,mili.0.2,seco.0.1,mode.0.2,strc.0.\'!\'')
        assert_equal "!", stdout
        assert_equal 0, status
    end
end
