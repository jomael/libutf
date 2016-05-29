#include "error.h"

const char * utfx_strerror(utfx_error_t error){
	switch (error){

		case UTFX_ERROR_NONE:
		return "No error";

		case UTFX_ERROR_INVALID_SEQUENCE:
		return "Invalid sequence";

		default:
		break;
	}
	/* should be unreachable */
	return "Unknown error";
}
