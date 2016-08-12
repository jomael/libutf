CROSS_COMPILE ?=
PREFIX ?= /usr/local
VERSION ?= 3.0.0
SOVERSION ?= $(VERSION)

CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -iquote..

CXX ?= g++
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++11 -iquote..

EXAMPLES = sigma iconv

ifndef NO_CPP
EXAMPLES += phi iconv-cpp
endif

.PHONY: all
all: ../libutfx.so.$(SOVERSION) $(EXAMPLES)

sigma: sigma.c
	$(CC) $(CFLAGS) $< -o $@ ../libutfx.so.$(SOVERSION)

iconv: iconv.c
	$(CC) $(CFLAGS) $< -o $@ ../libutfx.so.$(SOVERSION)

phi: phi.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ ../libutfx.so.$(SOVERSION)

iconv-cpp: iconv.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ ../libutfx.so.$(SOVERSION)

../libutfx.so.$(SOVERSION):
	$(MAKE) -C .. libutfx.so.$(SOVERSION)

.PHONY: clean
clean:
	rm -f $(EXAMPLES)

