#ifndef LIBSTRUCT_INTERNAL_H_INCLUDED_36EF7D89_5C11_4BC9_9B6B_C4F281F032BE
#define LIBSTRUCT_INTERNAL_H_INCLUDED_36EF7D89_5C11_4BC9_9B6B_C4F281F032BE

#pragma once

#ifdef __GNUC__
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif

#if defined(__GNUC__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#define INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE inline
#endif

#endif
