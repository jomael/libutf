DOXYGEN ?= doxygen
DOXYGEN_FLAGS =

PREFIX ?= /usr/local

.PHONY: all
all:
	$(DOXYGEN) $(DOXYGEN_FLAGS) Doxyfile

.PHONY: clean
clean:
	rm -Rf html
	rm -Rf latex
	rm -Rf man

# assumes a UNIX environment
.PHONY: install
install: all
	mkdir $(DESTDIR)$(PREFIX)/share/man/man3
	cp -R man/man3/*.3 $(DESTDIR)$(PREFIX)/share/man/man3

