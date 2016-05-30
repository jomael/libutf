# This Makefile is suppose to be compatible with both GNU's Make and Microsoft's NMake.
# For that reason, you may see lacking some of the awesome features of GNU's make for portabilty reasons.

# no default targets
all:
	@echo available targets:
	@echo utfx.lib
	@echo utfx.dll
	@echo libutfx.a
	@echo libutfx.so

utfx.lib: utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj error.obj
	lib /nologo utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj error.obj -out:utfx.lib

utfx.dll: utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj error.obj
	link /nologo /dll utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj error.obj -out:utfx.dll

libutfx.a: utf8.o utf16.o utf32.o encoder.o decoder.o error.o
	$(AR) $(ARFLAGS) libutfx.a utf8.o utf16.o utf32.o encoder.o decoder.o error.o

libutfx.so: utf8.o utf16.o utf32.o encoder.o decoder.o error.o
	$(CC) -shared -o libutfx.so utf8.o utf16.o utf32.o encoder.o decoder.o error.o

utf8.obj: utf8.c utf8.h utf32.h
	$(CC) /nologo /Wall /WX /c utf8.c /Foutf8.obj

utf16.obj: utf16.c utf16.h utf32.h
	$(CC) /nologo /Wall /WX /c utf16.c /Foutf16.obj

utf32.obj: utf32.c utf32.h
	$(CC) /nologo /Wall /WX /c utf32.c /Foutf32.obj

encoder.obj: encoder.c encoder.h utf8.h utf16.h utf32.h
	$(CC) /nologo /Wall /WX /c encoder.c /Foencoder.obj

decoder.obj: decoder.c decoder.h utf8.h utf16.h utf32.h
	$(CC) /nologo /Wall /WX /c decoder.c /Fodecoder.obj

error.obj: error.c error.h
	$(CC) /nologo /Wall /WX /c error.c /Foerror.obj

utf8.o: utf8.c utf8.h utf32.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c utf8.c -o utf8.o

utf16.o: utf16.c utf16.h utf32.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c utf16.c -o utf16.o

utf32.o: utf32.c utf32.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c utf32.c -o utf32.o

encoder.o: encoder.c encoder.h utf32.h error.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c encoder.c -o encoder.o

decoder.o: decoder.c decoder.h utf32.h error.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c decoder.c -o decoder.o

error.o: error.c error.h
	$(CC) -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -fPIC -c error.c -o error.o

