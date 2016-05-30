#!/bin/sh

CC=gcc
CFLAGS="-Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC"

$CC $CFLAGS utf8.c utf16.c utf32.c encoder.c decoder.c error.c -shared -o libutfx.so
if [ $? != 0 ]; then
	exit 1
fi

