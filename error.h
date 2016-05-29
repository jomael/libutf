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
	/** The size of a input or output buffer was not large enough to fit a UTF-8, UTF-16 or UTF-32 sequence. */
	UTFX_ERROR_OVERFLOW,
	/** An unknown error occured. */
	UTFX_ERROR_UNKNOWN
} utfx_error_t;

/** Returns a human-readable string containing a description of the error code.
 * @param error An error code returned from a utfx function call.
 * @returns A human-readable string containing a description of the error code.
 * @ingroup utfx_error
 */

const char * utfx_strerror(utfx_error_t error);

#endif /* UTFX_ERROR_H */

