/*
 *    This file is part of Utfx.
 *
 *    Utfx is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utfx is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utfx.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTFX_ERROR_H
#define UTFX_ERROR_H

/**
 * @defgroup utfx_error utfx_error
 * @brief Error type for utfx function calls.
 */

/** Error type for utfx function calls.
 * @ingroup utfx_error
 */

typedef enum utfx_error {
	/** No error occured. */
	UTFX_ERROR_NONE = 0,
	/** Invalid UTF-8, UTF-16 or UTF-32 sequence. */
	UTFX_ERROR_INVALID_SEQUENCE,
	/** Encoder or decoder mode is invalid or has not been implemented. */
	UTFX_ERROR_INVALID_MODE,
	/** Encoder or decoder mode is not set. */
	UTFX_ERROR_MODE_NOT_SET,
	/** Encoder or decoder is not accepting read calls */
	UTFX_ERROR_NOT_ACCEPTING_READ,
	/** Encoder or decoder is not accepting write calls */
	UTFX_ERROR_NOT_ACCEPTING_WRITE,
	/** The size of a input or output buffer was not large enough to fit a UTF-8, UTF-16 or UTF-32 sequence. */
	UTFX_ERROR_OVERFLOW,
	/** An unknown error occured. */
	UTFX_ERROR_UNKNOWN
} utfx_error_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Returns a human-readable string containing a description of the error code.
 * @param error An error code returned from a utfx function call.
 * @returns A human-readable string containing a description of the error code.
 * @ingroup utfx_error
 */

const char * utfx_strerror(utfx_error_t error);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* UTFX_ERROR_H */

