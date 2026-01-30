#ifndef BASE_H
#define BASE_H

#include <stdint.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

/* assert an expression and output the file and the line */

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define test(expr) \
    do \
    { \
        if ((expr) != 0) \
        { \
            write(STDERR_FILENO, " [FAILED] in ", 13); \
            write(STDERR_FILENO, __FILE__, 50); \
            write(STDERR_FILENO, __func__, 50); \
            write(STDERR_FILENO, "\n", 1); \
            _exit(1); \
        } \
        else \
        { \
            write(STDOUT_FILENO, "[PASSED] ", 9); \
            write(STDERR_FILENO, __FILE__, 50); \
            write(STDOUT_FILENO, __func__, 50); \
            write(STDOUT_FILENO, "\n", 1); \
        } \
    } while (0)

#define check(expr) \
    if ((expr) != 0) \
    { \
        write(STDERR_FILENO, RED " [ERROR] in ", 12); \
        write(STDERR_FILENO, __func__, 50); \
        write(STDERR_FILENO, RESET "\n", 1); \
    }

#define internal static
#define global_variable static
#define local_persist static

#define ERR_OK 0
#define ERR_IO 1
#define ERR_PARSE 2
#define ERR_PERM 3
#define ERR_INVALID 4

#define KiB(n) (((u64)(n)) << 10)
#define MiB(n) (((u64)(n)) << 20)
#define GiB(n) (((u64)(n)) << 30)

#define unused(x) (void)(x)

#define PATH_MAX_LEN 128
#define BUFF_SMALL 128
#define BUFF_DEFAULT 256
#define BUFF_LARGE 512

#define DEPRECATED __attribute__((__deprecated__))

#if defined(__arm__) || defined(__aarch64__)
#define breakpoint() __asm__ volatile("brk #0");
#elif defined(__i386__) || defined(__x86_64__)
#define breakpoint() __asm__ volatile("int3");
#endif

#define MemCpy(dest, src, len) memcpy((dest), (src), (len))
#define MemSet(dest, len) memset((dest), (0), (len))

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef i8 s8;

typedef float  f32;
typedef double f64;

typedef i32 b32;
typedef i16 b16;
typedef u8  b8;

typedef uintptr_t umm;
typedef intptr_t  smm;

#define TRUE (0 == 0)
#define FALSE (0 != 0)

#endif
