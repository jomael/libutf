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

#include <libutf/error.h>

const char * utf_strerror(utf_error_t error){
	switch (error){
		case UTF_ERROR_NONE:
			return "No error";
		case UTF_ERROR_INVALID_SEQUENCE:
			return "Invalid sequence";
		case UTF_ERROR_OVERFLOW:
			return "Buffer overflow";
		case UTF_ERROR_EOF:
			return "End of file reached";
		case UTF_ERROR_MALLOC:
			return "Memory allocation failure";
		default:
			break;
	}
	/* should be unreachable */
	return "Unknown error";
}

