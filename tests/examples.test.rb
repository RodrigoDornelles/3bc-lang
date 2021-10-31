require 'open3'
require 'minitest/spec'
require 'minitest/autorun'

class TestExample < Minitest::Test
    def test_fibonacci
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/fibonacci.3bc", :stdin_data => 9)
        assert_equal "", stderr
        assert_equal "FIB:9\n0\n1\n1\n2\n3\n5\n8\n13\n21", stdout
        assert_equal 0, status
    end

    def test_hello_world
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/heloworld.3bc")
        assert_equal "", stderr
        assert_equal "hello world!", stdout
        assert_equal 0, status
    end

    def test_input_login 
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/input_login.3bc", :stdin_data => "XXXXXXX")
        assert_equal "", stderr
        assert_equal "\n[?] login: XXX\n[?] password: ***\n\n[!] press any key.\n", stdout
        assert_equal 0, status
    end

    def test_loop_do_while
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/loop_do_while.3bc", :stdin_data => "t1yYn")
        assert_equal "", stderr
        assert_equal "\nREPEAT? [y/n]\nREPEAT? [y/n]\nREPEAT? [y/n]\nREPEAT? [y/n]", stdout
        assert_equal 0, status
    end

    def test_loop
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/loop.3bc")
        assert_equal "", stderr
        assert_equal "HI!\nHI!\nHI!\n", stdout
        assert_equal 0, status
    end

    def test_invert_default
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/invert_default.3bc")
        assert_equal "", stderr
        assert_equal "ABC CBA\n", stdout
        assert_equal 0, status
    end

    def test_invert_helper
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/invert_default.3bc")
        assert_equal "", stderr
        assert_equal "ABC CBA\n", stdout
        assert_equal 0, status
    end

    def test_invert_helper
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/invert_text.3bc", :stdin_data => 'socorram me subi no onibus em marrocos.')
        assert_equal "", stderr
        assert_equal "socorram me subi no onibus em marrocos..socorram me subino on ibus em marrocos", stdout
        assert_equal 0, status
    end

    def test_math_average
        for console in
        [
            {input:"888", output:"N1: 8\nN2: 8\nN3: 8\nA:8\n"},
            {input:"246", output:"N1: 2\nN2: 4\nN3: 6\nA:4\n"},
            {input:"198", output:"N1: 1\nN2: 9\nN3: 8\nA:6\n"}
        ]
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/math_average.3bc", :stdin_data => console[:input])
        assert_equal "", stderr
        assert_equal console[:output], stdout
        assert_equal 0, status
        end
    end

    def test_math_basics
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/math_basics.3bc")
        assert_equal "", stderr
        assert_equal "a,b=5,2\na+b=7\na-b=3\na*b=10\na/b=2\n", stdout
        assert_equal 0, status
    end

    def test_pointers
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/pointers.3bc")
        assert_equal "", stderr
        assert_equal "7", stdout
        assert_equal 0, status
    end

    def test_procedure
        stdout, stderr, status = Open3.capture3("./3bc.test.bin", "./examples/procedure.3bc")
        assert_equal "", stderr
        assert_equal "HelloWorld", stdout
        assert_equal 0, status
    end
end
