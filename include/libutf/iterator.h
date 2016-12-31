#ifndef LIBUTF_ITERATOR_H
#define LIBUTF_ITERATOR_H

#include <libutf/string.h>

typedef struct utf_iterator {
	const utf_string_t * string;
	unsigned long int pos;
	unsigned long int unit_pos;
} utf_iterator_t;

void utf_iterator_init(utf_iterator_t * iterator, const utf_string_t * string);

unsigned long int utf_iterator_available(const utf_iterator_t * iterator);

unsigned long int utf_iterator_count(const utf_iterator_t * iterator);

int utf_iterator_end(const utf_iterator_t * iterator);

utf32_t utf_iterator_get(const utf_iterator_t * iterator);

utf_error_t utf_iterator_next(utf_iterator_t * iterator);

void utf_iterator_reset(utf_iterator_t * iterator);

#endif /* LIBUTF_ITERATOR_H */

