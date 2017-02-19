#include <libutf/codec.h>

const utf_string_t utf8_name_string = {
	8 /* bits */,
	5 /* unit count */,
	5 /* unit count reserved */,
	{ NULL, NULL, NULL },
	{ (const utf8_t *)("UTF-8") }
};

const utf_string_t * utf_codec_to_string(utf_codec_t codec){
	switch (codec){
	case UTF_CODEC_UTF8:
		return &utf8_name_string;
	default:
		break;
	}
	return NULL;
}

