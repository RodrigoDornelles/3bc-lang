require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestCpu < Minitest::Test
    def test_mode_1
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 1\nstrb 0 0b1\nstri 0 0i9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA")
        assert_equal "19a7a", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_mode_2
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 2\nstrb 0 0b1\nstri 0 0d9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA")
        assert_equal "", stderr
        assert_equal "19a7a", stdout
        assert_equal 0, status
    end

    def test_mode_3
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 3\nstrb 1 0\n1\nstro 2 0\n2\nstri 3 0\n3\nstrx 4 0\n4strc 5 0\n5\nmode 0 2\nstrb 1 0\nstro 2 0\nstri 3 0\nstrx 4 0\nstrc 5 0")
        assert_equal "", stderr
        assert_equal "1234512345", stdout
        assert_equal 0, status
    end

    def test_mode_4
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 4\nstrb 1 0\n1\nstro 2 0\n2\nstri 3 0\n3\nstrx 4 0\n4strc 5 0\n5\nmode 0 2\nstrb 1 0\nstro 2 0\nstri 3 0\nstrx 4 0\nstrc 5 0")
        assert_equal "", stderr
        assert_equal "12345", stdout
        assert_equal 0, status
    end

    def test_mode_5
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 5\nstrb 1 0\n1\nstro 2 0\n2\nstri 3 0\n3\nstrx 4 0\n4strc 5 0\n5\nmode 0 2\nstrb 1 0\nstro 2 0\nstri 3 0\nstrx 4 0\nstrc 5 0")
        assert_equal "", stderr
        assert_equal "*****12345", stdout
        assert_equal 0, status
    end

=begin TODO: REWORK
    def test_mode_6
        console_input = [
            "mode.0.6,muse.1.16,muse.1.128,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
            "mode.0.6,muse.1.32,muse.1.128,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
            "mode.0.6,muse.1.32,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "25500", stdout
        assert_equal 0, status
    end
=end

    def test_mode_7
        console_input = [
            "mode 0 6\naloc 'p' 'a'\naloc 'a' 2\naloc 'b' 3\nmode 0 7\npush 'p' nill",
            "mode 0 6\naloc 'p' 'b'\nmode 0 7\nspin 'p' nill",
            "mode 0 6\naloc 'p' 'a'\nmode 0 7\npull 'p' nill\nmode 0 2\nstri 'a' nill\nstri 'b' nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "32", stdout
        assert_equal 0, status
    end

    def test_mode_8
        console_input = [
            "mode 0 8\naloc 0 1\npull 1 0\nfree 0 0\npull 2 0\naloc 0 8\npull 3 0\naloc 0 4\nspin 3 0\npull 4 0",
            "mode 0 2\nstri 1 0\nstri 2 0\nstri 3 0\nstri 4 0"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "1048", stdout
        assert_equal 0, status
    end

    def test_mode_9
        for console in
        [
            {input:"mode 0 9\ngoto 0 1\nmode 0 2\nstrc 0 'H'\nnill nill 1\nstrc 0 'o'\nstrc 0 'l'\nstrc 0 'a'\n", output:"ola"},
            {input:"mode 0 8\naloc 0 1\nmode 0 9\nfgto 0 1\nzgto 0 2\nmode 0 2\nstri 0 0\n0 0 1\nstri 0 1\n0 0 2\nstri 0 2", output:"12"},
            {input:"mode 0 9\nfgto 0 1\nzgto 0 2\nmode 0 2\n0 0 1\nstri 0 0\n0 0 2\nstri 0 2", output:"2"},
            {input:"mode 0 8\naloc 0 1\nmode 0 9\npgto 0 1\ngoto 0 2\nmode 0 2\nstri 0 0\n0 0 1\nstri 0 1\n0 0 2\nstri 0 2", output:"12"},
            {input:"mode 0 8\naloc 0 -1\nmode 0 9\nngto 0 1\ngoto 0 2\nmode 0 2\nstri 0 0\n0 0 1\nstri 0 1\n0 0 2\nstri 0 2", output:"12"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal "", stderr
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_11
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 11\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "12", stdout
        assert_equal 0, status
    end

    def test_mode_12
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 12\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "4", stdout
        assert_equal 0, status
    end

    def test_mode_13
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 13\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "32", stdout
        assert_equal 0, status
    end

    def test_mode_14
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 14\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "2", stdout
        assert_equal 0, status
    end

    def test_mode_15
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 15\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "0", stdout
        assert_equal 0, status
    end

    def test_mode_16
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 8\nmode 0 16\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "4096", stdout
        assert_equal 0, status
    end

    def test_mode_17
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 9\nmode 0 17\nmath 0 2\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "3", stdout
        assert_equal 0, status
    end

    def test_mode_18
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 -9\nmode 0 18\nmath 0 0\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "9", stdout
        assert_equal 0, status
    end

    def test_mode_19
        for console in
        [
            {input:"mode.0.19,nb02.0.0b1,nb02.0.0b0,mode.0.8,pull.'r'.nill,mode.0.2,strb.'r'.nill",output:"10"},
            {input:"mode.0.19,nb08.0.0o7,nb08.0.0o6,mode.0.8,pull.'r'.nill,mode.0.2,stro.'r'.nill",output:"76"},
            {input:"mode.0.19,nb10.0.0d9,nb10.0.0d8,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",output:"98"},
            {input:"mode.0.19,nb16.0.0xF,nb16.0.0xA,mode.0.8,pull.'r'.nill,mode.0.2,strx.'r'.nill",output:"fa"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_21
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b10,mode.0.21,math.0.0,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "-11", stdout
        assert_equal 0, status
    end

    def test_mode_22
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.22,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "1000", stdout
        assert_equal 0, status
    end 

    def test_mode_23
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.23,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "1110", stdout
        assert_equal 0, status
    end 

    def test_mode_24
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.24,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "110", stdout
        assert_equal 0, status
    end 

    def test_mode_25
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.25,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "-1001", stdout
        assert_equal 0, status
    end 

    def test_mode_26
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.26,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "-1111", stdout
        assert_equal 0, status
    end 

    def test_mode_27
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b1100,mode.0.27,math.0.0b1010,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "-111", stdout
        assert_equal 0, status
    end 

    def test_mode_28
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b10,mode.0.28,math.0.0b1,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "100", stdout
        assert_equal 0, status
    end 

    def test_mode_29
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.8,aloc.0.0b10,mode.0.29,math.0.0b1,mode.0.8,pull.1.0,mode.0.2,strb.1.0")
        assert_equal "", stderr
        assert_equal "1", stdout
        assert_equal 0, status
    end 

    def test_mode_31
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.31,math.0.0,mode.0.8,pull.1.0,aloc.0.8,mode.0.31,math.0.0,mode.0.8,pull.2.0,mode.0.2,stri.1.0,stri.2.0")
        assert_equal "", stderr
        assert_equal "10", stdout
        assert_equal 0, status
    end

    def test_mode_32
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.32,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.32,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.0,mode.0.32,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.32,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_33
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.33,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.33,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.0,mode.0.33,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.33,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_34
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.34,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.34,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.0,mode.0.34,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.34,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_35
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.35,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.35,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.0,mode.0.35,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.35,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_36
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.36,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.36,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.0,mode.0.36,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.36,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_37
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.37,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.37,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.0,mode.0.37,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.37,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_38
        console_input = [
            "mode.0.8,aloc.0.1,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.2,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.4,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.8,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.16,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.32,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.64,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.128,mode.0.38,math.0.2,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.1,mode.0.38,math.0.8,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.8,mode.0.38,math.0.8,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.64,mode.0.38,math.0.8,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.1,mode.0.38,math.0.10,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.10,mode.0.38,math.0.10,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.100,mode.0.38,math.0.10,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "01234567012012", stdout
        assert_equal 0, status
    end

    def test_mode_39
        console_input = [
            "mode.0.8,aloc.0.1,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.5,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.15,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.40,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.100,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
            "mode.0.8,aloc.0.255,mode.0.39,math.0.0,mode.0.8,pull.'r'.nill,mode.0.2,stri.'r'.nill",
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "012345", stdout
        assert_equal 0, status
    end

    def test_mode_41
        for console_input in [
            "mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure,stri.0.4,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure,mode.0.2,stri.0.2",
            "mode.0.8,aloc.0.1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.41,nill.0.:procedure,zret.0.0,mode.0.2,stri.0.4,mode.0.41,fret.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure,mode.0.2,stri.0.2",
            "mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.41,nill.0.:procedure,fret.0.0,pret.0.0,nret.0.0,mode.0.2,stri.0.4,mode.0.41,zret.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure,mode.0.2,stri.0.2",
            "mode.0.8,aloc.0.1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.41,nill.0.:procedure,zret.0.0,nret.0.0,mode.0.2,stri.0.4,mode.0.41,pret.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure,mode.0.2,stri.0.2",
            "mode.0.8,aloc.0.-1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.41,nill.0.:procedure,zret.0.0,pret.0.0,mode.0.2,stri.0.4,mode.0.41,nret.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure,mode.0.2,stri.0.2"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_equal "42", stdout
        assert_equal 0, status
        end
    end

    def test_mode_42 
        for console_input in [
            "mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure2,stri.0.2,mode.0.41,back.0.0,mode.0.2,nill.0.:procedure1,stri.0.4,mode.0.42,call.0.:procedure2,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,call.0.:procedure1",
            "mode.0.8,aloc.0.1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure2,stri.0.2,mode.0.41,back.0.0,mode.0.2,nill.0.:procedure1,stri.0.4,stri.0.2,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,zcal.0.:procedure2,fcal.0.:procedure1",
            "mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure2,stri.0.2,mode.0.41,back.0.0,mode.0.2,nill.0.:procedure1,stri.0.4,stri.0.2,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,fcal.0.:procedure2,pcal.0.:procedure2,ncal.0.:procedure2,zcal.0.:procedure1",
            "mode.0.8,aloc.0.1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure2,stri.0.2,mode.0.41,back.0.0,mode.0.2,nill.0.:procedure1,stri.0.4,stri.0.2,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,zcal.0.:procedure2,ncal.0.:procedure2,pcal.0.:procedure1",
            "mode.0.8,aloc.0.-1,mode.0.9,goto.0.:entry,mode.0.2,stri.0.6,mode.0.2,nill.0.:procedure2,stri.0.2,mode.0.41,back.0.0,mode.0.2,nill.0.:procedure1,stri.0.4,stri.0.2,mode.0.41,back.0.0,mode.0.2,stri.0.9,mode.0.42,nill.0.:entry,zcal.0.:procedure2,pcal.0.:procedure2,ncal.0.:procedure1",
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input)
        assert_equal "42", stdout
        assert_equal 0, status
        end
    end

end 