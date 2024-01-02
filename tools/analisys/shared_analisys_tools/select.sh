#!/bin/bash -e

analisys=$1

if [ "$analisys" = "crash_id" ]; then
    echo "Analisys crash_id requested"
    /magma_analisys/crash_to_magmaid.sh
elif [ "$analisys" = "dump_run_exe_lines" ]; then
    echo "Analisys dump_run_exe_lines requested"
    /magma_analisys/run_to_exe_lines.sh
else
    echo "No analisys requested or not found, spawning a shell"
    /bin/bash
fi
