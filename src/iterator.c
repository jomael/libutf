#include <libutf/iterator.h>

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

	unsigned long int bits = 0;
	utf32_t out = 0;

	if (utf_iterator_end(iterator)){
		return 0;
	}

	bits = iterator->string->bits;

	if (bits == 8){
		utf8_decode(&iterator->string->u.u8[iterator->unit_pos], &out);
	} else if (bits == 16){
		utf16_decode(&iterator->string->u.u16[iterator->unit_pos], &out);
	} else if (bits == 32){
		iterator->string->u.u32[iterator->unit_pos];
	}

	return out;
}

utf_error_t utf_iterator_next(utf_iterator_t * iterator){

	unsigned long int bits = 0;
	unsigned long int move_count = 0;

	if (utf_iterator_end(iterator)){
		return UTF_ERROR_EOF;
	}

	bits = iterator->string->bits;

	if (bits == 8){
		move_count = utf8_decode_length(iterator->string->u.u8[iterator->unit_pos]);
	} else if (bits == 16){
		move_count = utf16_decode_length(iterator->string->u.u16[iterator->unit_pos]);
	} else if (bits == 32){
		move_count = 1;
	}

	if (move_count == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	}

	iterator->pos++;
	iterator->unit_pos += move_count;

	return UTF_ERROR_NONE;
}

