#!/bin/bash -e

##
# Pre-requirements:
# - env FUZZER: fuzzer name (from fuzzers/)
# - env TARGET: target name (from targets/)
# - env PROGRAM: program name (name of binary artifact from $TARGET/build.sh)
# - env ARGS: program launch arguments
# - env FUZZARGS: fuzzer arguments
# - env POLL: time (in seconds) between polls
# - env TIMEOUT: time to run the campaign
# + env SHARED: path to host-local volume where fuzzer findings are saved
#       (default: no shared volume)
# + env AFFINITY: the CPU to bind the container to (default: no affinity)
# + env ENTRYPOINT: a custom entry point to launch in the container (default:
#       $MAGMA/run.sh)
##

cleanup() {
    if [ ! -t 1 ]; then
        docker rm -f $container_id &> /dev/null
    fi
    exit 0
}

trap cleanup EXIT SIGINT SIGTERM

if [ -z $FUZZER ] || [ -z $TARGET ] || [ -z $PROGRAM ]; then
    echo '$FUZZER, $TARGET, and $PROGRAM must be specified as' \
         'environment variables.'
    exit 1
fi

MAGMA=${MAGMA:-"$(cd "$(dirname "${BASH_SOURCE[0]}")/../../" >/dev/null 2>&1 \
    && pwd)"}
export MAGMA
source "$MAGMA/tools/captain/common.sh"

IMG_NAME="magma/$FUZZER/$TARGET"

if [ ! -z $AFFINITY ]; then
    flag_aff="--cpuset-cpus=$AFFINITY --env=AFFINITY=$AFFINITY"
fi


#### Here interesting for test purpose. (run different test routine each time)
flag_ep='--entrypoint=/magma_analisys/select.sh'
echo "$flag_ep"

#### Here interesting for test purpose. (map different test routine each time)
ANALISYS_DIR="$(realpath "$0")"
ANALISYS_DIR="$(dirname "$ANALISYS_DIR")"
ANALISYS_DIR="$ANALISYS_DIR/shared_analisys_tools/"

echo "$ANALISYS_DIR"

flag_volume_analisys="--volume=$ANALISYS_DIR:/magma_analisys"

flag_volume_input="--volume=$INPUT_DIR:/input/"
flag_volume_output="--volume=$OUTPUT_DIR:/output/"


if [ -t 1 ]; then
docker run -it --rm $flag_volume_analisys $flag_volume_input $flag_volume_output \
    --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
    --env=PROGRAM="$PROGRAM" --env=ARGS="$ARGS" \
    --env=FUZZARGS="$FUZZARGS" --env=POLL="$POLL" --env=TIMEOUT="$TIMEOUT" \
    --env=IRUN="$IRUN" \
    $flag_aff $flag_ep "$IMG_NAME" "$ANALISYS"
fi

##
# FUZZER=enumetric_asan TARGET=libtiff PROGRAM=tiff_read_rgba_fuzzer ANALISYS=crash_id INPUT_DIR=./testInput/findings/default/crashes/ OUTPUT_DIR=./testOuput/ ./tools/captain/start_analisys.sh
##