CROSS_COMPILE ?=

CC ?= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -iquote..

CXX ?= $(CROSS_COMPILE)g++
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++11 -iquote..

EXAMPLES = sigma iconv

ifndef NO_CPP
EXAMPLES += phi iconv-cpp
endif

.PHONY: all
all: $(EXAMPLES)

sigma: sigma.c ../libutfx.so
	$(CC) $(CFLAGS) $< -o $@ ../libutfx.so

iconv: iconv.c ../libutfx.so
	$(CC) $(CFLAGS) $< -o $@ ../libutfx.so

phi: phi.cpp ../libutfx.so
	$(CXX) $(CXXFLAGS) $< -o $@ ../libutfx.so

iconv-cpp: iconv.cpp ../libutfx.so
	$(CXX) $(CXXFLAGS) $< -o $@ ../libutfx.so

../libutfx.so:
	$(MAKE) -C .. libutfx.so

.PHONY: clean
clean:
	rm -f $(EXAMPLES)

