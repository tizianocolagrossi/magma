#!/bin/bash -e

##
# Pre-requirements:
# - FUZZER
# - PROGRAM
# - TARGET
# - IRUN
##

env

find_triggered()
{
    ##
    # Pre-requirements:
    # - $1: human-readable monitor output
    ##


    echo "$1" | while read line; do
        triggered=$(awk '{print $5}' <<< "$line")
        if [ ! -z $triggered ] && [ $triggered -ne 0 ]; then
            awk '{print $1}' <<< "$line"
            # return 1
        fi
    done
}

LIBRARY=$(echo "$TARGET" | sed "s,^[/][^\n]*[/],,")
FUZZERNAME=$(echo "$FUZZER" | sed "s,^[/][^\n]*[/],,")

echo "Crash_to_magmaid REQUESTED" > "/output/$FUZZERNAME,$LIBRARY,$PROGRAM,$IRUN"

# associate crash with bug_id
for crash_path in /input/*; do
    crash=$(echo "$crash_path" | sed s,^[/][^/]*[/],,) # remove /input/ from path

    cd "/tmp/"
    cp --force "$crash_path" "/tmp/runonce.tmp"
    output=$($OUT/monitor --fetch watch --dump human "$FUZZER/runonce.sh" "/tmp/runonce.tmp" || true)
    if [ "$output" = "" ]; then
        echo "continue"
        continue
    fi
    bug=$(find_triggered "$output")

    msg="$bug@$crash"
    echo "$msg"
    echo "$msg" >> "/output/$FUZZERNAME,$LIBRARY,$PROGRAM,$IRUN"
    rm "/tmp/runonce.tmp"
done




