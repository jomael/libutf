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

/** Compares an entry in the argument structure to either of a short or long
 * UTF-32 option string.
 * @param args An initialized argument structure.
 * @param index The index of the argument within the argument structure.
 * @param s_opt A single short-option character.
 *  The '-' is checked implicitly.
 * @param l_opt A long option string.
 *  The '--' is checked implicity.
 *  This string does not need to start with a '--'.
 * @returns Zero if the strings are equal.
 *  Non-zero if they are not, or if the argument does not contain a '-' or '--'.
 * @ingroup libutf
 */

int utf_args_cmp_opt_utf32(const struct utf_args * args, size_t index, char32_t s_opt, const char32_t * l_opt);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_ARGS_H */

