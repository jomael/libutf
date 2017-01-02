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

