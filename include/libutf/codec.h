#ifndef LIBUTF_CODEC_H
#define LIBUTF_CODEC_H

#include "config.h"
#include "string.h"
#include "types.h"

#ifndef UTF_CODEC_UTF16_NE
#ifndef UTF_BIG_ENDIAN
#define UTF_CODEC_UTF16_NE UTF_CODEC_UTF16_LE
#define UTF_CODEC_UTF32_NE UTF_CODEC_UTF32_LE
#else /* UTF_BIG_ENDIAN */
#define UTF_CODEC_UTF16_NE UTF_CODEC_UTF16_BE
#define UTF_CODEC_UTF32_NE UTF_CODEC_UTF32_BE
#endif /* UTF_BIG_ENDIAN */
#endif /* UTF_CODEC_UTF16_NE */

typedef enum utf_codec {
	/** UTF-8 codec */
	UTF_CODEC_UTF8,
	/** UTF-16 codec, using big endian format */
	UTF_CODEC_UTF16_BE,
	/** UTF-16 codec, using little endian format */
	UTF_CODEC_UTF16_LE,
	/** UTF-32 codec, using big endian format */
	UTF_CODEC_UTF32_BE,
	/** UTF-32 codec, using little endian format */
	UTF_CODEC_UTF32_LE,
	/** UTF-16 codec, using the native endian format */
	UTF_CODEC_UTF16 = UTF_CODEC_UTF16_NE,
	/** UTF-32 codec, using native endian format */
	UTF_CODEC_UTF32 = UTF_CODEC_UTF32_NE,
	/** The first codec in the codecs enumeration (useful for iteration) */
	UTF_CODEC_FIRST = UTF_CODEC_UTF8,
	/** The last codec in the codecs enumeration (useful for iteration) */
	UTF_CODEC_LAST = UTF_CODEC_UTF32_LE
} utf_codec_t;

/** Returns a string representation of the codec name.
 * @param codec The codec to get the string representation of.
 * @returns A UTF-8 string representing the codec name.
 */

const utf_string_t * utf_codec_to_string(utf_codec_t codec);

/** Calculate the minimum bytes size of a code point, for a given codec.
 * @param codec The codec to calculate the minimum character size for.
 * @returns The minimum number of bytes that occupy one character in the codec.
 */

utf_byte_count_t utf_codec_min_bytes(utf_codec_t codec);

/** Calculate the maximum bytes size of a code point, for a given codec.
 * @param codec The codec to calculate the maximum character size for.
 * @returns The maximum number of bytes that occupy one character in the codec.
 */

utf_byte_count_t utf_codec_max_bytes(utf_codec_t codec);

/** Calculate the maximum unit count of a code point, for a given codec.
 * @param codec The codec to calculate the maximum unit count for.
 * @returns The maximum number of units that occupy one code point in the codec.
 */

utf_unit_count_t utf_codec_max_units(utf_codec_t codec);

#endif /* LIBUTF_CODEC_H */

