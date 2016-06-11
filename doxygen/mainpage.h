/** @file */

/** @mainpage Utfx Documentation
 *
 * Utfx is a C89 library for encoding and decoding UTF8, UTF16 and UTF32 text.
 *
 * If you're reading this, you have a successfully built binary of the library and you are reading this documentation for the first time.
 *
 * If you do not have a successfully built binary of the library, instructions on how to build it are included with the source code.
 * You will not find instructions on how to build the project in this documentation.
 *
 * You will also not find documentation on the inner workings of UTF8 and UTF16 codecs.
 * If you'd like to know more about how UTF8 and UTF16 codecs work, read the [RFC2279] and [RFC2781] articles.
 * A copy of both [RFC2279] and [RFC2781] are included with the source code.
 * Although it does help to understand how the codecs work, it should be enough to know that they are variable length characters.
 *
 * @section using-the-library Using the Library
 *
 * @subsection getting-started Getting Started
 *
 * At the very base of the library are the low level encoding and decoding functions for each codec.
 * Some use cases for them may be in the following:
 *  - coding environments where only a single codec is used
 *  - writing a custom encoder or decoder
 *  - in a learning environment
 *
 * View the @ref sigma.c example for a demonstration of the low level functions.
 *
 * View the @ref utf8 and @ref utf16 modules for a complete reference of these functions.
 *
 * The lower level functions, however, do not perform abstraction of the codec being used.
 *
 * To encode and decode all codecs in a layer of abstraction, the encoder and decoder structures were made.
 *
 * View the @ref iconv.c example for a demonstration of the encoder and decoder structures.
 *
 * View the @ref encoding and @ref utfx_decoder modules for a complete reference of these structures.
 *
 * [RFC2279]: https://www.ietf.org/rfc/rfc2279.txt
 * [RFC2781]: https://www.ietf.org/rfc/rfc2781.txt
 *
 * @example iconv.c
 * @example sigma.c
 */

