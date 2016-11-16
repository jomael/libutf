topdir ?= ..

VPATH += $(topdir)/include/libutf
VPATH += $(topdir)/src

CFLAGS += -I $(topdir)/include

.PHONY: all
all: sigma iconv
sigma: sigma.c -lutf encoder.h utf8.h

iconv: iconv.c -lutf converter.h version.h

.PHONY: clean
clean:
	rm -f sigma iconv

