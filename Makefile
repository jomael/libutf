# no default targets
all:

utfx.lib: utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj
	lib /nologo utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj -out:utfx.lib

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

