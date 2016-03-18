#!/bin/bash
set -e

if [ "$1" = "clean" ];
then
    make clean

    shift

    if [ "$#" -eq 0 ];
    then
        exit
    fi
fi

if [ "$1" = "dbg" ];
then
    run_prefix="gdb -ex run --args"

    shift
fi

target="$1"; shift

make -j5 "$target"

$run_prefix "build/$target" "$@"
