include config.mk

.PHONY: all
all:
	$(MAKE) -C include/libutf
	$(MAKE) -C src
	$(MAKE) -C doxygen
	$(MAKE) -C examples

.PHONY: clean
clean:
	$(MAKE) -C include/libutf clean
	$(MAKE) -C src clean
	$(MAKE) -C doxygen clean
	$(MAKE) -C examples clean

.PHONY: test
test:
	$(MAKE) -C src test

.PHONY: install
install:
	$(MAKE) -C include/libutf install
	$(MAKE) -C src install
	$(MAKE) -C doxygen install

