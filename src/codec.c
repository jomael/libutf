#include <libutf/codec.h>

utf_byte_count_t utf_codec_min_bytes(utf_codec_t codec){
	switch (codec){
	case UTF_CODEC_UTF8:
		return 1;
	case UTF_CODEC_UTF16_LE:
	case UTF_CODEC_UTF16_BE:
		return 2;
	case UTF_CODEC_UTF32_LE:
	case UTF_CODEC_UTF32_BE:
		return 4;
	}
	return 0;
}

