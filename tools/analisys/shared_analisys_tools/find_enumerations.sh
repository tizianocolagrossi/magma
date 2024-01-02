#!/bin/bash -e


find /magma/ -name '*.dump' -size 0 -print -delete;

OutFile="/tmp/EnumerationFoundTotal.dump"
touch "$OutFile"

shopt -s globstar
for possibleDump in /magma/**/*.dump; do # Whitespace-safe and recursive
    # echo "$possibleDump"
    ls -lh $possibleDump
    echo "------------" >> $OutFile
    cat $possibleDump >> $OutFile
done

if test -d /output/; then
    echo "output directory exist."
    mv $OutFile /output/
else
    echo "output directory not defined."
    echo "dump at $OutFile"
    echo "spawning a shell"
    bash
fi


