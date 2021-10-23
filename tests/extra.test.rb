require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestFails < Minitest::Test
    def test_extra_labels
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.9,goto.0.:entry,mode.0.2,0.0.1,strc.0.'e',0.0.2,strc.0.'d',0.0.129,strc.0.'c',0.0.128,strc.0.'b' ,0.0.127,strc.0.'a',strc.0.'.',mode.0.41,back.0.0,mode.0.42,0.0.:entry,call.0.127,call.0.128,call.0.129,call.0.2,call.0.1")
        assert_equal "", stderr
        assert_equal "a.ba.cba.dcba.edcba.", stdout
        assert_equal 0, status
    end

    def test_nop
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "0.0.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end
end
