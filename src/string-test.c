#include <libutf/string.h>

#include <assert.h>

static void test_compare(void);

static void test_insert(void);

int main(void){
	test_compare();
	test_insert();
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

	b.data.u8[0] = 'a';
	assert(utf_string_compare(&a, &b) == 1);

	b.data.u8[0] = 'c';
	assert(utf_string_compare(&a, &b) == -1);

	utf_string_free(&a);
	utf_string_free(&b);
}

static void test_insert(void){

	utf_error_t error;
	utf_string_t string;

	utf_string_init(&string);

	error = utf_string_copy_asciiz(&string, "Hello, !");
	assert(error == UTF_ERROR_NONE);

	error = utf_string_insert_asciiz(&string, "Bill", 7);
	assert(error == UTF_ERROR_NONE);

	assert(utf_string_compare_asciiz(&string, "Hello, Bill!") == 0);

	utf_string_free(&string);
}

