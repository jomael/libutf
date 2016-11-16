topdir ?= ..

VPATH += $(topdir)/include/libutf
VPATH += $(topdir)/src

CFLAGS += -I $(topdir)/include

.PHONY: all
all: sigma iconv
sigma: sigma.c -lutf

iconv: iconv.c -lutf

.PHONY: clean
clean:
	rm -f sigma iconv

