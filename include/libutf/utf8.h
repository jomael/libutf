/** @file */

#ifndef LIBUTF_UTF8_H
#define LIBUTF_UTF8_H

/* for size_t */
#include <stdlib.h>

/* for char32_t */
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Decode a UTF-8 sequence.
 * @param in A buffer containing a UTF-8 sequence.
 *  The size of the buffer is calculated by the first byte in the sequence.
 * @param out A pointer to at least a 32 bit data type to store the result.
 * @returns The amount of bytes in the sequence that were decoded.
 * If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf8_decode(const char * in, char32_t * out);

/** Calculate the expected length of a UTF-8 sequence based on the first byte in the sequence.
 * @param in The first byte in the UTF-8 sequence.
 * @returns The length of the UTF-8 sequence, including the first byte.
 *  If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf8_decode_length(char in);

/** Decode a UTF-8 string.
 * @param in A UTF-8, null terminated string.
 * @param out A pointer to a utf-32 string. It must be large
 * enough to fit the size of the decoding.
 * @returns The number of UTF-8 points decoded.
 *  If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf8_decode_string(const char * in, char32_t * out);

/** Encode a UTF-8 sequence.
 * @param out A buffer where the result will be stored.
 *  This buffer must be large enough to store the sequence.
 *  The size may be calculated with utf_8_codec_Calculate_Length_Encoded().
 * @param in The character to encode. Must be > 0 and < 0x110000.
 * @returns The amount of bytes written to the buffer.
 *  If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf8_encode(char32_t in, char * out);

/** Calculate what the sequence length would be of a 32 bit character.
 * @param in A 32 bit character.
 * @returns The length of what the encoded sequence would be.
 *  If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf8_encode_length(char32_t in);

/** Calculate the length of a UTF-8 string.
 * The function will stop at the end of the string or at the first error.
 * @param in The UTF-8 string.
 * @param in_size The number of code units occupied by the UTF-8 string.
 * @returns The length of the UTF-8 string, in code points.
 * @ingroup libutf-procedural
 */

size_t utf8_strlen(const char * in, unsigned int in_size);

/** Converts a null-terminated UTF-8 string to a null-terminated UTF-32 string.
 * @param in A null-terminated UTF-8 string.
 * @returns A null-terminated UTF-32 string.
 *  If a memory allocation fails, NULL is returned.
 */

char32_t * utf8_to_utf32(const char * in);

/** Converts a UTF-8 string to a UTF-32 string.
 * Stops at the end of the UTF-8 string or when an invalid sequence is found.
 * @param in A UTF-8 string.
 * @param in_len The number of code units in the UTF-8 string.
 * @param out_len The number of code units in the output.
 *  This is set by the function. May be NULL.
 * @returns A null-terminated UTF-32 string.
 *  If a memory allocation fails, NULL is returned.
 */

char32_t * utf8_to_utf32_s(const char * in, size_t in_len, size_t * out_len);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_UTF8_H */

