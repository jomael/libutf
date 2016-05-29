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
	UTFX_ERROR_NONE = 0,
	UTFX_ERROR_INVALID_SEQUENCE,
	UTFX_ERROR_INVALID_MODE,
	UTFX_ERROR_MODE_NOT_SET,
	UTFX_ERROR_UNKNOWN
} utfx_error_t;

/** Returns a human-readable string containing a description of the error code.
 * @param error An error code returned from a utfx function call.
 * @returns A human-readable string containing a description of the error code.
 * @ingroup utfx_error
 */
const char * utfx_strerror(utfx_error_t error);

#endif /* UTFX_ERROR_H */

