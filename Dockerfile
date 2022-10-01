# Stage 1
from debian:11.5-slim as compiler

COPY . /src
RUN apt -y update && apt install -y musl-tools
RUN musl-gcc src/programs/interpreter.c -Os -lm --static -o /tbc
RUN strip /tbc

# Stage 2
FROM scratch
COPY --from=compiler /tbc /tbc
ENTRYPOINT ["/tbc"]
