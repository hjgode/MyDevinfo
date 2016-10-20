
#ifndef EKTYPES_H
#define EKTYPES_H

#define EK_MIN(X,Y) ((X)<(Y)?(X):(Y))
#define EK_MIN3(X,Y,Z) ((X)<(Y)?EK_MIN(X,Z):EK_MIN(Y,Z))
#define EK_MIN4(X,Y,Z,A) ((X)<(Y)?EK_MIN3(X,Z,A):EK_MIN3(Y,Z,A))

#define EK_MAX(X,Y) ((X)>(Y)?(X):(Y))
#define EK_MAX3(X,Y,Z) ((X)>(Y)?EK_MAX(X,Z):EK_MAX(Y,Z))
#define EK_MAX4(X,Y,Z,A) ((X)>(Y)?EK_MAX3(X,Z,A):EK_MAX3(Y,Z,A))

#define EK_ABS(X) (X) < 0 ? (-X) : (X)

// Not all platforms have stdint.h
// For those that don't, set the defines to common values for 32-bit
// processors.
#ifndef EK_HAVE_STDINT_H
#  if (defined (WIN32) || defined(_WIN32)) && !defined(__MINGW32__)
#    define EK_HAVE_STDINT_H 0
#  else
#    define EK_HAVE_STDINT_H 1
#  endif
#endif

#if (EK_HAVE_STDINT_H != 0)
#  if defined(__cplusplus) && !defined(__STDC_LIMIT_MACROS)
#    define __STDC_LIMIT_MACROS
#  endif
#  include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef double double_t;

#  define UINT64_MAX 0xffffffffffffffffULL

#endif

#endif
