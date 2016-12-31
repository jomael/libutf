topdir ?= ..

VPATH += $(topdir)/include/libutf
CFLAGS += -I $(topdir)/include

.PHONY: all
all: libutf libutf-dev

libutf: libutf.so

libutf-dev: libutf.a

OBJECTS += converter.o
OBJECTS += decoder.o
OBJECTS += encoder.o
OBJECTS += error.o
OBJECTS += utf8.o
OBJECTS += utf16.o
OBJECTS += utf32.o

pic_OBJECTS = $(OBJECTS:.o=-pic.o)

TESTS += converter-test
TESTS += decoder-test
TESTS += encoder-test
TESTS += utf8-test
TESTS += utf16-test

ifndef NO_VALGRIND
VALGRIND ?= valgrind
VALGRINDFLAGS ?= --quiet --leak-check=full --error-exitcode=1
endif

libutf.so: libutf.so.4
	ln --force --symbolic $< $@

libutf.so.4: libutf.so.4.0.2
	ln --force --symbolic $< $@

libutf.so.4.0.2: $(pic_OBJECTS)
	$(CC) -shared -Wl,-rpath=$(PREFIX)/lib -Wl,-soname,libutf.so.4 -o libutf.so.4.0.2 $(pic_OBJECTS)

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
	$(CC) $(CFLAGS) -g -O2 -c $< -o $@

%-pic.o: %.c
	$(CC) $(CFLAGS) -O3 -fPIC -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(pic_OBJECTS)
	rm -f libutf.so.4.0.2
	rm -f libutf.so.4
	rm -f libutf.so
	rm -f libutf.a
	rm -f $(TESTS)

.PHONY: install
install: libutf libutf-dev
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp -u libutf.so.4.0.2 $(DESTDIR)$(PREFIX)/lib/
	ln --force --symbolic libutf.so.4.0.2 $(DESTDIR)$(PREFIX)/lib/libutf.so.4
	ln --force --symbolic libutf.so.4 $(DESTDIR)$(PREFIX)/lib/libutf.so
	cp -u libutf.a $(DESTDIR)$(PREFIX)/lib/

.PHONY: test
test: libutf $(TESTS)
	$(VALGRIND) $(VALGRINDFLAGS) ./converter-test
	$(VALGRIND) $(VALGRINDFLAGS) ./decoder-test
	$(VALGRIND) $(VALGRINDFLAGS) ./encoder-test
	$(VALGRIND) $(VALGRINDFLAGS) ./utf8-test
	$(VALGRIND) $(VALGRINDFLAGS) ./utf16-test

converter-test: converter-test.c libutf.a

decoder-test: decoder-test.c libutf.a

encoder-test: encoder-test.c libutf.a

utf8-test: utf8-test.c libutf.a

utf16-test: utf16-test.c libutf.a

