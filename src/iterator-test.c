#include <libutf/iterator.h>

#include <assert.h>

int main(void) {

	utf16_t u16[3] = { 0xd801, 0xdc37, 0x0024 };

	utf_string_t string;

	utf_iterator_t iterator;

	string.bits = 16;
	string.count = 3;
	string.count_res = 3;
	string.u.u16 = u16;

	utf_iterator_init(&iterator, &string);

	assert(utf_iterator_end(&iterator) == 0);

	assert(utf_iterator_get(&iterator) == 0x10437);

	assert(utf_iterator_next(&iterator) == UTF_ERROR_NONE);

	assert(utf_iterator_get(&iterator) == 0x0024);

	assert(utf_iterator_next(&iterator) == UTF_ERROR_NONE);

	assert(utf_iterator_end(&iterator) == 1);

	assert(utf_iterator_next(&iterator) == UTF_ERROR_EOF);

	return 0;
}
