/** @file */

#ifndef LIBUTF_UTF32_H
#define LIBUTF_UTF32_H

/* for char32_t */
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Converts a UTF-32BE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

char32_t utf32be(const void * src);

/** Converts a UTF-32LE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

char32_t utf32le(const void * src);

/** Compares two UTF-32 strings.
 * @param a A null-terminated UTF-32 string.
 * @param b A null-terminated UTF-32 string.
 * @returns Zero if the strings are equal.
 *  Returns greater than zero if @p a is greater than @p b.
 *  Returns less than zero if @p a is less than @p b.
 * @ingroup libutf-procedural
 */

int utf32_cmp(const char32_t * a, const char32_t * b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBUTF_UTF32_H */

