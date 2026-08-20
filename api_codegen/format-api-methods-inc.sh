#!/bin/sh

set -eu

mode=$1
input=$2
style=$3
temporary_directory=$(mktemp -d)
wrapped=$temporary_directory/wrapped.h
formatted=$temporary_directory/formatted.h
output=$temporary_directory/output.inc.h

cleanup() {
    rm -f "$wrapped" "$formatted" "$output"
    rmdir "$temporary_directory"
}
trap cleanup EXIT HUP INT TERM

{
    printf 'class Api {\npublic:\n'
    sed '1,2d' "$input"
    printf '};\n'
} >"$wrapped"

clang-format --style="file:$style" "$wrapped" >"$formatted"

{
    sed -n '1p' "$input"
    printf '\n'
    sed -n '/^public:$/,/^};$/p' "$formatted" | sed '1d;$d'
} >"$output"

if [ "$mode" = "--check" ]; then
    if ! cmp -s "$input" "$output"; then
        printf '%s is not formatted\n' "$input" >&2
        exit 1
    fi
else
    mv "$output" "$input"
fi
