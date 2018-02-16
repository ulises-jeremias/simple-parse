/**
 * @mainpage
 *
 * <a target="_blank" href="https://github.com/ulises-jeremias/simple-parse.git">See SPARSE on GitHub</a>.
 *
 * @section Usage
 * See the documentation for the sparse_flag() function.
 *
 * @section Example
 * To handle the following program arguments:
 * @code
 * ./myprog --flag1 --flag3= --flag4="Hello world"
 * @endcode
 *
 * You could write this:
 * @code
 *
 * [...]
 *
 * int main(int argc, char* argv[])
 * {
 *
 *     char* f1 = sparse_flag("flag1", "FALSE",      argc, argv); // f1 = "TRUE"
 *     char *f2 = sparse_flag("flag2", "FALSE",      argc, argv); // f2 = "FALSE"
 *     char *f3 = sparse_flag("flag3", "defaultval", argc, argv); // f3 = ""
 *     char *f4 = sparse_flag("flag4", "Bye world",  argc, argv); // f4 = "Hello world"
 *     char *f5 = sparse_flag("flag5", "Bye world",  argc, argv); // f5 = "Bye world"
 *     char *f5 = sparse_flag("flag5", NULL,  argc, argv); // f5 = NULL
 *
 * }
 * @endcode
 */

/**
 * @file sparse.h
 */
#ifndef SPARSE_H
#define SPARSE_H

#include <string.h>
#include <stdlib.h>

/* Check C standard */
#ifdef __STDC__
        #define PREDEF_STANDARD_C89
        #ifdef __STDC_VERSION__
                #if __STDC_VERSION__ >= 199901L
                        #define PREDEF_STANDARD_C99
                        #if __STDC_VERSION__ >= 201112L
                                #define PREDEF_STANDARD_C11
                        #endif
                #endif
        #endif
#endif

#define __SPARSE_BEGIN_DECLS
#define __SPARSE_END_DECLS

#ifdef __cplusplus
        #undef __SPARSE_BEGIN_DECLS
        #undef __SPARSE_END_DECLS

        #define __SPARSE_BEGIN_DECLS extern "C" {
        #define __SPARSE_END_DECLS }

        #if __cplusplus >= 199901L
                #define PREDEF_STANDARD_CPP99
                #if __cplusplus >= 201112L
                        #define PREDEF_STANDARD_CPP11
                #endif
        #endif
#endif

#ifdef _MSC_VER
        #define __SPARSE_INLINE __forceinline
#else
        #define __SPARSE_INLINE inline __attribute((always_inline))
#endif

/* Use `extern inline` for C99 or later */
#ifdef PREDEF_STANDARD_C99
        #define __SPARSE_EXTERN_INLINE extern __SPARSE_INLINE
#else
        #define __SPARSE_EXTERN_INLINE static
#endif

#define FLAG_MAX_SIZE 80
#define FLAG_MAX_NUMBER 20

__SPARSE_BEGIN_DECLS

extern char** SPARSE_allocated_args;
extern int SPARSE_initialized;
extern int SPARSE_current_arg;

void sparse_cleanup();
void sparse_init();
char *sparse_flag(char *name, char *defaultValue, int argc, char **argv);

__SPARSE_END_DECLS

#endif /* SPARSE_H */
