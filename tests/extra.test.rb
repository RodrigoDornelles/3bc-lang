require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestFails < Minitest::Test
=begin DECREPTED
    def test_clamp_input
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,mmin.1.2,mmax.2.1,mode.0.4,stri.1.0,12,stri.2.0,21,mode.0.2,stri.1.0,stri.2.0")
        assert_equal "", stderr
        assert_equal "21", stdout
        assert_equal 0, status
    end
=end

    def test_scapes
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.10,4.0.0,mode.0.2,strc.0.'\\0',strc.0.'\\a',strc.0.'\\b',strc.0.'\\t',strc.0.'\\n',strc.0.'\\'',strc.0.'\\\\'")
        assert_equal "", stderr
        assert_equal "000708090A275C", stdout
        assert_equal 0, status
    end

    def test_labels
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

    def test_signal_sigint
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "7.0.10,1.0.2")
        assert_match "", stderr
        assert_equal 2, status.exitstatus
    end

    def test_memory_clean_unstarted
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,free.6.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_memory_clean_right_unbalanced
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,aloc.1.0,aloc.2.0,aloc.3.0,aloc.4.0,free.2.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_memory_clean_two_childrens
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,aloc.4.0,aloc.3.0,aloc.2.0,aloc.1.0,free.3.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_memory_clean_left_unbalanced
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,aloc.5.0,aloc.4.0,aloc.3.0,aloc.2.0,aloc.1.0,free.3.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_memory_node_child_left
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.6,aloc.2.0,aloc.1.0,free.2.0")
        assert_equal "", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end
end
