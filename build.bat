cl.exe /c /Wall /WX utf8.c utf16.c utf32.c encoder.c decoder.c

lib /out:utfx.lib utf8.obj utf16.obj utf32.obj encoder.obj decoder.obj

