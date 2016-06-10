#include "error.h"

const char * utfx_strerror(utfx_error_t error){
	switch (error){
		case UTFX_ERROR_NONE:
			return "No error";
		case UTFX_ERROR_INVALID_SEQUENCE:
			return "Invalid sequence";
		case UTFX_ERROR_OVERFLOW:
			return "Buffer overflow";
		case UTFX_ERROR_NOT_ACCEPTING_READ:
			return "Decoder or encoder is not accepting read calls";
		case UTFX_ERROR_NOT_ACCEPTING_WRITE:
			return "Decoder or encoder is not accepting write calls";
		default:
			break;
	}
	/* should be unreachable */
	return "Unknown error";
}

