CROSS_COMPILE ?=

CC ?= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -iquote..

EXAMPLES = sigma iconv

.PHONY: all
all: $(EXAMPLES)

sigma: sigma.c ../libutf.so
	$(CC) $(CFLAGS) $< -o $@ ../libutf.so

iconv: iconv.c ../libutf.so
	$(CC) $(CFLAGS) $< -o $@ ../libutf.so

../libutf.so:
	$(MAKE) -C .. libutf.so

.PHONY: clean
clean:
	rm -f $(EXAMPLES)

