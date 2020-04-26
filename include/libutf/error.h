#ifndef LIBUTF_ERROR_H
#define LIBUTF_ERROR_H

/** Error type for libutf function calls.
 * @ingroup libutf
 */

typedef enum utf_error {
	/** No error occured. */
	UTF_ERROR_NONE = 0,
	/** Permission denied */
	UTF_ERROR_ACCESS,
	/** Path refers to directory */
	UTF_ERROR_IS_DIRECTORY,
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
	/** No file or directory exists */
	UTF_ERROR_MISSING_ENTRY,
	/** An unknown error occured. */
	UTF_ERROR_UNKNOWN
} utf_error_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Returns an error code translated from errno.
 * @param errno_ An error number set by a library call.
 * @returns A libutf corresponding error code.
 *  If no such translation is available,
 *  then @ref UTF_ERROR_UNKNOWN is returned.
 * @ingroup libutf
 */

utf_error_t utf_errno(int errno_);

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

