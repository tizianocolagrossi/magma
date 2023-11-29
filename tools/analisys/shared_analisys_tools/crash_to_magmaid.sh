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

echo "Crash_to_magmaid REQUESTED" > /output/crash_to_magmaid_out.txt

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
    echo "$msg" >> /output/crash_to_magmaid_out.txt
    rm "/tmp/runonce.tmp"
done
echo "ANALISYS END"
echo "ANALISYS END" >> /output/crash_to_magmaid_out.txt



