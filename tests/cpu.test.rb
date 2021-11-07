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

    def test_mode_6
        console_input = [
            # TODO: MORE TESTS
            "mode.0.6,muse.1.16,muse.1.128,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
            "mode.0.6,muse.1.32,muse.1.128,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
            "mode.0.6,muse.1.32,aloc.1.0xFF,mode.0.2,stri.1.0,mode.0.6,free.1.0",
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "25500", stdout
        assert_equal 0, status
    end

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
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 9\nmode 0 19\nmath 0 0\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "-9", stdout
        assert_equal 0, status
    end

    def test_mode_21
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 21\nmath 0 3\nmath 0 6\nmath 0 9\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
         assert_equal "", stderr
        assert_equal "6", stdout
        assert_equal 0, status
    end

    def test_mode_22
        console_input = [
            "mode 0 22\nmath 0 -9\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 22\nmath 0 0\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 22\nmath 0 9\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "-101", stdout
        assert_equal 0, status
    end

    def test_mode_23
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 23\nmath 0 6\nmath 0 9\nmath 0 3\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "9", stdout
        assert_equal 0, status
    end

    def test_mode_24
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 24\nmath 0 6\nmath 0 3\nmath 0 9\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "3", stdout
        assert_equal 0, status
    end

    def test_mode_25
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 8\naloc 0 100\nmode 0 25\nmath 0 69\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill\nmode 0 25\nmath 0 609\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill\nmode 0 25\nmath 0 100\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill")
        assert_equal "", stderr
        assert_equal "69420420", stdout
        assert_equal 0, status
    end

    def test_mode_26
        for console in
        [
            {input:"mode 0 26\nnb02 0 0b110\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"3"}, #: base bin output
            {input:"mode 0 26\nnb08 0 0o137\nmode 0 8\npull 'r' nill\nmode 0 2\nstro 'r' nill", output:"731"},
            {input:"mode 0 26\nnb10 0 0d369\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"963"},
            {input:"mode 0 26\nnb16 0 0xABC\nmode 0 8\npull 'r' nill\nmode 0 2\nstrx 'r' nill", output:"cba"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_27
        console_input = [
            "mode 0 27\nmath 0 1\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 2\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 4\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 8\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 16\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 32\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 64\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 27\nmath 0 128\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "01234567", stdout
        assert_equal 0, status
    end

    def test_mode_28
        console_input = [
            "mode 0 28\nmath 0 1\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 28\nmath 0 10\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill",
            "mode 0 28\nmath 0 100\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "012", stdout
        assert_equal 0, status
    end

    def test_mode_29
        for console in
        [
            {input:"mode 0 29\nnb02 0 0b1\nnb02 0 0b0\nmode 0 8\npull 'r' nill\nmode 0 2\nstrb 'r' nill", output:"10"},
            {input:"mode 0 29\nnb08 0 0o7\nnb08 0 0o6\nmode 0 8\npull 'r' nill\nmode 0 2\nstro 'r' nill", output:"76"},
            {input:"mode 0 29\nnb10 0 0d9\nnb10 0 0d8\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"98"},
            {input:"mode 0 29\nnb16 0 0xF\nnb16 0 0xA\nmode 0 8\npull 'r' nill\nmode 0 2\nstrx 'r' nill", output:"fa"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_31
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode.0.31,math.0.0,mode.0.8,pull.1.0,mode.0.31,math.0.8,mode.0.8,pull.2.0,mode.0.2,stri.1.0,stri.2.0")
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
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.38,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.38,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.0,mode.0.38,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.38,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_mode_39
        for console in
        [
            {input:"mode.0.8,aloc.0.0,mode.0.39,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.1,mode.0.39,math.0.0,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
            {input:"mode.0.8,aloc.0.0,mode.0.39,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"0"},
            {input:"mode.0.8,aloc.0.1,mode.0.39,math.0.1,mode.0.8,pull.'r'.0,mode.0.2,stri.'r'.0", output:"1"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
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