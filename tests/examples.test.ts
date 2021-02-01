import { exec, OutputMode } from "https://deno.land/x/exec/mod.ts";

Deno.test("First test (NO API)", async () => {
    let cmd = await exec('./3bc.test.bin ./examples/heloworld.3bc',{
        output: OutputMode.Capture
    });
      
   console.log(cmd);
});