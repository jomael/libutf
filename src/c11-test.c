#include <libutf/utf16.h>

#include <assert.h>

int main(void){

	utf16_t * in = u"𐐷	";
	utf32_t ch;

	assert(utf16_decode(in, &ch) == 2);
	/* 𐐷	 is 0x10437 */
	assert(ch == 0x10437);

	return 0;
}

