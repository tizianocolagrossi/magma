#!/bin/bash -e


find /magma/ -name '*.dump' -size 0 -print -delete;

shopt -s globstar
for possibleDump in /magma/**/*.dump; do # Whitespace-safe and recursive
    echo "$possibleDump"
    ls -lh $possibleDump
done

bash