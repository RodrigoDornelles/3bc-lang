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
 * @file examples/math_basics.3bc
 */
Deno.test("Test Math Basics", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin", "./examples/math_basics.3bc"],
        stdout: "piped",
    });

    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();

    assertEquals(code, 0, "return code");

    await cmd.close();
});