DESTDIR ?=
PREFIX ?= /usr/local
CROSS_COMPILE ?=
VERSION = 4.0.1
SOVERSION = $(VERSION)

CC ?= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -g -O2

LD = $(CC)
LDFLAGS = -Wl,-rpath=.:$(PREFIX)

ifndef NO_VALGRIND
VALGRIND ?= valgrind
VALGRIND_FLAGS = --quiet
endif

.PHONY: all
all: libutf.so
	$(MAKE) -C examples

OBJECTS = \
	error.o \
	utf8.o \
	utf16.o \
	utf32.o \
	encoder.o \
	decoder.o \
	converter.o

HEADERS = \
	error.h \
	version.h \
	utf8.h \
	utf16.h \
	utf32.h \
	encoder.h \
	decoder.h \
	converter.h

ifndef NO_TESTS
TESTS += encoder-test decoder-test converter-test
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libutf.so: libutf.so.$(SOVERSION)
	ln -sf $< $@

libutf.so.$(SOVERSION): $(OBJECTS)
	$(LD) $(LDFLAGS) -shared $(OBJECTS) -o $@

%-test: %-test.c libutf.so
	$(LD) $(LDFLAGS) $< ./libutf.so -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f libutf.so
	rm -f libutf.so.$(SOVERSION)
	rm -f $(TESTS)
	$(MAKE) -C examples clean
	$(MAKE) -C doxygen clean

.PHONY: install
install:
	mkdir -p $(DESTDIR)/$(PREFIX)/include/libutf
	mkdir -p $(DESTDIR)/$(PREFIX)/lib
	cp -u $(HEADERS) $(DESTDIR)/$(PREFIX)/include/libutf
	cp -u libutf.so.$(SOVERSION) $(DESTDIR)/$(PREFIX)/lib/libutf.so.$(SOVERSION)
	ln -sf $(PREFIX)/lib/libutf.so.$(SOVERSION) $(DESTDIR)/$(PREFIX)/lib/libutf.so

.PHONY: test
test: $(TESTS)
	$(VALGRIND) $(VALGRIND_FLAGS) ./encoder-test
	$(VALGRIND) $(VALGRIND_FLAGS) ./decoder-test
	$(VALGRIND) $(VALGRIND_FLAGS) ./converter-test

