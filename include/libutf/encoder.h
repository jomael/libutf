#ifndef LIBUTF_ENCODER_H
#define LIBUTF_ENCODER_H

#include "utf32.h"
#include "codec.h"
#include "error.h"

/** A UTF-8, UTF-16 or UTF-32 encoder.
 * It may be used so that, once the codec is set, the encoding of the input text may be abstracted.
 * @ingroup libutf
 */

typedef struct {
	/** The encoding codec of the encoder */
	utf_codec_t codec;
	/** An array of bytes to store encoded characters */
	unsigned char * byte_array;
	/** The number of encoded bytes in the byte array */
	unsigned long int byte_count;
	/** The number of bytes reserved in the byte array */
	unsigned long int byte_count_res;
} utf_encoder_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Initializes the members of an encoder structure.
 * Sets the encoding codec to UTF-8.
 * @param encoder An uninitialized encoder structure.
 * @ingroup libutf
 */

void utf_encoder_init(utf_encoder_t * encoder);

/** Frees resources allocated by the encoder structure.
 * @param encoder An initialized encoder structure.
 *  May be a null pointer.
 * @ingroup libutf
 */

void utf_encoder_free(utf_encoder_t * encoder);

/** Returns the codec of the encoder.
 * @param encoder An initialized encoder structure.
 * @returns The current codec of the encoder.
 * @ingroup libutf
 */

utf_codec_t utf_encoder_get_codec(const utf_encoder_t * encoder);

/** Reads the internal output character of the last encoded input character.
 * The encoding of the output character is determined by what codec the encoder is in.
 * The codec of the encoder can be set with the function @ref utf_encoder_set_codec.
 * @param encoder An initialized encoder structure.
 * @param dst The address of where the output character will be written.
 * @param dst_size The number of bytes to read from the encoder.
 * @return The number of bytes read from the encoder.
 */

unsigned long int utf_encoder_read(utf_encoder_t * encoder, void * dst, unsigned long int dst_size);

/** Reserves an amount of memory for the encoder to store encoded characters.
 * This function can be used to optimize a series of write operations, that will
 * likely use a lot of memory.
 * @param encoder An initialized encoder structure.
 * @param size The number of bytes to allocate for the encoder's buffer.
 * @return On success, @ref UTF_ERROR_NONE.
 * @ingroup libutf
 */

utf_error_t utf_encoder_reserve(utf_encoder_t * encoder, unsigned long int size);

/** Sets the encoding codec of the encoder.
 * @param encoder An initialized encoder structure.
 * @param codec The new codec of the encoder.
 * @ingroup libutf
 */

void utf_encoder_set_codec(utf_encoder_t * encoder, utf_codec_t codec);

/** Encodes an input character.
 * The output of the encoding is determined by what codec the encoder is in.
 * @param encoder An initialized encoder structure
 * @param input_char A valid UTF-32 character.
 * @returns On success, UTF_ERROR_NONE is returned.
 * @ingroup libutf
 */

utf_error_t utf_encoder_write(utf_encoder_t * encoder, utf32_t input_char);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_ENCODER_H */

