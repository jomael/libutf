#ifndef LIBUTF_CONVERTER_H
#define LIBUTF_CONVERTER_H

#include "decoder.h"
#include "encoder.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** A UTF-8, UTF-16 or UTF-32 converter
 * @ingroup libutf
 */

typedef struct utf_converter {
	/** The decoder of the converter structure */
	utf_decoder_t decoder;
	/** The encoder of the converter structure */
	utf_encoder_t encoder;
} utf_converter_t;

/** Initializes the members of a converter structure.
 * @param converter An uninitialized converter structure.
 * @ingroup libutf
 */

void utf_converter_init(utf_converter_t * converter);

/** Frees resources allocated by a converter structure.
 * @param converter An initialized converter structure.
 * @ingroup libutf
 */

void utf_converter_free(utf_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

utf_decoder_t * utf_converter_get_decoder(utf_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

const utf_decoder_t * utf_converter_get_decoder_const(const utf_converter_t * converter);

/** Returns the codec of the decoder
 * @param converter An initialized converter
 * @ingroup libutf
 */

utf_codec_t utf_converter_get_decoder_codec(const utf_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

utf_encoder_t * utf_converter_get_encoder(utf_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

const utf_encoder_t * utf_converter_get_encoder_const(const utf_converter_t * converter);

/** Returns the codec of the encoder.
 * @param converter An initialized converter structure.
 * @ingroup libutf
 */

utf_codec_t utf_converter_get_encoder_codec(const utf_converter_t * converter);

/** Sets the codec of the decoder.
 * @param converter An initialized converter.
 * @param codec The new decoder codec for the converter.
 * @ingroup libutf
 */

void utf_converter_set_decoder_codec(utf_converter_t * converter, utf_codec_t codec);

/** Sets the codec of the encoder.
 * @param converter An initialized converter.
 * @param codec The new encoder codec for the converter.
 * @ingroup libutf
 */

void utf_converter_set_encoder_codec(utf_converter_t * converter, utf_codec_t codec);

/** Reads encoded data from the converter.
 * @param converter An initialized converter structure.
 * @param dst The address to write the encoded data to
 * @param dst_size The number of bytes that the destination address can store.
 * @returns The number of bytes read from the converter.
 * @ingroup libutf
 */

unsigned int utf_converter_read(utf_converter_t * converter, void * dst, unsigned int dst_size);

/** Writes data to the converter for decoding.
 * @param converter An initialized converter structure.
 * @param src The address to containing the encoded data
 * @param src_size The number of bytes that the source address contains
 * @returns The number of bytes to write to the converter
 * @ingroup libutf
 */

unsigned int utf_converter_write(utf_converter_t * converter, const void * src, unsigned int src_size);

/** Determines if the converter needs more input data or not.
 * @param converter An initialized converter structure.
 * @returns @ref LIBUTF_TRUE if the converter needs more data,
 * @ref LIBUTF_FALSE if it does not.
 * @ingroup libutf
 * */

utf_bool_t utf_converter_needs_data(const utf_converter_t * converter);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_CONVERTER_H */

