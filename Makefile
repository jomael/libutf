# This Makefile is suppose to be compatible with both GNU's Make and Microsoft's NMake.
# For that reason, you may see lacking some of the awesome features of GNU's make for portabilty reasons.

# no default targets
all:
	@echo available targets
	@echo utfx.lib (uses MSVC)
	@echo utfx.dll (uses MSVC)

utfx.lib: utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj
	lib /nologo utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj -out:utfx.lib

utfx.dll: utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj
	link /nologo /dll utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj -out:utfx.dll

utf8.obj: utf8.c utf8.h utf32.h
	cl /nologo /Wall /WX /c utf8.c /Foutf8.obj

utf16.obj: utf16.c utf16.h utf32.h
	cl /nologo /Wall /WX /c utf16.c /Foutf16.obj

utf32.obj: utf32.c utf32.h
	cl /nologo /Wall /WX /c utf32.c /Foutf32.obj

encoder.obj: encoder.c encoder.h utf8.h utf16.h utf32.h
	cl /nologo /Wall /WX /c encoder.c /Foencoder.obj

decoder.obj: decoder.c decoder.h utf8.h utf16.h utf32.h
	cl /nologo /Wall /WX /c decoder.c /Fodecoder.obj

