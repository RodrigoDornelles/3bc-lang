import { assertArrayIncludes, assertEquals } from "https://deno.land/std@0.85.0/testing/asserts.ts";

Deno.test("Error CPU Zero", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("strc 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 2, "return code");
 
    await cmd.close();
});

Deno.test("Error CPU Protected", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 7\nstrc 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 3, "return code");
 
    await cmd.close();
});

Deno.test("Error CPU reserved", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 10\nstri 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 4, "return code");
 
    await cmd.close();
});

Deno.test("Error Invalid Register", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 11\naloc 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 5, "return code");
 
    await cmd.close();
});

Deno.test("Error Invalid Address", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode e nill"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 6, "return code");
 
    await cmd.close();
});

Deno.test("Error Invalid Constant", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode nill e"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 7, "return code");
 
    await cmd.close();
});

Deno.test("Error Invalid CPU", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode nill full"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 8, "return code");
 
    await cmd.close();
});

Deno.test("Error Invalid Label", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("nill nill 2\nnill nill 1"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 9, "return code");
 
    await cmd.close();
});

Deno.test("Error Param Duality", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 2\nstri 1 1"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 10, "return code");
 
    await cmd.close();
});

Deno.test("Error Required Value", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 9\ngoto 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 11, "return code");
 
    await cmd.close();
});

Deno.test("Error Required Address", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 6\nfree 0 0"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 12, "return code");
 
    await cmd.close();
});

Deno.test("Error Number no digits", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 --"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 15, "return code");
 
    await cmd.close();
});

Deno.test("Error Number wrong base", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 0o8"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertArrayIncludes([18, 19, 20], [code], "return code");
 
    await cmd.close();
});

Deno.test("Error Number Dirty", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 2i"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 20, "return code");
 
    await cmd.close();
});

Deno.test("Error Memory Config", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 6\ntcfg 8 8"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 25, "return code");
 
    await cmd.close();
});

Deno.test("Error Memory Clamp", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 6\ntmin 1 2\ntmax 1 1"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 26, "return code");
 
    await cmd.close();
});

Deno.test("Error Helper MaxMin", async () => {
    const cmd = await Deno.run({
        cmd: ["./3bc.test.bin"],
        stdin: "piped",
        stdout: "piped",
        stderr: "null",
    });
 
    await cmd.stdin.write(new TextEncoder().encode("mode 0 23\nmode 0 23"));
    await cmd.stdin.close();
 
    const output = new TextDecoder().decode(await cmd.output());
    const { code } = await cmd.status();
 
    assertEquals(code, 27, "return code");
 
    await cmd.close();
});