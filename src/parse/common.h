#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#if defined(__clang__)
	#define _always_inline_ static inline __attribute__((always_inline))
#elif defined(__GNUC__) || defined(__GNUG__)
	#define _always_inline_ static inline __attribute__((always_inline))
#elif defined(_MSC_VER)
	#define _always_inline_ __forceinline
#endif

#define ZEROESx32                       \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define ZEROESx64                       \
    ZEROESx32,                          \
    ZEROESx32

#define ZEROESx128                      \
    ZEROESx64,                          \
    ZEROESx64

#define ZEROESx256                      \
    ZEROESx128,                         \
    ZEROESx128

#define ZEROESx25 \
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
	0,0,0,0,0,0,0,0,0,0

#define ZEROESx100 \
	ZEROESx25, ZEROESx25, ZEROESx25, \
	ZEROESx25


#define FLAG32(name, shift) \
	static const uint32_t name = 1 << shift

#define FLAG16(name, shift) \
	static const uint16_t name = 1 << shift

#define FLAG8(name, shift) \
	static const uint8_t name = 1 << shift

#endif /* common.h */
