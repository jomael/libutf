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

#ifndef LIBUTF_ARGS_H
#define LIBUTF_ARGS_H

/* for size_t */
#include <stdlib.h>

/* for char32_t */
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct utf_args {
    char32_t ** argv;
    size_t argc;
};

/** Initializes an argument structure.
 * @param args An uninitialized argument structure.
 * @param argc The number of arguments in @p argv.
 * @param argv A list of null terminated arguments.
 * @returns Zero on success.
 *  If there was an error allocating memory, ENOMEM is returned.
 * @ingroup libutf
 */

int utf_args_init(struct utf_args * args, int argc, const char ** argv);

/** Releases memory allocated by the argument structure.
 * @param args An initialized argument structure.
 * @ingroup libutf
 */

void utf_args_free(struct utf_args * args);

/** Returns the number of arguments in the argument structure.
 * @param args An initialized argument structure.
 * @returns The number of arguments in the argument structure.
 *  This does not include the null-terminating argument.
 * @ingroup libutf
 */

size_t utf_args_count(const struct utf_args * args);

/** Compares a entry in the argument structure to a UTF-32 literal.
 * @param args An initialized argument structure.
 * @param index The index of the argument in the argument structure.
 *  This value is not boundary checked.
 *  Use @ref utf_args_count to check the index boundary.
 * @param arg The string to compare the entry in the argument structure with.
 * @returns Zero if the strings are equal.
 *  Non-zero if the strings are not equal.
 * @ingroup libutf
 */

int utf_args_cmp_utf32(const struct utf_args * args, size_t index, const char32_t * arg);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_ARGS_H */

