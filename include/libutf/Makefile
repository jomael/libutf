PREFIX ?= /usr/local
LIBUTF_BIG_ENDIAN ?= 0

.PHONY: all
all: config.h

config.h: config.h.in
	sed 's/@LIBUTF_BIG_ENDIAN@/$(LIBUTF_BIG_ENDIAN)/' $< > $@

.PHONY: clean
clean:
	rm -f config.h

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/include/libutf
	cp *.h $(DESTDIR)$(PREFIX)/include/libutf/

