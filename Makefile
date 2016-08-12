PREFIX ?= /usr/local
CROSS_COMPILE ?=
VERSION = 3.0.0
SOVERSION = $(VERSION)

CC ?= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -g -O2

CXX ?= $(CROSS_COMPILE)g++
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++11 -fPIC -g -O2

ifndef NO_CPP
LD = $(CXX)
else
LD = $(CC)
endif
LDFLAGS = -Wl,-rpath=.:$(PREFIX)

ifndef NO_VALGRIND
VALGRIND ?= valgrind
endif

.PHONY: all
all: libutfx.so.$(SOVERSION)

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

ifndef NO_CPP
OBJECTS += ctypes-cpp.o encoder-cpp.o decoder-cpp.o converter-cpp.o stl-cpp.o
HEADERS += ctypes.hpp encoder.hpp decoder.hpp converter.hpp stl.hpp
endif

ifndef NO_TESTS
TESTS += encoder-test decoder-test converter-test
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%-cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

libutfx.so.$(SOVERSION): $(OBJECTS)
	$(LD) $(LDFLAGS) -shared $(OBJECTS) -o $@

%-test: %-test.c libutfx.so.$(SOVERSION)
	$(LD) $(LDFLAGS) encoder-test.c ./libutfx.so.$(SOVERSION) -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f libutfx.so.$(SOVERSION)
	rm -f $(TESTS)

.PHONY: install
install:
	mkdir -p $(PREFIX)/include/utfx
	mkdir -p $(PREFIX)/lib
	cp -u $(HEADERS) $(PREFIX)/include/utfx
	cp -u libutfx.so.$(SOVERSION) $(PREFIX)/lib/libutfx.so.$(SOVERSION)

.PHONY: test
test: $(TESTS)
	$(VALGRIND) ./encoder-test
	$(VALGRIND) ./decoder-test
	$(VALGRIND) ./converter-test

