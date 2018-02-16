#ifndef SPARSE_INLINE_H
#define SPARSE_INLINE_H

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

#endif
