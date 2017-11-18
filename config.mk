export topdir ?= $(shell pwd)
export DESTDIR ?=
export PREFIX ?= /usr/local
export CROSS_COMPILE ?=

export VERSION = 4.0.1

export CC = $(CROSS_COMPILE)gcc
export CFLAGS = -Wall -Wextra -Werror -Wfatal-errors

ifndef NO_VALGRIND
export VALGRIND ?= valgrind
export VALGRIND_FLAGS = --quiet
endif

