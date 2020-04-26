#include <libutf/utf32.h>

const char32_t utf32_max = 0x10ffff;

const char32_t utf32_min = 0x00;

char32_t utf32be(const void * src){
	char32_t out32 = 0;
	const unsigned char * src8 = (const unsigned char *)(src);
	out32 |= src8[0] << 0x18;
	out32 |= src8[1] << 0x10;
	out32 |= src8[2] << 0x08;
	out32 |= src8[3] << 0x00;
	return out32;
}

char32_t utf32le(const void * src){
	char32_t out32 = 0;
	const unsigned char * src8 = (const unsigned char *)(src);
	out32 |= src8[0] << 0x00;
	out32 |= src8[1] << 0x08;
	out32 |= src8[2] << 0x10;
	out32 |= src8[3] << 0x18;
	return out32;
}

int utf32_cmp(const char32_t * a, const char32_t * b){
	size_t i;
	for (i = 0; (a[i] != 0) && (b[i] != 0); i++){
		if (a[i] > b[i]){
			return 1;
		} else if (a[i] < b[i]){
			return -1;
		}
	}
	return 0;
}

