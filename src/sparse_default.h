#ifndef SPARSE_DEF_H
#define SPARSE_DEF_H

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

#endif
