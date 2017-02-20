#include <libutf/iterator.h>

#include <libutf/utf8.h>
#include <libutf/utf16.h>
#include <libutf/utf32.h>

void utf_iterator_init(utf_iterator_t * iterator, const utf_string_t * string){
	iterator->string = string;
	iterator->pos = 0;
	iterator->unit_pos = 0;
}

unsigned long int utf_iterator_avail(const utf_iterator_t * iterator){
	if (utf_iterator_end(iterator)){
		return 0;
	}
	return iterator->string->count - iterator->pos;
}

unsigned long int utf_iterator_count(const utf_iterator_t * iterator){
	return iterator->string->count;
}

int utf_iterator_end(const utf_iterator_t * iterator){
	if (iterator->unit_pos >= iterator->string->count){
		return 1;
	}
	return 0;
}

utf32_t utf_iterator_get(const utf_iterator_t * iterator){

	utf_codec_t codec;
	utf32_t out = 0;

	if (utf_iterator_end(iterator)){
		return 0;
	}

	codec = iterator->string->codec;

	if (codec == UTF_CODEC_UTF8){
		utf8_decode(&iterator->string->data_const.u8[iterator->unit_pos], &out);
	} else if (codec == UTF_CODEC_UTF16){
		utf16_decode(&iterator->string->data_const.u16[iterator->unit_pos], &out);
	} else if (codec == UTF_CODEC_UTF32){
		out = iterator->string->data_const.u32[iterator->unit_pos];
	}

	return out;
}

utf_error_t utf_iterator_next(utf_iterator_t * iterator){

	utf_codec_t codec;
	unsigned long int move_count = 0;

	if (utf_iterator_end(iterator)){
		return UTF_ERROR_EOF;
	}

	codec = iterator->string->codec;

	if (codec == UTF_CODEC_UTF8){
		move_count = utf8_decode_length(iterator->string->data_const.u8[iterator->unit_pos]);
	} else if (codec == UTF_CODEC_UTF16){
		move_count = utf16_decode_length(iterator->string->data_const.u16[iterator->unit_pos]);
	} else if (codec == UTF_CODEC_UTF32){
		move_count = 1;
	}

	if (move_count == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	}

	iterator->pos++;
	iterator->unit_pos += move_count;

	return UTF_ERROR_NONE;
}

void utf_iterator_reset(utf_iterator_t * iterator){
	iterator->pos = 0;
	iterator->unit_pos = 0;
}

