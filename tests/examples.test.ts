import { assertEquals } from "https://deno.land/std@0.85.0/testing/asserts.ts";

/**
 * @file examples/helloworld.3bc
 */
Deno.test("Test Hello world!", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/heloworld.3bc"],
        stdout: "piped",
    });

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(output, "hello world!", "output");
    assertEquals(code, 0, "return code");

    await cmd.close();
});

/**
 * @file examples/input_login.3bc
 */
Deno.test("Test Input Login", async () => {
   const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/input_login.3bc"],
        stdout: "piped",
        stdin: "piped",
    });

    await cmd.stdin.write(new TextEncoder().encode("XXXXXXX"));
    await cmd.stdin.close();

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(output, "\n[?] login: XXX\n[?] password: ***\n\n[!] press any key.\n");
    assertEquals(code, 0, "return code");

    await cmd.close();
});

/**
 * @file examples/loop.3bc
 */
Deno.test("Test Looping", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/loop.3bc"],
        stdout: "piped",
    });

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(output, "HI!\nHI!\nHI!\n", "output");
    assertEquals(code, 0, "return code");

    await cmd.close();
});

/**
 * @file examples/loop.3bc
 */
Deno.test("Test Invert Default", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/invert_default.3bc"],
        stdout: "piped",
    });

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(output, "ABC CBA\n", "output");
    assertEquals(code, 0, "return code");

    await cmd.close();
});

/**
 * @file examples/loop.3bc
 */
Deno.test("Test Invert Helper", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/invert_helper.3bc"],
        stdout: "piped",
    });

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(output, "ABC CBA\n", "output");
    assertEquals(code, 0, "return code");

    await cmd.close();
});

/**
 * @file examples/math_average.3bc
 */
Deno.test("Test Math Average Helper", async () => {
    const tests = [
        {input:"888", output: "N1: 8\nN2: 8\nN3: 8\nA:8\n"},
        {input:"246", output: "N1: 2\nN2: 4\nN3: 6\nA:4\n"},
        {input:"198", output: "N1: 1\nN2: 9\nN3: 8\nA:6\n"}
    ];

    for (const test of tests) {
        const cmd = await Deno.run({
            cmd: ["./3bc.test.bin", "./examples/math_average.3bc"],
            stdout: "piped",
            stdin: "piped",
        });

        await cmd.stdin.write(new TextEncoder().encode(test.input));
        await cmd.stdin.close();

        const output = new TextDecoder().decode(await cmd.output());
        const { code } = await cmd.status();

        assertEquals(output, test.output);
        assertEquals(code, 0, "return code");

        await cmd.close();
    }
});

/**
 * @file examples/math_sortable.3bc
 */
Deno.test("Test Math Sort Helper", async () => {
    const tests = [
        {input:"123", output: "3x numbers: 123\nsort: 123\n"},
        {input:"321", output: "3x numbers: 321\nsort: 123\n"},
        {input:"312", output: "3x numbers: 312\nsort: 123\n"},
        {input:"231", output: "3x numbers: 231\nsort: 123\n"},
        {input:"132", output: "3x numbers: 132\nsort: 123\n"},
        {input:"213", output: "3x numbers: 213\nsort: 123\n"},
    ];

    for (const test of tests) {
        const cmd = await Deno.run({
            cmd: ["./3bc.test.bin", "./examples/math_sortable.3bc"],
            stdout: "piped",
            stdin: "piped",
        });

        await cmd.stdin.write(new TextEncoder().encode(test.input));
        await cmd.stdin.close();

        const output = new TextDecoder().decode(await cmd.output());
        const { code } = await cmd.status();

        assertEquals(output, test.output);
        assertEquals(code, 0, "return code");

        await cmd.close();
    }
});