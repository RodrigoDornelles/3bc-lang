# Stage 1
from busybox:1.35-musl as compiler

COPY . /src
RUN wget https://ziglang.org/download/0.9.1/zig-linux-x86_64-0.9.1.tar.xz
RUN tar xf zig-linux-x86_64-0.9.1.tar.xz
RUN ./zig-linux-x86_64-0.9.1/zig cc src/programs/interpreter.c --target=x86_64-linux-musl -Os -static -o tbc

# Stage 2
FROM scratch
COPY --from=compiler /tbc /tbc
ENTRYPOINT ["/tbc"]
