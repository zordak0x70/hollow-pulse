#ifndef SV_HELPER_H
#define SV_HELPER_H


#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/**
 * @struct sv
 * @brief Non-owning string view.
 */
typedef struct {
    char *data;
    size_t size;
} sv;

/**
 * @brief Creates a string view from a null-terminated C string.
 *
 * The length is computed using strlen().
 *
 * @param str A valid null-terminated C string.
 * @return A string view pointing to the given string.
 */
static inline sv sv_from_cstr(char *str) {
    return (sv){
        .data = str,
        .size = strlen(str),
    };
}

/**
 * @brief Creates a string view from raw character data and a size.
 *
 * This function does not require the input data to be null-terminated.
 *
 * @param data Pointer to the beginning of the character sequence.
 * @param size Number of characters in the view.
 * @return A string view pointing to the specified memory range.
 */
static inline sv sv_from_parts(char *data, size_t size) {
    return (sv){
        .data = data,
        .size = size,
    };
}

/**
 * @brief Creates a string view from a string literal at compile time.
 *
 * This macro should only be used with string literals or fixed-size
 * character arrays known at compile time.
 */
#define SV_STATIC(str) (sv){ .data = (str), .size = sizeof(str) - 1 }

/**
 * @brief Returns a substring view from the given string view.
 *
 * If @p start is out of range, an empty view is returned.
 * If @p len exceeds the available range, it is clamped.
 *
 * @param s The source string view.
 * @param start Starting index of the substring.
 * @param len Requested length of the substring.
 * @return A string view representing the requested substring,
 *         or an empty view if @p start is out of bounds.
 */
static inline sv sv_substring(sv *s, size_t start, size_t len) {
    if (start >= s->size) return (sv){NULL, 0};
    if (start + len > s->size) len = s->size - start;
    return (sv){ .data = s->data + start, .size = len };
}

/**
 * @brief Compares two string views for exact equality.
 *
 * Two views are equal if they have the same size and identical contents.
 *
 * @param a The first string view.
 * @param b The second string view.
 * @return Non-zero if the two views are equal, 0 otherwise.
 */
static inline int sv_eq(sv *a, sv *b) {
    return a->size == b->size && memcmp(a->data, b->data, a->size) == 0;
}

/**
 * @brief Checks whether a string view starts with a given prefix.
 *
 * @param s The string view to test.
 * @param prefix The prefix to compare against.
 * @return true if @p s starts with @p prefix, false otherwise.
 */
static inline bool sv_starts_with(sv *s, sv *prefix) {
    return s->size >= prefix->size &&
           memcmp(s->data, prefix->data, prefix->size) == 0;
}

/**
 * @brief Checks whether a string view ends with a given suffix.
 *
 * @param s The string view to test.
 * @param suffix The suffix to compare against.
 * @return true if @p s ends with @p suffix, false otherwise.
 */
static inline bool sv_ends_with(sv *s, sv *suffix) {
    return s->size >= suffix->size &&
           memcmp(s->data + (s->size - suffix->size), suffix->data, suffix->size) == 0;
}

/**
 * @brief Format specifier for printing a string view with printf-style functions.
 *
 * Use together with @ref SV_ARG.
 */
#define SV_FMT "%.*s"

/**
 * @brief Expands a string view into printf-style arguments.
 *
 * This macro provides the length and data pointer expected by @ref SV_FMT.
 */
#define SV_ARG(s) ((int)(s)->size), ((s)->data)


#endif // SV_HELPER_H
