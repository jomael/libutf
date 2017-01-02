#include <libutf/string.h>

#include <assert.h>

static void test_compare(void);

int main(void){

	return 0;
}

static void test_compare(void){

	utf_error_t error;

	utf_string_t a;
	utf_string_t b;

	utf_string_init(&a);
	utf_string_init(&b);

	error = utf_string_copy_utf8(&a, (const utf8_t *)("bcd"), 3);
	assert(error == UTF_ERROR_NONE);

	error = utf_string_copy_utf8(&b, (const utf8_t *)("bcd"), 3);
	assert(error == UTF_ERROR_NONE);

	assert(utf_string_compare(&a, &b) == 0);

	b.u.u8[0] = 'a';
	assert(utf_string_compare(&a, &b) == 1);

	b.u.u8[0] = 'c';
	assert(utf_string_compare(&a, &b) == -1);

	utf_string_free(&a);
	utf_string_free(&b);
}

