#!/bin/bash -e

analisys=$1

if [ "$analisys" = "crash_id" ]; then
    echo "Analisys crash_id requested"
    /magma_analisys/crash_to_magmaid.sh
else
    echo "No analisys requested or not found, spawning a shell"
    /bin/bash
fi


