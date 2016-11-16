topdir ?= $(shell pwd)
DESTDIR ?=
PREFIX ?= /usr/local
CROSS_COMPILE ?=

VERSION = 4.0.1
SOVERSION = $(VERSION)

CC ?= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic

LD = $(CC)
LDFLAGS = -Wl,-rpath=.:$(PREFIX)

ifndef NO_VALGRIND
VALGRIND ?= valgrind
VALGRIND_FLAGS = --quiet
endif

