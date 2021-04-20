import { assertEquals } from "https://deno.land/std@0.85.0/testing/asserts.ts";

Deno.test("Channel 1 (MODE_DEBUG)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stderr: "piped"
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 1\nstri 0 0i9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.stderrOutput());
    const { code } = await cmd.status();
 
    assertEquals(output, "9a7a");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 2 (MODE_STRING)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 2\nstri 0 0d9\nstrc 0 'a'\nstro 0 0o7\nstrx 0 0xA"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "9a7a");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 3 (MODE_INPUT)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });
 
    const tests = [
        "mode 0 3\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4",
        "mode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0"
    ];

    await cmd.stdin.write(new TextEncoder().encode(tests.join("\n")));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "12341234");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 4 (MODE_INPUT_SILENT)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });

    const tests = [
        "mode 0 4\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4",
        "mode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0"
    ];
 
    await cmd.stdin.write(new TextEncoder().encode(tests.join("\n")));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "1234");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 5 (MODE_INPUT_PASSWORD)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });
 
    const tests = [
        "mode 0 5\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4",
        "mode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0"
    ];

    await cmd.stdin.write(new TextEncoder().encode(tests.join("\n")));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "****1234");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 5 (MODE_INPUT_PASSWORD)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });
 
    const tests = [
        "mode 0 5\nstri 1 0\n1\nstrc 2 0\n2\nstro 3 0\n3\nstrx 4 0\n4",
        "mode 0 2\nstri 1 0\nstrc 2 0\nstro 3 0\nstrx 4 0"
    ];

    await cmd.stdin.write(new TextEncoder().encode(tests.join("\n")));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "****1234");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

Deno.test("Channel 6 (MODE_MEMORY)", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
    });
 
    const tests = [
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
        "mode 0 6\ntmin 1 11\ntmax 1 13\ntcfg 1 0b1110\naloc 1 23\nmode 0 2\nstri 1 0\nmode 0 6\nfree 1 0",
    ];

    await cmd.stdin.write(new TextEncoder().encode(tests.join("\n")));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(output, "1888888131112131113111213111311121311");
    assertEquals(code, 0, "return code");
 
    await cmd.close();
});

