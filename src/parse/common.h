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

#define ESC_BLACK 		"\x1b[30m"
#define ESC_RED	 		"\x1b[31m"
#define ESC_GREEN 		"\x1b[32m"
#define ESC_YELLOW 		"\x1b[33m"
#define ESC_BLUE 		"\x1b[34m"
#define ESC_MAGENTA		"\x1b[35m"
#define ESC_CYAN 		"\x1b[36m"
#define ESC_WHITE 		"\x1b[37m"

#define ESC_BOLD		"\x1b[1m"
#define ESC_UNDERLINE	"\x1b[4m"

#define ESC_RESET		"\x1b[0m"

#define COLOR_CYAN(...)				\
	ESC_CYAN __VA_ARGS__ ESC_RESET

#define COLOR_RED(...)				\
	ESC_RED __VA_ARGS__ ESC_RESET

#define COLOR_GREEN(...)				\
	ESC_GREEN __VA_ARGS__ ESC_RESET

#define COLOR_YELLOW(...)				\
	ESC_YELLOW __VA_ARGS__ ESC_RESET

#define COLOR_BLUE(...)				\
	ESC_BLUE __VA_ARGS__ ESC_RESET

#define COLOR_MAGENTA(...)				\
	ESC_MAGENTA __VA_ARGS__ ESC_RESET

#endif /* common.h */
