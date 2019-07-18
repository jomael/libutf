#include <libutf/error.h>
#include <errno.h>

utf_error_t utf_errno(int errno_){
	switch (errno_){
		case 0:
			return UTF_ERROR_NONE;
		case EACCES:
			return UTF_ERROR_ACCESS;
		case ENOENT:
			return UTF_ERROR_MISSING_ENTRY;
		case EISDIR:
			return UTF_ERROR_IS_DIRECTORY;
		default:
			break;
	}
	return UTF_ERROR_UNKNOWN;
}

const char * utf_strerror(utf_error_t error){
	switch (error){
		case UTF_ERROR_NONE:
			return "No error";
		case UTF_ERROR_ACCESS:
			return "Permission denied";
		case UTF_ERROR_MISSING_ENTRY:
			return "No such file or directory";
		case UTF_ERROR_IS_DIRECTORY:
			return "Path refers to a directory";
		case UTF_ERROR_INVALID_SEQUENCE:
			return "Invalid sequence";
		case UTF_ERROR_OVERFLOW:
			return "Buffer overflow";
		case UTF_ERROR_EOF:
			return "End of file reached";
		case UTF_ERROR_BOUNDARY:
			return "Out of boundary read or write";
		case UTF_ERROR_MALLOC:
			return "Memory allocation failure";
		default:
			break;
	}
	/* should be unreachable */
	return "Unknown error";
}

