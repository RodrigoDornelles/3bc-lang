require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestCpu < Minitest::Test
    def test_mode_1
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 1\nstri 0 0i9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA")
        assert_equal "9a7a", stderr
        assert_equal "", stdout
        assert_equal 0, status
    end

    def test_mode_2
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 2\nstri 0 0d9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA")
        assert_equal "", stderr
        assert_equal "9a7a", stdout
        assert_equal 0, status
    end

    def test_mode_3
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 3\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4\nmode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0")
        assert_equal "", stderr
        assert_equal "12341234", stdout
        assert_equal 0, status
    end

    def test_mode_4
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 4\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4\nmode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0")
        assert_equal "", stderr
        assert_equal "1234", stdout
        assert_equal 0, status
    end

    def test_mode_5
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => "mode 0 5\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4\nmode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0")
        assert_equal "", stderr
        assert_equal "****1234", stdout
        assert_equal 0, status
    end

    def test_mode_6
        console_input = [
            "mode 0 6\ntmin 1 0\ntmax 1 1\naloc 1 2\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 0\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 2\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 4\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 6\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 8\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 8\ntmax 1 9\ntcfg 1 0b1110\naloc 1 10\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 1\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 2\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 3\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 4\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 5\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 10\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 11\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 12\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 13\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 14\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 19\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 20\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 21\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 22\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
            "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 23\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0"
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console_input.join("\n"))
        assert_equal "1888888131112131113111213111311121311", stdout
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
            {input:"mode 0 26\nnb02 0 0b110\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"3"}, #TODO: base bin output
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
            {input:"mode 0 29\nnb02 0 0b1\nnb02 0 0b0\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"2"}, #TODO: base bin output
            {input:"mode 0 29\nnb08 0 0o7\nnb08 0 0o6\nmode 0 8\npull 'r' nill\nmode 0 2\nstro 'r' nill", output:"76"},
            {input:"mode 0 29\nnb10 0 0d9\nnb10 0 0d8\nmode 0 8\npull 'r' nill\nmode 0 2\nstri 'r' nill", output:"98"},
            {input:"mode 0 29\nnb16 0 0xF\nnb16 0 0xA\nmode 0 8\npull 'r' nill\nmode 0 2\nstrx 'r' nill", output:"fa"},
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", :stdin_data => console[:input])
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end
end 