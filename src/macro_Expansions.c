# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 1
# 24 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 1



# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 1
# 64 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 1
# 68 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 1
# 649 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_symbol_aliasing.h" 1
# 650 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 2
# 715 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_posix_availability.h" 1
# 716 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h" 2
# 69 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/Availability.h" 1
# 135 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/Availability.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/AvailabilityVersions.h" 1
# 136 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/Availability.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/AvailabilityInternal.h" 1
# 137 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/Availability.h" 2
# 70 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types.h" 1
# 27 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 1
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_types.h" 1
# 37 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_types.h"
typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
# 70 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_types.h"
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;







typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_types.h" 2
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 2
# 55 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h"
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;



typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_types.h" 1
# 57 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_types.h"
struct __darwin_pthread_handler_rec {
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};

struct _opaque_pthread_attr_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_cond_t {
 long __sig;
 char __opaque[40];
};

struct _opaque_pthread_condattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_mutex_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_mutexattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_once_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_rwlock_t {
 long __sig;
 char __opaque[192];
};

struct _opaque_pthread_rwlockattr_t {
 long __sig;
 char __opaque[16];
};

struct _opaque_pthread_t {
 long __sig;
 struct __darwin_pthread_handler_rec *__cleanup_stack;
 char __opaque[8176];
};

typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;
# 81 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types.h" 2
# 28 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types.h" 2
# 40 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types.h"
typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;

typedef __uint32_t __darwin_wctype_t;
# 72 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2



# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_va_list.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_va_list.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 1
# 35 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 1
# 76 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int8_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int8_t.h"
typedef signed char int8_t;
# 77 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int16_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int16_t.h"
typedef short int16_t;
# 78 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int32_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int32_t.h"
typedef int int32_t;
# 79 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int64_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int64_t.h"
typedef long long int64_t;
# 80 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int8_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int8_t.h"
typedef unsigned char u_int8_t;
# 82 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int16_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int16_t.h"
typedef unsigned short u_int16_t;
# 83 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int32_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int32_t.h"
typedef unsigned int u_int32_t;
# 84 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int64_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_u_int64_t.h"
typedef unsigned long long u_int64_t;
# 85 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2


typedef int64_t register_t;




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_intptr_t.h" 2

typedef __darwin_intptr_t intptr_t;
# 93 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uintptr_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uintptr_t.h"
typedef unsigned long uintptr_t;
# 94 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/types.h" 2



typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;







typedef u_int64_t syscall_arg_t;
# 36 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/types.h" 2
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_va_list.h" 2
typedef __darwin_va_list va_list;
# 76 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_size_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_size_t.h"
typedef __darwin_size_t size_t;
# 77 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_null.h" 1
# 78 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stdio.h" 1
# 37 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stdio.h"


int renameat(int, const char *, int, const char *) ;






int renamex_np(const char *, const char *, unsigned int) ;
int renameatx_np(int, const char *, int, const char *, unsigned int) ;




# 80 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h" 2

typedef __darwin_off_t fpos_t;
# 92 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h"
struct __sbuf {
 unsigned char *_base;
 int _size;
};


struct __sFILEX;
# 126 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_stdio.h"
typedef struct __sFILE {
 unsigned char *_p;
 int _r;
 int _w;
 short _flags;
 short _file;
 struct __sbuf _bf;
 int _lbfsize;


 void *_cookie;
 int (* _close)(void *);
 int (* _read) (void *, char *, int);
 fpos_t (* _seek) (void *, fpos_t, int);
 int (* _write)(void *, const char *, int);


 struct __sbuf _ub;
 struct __sFILEX *_extra;
 int _ur;


 unsigned char _ubuf[3];
 unsigned char _nbuf[1];


 struct __sbuf _lb;


 int _blksize;
 fpos_t _offset;
} FILE;
# 65 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 2


extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;

# 141 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"

void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE * restrict, fpos_t *);
char *fgets(char * restrict, int, FILE *);



FILE *fopen(const char * restrict __filename, const char * restrict __mode) __asm("_" "fopen" );

int fprintf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
int fputc(int, FILE *);
int fputs(const char * restrict, FILE * restrict) __asm("_" "fputs" );
size_t fread(void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream);
FILE *freopen(const char * restrict, const char * restrict,
                 FILE * restrict) __asm("_" "freopen" );
int fscanf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream) __asm("_" "fwrite" );
int getc(FILE *);
int getchar(void);
char *gets(char *);
void perror(const char *) __attribute__((__cold__));
int printf(const char * restrict, ...) __attribute__((__format__ (__printf__, 1, 2)));
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename (const char *__old, const char *__new);
void rewind(FILE *);
int scanf(const char * restrict, ...) __attribute__((__format__ (__scanf__, 1, 2)));
void setbuf(FILE * restrict, char * restrict);
int setvbuf(FILE * restrict, char * restrict, int, size_t);
int sprintf(char * restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3))) ;
int sscanf(const char * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
FILE *tmpfile(void);



__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of tmpnam(3), it is highly recommended that you use mkstemp(3) instead.")))

char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE * restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
int vprintf(const char * restrict, va_list) __attribute__((__format__ (__printf__, 1, 0)));
int vsprintf(char * restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0))) ;

# 204 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_ctermid.h" 1
# 29 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_ctermid.h"


char *ctermid(char *);


# 206 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 2




FILE *fdopen(int, const char *) __asm("_" "fdopen" );

int fileno(FILE *);

# 227 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"

int pclose(FILE *) ;



FILE *popen(const char *, const char *) __asm("_" "popen" ) ;


# 248 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"

int __srget(FILE *);
int __svfscanf(FILE *, const char *, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int __swbuf(int, FILE *);








extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __sputc(int _c, FILE *_p) {
 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf(_c, _p));
}
# 285 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"

void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);



int getw(FILE *);
int putw(int, FILE *);




__attribute__((__deprecated__("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of tempnam(3), it is highly recommended that you use mkstemp(3) instead.")))

char *tempnam(const char *__dir, const char *__prefix) __asm("_" "tempnam" );

# 324 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_off_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_off_t.h"
typedef __darwin_off_t off_t;
# 325 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 2


int fseeko(FILE * __stream, off_t __offset, int __whence);
off_t ftello(FILE * __stream);





int snprintf(char * restrict __str, size_t __size, const char * restrict __format, ...) __attribute__((__format__ (__printf__, 3, 4)));
int vfscanf(FILE * restrict __stream, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int vscanf(const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 1, 0)));
int vsnprintf(char * restrict __str, size_t __size, const char * restrict __format, va_list) __attribute__((__format__ (__printf__, 3, 0)));
int vsscanf(const char * restrict __str, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));

# 349 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ssize_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ssize_t.h"
typedef __darwin_ssize_t ssize_t;
# 350 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 2


int dprintf(int, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3))) ;
int vdprintf(int, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0))) ;
ssize_t getdelim(char ** restrict __linep, size_t * restrict __linecapp, int __delimiter, FILE * restrict __stream) ;
ssize_t getline(char ** restrict __linep, size_t * restrict __linecapp, FILE * restrict __stream) ;
FILE *fmemopen(void * restrict __buf, size_t __size, const char * restrict __mode) ;
FILE *open_memstream(char **__bufp, size_t *__sizep) ;









extern const int sys_nerr;
extern const char *const sys_errlist[];

int asprintf(char ** restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
char *ctermid_r(char *);
char *fgetln(FILE *, size_t *);
const char *fmtcheck(const char *, const char *);
int fpurge(FILE *);
void setbuffer(FILE *, char *, int);
int setlinebuf(FILE *);
int vasprintf(char ** restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
FILE *zopen(const char *, const char *, int);





FILE *funopen(const void *,
                 int (* )(void *, char *, int),
                 int (* )(void *, const char *, int),
                 fpos_t (* )(void *, fpos_t, int),
                 int (* )(void *));

# 407 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_stdio.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_stdio.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_common.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_stdio.h" 2
# 42 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_stdio.h"
extern int __sprintf_chk (char * restrict, int, size_t,
     const char * restrict, ...);
# 52 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_stdio.h"
extern int __snprintf_chk (char * restrict, size_t, int, size_t,
      const char * restrict, ...);







extern int __vsprintf_chk (char * restrict, int, size_t,
      const char * restrict, va_list);







extern int __vsnprintf_chk (char * restrict, size_t, int, size_t,
       const char * restrict, va_list);
# 408 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdio.h" 2
# 5 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 1
# 66 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 1
# 79 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h"
typedef enum {
 P_ALL,
 P_PID,
 P_PGID
} idtype_t;





# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_pid_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_pid_t.h"
typedef __darwin_pid_t pid_t;
# 90 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_id_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_id_t.h"
typedef __darwin_id_t id_t;
# 91 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 2
# 109 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 1
# 73 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/appleapiopts.h" 1
# 74 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2
# 82 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/signal.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/signal.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/signal.h" 1
# 39 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/signal.h"
typedef int sig_atomic_t;
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/signal.h" 2
# 83 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2
# 146 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_mcontext.h" 1
# 29 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_mcontext.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_mcontext.h" 1
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_mcontext.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/machine/_structs.h" 1
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/machine/_structs.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h" 1
# 46 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_i386_thread_state
{
    unsigned int __eax;
    unsigned int __ebx;
    unsigned int __ecx;
    unsigned int __edx;
    unsigned int __edi;
    unsigned int __esi;
    unsigned int __ebp;
    unsigned int __esp;
    unsigned int __ss;
    unsigned int __eflags;
    unsigned int __eip;
    unsigned int __cs;
    unsigned int __ds;
    unsigned int __es;
    unsigned int __fs;
    unsigned int __gs;
};
# 92 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_fp_control
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
      :2,
    __pc :2,





    __rc :2,






             :1,
      :3;
};
typedef struct __darwin_fp_control __darwin_fp_control_t;
# 150 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_fp_status
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
    __stkflt :1,
    __errsumm :1,
    __c0 :1,
    __c1 :1,
    __c2 :1,
    __tos :3,
    __c3 :1,
    __busy :1;
};
typedef struct __darwin_fp_status __darwin_fp_status_t;
# 194 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_mmst_reg
{
 char __mmst_reg[10];
 char __mmst_rsrv[6];
};
# 213 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_xmm_reg
{
 char __xmm_reg[16];
};
# 229 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_ymm_reg
{
 char __ymm_reg[32];
};
# 245 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_zmm_reg
{
 char __zmm_reg[64];
};
# 259 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_opmask_reg
{
 char __opmask_reg[8];
};
# 281 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_i386_float_state
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;
 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;
 __uint16_t __fpu_rsrv2;
 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;
 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 char __fpu_rsrv4[14*16];
 int __fpu_reserved1;
};


struct __darwin_i386_avx_state
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;
 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;
 __uint16_t __fpu_rsrv2;
 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;
 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 char __fpu_rsrv4[14*16];
 int __fpu_reserved1;
 char __avx_reserved1[64];
 struct __darwin_xmm_reg __fpu_ymmh0;
 struct __darwin_xmm_reg __fpu_ymmh1;
 struct __darwin_xmm_reg __fpu_ymmh2;
 struct __darwin_xmm_reg __fpu_ymmh3;
 struct __darwin_xmm_reg __fpu_ymmh4;
 struct __darwin_xmm_reg __fpu_ymmh5;
 struct __darwin_xmm_reg __fpu_ymmh6;
 struct __darwin_xmm_reg __fpu_ymmh7;
};


struct __darwin_i386_avx512_state
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;
 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;
 __uint16_t __fpu_rsrv2;
 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;
 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 char __fpu_rsrv4[14*16];
 int __fpu_reserved1;
 char __avx_reserved1[64];
 struct __darwin_xmm_reg __fpu_ymmh0;
 struct __darwin_xmm_reg __fpu_ymmh1;
 struct __darwin_xmm_reg __fpu_ymmh2;
 struct __darwin_xmm_reg __fpu_ymmh3;
 struct __darwin_xmm_reg __fpu_ymmh4;
 struct __darwin_xmm_reg __fpu_ymmh5;
 struct __darwin_xmm_reg __fpu_ymmh6;
 struct __darwin_xmm_reg __fpu_ymmh7;
 struct __darwin_opmask_reg __fpu_k0;
 struct __darwin_opmask_reg __fpu_k1;
 struct __darwin_opmask_reg __fpu_k2;
 struct __darwin_opmask_reg __fpu_k3;
 struct __darwin_opmask_reg __fpu_k4;
 struct __darwin_opmask_reg __fpu_k5;
 struct __darwin_opmask_reg __fpu_k6;
 struct __darwin_opmask_reg __fpu_k7;
 struct __darwin_ymm_reg __fpu_zmmh0;
 struct __darwin_ymm_reg __fpu_zmmh1;
 struct __darwin_ymm_reg __fpu_zmmh2;
 struct __darwin_ymm_reg __fpu_zmmh3;
 struct __darwin_ymm_reg __fpu_zmmh4;
 struct __darwin_ymm_reg __fpu_zmmh5;
 struct __darwin_ymm_reg __fpu_zmmh6;
 struct __darwin_ymm_reg __fpu_zmmh7;
};
# 575 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_i386_exception_state
{
 __uint16_t __trapno;
 __uint16_t __cpu;
 __uint32_t __err;
 __uint32_t __faultvaddr;
};
# 595 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_debug_state32
{
 unsigned int __dr0;
 unsigned int __dr1;
 unsigned int __dr2;
 unsigned int __dr3;
 unsigned int __dr4;
 unsigned int __dr5;
 unsigned int __dr6;
 unsigned int __dr7;
};


struct __x86_instruction_state
{
        int __insn_stream_valid_bytes;
        int __insn_offset;
 int __out_of_synch;





        __uint8_t __insn_bytes[(2448 - 64 - 4)];

 __uint8_t __insn_cacheline[64];
};


struct __last_branch_record
{
 __uint64_t __from_ip;
 __uint64_t __to_ip;
 __uint32_t __mispredict : 1,
   __tsx_abort : 1,
   __in_tsx : 1,
   __cycle_count: 16,
   __reserved : 13;
};


struct __last_branch_state
{
        int __lbr_count;
 __uint32_t __lbr_supported_tsx : 1,
     __lbr_supported_cycle_count : 1,
     __reserved : 30;

 struct __last_branch_record __lbrs[32];
};
# 702 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __x86_pagein_state
{
 int __pagein_error;
};







struct __darwin_x86_thread_state64
{
 __uint64_t __rax;
 __uint64_t __rbx;
 __uint64_t __rcx;
 __uint64_t __rdx;
 __uint64_t __rdi;
 __uint64_t __rsi;
 __uint64_t __rbp;
 __uint64_t __rsp;
 __uint64_t __r8;
 __uint64_t __r9;
 __uint64_t __r10;
 __uint64_t __r11;
 __uint64_t __r12;
 __uint64_t __r13;
 __uint64_t __r14;
 __uint64_t __r15;
 __uint64_t __rip;
 __uint64_t __rflags;
 __uint64_t __cs;
 __uint64_t __fs;
 __uint64_t __gs;
};
# 771 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_thread_full_state64
{
 struct __darwin_x86_thread_state64 __ss64;
 __uint64_t __ds;
 __uint64_t __es;
 __uint64_t __ss;
 __uint64_t __gsbase;
};
# 794 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_float_state64
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;


 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;

 __uint16_t __fpu_rsrv2;


 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;

 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 struct __darwin_xmm_reg __fpu_xmm8;
 struct __darwin_xmm_reg __fpu_xmm9;
 struct __darwin_xmm_reg __fpu_xmm10;
 struct __darwin_xmm_reg __fpu_xmm11;
 struct __darwin_xmm_reg __fpu_xmm12;
 struct __darwin_xmm_reg __fpu_xmm13;
 struct __darwin_xmm_reg __fpu_xmm14;
 struct __darwin_xmm_reg __fpu_xmm15;
 char __fpu_rsrv4[6*16];
 int __fpu_reserved1;
};


struct __darwin_x86_avx_state64
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;


 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;

 __uint16_t __fpu_rsrv2;


 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;

 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 struct __darwin_xmm_reg __fpu_xmm8;
 struct __darwin_xmm_reg __fpu_xmm9;
 struct __darwin_xmm_reg __fpu_xmm10;
 struct __darwin_xmm_reg __fpu_xmm11;
 struct __darwin_xmm_reg __fpu_xmm12;
 struct __darwin_xmm_reg __fpu_xmm13;
 struct __darwin_xmm_reg __fpu_xmm14;
 struct __darwin_xmm_reg __fpu_xmm15;
 char __fpu_rsrv4[6*16];
 int __fpu_reserved1;
 char __avx_reserved1[64];
 struct __darwin_xmm_reg __fpu_ymmh0;
 struct __darwin_xmm_reg __fpu_ymmh1;
 struct __darwin_xmm_reg __fpu_ymmh2;
 struct __darwin_xmm_reg __fpu_ymmh3;
 struct __darwin_xmm_reg __fpu_ymmh4;
 struct __darwin_xmm_reg __fpu_ymmh5;
 struct __darwin_xmm_reg __fpu_ymmh6;
 struct __darwin_xmm_reg __fpu_ymmh7;
 struct __darwin_xmm_reg __fpu_ymmh8;
 struct __darwin_xmm_reg __fpu_ymmh9;
 struct __darwin_xmm_reg __fpu_ymmh10;
 struct __darwin_xmm_reg __fpu_ymmh11;
 struct __darwin_xmm_reg __fpu_ymmh12;
 struct __darwin_xmm_reg __fpu_ymmh13;
 struct __darwin_xmm_reg __fpu_ymmh14;
 struct __darwin_xmm_reg __fpu_ymmh15;
};


struct __darwin_x86_avx512_state64
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;


 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;

 __uint16_t __fpu_rsrv2;


 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;

 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 struct __darwin_xmm_reg __fpu_xmm8;
 struct __darwin_xmm_reg __fpu_xmm9;
 struct __darwin_xmm_reg __fpu_xmm10;
 struct __darwin_xmm_reg __fpu_xmm11;
 struct __darwin_xmm_reg __fpu_xmm12;
 struct __darwin_xmm_reg __fpu_xmm13;
 struct __darwin_xmm_reg __fpu_xmm14;
 struct __darwin_xmm_reg __fpu_xmm15;
 char __fpu_rsrv4[6*16];
 int __fpu_reserved1;
 char __avx_reserved1[64];
 struct __darwin_xmm_reg __fpu_ymmh0;
 struct __darwin_xmm_reg __fpu_ymmh1;
 struct __darwin_xmm_reg __fpu_ymmh2;
 struct __darwin_xmm_reg __fpu_ymmh3;
 struct __darwin_xmm_reg __fpu_ymmh4;
 struct __darwin_xmm_reg __fpu_ymmh5;
 struct __darwin_xmm_reg __fpu_ymmh6;
 struct __darwin_xmm_reg __fpu_ymmh7;
 struct __darwin_xmm_reg __fpu_ymmh8;
 struct __darwin_xmm_reg __fpu_ymmh9;
 struct __darwin_xmm_reg __fpu_ymmh10;
 struct __darwin_xmm_reg __fpu_ymmh11;
 struct __darwin_xmm_reg __fpu_ymmh12;
 struct __darwin_xmm_reg __fpu_ymmh13;
 struct __darwin_xmm_reg __fpu_ymmh14;
 struct __darwin_xmm_reg __fpu_ymmh15;
 struct __darwin_opmask_reg __fpu_k0;
 struct __darwin_opmask_reg __fpu_k1;
 struct __darwin_opmask_reg __fpu_k2;
 struct __darwin_opmask_reg __fpu_k3;
 struct __darwin_opmask_reg __fpu_k4;
 struct __darwin_opmask_reg __fpu_k5;
 struct __darwin_opmask_reg __fpu_k6;
 struct __darwin_opmask_reg __fpu_k7;
 struct __darwin_ymm_reg __fpu_zmmh0;
 struct __darwin_ymm_reg __fpu_zmmh1;
 struct __darwin_ymm_reg __fpu_zmmh2;
 struct __darwin_ymm_reg __fpu_zmmh3;
 struct __darwin_ymm_reg __fpu_zmmh4;
 struct __darwin_ymm_reg __fpu_zmmh5;
 struct __darwin_ymm_reg __fpu_zmmh6;
 struct __darwin_ymm_reg __fpu_zmmh7;
 struct __darwin_ymm_reg __fpu_zmmh8;
 struct __darwin_ymm_reg __fpu_zmmh9;
 struct __darwin_ymm_reg __fpu_zmmh10;
 struct __darwin_ymm_reg __fpu_zmmh11;
 struct __darwin_ymm_reg __fpu_zmmh12;
 struct __darwin_ymm_reg __fpu_zmmh13;
 struct __darwin_ymm_reg __fpu_zmmh14;
 struct __darwin_ymm_reg __fpu_zmmh15;
 struct __darwin_zmm_reg __fpu_zmm16;
 struct __darwin_zmm_reg __fpu_zmm17;
 struct __darwin_zmm_reg __fpu_zmm18;
 struct __darwin_zmm_reg __fpu_zmm19;
 struct __darwin_zmm_reg __fpu_zmm20;
 struct __darwin_zmm_reg __fpu_zmm21;
 struct __darwin_zmm_reg __fpu_zmm22;
 struct __darwin_zmm_reg __fpu_zmm23;
 struct __darwin_zmm_reg __fpu_zmm24;
 struct __darwin_zmm_reg __fpu_zmm25;
 struct __darwin_zmm_reg __fpu_zmm26;
 struct __darwin_zmm_reg __fpu_zmm27;
 struct __darwin_zmm_reg __fpu_zmm28;
 struct __darwin_zmm_reg __fpu_zmm29;
 struct __darwin_zmm_reg __fpu_zmm30;
 struct __darwin_zmm_reg __fpu_zmm31;
};
# 1252 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_exception_state64
{
    __uint16_t __trapno;
    __uint16_t __cpu;
    __uint32_t __err;
    __uint64_t __faultvaddr;
};
# 1272 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_debug_state64
{
 __uint64_t __dr0;
 __uint64_t __dr1;
 __uint64_t __dr2;
 __uint64_t __dr3;
 __uint64_t __dr4;
 __uint64_t __dr5;
 __uint64_t __dr6;
 __uint64_t __dr7;
};
# 1300 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/i386/_structs.h"
struct __darwin_x86_cpmu_state64
{
 __uint64_t __ctrs[16];
};
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach/machine/_structs.h" 2
# 35 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_mcontext.h" 2




struct __darwin_mcontext32
{
 struct __darwin_i386_exception_state __es;
 struct __darwin_i386_thread_state __ss;
 struct __darwin_i386_float_state __fs;
};


struct __darwin_mcontext_avx32
{
 struct __darwin_i386_exception_state __es;
 struct __darwin_i386_thread_state __ss;
 struct __darwin_i386_avx_state __fs;
};



struct __darwin_mcontext_avx512_32
{
 struct __darwin_i386_exception_state __es;
 struct __darwin_i386_thread_state __ss;
 struct __darwin_i386_avx512_state __fs;
};
# 97 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_mcontext.h"
struct __darwin_mcontext64
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_state64 __ss;
 struct __darwin_x86_float_state64 __fs;
};


struct __darwin_mcontext64_full
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_full_state64 __ss;
 struct __darwin_x86_float_state64 __fs;
};


struct __darwin_mcontext_avx64
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_state64 __ss;
 struct __darwin_x86_avx_state64 __fs;
};


struct __darwin_mcontext_avx64_full
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_full_state64 __ss;
 struct __darwin_x86_avx_state64 __fs;
};



struct __darwin_mcontext_avx512_64
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_state64 __ss;
 struct __darwin_x86_avx512_state64 __fs;
};


struct __darwin_mcontext_avx512_64_full
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_full_state64 __ss;
 struct __darwin_x86_avx512_state64 __fs;
};
# 204 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_mcontext.h"
typedef struct __darwin_mcontext64 *mcontext_t;
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_mcontext.h" 2
# 147 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_attr_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_attr_t.h"
typedef __darwin_pthread_attr_t pthread_attr_t;
# 149 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_sigaltstack.h" 1
# 42 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_sigaltstack.h"
struct __darwin_sigaltstack
{
 void *ss_sp;
 __darwin_size_t ss_size;
 int ss_flags;
};
typedef struct __darwin_sigaltstack stack_t;
# 151 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ucontext.h" 1
# 39 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ucontext.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/_mcontext.h" 1
# 40 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ucontext.h" 2



struct __darwin_ucontext
{
 int uc_onstack;
 __darwin_sigset_t uc_sigmask;
 struct __darwin_sigaltstack uc_stack;
 struct __darwin_ucontext *uc_link;
 __darwin_size_t uc_mcsize;
 struct __darwin_mcontext64 *uc_mcontext;



};


typedef struct __darwin_ucontext ucontext_t;
# 152 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_sigset_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_sigset_t.h"
typedef __darwin_sigset_t sigset_t;
# 155 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uid_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uid_t.h"
typedef __darwin_uid_t uid_t;
# 157 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h" 2

union sigval {

 int sival_int;
 void *sival_ptr;
};





struct sigevent {
 int sigev_notify;
 int sigev_signo;
 union sigval sigev_value;
 void (*sigev_notify_function)(union sigval);
 pthread_attr_t *sigev_notify_attributes;
};


typedef struct __siginfo {
 int si_signo;
 int si_errno;
 int si_code;
 pid_t si_pid;
 uid_t si_uid;
 int si_status;
 void *si_addr;
 union sigval si_value;
 long si_band;
 unsigned long __pad[7];
} siginfo_t;
# 269 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
union __sigaction_u {
 void (*__sa_handler)(int);
 void (*__sa_sigaction)(int, struct __siginfo *,
     void *);
};


struct __sigaction {
 union __sigaction_u __sigaction_u;
 void (*sa_tramp)(void *, int, int, siginfo_t *, void *);
 sigset_t sa_mask;
 int sa_flags;
};




struct sigaction {
 union __sigaction_u __sigaction_u;
 sigset_t sa_mask;
 int sa_flags;
};
# 331 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
typedef void (*sig_t)(int);
# 348 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
struct sigvec {
 void (*sv_handler)(int);
 int sv_mask;
 int sv_flags;
};
# 367 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"
struct sigstack {
 char *ss_sp;
 int ss_onstack;
};
# 389 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/signal.h"

    void(*signal(int, void (*)(int)))(int);

# 110 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h" 1
# 72 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 1
# 23 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint8_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint8_t.h"
typedef unsigned char uint8_t;
# 24 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint16_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint16_t.h"
typedef unsigned short uint16_t;
# 25 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint32_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint32_t.h"
typedef unsigned int uint32_t;
# 26 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint64_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uint64_t.h"
typedef unsigned long long uint64_t;
# 27 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;



typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;
# 58 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_intmax_t.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_intmax_t.h"
typedef long int intmax_t;
# 59 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uintmax_t.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types/_uintmax_t.h"
typedef long unsigned int uintmax_t;
# 60 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdint.h" 2
# 73 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h" 2







# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_timeval.h" 1
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_timeval.h"
struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
# 81 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h" 2
# 89 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
typedef __uint64_t rlim_t;
# 152 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
struct rusage {
 struct timeval ru_utime;
 struct timeval ru_stime;
# 163 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
 long ru_maxrss;

 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;


};
# 199 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
typedef void *rusage_info_t;

struct rusage_info_v0 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
};

struct rusage_info_v1 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
};

struct rusage_info_v2 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
};

struct rusage_info_v3 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
};

struct rusage_info_v4 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
 uint64_t ri_logical_writes;
 uint64_t ri_lifetime_max_phys_footprint;
 uint64_t ri_instructions;
 uint64_t ri_cycles;
 uint64_t ri_billed_energy;
 uint64_t ri_serviced_energy;
 uint64_t ri_interval_max_phys_footprint;
 uint64_t ri_runnable_time;
};

struct rusage_info_v5 {
 uint8_t ri_uuid[16];
 uint64_t ri_user_time;
 uint64_t ri_system_time;
 uint64_t ri_pkg_idle_wkups;
 uint64_t ri_interrupt_wkups;
 uint64_t ri_pageins;
 uint64_t ri_wired_size;
 uint64_t ri_resident_size;
 uint64_t ri_phys_footprint;
 uint64_t ri_proc_start_abstime;
 uint64_t ri_proc_exit_abstime;
 uint64_t ri_child_user_time;
 uint64_t ri_child_system_time;
 uint64_t ri_child_pkg_idle_wkups;
 uint64_t ri_child_interrupt_wkups;
 uint64_t ri_child_pageins;
 uint64_t ri_child_elapsed_abstime;
 uint64_t ri_diskio_bytesread;
 uint64_t ri_diskio_byteswritten;
 uint64_t ri_cpu_time_qos_default;
 uint64_t ri_cpu_time_qos_maintenance;
 uint64_t ri_cpu_time_qos_background;
 uint64_t ri_cpu_time_qos_utility;
 uint64_t ri_cpu_time_qos_legacy;
 uint64_t ri_cpu_time_qos_user_initiated;
 uint64_t ri_cpu_time_qos_user_interactive;
 uint64_t ri_billed_system_time;
 uint64_t ri_serviced_system_time;
 uint64_t ri_logical_writes;
 uint64_t ri_lifetime_max_phys_footprint;
 uint64_t ri_instructions;
 uint64_t ri_cycles;
 uint64_t ri_billed_energy;
 uint64_t ri_serviced_energy;
 uint64_t ri_interval_max_phys_footprint;
 uint64_t ri_runnable_time;
 uint64_t ri_flags;
};

typedef struct rusage_info_v5 rusage_info_current;
# 411 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
struct rlimit {
 rlim_t rlim_cur;
 rlim_t rlim_max;
};
# 446 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"
struct proc_rlimit_control_wakeupmon {
 uint32_t wm_flags;
 int32_t wm_rate;
};
# 498 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/resource.h"

int getpriority(int, id_t);

int getiopolicy_np(int, int) ;

int getrlimit(int, struct rlimit *) __asm("_" "getrlimit" );
int getrusage(int, struct rusage *);
int setpriority(int, id_t, int);

int setiopolicy_np(int, int, int) ;

int setrlimit(int, const struct rlimit *) __asm("_" "setrlimit" );

# 111 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 2
# 186 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/endian.h" 1
# 35 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/endian.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/endian.h" 1
# 99 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/endian.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_endian.h" 1
# 130 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_endian.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/_OSByteOrder.h" 1
# 76 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/_OSByteOrder.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/i386/_OSByteOrder.h" 1
# 44 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/i386/_OSByteOrder.h"
static inline
__uint16_t
_OSSwapInt16(
 __uint16_t _data
 )
{
 return (__uint16_t)((_data << 8) | (_data >> 8));
}

static inline
__uint32_t
_OSSwapInt32(
 __uint32_t _data
 )
{



 __asm__ ("bswap   %0" : "+r" (_data));
 return _data;

}
# 91 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/i386/_OSByteOrder.h"
static inline
__uint64_t
_OSSwapInt64(
 __uint64_t _data
 )
{
 __asm__ ("bswap   %0" : "+r" (_data));
 return _data;
}
# 77 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libkern/_OSByteOrder.h" 2
# 131 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_endian.h" 2
# 100 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/endian.h" 2
# 36 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/endian.h" 2
# 187 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h" 2







union wait {
 int w_status;



 struct {

  unsigned int w_Termsig:7,
      w_Coredump:1,
      w_Retcode:8,
      w_Filler:16;







 } w_T;





 struct {

  unsigned int w_Stopval:8,
      w_Stopsig:8,
      w_Filler:16;






 } w_S;
};
# 247 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/wait.h"

pid_t wait(int *) __asm("_" "wait" );
pid_t waitpid(pid_t, int *, int) __asm("_" "waitpid" );

int waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "waitid" );


pid_t wait3(int *, int, struct rusage *);
pid_t wait4(pid_t, int *, int, struct rusage *);


# 67 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/alloca.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/alloca.h"

void *alloca(size_t);

# 69 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2
# 77 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ct_rune_t.h" 1
# 32 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ct_rune_t.h"
typedef __darwin_ct_rune_t ct_rune_t;
# 78 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_rune_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_rune_t.h"
typedef __darwin_rune_t rune_t;
# 79 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_wchar_t.h" 1
# 34 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_wchar_t.h"
typedef __darwin_wchar_t wchar_t;
# 82 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2

typedef struct {
 int quot;
 int rem;
} div_t;

typedef struct {
 long quot;
 long rem;
} ldiv_t;


typedef struct {
 long long quot;
 long long rem;
} lldiv_t;
# 118 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"
extern int __mb_cur_max;
# 128 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/malloc/_malloc.h" 1
# 38 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/malloc/_malloc.h"


void *malloc(size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1)));
void *calloc(size_t __count, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1,2)));
void free(void *);
void *realloc(void *__ptr, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));

void *valloc(size_t) __attribute__((alloc_size(1)));




void *aligned_alloc(size_t __alignment, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2))) ;

int posix_memalign(void **__memptr, size_t __alignment, size_t __size) ;


# 129 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2


void abort(void) __attribute__((__cold__)) __attribute__((__noreturn__));
int abs(int) __attribute__((__const__));
int atexit(void (* )(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);

long long
  atoll(const char *);

void *bsearch(const void *__key, const void *__base, size_t __nel,
     size_t __width, int (* __compar)(const void *, const void *));

div_t div(int, int) __attribute__((__const__));
void exit(int) __attribute__((__noreturn__));

char *getenv(const char *);
long labs(long) __attribute__((__const__));
ldiv_t ldiv(long, long) __attribute__((__const__));

long long
  llabs(long long);
lldiv_t lldiv(long long, long long);


int mblen(const char *__s, size_t __n);
size_t mbstowcs(wchar_t * restrict , const char * restrict, size_t);
int mbtowc(wchar_t * restrict, const char * restrict, size_t);

void qsort(void *__base, size_t __nel, size_t __width,
     int (* __compar)(const void *, const void *));
int rand(void) ;

void srand(unsigned) ;
double strtod(const char *, char **) __asm("_" "strtod" );
float strtof(const char *, char **) __asm("_" "strtof" );
long strtol(const char *__str, char **__endptr, int __base);
long double
  strtold(const char *, char **);

long long
  strtoll(const char *__str, char **__endptr, int __base);

unsigned long
  strtoul(const char *__str, char **__endptr, int __base);

unsigned long long
  strtoull(const char *__str, char **__endptr, int __base);
# 187 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"



int system(const char *) __asm("_" "system" );



size_t wcstombs(char * restrict, const wchar_t * restrict, size_t);
int wctomb(char *, wchar_t);


void _Exit(int) __attribute__((__noreturn__));
long a64l(const char *);
double drand48(void);
char *ecvt(double, int, int *restrict, int *restrict);
double erand48(unsigned short[3]);
char *fcvt(double, int, int *restrict, int *restrict);
char *gcvt(double, int, char *);
int getsubopt(char **, char * const *, char **);
int grantpt(int);

char *initstate(unsigned, char *, size_t);



long jrand48(unsigned short[3]) ;
char *l64a(long);
void lcong48(unsigned short[7]);
long lrand48(void) ;
char *mktemp(char *);
int mkstemp(char *);
long mrand48(void) ;
long nrand48(unsigned short[3]) ;
int posix_openpt(int);
char *ptsname(int);


int ptsname_r(int fildes, char *buffer, size_t buflen) ;


int putenv(char *) __asm("_" "putenv" );
long random(void) ;
int rand_r(unsigned *) ;

char *realpath(const char * restrict, char * restrict) __asm("_" "realpath" "$DARWIN_EXTSN");



unsigned short
 *seed48(unsigned short[3]);
int setenv(const char * __name, const char * __value, int __overwrite) __asm("_" "setenv" );

void setkey(const char *) __asm("_" "setkey" );



char *setstate(const char *);
void srand48(long);

void srandom(unsigned);



int unlockpt(int);

int unsetenv(const char *) __asm("_" "unsetenv" );







# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_dev_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_dev_t.h"
typedef __darwin_dev_t dev_t;
# 261 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_mode_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_mode_t.h"
typedef __darwin_mode_t mode_t;
# 262 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h" 2


uint32_t arc4random(void);
void arc4random_addrandom(unsigned char * , int )
   
   
   
    ;
void arc4random_buf(void * __buf, size_t __nbytes) ;
void arc4random_stir(void);
uint32_t
  arc4random_uniform(uint32_t __upper_bound) ;







char *cgetcap(char *, const char *, int);
int cgetclose(void);
int cgetent(char **, char **, const char *);
int cgetfirst(char **, char **);
int cgetmatch(const char *, const char *);
int cgetnext(char **, char **);
int cgetnum(char *, const char *, long *);
int cgetset(const char *);
int cgetstr(char *, const char *, char **);
int cgetustr(char *, const char *, char **);

int daemon(int, int) __asm("_" "daemon" "$1050") ;
char *devname(dev_t, mode_t);
char *devname_r(dev_t, mode_t, char *buf, int len);
char *getbsize(int *, long *);
int getloadavg(double [], int);
const char
 *getprogname(void);
void setprogname(const char *);
# 309 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/stdlib.h"
int heapsort(void *__base, size_t __nel, size_t __width,
     int (* __compar)(const void *, const void *));





int mergesort(void *__base, size_t __nel, size_t __width,
     int (* __compar)(const void *, const void *));





void psort(void *__base, size_t __nel, size_t __width,
     int (* __compar)(const void *, const void *))
     ;





void psort_r(void *__base, size_t __nel, size_t __width, void *,
     int (* __compar)(void *, const void *, const void *))
     ;





void qsort_r(void *__base, size_t __nel, size_t __width, void *,
     int (* __compar)(void *, const void *, const void *));
int radixsort(const unsigned char **__base, int __nel, const unsigned char *__table,
     unsigned __endbyte);
int rpmatch(const char *)
 ;
int sradixsort(const unsigned char **__base, int __nel, const unsigned char *__table,
     unsigned __endbyte);
void sranddev(void);
void srandomdev(void);
void *reallocf(void *__ptr, size_t __size) __attribute__((alloc_size(2)));
long long
 strtonum(const char *__numstr, long long __minval, long long __maxval, const char **__errstrp)
 ;

long long
  strtoq(const char *__str, char **__endptr, int __base);
unsigned long long
  strtouq(const char *__str, char **__endptr, int __base);

extern char *suboptarg;








# 6 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 1
# 69 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h"

void *memchr(const void *__s, int __c, size_t __n);
int memcmp(const void *__s1, const void *__s2, size_t __n);
void *memcpy(void *__dst, const void *__src, size_t __n);
void *memmove(void *__dst, const void *__src, size_t __len);
void *memset(void *__b, int __c, size_t __len);
char *strcat(char *__s1, const char *__s2);
char *strchr(const char *__s, int __c);
int strcmp(const char *__s1, const char *__s2);
int strcoll(const char *__s1, const char *__s2);
char *strcpy(char *__dst, const char *__src);
size_t strcspn(const char *__s, const char *__charset);
char *strerror(int __errnum) __asm("_" "strerror" );
size_t strlen(const char *__s);
char *strncat(char *__s1, const char *__s2, size_t __n);
int strncmp(const char *__s1, const char *__s2, size_t __n);
char *strncpy(char *__dst, const char *__src, size_t __n);
char *strpbrk(const char *__s, const char *__charset);
char *strrchr(const char *__s, int __c);
size_t strspn(const char *__s, const char *__charset);
char *strstr(const char *__big, const char *__little);
char *strtok(char *__str, const char *__sep);
size_t strxfrm(char *__s1, const char *__s2, size_t __n);

# 103 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h"

char *strtok_r(char *__str, const char *__sep, char **__lasts);

# 115 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h"

int strerror_r(int __errnum, char *__strerrbuf, size_t __buflen);
char *strdup(const char *__s1);
void *memccpy(void *__dst, const void *__src, int __c, size_t __n);

# 129 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h"

char *stpcpy(char *__dst, const char *__src);
char *stpncpy(char *__dst, const char *__src, size_t __n) ;
char *strndup(const char *__s1, size_t __n) ;
size_t strnlen(const char *__s1, size_t __n) ;
char *strsignal(int __sig);






# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_rsize_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_rsize_t.h"
typedef __darwin_size_t rsize_t;
# 142 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_errno_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_errno_t.h"
typedef int errno_t;
# 143 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 2


errno_t memset_s(void *__s, rsize_t __smax, int __c, rsize_t __n) ;









void *memmem(const void *__big, size_t __big_len, const void *__little, size_t __little_len) ;
void memset_pattern4(void *__b, const void *__pattern4, size_t __len) ;
void memset_pattern8(void *__b, const void *__pattern8, size_t __len) ;
void memset_pattern16(void *__b, const void *__pattern16, size_t __len) ;

char *strcasestr(const char *__big, const char *__little);
char *strnstr(const char *__big, const char *__little, size_t __len);
size_t strlcat(char *__dst, const char *__source, size_t __size);
size_t strlcpy(char *__dst, const char *__source, size_t __size);
void strmode(int __mode, char *__bp);
char *strsep(char **__stringp, const char *__delim);


void swab(const void * restrict, void * restrict, ssize_t);



int timingsafe_bcmp(const void *__b1, const void *__b2, size_t __len);



int strsignal_r(int __sig, char *__strsignalbuf, size_t __buflen);







# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/strings.h" 1
# 67 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/strings.h"



int bcmp(const void *, const void *, size_t) ;
void bcopy(const void *, void *, size_t) ;
void bzero(void *, size_t) ;
char *index(const char *, int) ;
char *rindex(const char *, int) ;


int ffs(int);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);





int ffsl(long) ;
int ffsll(long long) ;
int fls(int) ;
int flsl(long) ;
int flsll(long long) ;


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 1
# 93 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/strings.h" 2




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_strings.h" 1
# 98 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/strings.h" 2
# 185 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 2
# 194 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/secure/_string.h" 1
# 195 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/string.h" 2
# 7 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/usr/local/Cellar/gcc@10/10.3.0/lib/gcc/10/gcc/x86_64-apple-darwin19/10.3.0/include/stdbool.h" 1 3 4
# 8 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/assert.h" 1
# 75 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/assert.h"

void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) __attribute__((__cold__)) ;




# 9 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/signal.h" 1
# 66 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/signal.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_pthread/_pthread_t.h"
typedef __darwin_pthread_t pthread_t;
# 67 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/signal.h" 2


extern const char *const sys_signame[32];
extern const char *const sys_siglist[32];



int raise(int);




void (* bsd_signal(int, void (* )(int)))(int);
int kill(pid_t, int) __asm("_" "kill" );
int killpg(pid_t, int) __asm("_" "killpg" );
int pthread_kill(pthread_t, int);
int pthread_sigmask(int, const sigset_t *, sigset_t *) __asm("_" "pthread_sigmask" );
int sigaction(int, const struct sigaction * restrict,
     struct sigaction * restrict);
int sigaddset(sigset_t *, int);
int sigaltstack(const stack_t * restrict, stack_t * restrict) __asm("_" "sigaltstack" ) ;
int sigdelset(sigset_t *, int);
int sigemptyset(sigset_t *);
int sigfillset(sigset_t *);
int sighold(int);
int sigignore(int);
int siginterrupt(int, int);
int sigismember(const sigset_t *, int);
int sigpause(int) __asm("_" "sigpause" );
int sigpending(sigset_t *);
int sigprocmask(int, const sigset_t * restrict, sigset_t * restrict);
int sigrelse(int);
void (* sigset(int, void (* )(int)))(int);
int sigsuspend(const sigset_t *) __asm("_" "sigsuspend" );
int sigwait(const sigset_t * restrict, int * restrict) __asm("_" "sigwait" );

void psignal(unsigned int, const char *);
int sigblock(int);
int sigsetmask(int);
int sigvec(int, struct sigvec *, struct sigvec *);




extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int
__sigbits(int __signo)
{
    return __signo > 32 ? 0 : (1 << (__signo - 1));
}
# 10 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/usr/local/Cellar/gcc@10/10.3.0/lib/gcc/10/gcc/x86_64-apple-darwin19/10.3.0/include/stdarg.h" 1 3 4
# 40 "/usr/local/Cellar/gcc@10/10.3.0/lib/gcc/10/gcc/x86_64-apple-darwin19/10.3.0/include/stdarg.h" 3 4

# 40 "/usr/local/Cellar/gcc@10/10.3.0/lib/gcc/10/gcc/x86_64-apple-darwin19/10.3.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/usr/local/Cellar/gcc@10/10.3.0/lib/gcc/10/gcc/x86_64-apple-darwin19/10.3.0/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 11 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2

# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/util/bit_util.h" 1






# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h" 1
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"

# 44 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
    
# 44 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
   typedef float float_t;
    typedef double double_t;
# 111 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern int __math_errhandling(void);
# 131 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern int __fpclassifyf(float);
extern int __fpclassifyd(double);
extern int __fpclassifyl(long double);
# 174 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinited(double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitel(long double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinff(float);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinfd(double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinfl(long double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnanf(float);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnand(double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnanl(long double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormalf(float);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormald(double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormall(long double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitf(float);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitd(double);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitl(long double);

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitef(float __x) {
    return __x == __x && __builtin_fabsf(__x) != __builtin_inff();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinited(double __x) {
    return __x == __x && __builtin_fabs(__x) != __builtin_inf();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitel(long double __x) {
    return __x == __x && __builtin_fabsl(__x) != __builtin_infl();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinff(float __x) {
    return __builtin_fabsf(__x) == __builtin_inff();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinfd(double __x) {
    return __builtin_fabs(__x) == __builtin_inf();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isinfl(long double __x) {
    return __builtin_fabsl(__x) == __builtin_infl();
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnanf(float __x) {
    return __x != __x;
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnand(double __x) {
    return __x != __x;
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnanl(long double __x) {
    return __x != __x;
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitf(float __x) {
    union { float __f; unsigned int __u; } __u;
    __u.__f = __x;
    return (int)(__u.__u >> 31);
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitd(double __x) {
    union { double __f; unsigned long long __u; } __u;
    __u.__f = __x;
    return (int)(__u.__u >> 63);
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_signbitl(long double __x) {
    union {
        long double __ld;
        struct{ unsigned long long __m; unsigned short __sexp; } __p;
    } __u;
    __u.__ld = __x;
    return (int)(__u.__p.__sexp >> 15);
}







extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormalf(float __x) {
    return __inline_isfinitef(__x) && __builtin_fabsf(__x) >= 1.17549435082228750796873653722224568e-38F;
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormald(double __x) {
    return __inline_isfinited(__x) && __builtin_fabs(__x) >= ((double)2.22507385850720138309023271733240406e-308L);
}
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isnormall(long double __x) {
    return __inline_isfinitel(__x) && __builtin_fabsl(__x) >= 3.36210314311209350626267781732175260e-4932L;
}
# 308 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern float acosf(float);
extern double acos(double);
extern long double acosl(long double);

extern float asinf(float);
extern double asin(double);
extern long double asinl(long double);

extern float atanf(float);
extern double atan(double);
extern long double atanl(long double);

extern float atan2f(float, float);
extern double atan2(double, double);
extern long double atan2l(long double, long double);

extern float cosf(float);
extern double cos(double);
extern long double cosl(long double);

extern float sinf(float);
extern double sin(double);
extern long double sinl(long double);

extern float tanf(float);
extern double tan(double);
extern long double tanl(long double);

extern float acoshf(float);
extern double acosh(double);
extern long double acoshl(long double);

extern float asinhf(float);
extern double asinh(double);
extern long double asinhl(long double);

extern float atanhf(float);
extern double atanh(double);
extern long double atanhl(long double);

extern float coshf(float);
extern double cosh(double);
extern long double coshl(long double);

extern float sinhf(float);
extern double sinh(double);
extern long double sinhl(long double);

extern float tanhf(float);
extern double tanh(double);
extern long double tanhl(long double);

extern float expf(float);
extern double exp(double);
extern long double expl(long double);

extern float exp2f(float);
extern double exp2(double);
extern long double exp2l(long double);

extern float expm1f(float);
extern double expm1(double);
extern long double expm1l(long double);

extern float logf(float);
extern double log(double);
extern long double logl(long double);

extern float log10f(float);
extern double log10(double);
extern long double log10l(long double);

extern float log2f(float);
extern double log2(double);
extern long double log2l(long double);

extern float log1pf(float);
extern double log1p(double);
extern long double log1pl(long double);

extern float logbf(float);
extern double logb(double);
extern long double logbl(long double);

extern float modff(float, float *);
extern double modf(double, double *);
extern long double modfl(long double, long double *);

extern float ldexpf(float, int);
extern double ldexp(double, int);
extern long double ldexpl(long double, int);

extern float frexpf(float, int *);
extern double frexp(double, int *);
extern long double frexpl(long double, int *);

extern int ilogbf(float);
extern int ilogb(double);
extern int ilogbl(long double);

extern float scalbnf(float, int);
extern double scalbn(double, int);
extern long double scalbnl(long double, int);

extern float scalblnf(float, long int);
extern double scalbln(double, long int);
extern long double scalblnl(long double, long int);

extern float fabsf(float);
extern double fabs(double);
extern long double fabsl(long double);

extern float cbrtf(float);
extern double cbrt(double);
extern long double cbrtl(long double);

extern float hypotf(float, float);
extern double hypot(double, double);
extern long double hypotl(long double, long double);

extern float powf(float, float);
extern double pow(double, double);
extern long double powl(long double, long double);

extern float sqrtf(float);
extern double sqrt(double);
extern long double sqrtl(long double);

extern float erff(float);
extern double erf(double);
extern long double erfl(long double);

extern float erfcf(float);
extern double erfc(double);
extern long double erfcl(long double);




extern float lgammaf(float);
extern double lgamma(double);
extern long double lgammal(long double);

extern float tgammaf(float);
extern double tgamma(double);
extern long double tgammal(long double);

extern float ceilf(float);
extern double ceil(double);
extern long double ceill(long double);

extern float floorf(float);
extern double floor(double);
extern long double floorl(long double);

extern float nearbyintf(float);
extern double nearbyint(double);
extern long double nearbyintl(long double);

extern float rintf(float);
extern double rint(double);
extern long double rintl(long double);

extern long int lrintf(float);
extern long int lrint(double);
extern long int lrintl(long double);

extern float roundf(float);
extern double round(double);
extern long double roundl(long double);

extern long int lroundf(float);
extern long int lround(double);
extern long int lroundl(long double);




extern long long int llrintf(float);
extern long long int llrint(double);
extern long long int llrintl(long double);

extern long long int llroundf(float);
extern long long int llround(double);
extern long long int llroundl(long double);


extern float truncf(float);
extern double trunc(double);
extern long double truncl(long double);

extern float fmodf(float, float);
extern double fmod(double, double);
extern long double fmodl(long double, long double);

extern float remainderf(float, float);
extern double remainder(double, double);
extern long double remainderl(long double, long double);

extern float remquof(float, float, int *);
extern double remquo(double, double, int *);
extern long double remquol(long double, long double, int *);

extern float copysignf(float, float);
extern double copysign(double, double);
extern long double copysignl(long double, long double);

extern float nanf(const char *);
extern double nan(const char *);
extern long double nanl(const char *);

extern float nextafterf(float, float);
extern double nextafter(double, double);
extern long double nextafterl(long double, long double);

extern double nexttoward(double, long double);
extern float nexttowardf(float, long double);
extern long double nexttowardl(long double, long double);

extern float fdimf(float, float);
extern double fdim(double, double);
extern long double fdiml(long double, long double);

extern float fmaxf(float, float);
extern double fmax(double, double);
extern long double fmaxl(long double, long double);

extern float fminf(float, float);
extern double fmin(double, double);
extern long double fminl(long double, long double);

extern float fmaf(float, float, float);
extern double fma(double, double, double);
extern long double fmal(long double, long double, long double);
# 552 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern float __inff(void)
 ;
extern double __inf(void)
 ;
extern long double __infl(void)
 ;
extern float __nan(void)
 ;
# 588 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern float __exp10f(float) ;
extern double __exp10(double) ;





extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp);
# 605 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern float __cospif(float) ;
extern double __cospi(double) ;
extern float __sinpif(float) ;
extern double __sinpi(double) ;
extern float __tanpif(float) ;
extern double __tanpi(double) ;
# 636 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp);
extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp);






struct __float2 { float __sinval; float __cosval; };
struct __double2 { double __sinval; double __cosval; };

extern struct __float2 __sincosf_stret(float);
extern struct __double2 __sincos_stret(double);
extern struct __float2 __sincospif_stret(float);
extern struct __double2 __sincospi_stret(double);

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincosf_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincos_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincospif_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincospi_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}







extern double j0(double) ;
extern double j1(double) ;
extern double jn(int, double) ;
extern double y0(double) ;
extern double y1(double) ;
extern double yn(int, double) ;
extern double scalb(double, double);
extern int signgam;
# 743 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/math.h"
extern long int rinttol(double)
 ;

extern long int roundtol(double)
 ;

extern double drem(double, double)
 ;

extern int finite(double)
 ;

extern double gamma(double)
 ;

extern double significand(double)
 ;



struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
};





# 8 "/Users/theofabilous/Documents/GitHub/bitarray/src/util/bit_util.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/limits.h" 1
# 64 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/limits.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/limits.h" 1





# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/limits.h" 1
# 40 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/limits.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_limits.h" 1
# 41 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/limits.h" 2
# 7 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/machine/limits.h" 2
# 65 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/limits.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/syslimits.h" 1
# 66 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/limits.h" 2
# 9 "/Users/theofabilous/Documents/GitHub/bitarray/src/util/bit_util.h" 2





extern const uint8_t LEFT_MOST_MASKS[9];

extern const uint8_t RIGHT_MOST_MASKS[9];

static inline size_t _byte_part(size_t n)
{
 return n >> 3;
}

static inline uint8_t _bit_part(size_t n)
{
 return n & 0b111;
}

static inline uint8_t get_lr_mask(uint8_t i, uint8_t j)
{
 return LEFT_MOST_MASKS[i] | RIGHT_MOST_MASKS[j];
}

static inline size_t
_bit_width(size_t num)
{
 if(num > (size_t) 2147483647)
 {
  size_t sum = 0;
  size_t curr;
  for(;num>=(size_t) 2147483647; num>>=16)
   sum+=16;
  return sum + _bit_width(num);
 }
 else if(num)
  return 1 + (size_t) floor(log2(num));
 else
  return 0;
}

static inline size_t
_byte_size(size_t bitsize)
{
 size_t num_bytes = bitsize >> 3;
 if(bitsize & 0b111)
  return num_bytes+1;
 else
  return num_bytes;
}

char* bit_repr(size_t num);

void print_bit_repr(size_t num);

void print_bit_repr_size(size_t num, size_t w);
# 13 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 1 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 1
# 11 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
struct BitArray;

extern uint8_t Map_Bits;
extern uint8_t Keep_Bits;
extern uint8_t Ignore_Bits;
extern uint8_t Callback_Bits;

typedef struct BinaryMapContext
{
 struct BitArray const * src;
 struct BitArray const * target;
 size_t index;
 char* acc;
} BinaryMapContext;

typedef void (*binary_map_callback_t)(BinaryMapContext* ctx);

typedef struct BinaryMapEntry
{
 const char* k;
 union
 {
  const char *v;
  uint32_t skip;
  void *raw;
  binary_map_callback_t cb;
 };
 uint8_t flags;

} BinaryMapEntry;

extern uint8_t MAPNODE_HAS_RIGHT;
extern uint8_t MAPNODE_HAS_LEFT;
extern uint8_t MAPNODE_MAPPED;
extern uint8_t MAPNODE_ROOT;
extern uint8_t MAPNODE_KEEP_TYPE;
extern uint8_t MAPNODE_IGNORE_TYPE;
extern uint8_t MAPNODE_CALLBACK_TYPE;

typedef struct _MapNode
{
 uint8_t flags;
 struct _MapNode* children[2];
 union
 {
  const char *result;
  uint32_t skip;
  void *raw;
  binary_map_callback_t cb;
 };
} MapNode;

typedef struct _MapTreeNav
{
 MapNode* root;
 size_t current_depth;
 MapNode* curr;
} MapTreeNav;

static inline void
mapnode_set_root(MapNode* node)
{
 node->flags |= MAPNODE_ROOT;
}

static inline 
# 76 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
             _Bool

# 77 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
mapnode_is_root(MapNode* node)
{
 return node->flags & MAPNODE_ROOT;
}

static inline 
# 82 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
             _Bool

# 83 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
mapnode_has_left(MapNode* node)
{
 return node->flags & MAPNODE_HAS_LEFT;
}

static inline 
# 88 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
             _Bool

# 89 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
mapnode_has_right(MapNode* node)
{
 return node->flags & MAPNODE_HAS_RIGHT;
}

static inline 
# 94 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
             _Bool

# 95 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
mapnode_is_leaf(MapNode* node)
{
 return !(node->flags & MAPNODE_HAS_RIGHT) && !(node->flags & MAPNODE_HAS_LEFT);
}

static inline void
mapnode_set_mapped(MapNode* node)
{
 node->flags |= MAPNODE_MAPPED;
}

static inline 
# 106 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
             _Bool

# 107 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
mapnode_is_mapped(MapNode* node)
{
 return node->flags & MAPNODE_MAPPED;
}

static inline void
mapnode_set_flag(MapNode* node, uint8_t flag)
{
 node->flags |= flag;
}

MapNode* new_root_node();

MapNode* new_node();


# 122 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
_Bool 
# 122 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
    new_child(MapNode* parent, 
# 122 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
                               _Bool 
# 122 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
                                    bit);

MapTreeNav* new_MapTreeNav();


# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
_Bool 
# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
    mapnode_delete_all(MapNode* root);


# 128 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h" 3 4
_Bool 
# 128 "/Users/theofabilous/Documents/GitHub/bitarray/src/binarymap.h"
    del_MapTreeNav(MapTreeNav* tree);

MapTreeNav*
build_binary_map(
 BinaryMapEntry entries[],
 size_t num_entries);
# 14 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 2
# 40 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
typedef size_t bitarray_size_t;

typedef size_t bit_allocator_t;

typedef struct BitArray
{
 bitarray_size_t size;
 bit_allocator_t allocator;
 uint8_t *data;
} BitArray;

typedef struct BitArrayModule
{
 bitarray_size_t (*size)(BitArray *self);
 void (*set)(BitArray *self, 
# 54 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                            _Bool 
# 54 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                 bit, size_t index);
 void (*unset)(BitArray *self, size_t i);
 
# 56 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 56 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     (*append)(BitArray *self, size_t val);
 
# 57 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 57 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     (*append_str)(BitArray *self, const char* bits);
 uint8_t (*get)(BitArray *self, size_t i);
 size_t (*get_slice)(BitArray *self, size_t i, size_t j);
 void (*set_slice)(BitArray *self, size_t i, size_t j, size_t val);
 void (*fill_slice)(BitArray *self, size_t i, size_t j, 
# 61 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                                                       _Bool 
# 61 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                                            bit);
 void (*set_slice_str)(BitArray *self, size_t i, size_t j,
        uint8_t flags, const char* bits);
 void (*memcpy)(BitArray* self, size_t i, size_t len, uint8_t* buffer);
 void (*bit_strcpy)(BitArray* self, size_t i, int64_t len, char* buffer);
 void (*print_bits)(BitArray* self, size_t i, int64_t len);
 void (*print_bytes)(BitArray* self, size_t i, int64_t len);
 char* (*to_str)(BitArray *self);
 
# 69 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 69 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     (*resize)(BitArray *self, size_t n);
 
# 70 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 70 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     (*reserve)(BitArray* self, bitarray_size_t new_size);
 void (*set_allocator_size)(BitArray* self, size_t alloc_size);
 void (*for_each)(BitArray *self, void (*f)(
# 72 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                                           _Bool
# 72 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                               ), int64_t m);
 void (*transform)(BitArray *self, 
# 73 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                                  _Bool 
# 73 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                       (*f)(
# 73 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                                            _Bool
# 73 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                                ), int64_t m);
 void (*enumerate_each)(BitArray* self, void (*func)(
# 74 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
                                                    _Bool 
# 74 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                                                         bit, size_t index),
         int64_t max);
 void (*map)(BitArray *self, BinaryMapEntry maps[], size_t n);
 
# 77 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 77 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     (*map_into)(BitArray* self, BitArray* other, BinaryMapEntry maps[], size_t n);
} BitArrayModule;



extern uint8_t _bitarray_ssize_t;
extern uint8_t _bitarray_ssize_t_bits;
extern const bitarray_size_t BITARRAY_S_ONE;
extern const bitarray_size_t BITARRAY_S_ZERO;
extern const bitarray_size_t BITARRAY_S_THREE;
extern bitarray_size_t bitarray_umask;
extern uint8_t bitarray_umask_amt;
extern bitarray_size_t bitarray_lmask;
extern bitarray_size_t bitarray_max_bytes;
extern bitarray_size_t BITARRAY_MEM_ERR_FLAG;
extern bitarray_size_t BITARRAY_ILL_ERR_FLAG;
extern bitarray_size_t BITARRAY_FLAG1;
extern bitarray_size_t BITARRAY_FLAG2;
extern bitarray_size_t BITARRAY_ERR_MASK;

extern const bit_allocator_t BIT_ALLOC_SIZE_MASK;
extern const bit_allocator_t BIT_ALLOC_EXTRA_MASK;
extern const uint8_t STRIP_MSB;
extern const uint8_t STRIP_LSB;






void
free_BitArray_buffer(
 BitArray* obj);


# 111 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 112 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
init_BitArray(
 BitArray* obj,
 bitarray_size_t size);

BitArray*
new_BitArray(
 bitarray_size_t size);


# 120 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 121 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
init_Bitarray_from_file(
 BitArray* obj,
 const char* path);

BitArray*
new_Bitarray_from_file(
 const char* path);

void
del_BitArray(
 BitArray* obj);






void
bitarray_set_allocator_size(
 BitArray* self,
 size_t alloc_size);

bitarray_size_t
bitarray_size(
 BitArray *self);


# 147 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 148 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_reserve(
 BitArray* self,
 bitarray_size_t new_size);


# 152 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 153 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_resize(
 BitArray* self,
 bitarray_size_t new_size);





void
bitarray_set(
 BitArray *self,
 
# 164 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 164 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     bit,
 size_t i);

void
bitarray_unset(
 BitArray *self,
 size_t i);

void
bitarray_set_byte(
 BitArray* self,
 uint8_t byte,
 size_t i);

void
bitarray_set_slice(
 BitArray *self,
 size_t i,
 size_t j,
 size_t val);

void
bitarray_set_slice_str(
 BitArray *self,
 size_t i,
 size_t j,
 uint8_t flags,
 const char* bits);

void
bitarray_fill_slice(
 BitArray *self,
 size_t i,
 size_t j,
 
# 198 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool 
# 198 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
     bit);


# 200 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 201 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_append(
 BitArray *self,
 size_t val);


# 205 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 206 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_append_str(
 BitArray *self,
 const char* bits);






uint8_t
bitarray_get(
 BitArray *self,
 size_t i);

uint8_t
bitarray_get_byte(
 BitArray* self,
 size_t i);

size_t
bitarray_get_slice(
 BitArray *self,
 size_t i,
 size_t j);

void
bitarray_memcpy(
 BitArray* self,
 size_t i,
 size_t len,
 uint8_t* buffer);

void
bitarray_bit_strcpy(
 BitArray* self,
 size_t i,
 int64_t len,
 char* buffer);

void
bitarray_print_bits(
 BitArray* self,
 size_t i,
 int64_t len);

void
bitarray_print_bytes(
 BitArray* self,
 size_t i,
 int64_t len);

char*
bitarray_to_str(
 BitArray *self);






void
bitarray_for_each(
 BitArray *self,
 void (*func)(
# 269 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool
# 269 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                 ),
 int64_t max);

void
bitarray_transform(
 BitArray *self,
 
# 275 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool
# 275 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
    (*func)(
# 275 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
            _Bool
# 275 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                ),
 int64_t max);

void
bitarray_enumerate_each(
 BitArray* self,
 void (*func)(
# 281 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool 
# 281 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
                  bit, size_t index),
 int64_t max);

void
bitarray_map(
 BitArray* self,
 BinaryMapEntry maps[],
    size_t n);


# 290 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 291 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_map_into(
 BitArray* self,
 BitArray* other,
 BinaryMapEntry maps[],
 size_t n);






void
bitarray_unset_err(
 BitArray* self,
 bitarray_size_t err);

void
bitarray_clear_all_err(
 BitArray* self);


# 311 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 312 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_check_err(
 BitArray* self,
 bitarray_size_t err);


# 316 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
_Bool

# 317 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
bitarray_check_status(
 BitArray* self);
# 352 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
static inline void
_bitarray_set_extra_bytes(
 BitArray* self,
 size_t extra_bytes)
{
 self->allocator = ((self->allocator & BIT_ALLOC_SIZE_MASK)
      | (BIT_ALLOC_EXTRA_MASK & extra_bytes));
}

static inline size_t
_bitarray_get_extra_bytes(
 BitArray* self)
{
 return self->allocator & BIT_ALLOC_EXTRA_MASK;
}

static inline size_t
_bitarray_get_alloc_size_bytes(
 BitArray* self)
{
 return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 16;
}

static inline size_t
_bitarray_get_alloc_size_bits(
 BitArray* self)
{
 return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 13;
}

static inline void
_bitarray_set_alloc_size_bytes(
 BitArray* self,
 size_t alloc_size)
{
 if(!alloc_size) alloc_size = 1;
 self->allocator = (self->allocator & BIT_ALLOC_EXTRA_MASK)
      | ((0xFFFF & alloc_size) << 16);
}

static inline void
_bitarray_set_on(
 BitArray *self,
 size_t i)
{
 bitarray_size_t byte_index = _byte_part(i);
 uint8_t bit_index = _bit_part(i);
 self->data[byte_index] |= (1 << (7-bit_index));
}

static inline void
_bitarray_set_off(
 BitArray *self,
 size_t i)
{
 bitarray_size_t byte_index = _byte_part(i);
 uint8_t bit_index = _bit_part(i);
 self->data[byte_index] &= ~(1 << (7-bit_index));
}

static inline 
# 412 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool

# 413 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
_bitarray_get(
 BitArray *self,
 size_t i)
{
 uint8_t r_bit_index = 7 - (i & 0b111);
 return (self->data[i >> 3] & (1 << r_bit_index)) >> r_bit_index;
}

static inline bitarray_size_t
_bitarray_size(
 BitArray *self)
{
 return bitarray_lmask & self->size;
}

static inline bitarray_size_t
_bitarray_num_bytes(
 BitArray *self)
{
 if(self->size & 0b111)
  return ((_bitarray_size(self) >> 3)+1);
 else
  return (_bitarray_size(self) >> 3);
}

static inline bitarray_size_t
_bitarray_real_num_bytes(
 BitArray *self)
{
 return _bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self);
}

static inline bitarray_size_t
_bitarray_real_num_bits(
 BitArray *self)
{
 return (_bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self)) << 3;
}

static inline 
# 452 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool

# 453 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
_bitarray_actually_needs_resize_bits(
 BitArray *self,
 size_t num_bits)
{
 return _byte_size(num_bits) > _bitarray_real_num_bytes(self);
}

static inline bitarray_size_t
_bitarray_flags(
 BitArray *self)
{
 return self->size & bitarray_umask;
}

static inline void
_bitarray_set_size(
 BitArray *self,
 bitarray_size_t size)
{
 self->size = (self->size & bitarray_umask) | size;
}

static inline void
_bitarray_incr_size(
 BitArray *self,
 bitarray_size_t incr)
{
 _bitarray_set_size(self, _bitarray_size(self) + incr);
}

static inline void
_bitarray_set_err(
 BitArray* self,
 bitarray_size_t err)
{
 self->size |= err;
}

static inline 
# 491 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool

# 492 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
_bitarray_reserve(
 BitArray* self,
 bitarray_size_t new_size)
{
 if(!_bitarray_actually_needs_resize_bits(self, new_size))
  return 
# 497 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
        1
# 497 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
            ;

 bitarray_size_t alloc_size = _byte_size(new_size);
 if(!alloc_size)
  alloc_size = 1;

 uint8_t* new_data;
 if(self->data == ((void *)0))
  new_data = (uint8_t*) calloc(alloc_size, sizeof(uint8_t));
 else
  new_data = (uint8_t*) realloc(self->data, alloc_size*sizeof(uint8_t));
 if(new_data == ((void *)0))
 {
  free(self->data);
  _bitarray_set_err(self, BITARRAY_MEM_ERR_FLAG);
  return 
# 512 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
        0
# 512 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
             ;
 }

 bitarray_size_t n_bytes = _bitarray_num_bytes(self);

 __builtin___memset_chk (&new_data[n_bytes], 0, (alloc_size-n_bytes)*sizeof(uint8_t), __builtin_object_size (&new_data[n_bytes], 0));

 _bitarray_set_extra_bytes(self, alloc_size - n_bytes);
 self->data = new_data;
 return 
# 521 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
       1
# 521 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
           ;
}

static inline void
_bitarray_resize_quick(
 BitArray* self,
 bitarray_size_t new_size)
{
 uint8_t bit_spill = new_size & 0b111;
 size_t prev_real_bytes = _bitarray_real_num_bytes(self);
 bitarray_size_t num_bytes = (new_size) ? _byte_size(new_size) : 1;
 if(bit_spill)
 {
  uint8_t mask = ~((1 << (8-bit_spill)) - 1);
  self->data[num_bytes-1] &= mask;
 }
 _bitarray_set_size(self, new_size);
 size_t extra_bytes = prev_real_bytes - num_bytes;
 _bitarray_set_extra_bytes(self, extra_bytes);
 __builtin___memset_chk (&(self->data[num_bytes]), 0, extra_bytes*sizeof(uint8_t), __builtin_object_size (&(self->data[num_bytes]), 0));
}

static inline 
# 543 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
             _Bool

# 544 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
_bitarray_resize_and_reserve(
 BitArray* self,
 bitarray_size_t new_size)
{






 bitarray_size_t arr_size = _bitarray_size(self);
 size_t real_num_bits = _bitarray_real_num_bits(self);
 if(_bitarray_actually_needs_resize_bits(self, new_size))
 {
  bit_allocator_t alloc_size = _bitarray_get_alloc_size_bits(self);
  size_t new_real_size_bits = (new_size / alloc_size)*alloc_size;
  if(new_size % alloc_size)
   new_real_size_bits += alloc_size;
  if(!_bitarray_reserve(self, new_real_size_bits))
   return 
# 563 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
         0
# 563 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
              ;
  _bitarray_resize_quick(self, new_size);
 }
 else if(new_size != arr_size)
  _bitarray_resize_quick(self, new_size);
 return 
# 568 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h" 3 4
       1
# 568 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitarray.h"
           ;
}
# 25 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/mman.h" 1
# 229 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/mman.h"


int mlockall(int);
int munlockall(void);

int mlock(const void *, size_t);



void * mmap(void *, size_t, int, int, int, off_t) __asm("_" "mmap" );


int mprotect(void *, size_t, int) __asm("_" "mprotect" );

int msync(void *, size_t, int) __asm("_" "msync" );

int munlock(const void *, size_t);

int munmap(void *, size_t) __asm("_" "munmap" );

int shm_open(const char *, int, ...);
int shm_unlink(const char *);

int posix_madvise(void *, size_t, int);


int madvise(void *, size_t, int);
int mincore(const void *, size_t, char *);
int minherit(void *, size_t, int);




# 27 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 1
# 78 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_timespec.h" 1
# 33 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_timespec.h"
struct timespec
{
 __darwin_time_t tv_sec;
 long tv_nsec;
};
# 79 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2






# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_blkcnt_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_blkcnt_t.h"
typedef __darwin_blkcnt_t blkcnt_t;
# 86 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_blksize_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_blksize_t.h"
typedef __darwin_blksize_t blksize_t;
# 87 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ino_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ino_t.h"
typedef __darwin_ino_t ino_t;
# 89 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ino64_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_ino64_t.h"
typedef __darwin_ino64_t ino64_t;
# 92 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2



# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_nlink_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_nlink_t.h"
typedef __uint16_t nlink_t;
# 96 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_gid_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_gid_t.h"
typedef __darwin_gid_t gid_t;
# 98 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2

# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_time_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_time_t.h"
typedef __darwin_time_t time_t;
# 100 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2
# 110 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"
struct ostat {
 __uint16_t st_dev;
 ino_t st_ino;
 mode_t st_mode;
 nlink_t st_nlink;
 __uint16_t st_uid;
 __uint16_t st_gid;
 __uint16_t st_rdev;
 __int32_t st_size;
 struct timespec st_atimespec;
 struct timespec st_mtimespec;
 struct timespec st_ctimespec;
 __int32_t st_blksize;
 __int32_t st_blocks;
 __uint32_t st_flags;
 __uint32_t st_gen;
};
# 182 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"
struct stat { dev_t st_dev; mode_t st_mode; nlink_t st_nlink; __darwin_ino64_t st_ino; uid_t st_uid; gid_t st_gid; dev_t st_rdev; struct timespec st_atimespec; struct timespec st_mtimespec; struct timespec st_ctimespec; struct timespec st_birthtimespec; off_t st_size; blkcnt_t st_blocks; blksize_t st_blksize; __uint32_t st_flags; __uint32_t st_gen; __int32_t st_lspare; __int64_t st_qspare[2]; };
# 221 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"
struct stat64 { dev_t st_dev; mode_t st_mode; nlink_t st_nlink; __darwin_ino64_t st_ino; uid_t st_uid; gid_t st_gid; dev_t st_rdev; struct timespec st_atimespec; struct timespec st_mtimespec; struct timespec st_ctimespec; struct timespec st_birthtimespec; off_t st_size; blkcnt_t st_blocks; blksize_t st_blksize; __uint32_t st_flags; __uint32_t st_gen; __int32_t st_lspare; __int64_t st_qspare[2]; };
# 241 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_s_ifmt.h" 1
# 242 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2
# 378 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h"


int chmod(const char *, mode_t) __asm("_" "chmod" );
int fchmod(int, mode_t) __asm("_" "fchmod" );
int fstat(int, struct stat *) __asm("_" "fstat" "$INODE64");
int lstat(const char *, struct stat *) __asm("_" "lstat" "$INODE64");
int mkdir(const char *, mode_t);
int mkfifo(const char *, mode_t);
int stat(const char *, struct stat *) __asm("_" "stat" "$INODE64");
int mknod(const char *, mode_t, dev_t);
mode_t umask(mode_t);


int fchmodat(int, const char *, mode_t, int) ;
int fstatat(int, const char *, struct stat *, int) __asm("_" "fstatat" "$INODE64") ;
int mkdirat(int, const char *, mode_t) ;




int futimens(int __fd, const struct timespec __times[2]) ;
int utimensat(int __fd, const char *__path, const struct timespec __times[2],
    int __flag) ;




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_filesec_t.h" 1
# 30 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_filesec_t.h"
struct _filesec;
typedef struct _filesec *filesec_t;
# 406 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/stat.h" 2

int chflags(const char *, __uint32_t);
int chmodx_np(const char *, filesec_t);
int fchflags(int, __uint32_t);
int fchmodx_np(int, filesec_t);
int fstatx_np(int, struct stat *, filesec_t) __asm("_" "fstatx_np" "$INODE64");
int lchflags(const char *, __uint32_t) ;
int lchmod(const char *, mode_t) ;
int lstatx_np(const char *, struct stat *, filesec_t) __asm("_" "lstatx_np" "$INODE64");
int mkdirx_np(const char *, filesec_t);
int mkfifox_np(const char *, filesec_t);
int statx_np(const char *, struct stat *, filesec_t) __asm("_" "statx_np" "$INODE64");
int umaskx_np(filesec_t) ;



int fstatx64_np(int, struct stat64 *, filesec_t) ;
int lstatx64_np(const char *, struct stat64 *, filesec_t) ;
int statx64_np(const char *, struct stat64 *, filesec_t) ;
int fstat64(int, struct stat64 *) ;
int lstat64(const char *, struct stat64 *) ;
int stat64(const char *, struct stat64 *) ;




# 28 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/fcntl.h" 1
# 23 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/fcntl.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h" 1
# 116 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_o_sync.h" 1
# 117 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h" 2
# 143 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_o_dsync.h" 1
# 144 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h" 2
# 325 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_seek_set.h" 1
# 326 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h" 2
# 350 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
struct flock {
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
 short l_type;
 short l_whence;
};
# 365 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
struct flocktimeout {
 struct flock fl;
 struct timespec timeout;
};
# 378 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
struct radvisory {
 off_t ra_offset;
 int ra_count;
};
# 391 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
typedef struct fsignatures {
 off_t fs_file_start;
 void *fs_blob_start;
 size_t fs_blob_size;



 size_t fs_fsignatures_size;
 char fs_cdhash[20];
 int fs_hash_type;
} fsignatures_t;

typedef struct fsupplement {
 off_t fs_file_start;
 off_t fs_blob_start;
 size_t fs_blob_size;
 int fs_orig_fd;
} fsupplement_t;
# 422 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
typedef struct fchecklv {
 off_t lv_file_start;
 size_t lv_error_message_size;
 void *lv_error_message;
} fchecklv_t;
# 436 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
typedef struct fgetsigsinfo {
 off_t fg_file_start;
 int fg_info_request;
 int fg_sig_is_platform;
} fgetsigsinfo_t;
# 451 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
typedef struct fstore {
 unsigned int fst_flags;
 int fst_posmode;
 off_t fst_offset;
 off_t fst_length;
 off_t fst_bytesalloc;
} fstore_t;


typedef struct fpunchhole {
 unsigned int fp_flags;
 unsigned int reserved;
 off_t fp_offset;
 off_t fp_length;
} fpunchhole_t;


typedef struct ftrimactivefile {
 off_t fta_offset;
 off_t fta_length;
} ftrimactivefile_t;


typedef struct fspecread {
 unsigned int fsr_flags;
 unsigned int reserved;
 off_t fsr_offset;
 off_t fsr_length;
} fspecread_t;



typedef struct fbootstraptransfer {
 off_t fbt_offset;
 size_t fbt_length;
 void *fbt_buffer;
} fbootstraptransfer_t;
# 511 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
#pragma pack(4)

struct log2phys {
 unsigned int l2p_flags;
 off_t l2p_contigbytes;


 off_t l2p_devoffset;


};

#pragma pack()
# 536 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/fcntl.h"
typedef enum {
 FILESEC_OWNER = 1,
 FILESEC_GROUP = 2,
 FILESEC_UUID = 3,
 FILESEC_MODE = 4,
 FILESEC_ACL = 5,
 FILESEC_GRPUUID = 6,


 FILESEC_ACL_RAW = 100,
 FILESEC_ACL_ALLOCSIZE = 101
} filesec_property_t;






int open(const char *, int, ...) __asm("_" "open" );

int openat(int, const char *, int, ...) __asm("_" "openat" ) ;

int creat(const char *, mode_t) __asm("_" "creat" );
int fcntl(int, int, ...) __asm("_" "fcntl" );


int openx_np(const char *, int, filesec_t);




int open_dprotected_np( const char *, int, int, int, ...);
int flock(int, int);
filesec_t filesec_init(void);
filesec_t filesec_dup(filesec_t);
void filesec_free(filesec_t);
int filesec_get_property(filesec_t, filesec_property_t, void *);
int filesec_query_property(filesec_t, filesec_property_t, int *);
int filesec_set_property(filesec_t, filesec_property_t, const void *);
int filesec_unset_property(filesec_t, filesec_property_t) ;




# 24 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/fcntl.h" 2
# 29 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 1
# 72 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h" 1
# 84 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_posix_vdisable.h" 1
# 85 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h" 2
# 122 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_seek_set.h" 1
# 123 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h" 2
# 132 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h"
struct accessx_descriptor {
 unsigned int ad_name_offset;
 int ad_flags;
 int ad_pad[2];
};
# 185 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h"


int getattrlistbulk(int, void *, void *, size_t, uint64_t) ;
int getattrlistat(int, const char *, void *, void *, size_t, unsigned long) ;
int setattrlistat(int, const char *, void *, void *, size_t, uint32_t) ;


# 205 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/unistd.h"


int faccessat(int, const char *, int, int) ;
int fchownat(int, const char *, uid_t, gid_t, int) ;
int linkat(int, const char *, int, const char *, int) ;
ssize_t readlinkat(int, const char *, char *, size_t) ;
int symlinkat(const char *, int, const char *) ;
int unlinkat(int, const char *, int) ;


# 73 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 2
# 83 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_useconds_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_useconds_t.h"
typedef __darwin_useconds_t useconds_t;
# 84 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 2
# 429 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"

void _exit(int) __attribute__((__noreturn__));
int access(const char *, int);
unsigned int
  alarm(unsigned int);
int chdir(const char *);
int chown(const char *, uid_t, gid_t);

int close(int) __asm("_" "close" );

int dup(int);
int dup2(int, int);
int execl(const char * __path, const char * __arg0, ...) ;
int execle(const char * __path, const char * __arg0, ...) ;
int execlp(const char * __file, const char * __arg0, ...) ;
int execv(const char * __path, char * const * __argv) ;
int execve(const char * __file, char * const * __argv, char * const * __envp) ;
int execvp(const char * __file, char * const * __argv) ;
pid_t fork(void) ;
long fpathconf(int, int);
char *getcwd(char *, size_t);
gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);



int getgroups(int, gid_t []);

char *getlogin(void);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
int isatty(int);
int link(const char *, const char *);
off_t lseek(int, off_t, int);
long pathconf(const char *, int);

int pause(void) __asm("_" "pause" );

int pipe(int [2]);

ssize_t read(int, void *, size_t) __asm("_" "read" );

int rmdir(const char *);
int setgid(gid_t);
int setpgid(pid_t, pid_t);
pid_t setsid(void);
int setuid(uid_t);

unsigned int
  sleep(unsigned int) __asm("_" "sleep" );

long sysconf(int);
pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);
char *ttyname(int);


int ttyname_r(int, char *, size_t) __asm("_" "ttyname_r" );




int unlink(const char *);

ssize_t write(int __fd, const void * __buf, size_t __nbyte) __asm("_" "write" );

# 506 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"

size_t confstr(int, char *, size_t) __asm("_" "confstr" );

int getopt(int, char * const [], const char *) __asm("_" "getopt" );

extern char *optarg;
extern int optind, opterr, optopt;

# 532 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"






__attribute__((__deprecated__))

void *brk(const void *);
int chroot(const char *) ;


char *crypt(const char *, const char *);

void encrypt(char *, int) __asm("_" "encrypt" );



int fchdir(int);
long gethostid(void);
pid_t getpgid(pid_t);
pid_t getsid(pid_t);



int getdtablesize(void) ;
int getpagesize(void) __attribute__((__const__)) ;
char *getpass(const char *) ;




char *getwd(char *) ;


int lchown(const char *, uid_t, gid_t) __asm("_" "lchown" );

int lockf(int, int, off_t) __asm("_" "lockf" );

int nice(int) __asm("_" "nice" );

ssize_t pread(int __fd, void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pread" );

ssize_t pwrite(int __fd, const void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pwrite" );






__attribute__((__deprecated__))

void *sbrk(int);



pid_t setpgrp(void) __asm("_" "setpgrp" );




int setregid(gid_t, gid_t) __asm("_" "setregid" );

int setreuid(uid_t, uid_t) __asm("_" "setreuid" );

void swab(const void * restrict, void * restrict, ssize_t);
void sync(void);
int truncate(const char *, off_t);
useconds_t ualarm(useconds_t, useconds_t);
int usleep(useconds_t) __asm("_" "usleep" );
pid_t vfork(void) ;


int fsync(int) __asm("_" "fsync" );

int ftruncate(int, off_t);
int getlogin_r(char *, size_t);

# 620 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"

int fchown(int, uid_t, gid_t);
int gethostname(char *, size_t);
ssize_t readlink(const char * restrict, char * restrict, size_t);
int setegid(gid_t);
int seteuid(uid_t);
int symlink(const char *, const char *);








# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 1
# 75 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_def.h" 1
# 49 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_def.h"

typedef struct fd_set {
 __int32_t fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;

int __darwin_check_fd_set_overflow(int, const void *, int) ;


extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int
__darwin_check_fd_set(int _a, const void *_b)
{




 if ((uintptr_t)&__darwin_check_fd_set_overflow != (uintptr_t) 0) {



  return __darwin_check_fd_set_overflow(_a, _b, 0);

 } else {
  return 1;
 }



}


extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int
__darwin_fd_isset(int _fd, const struct fd_set *_p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  return _p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] & ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8))));
 }

 return 0;
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void
__darwin_fd_set(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] |= ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
}

extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) void
__darwin_fd_clr(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] &= ~((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
}
# 76 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 85 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_suseconds_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_suseconds_t.h"
typedef __darwin_suseconds_t suseconds_t;
# 86 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 100 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h"
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_setsize.h" 1
# 101 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_set.h" 1
# 102 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_clr.h" 1
# 103 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_isset.h" 1
# 104 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2
# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_zero.h" 1
# 105 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_fd_copy.h" 1
# 108 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2






int pselect(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, const struct timespec * restrict,
    const sigset_t * restrict)




__asm("_" "pselect" "$1050")




;


# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_select.h" 1
# 43 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_select.h"
int select(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, struct timeval * restrict)





__asm("_" "select" "$1050")




;
# 130 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/select.h" 2


# 636 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 2



# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uuid_t.h" 1
# 31 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_uuid_t.h"
typedef __darwin_uuid_t uuid_t;
# 640 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 2


void _Exit(int) __attribute__((__noreturn__));
int accessx_np(const struct accessx_descriptor *, size_t, int *, uid_t);
int acct(const char *);
int add_profil(char *, size_t, unsigned long, unsigned int) ;
void endusershell(void);
int execvP(const char * __file, const char * __searchpath, char * const * __argv) ;
char *fflagstostr(unsigned long);
int getdomainname(char *, int);
int getgrouplist(const char *, int, int *, int *);




# 1 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/gethostuuid.h" 1
# 39 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/gethostuuid.h"
int gethostuuid(uuid_t, const struct timespec *) ;
# 656 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h" 2




mode_t getmode(const void *, mode_t);
int getpeereid(int, uid_t *, gid_t *);
int getsgroups_np(int *, uuid_t);
char *getusershell(void);
int getwgroups_np(int *, uuid_t);
int initgroups(const char *, int);
int issetugid(void);
char *mkdtemp(char *);
int mknod(const char *, mode_t, dev_t);
int mkpath_np(const char *path, mode_t omode) ;
int mkpathat_np(int dfd, const char *path, mode_t omode)
 
  ;
int mkstemp(char *);
int mkstemps(char *, int);
char *mktemp(char *);
int mkostemp(char *path, int oflags)
 
  ;
int mkostemps(char *path, int slen, int oflags)
 
  ;

int mkstemp_dprotected_np(char *path, int dpclass, int dpflags)
 
  ;
char *mkdtempat_np(int dfd, char *path)
 
  ;
int mkstempsat_np(int dfd, char *path, int slen)
 
  ;
int mkostempsat_np(int dfd, char *path, int slen, int oflags)
 
  ;
int nfssvc(int, void *);
int profil(char *, size_t, unsigned long, unsigned int);

__attribute__((__deprecated__("Use of per-thread security contexts is error-prone and discouraged.")))
int pthread_setugid_np(uid_t, gid_t);
int pthread_getugid_np( uid_t *, gid_t *);

int reboot(int);
int revoke(const char *);

__attribute__((__deprecated__)) int rcmd(char **, int, const char *, const char *, const char *, int *);
__attribute__((__deprecated__)) int rcmd_af(char **, int, const char *, const char *, const char *, int *,
  int);
__attribute__((__deprecated__)) int rresvport(int *);
__attribute__((__deprecated__)) int rresvport_af(int *, int);
__attribute__((__deprecated__)) int iruserok(unsigned long, int, const char *, const char *);
__attribute__((__deprecated__)) int iruserok_sa(const void *, int, int, const char *, const char *);
__attribute__((__deprecated__)) int ruserok(const char *, int, const char *, const char *);

int setdomainname(const char *, int);
int setgroups(int, const gid_t *);
void sethostid(long);
int sethostname(const char *, int);

void setkey(const char *) __asm("_" "setkey" );



int setlogin(const char *);
void *setmode(const char *) __asm("_" "setmode" );
int setrgid(gid_t);
int setruid(uid_t);
int setsgroups_np(int, const uuid_t);
void setusershell(void);
int setwgroups_np(int, const uuid_t);
int strtofflags(char **, unsigned long *, unsigned long *);
int swapon(const char *);
int ttyslot(void);
int undelete(const char *);
int unwhiteout(const char *);
void *valloc(size_t);






int syscall(int, ...);

extern char *suboptarg;
int getsubopt(char **, char * const *, char **);



int fgetattrlist(int,void*,void*,size_t,unsigned int) ;
int fsetattrlist(int,void*,void*,size_t,unsigned int) ;
int getattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "getattrlist" );
int setattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "setattrlist" );
int exchangedata(const char*,const char*,unsigned int) ;
int getdirentriesattr(int,void*,void*,size_t,unsigned int*,unsigned int*,unsigned int*,unsigned int) ;
# 769 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/unistd.h"
struct fssearchblock;
struct searchstate;

int searchfs(const char *, struct fssearchblock *, unsigned long *, unsigned int, unsigned int, struct searchstate *) ;
int fsctl(const char *,unsigned long,void*,unsigned int);
int ffsctl(int,unsigned long,void*,unsigned int) ;




int fsync_volume_np(int, int) ;
int sync_volume_np(const char *, int) ;

extern int optreset;


# 30 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 2




extern const uint8_t BITBUFFER_WRITE;
extern const uint8_t BITBUFFER_OPENED;
extern const uint8_t BITBUFFER_IS_MMAP;
extern const uint8_t BITBUFFER_EOF;
extern const uint8_t BITBUFFER_ILL_ERR;
extern const uint8_t BITBUFFER_MEM_ERR;
extern const uint8_t BITBUFFER_MASK_ERR;

extern const uint8_t BYTE_ALIGN_FLOOR;
extern const uint8_t BYTE_ALIGN_CEIL;

typedef struct BField BField;

struct BField
{
    uint16_t flags;
    uint16_t flags2;
    uint32_t size;
    union
    {
        void* raw;
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        size_t zu;
        uint8_t* u8_ptr;
        uint16_t* u16_ptr;
        uint32_t* u32_ptr;
        uint64_t* u64_ptr;
        size_t* zu_ptr;
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        int8_t* i8_ptr;
        int16_t* i16_ptr;
        int32_t* i32_ptr;
        int64_t* i64_ptr;
        char istr[8];
        unsigned char ustr[8];
        BField* bf_ptr;
        BitArray* bits;

    };
};

typedef BField BitReceiver[];

typedef struct BitBuffer
{
 uint8_t flags;
    size_t pos;
    union
    {
        struct
        {
            int file_no;
         struct stat file_info;
        };
        BitArray* source;
    };

    uint8_t *buffer;
} BitBuffer;


typedef struct _ReadTarget
{
    uint8_t readSize;
    union
    {
        void* raw;
        uint8_t* t8;
        uint16_t* t16;
        uint32_t* t32;
        uint64_t* t64;
    };
} ReadTarget;

typedef ReadTarget ReadSequence[];

static inline void bitbuffer_set_flag(BitBuffer* self, uint8_t flag)
{
    self->flags |= flag;
}

static inline void bitbuffer_set_err(BitBuffer* self, uint8_t err)
{
    self->flags |= err;
}

static inline 
# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
             _Bool 
# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                  bitbuffer_check_flag(BitBuffer* self, uint8_t flag)
{
    return self->flags & flag;
}

static inline 
# 131 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
             _Bool 
# 131 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                  bitbuffer_check_err(BitBuffer* self, uint8_t err)
{
    return self->flags & err;
}

static inline 
# 136 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
             _Bool 
# 136 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                  bitbuffer_check_status(BitBuffer* self)
{
    return !(self->flags & BITBUFFER_MASK_ERR);
}

static inline void bitbuffer_unset_flag(BitBuffer* self, uint8_t flag)
{
    self->flags &= ~flag;
}

static inline void bitbuffer_clear_err(BitBuffer* self, uint8_t err)
{
    self->flags &= ~err;
}

static inline size_t bitbuffer_num_bytes(BitBuffer* self)
{
    if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP))
     return self->file_info.st_size;
    else
        return _bitarray_num_bytes(self->source);
}

static inline size_t bitbuffer_size(BitBuffer* self)
{
    if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP))
     return (self->file_info.st_size << 3);
    else
        return _bitarray_size(self->source);
}

static inline 
# 167 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
             _Bool 
# 167 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                  bitbuffer_aligned(BitBuffer* self)
{
    return !(self->pos & 0b111);
}


# 172 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 172 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_align(BitBuffer* self, uint8_t align);


static inline 
# 175 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
             _Bool 
# 175 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                  bitbuffer_incr_pos(BitBuffer* self, long long int i);

uint8_t bitbuffer_get_byte(BitBuffer* self, size_t i);


# 179 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 179 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_get_bit(BitBuffer* self, size_t i);


# 181 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 181 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_seek(BitBuffer* self, long long int i, int whence);


# 183 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 183 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_seek_byte(BitBuffer* self, long long int i, int whence);


# 185 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 185 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_skip(BitBuffer* self, long long int i);


# 187 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 187 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_skip_bytes(BitBuffer* self, long long int i);

char bitbuffer_read_char(BitBuffer* self);

uint8_t bitbuffer_read_byte(BitBuffer* self);


# 193 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 193 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_read_bit(BitBuffer* self);

uint16_t bitbuffer_read_uint16(BitBuffer* self);

uint32_t bitbuffer_read_uint32(BitBuffer* self);

uint64_t bitbuffer_read_uint64(BitBuffer* self);

size_t bitbuffer_read(BitBuffer* self, size_t num, 
# 201 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
                                                  _Bool 
# 201 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                                                       little_endian);


# 203 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 203 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_read_fourcc(BitBuffer* self, char* dest);


# 205 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 205 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_peek_fourcc(BitBuffer* self, char* dest);


# 207 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 207 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_read_bytes(BitBuffer* self, char* dest, size_t len);

BitBuffer* new_BitBuffer_from_file(const char *path, 
# 209 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
                                                    _Bool 
# 209 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
                                                         write);

BitBuffer* new_BitBuffer_from_BitArray(BitArray* source);

size_t bitbuffer_unpack(BitBuffer* self, const char* fmt, BitReceiver dst, size_t size);

void bitbuffer_read_into(BitBuffer* self, int size, ReadTarget sequence[]);

void bitbuffer_read_into_uint32(BitBuffer* self, int size, uint32_t* sequence[]);


# 219 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h" 3 4
_Bool 
# 219 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.h"
    bitbuffer_flush(BitBuffer* self);

void bitbuffer_close(BitBuffer* self);

void del_BitBuffer(BitBuffer* self);
# 2 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 2




const uint8_t BITBUFFER_WRITE = 0b00000001;
const uint8_t BITBUFFER_OPENED = 0b00000010;
const uint8_t BITBUFFER_IS_MMAP = 0b00001000;
const uint8_t BITBUFFER_EOF = 0b00100000;
const uint8_t BITBUFFER_ILL_ERR = 0b01000000;
const uint8_t BITBUFFER_MEM_ERR = 0b10000000;
const uint8_t BITBUFFER_MASK_ERR = 0b11100000;

const uint8_t BYTE_ALIGN_FLOOR = 1;
const uint8_t BYTE_ALIGN_CEIL = 2;


# 17 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 17 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_align(BitBuffer* self, uint8_t align)
{




    if(bitbuffer_aligned(self))
        return 
# 24 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              1
# 24 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                  ;
    switch(align)
    {
        default:
        case 1:
            self->pos &= ~((size_t)0b111);
            return 
# 30 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                  1
# 30 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                      ;
        case 2:
            self->pos = (self->pos & ~((size_t)0b111)) + 8;
            if(self->pos >= bitbuffer_size(self))
            {
                bitbuffer_set_err(self, BITBUFFER_EOF);
                return 
# 36 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                      0
# 36 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                           ;
            }
            return 
# 38 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                  1
# 38 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                      ;
    }
}


static inline 
# 43 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
             _Bool 
# 43 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                  bitbuffer_incr_pos(BitBuffer* self, long long int i)
{
    self->pos += i;
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 50 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 50 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    return 
# 52 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 52 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}

uint8_t bitbuffer_get_byte(BitBuffer* self, size_t i)
{
 if(i >= bitbuffer_num_bytes(self))
    {
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
        return -1;
    }
    return self->buffer[i];
}


# 65 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 65 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_get_bit(BitBuffer* self, size_t i)
{
 if(i >= bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
        return -1;
    }
    return self->buffer[i >> 3] & (1 << (i & 0b111));
}


# 75 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 75 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_seek(BitBuffer* self, long long int i, int whence)
{
    switch(whence)
    {
        case 1:
            self->pos += i;
            break;
        case 0:
            self->pos = i;
            break;
        case 2:
            self->pos = bitbuffer_size(self) + i;
    }
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 92 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 92 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    return 
# 94 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 94 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}


# 97 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 97 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_seek_byte(BitBuffer* self, long long int i, int whence)
{
    switch(whence)
    {
        case 1:
            self->pos += (i<<3);
            break;
        case 0:
            self->pos = (i<<3);
            break;
        case 2:
            self->pos = bitbuffer_num_bytes(self) + i;
    }
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 114 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 114 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    return 
# 116 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 116 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}


# 119 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 119 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_skip(BitBuffer* self, long long int i)
{
    self->pos += i;
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    return 
# 128 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 128 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}


# 131 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 131 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_skip_bytes(BitBuffer* self, long long int i)
{
    self->pos += (i<<3);
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 138 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 138 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    return 
# 140 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 140 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}

char bitbuffer_read_char(BitBuffer* self)
{
    if(self->flags & BITBUFFER_EOF)
        return -1;

    char c = self->buffer[self->pos >> 3];
    self->pos += 8;

    if(self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);

    return c;
}

uint8_t bitbuffer_read_byte(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return -1;

    uint8_t c = self->buffer[self->pos >> 3];
    self->pos += 8;

    if(self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);

    return c;
}


# 171 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 171 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_read_bit(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return -1;

    
# 176 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
   _Bool 
# 176 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
        bit = self->buffer[self->pos >> 3] &
        (1 << (7-(self->pos & 0b111)));

    if(++self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);

    return bit;
}

uint16_t bitbuffer_read_uint16(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 188 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 188 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 190 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 190 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(self->pos + 16 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 194 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 194 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    uint16_t val;
    __builtin___memcpy_chk (&val, &(self->buffer[self->pos >> 3]), 2, __builtin_object_size (&val, 0));
    self->pos +=16;
    return val;
}

uint32_t bitbuffer_read_uint32(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 205 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 205 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 207 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 207 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(self->pos + 32 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 211 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 211 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    uint32_t val;
    __builtin___memcpy_chk (&val, &(self->buffer[self->pos >> 3]), 4, __builtin_object_size (&val, 0));
    self->pos +=32;
    return val;
}

uint64_t bitbuffer_read_uint64(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 222 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 222 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 224 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 224 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(self->pos + 64 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 228 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 228 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    uint64_t val;
    __builtin___memcpy_chk (&val, &(self->buffer[self->pos >> 3]), 8, __builtin_object_size (&val, 0));
    self->pos += 64;
    return val;
}

size_t bitbuffer_read(BitBuffer* self, size_t num, 
# 236 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                                                  _Bool 
# 236 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                                                       little_endian)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 239 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 239 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    else if(self->pos + num > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return 
# 243 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 243 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }


    size_t val = 0;
    size_t byte_pos = self->pos >> 3;
    size_t bit_curr;

    if(little_endian)
    {
        size_t bit_max = (((size_t) (1))) << (num-1);
        size_t bit_pos = 0;
        size_t bit_pos_max = num;
        bit_curr = 1;
        while((self->pos & 0b111) && (bit_curr < bit_max))
        {
            if( self->buffer[byte_pos] & (((size_t) (1)) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr <<= 1;
            bit_pos++;
        }
        while(bit_pos_max - bit_pos >= 8)
        {
            val |= ( ((size_t) (self->buffer[self->pos >> 3])) ) << bit_pos;
            bit_pos += 8;
            bit_curr <<= 8;
            self->pos += 8;
        }
        byte_pos = self->pos >> 3;
        while(bit_pos < bit_pos_max)
        {
            if( self->buffer[byte_pos] & (((size_t) (1)) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr <<= 1;
            bit_pos++;
        }
    }
    else
    {
        bit_curr = (((size_t) (1))) << (num-1);
        while((self->pos & 0b111) && bit_curr)
        {
            if( self->buffer[byte_pos] & (((size_t) (1)) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr >>= 1;
            num--;
        }
        while(bit_curr >= 128)
        {
            num -= 8;
            val |= ( ((size_t) (self->buffer[self->pos >> 3])) ) << num;
            bit_curr >>= 8;
            self->pos += 8;
        }
        byte_pos = self->pos >> 3;
        while(bit_curr)
        {
            if( self->buffer[byte_pos] & ( ((size_t) (1)) << (7-(self->pos++ & 0b111))) )
                    val |= bit_curr;
                bit_curr >>= 1;
        }
    }

    return val;



}


# 312 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 312 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_read_fourcc(BitBuffer* self, char* dest)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 315 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 315 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 317 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 317 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    else if(self->pos + 32 > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), q, __builtin_object_size (dest, 0));
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        return 
# 325 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 325 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    else
    {
        __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), 4, __builtin_object_size (dest, 0));
        dest[4] = '\0';
        self->pos += 32;
        return 
# 332 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              1
# 332 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                  ;
    }
}


# 336 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 336 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_peek_fourcc(BitBuffer* self, char* dest)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 339 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 339 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 341 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 341 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    else if(self->pos + 32 > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), q, __builtin_object_size (dest, 0));
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        return 
# 348 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 348 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    else
    {
        __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), 4, __builtin_object_size (dest, 0));
        dest[4] = '\0';
        return 
# 354 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              1
# 354 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                  ;
    }
}


# 358 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool

# 359 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
bitbuffer_read_bytes(BitBuffer* self, char* dest, size_t len)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return 
# 362 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 362 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(!bitbuffer_align(self, 2))
        return 
# 364 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 364 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    if(self->pos + (len << 3) > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), q, __builtin_object_size (dest, 0));
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        self->pos = bitbuffer_size(self);
        return 
# 372 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
              0
# 372 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                   ;
    }
    __builtin___memcpy_chk (dest, &(self->buffer[self->pos >> 3]), len, __builtin_object_size (dest, 0));
    dest[len] = '\0';
    self->pos += (len << 3);
    return 
# 377 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 377 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}


# 380 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool

# 381 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
bitbuffer_read_fmt(const char *format, ...)
{
    va_list args;
    
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
   __builtin_va_start(
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
   args
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
   ,
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
   format
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
   )
# 384 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                         ;

    while(*format != '\0')
    {
        if(*format != '%')
        {
            
# 390 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
           __builtin_va_end(
# 390 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
           args
# 390 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
           )
# 390 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                       ;
            return 
# 391 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                  0
# 391 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                       ;
        }
        format++;
        switch(*format)
        {

        }
    }
    return 
# 399 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
          1
# 399 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
              ;
}
# 436 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
const uint16_t INTEGRAL_TYPE = 0b1000000000000000;
const uint16_t LITTLE_END_TYPE = 0b0100000000000000;
const uint16_t ENV_TYPE = 0b0010000000000000;
const uint16_t REF_TYPE = 0b0001000000000000;
const uint16_t ARRAY_TYPE = 0b0000100000000000;
const uint16_t SKIP_TYPE = 0b0000010000000000;
const uint16_t SIZE_USES_ENV = 0b0000001000000000;
const uint16_t SIZE_USES_REF = 0b0000000100000000;
const uint16_t BITARRAY_TYPE = 0b0000000000001000;

static uint8_t UNPACK_MAPPINGS[257] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 
# 446 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                                                        0 
# 446 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                                                              };
static uint8_t UNPACK_BRACES[257] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 , 
# 447 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                                                        0 
# 447 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                                                              };
const uint8_t IS_WHITESPACE = 0b00000001;
const uint8_t IS_BRACE = 0b00000010;
# 459 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
static inline void
_bitbuffer_init_mappings()
{
    UNPACK_MAPPINGS[256] = 
# 462 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                          1
# 462 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                              ;
    UNPACK_MAPPINGS[(uint8_t) ('[')] |= (IS_BRACE);
    UNPACK_MAPPINGS[(uint8_t) ('(')] |= (IS_BRACE);
    UNPACK_MAPPINGS[(uint8_t) ('<')] |= (IS_BRACE);
    UNPACK_MAPPINGS[(uint8_t) ('{')] |= (IS_BRACE);
    UNPACK_BRACES[(uint8_t) ('[')] = (']');
    UNPACK_BRACES[(uint8_t) ('(')] = (')');
    UNPACK_BRACES[(uint8_t) ('<')] = ('>');
    UNPACK_BRACES[(uint8_t) ('{')] = ('}');
    UNPACK_MAPPINGS[(uint8_t) (' ')] |= (IS_WHITESPACE);
    UNPACK_MAPPINGS[(uint8_t) (',')] |= (IS_WHITESPACE);
    UNPACK_MAPPINGS[(uint8_t) ('\t')] |= (IS_WHITESPACE);
    UNPACK_MAPPINGS[(uint8_t) ('\n')] |= (IS_WHITESPACE);
}

size_t
bitbuffer_unpack(
    BitBuffer* self,
    const char* fmt,
    BitReceiver dst,
    size_t num)
{
    if(!UNPACK_MAPPINGS[256])
        _bitbuffer_init_mappings();

    char temp_str[100];
    BField env[100];
    BField* target;
    size_t env_curr = 0;
    uint16_t flags;
    size_t size;
    size_t array_size;
    uint8_t multiple;
    size_t array_max;
    char c;
    int i = 0;
    int j;
    while( (c = *(fmt++)) && i <= num && bitbuffer_check_status(self) )
    {
        dst[i].zu = (size_t) 0;
        target = &(dst[i]);
        flags = 0;
        size = 0;
        array_size = 0;
        while( ( (UNPACK_MAPPINGS)[(uint8_t) (c)] & (IS_WHITESPACE) ) )
            if( !((c) = *((fmt))++) ) return i;
        if(c != '%') return i;
        env_type:
        if( !((c) = *((fmt))++) ) return i;
        switch(c)
        {
            case 'z':
                if( ((c) = *((fmt))++) != ('u') ) return i;
                size = 64;
                flags |= (INTEGRAL_TYPE);
                goto check_modifiers;
            case 'u':
            case 'i':
                flags |= (INTEGRAL_TYPE);
                goto integral_type;
            case '$':
                if(( (flags) & (ENV_TYPE) ))
                        return i;
                flags |= (ENV_TYPE);
                target = &(env[env_curr++]);
                goto env_type;
            case '!':
                flags |= (SKIP_TYPE);
                if( ((c) = *((fmt))++) != ('[') ) return i;
                goto parse_array_type;
            default:
                return i;
        }

        integral_type:
        if( !((c) = *((fmt))++) ) return i;
        switch(c)
        {
            case '8':
                size = 8;
                goto check_modifiers;
            case '1':
                if( ((c) = *((fmt))++) != ('6') ) return i;
                size = 16;
                goto check_modifiers;
            case '3':
                if( ((c) = *((fmt))++) != ('2') ) return i;
                size = 32;
                goto check_modifiers;
            case '6':
                if( ((c) = *((fmt))++) != ('4') ) return i;
                size = 64;
                goto check_modifiers;
            default:
                return i;
        }

        check_modifiers:
        switch(*(fmt+1))
        {
            case '%':
            case '\0':
                goto parse_integral_type;
            case '[':
                if( !((c) = *((fmt))++) ) return i;
                goto parse_array_type;
            default:
                return i;
        }

        parse_integral_type:
        switch(size)
        {
            case 8:
                target->u8 = bitbuffer_read(self, 8, ((flags) & LITTLE_END_TYPE ));
                break;
            case 16:
                target->u16 = bitbuffer_read(self, 16, ((flags) & LITTLE_END_TYPE ));
                break;
            case 32:
                target->u32 = bitbuffer_read(self, 32, ((flags) & LITTLE_END_TYPE ));
                break;
            case 64:
                target->u64 = bitbuffer_read(self, 64, ((flags) & LITTLE_END_TYPE ));
                break;
            default:
                return i;
        }
        if(( (flags) & (ENV_TYPE) ))
        {
            i += (0); continue;
        }
        else
        {
            i += (1); continue;
        }

        parse_array_type:
        if(!( (flags) & (INTEGRAL_TYPE) ))
            return i;
        flags |= (ARRAY_TYPE);
        if(*(fmt+1) == '$')
        {
            flags |= (SIZE_USES_ENV);
            fmt++;
        }
        else if(*(fmt+1) == '&')
        {
            flags |= (SIZE_USES_REF);
            fmt++;
        }
        for (j=0;
             j<100 && c != ']';
             j++, c = *(fmt++))
        {
            if(!c) return i;
            else temp_str[j] = c;
        }
        temp_str[j] = '\0';
        array_size = atoi(temp_str);
        j = 0;

        switch(((flags) & 0b1100000000))
        {
            case 0b1000000000:
                if( ! ( (flags) & (SKIP_TYPE) )
                    && array_size >= env_curr )
                {
                    dst[i].raw = ((void *)0);
                    return i;
                }
                else array_size = env[array_size].zu;
                goto read_into_array;
            case 0b0100000000:
                if( ! ( (flags) & (SKIP_TYPE) )
                    && array_size >= num )
                {
                    dst[i].raw = ((void *)0);
                    return i;
                }
                else array_size = dst[array_size].zu;
                goto read_into_array;
            case 0:
                goto read_into_array;
            default:
                dst[i].raw = ((void *)0);
                return i;
        }

        read_into_array:
        if(( (flags) & (SKIP_TYPE) ))
        {
            bitbuffer_skip(self, array_size);
            i += (0); continue;
        }
        dst[i].size = array_size;
        multiple = size >> 3;
        array_max = array_size * multiple;
        dst[i].raw =
            calloc(dst[i].size, multiple);
        if(dst[i].raw == ((void *)0))
            return i;
        for(size_t ii=0; ii < array_max; ii++)
            dst[i].u8_ptr[ii] =
                    bitbuffer_read(self, 8, 
# 666 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                                           0
# 666 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                                                );
        i++;
    }
    return i;
}

void
bitbuffer_read_into(BitBuffer* self, int size, ReadSequence sequence)
{
    ReadTarget* t;
    for(int i=0; i<size; i++)
    {
        t = &(sequence[i]);
        switch(t->readSize)
        {
            case 1:
                *(t->t8) = bitbuffer_read_byte(self);
                break;
            case 2:
                *(t->t16) = bitbuffer_read_uint16(self);
                break;
            case 4:
                *(t->t32) = bitbuffer_read_uint32(self);
                break;
            case 8:
                *(t->t64) = bitbuffer_read_uint64(self);
                break;
            default:
                break;
        }
    }
}

void
bitbuffer_read_into_uint32(BitBuffer* self, int size, uint32_t* sequence[])
{
    for(int i=0; i<size; i++)
        *(sequence[i]) = bitbuffer_read_uint32(self);
}

BitBuffer* new_BitBuffer_from_file(const char *path, 
# 706 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
                                                    _Bool 
# 706 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
                                                         write)
{
 int file_no;
 if(write)
  file_no = open(path, 0x0002, 0000400 | 0000200);
 else
  file_no = open(path, 0x0000, 0000400);
 BitBuffer* obj = (BitBuffer*) malloc(sizeof(BitBuffer));
 if(obj == ((void *)0))
 {
  close(file_no);
  return ((void *)0);
 }
    obj->flags = 0;
 if(fstat(file_no, &(obj->file_info)) == -1)
 {
  free(obj);
  close(file_no);
  return ((void *)0);
 }
 obj->file_no = file_no;
 if(write)
 {
  obj->buffer = mmap(((void *)0), obj->file_info.st_size,
   0x01 | 0x02, 0x0001, obj->file_no, 0);
  obj->flags = 1;
 }
 else
  obj->buffer = mmap(((void *)0), obj->file_info.st_size,
   0x01, 0x0002, obj->file_no, 0);
 if(obj->buffer == ((void *)-1))
 {
  free(obj);
  close(file_no);
  return ((void *)0);
 }
    bitbuffer_set_flag(obj, BITBUFFER_OPENED);
    bitbuffer_set_flag(obj, BITBUFFER_IS_MMAP);
    obj->pos = 0;
 return obj;
}

BitBuffer* new_BitBuffer_from_BitArray(BitArray* source)
{
    BitBuffer* obj = (BitBuffer*) malloc(sizeof(BitBuffer));
 if(obj == ((void *)0))
        return ((void *)0);
    obj->flags = 0;
    obj->source = source;
    obj->pos = 0;
    obj->buffer = (char *) source->data;
    return obj;
}


# 760 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
_Bool 
# 760 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
    bitbuffer_flush(BitBuffer* self)
{
 if(!bitbuffer_check_flag(self, BITBUFFER_IS_MMAP) ||
       !(self->flags & 1))
  return 
# 764 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
        0
# 764 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
             ;
 else if(msync(self->buffer, self->file_info.st_size, 0x0010) == -1)
  return 
# 766 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
        0
# 766 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
             ;
 else
  return 
# 768 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c" 3 4
        1
# 768 "/Users/theofabilous/Documents/GitHub/bitarray/src/bitbuffer.c"
            ;
}

void bitbuffer_close(BitBuffer* self)
{
 if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP) &&
       bitbuffer_check_flag(self, BITBUFFER_OPENED))
 {
  munmap(self->buffer, self->file_info.st_size);
  close(self->file_no);
  bitbuffer_unset_flag(self, BITBUFFER_OPENED);
 }
}

void del_BitBuffer(BitBuffer* self)
{
 bitbuffer_close(self);
    if(self != ((void *)0))
     free(self);
}
