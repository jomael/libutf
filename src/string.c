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

#include <libutf/string.h>

#include <stdlib.h>

void utf_string_init(utf_string_t * string){
	string->bits = 8;
	string->count = 0;
	string->count_res = 0;
	string->u.u8 = NULL;
}

void utf_string_free(utf_string_t * string){
	if (string != NULL){
		free(string->u.u8);
	}
}

