topdir ?= ..

VPATH += $(topdir)/include/libutf
CFLAGS += -I $(topdir)/include

.PHONY: all
all: libutf libutf-dev

libutf: libutf.so.4.0.2

libutf-dev: libutf.a

OBJECTS += converter.o
OBJECTS += decoder.o
OBJECTS += encoder.o
OBJECTS += error.o
OBJECTS += utf8.o
OBJECTS += utf16.o
OBJECTS += utf32.o

pic_OBJECTS = $(OBJECTS:.o=-pic.o)

libutf.so.4.0.2: $(pic_OBJECTS)
	$(CC) -shared -Wl,-soname,libutf.so.4 -o libutf.so.4.0.2 $(pic_OBJECTS)

libutf.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

converter.o converter-pic.o: converter.c converter.h decoder.h encoder.h utf8.h utf16.h utf32.h

decoder.o decoder-pic.o: decoder.c decoder.h utf8.h utf16.h utf32.h

encoder.o encoder-pic.o: encoder.c encoder.h utf8.h utf16.h utf32.h

error.o error-pic.o: error.c error.h

utf8.o utf8-pic.o: utf8.c utf8.h utf32.h

utf16.o utf16-pic.o: utf16.c utf16.h utf32.h

utf32.o utf32-pic.o: utf32.c utf32.h

%.o: %.c
	$(CC) $(CFLAGS) -O2 -c $< -o $@

%-pic.o: %.c
	$(CC) $(CFLAGS) -O2 -fPIC -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(pic_OBJECTS)
	rm -f libutf.so.*
	rm -f libutf.so
	rm -f libutf.a

.PHONY: install
install:

.PHONY: test
test:

