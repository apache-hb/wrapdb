#!/bin/sh

WORKDIR=$1
INPUT=$2
OUTPUT=$3
CMD=$4

cd "$WORKDIR"

# due to linker trickery (DT_SONAME) when modifying a shared library and linking the new copy
# into a program `ld` is able to figure out the original shared library the copy was made
# from, and then *actually* links that. To workaround this we overwrite the original binary
# with the new one so that both binaries are ok to link against.
go run $CMD -o "$INPUT" -in-object "$INPUT"
cp "$INPUT" "$OUTPUT"
