#include <libutf/string.h>

#include <assert.h>
#include <string.h>

static void test_compare(void);

static void test_copy(void);

static void test_insert(void);

int main(void){
	test_compare();
	test_copy();
	test_insert();
	return 0;
}

static void test_compare(void){

	struct utf_string a;
	struct utf_string b;
	utf_string_init(&a);
	utf_string_init(&b);

	assert(utf_string_copy_utf32(&a, U"bcd") == 0);
	assert(utf_string_copy_utf32(&b, U"bcd") == 0);

	assert(utf_string_compare(&a, &b) == 0);

	b.data[0] = U'a';
	assert(utf_string_compare(&a, &b) == 1);

	b.data[0] = U'c';
	assert(utf_string_compare(&a, &b) == -1);

	utf_string_free(&a);
	utf_string_free(&b);
}

static void test_copy(void){

	struct utf_string string;

	assert(utf_string_copy_utf32(&string, U"¿Cómo estás?") == 0);
	assert(string.data_len == 12);
	assert(memcmp(string.data, U"¿Cómo estás?", string.data_len) == 0);

	utf_string_free(&string);
}

static void test_insert(void){

	struct utf_string string;

	utf_string_init(&string);

	utf_string_free(&string);
}

