/*
 *    This file is part of libutf.
 *
 *    libutf is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    libutf is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with libutf.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBUTF_ERROR_H
#define LIBUTF_ERROR_H

/** Error type for libutf function calls.
 * @ingroup libutf
 */

typedef enum utf_error {
	/** No error occured. */
	UTF_ERROR_NONE = 0,
	/** Invalid UTF-8, UTF-16 or UTF-32 sequence. */
	UTF_ERROR_INVALID_SEQUENCE,
	/** The size of a input or output buffer was not large enough to fit a UTF-8, UTF-16 or UTF-32 sequence. */
	UTF_ERROR_OVERFLOW,
	/** Failed to allocate memory */
	UTF_ERROR_MALLOC,
	/** Reached the end of a file or string */
	UTF_ERROR_EOF,
	/** Attempt to read/write an out of boundary location */
	UTF_ERROR_BOUNDARY,
	/** An unknown error occured. */
	UTF_ERROR_UNKNOWN
} utf_error_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Returns a human-readable string containing a description of the error code.
 * @param error An error code returned from a libutf function call.
 * @returns A human-readable string containing a description of the error code.
 * @ingroup libutf
 */

const char * utf_strerror(utf_error_t error);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_ERROR_H */

