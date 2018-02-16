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
        #define __SPARSE_EXTERN_INLINE
#endif

#define FLAG_MAX_SIZE 80
#define FLAG_MAX_NUMBER 20

__SPARSE_BEGIN_DECLS

extern char** sparse_allocated_args;
extern int sparse_initialized;
extern int sparse_current_arg;

void sparse_cleanup();
void sparse_init();
char *sparse_flag(char *name, char *defaultValue, int argc, char **argv);

__SPARSE_END_DECLS

#endif /* SPARSE_H */
