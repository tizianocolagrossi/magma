#!/bin/bash -e

##
# Pre-requirements:
# - NONE
##

echo "test of custom entrypoint"

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


# associate crash with bug_id
for crash in /input/*; do
    

    cd "/tmp/"
    cp --force "$crash" "/tmp/runonce.tmp"
    output=$($OUT/monitor --fetch watch --dump human "$FUZZER/runonce.sh" "/tmp/runonce.tmp" || true)
    if [ "$output" = "" ]; then
        echo "continue"
        continue
    fi
    bug=$(find_triggered "$output")

    msg="$bug@$crash"
    echo "$msg"
    rm "/tmp/runonce.tmp"
done



