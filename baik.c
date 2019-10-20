#include "baik.h"
#ifndef BAIK_EM_COMMON_PLATFORM_H_
#define BAIK_EM_COMMON_PLATFORM_H_

#define BAIK_EM_P_CUSTOM 0
#define BAIK_EM_P_UNIX 1
#define BAIK_EM_P_WINDOWS 2
#define BAIK_EM_P_ESP32 15
#define BAIK_EM_P_ESP8266 3
#define BAIK_EM_P_CC3100 6
#define BAIK_EM_P_CC3200 4
#define BAIK_EM_P_CC3220 17
#define BAIK_EM_P_MSP432 5
#define BAIK_EM_P_TM4C129 14
#define BAIK_EM_P_MBED 7
#define BAIK_EM_P_WINCE 8
#define BAIK_EM_P_NXP_LPC 13
#define BAIK_EM_P_NXP_KINETIS 9
#define BAIK_EM_P_NRF51 12
#define BAIK_EM_P_NRF52 10
#define BAIK_EM_P_PIC32 11
#define BAIK_EM_P_RS14100 18
#define BAIK_EM_P_STM32 16

#ifndef BAIK_EM_PLATFORM

#if defined(TARGET_IS_MSP432P4XX) || defined(__MSP432P401R__)
#define BAIK_EM_PLATFORM BAIK_EM_P_MSP432
#elif defined(cc3200) || defined(TARGET_IS_CC3200)
#define BAIK_EM_PLATFORM BAIK_EM_P_CC3200
#elif defined(cc3220) || defined(TARGET_IS_CC3220)
#define BAIK_EM_PLATFORM BAIK_EM_P_CC3220
#elif defined(__unix__) || defined(__APPLE__)
#define BAIK_EM_PLATFORM BAIK_EM_P_UNIX
#elif defined(WINCE)
#define BAIK_EM_PLATFORM BAIK_EM_P_WINCE
#elif defined(_WIN32)
#define BAIK_EM_PLATFORM BAIK_EM_P_WINDOWS
#elif defined(__MBED__)
#define BAIK_EM_PLATFORM BAIK_EM_P_MBED
#elif defined(__USE_LPCOPEN)
#define BAIK_EM_PLATFORM BAIK_EM_P_NXP_LPC
#elif defined(FRDM_K64F) || defined(FREEDOM)
#define BAIK_EM_PLATFORM BAIK_EM_P_NXP_KINETIS
#elif defined(PIC32)
#define BAIK_EM_PLATFORM BAIK_EM_P_PIC32
#elif defined(ESP_PLATFORM)
#define BAIK_EM_PLATFORM BAIK_EM_P_ESP32
#elif defined(ICACHE_FLASH)
#define BAIK_EM_PLATFORM BAIK_EM_P_ESP8266
#elif defined(TARGET_IS_TM4C129_RA0) || defined(TARGET_IS_TM4C129_RA1) || \
    defined(TARGET_IS_TM4C129_RA2)
#define BAIK_EM_PLATFORM BAIK_EM_P_TM4C129
#elif defined(RS14100)
#define BAIK_EM_PLATFORM BAIK_EM_P_RS14100
#elif defined(STM32)
#define BAIK_EM_PLATFORM BAIK_EM_P_STM32
#endif

#ifndef BAIK_EM_PLATFORM
#error "BAIK_EM_PLATFORM is not specified and we couldn't guess it."
#endif

#endif

#define GENERIC_NET_IF_SOCKET 1
#define GENERIC_NET_IF_SIMPLELINK 2
#define GENERIC_NET_IF_LWIP_LOW_LEVEL 3
#define GENERIC_NET_IF_PIC32 4
#define GENERIC_NET_IF_NULL 5

#define GENERIC_SSL_IF_OPENSSL 1
#define GENERIC_SSL_IF_MBEDTLS 2
#define GENERIC_SSL_IF_SIMPLELINK 3

#if BAIK_EM_PLATFORM == BAIK_EM_P_CUSTOM
#include <platform_custom.h>
#endif

#if !defined(PRINTF_LIKE)
#if defined(__GNUC__) || defined(__clang__) || defined(__TI_COMPILER_VERSION__)
#define PRINTF_LIKE(f, a) __attribute__((format(printf, f, a)))
#else
#define PRINTF_LIKE(f, a)
#endif
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__clang__) || \
     defined(__TI_COMPILER_VERSION__)) &&       \
    !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#define NOINLINE __attribute__((noinline))
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#define NOINSTR __attribute__((no_instrument_function))
#define DO_NOT_WARN_UNUSED __attribute__((unused))
#else
#define NORETURN
#define NOINLINE
#define WARN_UNUSED_RESULT
#define NOINSTR
#define DO_NOT_WARN_UNUSED
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif

#endif
#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_WINDOWS_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_WINDOWS


#ifdef _MSC_VER
#pragma warning(disable : 4127)
#pragma warning(disable : 4204)
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <direct.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#if _MSC_VER < 1700
typedef int bool;
#else
#include <stdbool.h>
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1800
#define strdup _strdup
#endif

#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif
#ifndef __func__
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
#endif
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define to64(x) _atoi64(x)
#if !defined(__MINGW32__) && !defined(__MINGW64__)
#define popen(x, y) _popen((x), (y))
#define pclose(x) _pclose(x)
#define fileno _fileno
#endif
#if defined(_MSC_VER) && _MSC_VER >= 1400
#define fseeko(x, y, z) _fseeki64((x), (y), (z))
#else
#define fseeko(x, y, z) fseek((x), (y), (z))
#endif
#if defined(_MSC_VER) && _MSC_VER <= 1200
typedef unsigned long uintptr_t;
typedef long intptr_t;
#endif
typedef int socklen_t;
#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef SOCKET sock_t;
typedef uint32_t in_addr_t;
#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif
#ifndef UINT32_MAX
#define UINT32_MAX 4294967295
#endif
#ifndef pid_t
#define pid_t HANDLE
#endif
#define INT64_FMT "I64d"
#define INT64_X_FMT "I64x"
#define SIZE_T_FMT "Iu"
typedef struct _stati64 BAIK_EM_stat_t;
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) &_S_IFMT) == _S_IFDIR)
#endif
#ifndef S_ISREG
#define S_ISREG(x) (((x) &_S_IFMT) == _S_IFREG)
#endif
#define DIRSEP '\\'
#define BAIK_EM_DEFINE_DIRENT

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#ifndef GENERIC_MAX_HTTP_REQUEST_SIZE
#define GENERIC_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef GENERIC_MAX_HTTP_SEND_MBUF
#define GENERIC_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef GENERIC_MAX_HTTP_HEADERS
#define GENERIC_MAX_HTTP_HEADERS 40
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifndef GENERIC_ENABLE_BROADCAST
#define GENERIC_ENABLE_BROADCAST 1
#endif

#ifndef GENERIC_ENABLE_DIRECTORY_LISTING
#define GENERIC_ENABLE_DIRECTORY_LISTING 1
#endif

#ifndef GENERIC_ENABLE_FILESYSTEM
#define GENERIC_ENABLE_FILESYSTEM 1
#endif

#ifndef GENERIC_ENABLE_HTTP_CGI
#define GENERIC_ENABLE_HTTP_CGI GENERIC_ENABLE_FILESYSTEM
#endif

#ifndef GENERIC_NET_IF
#define GENERIC_NET_IF GENERIC_NET_IF_SOCKET
#endif

unsigned int sleep(unsigned int seconds);


#define timegm _mkgmtime

#define gmtime_r(a, b) \
  do {                 \
    *(b) = *gmtime(a); \
  } while (0)

#endif
#endif
#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_UNIX_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_UNIX_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_UNIX

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#endif

#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif

#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __APPLE__
#include <machine/endian.h>
#ifndef BYTE_ORDER
#define LITTLE_ENDIAN __DARWIN_LITTLE_ENDIAN
#define BIG_ENDIAN __DARWIN_BIG_ENDIAN
#define PDP_ENDIAN __DARWIN_PDP_ENDIAN
#define BYTE_ORDER __DARWIN_BYTE_ORDER
#endif
#endif

#if !(defined(__cplusplus) && __cplusplus >= 201103L) && \
    !(defined(__DARWIN_C_LEVEL) && __DARWIN_C_LEVEL >= 200809L)
long long strtoll(const char *, char **, int);
#endif

typedef int sock_t;
#define INVALID_SOCKET (-1)
#define SIZE_T_FMT "zu"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64

#ifndef __cdecl
#define __cdecl
#endif

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#define closesocket(x) close(x)

#ifndef GENERIC_MAX_HTTP_REQUEST_SIZE
#define GENERIC_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef GENERIC_MAX_HTTP_SEND_MBUF
#define GENERIC_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef GENERIC_MAX_HTTP_HEADERS
#define GENERIC_MAX_HTTP_HEADERS 40
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifndef GENERIC_ENABLE_BROADCAST
#define GENERIC_ENABLE_BROADCAST 1
#endif

#ifndef GENERIC_ENABLE_DIRECTORY_LISTING
#define GENERIC_ENABLE_DIRECTORY_LISTING 1
#endif

#ifndef GENERIC_ENABLE_FILESYSTEM
#define GENERIC_ENABLE_FILESYSTEM 1
#endif

#ifndef GENERIC_ENABLE_HTTP_CGI
#define GENERIC_ENABLE_HTTP_CGI GENERIC_ENABLE_FILESYSTEM
#endif

#ifndef GENERIC_NET_IF
#define GENERIC_NET_IF GENERIC_NET_IF_SOCKET
#endif

#ifndef GENERIC_HOSTS_FILE_NAME
#define GENERIC_HOSTS_FILE_NAME "/etc/hosts"
#endif

#ifndef GENERIC_RESOLV_CONF_FILE_NAME
#define GENERIC_RESOLV_CONF_FILE_NAME "/etc/resolv.conf"
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_ESP32_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_ESP32

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl
#define _FILE_OFFSET_BITS 32

#define GENERIC_LWIP 1

#ifndef GENERIC_NET_IF
#define GENERIC_NET_IF GENERIC_NET_IF_SOCKET
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_ESP8266_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_ESP8266

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <machine/endian.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'
#if !defined(MGOS_VFS_DEFINE_DIRENT)
#define BAIK_EM_DEFINE_DIRENT
#endif

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl
#define _FILE_OFFSET_BITS 32

#define GENERIC_LWIP 1


#define LWIP_TIMEVAL_PRIVATE 0

#ifndef GENERIC_NET_IF
#include <lwip/opt.h>
#if LWIP_SOCKET
#define GENERIC_NET_IF GENERIC_NET_IF_SOCKET
#else
#define GENERIC_NET_IF GENERIC_NET_IF_LWIP_LOW_LEVEL
#endif
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#define inet_ntop(af, src, dst, size)                                          \
  (((af) == AF_INET) ? ipaddr_ntoa_r((const ip_addr_t *) (src), (dst), (size)) \
                     : NULL)
#define inet_pton(af, src, dst) \
  (((af) == AF_INET) ? ipaddr_aton((src), (ip_addr_t *) (dst)) : 0)

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3100_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3100_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_CC3100

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define GENERIC_NET_IF GENERIC_NET_IF_SIMPLELINK
#define GENERIC_SSL_IF GENERIC_SSL_IF_SIMPLELINK

#include <simplelink.h>
#include <netapp.h>
#undef timeval

typedef int sock_t;
#define INVALID_SOCKET (-1)

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define SIZE_T_FMT "u"

#define SOMAXCONN 8

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_SIMPLELINK_BAIK_EM_SIMPLELINK_H_
#define BAIK_EM_COMMON_PLATFORMS_SIMPLELINK_BAIK_EM_SIMPLELINK_H_

#if defined(GENERIC_NET_IF) && GENERIC_NET_IF == GENERIC_NET_IF_SIMPLELINK

#if !defined(__SIMPLELINK_H__)

#include <stdbool.h>

#ifndef __TI_COMPILER_VERSION__
#undef __CONCAT
#undef FD_CLR
#undef FD_ISSET
#undef FD_SET
#undef FD_SETSIZE
#undef FD_ZERO
#undef fd_set
#endif

#if BAIK_EM_PLATFORM == BAIK_EM_P_CC3220
#include <ti/drivers/net/wifi/porting/user.h>
#include <ti/drivers/net/wifi/simplelink.h>
#include <ti/drivers/net/wifi/sl_socket.h>
#include <ti/drivers/net/wifi/netapp.h>
#else

#define PROVISIONING_API_H_
#include <simplelink/user.h>
#undef PROVISIONING_API_H_
#undef SL_INC_STD_BSD_API_NAMING

#include <simplelink/include/simplelink.h>
#include <simplelink/include/netapp.h>
#endif


#define AF_INET SL_AF_INET

#define socklen_t SlSocklen_t
#define sockaddr SlSockAddr_t
#define sockaddr_in SlSockAddrIn_t
#define in_addr SlInAddr_t

#define SOCK_STREAM SL_SOCK_STREAM
#define SOCK_DGRAM SL_SOCK_DGRAM

#define htonl sl_Htonl
#define ntohl sl_Ntohl
#define htons sl_Htons
#define ntohs sl_Ntohs

#ifndef EACCES
#define EACCES SL_EACCES
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT SL_EAFNOSUPPORT
#endif
#ifndef EAGAIN
#define EAGAIN SL_EAGAIN
#endif
#ifndef EBADF
#define EBADF SL_EBADF
#endif
#ifndef EINVAL
#define EINVAL SL_EINVAL
#endif
#ifndef ENOMEM
#define ENOMEM SL_ENOMEM
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK SL_EWOULDBLOCK
#endif

#define SOMAXCONN 8

#ifdef __cplusplus
extern "C" {
#endif

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);

struct baik_generic_mgr;
struct baik_generic_connection;

typedef void (*baik_generic_init_cb)(struct baik_generic_mgr *mgr);
bool baik_generic_start_task(int priority, int stack_size, baik_generic_init_cb baik_generic_init);

void baik_generic_run_in_task(void (*cb)(struct baik_generic_mgr *mgr, void *arg), void *cb_arg);

int sl_fs_init(void);

void sl_restart_cb(struct baik_generic_mgr *mgr);

int sl_set_ssl_opts(int sock, struct baik_generic_connection *nc);

#ifdef __cplusplus
}
#endif

#endif


#if SL_MAJOR_VERSION_NUM < 2

#define SL_ERROR_BSD_EAGAIN SL_EAGAIN
#define SL_ERROR_BSD_EALREADY SL_EALREADY
#define SL_ERROR_BSD_ENOPROTOOPT SL_ENOPROTOOPT
#define SL_ERROR_BSD_ESECDATEERROR SL_ESECDATEERROR
#define SL_ERROR_BSD_ESECSNOVERIFY SL_ESECSNOVERIFY
#define SL_ERROR_FS_FAILED_TO_ALLOCATE_MEM SL_FS_ERR_FAILED_TO_ALLOCATE_MEM
#define SL_ERROR_FS_FILE_HAS_NOT_BEEN_CLOSE_CORRECTLY \
  SL_FS_FILE_HAS_NOT_BEEN_CLOSE_CORRECTLY
#define SL_ERROR_FS_FILE_NAME_EXIST SL_FS_FILE_NAME_EXIST
#define SL_ERROR_FS_FILE_NOT_EXISTS SL_FS_ERR_FILE_NOT_EXISTS
#define SL_ERROR_FS_NO_AVAILABLE_NV_INDEX SL_FS_ERR_NO_AVAILABLE_NV_INDEX
#define SL_ERROR_FS_NOT_ENOUGH_STORAGE_SPACE SL_FS_ERR_NO_AVAILABLE_BLOCKS
#define SL_ERROR_FS_NOT_SUPPORTED SL_FS_ERR_NOT_SUPPORTED
#define SL_ERROR_FS_WRONG_FILE_NAME SL_FS_WRONG_FILE_NAME
#define SL_ERROR_FS_INVALID_HANDLE SL_FS_ERR_INVALID_HANDLE
#define SL_NETCFG_MAC_ADDRESS_GET SL_MAC_ADDRESS_GET
#define SL_SOCKET_FD_ZERO SL_FD_ZERO
#define SL_SOCKET_FD_SET SL_FD_SET
#define SL_SOCKET_FD_ISSET SL_FD_ISSET
#define SL_SO_SECURE_DOMAIN_NAME_VERIFICATION SO_SECURE_DOMAIN_NAME_VERIFICATION

#define SL_FS_READ FS_MODE_OPEN_READ
#define SL_FS_WRITE FS_MODE_OPEN_WRITE

#define SL_FI_FILE_SIZE(fi) ((fi).FileLen)
#define SL_FI_FILE_MAX_SIZE(fi) ((fi).AllocatedLen)

#define SlDeviceVersion_t SlVersionFull
#define sl_DeviceGet sl_DevGet
#define SL_DEVICE_GENERAL SL_DEVICE_GENERAL_CONFIGURATION
#define SL_LEN_TYPE _u8
#define SL_OPT_TYPE _u8

#else

#define FS_MODE_OPEN_CREATE(max_size, flag) \
  (SL_FS_CREATE | SL_FS_CREATE_MAX_SIZE(max_size))
#define SL_FI_FILE_SIZE(fi) ((fi).Len)
#define SL_FI_FILE_MAX_SIZE(fi) ((fi).MaxSize)

#define SL_LEN_TYPE _u16
#define SL_OPT_TYPE _u16

#endif

int slfs_open(const unsigned char *fname, uint32_t flags, uint32_t *token);

#endif

#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3200_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_CC3200

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifndef __TI_COMPILER_VERSION__
#include <fcntl.h>
#include <sys/time.h>
#endif

#define GENERIC_NET_IF GENERIC_NET_IF_SIMPLELINK
#define GENERIC_SSL_IF GENERIC_SSL_IF_SIMPLELINK

#if defined(CC3200_FS_SPIFFS) && !defined(GENERIC_ENABLE_DIRECTORY_LISTING)
#define GENERIC_ENABLE_DIRECTORY_LISTING 1
#endif

typedef int sock_t;
#define INVALID_SOCKET (-1)
#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl

#define fileno(x) -1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __TI_COMPILER_VERSION__
struct SlTimeval_t;
#define timeval SlTimeval_t
int gettimeofday(struct timeval *t, void *tz);
int settimeofday(const struct timeval *tv, const void *tz);
int asprintf(char **strp, const char *fmt, ...);
#endif

#ifdef __TI_COMPILER_VERSION__
#include <file.h>

typedef unsigned int mode_t;
typedef size_t _off_t;
typedef long ssize_t;

struct stat {
  int st_ino;
  mode_t st_mode;
  int st_nlink;
  time_t st_mtime;
  off_t st_size;
};

int _stat(const char *pathname, struct stat *st);
int stat(const char *pathname, struct stat *st);

#define __S_IFMT 0170000

#define __S_IFDIR 0040000
#define __S_IFCHR 0020000
#define __S_IFREG 0100000

#define __S_ISTYPE(mode, mask) (((mode) &__S_IFMT) == (mask))

#define S_IFDIR __S_IFDIR
#define S_IFCHR __S_IFCHR
#define S_IFREG __S_IFREG
#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)

#if __TI_COMPILER_VERSION__ < 16000000
#define va_copy(apc, ap) ((apc) = (ap))
#endif

#endif

#ifdef CC3200_FS_SLFS
#define GENERIC_FS_SLFS
#endif

#if (defined(CC3200_FS_SPIFFS) || defined(CC3200_FS_SLFS)) && \
    !defined(GENERIC_ENABLE_FILESYSTEM)
#define GENERIC_ENABLE_FILESYSTEM 1
#define BAIK_EM_DEFINE_DIRENT
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3220_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_CC3220_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_CC3220

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifndef __TI_COMPILER_VERSION__
#include <fcntl.h>
#include <sys/time.h>
#endif

#define GENERIC_NET_IF GENERIC_NET_IF_SIMPLELINK
#ifndef GENERIC_SSL_IF
#define GENERIC_SSL_IF GENERIC_SSL_IF_SIMPLELINK
#endif

#if defined(CC3220_FS_SPIFFS) && !defined(GENERIC_ENABLE_DIRECTORY_LISTING)
#define GENERIC_ENABLE_DIRECTORY_LISTING 1
#endif

typedef int sock_t;
#define INVALID_SOCKET (-1)
#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define __cdecl

#define fileno(x) -1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __TI_COMPILER_VERSION__
struct SlTimeval_t;
#define timeval SlTimeval_t
int gettimeofday(struct timeval *t, void *tz);
int settimeofday(const struct timeval *tv, const void *tz);

int asprintf(char **strp, const char *fmt, ...);

#endif

#ifdef __TI_COMPILER_VERSION__

#include <file.h>

typedef unsigned int mode_t;
typedef size_t _off_t;
typedef long ssize_t;

struct stat {
  int st_ino;
  mode_t st_mode;
  int st_nlink;
  time_t st_mtime;
  off_t st_size;
};

int _stat(const char *pathname, struct stat *st);
int stat(const char *pathname, struct stat *st);

#define __S_IFMT 0170000
#define __S_IFDIR 0040000
#define __S_IFCHR 0020000
#define __S_IFREG 0100000
#define __S_ISTYPE(mode, mask) (((mode) &__S_IFMT) == (mask))
#define S_IFDIR __S_IFDIR
#define S_IFCHR __S_IFCHR
#define S_IFREG __S_IFREG
#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)

#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_MBED_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_MBED_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_MBED


#ifdef __cplusplus

#endif

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif


#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
#define _TIMEVAL_DEFINED
#define gettimeofday _gettimeofday


typedef long suseconds_t;
struct timeval {
  time_t tv_sec;      
  suseconds_t tv_usec;
};

#endif

#if GENERIC_NET_IF == GENERIC_NET_IF_SIMPLELINK

#define GENERIC_SIMPLELINK_NO_OSI 1

#include <simplelink.h>

typedef int sock_t;
#define INVALID_SOCKET (-1)

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT PRId64
#define INT64_X_FMT PRIx64
#define SIZE_T_FMT "u"

#define SOMAXCONN 8

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
char *inet_ntoa(struct in_addr in);
int inet_pton(int af, const char *src, void *dst);
int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);

#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_NRF51_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_NRF51_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_NRF51

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define to64(x) strtoll(x, NULL, 10)
#define GENERIC_NET_IF GENERIC_NET_IF_LWIP_LOW_LEVEL
#define GENERIC_LWIP 1
#define GENERIC_ENABLE_IPV6 1

#if !defined(__ARMCC_VERSION)
#define LWIP_TIMEVAL_PRIVATE 0
#else
struct timeval;
int gettimeofday(struct timeval *tp, void *tzp);
#endif

#define INT64_FMT PRId64
#define SIZE_T_FMT "u"
#define BAIK_EM_ENABLE_STRDUP defined(__ARMCC_VERSION)

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_NRF52_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_NRF52

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define to64(x) strtoll(x, NULL, 10)

#define GENERIC_NET_IF GENERIC_NET_IF_LWIP_LOW_LEVEL
#define GENERIC_LWIP 1
#define GENERIC_ENABLE_IPV6 1

#if !defined(ENOSPC)
#define ENOSPC 28
#endif


#if !defined(__ARMCC_VERSION)
#define LWIP_TIMEVAL_PRIVATE 0
#endif

#define INT64_FMT PRId64
#define SIZE_T_FMT "u"

#define BAIK_EM_ENABLE_STRDUP defined(__ARMCC_VERSION)

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_WINCE_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_WINCE_H_

#if BAIK_EM_PLATFORM == BAIK_EM_P_WINCE

#pragma warning(disable : 4127)
#pragma warning(disable : 4204)

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "ws2.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define strdup _strdup

#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

#ifndef EAGAIN
#define EAGAIN EWOULDBLOCK
#endif

#ifndef __func__
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)
#endif

#define snprintf _snprintf
#define fileno _fileno
#define vsnprintf _vsnprintf
#define sleep(x) Sleep((x) *1000)
#define to64(x) _atoi64(x)
#define rmdir _rmdir

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define fseeko(x, y, z) _fseeki64((x), (y), (z))
#else
#define fseeko(x, y, z) fseek((x), (y), (z))
#endif

typedef int socklen_t;

#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

typedef SOCKET sock_t;
typedef uint32_t in_addr_t;

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 4294967295
#endif

#ifndef pid_t
#define pid_t HANDLE
#endif

#define INT64_FMT "I64d"
#define INT64_X_FMT "I64x"

#define SIZE_T_FMT "u"

#define DIRSEP '\\'
#define BAIK_EM_DEFINE_DIRENT

#ifndef va_copy
#ifdef __va_copy
#define va_copy __va_copy
#else
#define va_copy(x, y) (x) = (y)
#endif
#endif

#ifndef GENERIC_MAX_HTTP_REQUEST_SIZE
#define GENERIC_MAX_HTTP_REQUEST_SIZE 8192
#endif

#ifndef GENERIC_MAX_HTTP_SEND_MBUF
#define GENERIC_MAX_HTTP_SEND_MBUF 4096
#endif

#ifndef GENERIC_MAX_HTTP_HEADERS
#define GENERIC_MAX_HTTP_HEADERS 40
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#define abort() DebugBreak();

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif

#ifndef GENERIC_ENABLE_THREADS
#define GENERIC_ENABLE_THREADS 0
#endif

#ifndef GENERIC_ENABLE_FILESYSTEM
#define GENERIC_ENABLE_FILESYSTEM 1
#endif

#ifndef GENERIC_NET_IF
#define GENERIC_NET_IF GENERIC_NET_IF_SOCKET
#endif

typedef struct _stati64 {
  uint32_t st_mtime;
  uint32_t st_size;
  uint32_t st_mode;
} BAIK_EM_stat_t;



#ifndef ENOENT
#define ENOENT ERROR_PATH_NOT_FOUND
#endif

#ifndef EACCES
#define EACCES ERROR_ACCESS_DENIED
#endif

#ifndef ENOMEM
#define ENOMEM ERROR_NOT_ENOUGH_MEMORY
#endif

#ifndef _UINTPTR_T_DEFINED
typedef unsigned int *uintptr_t;
#endif

#define _S_IFREG 2
#define _S_IFDIR 4

#ifndef S_ISDIR
#define S_ISDIR(x) (((x) &_S_IFDIR) != 0)
#endif

#ifndef S_ISREG
#define S_ISREG(x) (((x) &_S_IFREG) != 0)
#endif

int open(const char *filename, int oflag, int pmode);
int _wstati64(const wchar_t *path, BAIK_EM_stat_t *st);
const char *strerror();

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_NXP_LPC_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_NXP_LPC_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_NXP_LPC

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define INT64_FMT "lld"
#define INT64_X_FMT "llx"
#define __cdecl

#define GENERIC_LWIP 1

#define GENERIC_NET_IF GENERIC_NET_IF_LWIP_LOW_LEVEL


#ifdef __REDLIB_INTERFACE_VERSION__


#define LWIP_TIMEVAL_PRIVATE 1

#define va_copy(d, s) __builtin_va_copy(d, s)

#define BAIK_EM_ENABLE_TO64 1
#define to64(x) BAIK_EM_to64(x)

#define BAIK_EM_ENABLE_STRDUP 1

#else

#include <sys/time.h>
#define LWIP_TIMEVAL_PRIVATE 0
#define to64(x) strtoll(x, NULL, 10)

#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_NXP_KINETIS_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_NXP_KINETIS_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_NXP_KINETIS

#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <sys/time.h>

#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define INT64_X_FMT "llx"
#define __cdecl

#define GENERIC_LWIP 1

#define GENERIC_NET_IF GENERIC_NET_IF_LWIP_LOW_LEVEL


#define LWIP_TIMEVAL_PRIVATE 0

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_PIC32_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_PIC32_H_

#if BAIK_EM_PLATFORM == BAIK_EM_P_PIC32

#define GENERIC_NET_IF GENERIC_NET_IF_PIC32

#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <system_config.h>
#include <system_definitions.h>
#include <sys/types.h>

typedef TCP_SOCKET sock_t;
#define to64(x) strtoll(x, NULL, 10)

#define SIZE_T_FMT "lu"
#define INT64_FMT "lld"

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

char *inet_ntoa(struct in_addr in);

#endif

#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_RS14100_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_RS14100_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_RS14100

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef MGOS_HAVE_VFS_COMMON
#include <mgos_vfs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifndef GENERIC_ENABLE_FILESYSTEM
#define GENERIC_ENABLE_FILESYSTEM 1
#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_PLATFORMS_PLATFORM_STM32_H_
#define BAIK_EM_COMMON_PLATFORMS_PLATFORM_STM32_H_
#if BAIK_EM_PLATFORM == BAIK_EM_P_STM32

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

#include <stm32_sdk_hal.h>

#define to64(x) strtoll(x, NULL, 10)
#define INT64_FMT "lld"
#define SIZE_T_FMT "u"
typedef struct stat BAIK_EM_stat_t;
#define DIRSEP '/'

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#ifndef GENERIC_ENABLE_FILESYSTEM
#define GENERIC_ENABLE_FILESYSTEM 1
#endif

#endif
#endif

#ifndef BAIK_EM_COMMON_BAIK_EM_DBG_H_
#define BAIK_EM_COMMON_BAIK_EM_DBG_H_

#if BAIK_EM_ENABLE_STDIO
#include <stdio.h>
#endif

#ifndef BAIK_EM_ENABLE_DEBUG
#define BAIK_EM_ENABLE_DEBUG 0
#endif

#ifndef BAIK_EM_LOG_PREFIX_LEN
#define BAIK_EM_LOG_PREFIX_LEN 24
#endif

#ifndef BAIK_EM_LOG_ENABLE_TS_DIFF
#define BAIK_EM_LOG_ENABLE_TS_DIFF 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum BAIK_EM_log_level {
  LL_NONE = -1,
  LL_ERROR = 0,
  LL_WARN = 1,
  LL_INFO = 2,
  LL_DEBUG = 3,
  LL_VERBOSE_DEBUG = 4,

  _LL_MIN = -2,
  _LL_MAX = 5,
};


void BAIK_EM_log_set_level(enum BAIK_EM_log_level level);
void BAIK_EM_log_set_file_level(const char *file_level);
int BAIK_EM_log_print_prefix(enum BAIK_EM_log_level level, const char *fname, int line);

extern enum BAIK_EM_log_level BAIK_EM_log_level;

#if BAIK_EM_ENABLE_STDIO

void BAIK_EM_log_set_file(FILE *file);
void BAIK_EM_log_printf(const char *fmt, ...) PRINTF_LIKE(1, 2);

#if BAIK_EM_ENABLE_STDIO
#define LOG(l, x)                                     \
  do {                                                \
    if (BAIK_EM_log_print_prefix(l, __FILE__, __LINE__)) { \
      BAIK_EM_log_printf x;                                \
    }                                                 \
  } while (0)
#else
#define LOG(l, x) ((void) l)
#endif

#ifndef BAIK_EM_NDEBUG
#define DBG(x) LOG(LL_VERBOSE_DEBUG, x)
#else

#define DBG(x)

#endif

#else
#define LOG(l, x)
#define DBG(x)
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_COMMON_BAIK_EM_TIME_H_
#define BAIK_EM_COMMON_BAIK_EM_TIME_H_

#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif


double BAIK_EM_time(void);


double BAIK_EM_timegm(const struct tm *tm);

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_COMMON_GENERIC_STR_H_
#define BAIK_EM_COMMON_GENERIC_STR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct baik_generic_str {
  const char *p;
  size_t len;   
};

struct baik_generic_str baik_generic_mk_str(const char *s);
struct baik_generic_str baik_generic_mk_str_n(const char *s, size_t len);

#define GENERIC_MK_STR(str_literal) \
  { str_literal, sizeof(str_literal) - 1 }
#define GENERIC_MK_STR_N(str_literal, len) \
  { str_literal, len }
#define GENERIC_NULL_STR \
  { NULL, 0 }

int baik_generic_vcmp(const struct baik_generic_str *str2, const char *str1);
int baik_generic_vcasecmp(const struct baik_generic_str *str2, const char *str1);
struct baik_generic_str baik_generic_strdup(const struct baik_generic_str s);
struct baik_generic_str baik_generic_strdup_nul(const struct baik_generic_str s);
const char *baik_generic_strchr(const struct baik_generic_str s, int c);
int baik_generic_strcmp(const struct baik_generic_str str1, const struct baik_generic_str str2);
int baik_generic_strncmp(const struct baik_generic_str str1, const struct baik_generic_str str2, size_t n);
void baik_generic_strfree(struct baik_generic_str *s);
const char *baik_generic_strstr(const struct baik_generic_str haystack, const struct baik_generic_str needle);
struct baik_generic_str baik_generic_strstrip(struct baik_generic_str s);
int baik_generic_str_starts_with(struct baik_generic_str s, struct baik_generic_str prefix);

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_COMMON_STR_UTIL_H_
#define BAIK_EM_COMMON_STR_UTIL_H_

#include <stdarg.h>
#include <stdlib.h>

#ifndef BAIK_EM_ENABLE_STRDUP
#define BAIK_EM_ENABLE_STRDUP 0
#endif

#ifndef BAIK_EM_ENABLE_TO64
#define BAIK_EM_ENABLE_TO64 0
#endif

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#define BAIK_EM_STRINGIFY_LIT(...) #__VA_ARGS__
#else
#define BAIK_EM_STRINGIFY_LIT(x) #x
#endif

#define BAIK_EM_STRINGIFY_MACRO(x) BAIK_EM_STRINGIFY_LIT(x)

#ifdef __cplusplus
extern "C" {
#endif

size_t c_strnlen(const char *s, size_t maxlen);
int c_snprintf(char *buf, size_t buf_size, const char *format, ...)
    PRINTF_LIKE(3, 4);
int c_vsnprintf(char *buf, size_t buf_size, const char *format, va_list ap);
const char *c_strnstr(const char *s, const char *find, size_t slen);
void BAIK_EM_to_hex(char *to, const unsigned char *p, size_t len);
void BAIK_EM_from_hex(char *to, const char *p, size_t len);

#if BAIK_EM_ENABLE_STRDUP
char *strdup(const char *src);
#endif

#if BAIK_EM_ENABLE_TO64
#include <stdint.h>
int64_t BAIK_EM_to64(const char *s);
#endif
int baik_generic_ncasecmp(const char *s1, const char *s2, size_t len);
int baik_generic_casecmp(const char *s1, const char *s2);
int baik_generic_asprintf(char **buf, size_t size, const char *fmt, ...)
    PRINTF_LIKE(3, 4);
int baik_generic_avprintf(char **buf, size_t size, const char *fmt, va_list ap);
const char *baik_generic_next_comma_list_entry(const char *list, struct baik_generic_str *val,
                                     struct baik_generic_str *eq_val);
struct baik_generic_str baik_generic_next_comma_list_entry_n(struct baik_generic_str list, struct baik_generic_str *val,
                                         struct baik_generic_str *eq_val);
size_t baik_generic_match_prefix(const char *pattern, int pattern_len, const char *str);
size_t baik_generic_match_prefix_n(const struct baik_generic_str pattern, const struct baik_generic_str str);

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_COMMON_BAIK_EM_FILE_H_
#define BAIK_EM_COMMON_BAIK_EM_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

char *BAIK_EM_read_file(const char *path, size_t *size);

#ifdef BAIK_EM_MMAP
char *BAIK_EM_mmap_file(const char *path, size_t *size);
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_COMMON_MBUF_H_
#define BAIK_EM_COMMON_MBUF_H_
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef MBUF_SIZE_MULTIPLIER
#define MBUF_SIZE_MULTIPLIER 1.5
#endif

#ifndef MBUF_SIZE_MAX_HEADROOM
#ifdef BUFSIZ
#define MBUF_SIZE_MAX_HEADROOM BUFSIZ
#else
#define MBUF_SIZE_MAX_HEADROOM 1024
#endif
#endif

struct mbuf {
  char *buf;  
  size_t len; 
  size_t size;
};

void mbuf_init(struct mbuf *, size_t initial_capacity);
void mbuf_free(struct mbuf *);
size_t mbuf_append(struct mbuf *, const void *data, size_t data_size);
size_t mbuf_append_and_free(struct mbuf *, void *data, size_t data_size);
size_t mbuf_insert(struct mbuf *, size_t, const void *, size_t);
void mbuf_remove(struct mbuf *, size_t data_size);
void mbuf_resize(struct mbuf *, size_t new_size);
void mbuf_move(struct mbuf *from, struct mbuf *to);
void mbuf_clear(struct mbuf *);
void mbuf_trim(struct mbuf *);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_EM_COMMON_GENERIC_MEM_H_
#define BAIK_EM_COMMON_GENERIC_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GENERIC_MALLOC
#define GENERIC_MALLOC malloc
#endif

#ifndef GENERIC_CALLOC
#define GENERIC_CALLOC calloc
#endif

#ifndef GENERIC_REALLOC
#define GENERIC_REALLOC realloc
#endif

#ifndef GENERIC_FREE
#define GENERIC_FREE free
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_EM_FROZEN_FROZEN_H_
#define BAIK_EM_FROZEN_FROZEN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#if defined(_WIN32) && _MSC_VER < 1700
typedef int bool;
enum { false = 0, true = 1 };
#else
#include <stdbool.h>
#endif

enum json_token_type {
  JSON_TYPE_INVALID = 0,
  JSON_TYPE_STRING,
  JSON_TYPE_NUMBER,
  JSON_TYPE_TRUE,
  JSON_TYPE_FALSE,
  JSON_TYPE_NULL,
  JSON_TYPE_OBJECT_START,
  JSON_TYPE_OBJECT_END,
  JSON_TYPE_ARRAY_START,
  JSON_TYPE_ARRAY_END,
  JSON_TYPES_CNT
};

struct json_token {
  const char *ptr;          
  int len;                  
  enum json_token_type type;
};

#define JSON_INVALID_TOKEN \
  { 0, 0, JSON_TYPE_INVALID }

#define JSON_STRING_INVALID -1
#define JSON_STRING_INCOMPLETE -2

typedef void (*json_walk_callback_t)(void *callback_data, const char *name,
                                     size_t name_len, const char *path,
                                     const struct json_token *token);
int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data);
struct json_out {
  int (*printer)(struct json_out *, const char *str, size_t len);
  union {
    struct {
      char *buf;
      size_t size;
      size_t len;
    } buf;
    void *data;
    FILE *fp;
  } u;
};

extern int json_printer_buf(struct json_out *, const char *, size_t);
extern int json_printer_file(struct json_out *, const char *, size_t);

#define JSON_OUT_BUF(buf, len) \
  {                            \
    json_printer_buf, {        \
      { buf, len, 0 }          \
    }                          \
  }
#define JSON_OUT_FILE(fp)   \
  {                         \
    json_printer_file, {    \
      { (char *) fp, 0, 0 } \
    }                       \
  }
typedef int (*json_printf_callback_t)(struct json_out *, va_list *ap);

int json_printf(struct json_out *, const char *fmt, ...);
int json_vprintf(struct json_out *, const char *fmt, va_list ap);
int json_fprintf(const char *file_name, const char *fmt, ...);
int json_vfprintf(const char *file_name, const char *fmt, va_list ap);
char *json_asprintf(const char *fmt, ...);
char *json_vasprintf(const char *fmt, va_list ap);
int json_printf_array(struct json_out *, va_list *ap);
int json_scanf(const char *str, int str_len, const char *fmt, ...);
int json_vscanf(const char *str, int str_len, const char *fmt, va_list ap);
typedef void (*json_scanner_t)(const char *str, int len, void *user_data);
int json_scanf_array_elem(const char *s, int len, const char *path, int index,
                          struct json_token *token);
int json_unescape(const char *src, int slen, char *dst, int dlen);
int json_escape(struct json_out *out, const char *str, size_t str_len);
char *json_fread(const char *file_name);
int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...);
int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap);
int json_prettify(const char *s, int len, struct json_out *out);
int json_prettify_file(const char *file_name);
void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val);
void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val);
#ifndef JSON_MAX_PATH_LEN
#define JSON_MAX_PATH_LEN 256
#endif

#ifndef JSON_MINIMAL
#define JSON_MINIMAL 0
#endif

#ifndef JSON_ENABLE_BASE64
#define JSON_ENABLE_BASE64 !JSON_MINIMAL
#endif

#ifndef JSON_ENABLE_HEX
#define JSON_ENABLE_HEX !JSON_MINIMAL
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_FFI_FFI_H_
#define BAIK_FFI_FFI_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define FFI_MAX_ARGS_CNT 6

typedef void(ffi_fn_t)(void);
typedef intptr_t ffi_word_t;

enum ffi_ctype {
  FFI_CTYPE_WORD,
  FFI_CTYPE_BOOL,
  FFI_CTYPE_FLOAT,
  FFI_CTYPE_DOUBLE,
};

struct ffi_arg {
  enum ffi_ctype ctype;
  union {
    uint64_t i;
    double d;
    float f;
  } v;
};

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args);

void ffi_set_word(struct ffi_arg *arg, ffi_word_t v);
void ffi_set_bool(struct ffi_arg *arg, bool v);
void ffi_set_ptr(struct ffi_arg *arg, void *v);
void ffi_set_double(struct ffi_arg *arg, double v);
void ffi_set_float(struct ffi_arg *arg, float v);

const char *baik_dlsym_file;

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_INTERNAL_H_
#define BAIK_INTERNAL_H_

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef FAST
#define FAST
#endif

#ifndef STATIC
#define STATIC
#endif

#ifndef ENDL
#define ENDL "\n"
#endif

#ifdef BAIK_EXPOSE_PRIVATE
#define BAIK_PRIVATE
#define BAIK_EXTERN extern
#else
#define BAIK_PRIVATE static
#define BAIK_EXTERN static
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#if defined(_WIN32) && _MSC_VER < 1700
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)

#define vsnprintf _vsnprintf
#define isnan(x) _isnan(x)
#define va_copy(x, y) (x) = (y)
#define BAIK_EM_DEFINE_DIRENT
#include <windows.h>
#else
#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#endif
#endif

#ifndef BAIK_INIT_OFFSET_SIZE
#define BAIK_INIT_OFFSET_SIZE 1
#endif

#endif
#ifndef BAIK_FEATURES_H_
#define BAIK_FEATURES_H_

#if !defined(BAIK_AGGRESSIVE_GC)
#define BAIK_AGGRESSIVE_GC 0
#endif

#if !defined(BAIK_MEMORY_STATS)
#define BAIK_MEMORY_STATS 0
#endif


#if !defined(BAIK_GENERATE_INAC)
#if defined(BAIK_EM_MMAP)
#define BAIK_GENERATE_INAC 1
#else
#define BAIK_GENERATE_INAC 0
#endif
#endif

#endif

#ifndef BAIK_CORE_PUBLIC_H_
#define BAIK_CORE_PUBLIC_H_

#if !defined(_MSC_VER) || _MSC_VER >= 1700
#include <stdint.h>
#else
typedef unsigned __int64 uint64_t;
typedef int int32_t;
typedef unsigned char uint8_t;
#endif
#include <stdio.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define BAIK_ENABLE_DEBUG 1
typedef uint64_t baik_val_t;

#if 0
struct baik {
 
};
#endif

struct baik;

typedef enum baik_err {
  BAIK_OK,
  BAIK_SYNTAX_ERROR,
  BAIK_REFERENCE_ERROR,
  BAIK_TYPE_ERROR,
  BAIK_OUT_OF_MEMORY,
  BAIK_INTERNAL_ERROR,
  BAIK_NOT_IMPLEMENTED_ERROR,
  BAIK_FILE_READ_ERROR,
  BAIK_BAD_ARGS_ERROR,
  BAIK_ERRS_CNT
} baik_err_t;
struct baik;
struct baik *baik_create();
struct baik_create_opts {
  const struct bf_code *code;
};

struct baik *baik_create_opt(struct baik_create_opts opts);
void baik_destroy(struct baik *baik);
baik_val_t baik_get_global(struct baik *baik);
void baik_own(struct baik *baik, baik_val_t *v);
int baik_disown(struct baik *baik, baik_val_t *v);
baik_err_t baik_set_errorf(struct baik *baik, baik_err_t err, const char *fmt, ...);
baik_err_t baik_prepend_errorf(struct baik *baik, baik_err_t err, const char *fmt,
                             ...);
void baik_print_error(struct baik *baik, FILE *fp, const char *msg,
                     int print_stack_trace);
const char *baik_strerror(struct baik *baik, enum baik_err err);
void baik_set_generate_jsc(struct baik *baik, int generate_jsc);
int baik_nargs(struct baik *baik);
baik_val_t baik_arg(struct baik *baik, int n);
void baik_return(struct baik *baik, baik_val_t v);
#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_ARRAY_PUBLIC_H_
#define BAIK_ARRAY_PUBLIC_H_

#if defined(__cplusplus)
extern "C" {
#endif

baik_val_t baik_mk_array(struct baik *baik);
unsigned long baik_array_length(struct baik *baik, baik_val_t arr);
baik_err_t baik_array_push(struct baik *baik, baik_val_t arr, baik_val_t v);
baik_val_t baik_array_get(struct baik *, baik_val_t arr, unsigned long index);
baik_err_t baik_array_set(struct baik *baik, baik_val_t arr, unsigned long index,
                        baik_val_t v);
int baik_is_array(baik_val_t v);
void baik_array_del(struct baik *baik, baik_val_t arr, unsigned long index);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_ARRAY_H_
#define BAIK_ARRAY_H_

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_val_t
baik_array_get2(struct baik *baik, baik_val_t arr, unsigned long index, int *has);
BAIK_PRIVATE void baik_array_splice(struct baik *baik);
BAIK_PRIVATE void baik_array_push_internal(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_FFI_PUBLIC_H_
#define BAIK_FFI_PUBLIC_H_

#if defined(__cplusplus)
extern "C" {
#endif

enum baik_ffi_ctype {
  BAIK_FFI_CTYPE_NONE,
  BAIK_FFI_CTYPE_USERDATA,
  BAIK_FFI_CTYPE_CALLBACK,
  BAIK_FFI_CTYPE_INT,
  BAIK_FFI_CTYPE_BOOL,
  BAIK_FFI_CTYPE_DOUBLE,
  BAIK_FFI_CTYPE_FLOAT,
  BAIK_FFI_CTYPE_CHAR_PTR,
  BAIK_FFI_CTYPE_VOID_PTR,
  BAIK_FFI_CTYPE_STRUCT_GENERIC_STR_PTR,
  BAIK_FFI_CTYPE_STRUCT_GENERIC_STR,
  BAIK_FFI_CTYPE_INVALID,
};

typedef void *(baik_ffi_resolver_t)(void *handle, const char *symbol);
void baik_set_ffi_resolver(struct baik *baik, baik_ffi_resolver_t *dlsym);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_FFI_H_
#define BAIK_FFI_H_

#if defined(__cplusplus)
extern "C" {
#endif

baik_ffi_resolver_t dlsym;

#define BAIK_CB_ARGS_MAX_CNT 6
#define BAIK_CB_SIGNATURE_MAX_SIZE (BAIK_CB_ARGS_MAX_CNT + 1)

typedef uint8_t baik_ffi_ctype_t;

enum ffi_sig_type {
  FFI_SIG_FUNC,
  FFI_SIG_CALLBACK,
};

struct baik_ffi_sig {
  struct baik_ffi_sig *cb_sig;
  baik_ffi_ctype_t val_types[BAIK_CB_SIGNATURE_MAX_SIZE];
  ffi_fn_t *fn;
  int8_t args_cnt;
  unsigned is_callback : 1;
  unsigned is_valid : 1;
};
typedef struct baik_ffi_sig baik_ffi_sig_t;

BAIK_PRIVATE void baik_ffi_sig_init(baik_ffi_sig_t *sig);
BAIK_PRIVATE void baik_ffi_sig_copy(baik_ffi_sig_t *to, const baik_ffi_sig_t *from);
BAIK_PRIVATE void baik_ffi_sig_free(baik_ffi_sig_t *sig);
BAIK_PRIVATE baik_val_t baik_mk_ffi_sig(struct baik *baik);
BAIK_PRIVATE int baik_is_ffi_sig(baik_val_t v);
BAIK_PRIVATE baik_val_t baik_ffi_sig_to_value(struct baik_ffi_sig *psig);
BAIK_PRIVATE struct baik_ffi_sig *baik_get_ffi_sig_struct(baik_val_t v);
BAIK_PRIVATE void baik_ffi_sig_destructor(struct baik *baik, void *psig);
BAIK_PRIVATE int baik_ffi_sig_set_val_type(baik_ffi_sig_t *sig, int idx,
                                         baik_ffi_ctype_t type);
BAIK_PRIVATE int baik_ffi_sig_validate(struct baik *baik, baik_ffi_sig_t *sig,
                                     enum ffi_sig_type sig_type);
BAIK_PRIVATE int baik_ffi_is_regular_word(baik_ffi_ctype_t type);
BAIK_PRIVATE int baik_ffi_is_regular_word_or_void(baik_ffi_ctype_t type);

struct baik_ffi_cb_args {
  struct baik_ffi_cb_args *next;
  struct baik *baik;
  baik_ffi_sig_t sig;
  baik_val_t func;
  baik_val_t userdata;
};
typedef struct baik_ffi_cb_args ffi_cb_args_t;
BAIK_PRIVATE baik_err_t baik_ffi_call(struct baik *baik);
BAIK_PRIVATE baik_err_t baik_ffi_call2(struct baik *baik);
BAIK_PRIVATE void baik_ffi_cb_free(struct baik *);
BAIK_PRIVATE void baik_ffi_args_free_list(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_MM_H_
#define BAIK_MM_H_

#if defined(__cplusplus)
extern "C" {
#endif

struct baik;

typedef void (*gc_cell_destructor_t)(struct baik *baik, void *);

struct gc_block {
  struct gc_block *next;
  struct gc_cell *base;
  size_t size;
};

struct gc_arena {
  struct gc_block *blocks;
  size_t size_increment;
  struct gc_cell *free;
  size_t cell_size;

#if BAIK_MEMORY_STATS
  unsigned long allocations;
  unsigned long garbage;    
  unsigned long alive;      
#endif

  gc_cell_destructor_t destructor;
};

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_GC_H_
#define BAIK_GC_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define GC_CELL_OP(arena, cell, op, arg) \
  ((struct gc_cell *) (((char *) (cell)) op((arg) * (arena)->cell_size)))

struct gc_cell {
  union {
    struct gc_cell *link;
    uintptr_t word;
  } head;
};

void baik_gc(struct baik *baik, int full);
BAIK_PRIVATE int gc_strings_is_gc_needed(struct baik *baik);
BAIK_PRIVATE int maybe_gc(struct baik *baik);
BAIK_PRIVATE struct baik_object *new_object(struct baik *);
BAIK_PRIVATE struct baik_property *new_property(struct baik *);
BAIK_PRIVATE struct baik_ffi_sig *new_ffi_sig(struct baik *baik);
BAIK_PRIVATE void gc_mark(struct baik *baik, baik_val_t *val);
BAIK_PRIVATE void gc_arena_init(struct gc_arena *, size_t, size_t, size_t);
BAIK_PRIVATE void gc_arena_destroy(struct baik *, struct gc_arena *a);
BAIK_PRIVATE void gc_sweep(struct baik *, struct gc_arena *, size_t);
BAIK_PRIVATE void *gc_alloc_cell(struct baik *, struct gc_arena *);
BAIK_PRIVATE uint64_t gc_string_baik_val_to_offset(baik_val_t v);
BAIK_PRIVATE int gc_check_val(struct baik *baik, baik_val_t v);
BAIK_PRIVATE int gc_check_ptr(const struct gc_arena *a, const void *p);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_CORE_H
#define BAIK_CORE_H

#if defined(__cplusplus)
extern "C" {
#endif

#define JUMP_INSTRUCTION_SIZE 2

enum baik_type {
  BAIK_TYPE_UNDEFINED,
  BAIK_TYPE_NULL,
  BAIK_TYPE_BOOLEAN,
  BAIK_TYPE_NUMBER,
  BAIK_TYPE_STRING,
  BAIK_TYPE_FOREIGN,
  BAIK_TYPE_OBJECT_GENERIC,
  BAIK_TYPE_OBJECT_ARRAY,
  BAIK_TYPE_OBJECT_FUNCTION,
  BAIK_TYPES_CNT
};

enum baik_call_stack_frame_item {
  CALL_STACK_FRAME_ITEM_RETVAL_STACK_IDX,
  CALL_STACK_FRAME_ITEM_LOOP_ADDR_IDX,
  CALL_STACK_FRAME_ITEM_SCOPE_IDX,
  CALL_STACK_FRAME_ITEM_RETURN_ADDR,
  CALL_STACK_FRAME_ITEM_THIS,
  CALL_STACK_FRAME_ITEMS_CNT
};


#define MAKE_TAG(s, t) \
  ((uint64_t)(s) << 63 | (uint64_t) 0x7ff0 << 48 | (uint64_t)(t) << 48)

#define BAIK_TAG_OBJECT MAKE_TAG(1, 1)
#define BAIK_TAG_FOREIGN MAKE_TAG(1, 2)
#define BAIK_TAG_UNDEFINED MAKE_TAG(1, 3)
#define BAIK_TAG_BOOLEAN MAKE_TAG(1, 4)
#define BAIK_TAG_NAN MAKE_TAG(1, 5)
#define BAIK_TAG_STRING_I MAKE_TAG(1, 6) 
#define BAIK_TAG_STRING_5 MAKE_TAG(1, 7) 
#define BAIK_TAG_STRING_O MAKE_TAG(1, 8) 
#define BAIK_TAG_STRING_F MAKE_TAG(1, 9) 
#define BAIK_TAG_STRING_C MAKE_TAG(1, 10)
#define BAIK_TAG_STRING_D MAKE_TAG(1, 11)
#define BAIK_TAG_ARRAY MAKE_TAG(1, 12)
#define BAIK_TAG_FUNCTION MAKE_TAG(1, 13)
#define BAIK_TAG_FUNCTION_FFI MAKE_TAG(1, 14)
#define BAIK_TAG_NULL MAKE_TAG(1, 15)

#define BAIK_TAG_MASK MAKE_TAG(1, 15)

struct baik_vals {
  baik_val_t this_obj;
  baik_val_t dataview_proto;
  baik_val_t last_getprop_obj;
};

struct baik_bcode_part {
 
  size_t start_idx;

  struct {
    const char *p;
    size_t len;   
  } data;

  baik_err_t exec_res : 4;
  unsigned in_rom : 1;
};

struct baik {
  struct mbuf bcode_gen;
  struct mbuf bcode_parts;
  size_t bcode_len;
  struct mbuf stack;
  struct mbuf call_stack;
  struct mbuf arg_stack;
  struct mbuf scopes;         
  struct mbuf loop_addresses; 
  struct mbuf owned_strings;  
  struct mbuf foreign_strings;
  struct mbuf owned_values;
  struct mbuf json_visited_stack;
  struct baik_vals vals;
  char *error_msg;
  char *stack_trace;
  enum baik_err error;
  baik_ffi_resolver_t *dlsym; 
  ffi_cb_args_t *ffi_cb_args;
  size_t cur_bcode_offset;

  struct gc_arena object_arena;
  struct gc_arena property_arena;
  struct gc_arena ffi_sig_arena;

  unsigned inhibit_gc : 1;
  unsigned need_gc : 1;
  unsigned generate_jsc : 1;
};


typedef uint32_t baik_header_item_t;
enum baik_header_items {
  BAIK_HDR_ITEM_TOTAL_SIZE,  
  BAIK_HDR_ITEM_BCODE_OFFSET,
  BAIK_HDR_ITEM_MAP_OFFSET,  
  BAIK_HDR_ITEMS_CNT
};

BAIK_PRIVATE size_t baik_get_func_addr(baik_val_t v);
BAIK_PRIVATE int baik_getretvalpos(struct baik *baik);
BAIK_PRIVATE enum baik_type baik_get_type(baik_val_t v);
BAIK_PRIVATE void baik_gen_stack_trace(struct baik *baik, size_t offset);
BAIK_PRIVATE baik_val_t vtop(struct mbuf *m);
BAIK_PRIVATE size_t baik_stack_size(const struct mbuf *m);
BAIK_PRIVATE baik_val_t *vptr(struct mbuf *m, int idx);
BAIK_PRIVATE void push_baik_val(struct mbuf *m, baik_val_t v);
BAIK_PRIVATE baik_val_t baik_pop_val(struct mbuf *m);
BAIK_PRIVATE baik_val_t baik_pop(struct baik *baik);
BAIK_PRIVATE void baik_push(struct baik *baik, baik_val_t v);
BAIK_PRIVATE void baik_die(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_CONVERSION_H_
#define BAIK_CONVERSION_H_

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_err_t baik_to_string(struct baik *baik, baik_val_t *v, char **p,
                                    size_t *sizep, int *need_free);
BAIK_PRIVATE baik_val_t baik_to_boolean_v(struct baik *baik, baik_val_t v);
BAIK_PRIVATE int baik_is_truthy(struct baik *baik, baik_val_t v);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_OBJECT_PUBLIC_H_
#define BAIK_OBJECT_PUBLIC_H_

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

int baik_is_object(baik_val_t v);
baik_val_t baik_mk_object(struct baik *baik);

enum baik_struct_field_type {
  BAIK_STRUCT_FIELD_TYPE_INVALID,
  BAIK_STRUCT_FIELD_TYPE_STRUCT,    
  BAIK_STRUCT_FIELD_TYPE_STRUCT_PTR,
  BAIK_STRUCT_FIELD_TYPE_INT,
  BAIK_STRUCT_FIELD_TYPE_BOOL,
  BAIK_STRUCT_FIELD_TYPE_DOUBLE,
  BAIK_STRUCT_FIELD_TYPE_FLOAT,
  BAIK_STRUCT_FIELD_TYPE_CHAR_PTR,  
  BAIK_STRUCT_FIELD_TYPE_VOID_PTR,  
  BAIK_STRUCT_FIELD_TYPE_GENERIC_STR_PTR,
  BAIK_STRUCT_FIELD_TYPE_GENERIC_STR,    
  BAIK_STRUCT_FIELD_TYPE_DATA,      
  BAIK_STRUCT_FIELD_TYPE_INT8,
  BAIK_STRUCT_FIELD_TYPE_INT16,
  BAIK_STRUCT_FIELD_TYPE_UINT8,
  BAIK_STRUCT_FIELD_TYPE_UINT16,
  BAIK_STRUCT_FIELD_TYPE_CUSTOM,
};

struct baik_c_struct_member {
  const char *name;
  int offset;
  enum baik_struct_field_type type;
  const void *arg;
};

baik_val_t baik_struct_to_obj(struct baik *baik, const void *base,
                            const struct baik_c_struct_member *members);
baik_val_t baik_get(struct baik *baik, baik_val_t obj, const char *name,
                  size_t name_len);
baik_val_t baik_get_v(struct baik *baik, baik_val_t obj, baik_val_t name);
baik_val_t baik_get_v_proto(struct baik *baik, baik_val_t obj, baik_val_t key);
baik_err_t baik_set(struct baik *baik, baik_val_t obj, const char *name, size_t len,
                  baik_val_t val);
baik_err_t baik_set_v(struct baik *baik, baik_val_t obj, baik_val_t name,
                    baik_val_t val);
int baik_del(struct baik *baik, baik_val_t obj, const char *name, size_t len);
baik_val_t baik_next(struct baik *baik, baik_val_t obj, baik_val_t *iterator);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_OBJECT_H_
#define BAIK_OBJECT_H_

#if defined(__cplusplus)
extern "C" {
#endif

struct baik;
struct baik_property {
  struct baik_property *next;
  baik_val_t name;           
  baik_val_t value;          
};

struct baik_object {
  struct baik_property *properties;
};

BAIK_PRIVATE struct baik_object *get_object_struct(baik_val_t v);
BAIK_PRIVATE struct baik_property *baik_get_own_property(struct baik *baik,
                                                      baik_val_t obj,
                                                      const char *name,
                                                      size_t len);
BAIK_PRIVATE struct baik_property *baik_get_own_property_v(struct baik *baik,
                                                        baik_val_t obj,
                                                        baik_val_t key);
BAIK_PRIVATE baik_err_t baik_set_internal(struct baik *baik, baik_val_t obj,
                                       baik_val_t name_v, char *name,
                                       size_t name_len, baik_val_t val);
BAIK_PRIVATE void baik_op_create_object(struct baik *baik);

#define BAIK_PROTO_PROP_NAME "__p"

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_PRIMITIVE_PUBLIC_H_
#define BAIK_PRIMITIVE_PUBLIC_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define BAIK_NULL BAIK_TAG_NULL
#define BAIK_UNDEFINED BAIK_TAG_UNDEFINED

typedef void (*baik_func_ptr_t)(void);
baik_val_t baik_mk_null(void);
int baik_is_null(baik_val_t v);
baik_val_t baik_mk_undefined(void);
int baik_is_undefined(baik_val_t v);
baik_val_t baik_mk_number(struct baik *baik, double num);
double baik_get_double(struct baik *baik, baik_val_t v);
int baik_get_int(struct baik *baik, baik_val_t v);
int32_t baik_get_int32(struct baik *baik, baik_val_t v);
int baik_is_number(baik_val_t v);
baik_val_t baik_mk_foreign(struct baik *baik, void *ptr);
baik_val_t baik_mk_foreign_func(struct baik *baik, baik_func_ptr_t fn);
void *baik_get_ptr(struct baik *baik, baik_val_t v);
int baik_is_foreign(baik_val_t v);
baik_val_t baik_mk_boolean(struct baik *baik, int v);
int baik_get_bool(struct baik *baik, baik_val_t v);
int baik_is_boolean(baik_val_t v);

baik_val_t baik_mk_function(struct baik *baik, size_t off);
int baik_is_function(baik_val_t v);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_PRIMITIVE_H
#define BAIK_PRIMITIVE_H

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_val_t baik_legit_pointer_to_value(void *p);
BAIK_PRIVATE baik_val_t baik_pointer_to_value(struct baik *baik, void *p);
BAIK_PRIVATE void *get_ptr(baik_val_t v);
BAIK_PRIVATE void baik_op_isnan(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_STRING_PUBLIC_H_
#define BAIK_STRING_PUBLIC_H_
#define BAIK_STRING_LITERAL_MAX_LEN 128

#if defined(__cplusplus)
extern "C" {
#endif

baik_val_t baik_mk_string(struct baik *baik, const char *str, size_t len, int copy);
int baik_is_string(baik_val_t v);
const char *baik_get_string(struct baik *baik, baik_val_t *v, size_t *len);
const char *baik_get_cstring(struct baik *baik, baik_val_t *v);
int baik_strcmp(struct baik *baik, baik_val_t *a, const char *b, size_t len);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_STRING_H_
#define BAIK_STRING_H_

#if defined(__cplusplus)
extern "C" {
#endif
#define _BAIK_STRING_BUF_RESERVE 100

BAIK_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok);
BAIK_PRIVATE baik_err_t
str_to_ulong(struct baik *baik, baik_val_t v, int *ok, unsigned long *res);
BAIK_PRIVATE int s_cmp(struct baik *baik, baik_val_t a, baik_val_t b);
BAIK_PRIVATE baik_val_t s_concat(struct baik *baik, baik_val_t a, baik_val_t b);
BAIK_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t flags);
BAIK_PRIVATE void baik_mkstr(struct baik *baik);
BAIK_PRIVATE void baik_string_slice(struct baik *baik);
BAIK_PRIVATE void baik_string_index_of(struct baik *baik);
BAIK_PRIVATE void baik_string_char_code_at(struct baik *baik);
#define EMBSTR_ZERO_TERM 1
#define EMBSTR_UNESCAPE 2

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_UTIL_PUBLIC_H_
#define BAIK_UTIL_PUBLIC_H_


#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif

const char *baik_typeof(baik_val_t v);
void baik_fprintf(baik_val_t v, struct baik *baik, FILE *fp);
void baik_sprintf(baik_val_t v, struct baik *baik, char *buf, size_t buflen);

#if BAIK_ENABLE_DEBUG
void baik_disasm(const uint8_t *code, size_t len);
void baik_dump(struct baik *baik, int do_disasm);
#endif


const char *baik_get_bcode_filename_by_offset(struct baik *baik, int offset);
int baik_get_lineno_by_offset(struct baik *baik, int offset);


int baik_get_offset_by_call_frame_num(struct baik *baik, int cf_num);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_UTIL_H_
#define BAIK_UTIL_H_

#if defined(__cplusplus)
extern "C" {
#endif

struct baik_bcode_part;

BAIK_PRIVATE const char *opcodetostr(uint8_t opcode);
BAIK_PRIVATE size_t baik_disasm_single(const uint8_t *code, size_t i);
BAIK_PRIVATE const char *baik_stringify_type(enum baik_type t);
BAIK_PRIVATE int baik_check_arg(struct baik *baik, int arg_num,
                              const char *arg_name, enum baik_type expected_type,
                              baik_val_t *parg);
BAIK_PRIVATE int baik_normalize_idx(int idx, int size);
BAIK_PRIVATE const char *baik_get_bcode_filename(struct baik *baik,
                                               struct baik_bcode_part *bp);
void baik_jprintf(baik_val_t v, struct baik *baik, struct json_out *out);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_EM_COMMON_BAIK_EM_VARINT_H_
#define BAIK_EM_COMMON_BAIK_EM_VARINT_H_

#if defined(_WIN32) && _MSC_VER < 1700
typedef unsigned char uint8_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


size_t BAIK_EM_varint_llen(uint64_t num);
size_t BAIK_EM_varint_encode(uint64_t num, uint8_t *buf, size_t buf_size);
bool BAIK_EM_varint_decode(const uint8_t *buf, size_t buf_size, uint64_t *num,
                      size_t *llen);
uint64_t BAIK_EM_varint_decode_unsafe(const uint8_t *buf, int *llen);

#ifdef __cplusplus
}
#endif

#endif

#ifndef BAIK_BCODE_H_
#define BAIK_BCODE_H_

#if defined(__cplusplus)
extern "C" {
#endif

enum baik_opcode {
  OP_NOP,              
  OP_DROP,             
  OP_DUP,              
  OP_SWAP,             
  OP_JMP,              
  OP_JMP_TRUE,         
  OP_JMP_NEUTRAL_TRUE, 
  OP_JMP_FALSE,        
  OP_JMP_NEUTRAL_FALSE,
  OP_FIND_SCOPE,       
  OP_PUSH_SCOPE,       
  OP_PUSH_STR,         
  OP_PUSH_TRUE,        
  OP_PUSH_FALSE,       
  OP_PUSH_INT,         
  OP_PUSH_DBL,         
  OP_PUSH_NULL,        
  OP_PUSH_UNDEF,       
  OP_PUSH_OBJ,         
  OP_PUSH_ARRAY,       
  OP_PUSH_FUNC,        
  OP_PUSH_THIS,        
  OP_GET,              
  OP_CREATE,           
  OP_EXPR,             
  OP_APPEND,           
  OP_SET_ARG,          
  OP_NEW_SCOPE,        
  OP_DEL_SCOPE,        
  OP_CALL,             
  OP_RETURN,           
  OP_LOOP,        
  OP_BREAK,       
  OP_CONTINUE,    
  OP_SETRETVAL,   
  OP_EXIT,        
  OP_BCODE_HEADER,
  OP_ARGS,        
  OP_FOR_IN_NEXT, 
  OP_MAX
};

struct pstate;
struct baik;

BAIK_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte);
BAIK_PRIVATE void emit_int(struct pstate *pstate, int64_t n);
BAIK_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len);
BAIK_PRIVATE int baik_bcode_insert_offset(struct pstate *p, struct baik *baik,
                                        size_t offset, size_t v);
BAIK_PRIVATE void baik_bcode_part_add(struct baik *baik,
                                    const struct baik_bcode_part *bp);
BAIK_PRIVATE struct baik_bcode_part *baik_bcode_part_get(struct baik *baik, int num);
BAIK_PRIVATE struct baik_bcode_part *baik_bcode_part_get_by_offset(struct baik *baik,
                                                                size_t offset);
BAIK_PRIVATE int baik_bcode_parts_cnt(struct baik *baik);
BAIK_PRIVATE void baik_bcode_commit(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_INTERNAL_H_
#define BAIK_INTERNAL_H_

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef FAST
#define FAST
#endif

#ifndef STATIC
#define STATIC
#endif

#ifndef ENDL
#define ENDL "\n"
#endif

#ifdef BAIK_EXPOSE_PRIVATE
#define BAIK_PRIVATE
#define BAIK_EXTERN extern
#else
#define BAIK_PRIVATE static
#define BAIK_EXTERN static
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifndef BAIK_EM_ENABLE_STDIO
#define BAIK_EM_ENABLE_STDIO 1
#endif

#if defined(_WIN32) && _MSC_VER < 1700
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#define STRX(x) #x
#define STR(x) STRX(x)
#define __func__ __FILE__ ":" STR(__LINE__)

#define vsnprintf _vsnprintf
#define isnan(x) _isnan(x)
#define va_copy(x, y) (x) = (y)
#define BAIK_EM_DEFINE_DIRENT
#include <windows.h>
#else
#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#endif
#endif

#ifndef BAIK_INIT_OFFSET_SIZE
#define BAIK_INIT_OFFSET_SIZE 1
#endif

#endif

#ifndef BAIK_TOK_H_
#define BAIK_TOK_H_

#if defined(__cplusplus)
extern "C" {
#endif

struct tok {
  int tok;
  int len;
  const char *ptr;
};

struct pstate {
  const char *file_name;
  const char *buf;      
  const char *pos;      
  int line_no;          
  int last_emitted_line_no;
  struct mbuf offset_lineno_map;
  int prev_tok;  
  struct tok tok;
  struct baik *baik;
  int start_bcode_idx;
  int cur_idx;
  int depth;
};

enum {
  TOK_EOF,
  TOK_INVALID,

  TOK_COLON,
  TOK_SEMICOLON,
  TOK_COMMA,
  TOK_ASSIGN,
  TOK_OPEN_CURLY,
  TOK_CLOSE_CURLY,
  TOK_OPEN_PAREN,
  TOK_CLOSE_PAREN,
  TOK_OPEN_BRACKET,
  TOK_CLOSE_BRACKET,
  TOK_MUL,
  TOK_PLUS,
  TOK_MINUS,
  TOK_DIV,
  TOK_REM,
  TOK_AND,
  TOK_OR,
  TOK_XOR,
  TOK_DOT,
  TOK_QUESTION,
  TOK_NOT,
  TOK_TILDA,
  TOK_LT,
  TOK_GT,
  TOK_LSHIFT,
  TOK_RSHIFT,
  TOK_MINUS_MINUS,
  TOK_PLUS_PLUS,
  TOK_PLUS_ASSIGN,
  TOK_MINUS_ASSIGN,
  TOK_MUL_ASSIGN,
  TOK_DIV_ASSIGN,
  TOK_AND_ASSIGN,
  TOK_OR_ASSIGN,
  TOK_REM_ASSIGN,
  TOK_XOR_ASSIGN,
  TOK_EQ,
  TOK_NE,
  TOK_LE,
  TOK_GE,
  TOK_LOGICAL_AND,
  TOK_LOGICAL_OR,
  TOK_EQ_EQ,
  TOK_NE_NE,
  TOK_LSHIFT_ASSIGN,
  TOK_RSHIFT_ASSIGN,
  TOK_URSHIFT,
  TOK_URSHIFT_ASSIGN,

  TOK_UNARY_PLUS,
  TOK_UNARY_MINUS,
  TOK_POSTFIX_PLUS,
  TOK_POSTFIX_MINUS,

  TOK_NUM = 200,
  TOK_STR,
  TOK_IDENT,
  TOK_KEYWORD_BERHENTI,
  TOK_KEYWORD_SAMA,
  TOK_KEYWORD_CATCH,
  TOK_KEYWORD_TERUSKAN,
  TOK_KEYWORD_DEBUGGER,
  TOK_KEYWORD_STANDAR,
  TOK_KEYWORD_DELETE,
  TOK_KEYWORD_KERJAKAN,
  TOK_KEYWORD_LAINNYA,
  TOK_KEYWORD_FALSE,
  TOK_KEYWORD_FINALLY,
  TOK_KEYWORD_UNTUK,
  TOK_KEYWORD_FUNGSI,
  TOK_KEYWORD_JIKA,
  TOK_KEYWORD_IN,
  TOK_KEYWORD_INSTANCEOF,
  TOK_KEYWORD_NEW,
  TOK_KEYWORD_KOSONG,
  TOK_KEYWORD_BALIK,
  TOK_KEYWORD_PILIH,
  TOK_KEYWORD_THIS,
  TOK_KEYWORD_THROW,
  TOK_KEYWORD_TRUE,
  TOK_KEYWORD_TRY,
  TOK_KEYWORD_TIPE,
  TOK_KEYWORD_VAR,
  TOK_KEYWORD_VOID,
  TOK_KEYWORD_ULANG,
  TOK_KEYWORD_WITH,
  TOK_KEYWORD_ISI,
  TOK_KEYWORD_TAKTERDEFINISI,
  TOK_MAX
};

BAIK_PRIVATE void pinit(const char *file_name, const char *buf, struct pstate *);
BAIK_PRIVATE int pnext(struct pstate *);
BAIK_PRIVATE int baik_is_ident(int c);
BAIK_PRIVATE int baik_is_digit(int c);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_DATAVIEW_H_
#define BAIK_DATAVIEW_H_

#if defined(__cplusplus)
extern "C" {
#endif

void *baik_mem_to_ptr(unsigned int val);
void *baik_mem_get_ptr(void *base, int offset);
void baik_mem_set_ptr(void *ptr, void *val);
double baik_mem_get_dbl(void *ptr);
void baik_mem_set_dbl(void *ptr, double val);
double baik_mem_get_uint(void *ptr, int size, int bigendian);
double baik_mem_get_int(void *ptr, int size, int bigendian);
void baik_mem_set_uint(void *ptr, unsigned int val, int size, int bigendian);
void baik_mem_set_int(void *ptr, int val, int size, int bigendian);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_EXEC_PUBLIC_H_
#define BAIK_EXEC_PUBLIC_H_


#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif
baik_err_t baik_exec(struct baik *, const char *src, baik_val_t *res);
baik_err_t baik_exec_buf(struct baik *, const char *src, size_t, baik_val_t *res);
baik_err_t baik_exec_file(struct baik *baik, const char *path, baik_val_t *res);
baik_err_t baik_apply(struct baik *baik, baik_val_t *res, baik_val_t func,
                    baik_val_t this_val, int nargs, baik_val_t *args);
baik_err_t baik_call(struct baik *baik, baik_val_t *res, baik_val_t func,
                   baik_val_t this_val, int nargs, ...);
baik_val_t baik_get_this(struct baik *baik);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_EXEC_H_
#define BAIK_EXEC_H_
#define BAIK_BCODE_OFFSET_EXIT ((size_t) 0x7fffffff)

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_err_t baik_execute(struct baik *baik, size_t off, baik_val_t *res);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_JSON_H_
#define BAIK_JSON_H_

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_err_t to_json_or_debug(struct baik *baik, baik_val_t v, char *buf,
                                       size_t size, size_t *res_len,
                                       uint8_t is_debug);
BAIK_PRIVATE baik_err_t baik_json_stringify(struct baik *baik, baik_val_t v,
                                         char *buf, size_t size, char **res);
BAIK_PRIVATE void baik_op_json_stringify(struct baik *baik);
BAIK_PRIVATE void baik_op_json_parse(struct baik *baik);
BAIK_PRIVATE baik_err_t
baik_json_parse(struct baik *baik, const char *str, size_t len, baik_val_t *res);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_BUILTIN_H_
#define BAIK_BUILTIN_H_

#if defined(__cplusplus)
extern "C" {
#endif

void baik_init_builtin(struct baik *baik, baik_val_t obj);

#if defined(__cplusplus)
}
#endif

#endif

#ifndef BAIK_PARSER_H
#define BAIK_PARSER_H

#if defined(__cplusplus)
extern "C" {
#endif

BAIK_PRIVATE baik_err_t
baik_parse(const char *path, const char *buf, struct baik *);

#if defined(__cplusplus)
}
#endif

#endif
#ifndef BAIK_EXPORT_INTERNAL_HEADERS

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

enum BAIK_EM_log_level BAIK_EM_log_level WEAK =
#if BAIK_EM_ENABLE_DEBUG
    LL_VERBOSE_DEBUG;
#else
    LL_ERROR;
#endif

#if BAIK_EM_ENABLE_STDIO
static char *s_file_level = NULL;
void BAIK_EM_log_set_file_level(const char *file_level) WEAK;
FILE *BAIK_EM_log_file WEAK = NULL;

#if BAIK_EM_LOG_ENABLE_TS_DIFF
double BAIK_EM_log_ts WEAK;
#endif

enum BAIK_EM_log_level BAIK_EM_log_cur_msg_level WEAK = LL_NONE;

void BAIK_EM_log_set_file_level(const char *file_level) {
  char *fl = s_file_level;
  if (file_level != NULL) {
    s_file_level = strdup(file_level);
  } else {
    s_file_level = NULL;
  }
  free(fl);
}

int BAIK_EM_log_print_prefix(enum BAIK_EM_log_level level, const char *file, int ln) WEAK;
int BAIK_EM_log_print_prefix(enum BAIK_EM_log_level level, const char *file, int ln) {
  char prefix[BAIK_EM_LOG_PREFIX_LEN], *q;
  const char *p;
  size_t fl = 0, ll = 0, pl = 0;

  if (level > BAIK_EM_log_level && s_file_level == NULL) return 0;
  p = file + strlen(file);

  while (p != file) {
    const char c = *(p - 1);
    if (c == '/' || c == '\\') break;
    p--;
    fl++;
  }

  ll = (ln < 10000 ? (ln < 1000 ? (ln < 100 ? (ln < 10 ? 1 : 2) : 3) : 4) : 5);
  if (fl > (sizeof(prefix) - ll - 2)) fl = (sizeof(prefix) - ll - 2);

  pl = fl + 1 + ll;
  memcpy(prefix, p, fl);
  q = prefix + pl;
  memset(q, ' ', sizeof(prefix) - pl);
  do {
    *(--q) = '0' + (ln % 10);
    ln /= 10;
  } while (ln > 0);
  *(--q) = ':';

  if (s_file_level != NULL) {
    enum BAIK_EM_log_level pll = BAIK_EM_log_level;
    struct baik_generic_str fl = baik_generic_mk_str(s_file_level), ps = GENERIC_MK_STR_N(prefix, pl);
    struct baik_generic_str k, v;
    while ((fl = baik_generic_next_comma_list_entry_n(fl, &k, &v)).p != NULL) {
      bool yes = !(!baik_generic_str_starts_with(ps, k) || v.len == 0);
      if (!yes) continue;
      pll = (enum BAIK_EM_log_level)(*v.p - '0');
      break;
    }
    if (level > pll) return 0;
  }

  if (BAIK_EM_log_file == NULL) BAIK_EM_log_file = stderr;
  BAIK_EM_log_cur_msg_level = level;
  fwrite(prefix, 1, sizeof(prefix), BAIK_EM_log_file);
#if BAIK_EM_LOG_ENABLE_TS_DIFF
  {
    double now = BAIK_EM_time();
    fprintf(BAIK_EM_log_file, "%7u ", (unsigned int) ((now - BAIK_EM_log_ts) * 1000000));
    BAIK_EM_log_ts = now;
  }
#endif
  return 1;
}

void BAIK_EM_log_printf(const char *fmt, ...) WEAK;
void BAIK_EM_log_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(BAIK_EM_log_file, fmt, ap);
  va_end(ap);
  fputc('\n', BAIK_EM_log_file);
  fflush(BAIK_EM_log_file);
  BAIK_EM_log_cur_msg_level = LL_NONE;
}

void BAIK_EM_log_set_file(FILE *file) WEAK;
void BAIK_EM_log_set_file(FILE *file) {
  BAIK_EM_log_file = file;
}

#else

void BAIK_EM_log_set_file_level(const char *file_level) {
  (void) file_level;
}

#endif

void BAIK_EM_log_set_level(enum BAIK_EM_log_level level) WEAK;
void BAIK_EM_log_set_level(enum BAIK_EM_log_level level) {
  BAIK_EM_log_level = level;
#if BAIK_EM_LOG_ENABLE_TS_DIFF && BAIK_EM_ENABLE_STDIO
  BAIK_EM_log_ts = BAIK_EM_time();
#endif
}

#include <stdio.h>
#include <stdlib.h>

#ifdef BAIK_EM_MMAP
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#endif

#ifndef EXCLUDE_COMMON
char *BAIK_EM_read_file(const char *path, size_t *size) WEAK;
char *BAIK_EM_read_file(const char *path, size_t *size) {
  FILE *fp;
  char *data = NULL;
  if ((fp = fopen(path, "rb")) == NULL) {
  } else if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
  } else {
    *size = ftell(fp);
    data = (char *) malloc(*size + 1);
    if (data != NULL) {
      fseek(fp, 0, SEEK_SET);
      if (fread(data, 1, *size, fp) != *size) {
        free(data);
        return NULL;
      }
      data[*size] = '\0';
    }
    fclose(fp);
  }
  return data;
}
#endif

#ifdef BAIK_EM_MMAP
char *BAIK_EM_mmap_file(const char *path, size_t *size) WEAK;
char *BAIK_EM_mmap_file(const char *path, size_t *size) {
  char *r;
  int fd = open(path, O_RDONLY, 0);
  struct stat st;
  if (fd < 0) return NULL;
  fstat(fd, &st);
  *size = (size_t) st.st_size;
  r = (char *) mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (r == MAP_FAILED) return NULL;
  return r;
}
#endif

size_t BAIK_EM_varint_llen(uint64_t num) {
  size_t llen = 0;

  do {
    llen++;
  } while (num >>= 7);

  return llen;
}

size_t BAIK_EM_varint_encode(uint64_t num, uint8_t *buf, size_t buf_size) {
  size_t llen = 0;

  do {
    uint8_t byte = num & 0x7f;
    num >>= 7;
    if (num != 0) byte |= 0x80;
    if (llen < buf_size) *buf++ = byte;
    llen++;
  } while (num != 0);

  return llen;
}

bool BAIK_EM_varint_decode(const uint8_t *buf, size_t buf_size, uint64_t *num,
                      size_t *llen) {
  size_t i = 0, shift = 0;
  uint64_t n = 0;

  do {
    if (i == buf_size || i == (8 * sizeof(*num) / 7 + 1)) return false;
   
    n |= ((uint64_t)(buf[i] & 0x7f)) << shift;
   
    i++;
    shift += 7;
  } while (shift < sizeof(uint64_t) * 8 && (buf[i - 1] & 0x80));

  *num = n;
  *llen = i;

  return true;
}

uint64_t BAIK_EM_varint_decode_unsafe(const uint8_t *buf, int *llen) {
  uint64_t v;
  size_t l;
  BAIK_EM_varint_decode(buf, ~0, &v, &l);
  *llen = l;
  return v;
}

#ifndef EXCLUDE_COMMON

#include <assert.h>
#include <string.h>

#ifndef MBUF_REALLOC
#define MBUF_REALLOC realloc
#endif

#ifndef MBUF_FREE
#define MBUF_FREE free
#endif

void mbuf_init(struct mbuf *mbuf, size_t initial_size) WEAK;
void mbuf_init(struct mbuf *mbuf, size_t initial_size) {
  mbuf->len = mbuf->size = 0;
  mbuf->buf = NULL;
  mbuf_resize(mbuf, initial_size);
}

void mbuf_free(struct mbuf *mbuf) WEAK;
void mbuf_free(struct mbuf *mbuf) {
  if (mbuf->buf != NULL) {
    MBUF_FREE(mbuf->buf);
    mbuf_init(mbuf, 0);
  }
}

void mbuf_resize(struct mbuf *a, size_t new_size) WEAK;
void mbuf_resize(struct mbuf *a, size_t new_size) {
  if (new_size > a->size || (new_size < a->size && new_size >= a->len)) {
    char *buf = (char *) MBUF_REALLOC(a->buf, new_size);

    if (buf == NULL && new_size != 0) return;
    a->buf = buf;
    a->size = new_size;
  }
}

void mbuf_trim(struct mbuf *mbuf) WEAK;
void mbuf_trim(struct mbuf *mbuf) {
  mbuf_resize(mbuf, mbuf->len);
}

size_t mbuf_insert(struct mbuf *a, size_t off, const void *buf, size_t) WEAK;
size_t mbuf_insert(struct mbuf *a, size_t off, const void *buf, size_t len) {
  char *p = NULL;

  assert(a != NULL);
  assert(a->len <= a->size);
  assert(off <= a->len);

  if (~(size_t) 0 - (size_t) a->buf < len) return 0;

  if (a->len + len <= a->size) {
    memmove(a->buf + off + len, a->buf + off, a->len - off);
    if (buf != NULL) {
      memcpy(a->buf + off, buf, len);
    }
    a->len += len;
  } else {
    size_t min_size = (a->len + len);
    size_t new_size = (size_t)(min_size * MBUF_SIZE_MULTIPLIER);
    if (new_size - min_size > MBUF_SIZE_MAX_HEADROOM) {
      new_size = min_size + MBUF_SIZE_MAX_HEADROOM;
    }
    p = (char *) MBUF_REALLOC(a->buf, new_size);
    if (p == NULL && new_size != min_size) {
      new_size = min_size;
      p = (char *) MBUF_REALLOC(a->buf, new_size);
    }
    if (p != NULL) {
      a->buf = p;
      if (off != a->len) {
        memmove(a->buf + off + len, a->buf + off, a->len - off);
      }
      if (buf != NULL) memcpy(a->buf + off, buf, len);
      a->len += len;
      a->size = new_size;
    } else {
      len = 0;
    }
  }

  return len;
}

size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) WEAK;
size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) {
  return mbuf_insert(a, a->len, buf, len);
}

size_t mbuf_append_and_free(struct mbuf *a, void *buf, size_t len) WEAK;
size_t mbuf_append_and_free(struct mbuf *a, void *data, size_t len) {
  size_t ret;
 
  if (a->len == 0) {
    if (a->buf != NULL) free(a->buf);
    a->buf = (char *) data;
    a->len = a->size = len;
    return len;
  }
  ret = mbuf_insert(a, a->len, data, len);
  free(data);
  return ret;
}

void mbuf_remove(struct mbuf *mb, size_t n) WEAK;
void mbuf_remove(struct mbuf *mb, size_t n) {
  if (n > 0 && n <= mb->len) {
    memmove(mb->buf, mb->buf + n, mb->len - n);
    mb->len -= n;
  }
}

void mbuf_clear(struct mbuf *mb) WEAK;
void mbuf_clear(struct mbuf *mb) {
  mb->len = 0;
}

void mbuf_move(struct mbuf *from, struct mbuf *to) WEAK;
void mbuf_move(struct mbuf *from, struct mbuf *to) {
  memcpy(to, from, sizeof(*to));
  memset(from, 0, sizeof(*from));
}

#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int baik_generic_ncasecmp(const char *s1, const char *s2, size_t len) WEAK;
struct baik_generic_str baik_generic_mk_str(const char *s) WEAK;
struct baik_generic_str baik_generic_mk_str(const char *s) {
  struct baik_generic_str ret = {s, 0};
  if (s != NULL) ret.len = strlen(s);
  return ret;
}

struct baik_generic_str baik_generic_mk_str_n(const char *s, size_t len) WEAK;
struct baik_generic_str baik_generic_mk_str_n(const char *s, size_t len) {
  struct baik_generic_str ret = {s, len};
  return ret;
}

int baik_generic_vcmp(const struct baik_generic_str *str1, const char *str2) WEAK;
int baik_generic_vcmp(const struct baik_generic_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = strncmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

int baik_generic_vcasecmp(const struct baik_generic_str *str1, const char *str2) WEAK;
int baik_generic_vcasecmp(const struct baik_generic_str *str1, const char *str2) {
  size_t n2 = strlen(str2), n1 = str1->len;
  int r = baik_generic_ncasecmp(str1->p, str2, (n1 < n2) ? n1 : n2);
  if (r == 0) {
    return n1 - n2;
  }
  return r;
}

static struct baik_generic_str baik_generic_strdup_common(const struct baik_generic_str s,
                                      int nul_terminate) {
  struct baik_generic_str r = {NULL, 0};
  if (s.len > 0 && s.p != NULL) {
    char *sc = (char *) GENERIC_MALLOC(s.len + (nul_terminate ? 1 : 0));
    if (sc != NULL) {
      memcpy(sc, s.p, s.len);
      if (nul_terminate) sc[s.len] = '\0';
      r.p = sc;
      r.len = s.len;
    }
  }
  return r;
}

struct baik_generic_str baik_generic_strdup(const struct baik_generic_str s) WEAK;
struct baik_generic_str baik_generic_strdup(const struct baik_generic_str s) {
  return baik_generic_strdup_common(s, 0);
}

struct baik_generic_str baik_generic_strdup_nul(const struct baik_generic_str s) WEAK;
struct baik_generic_str baik_generic_strdup_nul(const struct baik_generic_str s) {
  return baik_generic_strdup_common(s, 1);
}

const char *baik_generic_strchr(const struct baik_generic_str s, int c) WEAK;
const char *baik_generic_strchr(const struct baik_generic_str s, int c) {
  size_t i;
  for (i = 0; i < s.len; i++) {
    if (s.p[i] == c) return &s.p[i];
  }
  return NULL;
}

int baik_generic_strcmp(const struct baik_generic_str str1, const struct baik_generic_str str2) WEAK;
int baik_generic_strcmp(const struct baik_generic_str str1, const struct baik_generic_str str2) {
  size_t i = 0;
  while (i < str1.len && i < str2.len) {
    if (str1.p[i] < str2.p[i]) return -1;
    if (str1.p[i] > str2.p[i]) return 1;
    i++;
  }
  if (i < str1.len) return 1;
  if (i < str2.len) return -1;
  return 0;
}

int baik_generic_strncmp(const struct baik_generic_str, const struct baik_generic_str, size_t n) WEAK;
int baik_generic_strncmp(const struct baik_generic_str str1, const struct baik_generic_str str2, size_t n) {
  struct baik_generic_str s1 = str1;
  struct baik_generic_str s2 = str2;

  if (s1.len > n) {
    s1.len = n;
  }
  if (s2.len > n) {
    s2.len = n;
  }
  return baik_generic_strcmp(s1, s2);
}

void baik_generic_strfree(struct baik_generic_str *s) WEAK;
void baik_generic_strfree(struct baik_generic_str *s) {
  char *sp = (char *) s->p;
  s->p = NULL;
  s->len = 0;
  if (sp != NULL) free(sp);
}

const char *baik_generic_strstr(const struct baik_generic_str haystack,
                      const struct baik_generic_str needle) WEAK;
const char *baik_generic_strstr(const struct baik_generic_str haystack,
                      const struct baik_generic_str needle) {
  size_t i;
  if (needle.len > haystack.len) return NULL;
  for (i = 0; i <= haystack.len - needle.len; i++) {
    if (memcmp(haystack.p + i, needle.p, needle.len) == 0) {
      return haystack.p + i;
    }
  }
  return NULL;
}

struct baik_generic_str baik_generic_strstrip(struct baik_generic_str s) WEAK;
struct baik_generic_str baik_generic_strstrip(struct baik_generic_str s) {
  while (s.len > 0 && isspace((int) *s.p)) {
    s.p++;
    s.len--;
  }
  while (s.len > 0 && isspace((int) *(s.p + s.len - 1))) {
    s.len--;
  }
  return s;
}

int baik_generic_str_starts_with(struct baik_generic_str s, struct baik_generic_str prefix) WEAK;
int baik_generic_str_starts_with(struct baik_generic_str s, struct baik_generic_str prefix) {
  const struct baik_generic_str sp = GENERIC_MK_STR_N(s.p, prefix.len);
  if (s.len < prefix.len) return 0;
  return (baik_generic_strcmp(sp, prefix) == 0);
}

#ifndef EXCLUDE_COMMON

#ifndef C_DISABLE_BUILTIN_SNPRINTF
#define C_DISABLE_BUILTIN_SNPRINTF 0
#endif

size_t c_strnlen(const char *s, size_t maxlen) WEAK;
size_t c_strnlen(const char *s, size_t maxlen) {
  size_t l = 0;
  for (; l < maxlen && s[l] != '\0'; l++) {
  }
  return l;
}

#define C_SNPRINTF_APPEND_CHAR(ch)       \
  do {                                   \
    if (i < (int) buf_size) buf[i] = ch; \
    i++;                                 \
  } while (0)

#define C_SNPRINTF_FLAG_ZERO 1

#if C_DISABLE_BUILTIN_SNPRINTF
int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) WEAK;
int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) {
  return vsnprintf(buf, buf_size, fmt, ap);
}
#else
static int c_itoa(char *buf, size_t buf_size, int64_t num, int base, int flags,
                  int field_width) {
  char tmp[40];
  int i = 0, k = 0, neg = 0;

  if (num < 0) {
    neg++;
    num = -num;
  }

  do {
    int rem = num % base;
    if (rem < 10) {
      tmp[k++] = '0' + rem;
    } else {
      tmp[k++] = 'a' + (rem - 10);
    }
    num /= base;
  } while (num > 0);

  if (flags && C_SNPRINTF_FLAG_ZERO) {
    while (k < field_width && k < (int) sizeof(tmp) - 1) {
      tmp[k++] = '0';
    }
  }

  if (neg) {
    tmp[k++] = '-';
  }

  while (--k >= 0) {
    C_SNPRINTF_APPEND_CHAR(tmp[k]);
  }

  return i;
}

int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) WEAK;
int c_vsnprintf(char *buf, size_t buf_size, const char *fmt, va_list ap) {
  int ch, i = 0, len_mod, flags, precision, field_width;

  while ((ch = *fmt++) != '\0') {
    if (ch != '%') {
      C_SNPRINTF_APPEND_CHAR(ch);
    } else {
     
      flags = field_width = precision = len_mod = 0;

      if (*fmt == '0') {
        flags |= C_SNPRINTF_FLAG_ZERO;
      }

      while (*fmt >= '0' && *fmt <= '9') {
        field_width *= 10;
        field_width += *fmt++ - '0';
      }
     
      if (*fmt == '*') {
        field_width = va_arg(ap, int);
        fmt++;
      }

      if (*fmt == '.') {
        fmt++;
        if (*fmt == '*') {
          precision = va_arg(ap, int);
          fmt++;
        } else {
          while (*fmt >= '0' && *fmt <= '9') {
            precision *= 10;
            precision += *fmt++ - '0';
          }
        }
      }

      switch (*fmt) {
        case 'h':
        case 'l':
        case 'L':
        case 'I':
        case 'q':
        case 'j':
        case 'z':
        case 't':
          len_mod = *fmt++;
          if (*fmt == 'h') {
            len_mod = 'H';
            fmt++;
          }
          if (*fmt == 'l') {
            len_mod = 'q';
            fmt++;
          }
          break;
      }

      ch = *fmt++;
      if (ch == 's') {
        const char *s = va_arg(ap, const char *);
        int j;
        int pad = field_width - (precision >= 0 ? c_strnlen(s, precision) : 0);
        for (j = 0; j < pad; j++) {
          C_SNPRINTF_APPEND_CHAR(' ');
        }

       
        if (s != NULL) {
         
          for (j = 0; (precision <= 0 || j < precision) && s[j] != '\0'; j++) {
            C_SNPRINTF_APPEND_CHAR(s[j]);
          }
        }
      } else if (ch == 'c') {
        ch = va_arg(ap, int);
        C_SNPRINTF_APPEND_CHAR(ch);
      } else if (ch == 'd' && len_mod == 0) {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, int), 10, flags,
                    field_width);
      } else if (ch == 'd' && len_mod == 'l') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, long), 10, flags,
                    field_width);
#ifdef SSIZE_MAX
      } else if (ch == 'd' && len_mod == 'z') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, ssize_t), 10, flags,
                    field_width);
#endif
      } else if (ch == 'd' && len_mod == 'q') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, int64_t), 10, flags,
                    field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 0) {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, unsigned),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 'l') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, unsigned long),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if ((ch == 'x' || ch == 'u') && len_mod == 'z') {
        i += c_itoa(buf + i, buf_size - i, va_arg(ap, size_t),
                    ch == 'x' ? 16 : 10, flags, field_width);
      } else if (ch == 'p') {
        unsigned long num = (unsigned long) (uintptr_t) va_arg(ap, void *);
        C_SNPRINTF_APPEND_CHAR('0');
        C_SNPRINTF_APPEND_CHAR('x');
        i += c_itoa(buf + i, buf_size - i, num, 16, flags, 0);
      } else {
#ifndef NO_LIBC
       
        abort();
#endif
      }
    }
  }

  if (buf_size > 0) {
    buf[i < (int) buf_size ? i : (int) buf_size - 1] = '\0';
  }

  return i;
}
#endif

int c_snprintf(char *buf, size_t buf_size, const char *fmt, ...) WEAK;
int c_snprintf(char *buf, size_t buf_size, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = c_vsnprintf(buf, buf_size, fmt, ap);
  va_end(ap);
  return result;
}

#ifdef _WIN32
int to_wchar(const char *path, wchar_t *wbuf, size_t wbuf_len) {
  int ret;
  char buf[MAX_PATH * 2], buf2[MAX_PATH * 2], *p;

  strncpy(buf, path, sizeof(buf));
  buf[sizeof(buf) - 1] = '\0';

  p = buf + strlen(buf) - 1;
  while (p > buf && p[-1] != ':' && (p[0] == '\\' || p[0] == '/')) *p-- = '\0';

  memset(wbuf, 0, wbuf_len * sizeof(wchar_t));
  ret = MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, (int) wbuf_len);

  WideCharToMultiByte(CP_UTF8, 0, wbuf, (int) wbuf_len, buf2, sizeof(buf2),
                      NULL, NULL);
  if (strcmp(buf, buf2) != 0) {
    wbuf[0] = L'\0';
    ret = 0;
  }

  return ret;
}
#endif


const char *c_strnstr(const char *s, const char *find, size_t slen) WEAK;
const char *c_strnstr(const char *s, const char *find, size_t slen) {
  size_t find_length = strlen(find);
  size_t i;

  for (i = 0; i < slen; i++) {
    if (i + find_length > slen) {
      return NULL;
    }

    if (strncmp(&s[i], find, find_length) == 0) {
      return &s[i];
    }
  }

  return NULL;
}

#if BAIK_EM_ENABLE_STRDUP
char *strdup(const char *src) WEAK;
char *strdup(const char *src) {
  size_t len = strlen(src) + 1;
  char *ret = GENERIC_MALLOC(len);
  if (ret != NULL) {
    strcpy(ret, src);
  }
  return ret;
}
#endif

void BAIK_EM_to_hex(char *to, const unsigned char *p, size_t len) WEAK;
void BAIK_EM_to_hex(char *to, const unsigned char *p, size_t len) {
  static const char *hex = "0123456789abcdef";

  for (; len--; p++) {
    *to++ = hex[p[0] >> 4];
    *to++ = hex[p[0] & 0x0f];
  }

  *to = '\0';
}

static int fourbit(int ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  } else if (ch >= 'a' && ch <= 'f') {
    return ch - 'a' + 10;
  } else if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  }
  return 0;
}

void BAIK_EM_from_hex(char *to, const char *p, size_t len) WEAK;
void BAIK_EM_from_hex(char *to, const char *p, size_t len) {
  size_t i;

  for (i = 0; i < len; i += 2) {
    *to++ = (fourbit(p[i]) << 4) + fourbit(p[i + 1]);
  }
  *to = '\0';
}

#if BAIK_EM_ENABLE_TO64
int64_t BAIK_EM_to64(const char *s) WEAK;
int64_t BAIK_EM_to64(const char *s) {
  int64_t result = 0;
  int64_t neg = 1;
  while (*s && isspace((unsigned char) *s)) s++;
  if (*s == '-') {
    neg = -1;
    s++;
  }
  while (isdigit((unsigned char) *s)) {
    result *= 10;
    result += (*s - '0');
    s++;
  }
  return result * neg;
}
#endif

static int str_util_lowercase(const char *s) {
  return tolower(*(const unsigned char *) s);
}

int baik_generic_ncasecmp(const char *s1, const char *s2, size_t len) WEAK;
int baik_generic_ncasecmp(const char *s1, const char *s2, size_t len) {
  int diff = 0;

  if (len > 0) do {
      diff = str_util_lowercase(s1++) - str_util_lowercase(s2++);
    } while (diff == 0 && s1[-1] != '\0' && --len > 0);

  return diff;
}

int baik_generic_casecmp(const char *s1, const char *s2) WEAK;
int baik_generic_casecmp(const char *s1, const char *s2) {
  return baik_generic_ncasecmp(s1, s2, (size_t) ~0);
}

int baik_generic_asprintf(char **buf, size_t size, const char *fmt, ...) WEAK;
int baik_generic_asprintf(char **buf, size_t size, const char *fmt, ...) {
  int ret;
  va_list ap;
  va_start(ap, fmt);
  ret = baik_generic_avprintf(buf, size, fmt, ap);
  va_end(ap);
  return ret;
}

int baik_generic_avprintf(char **buf, size_t size, const char *fmt, va_list ap) WEAK;
int baik_generic_avprintf(char **buf, size_t size, const char *fmt, va_list ap) {
  va_list ap_copy;
  int len;

  va_copy(ap_copy, ap);
  len = vsnprintf(*buf, size, fmt, ap_copy);
  va_end(ap_copy);

  if (len < 0) {
   
    *buf = NULL;
    while (len < 0) {
      GENERIC_FREE(*buf);
      if (size == 0) {
        size = 5;
      }
      size *= 2;
      if ((*buf = (char *) GENERIC_MALLOC(size)) == NULL) {
        len = -1;
        break;
      }
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, size - 1, fmt, ap_copy);
      va_end(ap_copy);
    }

    (*buf)[len] = 0;
   
  } else if (len >= (int) size) {
   
    if ((*buf = (char *) GENERIC_MALLOC(len + 1)) == NULL) {
      len = -1;
    } else {   
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, len + 1, fmt, ap_copy);
      va_end(ap_copy);
    }
  }

  return len;
}

const char *baik_generic_next_comma_list_entry(const char *, struct baik_generic_str *,
                                     struct baik_generic_str *) WEAK;
const char *baik_generic_next_comma_list_entry(const char *list, struct baik_generic_str *val,
                                     struct baik_generic_str *eq_val) {
  struct baik_generic_str ret = baik_generic_next_comma_list_entry_n(baik_generic_mk_str(list), val, eq_val);
  return ret.p;
}
struct baik_generic_str baik_generic_next_comma_list_entry_n(struct baik_generic_str list, struct baik_generic_str *val,
                                         struct baik_generic_str *eq_val) WEAK;
struct baik_generic_str baik_generic_next_comma_list_entry_n(struct baik_generic_str list, struct baik_generic_str *val,
                                         struct baik_generic_str *eq_val) {
  if (list.len == 0) {
    list = baik_generic_mk_str(NULL);
  } else {
    const char *chr = NULL;
    *val = list;

    if ((chr = baik_generic_strchr(*val, ',')) != NULL) {
      val->len = chr - val->p;
      chr++;
      list.len -= (chr - list.p);
      list.p = chr;
    } else {
      list = baik_generic_mk_str_n(list.p + list.len, 0);
    }

    if (eq_val != NULL) {
      eq_val->len = 0;
      eq_val->p = (const char *) memchr(val->p, '=', val->len);
      if (eq_val->p != NULL) {
        eq_val->p++;
        eq_val->len = val->p + val->len - eq_val->p;
        val->len = (eq_val->p - val->p) - 1;
      }
    }
  }

  return list;
}

size_t baik_generic_match_prefix_n(const struct baik_generic_str, const struct baik_generic_str) WEAK;
size_t baik_generic_match_prefix_n(const struct baik_generic_str pattern, const struct baik_generic_str str) {
  const char *or_str;
  size_t res = 0, len = 0, i = 0, j = 0;

  if ((or_str = (const char *) memchr(pattern.p, '|', pattern.len)) != NULL ||
      (or_str = (const char *) memchr(pattern.p, ',', pattern.len)) != NULL) {
    struct baik_generic_str pstr = {pattern.p, (size_t)(or_str - pattern.p)};
    res = baik_generic_match_prefix_n(pstr, str);
    if (res > 0) return res;
    pstr.p = or_str + 1;
    pstr.len = (pattern.p + pattern.len) - (or_str + 1);
    return baik_generic_match_prefix_n(pstr, str);
  }

  for (; i < pattern.len && j < str.len; i++, j++) {
    if (pattern.p[i] == '?') {
      continue;
    } else if (pattern.p[i] == '*') {
      i++;
      if (i < pattern.len && pattern.p[i] == '*') {
        i++;
        len = str.len - j;
      } else {
        len = 0;
        while (j + len < str.len && str.p[j + len] != '/') len++;
      }
      if (i == pattern.len || (pattern.p[i] == '$' && i == pattern.len - 1))
        return j + len;
      do {
        const struct baik_generic_str pstr = {pattern.p + i, pattern.len - i};
        const struct baik_generic_str sstr = {str.p + j + len, str.len - j - len};
        res = baik_generic_match_prefix_n(pstr, sstr);
      } while (res == 0 && len != 0 && len-- > 0);
      return res == 0 ? 0 : j + res + len;
    } else if (str_util_lowercase(&pattern.p[i]) !=
               str_util_lowercase(&str.p[j])) {
      break;
    }
  }
  if (i < pattern.len && pattern.p[i] == '$') {
    return j == str.len ? str.len : 0;
  }
  return i == pattern.len ? j : 0;
}

size_t baik_generic_match_prefix(const char *, int, const char *) WEAK;
size_t baik_generic_match_prefix(const char *pattern, int pattern_len, const char *str) {
  const struct baik_generic_str pstr = {pattern, (size_t) pattern_len};
  struct baik_generic_str s = {str, 0};
  if (str != NULL) s.len = strlen(str);
  return baik_generic_match_prefix_n(pstr, s);
}

#endif

#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(WEAK)
#if (defined(__GNUC__) || defined(__TI_COMPILER_VERSION__)) && !defined(_WIN32)
#define WEAK __attribute__((weak))
#else
#define WEAK
#endif
#endif

#ifdef _WIN32
#undef snprintf
#undef vsnprintf
#define snprintf BAIK_EM_win_snprintf
#define vsnprintf BAIK_EM_win_vsnprintf
int BAIK_EM_win_snprintf(char *str, size_t size, const char *format, ...);
int BAIK_EM_win_vsnprintf(char *str, size_t size, const char *format, va_list ap);
#if _MSC_VER >= 1700
#include <stdint.h>
#else
typedef _int64 int64_t;
typedef unsigned _int64 uint64_t;
#endif
#define PRId64 "I64d"
#define PRIu64 "I64u"
#else

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#endif

#ifndef INT64_FMT
#define INT64_FMT PRId64
#endif
#ifndef UINT64_FMT
#define UINT64_FMT PRIu64
#endif

#ifndef va_copy
#define va_copy(x, y) x = y
#endif

#ifndef JSON_ENABLE_ARRAY
#define JSON_ENABLE_ARRAY 1
#endif

struct frozen {
  const char *end;
  const char *cur;

  const char *cur_name;
  size_t cur_name_len;

  char path[JSON_MAX_PATH_LEN];
  size_t path_len;
  void *callback_data;
  json_walk_callback_t callback;
};

struct fstate {
  const char *ptr;
  size_t path_len;
};

#define SET_STATE(fr, ptr, str, len)              \
  struct fstate fstate = {(ptr), (fr)->path_len}; \
  json_append_to_path((fr), (str), (len));

#define CALL_BACK(fr, tok, value, len)                                        \
  do {                                                                        \
    if ((fr)->callback &&                                                     \
        ((fr)->path_len == 0 || (fr)->path[(fr)->path_len - 1] != '.')) {     \
      struct json_token t = {(value), (int) (len), (tok)};                    \
                                                                              \
                \
      (fr)->callback((fr)->callback_data, (fr)->cur_name, (fr)->cur_name_len, \
                     (fr)->path, &t);                                         \
                                                                              \
                                                         \
      (fr)->cur_name = NULL;                                                  \
      (fr)->cur_name_len = 0;                                                 \
    }                                                                         \
  } while (0)

static int json_append_to_path(struct frozen *f, const char *str, int size) {
  int n = f->path_len;
  int left = sizeof(f->path) - n - 1;
  if (size > left) size = left;
  memcpy(f->path + n, str, size);
  f->path[n + size] = '\0';
  f->path_len += size;
  return n;
}

static void json_truncate_path(struct frozen *f, size_t len) {
  f->path_len = len;
  f->path[len] = '\0';
}

static int json_parse_object(struct frozen *f);
static int json_parse_value(struct frozen *f);

#define EXPECT(cond, err_code)      \
  do {                              \
    if (!(cond)) return (err_code); \
  } while (0)

#define TRY(expr)          \
  do {                     \
    int _n = expr;         \
    if (_n < 0) return _n; \
  } while (0)

#define END_OF_STRING (-1)

static int json_left(const struct frozen *f) {
  return f->end - f->cur;
}

static int json_isspace(int ch) {
  return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

static void json_skip_whitespaces(struct frozen *f) {
  while (f->cur < f->end && json_isspace(*f->cur)) f->cur++;
}

static int json_cur(struct frozen *f) {
  json_skip_whitespaces(f);
  return f->cur >= f->end ? END_OF_STRING : *(unsigned char *) f->cur;
}

static int json_test_and_skip(struct frozen *f, int expected) {
  int ch = json_cur(f);
  if (ch == expected) {
    f->cur++;
    return 0;
  }
  return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
}

static int json_isalpha(int ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static int json_isdigit(int ch) {
  return ch >= '0' && ch <= '9';
}

static int json_isxdigit(int ch) {
  return json_isdigit(ch) || (ch >= 'a' && ch <= 'f') ||
         (ch >= 'A' && ch <= 'F');
}

static int json_get_escape_len(const char *s, int len) {
  switch (*s) {
    case 'u':
      return len < 6 ? JSON_STRING_INCOMPLETE
                     : json_isxdigit(s[1]) && json_isxdigit(s[2]) &&
                               json_isxdigit(s[3]) && json_isxdigit(s[4])
                           ? 5
                           : JSON_STRING_INVALID;
    case '"':
    case '\\':
    case '/':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
      return len < 2 ? JSON_STRING_INCOMPLETE : 1;
    default:
      return JSON_STRING_INVALID;
  }
}

static int json_parse_identifier(struct frozen *f) {
  EXPECT(json_isalpha(json_cur(f)), JSON_STRING_INVALID);
  {
    SET_STATE(f, f->cur, "", 0);
    while (f->cur < f->end &&
           (*f->cur == '_' || json_isalpha(*f->cur) || json_isdigit(*f->cur))) {
      f->cur++;
    }
    json_truncate_path(f, fstate.path_len);
    CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
  }
  return 0;
}

static int json_get_utf8_char_len(unsigned char ch) {
  if ((ch & 0x80) == 0) return 1;
  switch (ch & 0xf0) {
    case 0xf0:
      return 4;
    case 0xe0:
      return 3;
    default:
      return 2;
  }
}

static int json_parse_string(struct frozen *f) {
  int n, ch = 0, len = 0;
  TRY(json_test_and_skip(f, '"'));
  {
    SET_STATE(f, f->cur, "", 0);
    for (; f->cur < f->end; f->cur += len) {
      ch = *(unsigned char *) f->cur;
      len = json_get_utf8_char_len((unsigned char) ch);
      EXPECT(ch >= 32 && len > 0, JSON_STRING_INVALID);
      EXPECT(len <= json_left(f), JSON_STRING_INCOMPLETE);
      if (ch == '\\') {
        EXPECT((n = json_get_escape_len(f->cur + 1, json_left(f))) > 0, n);
        len += n;
      } else if (ch == '"') {
        json_truncate_path(f, fstate.path_len);
        CALL_BACK(f, JSON_TYPE_STRING, fstate.ptr, f->cur - fstate.ptr);
        f->cur++;
        break;
      };
    }
  }
  return ch == '"' ? 0 : JSON_STRING_INCOMPLETE;
}

static int json_parse_number(struct frozen *f) {
  int ch = json_cur(f);
  SET_STATE(f, f->cur, "", 0);
  if (ch == '-') f->cur++;
  EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
  if (f->cur + 1 < f->end && f->cur[0] == '0' && f->cur[1] == 'x') {
    f->cur += 2;
    EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
    EXPECT(json_isxdigit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && json_isxdigit(f->cur[0])) f->cur++;
  } else {
    EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
    while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    if (f->cur < f->end && f->cur[0] == '.') {
      f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
      while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    }
    if (f->cur < f->end && (f->cur[0] == 'e' || f->cur[0] == 'E')) {
      f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      if ((f->cur[0] == '+' || f->cur[0] == '-')) f->cur++;
      EXPECT(f->cur < f->end, JSON_STRING_INCOMPLETE);
      EXPECT(json_isdigit(f->cur[0]), JSON_STRING_INVALID);
      while (f->cur < f->end && json_isdigit(f->cur[0])) f->cur++;
    }
  }
  json_truncate_path(f, fstate.path_len);
  CALL_BACK(f, JSON_TYPE_NUMBER, fstate.ptr, f->cur - fstate.ptr);
  return 0;
}

#if JSON_ENABLE_ARRAY

static int json_parse_array(struct frozen *f) {
  int i = 0, current_path_len;
  char buf[20];
  CALL_BACK(f, JSON_TYPE_ARRAY_START, NULL, 0);
  TRY(json_test_and_skip(f, '['));
  {
    {
      SET_STATE(f, f->cur - 1, "", 0);
      while (json_cur(f) != ']') {
        snprintf(buf, sizeof(buf), "[%d]", i);
        i++;
        current_path_len = json_append_to_path(f, buf, strlen(buf));
        f->cur_name =
            f->path + strlen(f->path) - strlen(buf) + 1;
        f->cur_name_len = strlen(buf) - 2;
        TRY(json_parse_value(f));
        json_truncate_path(f, current_path_len);
        if (json_cur(f) == ',') f->cur++;
      }
      TRY(json_test_and_skip(f, ']'));
      json_truncate_path(f, fstate.path_len);
      CALL_BACK(f, JSON_TYPE_ARRAY_END, fstate.ptr, f->cur - fstate.ptr);
    }
  }
  return 0;
}
#endif

static int json_expect(struct frozen *f, const char *s, int len,
                       enum json_token_type tok_type) {
  int i, n = json_left(f);
  SET_STATE(f, f->cur, "", 0);
  for (i = 0; i < len; i++) {
    if (i >= n) return JSON_STRING_INCOMPLETE;
    if (f->cur[i] != s[i]) return JSON_STRING_INVALID;
  }
  f->cur += len;
  json_truncate_path(f, fstate.path_len);

  CALL_BACK(f, tok_type, fstate.ptr, f->cur - fstate.ptr);

  return 0;
}

static int json_parse_value(struct frozen *f) {
  int ch = json_cur(f);

  switch (ch) {
    case '"':
      TRY(json_parse_string(f));
      break;
    case '{':
      TRY(json_parse_object(f));
      break;
#if JSON_ENABLE_ARRAY
    case '[':
      TRY(json_parse_array(f));
      break;
#endif
    case 'n':
      TRY(json_expect(f, "kosong", 4, JSON_TYPE_NULL));
      break;
    case 't':
      TRY(json_expect(f, "benar", 4, JSON_TYPE_TRUE));
      break;
    case 'f':
      TRY(json_expect(f, "salah", 5, JSON_TYPE_FALSE));
      break;
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      TRY(json_parse_number(f));
      break;
    default:
      return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }

  return 0;
}


static int json_parse_key(struct frozen *f) {
  int ch = json_cur(f);
  if (json_isalpha(ch)) {
    TRY(json_parse_identifier(f));
  } else if (ch == '"') {
    TRY(json_parse_string(f));
  } else {
    return ch == END_OF_STRING ? JSON_STRING_INCOMPLETE : JSON_STRING_INVALID;
  }
  return 0;
}


static int json_parse_pair(struct frozen *f) {
  int current_path_len;
  const char *tok;
  json_skip_whitespaces(f);
  tok = f->cur;
  TRY(json_parse_key(f));
  {
    f->cur_name = *tok == '"' ? tok + 1 : tok;
    f->cur_name_len = *tok == '"' ? f->cur - tok - 2 : f->cur - tok;
    current_path_len = json_append_to_path(f, f->cur_name, f->cur_name_len);
  }
  TRY(json_test_and_skip(f, ':'));
  TRY(json_parse_value(f));
  json_truncate_path(f, current_path_len);
  return 0;
}


static int json_parse_object(struct frozen *f) {
  CALL_BACK(f, JSON_TYPE_OBJECT_START, NULL, 0);
  TRY(json_test_and_skip(f, '{'));
  {
    SET_STATE(f, f->cur - 1, ".", 1);
    while (json_cur(f) != '}') {
      TRY(json_parse_pair(f));
      if (json_cur(f) == ',') f->cur++;
    }
    TRY(json_test_and_skip(f, '}'));
    json_truncate_path(f, fstate.path_len);
    CALL_BACK(f, JSON_TYPE_OBJECT_END, fstate.ptr, f->cur - fstate.ptr);
  }
  return 0;
}

static int json_doit(struct frozen *f) {
  if (f->cur == 0 || f->end < f->cur) return JSON_STRING_INVALID;
  if (f->end == f->cur) return JSON_STRING_INCOMPLETE;
  return json_parse_value(f);
}

int json_escape(struct json_out *out, const char *p, size_t len) WEAK;
int json_escape(struct json_out *out, const char *p, size_t len) {
  size_t i, cl, n = 0;
  const char *hex_digits = "0123456789abcdef";
  const char *specials = "btnvfr";

  for (i = 0; i < len; i++) {
    unsigned char ch = ((unsigned char *) p)[i];
    if (ch == '"' || ch == '\\') {
      n += out->printer(out, "\\", 1);
      n += out->printer(out, p + i, 1);
    } else if (ch >= '\b' && ch <= '\r') {
      n += out->printer(out, "\\", 1);
      n += out->printer(out, &specials[ch - '\b'], 1);
    } else if (isprint(ch)) {
      n += out->printer(out, p + i, 1);
    } else if ((cl = json_get_utf8_char_len(ch)) == 1) {
      n += out->printer(out, "\\u00", 4);
      n += out->printer(out, &hex_digits[(ch >> 4) % 0xf], 1);
      n += out->printer(out, &hex_digits[ch % 0xf], 1);
    } else {
      n += out->printer(out, p + i, cl);
      i += cl - 1;
    }
  }

  return n;
}

int json_printer_buf(struct json_out *out, const char *buf, size_t len) WEAK;
int json_printer_buf(struct json_out *out, const char *buf, size_t len) {
  size_t avail = out->u.buf.size - out->u.buf.len;
  size_t n = len < avail ? len : avail;
  memcpy(out->u.buf.buf + out->u.buf.len, buf, n);
  out->u.buf.len += n;
  if (out->u.buf.size > 0) {
    size_t idx = out->u.buf.len;
    if (idx >= out->u.buf.size) idx = out->u.buf.size - 1;
    out->u.buf.buf[idx] = '\0';
  }
  return len;
}

int json_printer_file(struct json_out *out, const char *buf, size_t len) WEAK;
int json_printer_file(struct json_out *out, const char *buf, size_t len) {
  return fwrite(buf, 1, len, out->u.fp);
}

#if JSON_ENABLE_BASE64
static int b64idx(int c) {
  if (c < 26) {
    return c + 'A';
  } else if (c < 52) {
    return c - 26 + 'a';
  } else if (c < 62) {
    return c - 52 + '0';
  } else {
    return c == 62 ? '+' : '/';
  }
}

static int b64rev(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  } else if (c >= 'a' && c <= 'z') {
    return c + 26 - 'a';
  } else if (c >= '0' && c <= '9') {
    return c + 52 - '0';
  } else if (c == '+') {
    return 62;
  } else if (c == '/') {
    return 63;
  } else {
    return 64;
  }
}

static int b64enc(struct json_out *out, const unsigned char *p, int n) {
  char buf[4];
  int i, len = 0;
  for (i = 0; i < n; i += 3) {
    int a = p[i], b = i + 1 < n ? p[i + 1] : 0, c = i + 2 < n ? p[i + 2] : 0;
    buf[0] = b64idx(a >> 2);
    buf[1] = b64idx((a & 3) << 4 | (b >> 4));
    buf[2] = b64idx((b & 15) << 2 | (c >> 6));
    buf[3] = b64idx(c & 63);
    if (i + 1 >= n) buf[2] = '=';
    if (i + 2 >= n) buf[3] = '=';
    len += out->printer(out, buf, sizeof(buf));
  }
  return len;
}

static int b64dec(const char *src, int n, char *dst) {
  const char *end = src + n;
  int len = 0;
  while (src + 3 < end) {
    int a = b64rev(src[0]), b = b64rev(src[1]), c = b64rev(src[2]),
        d = b64rev(src[3]);
    dst[len++] = (a << 2) | (b >> 4);
    if (src[2] != '=') {
      dst[len++] = (b << 4) | (c >> 2);
      if (src[3] != '=') {
        dst[len++] = (c << 6) | d;
      }
    }
    src += 4;
  }
  return len;
}
#endif

static unsigned char hexdec(const char *s) {
#define HEXTOI(x) (x >= '0' && x <= '9' ? x - '0' : x - 'W')
  int a = tolower(*(const unsigned char *) s);
  int b = tolower(*(const unsigned char *) (s + 1));
  return (HEXTOI(a) << 4) | HEXTOI(b);
}

int json_vprintf(struct json_out *out, const char *fmt, va_list xap) WEAK;
int json_vprintf(struct json_out *out, const char *fmt, va_list xap) {
  int len = 0;
  const char *quote = "\"", *null = "kosong";
  va_list ap;
  va_copy(ap, xap);

  while (*fmt != '\0') {
    if (strchr(":, \r\n\t[]{}\"", *fmt) != NULL) {
      len += out->printer(out, fmt, 1);
      fmt++;
    } else if (fmt[0] == '%') {
      char buf[21];
      size_t skip = 2;

      if (fmt[1] == 'l' && fmt[2] == 'l' && (fmt[3] == 'd' || fmt[3] == 'u')) {
        int64_t val = va_arg(ap, int64_t);
        const char *fmt2 = fmt[3] == 'u' ? "%" UINT64_FMT : "%" INT64_FMT;
        snprintf(buf, sizeof(buf), fmt2, val);
        len += out->printer(out, buf, strlen(buf));
        skip += 2;
      } else if (fmt[1] == 'z' && fmt[2] == 'u') {
        size_t val = va_arg(ap, size_t);
        snprintf(buf, sizeof(buf), "%lu", (unsigned long) val);
        len += out->printer(out, buf, strlen(buf));
        skip += 1;
      } else if (fmt[1] == 'M') {
        json_printf_callback_t f = va_arg(ap, json_printf_callback_t);
        len += f(out, &ap);
      } else if (fmt[1] == 'B') {
        int val = va_arg(ap, int);
        const char *str = val ? "benar" : "salah";
        len += out->printer(out, str, strlen(str));
      } else if (fmt[1] == 'H') {
#if JSON_ENABLE_HEX
        const char *hex = "0123456789abcdef";
        int i, n = va_arg(ap, int);
        const unsigned char *p = va_arg(ap, const unsigned char *);
        len += out->printer(out, quote, 1);
        for (i = 0; i < n; i++) {
          len += out->printer(out, &hex[(p[i] >> 4) & 0xf], 1);
          len += out->printer(out, &hex[p[i] & 0xf], 1);
        }
        len += out->printer(out, quote, 1);
#endif
      } else if (fmt[1] == 'V') {
#if JSON_ENABLE_BASE64
        const unsigned char *p = va_arg(ap, const unsigned char *);
        int n = va_arg(ap, int);
        len += out->printer(out, quote, 1);
        len += b64enc(out, p, n);
        len += out->printer(out, quote, 1);
#endif
      } else if (fmt[1] == 'Q' ||
                 (fmt[1] == '.' && fmt[2] == '*' && fmt[3] == 'Q')) {
        size_t l = 0;
        const char *p;

        if (fmt[1] == '.') {
          l = (size_t) va_arg(ap, int);
          skip += 2;
        }
        p = va_arg(ap, char *);

        if (p == NULL) {
          len += out->printer(out, null, 4);
        } else {
          if (fmt[1] == 'Q') {
            l = strlen(p);
          }
          len += out->printer(out, quote, 1);
          len += json_escape(out, p, l);
          len += out->printer(out, quote, 1);
        }
      } else {
       

        const char *end_of_format_specifier = "sdfFeEgGlhuIcx.*-0123456789";
        int n = strspn(fmt + 1, end_of_format_specifier);
        char *pbuf = buf;
        int need_len, size = sizeof(buf);
        char fmt2[20];
        va_list ap_copy;
        strncpy(fmt2, fmt,
                n + 1 > (int) sizeof(fmt2) ? sizeof(fmt2) : (size_t) n + 1);
        fmt2[n + 1] = '\0';

        va_copy(ap_copy, ap);
        need_len = vsnprintf(pbuf, size, fmt2, ap_copy);
        va_end(ap_copy);

        if (need_len < 0) {
         
          pbuf = NULL;
          while (need_len < 0) {
            free(pbuf);
            size *= 2;
            if ((pbuf = (char *) malloc(size)) == NULL) break;
            va_copy(ap_copy, ap);
            need_len = vsnprintf(pbuf, size, fmt2, ap_copy);
            va_end(ap_copy);
          }
        } else if (need_len >= (int) sizeof(buf)) {
         
          if ((pbuf = (char *) malloc(need_len + 1)) != NULL) {
            va_copy(ap_copy, ap);
            vsnprintf(pbuf, need_len + 1, fmt2, ap_copy);
            va_end(ap_copy);
          }
        }
        if (pbuf == NULL) {
          buf[0] = '\0';
          pbuf = buf;
        }

       
        if ((n + 1 == strlen("%" PRId64) && strcmp(fmt2, "%" PRId64) == 0) ||
            (n + 1 == strlen("%" PRIu64) && strcmp(fmt2, "%" PRIu64) == 0)) {
          (void) va_arg(ap, int64_t);
        } else if (strcmp(fmt2, "%.*s") == 0) {
          (void) va_arg(ap, int);
          (void) va_arg(ap, char *);
        } else {
          switch (fmt2[n]) {
            case 'u':
            case 'd':
              (void) va_arg(ap, int);
              break;
            case 'g':
            case 'f':
              (void) va_arg(ap, double);
              break;
            case 'p':
              (void) va_arg(ap, void *);
              break;
            default:
             
              (void) va_arg(ap, int);
          }
        }

        len += out->printer(out, pbuf, strlen(pbuf));
        skip = n + 1;
 
        if (pbuf != buf) {
          free(pbuf);
          pbuf = NULL;
        }
      }
      fmt += skip;
    } else if (*fmt == '_' || json_isalpha(*fmt)) {
      len += out->printer(out, quote, 1);
      while (*fmt == '_' || json_isalpha(*fmt) || json_isdigit(*fmt)) {
        len += out->printer(out, fmt, 1);
        fmt++;
      }
      len += out->printer(out, quote, 1);
    } else {
      len += out->printer(out, fmt, 1);
      fmt++;
    }
  }
  va_end(ap);

  return len;
}

int json_printf(struct json_out *out, const char *fmt, ...) WEAK;
int json_printf(struct json_out *out, const char *fmt, ...) {
  int n;
  va_list ap;
  va_start(ap, fmt);
  n = json_vprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int json_printf_array(struct json_out *out, va_list *ap) WEAK;
int json_printf_array(struct json_out *out, va_list *ap) {
  int len = 0;
  char *arr = va_arg(*ap, char *);
  size_t i, arr_size = va_arg(*ap, size_t);
  size_t elem_size = va_arg(*ap, size_t);
  const char *fmt = va_arg(*ap, char *);
  len += json_printf(out, "[", 1);
  for (i = 0; arr != NULL && i < arr_size / elem_size; i++) {
    union {
      int64_t i;
      double d;
    } val;
    memcpy(&val, arr + i * elem_size,
           elem_size > sizeof(val) ? sizeof(val) : elem_size);
    if (i > 0) len += json_printf(out, ", ");
    if (strpbrk(fmt, "efg") != NULL) {
      len += json_printf(out, fmt, val.d);
    } else {
      len += json_printf(out, fmt, val.i);
    }
  }
  len += json_printf(out, "]", 1);
  return len;
}

#ifdef _WIN32
int BAIK_EM_win_vsnprintf(char *str, size_t size, const char *format,
                     va_list ap) WEAK;
int BAIK_EM_win_vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  int res = _vsnprintf(str, size, format, ap);
  va_end(ap);
  if (res >= size) {
    str[size - 1] = '\0';
  }
  return res;
}

int BAIK_EM_win_snprintf(char *str, size_t size, const char *format, ...) WEAK;
int BAIK_EM_win_snprintf(char *str, size_t size, const char *format, ...) {
  int res;
  va_list ap;
  va_start(ap, format);
  res = vsnprintf(str, size, format, ap);
  va_end(ap);
  return res;
}
#endif

int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data) WEAK;
int json_walk(const char *json_string, int json_string_length,
              json_walk_callback_t callback, void *callback_data) {
  struct frozen frozen;

  memset(&frozen, 0, sizeof(frozen));
  frozen.end = json_string + json_string_length;
  frozen.cur = json_string;
  frozen.callback_data = callback_data;
  frozen.callback = callback;

  TRY(json_doit(&frozen));

  return frozen.cur - json_string;
}

struct scan_array_info {
  int found;
  char path[JSON_MAX_PATH_LEN];
  struct json_token *token;
};

static void json_scanf_array_elem_cb(void *callback_data, const char *name,
                                     size_t name_len, const char *path,
                                     const struct json_token *token) {
  struct scan_array_info *info = (struct scan_array_info *) callback_data;

  (void) name;
  (void) name_len;

  if (strcmp(path, info->path) == 0) {
    *info->token = *token;
    info->found = 1;
  }
}

int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) WEAK;
int json_scanf_array_elem(const char *s, int len, const char *path, int idx,
                          struct json_token *token) {
  struct scan_array_info info;
  info.token = token;
  info.found = 0;
  memset(token, 0, sizeof(*token));
  snprintf(info.path, sizeof(info.path), "%s[%d]", path, idx);
  json_walk(s, len, json_scanf_array_elem_cb, &info);
  return info.found ? token->len : -1;
}

struct json_scanf_info {
  int num_conversions;
  char *path;
  const char *fmt;
  void *target;
  void *user_data;
  int type;
};

int json_unescape(const char *src, int slen, char *dst, int dlen) WEAK;
int json_unescape(const char *src, int slen, char *dst, int dlen) {
  char *send = (char *) src + slen, *dend = dst + dlen, *orig_dst = dst, *p;
  const char *esc1 = "\"\\/bfnrt", *esc2 = "\"\\/\b\f\n\r\t";

  while (src < send) {
    if (*src == '\\') {
      if (++src >= send) return JSON_STRING_INCOMPLETE;
      if (*src == 'u') {
        if (send - src < 5) return JSON_STRING_INCOMPLETE;
       
        if (src[1] == '0' && src[2] == '0') {
         
          if (dst < dend) *dst = hexdec(src + 3);
          src += 4;
        } else {
          return JSON_STRING_INVALID;
        }
      } else if ((p = (char *) strchr(esc1, *src)) != NULL) {
        if (dst < dend) *dst = esc2[p - esc1];
      } else {
        return JSON_STRING_INVALID;
      }
    } else {
      if (dst < dend) *dst = *src;
    }
    dst++;
    src++;
  }

  return dst - orig_dst;
}

static void json_scanf_cb(void *callback_data, const char *name,
                          size_t name_len, const char *path,
                          const struct json_token *token) {
  struct json_scanf_info *info = (struct json_scanf_info *) callback_data;
  char buf[32];

  (void) name;
  (void) name_len;

  if (token->ptr == NULL) {
    return;
  }

  if (strcmp(path, info->path) != 0) {
    return;
  }

  switch (info->type) {
    case 'B':
      info->num_conversions++;
      switch (sizeof(bool)) {
        case sizeof(char):
          *(char *) info->target = (token->type == JSON_TYPE_TRUE ? 1 : 0);
          break;
        case sizeof(int):
          *(int *) info->target = (token->type == JSON_TYPE_TRUE ? 1 : 0);
          break;
        default:
          abort();
      }
      break;
    case 'M': {
      union {
        void *p;
        json_scanner_t f;
      } u = {info->target};
      info->num_conversions++;
      u.f(token->ptr, token->len, info->user_data);
      break;
    }
    case 'Q': {
      char **dst = (char **) info->target;
      if (token->type == JSON_TYPE_NULL) {
        *dst = NULL;
      } else {
        int unescaped_len = json_unescape(token->ptr, token->len, NULL, 0);
        if (unescaped_len >= 0 &&
            (*dst = (char *) malloc(unescaped_len + 1)) != NULL) {
          info->num_conversions++;
          if (json_unescape(token->ptr, token->len, *dst, unescaped_len) ==
              unescaped_len) {
            (*dst)[unescaped_len] = '\0';
          } else {
            free(*dst);
            *dst = NULL;
          }
        }
      }
      break;
    }
    case 'H': {
#if JSON_ENABLE_HEX
      char **dst = (char **) info->user_data;
      int i, len = token->len / 2;
      *(int *) info->target = len;
      if ((*dst = (char *) malloc(len + 1)) != NULL) {
        for (i = 0; i < len; i++) {
          (*dst)[i] = hexdec(token->ptr + 2 * i);
        }
        (*dst)[len] = '\0';
        info->num_conversions++;
      }
#endif
      break;
    }
    case 'V': {
#if JSON_ENABLE_BASE64
      char **dst = (char **) info->target;
      int len = token->len * 4 / 3 + 2;
      if ((*dst = (char *) malloc(len + 1)) != NULL) {
        int n = b64dec(token->ptr, token->len, *dst);
        (*dst)[n] = '\0';
        *(int *) info->user_data = n;
        info->num_conversions++;
      }
#endif
      break;
    }
    case 'T':
      info->num_conversions++;
      *(struct json_token *) info->target = *token;
      break;
    default:
      if (token->len >= (int) sizeof(buf)) break;
     
      memcpy(buf, token->ptr, token->len);
      buf[token->len] = '\0';
     
      if (info->fmt[1] == 'd' || (info->fmt[1] == 'l' && info->fmt[2] == 'd') ||
          info->fmt[1] == 'i') {
        char *endptr = NULL;
        long r = strtol(buf, &endptr, 0);
        if (*endptr == '\0') {
          if (info->fmt[1] == 'l') {
            *((long *) info->target) = r;
          } else {
            *((int *) info->target) = (int) r;
          }
          info->num_conversions++;
        }
      } else if (info->fmt[1] == 'u' ||
                 (info->fmt[1] == 'l' && info->fmt[2] == 'u')) {
        char *endptr = NULL;
        unsigned long r = strtoul(buf, &endptr, 0);
        if (*endptr == '\0') {
          if (info->fmt[1] == 'l') {
            *((unsigned long *) info->target) = r;
          } else {
            *((unsigned int *) info->target) = (unsigned int) r;
          }
          info->num_conversions++;
        }
      } else {
#if !JSON_MINIMAL
        info->num_conversions += sscanf(buf, info->fmt, info->target);
#endif
      }
      break;
  }
}

int json_vscanf(const char *s, int len, const char *fmt, va_list ap) WEAK;
int json_vscanf(const char *s, int len, const char *fmt, va_list ap) {
  char path[JSON_MAX_PATH_LEN] = "", fmtbuf[20];
  int i = 0;
  char *p = NULL;
  struct json_scanf_info info = {0, path, fmtbuf, NULL, NULL, 0};

  while (fmt[i] != '\0') {
    if (fmt[i] == '{') {
      strcat(path, ".");
      i++;
    } else if (fmt[i] == '}') {
      if ((p = strrchr(path, '.')) != NULL) *p = '\0';
      i++;
    } else if (fmt[i] == '%') {
      info.target = va_arg(ap, void *);
      info.type = fmt[i + 1];
      switch (fmt[i + 1]) {
        case 'M':
        case 'V':
        case 'H':
          info.user_data = va_arg(ap, void *);
       
        case 'B':
        case 'Q':
        case 'T':
          i += 2;
          break;
        default: {
          const char *delims = ", \t\r\n]}";
          int conv_len = strcspn(fmt + i + 1, delims) + 1;
          memcpy(fmtbuf, fmt + i, conv_len);
          fmtbuf[conv_len] = '\0';
          i += conv_len;
          i += strspn(fmt + i, delims);
          break;
        }
      }
      json_walk(s, len, json_scanf_cb, &info);
    } else if (json_isalpha(fmt[i]) || json_get_utf8_char_len(fmt[i]) > 1) {
      char *pe;
      const char *delims = ": \r\n\t";
      int key_len = strcspn(&fmt[i], delims);
      if ((p = strrchr(path, '.')) != NULL) p[1] = '\0';
      pe = path + strlen(path);
      memcpy(pe, fmt + i, key_len);
      pe[key_len] = '\0';
      i += key_len + strspn(fmt + i + key_len, delims);
    } else {
      i++;
    }
  }
  return info.num_conversions;
}

int json_scanf(const char *str, int len, const char *fmt, ...) WEAK;
int json_scanf(const char *str, int len, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = json_vscanf(str, len, fmt, ap);
  va_end(ap);
  return result;
}

int json_vfprintf(const char *file_name, const char *fmt, va_list ap) WEAK;
int json_vfprintf(const char *file_name, const char *fmt, va_list ap) {
  int res = -1;
  FILE *fp = fopen(file_name, "wb");
  if (fp != NULL) {
    struct json_out out = JSON_OUT_FILE(fp);
    res = json_vprintf(&out, fmt, ap);
    fputc('\n', fp);
    fclose(fp);
  }
  return res;
}

int json_fprintf(const char *file_name, const char *fmt, ...) WEAK;
int json_fprintf(const char *file_name, const char *fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, fmt);
  result = json_vfprintf(file_name, fmt, ap);
  va_end(ap);
  return result;
}

char *json_fread(const char *path) WEAK;
char *json_fread(const char *path) {
  FILE *fp;
  char *data = NULL;
  if ((fp = fopen(path, "rb")) == NULL) {
  } else if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
  } else {
    long size = ftell(fp);
    if (size > 0 && (data = (char *) malloc(size + 1)) != NULL) {
      fseek(fp, 0, SEEK_SET);
      if (fread(data, 1, size, fp) != (size_t) size) {
        free(data);
        data = NULL;
      } else {
        data[size] = '\0';
      }
    }
    fclose(fp);
  }
  return data;
}

struct json_setf_data {
  const char *json_path;
  const char *base;
  int matched;     
  int pos;         
  int end;         
  int prev;        
};

static int get_matched_prefix_len(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
  return i;
}

static void json_vsetf_cb(void *userdata, const char *name, size_t name_len,
                          const char *path, const struct json_token *t) {
  struct json_setf_data *data = (struct json_setf_data *) userdata;
  int off, len = get_matched_prefix_len(path, data->json_path);
  if (t->ptr == NULL) return;
  off = t->ptr - data->base;
  if (len > data->matched) data->matched = len;

 
  if (len < data->matched && data->pos == 0 &&
      (t->type == JSON_TYPE_OBJECT_END || t->type == JSON_TYPE_ARRAY_END)) {
    data->pos = data->end = data->prev;
  }

 
  if (strcmp(path, data->json_path) == 0 && t->type != JSON_TYPE_OBJECT_START &&
      t->type != JSON_TYPE_ARRAY_START) {
    data->pos = off;
    data->end = off + t->len;
  }

  if (data->pos == 0) {
    data->prev = off + t->len;
  } else if ((t->ptr[0] == '[' || t->ptr[0] == '{') && off + 1 < data->pos &&
             off + 1 > data->prev) {
    data->prev = off + 1;
  }
  (void) name;
  (void) name_len;
}

int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap) WEAK;
int json_vsetf(const char *s, int len, struct json_out *out,
               const char *json_path, const char *json_fmt, va_list ap) {
  struct json_setf_data data;
  memset(&data, 0, sizeof(data));
  data.json_path = json_path;
  data.base = s;
  data.end = len;
  json_walk(s, len, json_vsetf_cb, &data);
  if (json_fmt == NULL) {
   
    json_printf(out, "%.*s", data.prev, s);
   
    if (s[data.prev - 1] == '{' || s[data.prev - 1] == '[') {
      int i = data.end;
      while (i < len && json_isspace(s[i])) i++;
      if (s[i] == ',') data.end = i + 1;
    }
    json_printf(out, "%.*s", len - data.end, s + data.end);
  } else {
   
    int n, off = data.matched, depth = 0;

    json_printf(out, "%.*s", data.pos, s);

    while ((n = strcspn(&json_path[off], ".[")) > 0) {
      if (s[data.prev - 1] != '{' && s[data.prev - 1] != '[' && depth == 0) {
        json_printf(out, ",");
      }
      if (off > 0 && json_path[off - 1] != '.') break;
      json_printf(out, "%.*Q:", n, json_path + off);
      off += n;
      if (json_path[off] != '\0') {
        json_printf(out, "%c", json_path[off] == '.' ? '{' : '[');
        depth++;
        off++;
      }
    }
   
    json_vprintf(out, json_fmt, ap);

    for (; off > data.matched; off--) {
      int ch = json_path[off];
      const char *p = ch == '.' ? "}" : ch == '[' ? "]" : "";
      json_printf(out, "%s", p);
    }

    json_printf(out, "%.*s", len - data.end, s + data.end);
  }
  return data.end > data.pos ? 1 : 0;
}

int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...) WEAK;
int json_setf(const char *s, int len, struct json_out *out,
              const char *json_path, const char *json_fmt, ...) {
  int result;
  va_list ap;
  va_start(ap, json_fmt);
  result = json_vsetf(s, len, out, json_path, json_fmt, ap);
  va_end(ap);
  return result;
}

struct prettify_data {
  struct json_out *out;
  int level;
  int last_token;
};

static void indent(struct json_out *out, int level) {
  while (level-- > 0) out->printer(out, "  ", 2);
}

static void print_key(struct prettify_data *pd, const char *path,
                      const char *name, int name_len) {
  if (pd->last_token != JSON_TYPE_INVALID &&
      pd->last_token != JSON_TYPE_ARRAY_START &&
      pd->last_token != JSON_TYPE_OBJECT_START) {
    pd->out->printer(pd->out, ",", 1);
  }
  if (path[0] != '\0') pd->out->printer(pd->out, "\n", 1);
  indent(pd->out, pd->level);
  if (path[0] != '\0' && path[strlen(path) - 1] != ']') {
    pd->out->printer(pd->out, "\"", 1);
    pd->out->printer(pd->out, name, (int) name_len);
    pd->out->printer(pd->out, "\"", 1);
    pd->out->printer(pd->out, ": ", 2);
  }
}

static void prettify_cb(void *userdata, const char *name, size_t name_len,
                        const char *path, const struct json_token *t) {
  struct prettify_data *pd = (struct prettify_data *) userdata;
  switch (t->type) {
    case JSON_TYPE_OBJECT_START:
    case JSON_TYPE_ARRAY_START:
      print_key(pd, path, name, name_len);
      pd->out->printer(pd->out, t->type == JSON_TYPE_ARRAY_START ? "[" : "{",
                       1);
      pd->level++;
      break;
    case JSON_TYPE_OBJECT_END:
    case JSON_TYPE_ARRAY_END:
      pd->level--;
      if (pd->last_token != JSON_TYPE_INVALID &&
          pd->last_token != JSON_TYPE_ARRAY_START &&
          pd->last_token != JSON_TYPE_OBJECT_START) {
        pd->out->printer(pd->out, "\n", 1);
        indent(pd->out, pd->level);
      }
      pd->out->printer(pd->out, t->type == JSON_TYPE_ARRAY_END ? "]" : "}", 1);
      break;
    case JSON_TYPE_NUMBER:
    case JSON_TYPE_NULL:
    case JSON_TYPE_TRUE:
    case JSON_TYPE_FALSE:
    case JSON_TYPE_STRING:
      print_key(pd, path, name, name_len);
      if (t->type == JSON_TYPE_STRING) pd->out->printer(pd->out, "\"", 1);
      pd->out->printer(pd->out, t->ptr, t->len);
      if (t->type == JSON_TYPE_STRING) pd->out->printer(pd->out, "\"", 1);
      break;
    default:
      break;
  }
  pd->last_token = t->type;
}

int json_prettify(const char *s, int len, struct json_out *out) WEAK;
int json_prettify(const char *s, int len, struct json_out *out) {
  struct prettify_data pd = {out, 0, JSON_TYPE_INVALID};
  return json_walk(s, len, prettify_cb, &pd);
}

int json_prettify_file(const char *file_name) WEAK;
int json_prettify_file(const char *file_name) {
  int res = -1;
  char *s = json_fread(file_name);
  FILE *fp;
  if (s != NULL && (fp = fopen(file_name, "wb")) != NULL) {
    struct json_out out = JSON_OUT_FILE(fp);
    res = json_prettify(s, strlen(s), &out);
    if (res < 0) {
     
      fclose(fp);
      fp = fopen(file_name, "wb");
      fseek(fp, 0, SEEK_SET);
      fwrite(s, 1, strlen(s), fp);
    } else {
      fputc('\n', fp);
    }
    fclose(fp);
  }
  free(s);
  return res;
}

struct next_data {
  void *handle;            
  const char *path;        
  int path_len;            
  int found;               
  struct json_token *key;  
  struct json_token *val;  
  int *idx;                
};

static void next_set_key(struct next_data *d, const char *name, int name_len,
                         int is_array) {
  if (is_array) {
    if (d->key != NULL) {
      d->key->len = 0;
      d->key->ptr = NULL;
    }
    if (d->idx != NULL) *d->idx = atoi(name);
  } else {
   
    if (d->key != NULL) {
      d->key->ptr = name;
      d->key->len = name_len;
    }
    if (d->idx != NULL) *d->idx = -1;
  }
}

static void json_next_cb(void *userdata, const char *name, size_t name_len,
                         const char *path, const struct json_token *t) {
  struct next_data *d = (struct next_data *) userdata;
  const char *p = path + d->path_len;
  if (d->found) return;
  if (d->path_len >= (int) strlen(path)) return;
  if (strncmp(d->path, path, d->path_len) != 0) return;
  if (strchr(p + 1, '.') != NULL) return;
  if (strchr(p + 1, '[') != NULL) return;
  
  if (t->type == JSON_TYPE_OBJECT_START || t->type == JSON_TYPE_ARRAY_START) {
    next_set_key(d, name, name_len, p[0] == '[');
  } else if (d->handle == NULL || d->handle < (void *) t->ptr) {
    if (t->type != JSON_TYPE_OBJECT_END && t->type != JSON_TYPE_ARRAY_END) {
      next_set_key(d, name, name_len, p[0] == '[');
    }
    if (d->val != NULL) *d->val = *t;
    d->handle = (void *) t->ptr;
    d->found = 1;
  }
}

static void *json_next(const char *s, int len, void *handle, const char *path,
                       struct json_token *key, struct json_token *val, int *i) {
  struct json_token tmpval, *v = val == NULL ? &tmpval : val;
  struct json_token tmpkey, *k = key == NULL ? &tmpkey : key;
  int tmpidx, *pidx = i == NULL ? &tmpidx : i;
  struct next_data data = {handle, path, (int) strlen(path), 0, k, v, pidx};
  json_walk(s, len, json_next_cb, &data);
  return data.found ? data.handle : NULL;
}

void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val) WEAK;
void *json_next_key(const char *s, int len, void *handle, const char *path,
                    struct json_token *key, struct json_token *val) {
  return json_next(s, len, handle, path, key, val, NULL);
}

void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val) WEAK;
void *json_next_elem(const char *s, int len, void *handle, const char *path,
                     int *idx, struct json_token *val) {
  return json_next(s, len, handle, path, NULL, val, idx);
}

static int json_sprinter(struct json_out *out, const char *str, size_t len) {
  size_t old_len = out->u.buf.buf == NULL ? 0 : strlen(out->u.buf.buf);
  size_t new_len = len + old_len;
  char *p = (char *) realloc(out->u.buf.buf, new_len + 1);
  if (p != NULL) {
    memcpy(p + old_len, str, len);
    p[new_len] = '\0';
    out->u.buf.buf = p;
  }
  return len;
}

char *json_vasprintf(const char *fmt, va_list ap) WEAK;
char *json_vasprintf(const char *fmt, va_list ap) {
  struct json_out out;
  memset(&out, 0, sizeof(out));
  out.printer = json_sprinter;
  json_vprintf(&out, fmt, ap);
  return out.u.buf.buf;
}

char *json_asprintf(const char *fmt, ...) WEAK;
char *json_asprintf(const char *fmt, ...) {
  char *result = NULL;
  va_list ap;
  va_start(ap, fmt);
  result = json_vasprintf(fmt, ap);
  va_end(ap);
  return result;
}

#define IS_W(arg) ((arg).ctype == FFI_CTYPE_WORD)
#define IS_D(arg) ((arg).ctype == FFI_CTYPE_DOUBLE)
#define IS_F(arg) ((arg).ctype == FFI_CTYPE_FLOAT)

#define W(arg) ((ffi_word_t)(arg).v.i)
#define D(arg) ((arg).v.d)
#define F(arg) ((arg).v.f)

void ffi_set_word(struct ffi_arg *arg, ffi_word_t v) {
  arg->ctype = FFI_CTYPE_WORD;
  arg->v.i = v;
}

void ffi_set_bool(struct ffi_arg *arg, bool v) {
  arg->ctype = FFI_CTYPE_BOOL;
  arg->v.i = v;
}

void ffi_set_ptr(struct ffi_arg *arg, void *v) {
  ffi_set_word(arg, (ffi_word_t) v);
}

void ffi_set_double(struct ffi_arg *arg, double v) {
  arg->ctype = FFI_CTYPE_DOUBLE;
  arg->v.d = v;
}

void ffi_set_float(struct ffi_arg *arg, float v) {
  arg->ctype = FFI_CTYPE_FLOAT;
  arg->v.f = v;
}

typedef ffi_word_t (*w4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*w5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t);
typedef ffi_word_t (*w6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wdw_t)(double, ffi_word_t);
typedef ffi_word_t (*wwd_t)(ffi_word_t, double);
typedef ffi_word_t (*wdd_t)(double, double);
typedef ffi_word_t (*wwwd_t)(ffi_word_t, ffi_word_t, double);
typedef ffi_word_t (*wwdw_t)(ffi_word_t, double, ffi_word_t);
typedef ffi_word_t (*wwdd_t)(ffi_word_t, double, double);
typedef ffi_word_t (*wdww_t)(double, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wdwd_t)(double, ffi_word_t, double);
typedef ffi_word_t (*wddw_t)(double, double, ffi_word_t);
typedef ffi_word_t (*wddd_t)(double, double, double);
typedef ffi_word_t (*wfw_t)(float, ffi_word_t);
typedef ffi_word_t (*wwf_t)(ffi_word_t, float);
typedef ffi_word_t (*wff_t)(float, float);
typedef ffi_word_t (*wwwf_t)(ffi_word_t, ffi_word_t, float);
typedef ffi_word_t (*wwfw_t)(ffi_word_t, float, ffi_word_t);
typedef ffi_word_t (*wwff_t)(ffi_word_t, float, float);
typedef ffi_word_t (*wfww_t)(float, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wfwf_t)(float, ffi_word_t, float);
typedef ffi_word_t (*wffw_t)(float, float, ffi_word_t);
typedef ffi_word_t (*wfff_t)(float, float, float);

typedef bool (*b4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef bool (*b5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t);
typedef bool (*b6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t, ffi_word_t);
typedef bool (*bdw_t)(double, ffi_word_t);
typedef bool (*bwd_t)(ffi_word_t, double);
typedef bool (*bdd_t)(double, double);
typedef bool (*bwwd_t)(ffi_word_t, ffi_word_t, double);
typedef bool (*bwdw_t)(ffi_word_t, double, ffi_word_t);
typedef bool (*bwdd_t)(ffi_word_t, double, double);
typedef bool (*bdww_t)(double, ffi_word_t, ffi_word_t);
typedef bool (*bdwd_t)(double, ffi_word_t, double);
typedef bool (*bddw_t)(double, double, ffi_word_t);
typedef bool (*bddd_t)(double, double, double);
typedef bool (*bfw_t)(float, ffi_word_t);
typedef bool (*bwf_t)(ffi_word_t, float);
typedef bool (*bff_t)(float, float);
typedef bool (*bwwf_t)(ffi_word_t, ffi_word_t, float);
typedef bool (*bwfw_t)(ffi_word_t, float, ffi_word_t);
typedef bool (*bwff_t)(ffi_word_t, float, float);
typedef bool (*bfww_t)(float, ffi_word_t, ffi_word_t);
typedef bool (*bfwf_t)(float, ffi_word_t, float);
typedef bool (*bffw_t)(float, float, ffi_word_t);
typedef bool (*bfff_t)(float, float, float);

typedef double (*d4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef double (*d5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t);
typedef double (*d6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t, ffi_word_t);
typedef double (*ddw_t)(double, ffi_word_t);
typedef double (*dwd_t)(ffi_word_t, double);
typedef double (*ddd_t)(double, double);
typedef double (*dwwd_t)(ffi_word_t, ffi_word_t, double);
typedef double (*dwdw_t)(ffi_word_t, double, ffi_word_t);
typedef double (*dwdd_t)(ffi_word_t, double, double);
typedef double (*ddww_t)(double, ffi_word_t, ffi_word_t);
typedef double (*ddwd_t)(double, ffi_word_t, double);
typedef double (*dddw_t)(double, double, ffi_word_t);
typedef double (*dddd_t)(double, double, double);

typedef float (*f4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef float (*f5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                       ffi_word_t);
typedef float (*f6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                       ffi_word_t, ffi_word_t);
typedef float (*ffw_t)(float, ffi_word_t);
typedef float (*fwf_t)(ffi_word_t, float);
typedef float (*fff_t)(float, float);
typedef float (*fwwf_t)(ffi_word_t, ffi_word_t, float);
typedef float (*fwfw_t)(ffi_word_t, float, ffi_word_t);
typedef float (*fwff_t)(ffi_word_t, float, float);
typedef float (*ffww_t)(float, ffi_word_t, ffi_word_t);
typedef float (*ffwf_t)(float, ffi_word_t, float);
typedef float (*fffw_t)(float, float, ffi_word_t);
typedef float (*ffff_t)(float, float, float);

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0, floats = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += (IS_D(args[i]));
    floats += (IS_F(args[i]));
  }

  if (doubles > 0 && floats > 0) {
    return -1;
  }

  switch (res->ctype) {
    case FFI_CTYPE_WORD: {
      ffi_word_t r;
      if (doubles == 0) {
        if (floats == 0) {
         
          if (nargs <= 4) {
            w4w_t f = (w4w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            w5w_t f = (w5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            w6w_t f = (w6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
        } else {
         
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_F(args[0]) && IS_F(args[1])) {
                wff_t f = (wff_t) func;
                r = f(F(args[0]), F(args[1]));
              } else if (IS_F(args[0])) {
                wfw_t f = (wfw_t) func;
                r = f(F(args[0]), W(args[1]));
              } else {
                wwf_t f = (wwf_t) func;
                r = f(W(args[0]), F(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                wwwf_t f = (wwwf_t) func;
                r = f(W(args[0]), W(args[1]), F(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                wwfw_t f = (wwfw_t) func;
                r = f(W(args[0]), F(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                wwff_t f = (wwff_t) func;
                r = f(W(args[0]), F(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                wfww_t f = (wfww_t) func;
                r = f(F(args[0]), W(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                wfwf_t f = (wfwf_t) func;
                r = f(F(args[0]), W(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                wffw_t f = (wffw_t) func;
                r = f(F(args[0]), F(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                wfff_t f = (wfff_t) func;
                r = f(F(args[0]), F(args[1]), F(args[2]));
              } else {
                
                abort();
              }
              break;
            default:
              return -1;
          }
        }
      } else {
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              wdd_t f = (wdd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              wdw_t f = (wdw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              wwd_t f = (wwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              wwwd_t f = (wwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              wwdw_t f = (wwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              wwdd_t f = (wwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              wdww_t f = (wdww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              wdwd_t f = (wdwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              wddw_t f = (wddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              wddd_t f = (wddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.i = (uint64_t) r;
    } break;              
    case FFI_CTYPE_BOOL: {
      ffi_word_t r;
      if (doubles == 0) {
        if (floats == 0) {
         
          if (nargs <= 4) {
            b4w_t f = (b4w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            b5w_t f = (b5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            b6w_t f = (b6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
        } else {
         
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_F(args[0]) && IS_F(args[1])) {
                bff_t f = (bff_t) func;
                r = f(F(args[0]), F(args[1]));
              } else if (IS_F(args[0])) {
                bfw_t f = (bfw_t) func;
                r = f(F(args[0]), W(args[1]));
              } else {
                bwf_t f = (bwf_t) func;
                r = f(W(args[0]), F(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                bwwf_t f = (bwwf_t) func;
                r = f(W(args[0]), W(args[1]), F(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                bwfw_t f = (bwfw_t) func;
                r = f(W(args[0]), F(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                bwff_t f = (bwff_t) func;
                r = f(W(args[0]), F(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                bfww_t f = (bfww_t) func;
                r = f(F(args[0]), W(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
                bfwf_t f = (bfwf_t) func;
                r = f(F(args[0]), W(args[1]), F(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
                bffw_t f = (bffw_t) func;
                r = f(F(args[0]), F(args[1]), W(args[2]));
              } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
                bfff_t f = (bfff_t) func;
                r = f(F(args[0]), F(args[1]), F(args[2]));
              } else {
                
                abort();
              }
              break;
            default:
              return -1;
          }
        }
      } else {
       
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              bdd_t f = (bdd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              bdw_t f = (bdw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              bwd_t f = (bwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              bwwd_t f = (bwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              bwdw_t f = (bwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              bwdd_t f = (bwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              bdww_t f = (bdww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              bdwd_t f = (bdwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              bddw_t f = (bddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              bddd_t f = (bddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.i = (uint64_t) r;
    } break;                
    case FFI_CTYPE_DOUBLE: {
      double r;
      if (doubles == 0) {
       
        if (nargs <= 4) {
          d4w_t f = (d4w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
        } else if (nargs == 5) {
          d5w_t f = (d5w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
        } else if (nargs == 6) {
          d6w_t f = (d6w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                W(args[5]));
        } else {
          abort();
        }
      } else {
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_D(args[0]) && IS_D(args[1])) {
              ddd_t f = (ddd_t) func;
              r = f(D(args[0]), D(args[1]));
            } else if (IS_D(args[0])) {
              ddw_t f = (ddw_t) func;
              r = f(D(args[0]), W(args[1]));
            } else {
              dwd_t f = (dwd_t) func;
              r = f(W(args[0]), D(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              dwwd_t f = (dwwd_t) func;
              r = f(W(args[0]), W(args[1]), D(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              dwdw_t f = (dwdw_t) func;
              r = f(W(args[0]), D(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              dwdd_t f = (dwdd_t) func;
              r = f(W(args[0]), D(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              ddww_t f = (ddww_t) func;
              r = f(D(args[0]), W(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
              ddwd_t f = (ddwd_t) func;
              r = f(D(args[0]), W(args[1]), D(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
              dddw_t f = (dddw_t) func;
              r = f(D(args[0]), D(args[1]), W(args[2]));
            } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
              dddd_t f = (dddd_t) func;
              r = f(D(args[0]), D(args[1]), D(args[2]));
            } else {
              
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.d = r;
    } break;               
    case FFI_CTYPE_FLOAT: {
      double r;
      if (floats == 0) {
       
        if (nargs <= 4) {
          f4w_t f = (f4w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
        } else if (nargs == 5) {
          f5w_t f = (f5w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
        } else if (nargs == 6) {
          f6w_t f = (f6w_t) func;
          r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                W(args[5]));
        } else {
          abort();
        }
      } else {
       
        switch (nargs) {
          case 0:
          case 1:
          case 2:
            if (IS_F(args[0]) && IS_F(args[1])) {
              fff_t f = (fff_t) func;
              r = f(F(args[0]), F(args[1]));
            } else if (IS_F(args[0])) {
              ffw_t f = (ffw_t) func;
              r = f(F(args[0]), W(args[1]));
            } else {
              fwf_t f = (fwf_t) func;
              r = f(W(args[0]), F(args[1]));
            }
            break;

          case 3:
            if (IS_W(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
              fwwf_t f = (fwwf_t) func;
              r = f(W(args[0]), W(args[1]), F(args[2]));
            } else if (IS_W(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
              fwfw_t f = (fwfw_t) func;
              r = f(W(args[0]), F(args[1]), W(args[2]));
            } else if (IS_W(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
              fwff_t f = (fwff_t) func;
              r = f(W(args[0]), F(args[1]), F(args[2]));
            } else if (IS_F(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
              ffww_t f = (ffww_t) func;
              r = f(F(args[0]), W(args[1]), W(args[2]));
            } else if (IS_F(args[0]) && IS_W(args[1]) && IS_F(args[2])) {
              ffwf_t f = (ffwf_t) func;
              r = f(F(args[0]), W(args[1]), F(args[2]));
            } else if (IS_F(args[0]) && IS_F(args[1]) && IS_W(args[2])) {
              fffw_t f = (fffw_t) func;
              r = f(F(args[0]), F(args[1]), W(args[2]));
            } else if (IS_F(args[0]) && IS_F(args[1]) && IS_F(args[2])) {
              ffff_t f = (ffff_t) func;
              r = f(F(args[0]), F(args[1]), F(args[2]));
            } else {
              
              abort();
            }
            break;
          default:
            return -1;
        }
      }
      res->v.f = r;
    } break;
  }

  return 0;
}

#include <stdio.h>

#define SPLICE_NEW_ITEM_IDX 2

static int v_sprintf_s(char *buf, size_t size, const char *fmt, ...) {
  size_t n;
  va_list ap;
  va_start(ap, fmt);
  n = c_vsnprintf(buf, size, fmt, ap);
  if (n > size) {
    return size;
  }
  return n;
}

baik_val_t baik_mk_array(struct baik *baik) {
  baik_val_t ret = baik_mk_object(baik);
  ret &= ~BAIK_TAG_MASK;
  ret |= BAIK_TAG_ARRAY;
  return ret;
}

int baik_is_array(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_ARRAY;
}

baik_val_t baik_array_get(struct baik *baik, baik_val_t arr, unsigned long index) {
  return baik_array_get2(baik, arr, index, NULL);
}

baik_val_t baik_array_get2(struct baik *baik, baik_val_t arr, unsigned long index,
                         int *has) {
  baik_val_t res = BAIK_UNDEFINED;

  if (has != NULL) {
    *has = 0;
  }

  if (baik_is_object(arr)) {
    struct baik_property *p;
    char buf[20];
    int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
    p = baik_get_own_property(baik, arr, buf, n);
    if (p != NULL) {
      if (has != NULL) {
        *has = 1;
      }
      res = p->value;
    }
  }

  return res;
}

unsigned long baik_array_length(struct baik *baik, baik_val_t v) {
  struct baik_property *p;
  unsigned long len = 0;

  if (!baik_is_object(v)) {
    len = 0;
    goto clean;
  }

  for (p = get_object_struct(v)->properties; p != NULL; p = p->next) {
    int ok = 0;
    unsigned long n = 0;
    str_to_ulong(baik, p->name, &ok, &n);
    if (ok && n >= len && n < 0xffffffff) {
      len = n + 1;
    }
  }

clean:
  return len;
}

baik_err_t baik_array_set(struct baik *baik, baik_val_t arr, unsigned long index,
                        baik_val_t v) {
  baik_err_t ret = BAIK_OK;

  if (baik_is_object(arr)) {
    char buf[20];
    int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
    ret = baik_set(baik, arr, buf, n, v);
  } else {
    ret = BAIK_TYPE_ERROR;
  }

  return ret;
}

void baik_array_del(struct baik *baik, baik_val_t arr, unsigned long index) {
  char buf[20];
  int n = v_sprintf_s(buf, sizeof(buf), "%lu", index);
  baik_del(baik, arr, buf, n);
}

baik_err_t baik_array_push(struct baik *baik, baik_val_t arr, baik_val_t v) {
  return baik_array_set(baik, arr, baik_array_length(baik, arr), v);
}

BAIK_PRIVATE void baik_array_push_internal(struct baik *baik) {
  baik_err_t rcode = BAIK_OK;
  baik_val_t ret = BAIK_UNDEFINED;
  int nargs = baik_nargs(baik);
  int i;

  if (!baik_check_arg(baik, -1, "this", BAIK_TYPE_OBJECT_ARRAY, NULL)) {
    goto clean;
  }

  for (i = 0; i < nargs; i++) {
    rcode = baik_array_push(baik, baik->vals.this_obj, baik_arg(baik, i));
    if (rcode != BAIK_OK) {
      baik_prepend_errorf(baik, rcode, "");
      goto clean;
    }
  }

  ret = baik_mk_number(baik, baik_array_length(baik, baik->vals.this_obj));

clean:
  baik_return(baik, ret);
  return;
}

static void move_item(struct baik *baik, baik_val_t arr, unsigned long from,
                      unsigned long to) {
  baik_val_t cur = baik_array_get(baik, arr, from);
  baik_array_set(baik, arr, to, cur);
  baik_array_del(baik, arr, from);
}

BAIK_PRIVATE void baik_array_splice(struct baik *baik) {
  int nargs = baik_nargs(baik);
  baik_err_t rcode = BAIK_OK;
  baik_val_t ret = baik_mk_array(baik);
  baik_val_t start_v = BAIK_UNDEFINED;
  baik_val_t deleteCount_v = BAIK_UNDEFINED;
  int start = 0;
  int arr_len;
  int delete_cnt = 0;
  int new_items_cnt = 0;
  int delta = 0;
  int i;

  if (!baik_check_arg(baik, -1, "this", BAIK_TYPE_OBJECT_ARRAY, NULL)) {
    goto clean;
  }

  arr_len = baik_array_length(baik, baik->vals.this_obj);

  if (!baik_check_arg(baik, 0, "start", BAIK_TYPE_NUMBER, &start_v)) {
    goto clean;
  }

  start = baik_normalize_idx(baik_get_int(baik, start_v), arr_len);

  if (nargs >= SPLICE_NEW_ITEM_IDX) {
    if (!baik_check_arg(baik, 1, "deleteCount", BAIK_TYPE_NUMBER,
                       &deleteCount_v)) {
      goto clean;
    }
    delete_cnt = baik_get_int(baik, deleteCount_v);
    new_items_cnt = nargs - SPLICE_NEW_ITEM_IDX;
  } else {
   
    delete_cnt = arr_len - start;
  }
  if (delete_cnt > arr_len - start) {
    delete_cnt = arr_len - start;
  } else if (delete_cnt < 0) {
    delete_cnt = 0;
  }

  delta = new_items_cnt - delete_cnt;

  for (i = 0; i < delete_cnt; i++) {
    baik_val_t cur = baik_array_get(baik, baik->vals.this_obj, start + i);
    rcode = baik_array_push(baik, ret, cur);
    if (rcode != BAIK_OK) {
      baik_prepend_errorf(baik, rcode, "");
      goto clean;
    }
  }

  if (delta < 0) {
    for (i = start; i < arr_len; i++) {
      if (i >= start - delta) {
        move_item(baik, baik->vals.this_obj, i, i + delta);
      } else {
        baik_array_del(baik, baik->vals.this_obj, i);
      }
    }
  } else if (delta > 0) {
    for (i = arr_len - 1; i >= start; i--) {
      move_item(baik, baik->vals.this_obj, i, i + delta);
    }
  }

  for (i = 0; i < nargs - SPLICE_NEW_ITEM_IDX; i++) {
    baik_array_set(baik, baik->vals.this_obj, start + i,
                  baik_arg(baik, SPLICE_NEW_ITEM_IDX + i));
  }

clean:
  baik_return(baik, ret);
}

static void add_lineno_map_item(struct pstate *pstate) {
  if (pstate->last_emitted_line_no < pstate->line_no) {
    int offset = pstate->cur_idx - pstate->start_bcode_idx;
    size_t offset_llen = BAIK_EM_varint_llen(offset);
    size_t lineno_llen = BAIK_EM_varint_llen(pstate->line_no);
    mbuf_resize(&pstate->offset_lineno_map,
                pstate->offset_lineno_map.size + offset_llen + lineno_llen);
    BAIK_EM_varint_encode(offset, (uint8_t *) pstate->offset_lineno_map.buf +
                                 pstate->offset_lineno_map.len,
                     offset_llen);
    pstate->offset_lineno_map.len += offset_llen;
    BAIK_EM_varint_encode(pstate->line_no,
                     (uint8_t *) pstate->offset_lineno_map.buf +
                         pstate->offset_lineno_map.len,
                     lineno_llen);
    pstate->offset_lineno_map.len += lineno_llen;
    pstate->last_emitted_line_no = pstate->line_no;
  }
}

BAIK_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte) {
  add_lineno_map_item(pstate);
  mbuf_insert(&pstate->baik->bcode_gen, pstate->cur_idx, &byte, sizeof(byte));
  pstate->cur_idx += sizeof(byte);
}

BAIK_PRIVATE void emit_int(struct pstate *pstate, int64_t n) {
  struct mbuf *b = &pstate->baik->bcode_gen;
  size_t llen = BAIK_EM_varint_llen(n);
  add_lineno_map_item(pstate);
  mbuf_insert(b, pstate->cur_idx, NULL, llen);
  BAIK_EM_varint_encode(n, (uint8_t *) b->buf + pstate->cur_idx, llen);
  pstate->cur_idx += llen;
}

BAIK_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len) {
  struct mbuf *b = &pstate->baik->bcode_gen;
  size_t llen = BAIK_EM_varint_llen(len);
  add_lineno_map_item(pstate);
  mbuf_insert(b, pstate->cur_idx, NULL, llen + len);
  BAIK_EM_varint_encode(len, (uint8_t *) b->buf + pstate->cur_idx, llen);
  memcpy(b->buf + pstate->cur_idx + llen, ptr, len);
  pstate->cur_idx += llen + len;
}

BAIK_PRIVATE int baik_bcode_insert_offset(struct pstate *p, struct baik *baik,
                                        size_t offset, size_t v) {
  int llen = (int) BAIK_EM_varint_llen(v);
  int diff = llen - BAIK_INIT_OFFSET_SIZE;
  assert(offset < baik->bcode_gen.len);
  if (diff > 0) {
    mbuf_resize(&baik->bcode_gen, baik->bcode_gen.size + diff);
  }
 
  memmove(baik->bcode_gen.buf + offset + llen,
          baik->bcode_gen.buf + offset + BAIK_INIT_OFFSET_SIZE,
          baik->bcode_gen.len - offset - BAIK_INIT_OFFSET_SIZE);
  baik->bcode_gen.len += diff;
  BAIK_EM_varint_encode(v, (uint8_t *) baik->bcode_gen.buf + offset, llen);

  if (p->cur_idx >= (int) offset) {
    p->cur_idx += diff;
  }
  return diff;
}

BAIK_PRIVATE void baik_bcode_part_add(struct baik *baik,
                                    const struct baik_bcode_part *bp) {
  mbuf_append(&baik->bcode_parts, bp, sizeof(*bp));
}

BAIK_PRIVATE struct baik_bcode_part *baik_bcode_part_get(struct baik *baik,
                                                      int num) {
  assert(num < baik_bcode_parts_cnt(baik));
  return (struct baik_bcode_part *) (baik->bcode_parts.buf +
                                    num * sizeof(struct baik_bcode_part));
}

BAIK_PRIVATE struct baik_bcode_part *baik_bcode_part_get_by_offset(struct baik *baik,
                                                                size_t offset) {
  int i;
  int parts_cnt = baik_bcode_parts_cnt(baik);
  struct baik_bcode_part *bp = NULL;

  if (offset >= baik->bcode_len) {
    return NULL;
  }

  for (i = 0; i < parts_cnt; i++) {
    bp = baik_bcode_part_get(baik, i);
    if (offset < bp->start_idx + bp->data.len) {
      break;
    }
  }

  assert(i < parts_cnt);

  return bp;
}

BAIK_PRIVATE int baik_bcode_parts_cnt(struct baik *baik) {
  return baik->bcode_parts.len / sizeof(struct baik_bcode_part);
}

BAIK_PRIVATE void baik_bcode_commit(struct baik *baik) {
  struct baik_bcode_part bp;
  memset(&bp, 0, sizeof(bp));
  mbuf_trim(&baik->bcode_gen);

  bp.data.p = baik->bcode_gen.buf;
  bp.data.len = baik->bcode_gen.len;
  mbuf_init(&baik->bcode_gen, 0);

  bp.start_idx = baik->bcode_len;
  bp.exec_res = BAIK_ERRS_CNT;

  baik_bcode_part_add(baik, &bp);
  baik->bcode_len += bp.data.len;
}

static void baik_print(struct baik *baik) {
  size_t i, num_args = baik_nargs(baik);
  for (i = 0; i < num_args; i++) {
    baik_fprintf(baik_arg(baik, i), baik, stdout);
    putchar(' ');
  }
  putchar('\n');
  baik_return(baik, BAIK_UNDEFINED);
}

static struct baik_bcode_part *baik_get_loaded_file_bcode(struct baik *baik,
                                                        const char *filename) {
  int parts_cnt = baik_bcode_parts_cnt(baik);
  int i;

  if (filename == NULL) {
    return 0;
  }

  for (i = 0; i < parts_cnt; i++) {
    struct baik_bcode_part *bp = baik_bcode_part_get(baik, i);
    const char *cur_fn = baik_get_bcode_filename(baik, bp);
    if (strcmp(filename, cur_fn) == 0) {
      return bp;
    }
  }
  return NULL;
}

static void baik_load(struct baik *baik) {
  baik_val_t res = BAIK_UNDEFINED;
  baik_val_t arg0 = baik_arg(baik, 0);
  baik_val_t arg1 = baik_arg(baik, 1);
  int custom_global = 0;

  if (baik_is_string(arg0)) {
    const char *path = baik_get_cstring(baik, &arg0);
    struct baik_bcode_part *bp = NULL;
    baik_err_t ret;

    if (baik_is_object(arg1)) {
      custom_global = 1;
      push_baik_val(&baik->scopes, arg1);
    }
    bp = baik_get_loaded_file_bcode(baik, path);
    if (bp == NULL) {
     
      ret = baik_exec_file(baik, path, &res);
    } else {
     
      if (bp->exec_res != BAIK_OK || custom_global) {
        ret = baik_execute(baik, bp->start_idx, &res);
      } else {
        ret = BAIK_OK;
      }
    }
    if (ret != BAIK_OK) {
     
      arg0 = baik_arg(baik, 0);
      path = baik_get_cstring(baik, &arg0);
      baik_prepend_errorf(baik, ret, "galat : eksekusi file \"%s\"", path);
      goto clean;
    }

  clean:
    if (custom_global) {
      baik_pop_val(&baik->scopes);
    }
  }
  baik_return(baik, res);
}

static void baik_get_baik(struct baik *baik) {
  baik_return(baik, baik_mk_foreign(baik, baik));
}

static void baik_chr(struct baik *baik) {
  baik_val_t arg0 = baik_arg(baik, 0), res = BAIK_NULL;
  int n = baik_get_int(baik, arg0);
  if (baik_is_number(arg0) && n >= 0 && n <= 255) {
    uint8_t s = n;
    res = baik_mk_string(baik, (const char *) &s, sizeof(s), 1);
  }
  baik_return(baik, res);
}

static void baik_do_gc(struct baik *baik) {
  baik_val_t arg0 = baik_arg(baik, 0);
  baik_gc(baik, baik_is_boolean(arg0) ? baik_get_bool(baik, arg0) : 0);
  baik_return(baik, arg0);
}

static void baik_s2o(struct baik *baik) {
  baik_return(baik,
             baik_struct_to_obj(baik, baik_get_ptr(baik, baik_arg(baik, 0)),
                               (const struct baik_c_struct_member *) baik_get_ptr(
                                   baik, baik_arg(baik, 1))));
}

void baik_init_builtin(struct baik *baik, baik_val_t obj) {
  baik_val_t v;

  baik_set(baik, obj, "global", ~0, obj);
  baik_set(baik, obj, "muat", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_load));
  baik_set(baik, obj, "tulis", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_print));
  baik_set(baik, obj, "ffi", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_ffi_call));
  baik_set(baik, obj, "ffi_cb_free", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_ffi_cb_free));
  baik_set(baik, obj, "mkstr", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_mkstr));
  baik_set(baik, obj, "getBAIK", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_get_baik));
  baik_set(baik, obj, "die", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_die));
  baik_set(baik, obj, "gc", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_do_gc));
  baik_set(baik, obj, "chr", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_chr));
  baik_set(baik, obj, "s2o", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_s2o));
  v = baik_mk_object(baik);
  baik_set(baik, v, "stringify", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_op_json_stringify));
  baik_set(baik, v, "parse", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_op_json_parse));
  baik_set(baik, obj, "JSON", ~0, v);
  v = baik_mk_object(baik);
  baik_set(baik, v, "create", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_op_create_object));
  baik_set(baik, obj, "Object", ~0, v);
  baik_set(baik, obj, "NaN", ~0, BAIK_TAG_NAN);
  baik_set(baik, obj, "isNaN", ~0,
          baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_op_isnan));
}

BAIK_PRIVATE baik_err_t baik_to_string(struct baik *baik, baik_val_t *v, char **p,
                                    size_t *sizep, int *need_free) {
  baik_err_t ret = BAIK_OK;

  *p = NULL;
  *sizep = 0;
  *need_free = 0;

  if (baik_is_string(*v)) {
    *p = (char *) baik_get_string(baik, v, sizep);
  } else if (baik_is_number(*v)) {
    char buf[50] = "";
    struct json_out out = JSON_OUT_BUF(buf, sizeof(buf));
    baik_jprintf(*v, baik, &out);
    *sizep = strlen(buf);
    *p = malloc(*sizep + 1);
    if (*p == NULL) {
      ret = BAIK_OUT_OF_MEMORY;
      goto clean;
    }
    memmove(*p, buf, *sizep + 1);
    *need_free = 1;
  } else if (baik_is_boolean(*v)) {
    if (baik_get_bool(baik, *v)) {
      *p = "benar";
      *sizep = 4;
    } else {
      *p = "salah";
      *sizep = 5;
    }
  } else if (baik_is_undefined(*v)) {
    *p = "takterdefinisi";
    *sizep = 9;
  } else if (baik_is_null(*v)) {
    *p = "kosong";
    *sizep = 4;
  } else if (baik_is_object(*v)) {
    ret = BAIK_TYPE_ERROR;
    baik_set_errorf(baik, ret,
                   "conversion from object to string is not supported");
  } else if (baik_is_foreign(*v)) {
    *p = "TODO_foreign";
    *sizep = 12;
  } else {
    ret = BAIK_TYPE_ERROR;
    baik_set_errorf(baik, ret, "unknown type to convert to string");
  }

clean:
  return ret;
}

BAIK_PRIVATE baik_val_t baik_to_boolean_v(struct baik *baik, baik_val_t v) {
  size_t len;
  int is_truthy;

  is_truthy =
      ((baik_is_boolean(v) && baik_get_bool(baik, v)) ||
       (baik_is_number(v) && baik_get_double(baik, v) != 0.0) ||
       (baik_is_string(v) && baik_get_string(baik, &v, &len) && len > 0) ||
       (baik_is_function(v)) || (baik_is_foreign(v)) || (baik_is_object(v))) &&
      v != BAIK_TAG_NAN;

  return baik_mk_boolean(baik, is_truthy);
}

BAIK_PRIVATE int baik_is_truthy(struct baik *baik, baik_val_t v) {
  return baik_get_bool(baik, baik_to_boolean_v(baik, v));
}

#ifndef BAIK_OBJECT_ARENA_SIZE
#define BAIK_OBJECT_ARENA_SIZE 20
#endif
#ifndef BAIK_PROPERTY_ARENA_SIZE
#define BAIK_PROPERTY_ARENA_SIZE 20
#endif
#ifndef BAIK_FUNC_FFI_ARENA_SIZE
#define BAIK_FUNC_FFI_ARENA_SIZE 20
#endif
#ifndef BAIK_OBJECT_ARENA_INC_SIZE
#define BAIK_OBJECT_ARENA_INC_SIZE 10
#endif
#ifndef BAIK_PROPERTY_ARENA_INC_SIZE
#define BAIK_PROPERTY_ARENA_INC_SIZE 10
#endif
#ifndef BAIK_FUNC_FFI_ARENA_INC_SIZE
#define BAIK_FUNC_FFI_ARENA_INC_SIZE 10
#endif

void baik_destroy(struct baik *baik) {
  {
    int parts_cnt = baik_bcode_parts_cnt(baik);
    int i;
    for (i = 0; i < parts_cnt; i++) {
      struct baik_bcode_part *bp = baik_bcode_part_get(baik, i);
      if (!bp->in_rom) {
        free((void *) bp->data.p);
      }
    }
  }

  mbuf_free(&baik->bcode_gen);
  mbuf_free(&baik->bcode_parts);
  mbuf_free(&baik->stack);
  mbuf_free(&baik->call_stack);
  mbuf_free(&baik->arg_stack);
  mbuf_free(&baik->owned_strings);
  mbuf_free(&baik->foreign_strings);
  mbuf_free(&baik->owned_values);
  mbuf_free(&baik->scopes);
  mbuf_free(&baik->loop_addresses);
  mbuf_free(&baik->json_visited_stack);
  free(baik->error_msg);
  free(baik->stack_trace);
  baik_ffi_args_free_list(baik);
  gc_arena_destroy(baik, &baik->object_arena);
  gc_arena_destroy(baik, &baik->property_arena);
  gc_arena_destroy(baik, &baik->ffi_sig_arena);
  free(baik);
}

struct baik *baik_create(void) {
  baik_val_t global_object;
  struct baik *baik = calloc(1, sizeof(*baik));
  mbuf_init(&baik->stack, 0);
  mbuf_init(&baik->call_stack, 0);
  mbuf_init(&baik->arg_stack, 0);
  mbuf_init(&baik->owned_strings, 0);
  mbuf_init(&baik->foreign_strings, 0);
  mbuf_init(&baik->bcode_gen, 0);
  mbuf_init(&baik->bcode_parts, 0);
  mbuf_init(&baik->owned_values, 0);
  mbuf_init(&baik->scopes, 0);
  mbuf_init(&baik->loop_addresses, 0);
  mbuf_init(&baik->json_visited_stack, 0);

  baik->bcode_len = 0;
 
  {
    char z = 0;
    mbuf_append(&baik->owned_strings, &z, 1);
  }

  gc_arena_init(&baik->object_arena, sizeof(struct baik_object),
                BAIK_OBJECT_ARENA_SIZE, BAIK_OBJECT_ARENA_INC_SIZE);
  gc_arena_init(&baik->property_arena, sizeof(struct baik_property),
                BAIK_PROPERTY_ARENA_SIZE, BAIK_PROPERTY_ARENA_INC_SIZE);
  gc_arena_init(&baik->ffi_sig_arena, sizeof(struct baik_ffi_sig),
                BAIK_FUNC_FFI_ARENA_SIZE, BAIK_FUNC_FFI_ARENA_INC_SIZE);
  baik->ffi_sig_arena.destructor = baik_ffi_sig_destructor;

  global_object = baik_mk_object(baik);
  baik_init_builtin(baik, global_object);
  baik_set_ffi_resolver(baik, dlsym);
  push_baik_val(&baik->scopes, global_object);
  baik->vals.this_obj = BAIK_UNDEFINED;
  baik->vals.dataview_proto = BAIK_UNDEFINED;

  return baik;
}

baik_err_t baik_set_errorf(struct baik *baik, baik_err_t err, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  free(baik->error_msg);
  baik->error_msg = NULL;
  baik->error = err;
  if (fmt != NULL) {
    baik_generic_avprintf(&baik->error_msg, 0, fmt, ap);
  }
  va_end(ap);
  return err;
}

baik_err_t baik_prepend_errorf(struct baik *baik, baik_err_t err, const char *fmt,
                             ...) {
  char *old_error_msg = baik->error_msg;
  char *new_error_msg = NULL;
  va_list ap;
  va_start(ap, fmt);

  assert(err != BAIK_OK);

  baik->error_msg = NULL;
 
  if (baik->error == BAIK_OK) {
    baik->error = err;
  }
  baik_generic_avprintf(&new_error_msg, 0, fmt, ap);
  va_end(ap);

  if (old_error_msg != NULL) {
    baik_generic_asprintf(&baik->error_msg, 0, "%s: %s", new_error_msg, old_error_msg);
    free(new_error_msg);
    free(old_error_msg);
  } else {
    baik->error_msg = new_error_msg;
  }
  return err;
}

void baik_print_error(struct baik *baik, FILE *fp, const char *msg,
                     int print_stack_trace) {
  if (print_stack_trace && baik->stack_trace != NULL) {
    fprintf(fp, "%s", baik->stack_trace);
  }

  if (msg == NULL) {
    msg = "BAIK galat";
  }

  fprintf(fp, "%s: %s\n", msg, baik_strerror(baik, baik->error));
}

BAIK_PRIVATE void baik_die(struct baik *baik) {
  baik_val_t msg_v = BAIK_UNDEFINED;
  const char *msg = NULL;
  size_t msg_len = 0;

  if (!baik_check_arg(baik, 0, "msg", BAIK_TYPE_STRING, &msg_v)) {
    goto clean;
  }

  msg = baik_get_string(baik, &msg_v, &msg_len);

  baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "%.*s", (int) msg_len, msg);

clean:
  baik_return(baik, BAIK_UNDEFINED);
}

const char *baik_strerror(struct baik *baik, enum baik_err err) {
  const char *err_names[] = {
      "NO_ERROR",        "SYNTAX_ERROR",    "REFERENCE_ERROR",
      "TYPE_ERROR",      "OUT_OF_MEMORY",   "INTERNAL_ERROR",
      "NOT_IMPLEMENTED", "FILE_OPEN_ERROR", "BAD_ARGUMENTS"};
  return baik->error_msg == NULL || baik->error_msg[0] == '\0' ? err_names[err]
                                                             : baik->error_msg;
}

BAIK_PRIVATE size_t baik_get_func_addr(baik_val_t v) {
  return v & ~BAIK_TAG_MASK;
}

BAIK_PRIVATE enum baik_type baik_get_type(baik_val_t v) {
  int tag;
  if (baik_is_number(v)) {
    return BAIK_TYPE_NUMBER;
  }
  tag = (v & BAIK_TAG_MASK) >> 48;
  switch (tag) {
    case BAIK_TAG_FOREIGN >> 48:
      return BAIK_TYPE_FOREIGN;
    case BAIK_TAG_UNDEFINED >> 48:
      return BAIK_TYPE_UNDEFINED;
    case BAIK_TAG_OBJECT >> 48:
      return BAIK_TYPE_OBJECT_GENERIC;
    case BAIK_TAG_ARRAY >> 48:
      return BAIK_TYPE_OBJECT_ARRAY;
    case BAIK_TAG_FUNCTION >> 48:
      return BAIK_TYPE_OBJECT_FUNCTION;
    case BAIK_TAG_STRING_I >> 48:
    case BAIK_TAG_STRING_O >> 48:
    case BAIK_TAG_STRING_F >> 48:
    case BAIK_TAG_STRING_D >> 48:
    case BAIK_TAG_STRING_5 >> 48:
      return BAIK_TYPE_STRING;
    case BAIK_TAG_BOOLEAN >> 48:
      return BAIK_TYPE_BOOLEAN;
    case BAIK_TAG_NULL >> 48:
      return BAIK_TYPE_NULL;
    default:
      abort();
      return BAIK_TYPE_UNDEFINED;
  }
}

baik_val_t baik_get_global(struct baik *baik) {
  return *vptr(&baik->scopes, 0);
}

static void baik_append_stack_trace_line(struct baik *baik, size_t offset) {
  if (offset != BAIK_BCODE_OFFSET_EXIT) {
    const char *filename = baik_get_bcode_filename_by_offset(baik, offset);
    int line_no = baik_get_lineno_by_offset(baik, offset);
    char *new_line = NULL;
    const char *fmt = "  at %s:%d\n";
    if (filename == NULL) {
      fprintf(stderr,
              "ERROR during stack trace generation: wrong bcode offset %d\n",
              (int) offset);
      filename = "<unknown-filename>";
    }
    baik_generic_asprintf(&new_line, 0, fmt, filename, line_no);

    if (baik->stack_trace != NULL) {
      char *old = baik->stack_trace;
      baik_generic_asprintf(&baik->stack_trace, 0, "%s%s", baik->stack_trace, new_line);
      free(old);
      free(new_line);
    } else {
      baik->stack_trace = new_line;
    }
  }
}

BAIK_PRIVATE void baik_gen_stack_trace(struct baik *baik, size_t offset) {
  baik_append_stack_trace_line(baik, offset);
  while (baik->call_stack.len >=
         sizeof(baik_val_t) * CALL_STACK_FRAME_ITEMS_CNT) {
    int i;

    offset = baik_get_int(
        baik, *vptr(&baik->call_stack, -1 - CALL_STACK_FRAME_ITEM_RETURN_ADDR));

    for (i = 0; i < CALL_STACK_FRAME_ITEMS_CNT; i++) {
      baik_pop_val(&baik->call_stack);
    }

    baik_append_stack_trace_line(baik, offset);
  }
}

void baik_own(struct baik *baik, baik_val_t *v) {
  mbuf_append(&baik->owned_values, &v, sizeof(v));
}

int baik_disown(struct baik *baik, baik_val_t *v) {
  baik_val_t **vp = (baik_val_t **) (baik->owned_values.buf +
                                   baik->owned_values.len - sizeof(v));

  for (; (char *) vp >= baik->owned_values.buf; vp--) {
    if (*vp == v) {
      *vp = *(baik_val_t **) (baik->owned_values.buf + baik->owned_values.len -
                             sizeof(v));
      baik->owned_values.len -= sizeof(v);
      return 1;
    }
  }

  return 0;
}


BAIK_PRIVATE int baik_getretvalpos(struct baik *baik) {
  int pos;
  baik_val_t *ppos = vptr(&baik->call_stack, -1);
  
  assert(ppos != NULL && baik_is_number(*ppos));
  pos = baik_get_int(baik, *ppos) - 1;
  assert(pos < (int) baik_stack_size(&baik->stack));
  return pos;
}

int baik_nargs(struct baik *baik) {
  int top = baik_stack_size(&baik->stack);
  int pos = baik_getretvalpos(baik) + 1;
  
  return pos > 0 && pos < top ? top - pos : 0;
}

baik_val_t baik_arg(struct baik *baik, int arg_index) {
  baik_val_t res = BAIK_UNDEFINED;
  int top = baik_stack_size(&baik->stack);
  int pos = baik_getretvalpos(baik) + 1;
  
  if (pos > 0 && pos + arg_index < top) {
    res = *vptr(&baik->stack, pos + arg_index);
  }

  return res;
}

void baik_return(struct baik *baik, baik_val_t v) {
  int pos = baik_getretvalpos(baik);
  
  baik->stack.len = sizeof(baik_val_t) * pos;
  baik_push(baik, v);
}

BAIK_PRIVATE baik_val_t vtop(struct mbuf *m) {
  size_t size = baik_stack_size(m);
  return size > 0 ? *vptr(m, size - 1) : BAIK_UNDEFINED;
}

BAIK_PRIVATE size_t baik_stack_size(const struct mbuf *m) {
  return m->len / sizeof(baik_val_t);
}

BAIK_PRIVATE baik_val_t *vptr(struct mbuf *m, int idx) {
  int size = baik_stack_size(m);
  if (idx < 0) idx = size + idx;
  return idx >= 0 && idx < size ? &((baik_val_t *) m->buf)[idx] : NULL;
}

BAIK_PRIVATE baik_val_t baik_pop(struct baik *baik) {
  if (baik->stack.len == 0) {
    baik_set_errorf(baik, BAIK_INTERNAL_ERROR, "stack underflow");
    return BAIK_UNDEFINED;
  } else {
    return baik_pop_val(&baik->stack);
  }
}

BAIK_PRIVATE void push_baik_val(struct mbuf *m, baik_val_t v) {
  mbuf_append(m, &v, sizeof(v));
}

BAIK_PRIVATE baik_val_t baik_pop_val(struct mbuf *m) {
  baik_val_t v = BAIK_UNDEFINED;
  assert(m->len >= sizeof(v));
  if (m->len >= sizeof(v)) {
    memcpy(&v, m->buf + m->len - sizeof(v), sizeof(v));
    m->len -= sizeof(v);
  }
  return v;
}

BAIK_PRIVATE void baik_push(struct baik *baik, baik_val_t v) {
  push_baik_val(&baik->stack, v);
}

void baik_set_generate_jsc(struct baik *baik, int generate_jsc) {
  baik->generate_jsc = generate_jsc;
}

void *baik_mem_to_ptr(unsigned val) {
  return (void *) (uintptr_t) val;
}

void *baik_mem_get_ptr(void *base, int offset) {
  return (char *) base + offset;
}

void baik_mem_set_ptr(void *ptr, void *val) {
  *(void **) ptr = val;
}

double baik_mem_get_dbl(void *ptr) {
  double v;
  memcpy(&v, ptr, sizeof(v));
  return v;
}

void baik_mem_set_dbl(void *ptr, double val) {
  memcpy(ptr, &val, sizeof(val));
}

double baik_mem_get_uint(void *ptr, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr;
  int i, inc = bigendian ? 1 : -1;
  unsigned int res = 0;
  p += bigendian ? 0 : size - 1;
  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }
  return res;
}

double baik_mem_get_int(void *ptr, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr;
  int i, inc = bigendian ? 1 : -1;
  int res = 0;
  p += bigendian ? 0 : size - 1;

  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }

  {
    int extra = sizeof(res) - size;
    for (i = 0; i < extra; i++) res <<= 8;
    for (i = 0; i < extra; i++) res >>= 8;
  }

  return res;
}

void baik_mem_set_uint(void *ptr, unsigned int val, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr + (bigendian ? size - 1 : 0);
  int i, inc = bigendian ? -1 : 1;
  for (i = 0; i < size; i++, p += inc) {
    *p = val & 0xff;
    val >>= 8;
  }
}

void baik_mem_set_int(void *ptr, int val, int size, int bigendian) {
  baik_mem_set_uint(ptr, val, size, bigendian);
}

#if BAIK_GENERATE_INAC && defined(BAIK_EM_MMAP)
#include <sys/mman.h>
#endif

static void call_stack_push_frame(struct baik *baik, size_t offset,
                                  baik_val_t retval_stack_idx) {
 
  baik_val_t this_obj = baik_pop_val(&baik->arg_stack);
  push_baik_val(&baik->call_stack, baik->vals.this_obj);
  baik->vals.this_obj = this_obj;
  push_baik_val(&baik->call_stack, baik_mk_number(baik, (double) offset));
  push_baik_val(&baik->call_stack,
               baik_mk_number(baik, (double) baik_stack_size(&baik->scopes)));
  push_baik_val(
      &baik->call_stack,
      baik_mk_number(baik, (double) baik_stack_size(&baik->loop_addresses)));
  push_baik_val(&baik->call_stack, retval_stack_idx);
}


static size_t call_stack_restore_frame(struct baik *baik) {
  size_t retval_stack_idx, return_address, scope_index, loop_addr_index;
  assert(baik_stack_size(&baik->call_stack) >= CALL_STACK_FRAME_ITEMS_CNT);

  retval_stack_idx = baik_get_int(baik, baik_pop_val(&baik->call_stack));
  loop_addr_index = baik_get_int(baik, baik_pop_val(&baik->call_stack));
  scope_index = baik_get_int(baik, baik_pop_val(&baik->call_stack));
  return_address = baik_get_int(baik, baik_pop_val(&baik->call_stack));
  baik->vals.this_obj = baik_pop_val(&baik->call_stack);

  while (baik_stack_size(&baik->scopes) > scope_index) {
    baik_pop_val(&baik->scopes);
  }

  while (baik_stack_size(&baik->loop_addresses) > loop_addr_index) {
    baik_pop_val(&baik->loop_addresses);
  }

  baik->stack.len = retval_stack_idx * sizeof(baik_val_t);

  return return_address;
}

static baik_val_t baik_find_scope(struct baik *baik, baik_val_t key) {
  size_t num_scopes = baik_stack_size(&baik->scopes);
  while (num_scopes > 0) {
    baik_val_t scope = *vptr(&baik->scopes, num_scopes - 1);
    num_scopes--;
    if (baik_get_own_property_v(baik, scope, key) != NULL) return scope;
  }
  baik_set_errorf(baik, BAIK_REFERENCE_ERROR, "[%s] tidak terdefinisikan",
                 baik_get_cstring(baik, &key));
  return BAIK_UNDEFINED;
}

baik_val_t baik_get_this(struct baik *baik) {
  return baik->vals.this_obj;
}

static double do_arith_op(double da, double db, int op, bool *resnan) {
  *resnan = false;

  if (isnan(da) || isnan(db)) {
    *resnan = true;
    return 0;
  }
 
  switch (op) {
    case TOK_MINUS:   return da - db;
    case TOK_PLUS:    return da + db;
    case TOK_MUL:     return da * db;
    case TOK_DIV:
      if (db != 0) {
        return da / db;
      } else {
       
        *resnan = true;
        return 0;
      }
    case TOK_REM:
     
      db = (int) db;
      if (db != 0) {
        bool neg = false;
        if (da < 0) {
          neg = true;
          da = -da;
        }
        if (db < 0) {
          db = -db;
        }
        da = (double) ((int64_t) da % (int64_t) db);
        if (neg) {
          da = -da;
        }
        return da;
      } else {
        *resnan = true;
        return 0;
      }
    case TOK_AND:     return (double) ((int64_t) da & (int64_t) db);
    case TOK_OR:      return (double) ((int64_t) da | (int64_t) db);
    case TOK_XOR:     return (double) ((int64_t) da ^ (int64_t) db);
    case TOK_LSHIFT:  return (double) ((int64_t) da << (int64_t) db);
    case TOK_RSHIFT:  return (double) ((int64_t) da >> (int64_t) db);
    case TOK_URSHIFT: return (double) ((uint32_t) da >> (uint32_t) db);
  }
 
  *resnan = true;
  return 0;
}

static void set_no_autoconversion_error(struct baik *baik) {
  baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                     "galat : konversi tipe implisit dilarang");
}

static baik_val_t do_op(struct baik *baik, baik_val_t a, baik_val_t b, int op) {
  baik_val_t ret = BAIK_UNDEFINED;
  bool resnan = false;
  if ((baik_is_foreign(a) || baik_is_number(a)) &&
      (baik_is_foreign(b) || baik_is_number(b))) {
    int is_result_ptr = 0;
    double da, db, result;

    if (baik_is_foreign(a) && baik_is_foreign(b)) {
      if (op != TOK_MINUS) {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : operan tidak valid");
      }
    } else if (baik_is_foreign(a) || baik_is_foreign(b)) {
      if (op != TOK_MINUS && op != TOK_PLUS) {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : operan tidak valid");
      }
      is_result_ptr = 1;
    }
    da = baik_is_number(a) ? baik_get_double(baik, a)
                          : (double) (uintptr_t) baik_get_ptr(baik, a);
    db = baik_is_number(b) ? baik_get_double(baik, b)
                          : (double) (uintptr_t) baik_get_ptr(baik, b);
    result = do_arith_op(da, db, op, &resnan);
    if (resnan) {
      ret = BAIK_TAG_NAN;
    } else {
     
      ret = is_result_ptr ? baik_mk_foreign(baik, (void *) (uintptr_t) result)
                          : baik_mk_number(baik, result);
    }
  } else if (baik_is_string(a) && baik_is_string(b) && (op == TOK_PLUS)) {
    ret = s_concat(baik, a, b);
  } else {
    set_no_autoconversion_error(baik);
  }
  return ret;
}

static void op_assign(struct baik *baik, int op) {
  baik_val_t val = baik_pop(baik);
  baik_val_t obj = baik_pop(baik);
  baik_val_t key = baik_pop(baik);
  if (baik_is_object(obj) && baik_is_string(key)) {
    baik_val_t v = baik_get_v(baik, obj, key);
    baik_set_v(baik, obj, key, do_op(baik, v, val, op));
    baik_push(baik, v);
  } else {
    baik_set_errorf(baik, BAIK_TYPE_ERROR, "invalid operand");
  }
}

static int check_equal(struct baik *baik, baik_val_t a, baik_val_t b) {
  int ret = 0;
  if (a == BAIK_TAG_NAN && b == BAIK_TAG_NAN) {
    ret = 0;
  } else if (a == b) {
    ret = 1;
  } else if (baik_is_number(a) && baik_is_number(b)) {
    ret = 0;
  } else if (baik_is_string(a) && baik_is_string(b)) {
    ret = s_cmp(baik, a, b) == 0;
  } else if (baik_is_foreign(a) && b == BAIK_NULL) {
    ret = baik_get_ptr(baik, a) == NULL;
  } else if (a == BAIK_NULL && baik_is_foreign(b)) {
    ret = baik_get_ptr(baik, b) == NULL;
  } else {
    ret = 0;
  }
  return ret;
}

static void exec_expr(struct baik *baik, int op) {
  switch (op) {
    case TOK_DOT:
      break;
    case TOK_MINUS:
    case TOK_PLUS:
    case TOK_MUL:
    case TOK_DIV:
    case TOK_REM:
    case TOK_XOR:
    case TOK_AND:
    case TOK_OR:
    case TOK_LSHIFT:
    case TOK_RSHIFT:
    case TOK_URSHIFT: {
      baik_val_t b = baik_pop(baik);
      baik_val_t a = baik_pop(baik);
      baik_push(baik, do_op(baik, a, b, op));
      break;
    }
    case TOK_UNARY_MINUS: {
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_number(baik, -a));
      break;
    }
    case TOK_NOT: {
      baik_val_t val = baik_pop(baik);
      baik_push(baik, baik_mk_boolean(baik, !baik_is_truthy(baik, val)));
      break;
    }
    case TOK_TILDA: {
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_number(baik, (double) (~(int64_t) a)));
      break;
    }
    case TOK_UNARY_PLUS:
      break;
    case TOK_EQ:
      baik_set_errorf(baik, BAIK_NOT_IMPLEMENTED_ERROR, "Use ===, not ==");
      break;
    case TOK_NE:
      baik_set_errorf(baik, BAIK_NOT_IMPLEMENTED_ERROR, "Use !==, not !=");
      break;
    case TOK_EQ_EQ: {
      baik_val_t a = baik_pop(baik);
      baik_val_t b = baik_pop(baik);
      baik_push(baik, baik_mk_boolean(baik, check_equal(baik, a, b)));
      break;
    }
    case TOK_NE_NE: {
      baik_val_t a = baik_pop(baik);
      baik_val_t b = baik_pop(baik);
      baik_push(baik, baik_mk_boolean(baik, !check_equal(baik, a, b)));
      break;
    }
    case TOK_LT: {
      double b = baik_get_double(baik, baik_pop(baik));
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_boolean(baik, a < b));
      break;
    }
    case TOK_GT: {
      double b = baik_get_double(baik, baik_pop(baik));
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_boolean(baik, a > b));
      break;
    }
    case TOK_LE: {
      double b = baik_get_double(baik, baik_pop(baik));
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_boolean(baik, a <= b));
      break;
    }
    case TOK_GE: {
      double b = baik_get_double(baik, baik_pop(baik));
      double a = baik_get_double(baik, baik_pop(baik));
      baik_push(baik, baik_mk_boolean(baik, a >= b));
      break;
    }
    case TOK_ASSIGN: {
      baik_val_t val = baik_pop(baik);
      baik_val_t obj = baik_pop(baik);
      baik_val_t key = baik_pop(baik);
      if (baik_is_object(obj)) {
        baik_set_v(baik, obj, key, val);
      } else if (baik_is_foreign(obj)) {
       

        int ikey = baik_get_int(baik, key);
        int ival = baik_get_int(baik, val);

        if (!baik_is_number(key)) {
          baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : index harus angka");
          val = BAIK_UNDEFINED;
        } else if (!baik_is_number(val) || ival < 0 || ival > 0xff) {
          baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                             "GALAT : hanya angka 0 .. 255 yang bisa digunakan");
          val = BAIK_UNDEFINED;
        } else {
          uint8_t *ptr = (uint8_t *) baik_get_ptr(baik, obj);
          *(ptr + ikey) = (uint8_t) ival;
        }
      } else {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : tipe objek tidak didukung");
      }
      baik_push(baik, val);
      break;
    }
    case TOK_POSTFIX_PLUS: {
      baik_val_t obj = baik_pop(baik);
      baik_val_t key = baik_pop(baik);
      if (baik_is_object(obj) && baik_is_string(key)) {
        baik_val_t v = baik_get_v(baik, obj, key);
        baik_val_t v1 = do_op(baik, v, baik_mk_number(baik, 1), TOK_PLUS);
        baik_set_v(baik, obj, key, v1);
        baik_push(baik, v);
      } else {
        baik_set_errorf(baik, BAIK_TYPE_ERROR, "invalid operand for ++");
      }
      break;
    }
    case TOK_POSTFIX_MINUS: {
      baik_val_t obj = baik_pop(baik);
      baik_val_t key = baik_pop(baik);
      if (baik_is_object(obj) && baik_is_string(key)) {
        baik_val_t v = baik_get_v(baik, obj, key);
        baik_val_t v1 = do_op(baik, v, baik_mk_number(baik, 1), TOK_MINUS);
        baik_set_v(baik, obj, key, v1);
        baik_push(baik, v);
      } else {
        baik_set_errorf(baik, BAIK_TYPE_ERROR, "invalid operand for --");
      }
      break;
    }
    case TOK_MINUS_MINUS: {
      baik_val_t obj = baik_pop(baik);
      baik_val_t key = baik_pop(baik);
      if (baik_is_object(obj) && baik_is_string(key)) {
        baik_val_t v = baik_get_v(baik, obj, key);
        v = do_op(baik, v, baik_mk_number(baik, 1), TOK_MINUS);
        baik_set_v(baik, obj, key, v);
        baik_push(baik, v);
      } else {
        baik_set_errorf(baik, BAIK_TYPE_ERROR, "invalid operand for --");
      }
      break;
    }
    case TOK_PLUS_PLUS: {
      baik_val_t obj = baik_pop(baik);
      baik_val_t key = baik_pop(baik);
      if (baik_is_object(obj) && baik_is_string(key)) {
        baik_val_t v = baik_get_v(baik, obj, key);
        v = do_op(baik, v, baik_mk_number(baik, 1), TOK_PLUS);
        baik_set_v(baik, obj, key, v);
        baik_push(baik, v);
      } else {
        baik_set_errorf(baik, BAIK_TYPE_ERROR, "invalid operand for ++");
      }
      break;
    }
   

   
    case TOK_MINUS_ASSIGN:    op_assign(baik, TOK_MINUS);    break;
    case TOK_PLUS_ASSIGN:     op_assign(baik, TOK_PLUS);     break;
    case TOK_MUL_ASSIGN:      op_assign(baik, TOK_MUL);      break;
    case TOK_DIV_ASSIGN:      op_assign(baik, TOK_DIV);      break;
    case TOK_REM_ASSIGN:      op_assign(baik, TOK_REM);      break;
    case TOK_AND_ASSIGN:      op_assign(baik, TOK_AND);      break;
    case TOK_OR_ASSIGN:       op_assign(baik, TOK_OR);       break;
    case TOK_XOR_ASSIGN:      op_assign(baik, TOK_XOR);      break;
    case TOK_LSHIFT_ASSIGN:   op_assign(baik, TOK_LSHIFT);   break;
    case TOK_RSHIFT_ASSIGN:   op_assign(baik, TOK_RSHIFT);   break;
    case TOK_URSHIFT_ASSIGN:  op_assign(baik, TOK_URSHIFT);  break;
    case TOK_COMMA: break;
   
    case TOK_KEYWORD_TIPE:
      baik_push(baik, baik_mk_string(baik, baik_typeof(baik_pop(baik)), ~0, 1));
      break;
    default:
      LOG(LL_ERROR, ("Unknown expr: %d", op));
      break;
  }
}

static int getprop_builtin_string(struct baik *baik, baik_val_t val,
                                  const char *name, size_t name_len,
                                  baik_val_t *res) {
  int isnum = 0;
  int idx = cstr_to_ulong(name, name_len, &isnum);

  if (strcmp(name, "panjang") == 0) {
    size_t val_len;
    baik_get_string(baik, &val, &val_len);
    *res = baik_mk_number(baik, (double) val_len);
    return 1;
  } else if (strcmp(name, "at") == 0 || strcmp(name, "charCodeAt") == 0) {
    *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_string_char_code_at);
    return 1;
  } else if (strcmp(name, "indexOf") == 0) {
    *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_string_index_of);
    return 1;
  } else if (strcmp(name, "slice") == 0) {
    *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_string_slice);
    return 1;
  } else if (isnum) {
   
    size_t val_len;
    const char *str = baik_get_string(baik, &val, &val_len);
    if (idx >= 0 && idx < (int) val_len) {
      *res = baik_mk_string(baik, str + idx, 1, 1);
    } else {
      *res = BAIK_UNDEFINED;
    }
    return 1;
  }
  return 0;
}

static int getprop_builtin_array(struct baik *baik, baik_val_t val,
                                 const char *name, size_t name_len,
                                 baik_val_t *res) {
  if (strcmp(name, "splice") == 0) {
    *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_array_splice);
    return 1;
  } else if (strcmp(name, "push") == 0) {
    *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_array_push_internal);
    return 1;
  } else if (strcmp(name, "panjang") == 0) {
    *res = baik_mk_number(baik, baik_array_length(baik, val));
    return 1;
  }

  (void) name_len;
  return 0;
}

static int getprop_builtin_foreign(struct baik *baik, baik_val_t val,
                                   const char *name, size_t name_len,
                                   baik_val_t *res) {
  int isnum = 0;
  int idx = cstr_to_ulong(name, name_len, &isnum);

  if (!isnum) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : index harus angka");
  } else {
    uint8_t *ptr = (uint8_t *) baik_get_ptr(baik, val);
    *res = baik_mk_number(baik, *(ptr + idx));
  }
  return 1;
}

static void baik_apply_(struct baik *baik) {
  baik_val_t res = BAIK_UNDEFINED, *args = NULL;
  baik_val_t func = baik->vals.this_obj, v = baik_arg(baik, 1);
  int i, nargs = 0;
  if (baik_is_array(v)) {
    nargs = baik_array_length(baik, v);
    args = calloc(nargs, sizeof(args[0]));
    for (i = 0; i < nargs; i++) args[i] = baik_array_get(baik, v, i);
  }
  baik_apply(baik, &res, func, baik_arg(baik, 0), nargs, args);
  free(args);
  baik_return(baik, res);
}

static int getprop_builtin(struct baik *baik, baik_val_t val, baik_val_t name,
                           baik_val_t *res) {
  size_t n;
  char *s = NULL;
  int need_free = 0;
  int handled = 0;

  baik_err_t err = baik_to_string(baik, &name, &s, &n, &need_free);

  if (err == BAIK_OK) {
    if (baik_is_string(val)) {
      handled = getprop_builtin_string(baik, val, s, n, res);
    } else if (s != NULL && n == 5 && strncmp(s, "apply", n) == 0) {
      *res = baik_mk_foreign_func(baik, (baik_func_ptr_t) baik_apply_);
      handled = 1;
    } else if (baik_is_array(val)) {
      handled = getprop_builtin_array(baik, val, s, n, res);
    } else if (baik_is_foreign(val)) {
      handled = getprop_builtin_foreign(baik, val, s, n, res);
    }
  }

  if (need_free) {
    free(s);
    s = NULL;
  }

  return handled;
}

BAIK_PRIVATE baik_err_t baik_execute(struct baik *baik, size_t off, baik_val_t *res) {
  size_t i;
  uint8_t prev_opcode = OP_MAX;
  uint8_t opcode = OP_MAX;

 
  int stack_len = baik->stack.len;
  int call_stack_len = baik->call_stack.len;
  int arg_stack_len = baik->arg_stack.len;
  int scopes_len = baik->scopes.len;
  int loop_addresses_len = baik->loop_addresses.len;
  size_t start_off = off;
  const uint8_t *code;

  struct baik_bcode_part bp = *baik_bcode_part_get_by_offset(baik, off);

  baik_set_errorf(baik, BAIK_OK, NULL);
  free(baik->stack_trace);
  baik->stack_trace = NULL;

  off -= bp.start_idx;

  for (i = off; i < bp.data.len; i++) {
    baik->cur_bcode_offset = i;

    if (baik->need_gc) {
      if (maybe_gc(baik)) {
        baik->need_gc = 0;
      }
    }
#if BAIK_AGGRESSIVE_GC
    maybe_gc(baik);
#endif

    code = (const uint8_t *) bp.data.p;
    baik_disasm_single(code, i);
    prev_opcode = opcode;
    opcode = code[i];
    switch (opcode) {
      case OP_BCODE_HEADER: {
        baik_header_item_t bcode_offset;
        memcpy(&bcode_offset,
               code + i + 1 +
                   sizeof(baik_header_item_t) * BAIK_HDR_ITEM_BCODE_OFFSET,
               sizeof(bcode_offset));
        i += bcode_offset;
      } break;
      case OP_PUSH_NULL:
        baik_push(baik, baik_mk_null());
        break;
      case OP_PUSH_UNDEF:
        baik_push(baik, baik_mk_undefined());
        break;
      case OP_PUSH_FALSE:
        baik_push(baik, baik_mk_boolean(baik, 0));
        break;
      case OP_PUSH_TRUE:
        baik_push(baik, baik_mk_boolean(baik, 1));
        break;
      case OP_PUSH_OBJ:
        baik_push(baik, baik_mk_object(baik));
        break;
      case OP_PUSH_ARRAY:
        baik_push(baik, baik_mk_array(baik));
        break;
      case OP_PUSH_FUNC: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        baik_push(baik, baik_mk_function(baik, bp.start_idx + i - n));
        i += llen;
        break;
      }
      case OP_PUSH_THIS:
        baik_push(baik, baik->vals.this_obj);
        break;
      case OP_JMP: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        i += n + llen;
        break;
      }
      case OP_JMP_FALSE: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (!baik_is_truthy(baik, baik_pop(baik))) {
          baik_push(baik, BAIK_UNDEFINED);
          i += n;
        }
        break;
      }
     
      case OP_JMP_NEUTRAL_TRUE: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (baik_is_truthy(baik, vtop(&baik->stack))) {
          i += n;
        }
        break;
      }
      case OP_JMP_NEUTRAL_FALSE: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        i += llen;
        if (!baik_is_truthy(baik, vtop(&baik->stack))) {
          i += n;
        }
        break;
      }
      case OP_FIND_SCOPE: {
        baik_val_t key = vtop(&baik->stack);
        baik_push(baik, baik_find_scope(baik, key));
        break;
      }
      case OP_CREATE: {
        baik_val_t obj = baik_pop(baik);
        baik_val_t key = baik_pop(baik);
        if (baik_get_own_property_v(baik, obj, key) == NULL) {
          baik_set_v(baik, obj, key, BAIK_UNDEFINED);
        }
        break;
      }
      case OP_APPEND: {
        baik_val_t val = baik_pop(baik);
        baik_val_t arr = baik_pop(baik);
        baik_err_t err = baik_array_push(baik, arr, val);
        if (err != BAIK_OK) {
          baik_set_errorf(baik, BAIK_TYPE_ERROR, "append to non-array");
        }
        break;
      }
      case OP_GET: {
        baik_val_t obj = baik_pop(baik);
        baik_val_t key = baik_pop(baik);
        baik_val_t val = BAIK_UNDEFINED;

        if (!getprop_builtin(baik, obj, key, &val)) {
          if (baik_is_object(obj)) {
            val = baik_get_v_proto(baik, obj, key);
          } else {
            baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : tipe galat");
          }
        }

        baik_push(baik, val);
        if (prev_opcode != OP_FIND_SCOPE) {
         
          baik->vals.last_getprop_obj = obj;
        } else {
         
          baik->vals.last_getprop_obj = BAIK_UNDEFINED;
        }
        break;
      }
      case OP_DEL_SCOPE:
        if (baik->scopes.len <= 1) {
          baik_set_errorf(baik, BAIK_INTERNAL_ERROR, "scopes underflow");
        } else {
          baik_pop_val(&baik->scopes);
        }
        break;
      case OP_NEW_SCOPE:
        push_baik_val(&baik->scopes, baik_mk_object(baik));
        break;
      case OP_PUSH_SCOPE:
        assert(baik_stack_size(&baik->scopes) > 0);
        baik_push(baik, vtop(&baik->scopes));
        break;
      case OP_PUSH_STR: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        baik_push(baik, baik_mk_string(baik, (char *) code + i + 1 + llen, n, 1));
        i += llen + n;
        break;
      }
      case OP_PUSH_INT: {
        int llen;
        int64_t n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        baik_push(baik, baik_mk_number(baik, (double) n));
        i += llen;
        break;
      }
      case OP_PUSH_DBL: {
        int llen, n = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen);
        baik_push(baik, baik_mk_number(
                          baik, strtod((char *) code + i + 1 + llen, NULL)));
        i += llen + n;
        break;
      }
      case OP_FOR_IN_NEXT: {
       
        baik_val_t *iterator = vptr(&baik->stack, -1);
        baik_val_t obj = *vptr(&baik->stack, -2);
        if (baik_is_object(obj)) {
          baik_val_t var_name = *vptr(&baik->stack, -3);
          baik_val_t key = baik_next(baik, obj, iterator);
          if (key != BAIK_UNDEFINED) {
            baik_val_t scope = baik_find_scope(baik, var_name);
            baik_set_v(baik, scope, var_name, key);
          }
        } else {
          baik_set_errorf(baik, BAIK_TYPE_ERROR,
                         "can't iterate over non-object value");
        }
        break;
      }
      case OP_RETURN: {
       
        size_t off_ret = call_stack_restore_frame(baik);
        if (off_ret != BAIK_BCODE_OFFSET_EXIT) {
          bp = *baik_bcode_part_get_by_offset(baik, off_ret);
          code = (const uint8_t *) bp.data.p;
          i = off_ret - bp.start_idx;
          LOG(LL_VERBOSE_DEBUG, ("RETURNING TO %d", (int) off_ret + 1));
        } else {
          goto clean;
        }
        
        break;
      }
      case OP_ARGS: {
       
        if (prev_opcode != OP_GET) {
          baik->vals.last_getprop_obj = BAIK_UNDEFINED;
        }

       
        push_baik_val(&baik->arg_stack, baik->vals.last_getprop_obj);
       
        push_baik_val(&baik->arg_stack,
                     baik_mk_number(baik, (double) baik_stack_size(&baik->stack)));
        break;
      }
      case OP_CALL: {
        
        
        int func_pos;
        baik_val_t *func;
        baik_val_t retval_stack_idx = vtop(&baik->arg_stack);
        func_pos = baik_get_int(baik, retval_stack_idx) - 1;
        func = vptr(&baik->stack, func_pos);

       
        baik_pop_val(&baik->arg_stack);

        if (baik_is_function(*func)) {
          size_t off_call;
          call_stack_push_frame(baik, bp.start_idx + i, retval_stack_idx);

         
          off_call = baik_get_func_addr(*func) - 1;
          bp = *baik_bcode_part_get_by_offset(baik, off_call);
          code = (const uint8_t *) bp.data.p;
          i = off_call - bp.start_idx;

          *func = BAIK_UNDEFINED;  
          
        } else if (baik_is_string(*func) || baik_is_ffi_sig(*func)) {
         

          call_stack_push_frame(baik, bp.start_idx + i, retval_stack_idx);

         
          baik_ffi_call2(baik);

          call_stack_restore_frame(baik);
        } else if (baik_is_foreign(*func)) {
         

          call_stack_push_frame(baik, bp.start_idx + i, retval_stack_idx);

         
          ((void (*) (struct baik *)) baik_get_ptr(baik, *func))(baik);

          call_stack_restore_frame(baik);
        } else {
          baik_set_errorf(baik, BAIK_TYPE_ERROR, "calling non-callable");
        }
        break;
      }
      case OP_SET_ARG: {
        int llen1, llen2, n,
            arg_no = BAIK_EM_varint_decode_unsafe(&code[i + 1], &llen1);
        baik_val_t obj, key, v;
        n = BAIK_EM_varint_decode_unsafe(&code[i + llen1 + 1], &llen2);
        key = baik_mk_string(baik, (char *) code + i + 1 + llen1 + llen2, n, 1);
        obj = vtop(&baik->scopes);
        v = baik_arg(baik, arg_no);
        baik_set_v(baik, obj, key, v);
        i += llen1 + llen2 + n;
        break;
      }
      case OP_SETRETVAL: {
        if (baik_stack_size(&baik->call_stack) < CALL_STACK_FRAME_ITEMS_CNT) {
          baik_set_errorf(baik, BAIK_INTERNAL_ERROR, "cannot return");
        } else {
          size_t retval_pos = baik_get_int(
              baik, *vptr(&baik->call_stack,
                         -1 - CALL_STACK_FRAME_ITEM_RETVAL_STACK_IDX));
          *vptr(&baik->stack, retval_pos - 1) = baik_pop(baik);
        }
        
        
        break;
      }
      case OP_EXPR: {
        int op = code[i + 1];
        exec_expr(baik, op);
        i++;
        break;
      }
      case OP_DROP: {
        baik_pop(baik);
        break;
      }
      case OP_DUP: {
        baik_push(baik, vtop(&baik->stack));
        break;
      }
      case OP_SWAP: {
        baik_val_t a = baik_pop(baik);
        baik_val_t b = baik_pop(baik);
        baik_push(baik, a);
        baik_push(baik, b);
        break;
      }
      case OP_LOOP: {
        int l1, l2, off = BAIK_EM_varint_decode_unsafe(&code[i + 1], &l1);
       
        push_baik_val(&baik->loop_addresses,
                     baik_mk_number(baik, (double) baik_stack_size(&baik->scopes)));

       
        push_baik_val(
            &baik->loop_addresses,
            baik_mk_number(baik, (double) (i + 1 + l1 + off)));
        off = BAIK_EM_varint_decode_unsafe(&code[i + 1 + l1], &l2);

       
        push_baik_val(
            &baik->loop_addresses,
            baik_mk_number(baik, (double) (i + 1 + l1 + l2 + off)));
        i += l1 + l2;
        break;
      }
      case OP_CONTINUE: {
        if (baik_stack_size(&baik->loop_addresses) >= 3) {
          size_t scopes_len = baik_get_int(baik, *vptr(&baik->loop_addresses, -3));
          assert(baik_stack_size(&baik->scopes) >= scopes_len);
          baik->scopes.len = scopes_len * sizeof(baik_val_t);

         
          i = baik_get_int(baik, vtop(&baik->loop_addresses)) - 1;
        } else {
          baik_set_errorf(baik, BAIK_SYNTAX_ERROR, "misplaced 'continue'");
        }
      } break;
      case OP_BREAK: {
        if (baik_stack_size(&baik->loop_addresses) >= 3) {
          size_t scopes_len;
         
          baik_pop_val(&baik->loop_addresses);

         
          i = baik_get_int(baik, baik_pop_val(&baik->loop_addresses)) - 1;

         
          scopes_len = baik_get_int(baik, baik_pop_val(&baik->loop_addresses));
          assert(baik_stack_size(&baik->scopes) >= scopes_len);
          baik->scopes.len = scopes_len * sizeof(baik_val_t);

          LOG(LL_VERBOSE_DEBUG, ("BREAKING TO %d", (int) i + 1));
        } else {
          baik_set_errorf(baik, BAIK_SYNTAX_ERROR, "misplaced 'break'");
        }
      } break;
      case OP_NOP:
        break;
      case OP_EXIT:
        i = bp.data.len;
        break;
      default:
#if BAIK_ENABLE_DEBUG
        baik_dump(baik, 1);
#endif
        baik_set_errorf(baik, BAIK_INTERNAL_ERROR, "Unknown opcode: %d, off %d+%d",
                       (int) opcode, (int) bp.start_idx, (int) i);
        i = bp.data.len;
        break;
    }
    if (baik->error != BAIK_OK) {
      baik_gen_stack_trace(baik, bp.start_idx + i - 1);

      baik->stack.len = stack_len;
      baik->call_stack.len = call_stack_len;
      baik->arg_stack.len = arg_stack_len;
      baik->scopes.len = scopes_len;
      baik->loop_addresses.len = loop_addresses_len;

      baik_push(baik, BAIK_UNDEFINED);
      break;
    }
  }

clean:
 
  baik_bcode_part_get_by_offset(baik, start_off)->exec_res = baik->error;

  *res = baik_pop(baik);
  return baik->error;
}

BAIK_PRIVATE baik_err_t baik_exec_internal(struct baik *baik, const char *path,
                                        const char *src, int generate_jsc,
                                        baik_val_t *res) {
  size_t off = baik->bcode_len;
  baik_val_t r = BAIK_UNDEFINED;
  baik->error = baik_parse(path, src, baik);
  if (BAIK_EM_log_level >= LL_VERBOSE_DEBUG) baik_dump(baik, 1);
  if (generate_jsc == -1) generate_jsc = baik->generate_jsc;
  if (baik->error == BAIK_OK) {
#if BAIK_GENERATE_INAC && defined(BAIK_EM_MMAP)
    if (generate_jsc && path != NULL) {
      const char *jsext = ".ina";
      int basename_len = (int) strlen(path) - strlen(jsext);
      if (basename_len > 0 && strcmp(path + basename_len, jsext) == 0) {
       
        int rewrite = 1;
        int read_mmapped = 1;

       
        const char *jscext = ".inac";
        char filename_jsc[basename_len + strlen(jscext) + 1];
        memcpy(filename_jsc, path, basename_len);
        strcpy(filename_jsc + basename_len, jscext);

       
        struct baik_bcode_part *bp =
            baik_bcode_part_get(baik, baik_bcode_parts_cnt(baik) - 1);

       
        {
          size_t size;
          char *data = BAIK_EM_mmap_file(filename_jsc, &size);
          if (data != NULL) {
            if (size == bp->data.len) {
              if (memcmp(data, bp->data.p, size) == 0) {
               
                rewrite = 0;
              }
            }
            munmap(data, size);
          }
        }

       
        if (rewrite) {
          FILE *fp = fopen(filename_jsc, "wb");
          if (fp != NULL) {
           
            fwrite(bp->data.p, bp->data.len, 1, fp);
            fclose(fp);
          } else {
            LOG(LL_WARN, ("Failed to open %s for writing", filename_jsc));
            read_mmapped = 0;
          }
        }

        if (read_mmapped) {
          free((void *) bp->data.p);
          bp->data.p = BAIK_EM_mmap_file(filename_jsc, &bp->data.len);
          bp->in_rom = 1;
        }
      }
    }
#else
    (void) generate_jsc;
#endif

    baik_execute(baik, off, &r);
  }
  if (res != NULL) *res = r;
  return baik->error;
}

baik_err_t baik_exec(struct baik *baik, const char *src, baik_val_t *res) {
  return baik_exec_internal(baik, "<stdin>", src, 0, res);
}

baik_err_t baik_exec_file(struct baik *baik, const char *path, baik_val_t *res) {
  baik_err_t error = BAIK_FILE_READ_ERROR;
  baik_val_t r = BAIK_UNDEFINED;
  size_t size;
  char *source_code = BAIK_EM_read_file(path, &size);

  if (source_code == NULL) {
    error = BAIK_FILE_READ_ERROR;
    baik_prepend_errorf(baik, error, "GALAT : gagal membaca file \"%s\"", path);
    goto clean;
  }

  r = BAIK_UNDEFINED;
  error = baik_exec_internal(baik, path, source_code, -1, &r);
  free(source_code);

clean:
  if (res != NULL) *res = r;
  return error;
}

baik_err_t baik_call(struct baik *baik, baik_val_t *res, baik_val_t func,
                   baik_val_t this_val, int nargs, ...) {
  va_list ap;
  int i;
  baik_err_t ret;
  baik_val_t *args = calloc(nargs, sizeof(baik_val_t));
  va_start(ap, nargs);
  for (i = 0; i < nargs; i++) {
    args[i] = va_arg(ap, baik_val_t);
  }
  va_end(ap);

  ret = baik_apply(baik, res, func, this_val, nargs, args);

  free(args);
  return ret;
}

baik_err_t baik_apply(struct baik *baik, baik_val_t *res, baik_val_t func,
                    baik_val_t this_val, int nargs, baik_val_t *args) {
  baik_val_t r, prev_this_val, retval_stack_idx, *resp;
  int i;

  if (!baik_is_function(func) && !baik_is_foreign(func) &&
      !baik_is_ffi_sig(func)) {
    return baik_set_errorf(baik, BAIK_TYPE_ERROR, "calling non-callable");
  }

  LOG(LL_VERBOSE_DEBUG, ("applying func %d", (int) baik_get_func_addr(func)));

  prev_this_val = baik->vals.this_obj;

  baik_push(baik, func);
  resp = vptr(&baik->stack, -1);
  retval_stack_idx = baik_mk_number(baik, (double) baik_stack_size(&baik->stack));

  for (i = 0; i < nargs; i++) {
    baik_push(baik, args[i]);
  }

  push_baik_val(&baik->arg_stack, this_val);
  call_stack_push_frame(baik, BAIK_BCODE_OFFSET_EXIT, retval_stack_idx);

  if (baik_is_foreign(func)) {
    ((void (*) (struct baik *)) baik_get_ptr(baik, func))(baik);
    if (res != NULL) *res = *resp;
  } else if (baik_is_ffi_sig(func)) {
    baik_ffi_call2(baik);
    if (res != NULL) *res = *resp;
  } else {
    size_t addr = baik_get_func_addr(func);
    baik_execute(baik, addr, &r);
    if (res != NULL) *res = r;
  }

  if (baik->error != BAIK_OK) {
    call_stack_restore_frame(baik);

    
    baik_pop(baik);
  }
  baik->vals.this_obj = prev_this_val;

  return baik->error;
}

#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT NULL
#endif

static ffi_fn_t *get_cb_impl_by_signature(const baik_ffi_sig_t *sig);


struct cbdata {
  baik_val_t func;
  baik_val_t userdata;
  int8_t func_idx;
  int8_t userdata_idx;
};

void baik_set_ffi_resolver(struct baik *baik, baik_ffi_resolver_t *dlsym) {
  baik->dlsym = dlsym;
}

static baik_ffi_ctype_t parse_cval_type(struct baik *baik, const char *s,
                                       const char *e) {
  struct baik_generic_str ms = GENERIC_NULL_STR;
 
  while (s < e && isspace((int) *s)) s++;
  while (e > s && isspace((int) e[-1])) e--;
  ms.p = s;
  ms.len = e - s;
  if (baik_generic_vcmp(&ms, "void") == 0) {
    return BAIK_FFI_CTYPE_NONE;
  } else if (baik_generic_vcmp(&ms, "userdata") == 0) {
    return BAIK_FFI_CTYPE_USERDATA;
  } else if (baik_generic_vcmp(&ms, "int") == 0) {
    return BAIK_FFI_CTYPE_INT;
  } else if (baik_generic_vcmp(&ms, "bool") == 0) {
    return BAIK_FFI_CTYPE_BOOL;
  } else if (baik_generic_vcmp(&ms, "double") == 0) {
    return BAIK_FFI_CTYPE_DOUBLE;
  } else if (baik_generic_vcmp(&ms, "float") == 0) {
    return BAIK_FFI_CTYPE_FLOAT;
  } else if (baik_generic_vcmp(&ms, "char*") == 0 || baik_generic_vcmp(&ms, "char *") == 0) {
    return BAIK_FFI_CTYPE_CHAR_PTR;
  } else if (baik_generic_vcmp(&ms, "void*") == 0 || baik_generic_vcmp(&ms, "void *") == 0) {
    return BAIK_FFI_CTYPE_VOID_PTR;
  } else if (baik_generic_vcmp(&ms, "struct baik_generic_str") == 0) {
    return BAIK_FFI_CTYPE_STRUCT_GENERIC_STR;
  } else if (baik_generic_vcmp(&ms, "struct baik_generic_str *") == 0 ||
             baik_generic_vcmp(&ms, "struct baik_generic_str*") == 0) {
    return BAIK_FFI_CTYPE_STRUCT_GENERIC_STR_PTR;
  } else {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : gagal menguraikan isi tipe \"%.*s\"",
                       (int) ms.len, ms.p);
    return BAIK_FFI_CTYPE_INVALID;
  }
}

static const char *find_paren(const char *s, const char *e) {
  for (; s < e; s++) {
    if (*s == '(') return s;
  }
  return NULL;
}

static const char *find_closing_paren(const char *s, const char *e) {
  int nesting = 1;
  while (s < e) {
    if (*s == '(') {
      nesting++;
    } else if (*s == ')') {
      if (--nesting == 0) break;
    }
    s++;
  }
  return (s < e ? s : NULL);
}

BAIK_PRIVATE baik_err_t baik_parse_ffi_signature(struct baik *baik, const char *s,
                                              int sig_len, baik_ffi_sig_t *sig,
                                              enum ffi_sig_type sig_type) {
  baik_err_t ret = BAIK_OK;
  int vtidx = 0;
  const char *cur, *e, *tmp_e, *tmp;
  struct baik_generic_str rt = GENERIC_NULL_STR, fn = GENERIC_NULL_STR, args = GENERIC_NULL_STR;
  baik_ffi_ctype_t val_type = BAIK_FFI_CTYPE_INVALID;
  if (sig_len == ~0) {
    sig_len = strlen(s);
  }
  e = s + sig_len;

  baik_ffi_sig_init(sig);
  for (cur = s; cur < e && isspace((int) *cur); cur++);

  tmp_e = find_paren(cur, e);
  if (tmp_e == NULL || tmp_e - s < 2) {
    ret = BAIK_TYPE_ERROR;
    baik_prepend_errorf(baik, ret, "1");
    goto clean;
  }
  tmp = find_closing_paren(tmp_e + 1, e);
  if (tmp == NULL) {
    ret = BAIK_TYPE_ERROR;
    baik_prepend_errorf(baik, ret, "2");
    goto clean;
  }

  args.p = find_paren(tmp + 1, e);
  if (args.p == NULL) {
   
    fn.p = tmp_e - 1;
    while (fn.p > cur && isspace((int) *fn.p)) fn.p--;
    while (fn.p > cur && (isalnum((int) *fn.p) || *fn.p == '_')) {
      fn.p--;
      fn.len++;
    }
    fn.p++;
    rt.p = cur;
    rt.len = fn.p - rt.p;
   
    args.p = tmp_e + 1;
    args.len = tmp - args.p;
  } else {
   
    fn.p = tmp + 1;
    fn.len = args.p - tmp;
    rt.p = cur;
    rt.len = tmp_e - rt.p;
    args.p++;
    tmp = find_closing_paren(args.p, e);
    if (tmp == NULL) {
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret, "3");
      goto clean;
    }
    args.len = tmp - args.p;
   
    sig->is_callback = 1;
  }

  val_type = parse_cval_type(baik, rt.p, rt.p + rt.len);
  if (val_type == BAIK_FFI_CTYPE_INVALID) {
    ret = baik->error;
    goto clean;
  }
  baik_ffi_sig_set_val_type(sig, vtidx++, val_type);

  if (!sig->is_callback) {
    char buf[100];
    if (baik->dlsym == NULL) {
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret,
                         "GALAT : resolver belum diaktifkan, panggil baik_set_ffi_resolver");
      goto clean;
    }

    snprintf(buf, sizeof(buf), "%.*s", (int) fn.len, fn.p);
    sig->fn = (ffi_fn_t *) baik->dlsym(RTLD_DEFAULT, buf);
    if (sig->fn == NULL) {
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret, "GALAT : dlsym('%s') gagal", buf);
      goto clean;
    }
  } else {
    tmp_e = strchr(tmp_e, ')');
    if (tmp_e == NULL) {
      ret = BAIK_TYPE_ERROR;
      goto clean;
    }
  }

  cur = tmp_e = args.p;

  while (tmp_e - args.p < (ptrdiff_t) args.len) {
    int level = 0;
    int is_fp = 0;
    tmp_e = cur;

    while (*tmp_e && (level > 0 || (*tmp_e != ',' && *tmp_e != ')'))) {
      switch (*tmp_e) {
        case '(':
          level++;
         
          is_fp = 1;
          break;
        case ')':
          level--;
          break;
      }
      tmp_e++;
    }

    if (tmp_e == cur) break;

    if (is_fp) {
     
      if (sig->cb_sig != NULL) {
       
        ret = BAIK_TYPE_ERROR;
        baik_prepend_errorf(baik, ret, "GALAT : hanya satu callback yang diijinkan");
        goto clean;
      }

      sig->cb_sig = calloc(sizeof(*sig->cb_sig), 1);
      ret = baik_parse_ffi_signature(baik, cur, tmp_e - cur, sig->cb_sig,
                                    FFI_SIG_CALLBACK);
      if (ret != BAIK_OK) {
        baik_ffi_sig_free(sig->cb_sig);
        free(sig->cb_sig);
        sig->cb_sig = NULL;
        goto clean;
      }
      val_type = BAIK_FFI_CTYPE_CALLBACK;
    } else {
     
      val_type = parse_cval_type(baik, cur, tmp_e);
      if (val_type == BAIK_FFI_CTYPE_INVALID) {
       
        ret = BAIK_TYPE_ERROR;
        goto clean;
      }
    }

    if (!baik_ffi_sig_set_val_type(sig, vtidx++, val_type)) {
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret, "GALAT : begitu banyak argumen callback");
      goto clean;
    }

    if (*tmp_e == ',') {
      cur = tmp_e + 1;
      while (*cur == ' ') cur++;
    } else {
     
      break;
    }
  }
 

 
  baik_ffi_sig_validate(baik, sig, sig_type);
  if (!sig->is_valid) {
    ret = BAIK_TYPE_ERROR;
    goto clean;
  }

  if (sig->is_callback) {
    sig->fn = get_cb_impl_by_signature(sig);
    if (sig->fn == NULL) {
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret,
                         "GALAT : callback signature valid, "
                         "tetapi tidak ada callback yang terdefinisi");
      goto clean;
    }
  }

clean:
  if (ret != BAIK_OK) {
    baik_prepend_errorf(baik, ret, "GALAT : ffi signature bermasalah: \"%.*s\"", sig_len, s);
    sig->is_valid = 0;
  }
  return ret;
}

union ffi_cb_data_val {
  void *p;
  uintptr_t w;
  double d;
  float f;
};

struct ffi_cb_data {
  union ffi_cb_data_val args[BAIK_CB_ARGS_MAX_CNT];
};

static union ffi_cb_data_val ffi_cb_impl_generic(void *param,
                                                 struct ffi_cb_data *data) {
  struct baik_ffi_cb_args *cbargs = (struct baik_ffi_cb_args *) param;
  baik_val_t *args, res = BAIK_UNDEFINED;
  union ffi_cb_data_val ret;
  int i;
  struct baik *baik = cbargs->baik;
  baik_ffi_ctype_t return_ctype = BAIK_FFI_CTYPE_NONE;
  baik_err_t err;

  memset(&ret, 0, sizeof(ret));
  baik_own(baik, &res);

  assert(cbargs->sig.args_cnt > 0);

  args = calloc(1, sizeof(baik_val_t) * cbargs->sig.args_cnt);
  for (i = 0; i < cbargs->sig.args_cnt; i++) {
    baik_ffi_ctype_t val_type =
        cbargs->sig.val_types[i + 1];
    switch (val_type) {
      case BAIK_FFI_CTYPE_USERDATA:
        args[i] = cbargs->userdata;
        break;
      case BAIK_FFI_CTYPE_INT:
        args[i] = baik_mk_number(baik, (double) data->args[i].w);
        break;
      case BAIK_FFI_CTYPE_BOOL:
        args[i] = baik_mk_boolean(baik, !!data->args[i].w);
        break;
      case BAIK_FFI_CTYPE_CHAR_PTR: {
        const char *s = (char *) data->args[i].w;
        if (s == NULL) s = "";
        args[i] = baik_mk_string(baik, s, ~0, 1);
        break;
      }
      case BAIK_FFI_CTYPE_VOID_PTR:
        args[i] = baik_mk_foreign(baik, (void *) data->args[i].w);
        break;
      case BAIK_FFI_CTYPE_DOUBLE:
        args[i] = baik_mk_number(baik, data->args[i].d);
        break;
      case BAIK_FFI_CTYPE_FLOAT:
        args[i] = baik_mk_number(baik, data->args[i].f);
        break;
      case BAIK_FFI_CTYPE_STRUCT_GENERIC_STR_PTR: {
        struct baik_generic_str *s = (struct baik_generic_str *) (void *) data->args[i].w;
        args[i] = baik_mk_string(baik, s->p, s->len, 1);
        break;
      }
      default:
       
        LOG(LL_ERROR, ("unexpected val type for arg #%d: %d\n", i, val_type));
        abort();
    }
  }

 
  return_ctype = cbargs->sig.val_types[0];

  LOG(LL_VERBOSE_DEBUG, ("calling BAIK callback void-void %d from C",
                         baik_get_int(baik, cbargs->func)));
  err = baik_apply(baik, &res, cbargs->func, BAIK_UNDEFINED, cbargs->sig.args_cnt,
                  args);
  cbargs = NULL;
  if (err != BAIK_OK) {
    baik_print_error(baik, stderr, "BAIK callback error",
                    1);
    goto clean;
  }

 
  switch (return_ctype) {
    case BAIK_FFI_CTYPE_NONE:
      break;
    case BAIK_FFI_CTYPE_INT:
      ret.w = baik_get_int(baik, res);
      break;
    case BAIK_FFI_CTYPE_BOOL:
      ret.w = baik_get_bool(baik, res);
      break;
    case BAIK_FFI_CTYPE_VOID_PTR:
      ret.p = baik_get_ptr(baik, res);
      break;
    case BAIK_FFI_CTYPE_DOUBLE:
      ret.d = baik_get_double(baik, res);
      break;
    case BAIK_FFI_CTYPE_FLOAT:
      ret.f = (float) baik_get_double(baik, res);
      break;
    default:
      LOG(LL_ERROR, ("unexpected return val type %d\n", return_ctype));
      abort();
  }

clean:
  free(args);
  baik_disown(baik, &res);
  return ret;
}

static void ffi_init_cb_data_wwww(struct ffi_cb_data *data, uintptr_t w0,
                                  uintptr_t w1, uintptr_t w2, uintptr_t w3,
                                  uintptr_t w4, uintptr_t w5) {
  memset(data, 0, sizeof(*data));
  data->args[0].w = w0;
  data->args[1].w = w1;
  data->args[2].w = w2;
  data->args[3].w = w3;
  data->args[4].w = w4;
  data->args[5].w = w5;
}

static uintptr_t ffi_cb_impl_wpwwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w0, &data).w;
}

static uintptr_t ffi_cb_impl_wwpwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w1, &data).w;
}

static uintptr_t ffi_cb_impl_wwwpwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w2, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwpww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w3, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwpw(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w4, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwwp(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w5, &data).w;
}

static uintptr_t ffi_cb_impl_wpd(uintptr_t w0, double d1) {
  struct ffi_cb_data data;

  memset(&data, 0, sizeof(data));
  data.args[0].w = w0;
  data.args[1].d = d1;

  return ffi_cb_impl_generic((void *) w0, &data).w;
}

static uintptr_t ffi_cb_impl_wdp(double d0, uintptr_t w1) {
  struct ffi_cb_data data;

  memset(&data, 0, sizeof(data));
  data.args[0].d = d0;
  data.args[1].w = w1;

  return ffi_cb_impl_generic((void *) w1, &data).w;
}


static struct baik_ffi_cb_args **ffi_get_matching(struct baik_ffi_cb_args **plist,
                                                 baik_val_t func,
                                                 baik_val_t userdata) {
  for (; *plist != NULL; plist = &((*plist)->next)) {
    if ((*plist)->func == func && (*plist)->userdata == userdata) {
      break;
    }
  }
  return plist;
}

static ffi_fn_t *get_cb_impl_by_signature(const baik_ffi_sig_t *sig) {
  if (sig->is_valid) {
    int i;
    int double_cnt = 0;
    int float_cnt = 0;
    int userdata_idx = 0;

    for (i = 1; i < BAIK_CB_SIGNATURE_MAX_SIZE;
         i++) {
      baik_ffi_ctype_t type = sig->val_types[i];
      switch (type) {
        case BAIK_FFI_CTYPE_DOUBLE:
          double_cnt++;
          break;
        case BAIK_FFI_CTYPE_FLOAT:
          float_cnt++;
          break;
        case BAIK_FFI_CTYPE_USERDATA:
          assert(userdata_idx == 0);
          userdata_idx = i;
          break;
        default:
          break;
      }
    }

    if (float_cnt > 0) {
      return NULL;
    }

    assert(userdata_idx > 0);

    if (sig->args_cnt <= BAIK_CB_ARGS_MAX_CNT) {
      if (baik_ffi_is_regular_word_or_void(sig->val_types[0])) {
       
        switch (double_cnt) {
          case 0:
            switch (userdata_idx) {
              case 1:
                return (ffi_fn_t *) ffi_cb_impl_wpwwwww;
              case 2:
                return (ffi_fn_t *) ffi_cb_impl_wwpwwww;
              case 3:
                return (ffi_fn_t *) ffi_cb_impl_wwwpwww;
              case 4:
                return (ffi_fn_t *) ffi_cb_impl_wwwwpww;
              case 5:
                return (ffi_fn_t *) ffi_cb_impl_wwwwwpw;
              case 6:
                return (ffi_fn_t *) ffi_cb_impl_wwwwwwp;
              default:
                abort();
            }
            break;
          case 1:
           
            switch (userdata_idx) {
              case 1:
                return (ffi_fn_t *) ffi_cb_impl_wpd;
              case 2:
                return (ffi_fn_t *) ffi_cb_impl_wdp;
            }
            break;
        }
      }
    } else {}
  }

  return NULL;
}

BAIK_PRIVATE baik_val_t baik_ffi_sig_to_value(struct baik_ffi_sig *psig) {
  if (psig == NULL) {
    return BAIK_NULL;
  } else {
    return baik_legit_pointer_to_value(psig) | BAIK_TAG_FUNCTION_FFI;
  }
}

BAIK_PRIVATE int baik_is_ffi_sig(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_FUNCTION_FFI;
}

BAIK_PRIVATE struct baik_ffi_sig *baik_get_ffi_sig_struct(baik_val_t v) {
  struct baik_ffi_sig *ret = NULL;
  assert(baik_is_ffi_sig(v));
  ret = (struct baik_ffi_sig *) get_ptr(v);
  return ret;
}

BAIK_PRIVATE baik_val_t baik_mk_ffi_sig(struct baik *baik) {
  struct baik_ffi_sig *psig = new_ffi_sig(baik);
  baik_ffi_sig_init(psig);
  return baik_ffi_sig_to_value(psig);
}

BAIK_PRIVATE void baik_ffi_sig_destructor(struct baik *baik, void *psig) {
  baik_ffi_sig_free((baik_ffi_sig_t *) psig);
  (void) baik;
}

BAIK_PRIVATE void *baik_dlsym(void *handle, const char *name) {
    void *client_hndl;
    typedef int main_t(int, char**);
    main_t *client_main;
    client_hndl = dlopen(baik_dlsym_file,  RTLD_LAZY);
    if (!client_hndl){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    client_main = (main_t*)dlsym(client_hndl, name);
    if (!client_main){
        fprintf(stderr, "%s\n", dlerror());
        exit(2);
    }
    else{
        return (main_t*)dlsym(client_hndl, name);
    }
    return NULL;
}

BAIK_PRIVATE baik_err_t baik_ffi_call(struct baik *baik) {
  baik_err_t e = BAIK_OK;
  const char *sig_str = NULL;
  baik_val_t sig_str_v = baik_arg(baik, 0);
  baik_val_t ret_v = BAIK_UNDEFINED;
  struct baik_ffi_sig *psig = baik_get_ffi_sig_struct(baik_mk_ffi_sig(baik));
  size_t sig_str_len;
  
  sig_str = baik_get_string(baik, &sig_str_v, &sig_str_len);

  size_t sig_str_len_dlsym_file;
  baik_val_t sig_str_v_dlsym_file = baik_arg(baik, 1);
  baik_dlsym_file = baik_get_string(baik, &sig_str_v_dlsym_file, &sig_str_len_dlsym_file);
  if(baik_dlsym_file != NULL){
    //printf("%s",baik_dlsym_file);
    baik_set_ffi_resolver(baik, baik_dlsym);
  }

  e = baik_parse_ffi_signature(baik, sig_str, sig_str_len, psig, FFI_SIG_FUNC);
  if (e != BAIK_OK) goto clean;
  ret_v = baik_ffi_sig_to_value(psig);

clean:
  baik_return(baik, ret_v);
  return e;
}

BAIK_PRIVATE baik_err_t baik_ffi_call2(struct baik *baik) {
  baik_err_t ret = BAIK_OK;
  baik_ffi_sig_t *psig = NULL;
  baik_ffi_ctype_t rtype;
  baik_val_t sig_v = *vptr(&baik->stack, baik_getretvalpos(baik));

  int i, nargs;
  struct ffi_arg res;
  struct ffi_arg args[FFI_MAX_ARGS_CNT];
  struct cbdata cbdata;

 
  baik_val_t resv = baik_mk_undefined();

 
  baik_val_t argvs[FFI_MAX_ARGS_CNT];
  struct baik_generic_str argvmgstr[FFI_MAX_ARGS_CNT];

  if (baik_is_ffi_sig(sig_v)) {
    psig = baik_get_ffi_sig_struct(sig_v);
  } else {
    ret = BAIK_TYPE_ERROR;
    baik_prepend_errorf(baik, ret, "GALAT :  isi non-ffi-callable");
    goto clean;
  }

  memset(&cbdata, 0, sizeof(cbdata));
  cbdata.func_idx = -1;
  cbdata.userdata_idx = -1;

  rtype = psig->val_types[0];

  switch (rtype) {
    case BAIK_FFI_CTYPE_DOUBLE:
      res.ctype = FFI_CTYPE_DOUBLE;
      break;
    case BAIK_FFI_CTYPE_FLOAT:
      res.ctype = FFI_CTYPE_FLOAT;
      break;
    case BAIK_FFI_CTYPE_BOOL:
      res.ctype = FFI_CTYPE_BOOL;
      break;
    case BAIK_FFI_CTYPE_USERDATA:
    case BAIK_FFI_CTYPE_INT:
    case BAIK_FFI_CTYPE_CHAR_PTR:
    case BAIK_FFI_CTYPE_VOID_PTR:
    case BAIK_FFI_CTYPE_NONE:
      res.ctype = FFI_CTYPE_WORD;
      break;
    case BAIK_FFI_CTYPE_INVALID:
      ret = BAIK_TYPE_ERROR;
      baik_prepend_errorf(baik, ret, "GALAT : kesalahan balikan tipe pada fungsi ffi");
      goto clean;
  }
  res.v.i = 0;

  nargs =
      baik_stack_size(&baik->stack) - baik_get_int(baik, vtop(&baik->call_stack));

  if (nargs != psig->args_cnt) {
    ret = BAIK_TYPE_ERROR;
    baik_prepend_errorf(baik, ret, "GALAT : got %d actuals, but function takes %d args",
                       nargs, psig->args_cnt);
    goto clean;
  }

  for (i = 0; i < nargs; i++) {
    baik_val_t arg = baik_arg(baik, i);

    switch (psig->val_types[1 + i]) {
      case BAIK_FFI_CTYPE_NONE:
       
        ret = BAIK_TYPE_ERROR;
        if (i == 0) {
         
          baik_prepend_errorf(baik, ret, "GALAT : fungsi ffi-ed tidak memiliki argumen");
        } else {
         
          baik_prepend_errorf(baik, ret, "GALAT : arg ffi bermasalah #%d tipe: \"void\"", i);
        }

        goto clean;
      case BAIK_FFI_CTYPE_USERDATA:
       
        if (cbdata.userdata_idx != -1) {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(baik, ret, "GALAT dua atau lebih argumen userdata : #%d and %d",
                             cbdata.userdata_idx, i);

          goto clean;
        }
        cbdata.userdata = arg;
        cbdata.userdata_idx = i;
        break;
      case BAIK_FFI_CTYPE_INT: {
        int intval = 0;
        if (baik_is_number(arg)) {
          intval = baik_get_int(baik, arg);
        } else if (baik_is_boolean(arg)) {
          intval = baik_get_bool(baik, arg);
        } else {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(
              baik, ret, "GALAT : arg #%d bukan int (tipe idx adalah: %s)", i,
              baik_typeof(arg));
        }
        ffi_set_word(&args[i], intval);
      } break;
      case BAIK_FFI_CTYPE_STRUCT_GENERIC_STR_PTR: {
        if (!baik_is_string(arg)) {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(
              baik, ret, "GALAT : arg #%d bukan string (tipe idx adalah: %s)",
              i, baik_typeof(arg));
          goto clean;
        }
        argvs[i] = arg;
        argvmgstr[i].p = baik_get_string(baik, &argvs[i], &argvmgstr[i].len);
       
        ffi_set_ptr(&args[i], (void *) &argvmgstr[i]);
        break;
      }
      case BAIK_FFI_CTYPE_BOOL: {
        int intval = 0;
        if (baik_is_number(arg)) {
          intval = !!baik_get_int(baik, arg);
        } else if (baik_is_boolean(arg)) {
          intval = baik_get_bool(baik, arg);
        } else {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(
              baik, ret, "GALAT : arg #%d bukan bool (tipe idx adalah: %s)", i,
              baik_typeof(arg));
        }
        ffi_set_word(&args[i], intval);
      } break;
      case BAIK_FFI_CTYPE_DOUBLE:
        ffi_set_double(&args[i], baik_get_double(baik, arg));
        break;
      case BAIK_FFI_CTYPE_FLOAT:
        ffi_set_float(&args[i], (float) baik_get_double(baik, arg));
        break;
      case BAIK_FFI_CTYPE_CHAR_PTR: {
        size_t s;
        if (baik_is_string(arg)) {
         
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) baik_get_string(baik, &argvs[i], &s));
        } else if (baik_is_null(arg)) {
          ffi_set_ptr(&args[i], NULL);
        } else {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(
              baik, ret, "GALAT : arg #%d bukan string (tipe idx adalah: %s)",
              i, baik_typeof(arg));
          goto clean;
        }
      } break;
      case BAIK_FFI_CTYPE_VOID_PTR:
        if (baik_is_string(arg)) {
          size_t n;
         
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) baik_get_string(baik, &argvs[i], &n));
        } else if (baik_is_foreign(arg)) {
          ffi_set_ptr(&args[i], (void *) baik_get_ptr(baik, arg));
        } else if (baik_is_null(arg)) {
          ffi_set_ptr(&args[i], NULL);
        } else {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(baik, ret, "GALAT : arg #%d bukan ptr", i);
          goto clean;
        }
        break;
      case BAIK_FFI_CTYPE_CALLBACK:
        if (baik_is_function(arg) || baik_is_foreign(arg) ||
            baik_is_ffi_sig(arg)) {
         
          cbdata.func = arg;
          cbdata.func_idx = i;
        } else {
          ret = BAIK_TYPE_ERROR;
          baik_prepend_errorf(baik, ret,
                             "GALAT : arg #%d bukan fungsi, tetapi %s", i,
                             baik_stringify_type((enum baik_type) arg));
          goto clean;
        }
        break;
      case BAIK_FFI_CTYPE_INVALID:
       
        ret = BAIK_TYPE_ERROR;
        baik_prepend_errorf(baik, ret, "GALAT : kesalahan tipe arg");
        goto clean;
      default:
        abort();
        break;
    }
  }

  if (cbdata.userdata_idx >= 0 && cbdata.func_idx >= 0) {
    struct baik_ffi_cb_args *cbargs = NULL;
    struct baik_ffi_cb_args **pitem = NULL;

    pitem = ffi_get_matching(&baik->ffi_cb_args, cbdata.func, cbdata.userdata);
    if (*pitem == NULL) {
     
      cbargs = calloc(1, sizeof(*cbargs));
      cbargs->baik = baik;
      cbargs->func = cbdata.func;
      cbargs->userdata = cbdata.userdata;
      baik_ffi_sig_copy(&cbargs->sig, psig->cb_sig);

      *pitem = cbargs;
    } else {
     
      cbargs = *pitem;
    }

    {
      union {
        ffi_fn_t *fn;
        void *p;
      } u;
      u.fn = psig->cb_sig->fn;
      ffi_set_ptr(&args[cbdata.func_idx], u.p);
      ffi_set_ptr(&args[cbdata.userdata_idx], cbargs);
    }
  } else if (!(cbdata.userdata_idx == -1 && cbdata.func_idx == -1)) {
   
    abort();
  }

  ffi_call(psig->fn, nargs, &res, args);

  switch (rtype) {
    case BAIK_FFI_CTYPE_CHAR_PTR: {
      const char *s = (const char *) (uintptr_t) res.v.i;
      if (s != NULL) {
        resv = baik_mk_string(baik, s, ~0, 1);
      } else {
        resv = BAIK_NULL;
      }
      break;
    }
    case BAIK_FFI_CTYPE_VOID_PTR:
      resv = baik_mk_foreign(baik, (void *) (uintptr_t) res.v.i);
      break;
    case BAIK_FFI_CTYPE_INT:
      resv = baik_mk_number(baik, (int) res.v.i);
      break;
    case BAIK_FFI_CTYPE_BOOL:
      resv = baik_mk_boolean(baik, !!res.v.i);
      break;
    case BAIK_FFI_CTYPE_DOUBLE:
      resv = baik_mk_number(baik, res.v.d);
      break;
    case BAIK_FFI_CTYPE_FLOAT:
      resv = baik_mk_number(baik, res.v.f);
      break;
    default:
      resv = baik_mk_undefined();
      break;
  }

clean:
 
  if (ret != BAIK_OK) {
    baik_prepend_errorf(baik, ret, "GALAT : gagal memanggil fungsi FFIed");
   
  }
  baik_return(baik, resv);

  return ret;
}

BAIK_PRIVATE void baik_ffi_cb_free(struct baik *baik) {
  baik_val_t ret = baik_mk_number(baik, 0);
  baik_val_t func = baik_arg(baik, 0);
  baik_val_t userdata = baik_arg(baik, 1);

  if (baik_is_function(func)) {
    struct baik_ffi_cb_args **pitem =
        ffi_get_matching(&baik->ffi_cb_args, func, userdata);
    if (*pitem != NULL) {
     
      struct baik_ffi_cb_args *cbargs = *pitem;
      *pitem = cbargs->next;
      baik_ffi_sig_free(&cbargs->sig);
      free(cbargs);
      ret = baik_mk_number(baik, 1);
    }
  } else {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : kesalahan argumen 'func'");
  }

  baik_return(baik, ret);
}

void baik_ffi_args_free_list(struct baik *baik) {
  ffi_cb_args_t *next = baik->ffi_cb_args;

  while (next != NULL) {
    ffi_cb_args_t *cur = next;
    next = next->next;
    free(cur);
  }
}

BAIK_PRIVATE void baik_ffi_sig_init(baik_ffi_sig_t *sig) {
  memset(sig, 0, sizeof(*sig));
}

BAIK_PRIVATE void baik_ffi_sig_copy(baik_ffi_sig_t *to,
                                  const baik_ffi_sig_t *from) {
  memcpy(to, from, sizeof(*to));
  if (from->cb_sig != NULL) {
    to->cb_sig = calloc(sizeof(*to->cb_sig), 1);
    baik_ffi_sig_copy(to->cb_sig, from->cb_sig);
  }
}

BAIK_PRIVATE void baik_ffi_sig_free(baik_ffi_sig_t *sig) {
  if (sig->cb_sig != NULL) {
    free(sig->cb_sig);
    sig->cb_sig = NULL;
  }
}

BAIK_PRIVATE int baik_ffi_sig_set_val_type(baik_ffi_sig_t *sig, int idx,
                                         baik_ffi_ctype_t type) {
  if (idx < BAIK_CB_SIGNATURE_MAX_SIZE) {
    sig->val_types[idx] = type;
    return 1;
  } else {
   
    return 0;
  }
}

BAIK_PRIVATE int baik_ffi_sig_validate(struct baik *baik, baik_ffi_sig_t *sig,
                                     enum ffi_sig_type sig_type) {
  int ret = 0;
  int i;
  int callback_idx = 0;
  int userdata_idx = 0;

  sig->is_valid = 0;

  switch (sig_type) {
    case FFI_SIG_FUNC:
     
      if (sig->val_types[0] != BAIK_FFI_CTYPE_NONE &&
          sig->val_types[0] != BAIK_FFI_CTYPE_INT &&
          sig->val_types[0] != BAIK_FFI_CTYPE_BOOL &&
          sig->val_types[0] != BAIK_FFI_CTYPE_DOUBLE &&
          sig->val_types[0] != BAIK_FFI_CTYPE_FLOAT &&
          sig->val_types[0] != BAIK_FFI_CTYPE_VOID_PTR &&
          sig->val_types[0] != BAIK_FFI_CTYPE_CHAR_PTR) {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : nilai tipe balikan salah");
        goto clean;
      }
      break;
    case FFI_SIG_CALLBACK:
     
      if (sig->val_types[0] != BAIK_FFI_CTYPE_NONE &&
          sig->val_types[0] != BAIK_FFI_CTYPE_INT &&
          sig->val_types[0] != BAIK_FFI_CTYPE_BOOL &&
          sig->val_types[0] != BAIK_FFI_CTYPE_DOUBLE &&
          sig->val_types[0] != BAIK_FFI_CTYPE_FLOAT &&
          sig->val_types[0] != BAIK_FFI_CTYPE_VOID_PTR) {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : tipe nilai balikan salah");
        goto clean;
      }
  }

 
  for (i = 1; i < BAIK_CB_SIGNATURE_MAX_SIZE; i++) {
    baik_ffi_ctype_t type = sig->val_types[i];
    switch (type) {
      case BAIK_FFI_CTYPE_USERDATA:
        if (userdata_idx != 0) {
         
          baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                             "GALAT : lebih dari satu userdata arg: #%d dan #%d",
                             (userdata_idx - 1), (i - 1));
          goto clean;
        }
        userdata_idx = i;
        break;
      case BAIK_FFI_CTYPE_CALLBACK:
        switch (sig_type) {
          case FFI_SIG_FUNC:
            break;
          case FFI_SIG_CALLBACK:
            baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                               "GALAT : callback tidak mendapatkan callback lainnya");
            goto clean;
        }
        callback_idx = i;
        break;
      case BAIK_FFI_CTYPE_INT:
      case BAIK_FFI_CTYPE_BOOL:
      case BAIK_FFI_CTYPE_VOID_PTR:
      case BAIK_FFI_CTYPE_CHAR_PTR:
      case BAIK_FFI_CTYPE_STRUCT_GENERIC_STR_PTR:
      case BAIK_FFI_CTYPE_DOUBLE:
      case BAIK_FFI_CTYPE_FLOAT:
       
        break;
      case BAIK_FFI_CTYPE_NONE:
       
        goto args_over;
      default:
        baik_prepend_errorf(baik, BAIK_INTERNAL_ERROR, "GALAT : kesalahan ffi_ctype: %d",
                           type);
        goto clean;
    }

    sig->args_cnt++;
  }
args_over:

  switch (sig_type) {
    case FFI_SIG_FUNC:
      if (!((callback_idx > 0 && userdata_idx > 0) ||
            (callback_idx == 0 && userdata_idx == 0))) {
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                           "GALAT : callback and userdata should be either both "
                           "present or both absent");
        goto clean;
      }
      break;
    case FFI_SIG_CALLBACK:
      if (userdata_idx == 0) {
       
        baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : tanpa userdata arg");
        goto clean;
      }
      break;
  }

  ret = 1;

clean:
  if (ret) {
    sig->is_valid = 1;
  }
  return ret;
}

BAIK_PRIVATE int baik_ffi_is_regular_word(baik_ffi_ctype_t type) {
  switch (type) {
    case BAIK_FFI_CTYPE_INT:
    case BAIK_FFI_CTYPE_BOOL:
      return 1;
    default:
      return 0;
  }
}

BAIK_PRIVATE int baik_ffi_is_regular_word_or_void(baik_ffi_ctype_t type) {
  return (type == BAIK_FFI_CTYPE_NONE || baik_ffi_is_regular_word(type));
}

#ifdef _WIN32
void *dlsym(void *handle, const char *name) {
  static HANDLE msvcrt_dll;
  void *sym = NULL;
  if (msvcrt_dll == NULL) msvcrt_dll = GetModuleHandle("msvcrt.dll");
  if ((sym = GetProcAddress(GetModuleHandle(NULL), name)) == NULL) {
    sym = GetProcAddress(msvcrt_dll, name);
  }
  return sym;
}
#elif !defined(__unix__) && !defined(__APPLE__)
void *dlsym(void *handle, const char *name) {
  (void) handle;
  (void) name;
  return NULL;
}
#endif

#include <stdio.h>

#define MARK(p) (((struct gc_cell *) (p))->head.word |= 1)
#define UNMARK(p) (((struct gc_cell *) (p))->head.word &= ~1)
#define MARKED(p) (((struct gc_cell *) (p))->head.word & 1)
#define MARK_FREE(p) (((struct gc_cell *) (p))->head.word |= 2)
#define UNMARK_FREE(p) (((struct gc_cell *) (p))->head.word &= ~2)
#define MARKED_FREE(p) (((struct gc_cell *) (p))->head.word & 2)
#define GC_ARENA_CELLS_RESERVE 2

static struct gc_block *gc_new_block(struct gc_arena *a, size_t size);
static void gc_free_block(struct gc_block *b);
static void gc_mark_mbuf_pt(struct baik *baik, const struct mbuf *mbuf);

BAIK_PRIVATE struct baik_object *new_object(struct baik *baik) {
  return (struct baik_object *) gc_alloc_cell(baik, &baik->object_arena);
}

BAIK_PRIVATE struct baik_property *new_property(struct baik *baik) {
  return (struct baik_property *) gc_alloc_cell(baik, &baik->property_arena);
}

BAIK_PRIVATE struct baik_ffi_sig *new_ffi_sig(struct baik *baik) {
  return (struct baik_ffi_sig *) gc_alloc_cell(baik, &baik->ffi_sig_arena);
}

BAIK_PRIVATE void gc_arena_init(struct gc_arena *a, size_t cell_size,
                               size_t initial_size, size_t size_increment) {
  assert(cell_size >= sizeof(uintptr_t));

  memset(a, 0, sizeof(*a));
  a->cell_size = cell_size;
  a->size_increment = size_increment;
  a->blocks = gc_new_block(a, initial_size);
}

BAIK_PRIVATE void gc_arena_destroy(struct baik *baik, struct gc_arena *a) {
  struct gc_block *b;

  if (a->blocks != NULL) {
    gc_sweep(baik, a, 0);
    for (b = a->blocks; b != NULL;) {
      struct gc_block *tmp;
      tmp = b;
      b = b->next;
      gc_free_block(tmp);
    }
  }
}

static void gc_free_block(struct gc_block *b) {
  free(b->base);
  free(b);
}

static struct gc_block *gc_new_block(struct gc_arena *a, size_t size) {
  struct gc_cell *cur;
  struct gc_block *b;

  b = (struct gc_block *) calloc(1, sizeof(*b));
  if (b == NULL) abort();

  b->size = size;
  b->base = (struct gc_cell *) calloc(a->cell_size, b->size);
  if (b->base == NULL) abort();

  for (cur = GC_CELL_OP(a, b->base, +, 0);
       cur < GC_CELL_OP(a, b->base, +, b->size);
       cur = GC_CELL_OP(a, cur, +, 1)) {
    cur->head.link = a->free;
    a->free = cur;
  }

  return b;
}


static int gc_arena_is_gc_needed(struct gc_arena *a) {
  struct gc_cell *r = a->free;
  int i;

  for (i = 0; i <= GC_ARENA_CELLS_RESERVE; i++, r = r->head.link) {
    if (r == NULL) {
      return 1;
    }
  }

  return 0;
}

BAIK_PRIVATE int gc_strings_is_gc_needed(struct baik *baik) {
  struct mbuf *m = &baik->owned_strings;
  return (double) m->len / (double) m->size > 0.9;
}

BAIK_PRIVATE void *gc_alloc_cell(struct baik *baik, struct gc_arena *a) {
  struct gc_cell *r;

  if (a->free == NULL) {
    struct gc_block *b = gc_new_block(a, a->size_increment);
    b->next = a->blocks;
    a->blocks = b;
  }
  r = a->free;

  UNMARK(r);

  a->free = r->head.link;

#if BAIK_MEMORY_STATS
  a->allocations++;
  a->alive++;
#endif

  if (gc_arena_is_gc_needed(a)) {
    baik->need_gc = 1;
  }

  memset(r, 0, a->cell_size);
  return (void *) r;
}


void gc_sweep(struct baik *baik, struct gc_arena *a, size_t start) {
  struct gc_block *b;
  struct gc_cell *cur;
  struct gc_block **prevp = &a->blocks;
#if BAIK_MEMORY_STATS
  a->alive = 0;
#endif

  {
    struct gc_cell *next;
    for (cur = a->free; cur != NULL; cur = next) {
      next = cur->head.link;
      MARK_FREE(cur);
    }
  }

  a->free = NULL;

  for (b = a->blocks; b != NULL;) {
    size_t freed_in_block = 0;
   
    struct gc_cell *prev_free = a->free;

    for (cur = GC_CELL_OP(a, b->base, +, start);
         cur < GC_CELL_OP(a, b->base, +, b->size);
         cur = GC_CELL_OP(a, cur, +, 1)) {
      if (MARKED(cur)) {
        UNMARK(cur);
#if BAIK_MEMORY_STATS
        a->alive++;
#endif
      } else {
        if (MARKED_FREE(cur)) {
         
          UNMARK_FREE(cur);
        } else {
         
          if (a->destructor != NULL) {
            a->destructor(baik, cur);
          }
          memset(cur, 0, a->cell_size);
        }
        cur->head.link = a->free;
        a->free = cur;
        freed_in_block++;
#if BAIK_MEMORY_STATS
        a->garbage++;
#endif
      }
    }

    if (b->next != NULL && freed_in_block == b->size) {
      *prevp = b->next;
      gc_free_block(b);
      b = *prevp;
      a->free = prev_free;
    } else {
      prevp = &b->next;
      b = b->next;
    }
  }
}


static void gc_mark_ffi_sig(struct baik *baik, baik_val_t *v) {
  struct baik_ffi_sig *psig;

  assert(baik_is_ffi_sig(*v));

  psig = baik_get_ffi_sig_struct(*v);

  if (!gc_check_val(baik, *v)) {
    abort();
  }

  if (MARKED(psig)) return;

  MARK(psig);
}


static void gc_mark_object(struct baik *baik, baik_val_t *v) {
  struct baik_object *obj_base;
  struct baik_property *prop;
  struct baik_property *next;

  assert(baik_is_object(*v));

  obj_base = get_object_struct(*v);

  if (!gc_check_val(baik, *v)) {
    abort();
  }

  if (MARKED(obj_base)) return;

  for ((prop = obj_base->properties), MARK(obj_base); prop != NULL;
       prop = next) {
    if (!gc_check_ptr(&baik->property_arena, prop)) {
      abort();
    }

    gc_mark(baik, &prop->name);
    gc_mark(baik, &prop->value);

    next = prop->next;
    MARK(prop);
  }

}


static void gc_mark_string(struct baik *baik, baik_val_t *v) {
  baik_val_t h, tmp = 0;
  char *s;
  assert((*v & BAIK_TAG_MASK) == BAIK_TAG_STRING_O);

  s = baik->owned_strings.buf + gc_string_baik_val_to_offset(*v);
  assert(s < baik->owned_strings.buf + baik->owned_strings.len);
  if (s[-1] == '\0') {
    memcpy(&tmp, s, sizeof(tmp) - 2);
    tmp |= BAIK_TAG_STRING_C;
  } else {
    memcpy(&tmp, s, sizeof(tmp) - 2);
    tmp |= BAIK_TAG_FOREIGN;
  }

  h = (baik_val_t)(uintptr_t) v;
  s[-1] = 1;
  memcpy(s, &h, sizeof(h) - 2);
  memcpy(v, &tmp, sizeof(tmp));
}

BAIK_PRIVATE void gc_mark(struct baik *baik, baik_val_t *v) {
  if (baik_is_object(*v)) {
    gc_mark_object(baik, v);
  }
  if (baik_is_ffi_sig(*v)) {
    gc_mark_ffi_sig(baik, v);
  }
  if ((*v & BAIK_TAG_MASK) == BAIK_TAG_STRING_O) {
    gc_mark_string(baik, v);
  }
}

BAIK_PRIVATE uint64_t gc_string_baik_val_to_offset(baik_val_t v) {
  return (((uint64_t)(uintptr_t) get_ptr(v)) & ~BAIK_TAG_MASK);
}

BAIK_PRIVATE baik_val_t gc_string_val_from_offset(uint64_t s) {
  return s | BAIK_TAG_STRING_O;
}

void gc_compact_strings(struct baik *baik) {
  char *p = baik->owned_strings.buf + 1;
  uint64_t h, next, head = 1;
  int len, llen;

  while (p < baik->owned_strings.buf + baik->owned_strings.len) {
    if (p[-1] == '\1') {
     
      h = 0;
      memcpy(&h, p, sizeof(h) - 2);

      for (; (h & BAIK_TAG_MASK) != BAIK_TAG_STRING_C; h = next) {
        h &= ~BAIK_TAG_MASK;
        memcpy(&next, (char *) (uintptr_t) h, sizeof(h));

        *(baik_val_t *) (uintptr_t) h = gc_string_val_from_offset(head);
      }
      h &= ~BAIK_TAG_MASK;

      len = BAIK_EM_varint_decode_unsafe((unsigned char *) &h, &llen);
      len += llen + 1;

      memcpy(p, &h, sizeof(h) - 2);

      memmove(baik->owned_strings.buf + head, p, len);
      baik->owned_strings.buf[head - 1] = 0x0;
      p += len;
      head += len;
    } else {
      len = BAIK_EM_varint_decode_unsafe((unsigned char *) p, &llen);
      len += llen + 1;

      p += len;
    }
  }

  baik->owned_strings.len = head;
}

BAIK_PRIVATE int maybe_gc(struct baik *baik) {
  if (!baik->inhibit_gc) {
    baik_gc(baik, 0);
    return 1;
  }
  return 0;
}


static void gc_mark_val_array(struct baik *baik, baik_val_t *vals, size_t len) {
  baik_val_t *vp;
  for (vp = vals; vp < vals + len; vp++) {
    gc_mark(baik, vp);
  }
}


static void gc_mark_mbuf_pt(struct baik *baik, const struct mbuf *mbuf) {
  baik_val_t **vp;
  for (vp = (baik_val_t **) mbuf->buf; (char *) vp < mbuf->buf + mbuf->len;
       vp++) {
    gc_mark(baik, *vp);
  }
}


static void gc_mark_mbuf_val(struct baik *baik, const struct mbuf *mbuf) {
  gc_mark_val_array(baik, (baik_val_t *) mbuf->buf,
                    mbuf->len / sizeof(baik_val_t));
}

static void gc_mark_ffi_cbargs_list(struct baik *baik, ffi_cb_args_t *cbargs) {
  for (; cbargs != NULL; cbargs = cbargs->next) {
    gc_mark(baik, &cbargs->func);
    gc_mark(baik, &cbargs->userdata);
  }
}


void baik_gc(struct baik *baik, int full) {
  gc_mark_val_array(baik, (baik_val_t *) &baik->vals,
                    sizeof(baik->vals) / sizeof(baik_val_t));

  gc_mark_mbuf_pt(baik, &baik->owned_values);
  gc_mark_mbuf_val(baik, &baik->scopes);
  gc_mark_mbuf_val(baik, &baik->stack);
  gc_mark_mbuf_val(baik, &baik->call_stack);
  gc_mark_ffi_cbargs_list(baik, baik->ffi_cb_args);
  gc_compact_strings(baik);
  gc_sweep(baik, &baik->object_arena, 0);
  gc_sweep(baik, &baik->property_arena, 0);
  gc_sweep(baik, &baik->ffi_sig_arena, 0);

  if (full) {
    size_t trimmed_size = baik->owned_strings.len + _BAIK_STRING_BUF_RESERVE;
    if (trimmed_size < baik->owned_strings.size) {
      mbuf_resize(&baik->owned_strings, trimmed_size);
    }
  }
}

BAIK_PRIVATE int gc_check_val(struct baik *baik, baik_val_t v) {
  if (baik_is_object(v)) {
    return gc_check_ptr(&baik->object_arena, get_object_struct(v));
  }
  if (baik_is_ffi_sig(v)) {
    return gc_check_ptr(&baik->ffi_sig_arena, baik_get_ffi_sig_struct(v));
  }
  return 1;
}

BAIK_PRIVATE int gc_check_ptr(const struct gc_arena *a, const void *ptr) {
  const struct gc_cell *p = (const struct gc_cell *) ptr;
  struct gc_block *b;
  for (b = a->blocks; b != NULL; b = b->next) {
    if (p >= b->base && p < GC_CELL_OP(a, b->base, +, b->size)) {
      return 1;
    }
  }
  return 0;
}

#define BUF_LEFT(size, used) (((size_t)(used) < (size)) ? ((size) - (used)) : 0)

static int should_skip_for_json(enum baik_type type) {
  int ret;
  switch (type) {
    case BAIK_TYPE_NULL:
    case BAIK_TYPE_BOOLEAN:
    case BAIK_TYPE_NUMBER:
    case BAIK_TYPE_STRING:
    case BAIK_TYPE_OBJECT_GENERIC:
    case BAIK_TYPE_OBJECT_ARRAY:
      ret = 0;
      break;
    default:
      ret = 1;
      break;
  }
  return ret;
}

static const char *hex_digits = "0123456789abcdef";
static char *append_hex(char *buf, char *limit, uint8_t c) {
  if (buf < limit) *buf++ = 'u';
  if (buf < limit) *buf++ = '0';
  if (buf < limit) *buf++ = '0';
  if (buf < limit) *buf++ = hex_digits[(int) ((c >> 4) % 0xf)];
  if (buf < limit) *buf++ = hex_digits[(int) (c & 0xf)];
  return buf;
}

static int snquote(char *buf, size_t size, const char *s, size_t len) {
  char *limit = buf + size;
  const char *end;
 
  const char *specials = "btnvfr";
  size_t i = 0;

  i++;
  if (buf < limit) *buf++ = '"';

  for (end = s + len; s < end; s++) {
    if (*s == '"' || *s == '\\') {
      i++;
      if (buf < limit) *buf++ = '\\';
    } else if (*s >= '\b' && *s <= '\r') {
      i += 2;
      if (buf < limit) *buf++ = '\\';
      if (buf < limit) *buf++ = specials[*s - '\b'];
      continue;
    } else if ((unsigned char) *s < '\b' || (*s > '\r' && *s < ' ')) {
      i += 6;
      if (buf < limit) *buf++ = '\\';
      buf = append_hex(buf, limit, (uint8_t) *s);
      continue;
    }
    i++;
    if (buf < limit) *buf++ = *s;
  }

  i++;
  if (buf < limit) *buf++ = '"';

  if (buf < limit) {
    *buf = '\0';
  } else if (size != 0) {
   
    *(buf - 1) = '\0';
  }
  return i;
}

BAIK_PRIVATE baik_err_t to_json_or_debug(struct baik *baik, baik_val_t v, char *buf,
                                       size_t size, size_t *res_len,
                                       uint8_t is_debug) {
  baik_val_t el;
  char *vp;
  baik_err_t rcode = BAIK_OK;
  size_t len = 0;

  if (size > 0) *buf = '\0';

  if (!is_debug && should_skip_for_json(baik_get_type(v))) {
    goto clean;
  }

  for (vp = baik->json_visited_stack.buf;
       vp < baik->json_visited_stack.buf + baik->json_visited_stack.len;
       vp += sizeof(baik_val_t)) {
    if (*(baik_val_t *) vp == v) {
      strncpy(buf, "[Circular]", size);
      len = 10;
      goto clean;
    }
  }

  switch (baik_get_type(v)) {
    case BAIK_TYPE_NULL:
    case BAIK_TYPE_BOOLEAN:
    case BAIK_TYPE_NUMBER:
    case BAIK_TYPE_UNDEFINED:
    case BAIK_TYPE_FOREIGN:
      {
       
        char *p = NULL;
        int need_free = 0;
        rcode = baik_to_string(baik, &v, &p, &len, &need_free);
        c_snprintf(buf, size, "%.*s", (int) len, p);
        if (need_free) {
          free(p);
        }
      }
      goto clean;

    case BAIK_TYPE_STRING: {
      size_t n;
      const char *str = baik_get_string(baik, &v, &n);
      len = snquote(buf, size, str, n);
      goto clean;
    }

    case BAIK_TYPE_OBJECT_FUNCTION:
    case BAIK_TYPE_OBJECT_GENERIC: {
      char *b = buf;
      struct baik_property *prop = NULL;
      struct baik_object *o = NULL;

      mbuf_append(&baik->json_visited_stack, (char *) &v, sizeof(v));
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "{");
      o = get_object_struct(v);
      for (prop = o->properties; prop != NULL; prop = prop->next) {
        size_t n;
        const char *s;
        if (!is_debug && should_skip_for_json(baik_get_type(prop->value))) {
          continue;
        }
        if (b - buf != 1) {
          b += c_snprintf(b, BUF_LEFT(size, b - buf), ",");
        }
        s = baik_get_string(baik, &prop->name, &n);
        b += c_snprintf(b, BUF_LEFT(size, b - buf), "\"%.*s\":", (int) n, s);
        {
          size_t tmp = 0;
          rcode = to_json_or_debug(baik, prop->value, b, BUF_LEFT(size, b - buf),
                                   &tmp, is_debug);
          if (rcode != BAIK_OK) {
            goto clean_iter;
          }
          b += tmp;
        }
      }

      b += c_snprintf(b, BUF_LEFT(size, b - buf), "}");
      baik->json_visited_stack.len -= sizeof(v);

    clean_iter:
      len = b - buf;
      goto clean;
    }
    case BAIK_TYPE_OBJECT_ARRAY: {
      int has;
      char *b = buf;
      size_t i, alen = baik_array_length(baik, v);
      mbuf_append(&baik->json_visited_stack, (char *) &v, sizeof(v));
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "[");
      for (i = 0; i < alen; i++) {
        el = baik_array_get2(baik, v, i, &has);
        if (has) {
          size_t tmp = 0;
          if (!is_debug && should_skip_for_json(baik_get_type(el))) {
            b += c_snprintf(b, BUF_LEFT(size, b - buf), "kosong");
          } else {
            rcode = to_json_or_debug(baik, el, b, BUF_LEFT(size, b - buf), &tmp,
                                     is_debug);
            if (rcode != BAIK_OK) {
              goto clean;
            }
          }
          b += tmp;
        } else {
          b += c_snprintf(b, BUF_LEFT(size, b - buf), "kosong");
        }
        if (i != alen - 1) {
          b += c_snprintf(b, BUF_LEFT(size, b - buf), ",");
        }
      }
      b += c_snprintf(b, BUF_LEFT(size, b - buf), "]");
      baik->json_visited_stack.len -= sizeof(v);
      len = b - buf;
      goto clean;
    }

    case BAIK_TYPES_CNT:
      abort();
  }

  abort();

  len = 0;
  goto clean;

clean:
  if (rcode != BAIK_OK) {
    len = 0;
  }
  if (res_len != NULL) {
    *res_len = len;
  }
  return rcode;
}

BAIK_PRIVATE baik_err_t baik_json_stringify(struct baik *baik, baik_val_t v,
                                         char *buf, size_t size, char **res) {
  baik_err_t rcode = BAIK_OK;
  char *p = buf;
  size_t len;

  to_json_or_debug(baik, v, buf, size, &len, 0);

  if (len >= size) {
   
    p = (char *) malloc(len + 1);
    rcode = baik_json_stringify(baik, v, p, len + 1, res);
    assert(*res == p);
    goto clean;
  } else {
    *res = p;
    goto clean;
  }

clean:
 
  if (rcode != BAIK_OK && p != buf) {
    free(p);
  }
  return rcode;
}

struct json_parse_frame {
  baik_val_t val;
  struct json_parse_frame *up;
};

struct json_parse_ctx {
  struct baik *baik;
  baik_val_t result;
  struct json_parse_frame *frame;
  enum baik_err rcode;
};

static struct json_parse_frame *alloc_json_frame(struct json_parse_ctx *ctx,
                                                 baik_val_t v) {
  struct json_parse_frame *frame =
      (struct json_parse_frame *) calloc(sizeof(struct json_parse_frame), 1);
  frame->val = v;
  baik_own(ctx->baik, &frame->val);
  return frame;
}

static struct json_parse_frame *free_json_frame(
    struct json_parse_ctx *ctx, struct json_parse_frame *frame) {
  struct json_parse_frame *up = frame->up;
  baik_disown(ctx->baik, &frame->val);
  free(frame);
  return up;
}

static void frozen_cb(void *data, const char *name, size_t name_len,
                      const char *path, const struct json_token *token) {
  struct json_parse_ctx *ctx = (struct json_parse_ctx *) data;
  baik_val_t v = BAIK_UNDEFINED;

  (void) path;

  baik_own(ctx->baik, &v);

  switch (token->type) {
    case JSON_TYPE_STRING: {
      char *dst;
      if (token->len > 0 && (dst = malloc(token->len)) != NULL) {
        int len = json_unescape(token->ptr, token->len, dst, token->len);
        if (len < 0) {
          baik_prepend_errorf(ctx->baik, BAIK_TYPE_ERROR, "GALAT : kesalahan JSON string");
          break;
        }
        v = baik_mk_string(ctx->baik, dst, len, 1);
        free(dst);
      } else {
       
        v = baik_mk_string(ctx->baik, "", 0, 1);
      }
      break;
    }
    case JSON_TYPE_NUMBER:
      v = baik_mk_number(ctx->baik, strtod(token->ptr, NULL));
      break;
    case JSON_TYPE_TRUE:
      v = baik_mk_boolean(ctx->baik, 1);
      break;
    case JSON_TYPE_FALSE:
      v = baik_mk_boolean(ctx->baik, 0);
      break;
    case JSON_TYPE_NULL:
      v = BAIK_NULL;
      break;
    case JSON_TYPE_OBJECT_START:
      v = baik_mk_object(ctx->baik);
      break;
    case JSON_TYPE_ARRAY_START:
      v = baik_mk_array(ctx->baik);
      break;

    case JSON_TYPE_OBJECT_END:
    case JSON_TYPE_ARRAY_END: {
     
      ctx->frame = free_json_frame(ctx, ctx->frame);
    } break;

    default:
      LOG(LL_ERROR, ("Wrong token type %d\n", token->type));
      break;
  }

  if (!baik_is_undefined(v)) {
    if (name != NULL && name_len != 0) {
     
      if (baik_is_object(ctx->frame->val)) {
        baik_set(ctx->baik, ctx->frame->val, name, name_len, v);
      } else if (baik_is_array(ctx->frame->val)) {
       
        int idx = (int) strtod(name, NULL);
        baik_array_set(ctx->baik, ctx->frame->val, idx, v);
      } else {
        LOG(LL_ERROR, ("Current value is neither object nor array\n"));
      }

    } else {
      assert(ctx->frame == NULL);
      ctx->result = v;
    }

    if (token->type == JSON_TYPE_OBJECT_START ||
        token->type == JSON_TYPE_ARRAY_START) {
     
      struct json_parse_frame *new_frame = alloc_json_frame(ctx, v);
      new_frame->up = ctx->frame;
      ctx->frame = new_frame;
    }
  }

  baik_disown(ctx->baik, &v);
}

BAIK_PRIVATE baik_err_t
baik_json_parse(struct baik *baik, const char *str, size_t len, baik_val_t *res) {
  struct json_parse_ctx *ctx =
      (struct json_parse_ctx *) calloc(sizeof(struct json_parse_ctx), 1);
  int json_res;
  enum baik_err rcode = BAIK_OK;

  ctx->baik = baik;
  ctx->result = BAIK_UNDEFINED;
  ctx->frame = NULL;
  ctx->rcode = BAIK_OK;

  baik_own(baik, &ctx->result);

  {
   
    char *stmp = malloc(len);
    memcpy(stmp, str, len);
    json_res = json_walk(stmp, len, frozen_cb, ctx);
    free(stmp);
    stmp = NULL;
    str = NULL;
  }

  if (ctx->rcode != BAIK_OK) {
    rcode = ctx->rcode;
    baik_prepend_errorf(baik, rcode, "GALAT : kesalahan JSON string");
  } else if (json_res < 0) {
   
    rcode = BAIK_TYPE_ERROR;
    baik_prepend_errorf(baik, rcode, "GALAT : kesalahan JSON string");
  } else {
    *res = ctx->result;
    assert(ctx->frame == NULL);
  }

  if (rcode != BAIK_OK) {
    while (ctx->frame != NULL) {
      ctx->frame = free_json_frame(ctx, ctx->frame);
    }
  }

  baik_disown(baik, &ctx->result);
  free(ctx);

  return rcode;
}

BAIK_PRIVATE void baik_op_json_stringify(struct baik *baik) {
  baik_val_t ret = BAIK_UNDEFINED;
  baik_val_t val = baik_arg(baik, 0);

  if (baik_nargs(baik) < 1) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : kesalahan nilai stringify");
  } else {
    char *p = NULL;
    if (baik_json_stringify(baik, val, NULL, 0, &p) == BAIK_OK) {
      ret = baik_mk_string(baik, p, ~0, 1);
      free(p);
    }
  }

  baik_return(baik, ret);
}

BAIK_PRIVATE void baik_op_json_parse(struct baik *baik) {
  baik_val_t ret = BAIK_UNDEFINED;
  baik_val_t arg0 = baik_arg(baik, 0);

  if (baik_is_string(arg0)) {
    size_t len;
    const char *str = baik_get_string(baik, &arg0, &len);
    baik_json_parse(baik, str, len, &ret);
  } else {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : string argumen dibutuhkan");
  }

  baik_return(baik, ret);
}

#ifdef BAIK_MAIN

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "strings.h"
#include "baik.h"

char **baik_type_completion(const char *, int, int);
char *baik_type_generator(const char *, int);
char *baik_types[] = {
    "tulis",
    "jika",
    "lainnya",
    "untuk",
    "ulang",
    "benar",
    "salah",
    "isi",
    "panjang",
    NULL
};

char **
baik_type_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, baik_type_generator);
}

char *
baik_type_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = baik_types[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

int repl()
{
    rl_bind_key('\t', rl_complete);
    rl_attempted_completion_function = baik_type_completion;
    struct baik *baik = baik_create();
    printf("Baik X, " __DATE__ "\n");

    while (1) {
        char* baik_input = readline("baik >> ");

        if (!baik_input)
            break;

        if( 0 == strcmp(&baik_input[(strlen(baik_input)-1)], "{"))
        {
            while (1) {
                char* baik_input_next = readline("... ");
                strcat(baik_input,baik_input_next);
                if( 0 == strcmp(&baik_input[(strlen(baik_input)-1)], "}")){
                    break;
                }
                free(baik_input_next);
            }
        }

        add_history(baik_input);
        baik_exec(baik, baik_input, NULL);
        free(baik_input);
    }
    return 0;
}
  
int main(int argc,char* argv[]) 
{ 
    struct baik *baik = baik_create();
    baik_err_t err = BAIK_OK;
    baik_val_t res = 0;
    int i;

    for (i = 1; i < argc && argv[i][0] == '-' && err == BAIK_OK; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            err = baik_exec(baik, argv[++i], &res);
        } else if  (strcmp(argv[i], "-c") == 0){
            baik_set_generate_jsc(baik, 1);
        } else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
            //BAIK_EM_log_set_level(atoi(argv[++i]));
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            err = baik_exec_file(baik, argv[++i], &res);
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Baik X, " __DATE__ "\n");
            printf("Pakai:\n");
            printf("%s [PARAMETER] [baik_file ...]\n", argv[0]);
            printf("PARAMETER:\n");
            printf("  -e <baik script>  - Eksekusi ekspresi Baik\n");
            printf("  -c                - Aktifkan precompiling (berkas .inac)\n");
            printf("  -f <baik file>    - Eksekusi kode dari file (.ina)\n");
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Unknown flag: [%s]\n", argv[i]);
            return EXIT_FAILURE;
        }
    }
    for (; i < argc && err == BAIK_OK; i++) {
        err = baik_exec_file(baik, argv[i], &res);
    }

    if (err == BAIK_OK) {
        if(res == 0)
            repl();
    } else {
        baik_print_error(baik, stdout, NULL, 1);
    }

    baik_destroy(baik);
    return EXIT_SUCCESS;
} 

#endif

BAIK_PRIVATE baik_val_t baik_object_to_value(struct baik_object *o) {
  if (o == NULL) {
    return BAIK_NULL;
  } else {
    return baik_legit_pointer_to_value(o) | BAIK_TAG_OBJECT;
  }
}

BAIK_PRIVATE struct baik_object *get_object_struct(baik_val_t v) {
  struct baik_object *ret = NULL;
  if (baik_is_null(v)) {
    ret = NULL;
  } else {
    assert(baik_is_object(v));
    ret = (struct baik_object *) get_ptr(v);
  }
  return ret;
}

baik_val_t baik_mk_object(struct baik *baik) {
  struct baik_object *o = new_object(baik);
  if (o == NULL) {
    return BAIK_NULL;
  }
  (void) baik;
  o->properties = NULL;
  return baik_object_to_value(o);
}

int baik_is_object(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_OBJECT ||
         (v & BAIK_TAG_MASK) == BAIK_TAG_ARRAY;
}

BAIK_PRIVATE struct baik_property *baik_get_own_property(struct baik *baik,
                                                      baik_val_t obj,
                                                      const char *name,
                                                      size_t len) {
  struct baik_property *p;
  struct baik_object *o;

  if (!baik_is_object(obj)) {
    return NULL;
  }

  o = get_object_struct(obj);

  if (len <= 5) {
    baik_val_t ss = baik_mk_string(baik, name, len, 1);
    for (p = o->properties; p != NULL; p = p->next) {
      if (p->name == ss) return p;
    }
  } else {
    for (p = o->properties; p != NULL; p = p->next) {
      if (baik_strcmp(baik, &p->name, name, len) == 0) return p;
    }
    return p;
  }

  return NULL;
}

BAIK_PRIVATE struct baik_property *baik_get_own_property_v(struct baik *baik,
                                                        baik_val_t obj,
                                                        baik_val_t key) {
  size_t n;
  char *s = NULL;
  int need_free = 0;
  struct baik_property *p = NULL;
  baik_err_t err = baik_to_string(baik, &key, &s, &n, &need_free);
  if (err == BAIK_OK) {
    p = baik_get_own_property(baik, obj, s, n);
  }
  if (need_free) free(s);
  return p;
}

BAIK_PRIVATE struct baik_property *baik_mk_property(struct baik *baik,
                                                 baik_val_t name,
                                                 baik_val_t value) {
  struct baik_property *p = new_property(baik);
  p->next = NULL;
  p->name = name;
  p->value = value;
  return p;
}

baik_val_t baik_get(struct baik *baik, baik_val_t obj, const char *name,
                  size_t name_len) {
  struct baik_property *p;

  if (name_len == (size_t) ~0) {
    name_len = strlen(name);
  }

  p = baik_get_own_property(baik, obj, name, name_len);
  if (p == NULL) {
    return BAIK_UNDEFINED;
  } else {
    return p->value;
  }
}

baik_val_t baik_get_v(struct baik *baik, baik_val_t obj, baik_val_t name) {
  size_t n;
  char *s = NULL;
  int need_free = 0;
  baik_val_t ret = BAIK_UNDEFINED;

  baik_err_t err = baik_to_string(baik, &name, &s, &n, &need_free);

  if (err == BAIK_OK) {
   
    ret = baik_get(baik, obj, s, n);
  }

  if (need_free) {
    free(s);
    s = NULL;
  }
  return ret;
}

baik_val_t baik_get_v_proto(struct baik *baik, baik_val_t obj, baik_val_t key) {
  struct baik_property *p;
  baik_val_t pn = baik_mk_string(baik, BAIK_PROTO_PROP_NAME, ~0, 1);
  if ((p = baik_get_own_property_v(baik, obj, key)) != NULL) return p->value;
  if ((p = baik_get_own_property_v(baik, obj, pn)) == NULL) return BAIK_UNDEFINED;
  return baik_get_v_proto(baik, p->value, key);
}

baik_err_t baik_set(struct baik *baik, baik_val_t obj, const char *name,
                  size_t name_len, baik_val_t val) {
  return baik_set_internal(baik, obj, BAIK_UNDEFINED, (char *) name, name_len,
                          val);
}

baik_err_t baik_set_v(struct baik *baik, baik_val_t obj, baik_val_t name,
                    baik_val_t val) {
  return baik_set_internal(baik, obj, name, NULL, 0, val);
}

BAIK_PRIVATE baik_err_t baik_set_internal(struct baik *baik, baik_val_t obj,
                                       baik_val_t name_v, char *name,
                                       size_t name_len, baik_val_t val) {
  baik_err_t rcode = BAIK_OK;
  struct baik_property *p;
  int need_free = 0;

  if (name == NULL) {
    rcode = baik_to_string(baik, &name_v, &name, &name_len, &need_free);
    if (rcode != BAIK_OK) {
      goto clean;
    }
  } else {
    name_v = BAIK_UNDEFINED;
  }

  p = baik_get_own_property(baik, obj, name, name_len);

  if (p == NULL) {
    struct baik_object *o;
    if (!baik_is_object(obj)) {
      return BAIK_REFERENCE_ERROR;
    }

    if (!baik_is_string(name_v)) {
      name_v = baik_mk_string(baik, name, name_len, 1);
    }

    p = baik_mk_property(baik, name_v, val);

    o = get_object_struct(obj);
    p->next = o->properties;
    o->properties = p;
  }

  p->value = val;

clean:
  if (need_free) {
    free(name);
    name = NULL;
  }
  return rcode;
}

BAIK_PRIVATE void baik_destroy_property(struct baik_property **p) {
  *p = NULL;
}


int baik_del(struct baik *baik, baik_val_t obj, const char *name, size_t len) {
  struct baik_property *prop, *prev;

  if (!baik_is_object(obj)) {
    return -1;
  }
  if (len == (size_t) ~0) {
    len = strlen(name);
  }
  for (prev = NULL, prop = get_object_struct(obj)->properties; prop != NULL;
       prev = prop, prop = prop->next) {
    size_t n;
    const char *s = baik_get_string(baik, &prop->name, &n);
    if (n == len && strncmp(s, name, len) == 0) {
      if (prev) {
        prev->next = prop->next;
      } else {
        get_object_struct(obj)->properties = prop->next;
      }
      baik_destroy_property(&prop);
      return 0;
    }
  }
  return -1;
}

baik_val_t baik_next(struct baik *baik, baik_val_t obj, baik_val_t *iterator) {
  struct baik_property *p = NULL;
  baik_val_t key = BAIK_UNDEFINED;

  if (*iterator == BAIK_UNDEFINED) {
    struct baik_object *o = get_object_struct(obj);
    p = o->properties;
  } else {
    p = ((struct baik_property *) get_ptr(*iterator))->next;
  }

  if (p == NULL) {
    *iterator = BAIK_UNDEFINED;
  } else {
    key = p->name;
    *iterator = baik_mk_foreign(baik, p);
  }

  return key;
}

BAIK_PRIVATE void baik_op_create_object(struct baik *baik) {
  baik_val_t ret = BAIK_UNDEFINED;
  baik_val_t proto_v = baik_arg(baik, 0);

  if (!baik_check_arg(baik, 0, "proto", BAIK_TYPE_OBJECT_GENERIC, &proto_v)) {
    goto clean;
  }

  ret = baik_mk_object(baik);
  baik_set(baik, ret, BAIK_PROTO_PROP_NAME, ~0, proto_v);

clean:
  baik_return(baik, ret);
}

baik_val_t baik_struct_to_obj(struct baik *baik, const void *base,
                            const struct baik_c_struct_member *defs) {
  baik_val_t obj;
  const struct baik_c_struct_member *def = defs;
  if (base == NULL || def == NULL) return BAIK_UNDEFINED;
  obj = baik_mk_object(baik);
 
  baik_own(baik, &obj);
 
  while (def->name != NULL) def++;
  for (def--; def >= defs; def--) {
    baik_val_t v = BAIK_UNDEFINED;
    const char *ptr = (const char *) base + def->offset;
    switch (def->type) {
      case BAIK_STRUCT_FIELD_TYPE_STRUCT: {
        const void *sub_base = (const void *) ptr;
        const struct baik_c_struct_member *sub_def =
            (const struct baik_c_struct_member *) def->arg;
        v = baik_struct_to_obj(baik, sub_base, sub_def);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_STRUCT_PTR: {
        const void **sub_base = (const void **) ptr;
        const struct baik_c_struct_member *sub_def =
            (const struct baik_c_struct_member *) def->arg;
        if (*sub_base != NULL) {
          v = baik_struct_to_obj(baik, *sub_base, sub_def);
        } else {
          v = BAIK_NULL;
        }
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_INT: {
        double value = (double) (*(int *) ptr);
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_BOOL: {
        v = baik_mk_boolean(baik, *(bool *) ptr);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_DOUBLE: {
        v = baik_mk_number(baik, *(double *) ptr);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_FLOAT: {
        float value = *(float *) ptr;
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_CHAR_PTR: {
        const char *value = *(const char **) ptr;
        v = baik_mk_string(baik, value, ~0, 1);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_VOID_PTR: {
        v = baik_mk_foreign(baik, *(void **) ptr);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_GENERIC_STR_PTR: {
        const struct baik_generic_str *s = *(const struct baik_generic_str **) ptr;
        if (s != NULL) {
          v = baik_mk_string(baik, s->p, s->len, 1);
        } else {
          v = BAIK_NULL;
        }
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_GENERIC_STR: {
        const struct baik_generic_str *s = (const struct baik_generic_str *) ptr;
        v = baik_mk_string(baik, s->p, s->len, 1);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_DATA: {
        const char *dptr = (const char *) ptr;
        const intptr_t dlen = (intptr_t) def->arg;
        v = baik_mk_string(baik, dptr, dlen, 1);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_INT8: {
        double value = (double) (*(int8_t *) ptr);
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_INT16: {
        double value = (double) (*(int16_t *) ptr);
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_UINT8: {
        double value = (double) (*(uint8_t *) ptr);
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_UINT16: {
        double value = (double) (*(uint16_t *) ptr);
        v = baik_mk_number(baik, value);
        break;
      }
      case BAIK_STRUCT_FIELD_TYPE_CUSTOM: {
        baik_val_t (*fptr)(struct baik *, const void *) =
            (baik_val_t (*) (struct baik *, const void *)) def->arg;
        v = fptr(baik, ptr);
      }
      default: { break; }
    }
    baik_set(baik, obj, def->name, ~0, v);
  }
  baik_disown(baik, &obj);
  return obj;
}

#ifndef MAX_TOKS_IN_EXPR
#define MAX_TOKS_IN_EXPR 40
#endif

#define FAIL_ERR(p, code)                                                      \
  do {                                                                         \
    baik_set_errorf(p->baik, code, "parse error at line %d: [%.*s]", p->line_no, \
                   10, p->tok.ptr);                                            \
    return code;                                                               \
  } while (0)

#define pnext1(p)                                    \
  do {                                               \
    LOG(LL_VERBOSE_DEBUG, ("  PNEXT %d", __LINE__)); \
    pnext(p);                                        \
  } while (0)

#define SYNTAX_ERROR(p) FAIL_ERR(p, BAIK_SYNTAX_ERROR)
#undef EXPECT
#define EXPECT(p, t)       \
  if ((p)->tok.tok != (t)) \
    SYNTAX_ERROR(p);       \
  else                     \
    pnext1(p);

static baik_err_t parse_statement(struct pstate *p);
static baik_err_t parse_expr(struct pstate *p);

static int ptest(struct pstate *p) {
  struct pstate saved = *p;
  int tok = pnext(p);
  *p = saved;
  return tok;
}

static int s_unary_ops[] = {TOK_NOT, TOK_TILDA, TOK_PLUS_PLUS, TOK_MINUS_MINUS,
                            TOK_KEYWORD_TIPE, TOK_MINUS, TOK_PLUS, TOK_EOF};
static int s_comparison_ops[] = {TOK_LT, TOK_LE, TOK_GT, TOK_GE, TOK_EOF};
static int s_postfix_ops[] = {TOK_PLUS_PLUS, TOK_MINUS_MINUS, TOK_EOF};
static int s_equality_ops[] = {TOK_EQ, TOK_NE, TOK_EQ_EQ, TOK_NE_NE, TOK_EOF};
static int s_assign_ops[] = {
    TOK_ASSIGN,         TOK_PLUS_ASSIGN, TOK_MINUS_ASSIGN,  TOK_MUL_ASSIGN,
    TOK_DIV_ASSIGN,     TOK_REM_ASSIGN,  TOK_LSHIFT_ASSIGN, TOK_RSHIFT_ASSIGN,
    TOK_URSHIFT_ASSIGN, TOK_AND_ASSIGN,  TOK_XOR_ASSIGN,    TOK_OR_ASSIGN,
    TOK_EOF};

static int findtok(int *toks, int tok) {
  int i = 0;
  while (tok != toks[i] && toks[i] != TOK_EOF) i++;
  return toks[i];
}

static void emit_op(struct pstate *pstate, int tok) {
  assert(tok >= 0 && tok <= 255);
  emit_byte(pstate, OP_EXPR);
  emit_byte(pstate, (uint8_t) tok);
}

#define BINOP_STACK_FRAME_SIZE 16
#define STACK_LIMIT 8192

#define PARSE_LTR_BINOP(p, f1, f2, ops, prev_op)                               \
  do {                                                                         \
    baik_err_t res = BAIK_OK;                                                    \
    p->depth++;                                                                \
    if (p->depth > (STACK_LIMIT / BINOP_STACK_FRAME_SIZE)) {                   \
      baik_set_errorf(p->baik, BAIK_SYNTAX_ERROR, "parser stack overflow");       \
      res = BAIK_SYNTAX_ERROR;                                                  \
      goto binop_clean;                                                        \
    }                                                                          \
    if ((res = f1(p, TOK_EOF)) != BAIK_OK) goto binop_clean;                    \
    if (prev_op != TOK_EOF) emit_op(p, prev_op);                               \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {                                 \
      int op = p->tok.tok;                                                     \
      size_t off_if = 0;                                                       \
                          \
      if (ops[0] == TOK_LOGICAL_AND || ops[0] == TOK_LOGICAL_OR) {             \
        emit_byte(p,                                                           \
                  (uint8_t)(ops[0] == TOK_LOGICAL_AND ? OP_JMP_NEUTRAL_FALSE   \
                                                      : OP_JMP_NEUTRAL_TRUE)); \
        off_if = p->cur_idx;                                                   \
        emit_init_offset(p);                                                   \
                     \
                 \
        emit_byte(p, (uint8_t) OP_DROP);                                       \
        op = TOK_EOF;                                                          \
      }                                                                        \
      pnext1(p);                                                               \
      if ((res = f2(p, op)) != BAIK_OK) goto binop_clean;                       \
                                                                               \
      if (off_if != 0) {                                                       \
        baik_bcode_insert_offset(p, p->baik, off_if,                             \
                                p->cur_idx - off_if - BAIK_INIT_OFFSET_SIZE);   \
      }                                                                        \
    }                                                                          \
  binop_clean:                                                                 \
    p->depth--;                                                                \
    return res;                                                                \
  } while (0)

#define PARSE_RTL_BINOP(p, f1, f2, ops, prev_op)        \
  do {                                                  \
    baik_err_t res = BAIK_OK;                             \
    (void) prev_op;                                     \
    if ((res = f1(p, TOK_EOF)) != BAIK_OK) return res;   \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {          \
      int op = p->tok.tok;                              \
      pnext1(p);                                        \
      if ((res = f2(p, TOK_EOF)) != BAIK_OK) return res; \
      emit_op(p, op);                                   \
    }                                                   \
    return res;                                         \
  } while (0)

#if BAIK_INIT_OFFSET_SIZE > 0
static void emit_init_offset(struct pstate *p) {
  size_t i;
  for (i = 0; i < BAIK_INIT_OFFSET_SIZE; i++) {
    emit_byte(p, 0);
  }
}
#else
static void emit_init_offset(struct pstate *p) {
  (void) p;
}
#endif

static baik_err_t parse_statement_list(struct pstate *p, int et) {
  baik_err_t res = BAIK_OK;
  int drop = 0;
  pnext1(p);
  while (res == BAIK_OK && p->tok.tok != TOK_EOF && p->tok.tok != et) {
    if (drop) emit_byte(p, OP_DROP);
    res = parse_statement(p);
    drop = 1;
    while (p->tok.tok == TOK_SEMICOLON) pnext1(p);
  }

  if (!drop) {
    emit_byte(p, OP_PUSH_UNDEF);
  }
  return res;
}

static baik_err_t parse_block(struct pstate *p, int mkscope) {
  baik_err_t res = BAIK_OK;
  p->depth++;
  if (p->depth > (STACK_LIMIT / BINOP_STACK_FRAME_SIZE)) {
    baik_set_errorf(p->baik, BAIK_SYNTAX_ERROR, "parser stack overflow");
    res = BAIK_SYNTAX_ERROR;
    return res;
  }
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  if (mkscope) emit_byte(p, OP_NEW_SCOPE);
  res = parse_statement_list(p, TOK_CLOSE_CURLY);
  EXPECT(p, TOK_CLOSE_CURLY);
  if (mkscope) emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static baik_err_t parse_function(struct pstate *p) {
  size_t prologue, off;
  int arg_no = 0;
  int name_provided = 0;
  baik_err_t res = BAIK_OK;

  EXPECT(p, TOK_KEYWORD_FUNGSI);

  if (p->tok.tok == TOK_IDENT) {
    struct tok tmp = p->tok;
    name_provided = 1;
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_FIND_SCOPE);
    pnext1(p);
  }

  emit_byte(p, OP_JMP);
  off = p->cur_idx;
  emit_init_offset(p);
  prologue = p->cur_idx;
  EXPECT(p, TOK_OPEN_PAREN);
  emit_byte(p, OP_NEW_SCOPE);
  
  while (p->tok.tok != TOK_CLOSE_PAREN) {
    if (p->tok.tok != TOK_IDENT) SYNTAX_ERROR(p);
    emit_byte(p, OP_SET_ARG);
    emit_int(p, arg_no);
    arg_no++;
    emit_str(p, p->tok.ptr, p->tok.len);
    if (ptest(p) == TOK_COMMA) pnext1(p);
    pnext1(p);
  }
  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block(p, 0)) != BAIK_OK) return res;
  emit_byte(p, OP_RETURN);
  prologue += baik_bcode_insert_offset(p, p->baik, off,
                                      p->cur_idx - off - BAIK_INIT_OFFSET_SIZE);
  emit_byte(p, OP_PUSH_FUNC);
  emit_int(p, p->cur_idx - 1 - prologue);
  if (name_provided) {
    emit_op(p, TOK_ASSIGN);
  }

  return res;
}

static baik_err_t parse_object_literal(struct pstate *p) {
  baik_err_t res = BAIK_OK;
  EXPECT(p, TOK_OPEN_CURLY);
  emit_byte(p, OP_PUSH_OBJ);
  while (p->tok.tok != TOK_CLOSE_CURLY) {
    if (p->tok.tok != TOK_IDENT && p->tok.tok != TOK_STR) SYNTAX_ERROR(p);
    emit_byte(p, OP_DUP);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_SWAP);
    pnext1(p);
    EXPECT(p, TOK_COLON);
    if ((res = parse_expr(p)) != BAIK_OK) return res;
    emit_op(p, TOK_ASSIGN);
    emit_byte(p, OP_DROP);
    if (p->tok.tok == TOK_COMMA) {
      pnext1(p);
    } else if (p->tok.tok != TOK_CLOSE_CURLY) {
      SYNTAX_ERROR(p);
    }
  }
  return res;
}

static baik_err_t parse_array_literal(struct pstate *p) {
  baik_err_t res = BAIK_OK;
  EXPECT(p, TOK_OPEN_BRACKET);
  emit_byte(p, OP_PUSH_ARRAY);
  while (p->tok.tok != TOK_CLOSE_BRACKET) {
    emit_byte(p, OP_DUP);
    if ((res = parse_expr(p)) != BAIK_OK) return res;
    emit_byte(p, OP_APPEND);
    if (p->tok.tok == TOK_COMMA) pnext1(p);
  }
  return res;
}

static enum baik_err parse_literal(struct pstate *p, const struct tok *t) {
  struct mbuf *bcode_gen = &p->baik->bcode_gen;
  enum baik_err res = BAIK_OK;
  int tok = t->tok;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s] %p", p->tok.len, p->tok.ptr, (void *) &t));
  switch (t->tok) {
    case TOK_KEYWORD_FALSE:
      emit_byte(p, OP_PUSH_FALSE);
      break;
    case TOK_KEYWORD_TRUE:
      emit_byte(p, OP_PUSH_TRUE);
      break;
    case TOK_KEYWORD_TAKTERDEFINISI:
      emit_byte(p, OP_PUSH_UNDEF);
      break;
    case TOK_KEYWORD_KOSONG:
      emit_byte(p, OP_PUSH_NULL);
      break;
    case TOK_IDENT: {
      int prev_tok = p->prev_tok;
      int next_tok = ptest(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, t->ptr, t->len);
      emit_byte(p, (uint8_t)(prev_tok == TOK_DOT ? OP_SWAP : OP_FIND_SCOPE));
      if (!findtok(s_assign_ops, next_tok) &&
          !findtok(s_postfix_ops, next_tok) &&
         
          !findtok(s_postfix_ops, prev_tok)) {
        emit_byte(p, OP_GET);
      }
      break;
    }
    case TOK_NUM: {
      double iv, d = strtod(t->ptr, NULL);
      unsigned long uv = strtoul(t->ptr + 2, NULL, 16);
      if (t->ptr[0] == '0' && t->ptr[1] == 'x') d = uv;
      if (modf(d, &iv) == 0) {
        emit_byte(p, OP_PUSH_INT);
        emit_int(p, (int64_t) d);
      } else {
        emit_byte(p, OP_PUSH_DBL);
        emit_str(p, t->ptr, t->len);
      }
      break;
    }
    case TOK_STR: {
      size_t oldlen;
      emit_byte(p, OP_PUSH_STR);
      oldlen = bcode_gen->len;
      embed_string(bcode_gen, p->cur_idx, t->ptr, t->len, EMBSTR_UNESCAPE);
      p->cur_idx += bcode_gen->len - oldlen;
    } break;
    case TOK_OPEN_BRACKET:
      res = parse_array_literal(p);
      break;
    case TOK_OPEN_CURLY:
      res = parse_object_literal(p);
      break;
    case TOK_OPEN_PAREN:
      pnext1(p);
      res = parse_expr(p);
      if (p->tok.tok != TOK_CLOSE_PAREN) SYNTAX_ERROR(p);
      break;
    case TOK_KEYWORD_FUNGSI:
      res = parse_function(p);
      break;
    case TOK_KEYWORD_THIS:
      emit_byte(p, OP_PUSH_THIS);
      break;
    default:
      SYNTAX_ERROR(p);
  }
  if (tok != TOK_KEYWORD_FUNGSI) pnext1(p);
  return res;
}

static baik_err_t parse_call_dot_mem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_DOT, TOK_OPEN_PAREN, TOK_OPEN_BRACKET, TOK_EOF};
  baik_err_t res = BAIK_OK;
  if ((res = parse_literal(p, &p->tok)) != BAIK_OK) return res;
  while (findtok(ops, p->tok.tok) != TOK_EOF) {
    if (p->tok.tok == TOK_OPEN_BRACKET) {
      int prev_tok = p->prev_tok;
      EXPECT(p, TOK_OPEN_BRACKET);
      if ((res = parse_expr(p)) != BAIK_OK) return res;
      emit_byte(p, OP_SWAP);
      EXPECT(p, TOK_CLOSE_BRACKET);
      if (!findtok(s_assign_ops, p->tok.tok) &&
          !findtok(s_postfix_ops, p->tok.tok) &&
         
          !findtok(s_postfix_ops, prev_tok)) {
        emit_byte(p, OP_GET);
      }
    } else if (p->tok.tok == TOK_OPEN_PAREN) {
      EXPECT(p, TOK_OPEN_PAREN);
      emit_byte(p, OP_ARGS);
      while (p->tok.tok != TOK_CLOSE_PAREN) {
        if ((res = parse_expr(p)) != BAIK_OK) return res;
        if (p->tok.tok == TOK_COMMA) pnext1(p);
      }
      emit_byte(p, OP_CALL);
      EXPECT(p, TOK_CLOSE_PAREN);
    } else if (p->tok.tok == TOK_DOT) {
      EXPECT(p, TOK_DOT);
      if ((res = parse_call_dot_mem(p, TOK_DOT)) != BAIK_OK) return res;
    }
  }
  (void) prev_op;
  return res;
}

static baik_err_t parse_postfix(struct pstate *p, int prev_op) {
  baik_err_t res = BAIK_OK;
  if ((res = parse_call_dot_mem(p, prev_op)) != BAIK_OK) return res;
  if (p->tok.tok == TOK_PLUS_PLUS || p->tok.tok == TOK_MINUS_MINUS) {
    int op = p->tok.tok == TOK_PLUS_PLUS ? TOK_POSTFIX_PLUS : TOK_POSTFIX_MINUS;
    emit_op(p, op);
    pnext1(p);
  }
  return res;
}

static baik_err_t parse_unary(struct pstate *p, int prev_op) {
  baik_err_t res = BAIK_OK;
  int op = TOK_EOF;
  if (findtok(s_unary_ops, p->tok.tok) != TOK_EOF) {
    op = p->tok.tok;
    pnext1(p);
  }
  if (findtok(s_unary_ops, p->tok.tok) != TOK_EOF) {
    res = parse_unary(p, prev_op);
  } else {
    res = parse_postfix(p, prev_op);
  }
  if (res != BAIK_OK) return res;
  if (op != TOK_EOF) {
    if (op == TOK_MINUS) op = TOK_UNARY_MINUS;
    if (op == TOK_PLUS) op = TOK_UNARY_PLUS;
    emit_op(p, op);
  }
  return res;
}

static baik_err_t parse_mul_div_rem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_MUL, TOK_DIV, TOK_REM, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_unary, parse_mul_div_rem, ops, prev_op);
}

static baik_err_t parse_plus_minus(struct pstate *p, int prev_op) {
  int ops[] = {TOK_PLUS, TOK_MINUS, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_mul_div_rem, parse_plus_minus, ops, prev_op);
}

static baik_err_t parse_shifts(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LSHIFT, TOK_RSHIFT, TOK_URSHIFT, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_plus_minus, parse_shifts, ops, prev_op);
}

static baik_err_t parse_comparison(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_shifts, parse_comparison, s_comparison_ops, prev_op);
}

static baik_err_t parse_equality(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_comparison, parse_equality, s_equality_ops, prev_op);
}

static baik_err_t parse_bitwise_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_equality, parse_bitwise_and, ops, prev_op);
}

static baik_err_t parse_bitwise_xor(struct pstate *p, int prev_op) {
  int ops[] = {TOK_XOR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_and, parse_bitwise_xor, ops, prev_op);
}

static baik_err_t parse_bitwise_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_xor, parse_bitwise_or, ops, prev_op);
}

static baik_err_t parse_logical_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_or, parse_logical_and, ops, prev_op);
}

static baik_err_t parse_logical_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_logical_and, parse_logical_or, ops, prev_op);
}

static baik_err_t parse_ternary(struct pstate *p, int prev_op) {
  baik_err_t res = BAIK_OK;
  if ((res = parse_logical_or(p, TOK_EOF)) != BAIK_OK) return res;
  if (prev_op != TOK_EOF) emit_op(p, prev_op);

  if (p->tok.tok == TOK_QUESTION) {
    size_t off_if, off_endif, off_else;
    EXPECT(p, TOK_QUESTION);

    emit_byte(p, OP_JMP_FALSE);
    off_if = p->cur_idx;
    emit_init_offset(p);

    if ((res = parse_ternary(p, TOK_EOF)) != BAIK_OK) return res;

    emit_byte(p, OP_JMP);
    off_else = p->cur_idx;
    emit_init_offset(p);
    off_endif = p->cur_idx;

    emit_byte(p, OP_DROP);

    EXPECT(p, TOK_COLON);
    if ((res = parse_ternary(p, TOK_EOF)) != BAIK_OK) return res;

   
    off_endif += baik_bcode_insert_offset(
        p, p->baik, off_else, p->cur_idx - off_else - BAIK_INIT_OFFSET_SIZE);

    baik_bcode_insert_offset(p, p->baik, off_if,
                            off_endif - off_if - BAIK_INIT_OFFSET_SIZE);
  }

  return res;
}

static baik_err_t parse_assignment(struct pstate *p, int prev_op) {
  PARSE_RTL_BINOP(p, parse_ternary, parse_assignment, s_assign_ops, prev_op);
}

static baik_err_t parse_expr(struct pstate *p) {
  return parse_assignment(p, TOK_EOF);
}

static baik_err_t parse_let(struct pstate *p) {
  baik_err_t res = BAIK_OK;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_ISI);
  for (;;) {
    struct tok tmp = p->tok;
    EXPECT(p, TOK_IDENT);

    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);

    if (p->tok.tok == TOK_ASSIGN) {
      pnext1(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, tmp.ptr, tmp.len);
      emit_byte(p, OP_FIND_SCOPE);
      if ((res = parse_expr(p)) != BAIK_OK) return res;
      emit_op(p, TOK_ASSIGN);
    } else {
      emit_byte(p, OP_PUSH_UNDEF);
    }
    if (p->tok.tok == TOK_COMMA) {
      emit_byte(p, OP_DROP);
      pnext1(p);
    }
    if (p->tok.tok == TOK_SEMICOLON || p->tok.tok == TOK_EOF) break;
  }
  return res;
}

static baik_err_t parse_block_or_stmt(struct pstate *p, int cs) {
  if (ptest(p) == TOK_OPEN_CURLY) {
    return parse_block(p, cs);
  } else {
    return parse_statement(p);
  }
}

static baik_err_t parse_for_in(struct pstate *p) {
  baik_err_t res = BAIK_OK;
  size_t off_b, off_check_end;

 
  emit_byte(p, OP_NEW_SCOPE);

 
  if (p->tok.tok == TOK_KEYWORD_ISI) {
    EXPECT(p, TOK_KEYWORD_ISI);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
  }
  emit_byte(p, OP_PUSH_STR);
  emit_str(p, p->tok.ptr, p->tok.len);

 
  EXPECT(p, TOK_IDENT);
  EXPECT(p, TOK_KEYWORD_IN);
  parse_expr(p);
  EXPECT(p, TOK_CLOSE_PAREN);

  emit_byte(p, OP_PUSH_UNDEF);

 
  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  emit_byte(p, 0);

  emit_byte(p, OP_FOR_IN_NEXT);
  emit_byte(p, OP_DUP);
  emit_byte(p, OP_JMP_FALSE);
  off_check_end = p->cur_idx;
  emit_init_offset(p);

  
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != BAIK_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != BAIK_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);
 
  baik_bcode_insert_offset(p, p->baik, off_check_end,
                          p->cur_idx - off_check_end - BAIK_INIT_OFFSET_SIZE);

  emit_byte(p, OP_BREAK);

  baik_bcode_insert_offset(p, p->baik, off_b,
                          p->cur_idx - off_b - BAIK_INIT_OFFSET_SIZE);

  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static int check_for_in(struct pstate *p) {
  struct pstate saved = *p;
  int forin = 0;
  if (p->tok.tok == TOK_KEYWORD_ISI) pnext1(p);
  if (p->tok.tok == TOK_IDENT) {
    pnext1(p);
    if (p->tok.tok == TOK_KEYWORD_IN) forin = 1;
  }
  *p = saved;
  return forin;
}

static baik_err_t parse_for(struct pstate *p) {
  baik_err_t res = BAIK_OK;
  size_t off_b, off_c, off_init_end;
  size_t off_incr_begin, off_cond_begin, off_cond_end;
  int buf_cur_idx;

  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_UNTUK);
  EXPECT(p, TOK_OPEN_PAREN);

  if (check_for_in(p)) return parse_for_in(p);

  emit_byte(p, OP_NEW_SCOPE);
  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  off_c = p->cur_idx;
  emit_init_offset(p);

  if (p->tok.tok == TOK_KEYWORD_ISI) {
    if ((res = parse_let(p)) != BAIK_OK) return res;
  } else {
    if ((res = parse_expr(p)) != BAIK_OK) return res;
  }
  EXPECT(p, TOK_SEMICOLON);
  emit_byte(p, OP_DROP);

  emit_byte(p, OP_JMP);
  off_init_end = p->cur_idx;
  emit_init_offset(p);

  off_incr_begin = p->cur_idx;
  off_cond_begin = p->cur_idx;

  if ((res = parse_expr(p)) != BAIK_OK) return res;
  EXPECT(p, TOK_SEMICOLON);

  buf_cur_idx = p->cur_idx;
  p->cur_idx = off_incr_begin;

  if ((res = parse_expr(p)) != BAIK_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);
  emit_byte(p, OP_DROP);

  {
    int incr_size = p->cur_idx - off_incr_begin;
    off_cond_begin += incr_size;
    p->cur_idx = buf_cur_idx + incr_size;
  }

  emit_byte(p, OP_JMP_FALSE);
  off_cond_end = p->cur_idx;
  emit_init_offset(p);

  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != BAIK_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != BAIK_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);
  baik_bcode_insert_offset(p, p->baik, off_cond_end,
                          p->cur_idx - off_cond_end - BAIK_INIT_OFFSET_SIZE);
  off_incr_begin += baik_bcode_insert_offset(
      p, p->baik, off_init_end,
      off_cond_begin - off_init_end - BAIK_INIT_OFFSET_SIZE);
  baik_bcode_insert_offset(p, p->baik, off_c,
                          off_incr_begin - off_c - BAIK_INIT_OFFSET_SIZE);

  emit_byte(p, OP_BREAK);
  baik_bcode_insert_offset(p, p->baik, off_b,
                          p->cur_idx - off_b - BAIK_INIT_OFFSET_SIZE);

  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static baik_err_t parse_while(struct pstate *p) {
  size_t off_cond_end, off_b;
  baik_err_t res = BAIK_OK;

  EXPECT(p, TOK_KEYWORD_ULANG);
  EXPECT(p, TOK_OPEN_PAREN);

  emit_byte(p, OP_NEW_SCOPE);
  emit_byte(p, OP_LOOP);
  off_b = p->cur_idx;
  emit_init_offset(p);
  emit_byte(p, 0);

  if ((res = parse_expr(p)) != BAIK_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);

  emit_byte(p, OP_JMP_FALSE);
  off_cond_end = p->cur_idx;
  emit_init_offset(p);

  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != BAIK_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != BAIK_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  baik_bcode_insert_offset(p, p->baik, off_cond_end,
                          p->cur_idx - off_cond_end - BAIK_INIT_OFFSET_SIZE);
  emit_byte(p, OP_BREAK);
  baik_bcode_insert_offset(p, p->baik, off_b,
                          p->cur_idx - off_b - BAIK_INIT_OFFSET_SIZE);
  emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static baik_err_t parse_if(struct pstate *p) {
  size_t off_if, off_endif;
  baik_err_t res = BAIK_OK;
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_JIKA);
  EXPECT(p, TOK_OPEN_PAREN);
  if ((res = parse_expr(p)) != BAIK_OK) return res;

  emit_byte(p, OP_JMP_FALSE);
  off_if = p->cur_idx;
  emit_init_offset(p);

  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block_or_stmt(p, 1)) != BAIK_OK) return res;

  if (p->tok.tok == TOK_KEYWORD_LAINNYA) {
   
    size_t off_else, off_endelse;
    pnext1(p);
    emit_byte(p, OP_JMP);
    off_else = p->cur_idx;
    emit_init_offset(p);
    off_endif = p->cur_idx;

    emit_byte(p, OP_DROP);
    if ((res = parse_block_or_stmt(p, 1)) != BAIK_OK) return res;
    off_endelse = p->cur_idx;
    off_endif += baik_bcode_insert_offset(
        p, p->baik, off_else, off_endelse - off_else - BAIK_INIT_OFFSET_SIZE);
  } else {
    off_endif = p->cur_idx;
  }

  baik_bcode_insert_offset(p, p->baik, off_if,
                          off_endif - off_if - BAIK_INIT_OFFSET_SIZE);
  return res;
}

static void pstate_revert(struct pstate *p, struct pstate *old,
                          int old_bcode_gen_len) {
  p->pos = old->pos;
  p->line_no = old->line_no;
  p->last_emitted_line_no = old->last_emitted_line_no;
  p->offset_lineno_map.len = old->offset_lineno_map.len;
  p->prev_tok = old->prev_tok;
  p->tok = old->tok;
  p->baik->bcode_gen.len = old_bcode_gen_len;
  p->cur_idx = old->cur_idx;
  p->depth = old->depth;
}

static baik_err_t parse_return(struct pstate *p) {
  int old_bcode_gen_len;
  struct pstate p_saved;
  EXPECT(p, TOK_KEYWORD_BALIK);
  p_saved = *p;
  old_bcode_gen_len = p->baik->bcode_gen.len;
  if (parse_expr(p) != BAIK_OK) {
    pstate_revert(p, &p_saved, old_bcode_gen_len);
    emit_byte(p, OP_PUSH_UNDEF);
  }
  emit_byte(p, OP_SETRETVAL);
  emit_byte(p, OP_RETURN);
  return BAIK_OK;
}

static baik_err_t parse_statement(struct pstate *p) {
  LOG(LL_VERBOSE_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  switch (p->tok.tok) {
    case TOK_SEMICOLON:
      emit_byte(p, OP_PUSH_UNDEF);
      pnext1(p);
      return BAIK_OK;
    case TOK_KEYWORD_ISI:
      return parse_let(p);
    case TOK_OPEN_CURLY:
      return parse_block(p, 1);
    case TOK_KEYWORD_BALIK:
      return parse_return(p);
    case TOK_KEYWORD_UNTUK:
      return parse_for(p);
    case TOK_KEYWORD_ULANG:
      return parse_while(p);
    case TOK_KEYWORD_BERHENTI:
      emit_byte(p, OP_PUSH_UNDEF);
      emit_byte(p, OP_BREAK);
      pnext1(p);
      return BAIK_OK;
    case TOK_KEYWORD_TERUSKAN:
      emit_byte(p, OP_CONTINUE);
      pnext1(p);
      return BAIK_OK;
    case TOK_KEYWORD_JIKA:
      return parse_if(p);
    case TOK_KEYWORD_SAMA:
    case TOK_KEYWORD_CATCH:
    case TOK_KEYWORD_DELETE:
    case TOK_KEYWORD_KERJAKAN:
    case TOK_KEYWORD_INSTANCEOF:
    case TOK_KEYWORD_NEW:
    case TOK_KEYWORD_PILIH:
    case TOK_KEYWORD_THROW:
    case TOK_KEYWORD_TRY:
    case TOK_KEYWORD_VAR:
    case TOK_KEYWORD_VOID:
    case TOK_KEYWORD_WITH:
      baik_set_errorf(p->baik, BAIK_SYNTAX_ERROR, "[%.*s] tidak terimplementasi",
                     p->tok.len, p->tok.ptr);
      return BAIK_SYNTAX_ERROR;
    default: {
      baik_err_t res = BAIK_OK;
      for (;;) {
        if ((res = parse_expr(p)) != BAIK_OK) return res;
        if (p->tok.tok != TOK_COMMA) break;
        emit_byte(p, OP_DROP);
        pnext1(p);
      }
      return res;
    }
  }
}

BAIK_PRIVATE baik_err_t
baik_parse(const char *path, const char *buf, struct baik *baik) {
  baik_err_t res = BAIK_OK;
  struct pstate p;
  size_t start_idx, llen;
  int map_len;
  baik_header_item_t bcode_offset, map_offset, total_size;

  pinit(path, buf, &p);
  p.baik = baik;
  p.cur_idx = p.baik->bcode_gen.len;
  emit_byte(&p, OP_BCODE_HEADER);

  start_idx = p.baik->bcode_gen.len;
  mbuf_append(&p.baik->bcode_gen, NULL,
              sizeof(baik_header_item_t) * BAIK_HDR_ITEMS_CNT);

  mbuf_append(&p.baik->bcode_gen, path, strlen(path) + 1);

  bcode_offset = p.baik->bcode_gen.len - start_idx;
  memcpy(p.baik->bcode_gen.buf + start_idx +
             sizeof(baik_header_item_t) * BAIK_HDR_ITEM_BCODE_OFFSET,
         &bcode_offset, sizeof(baik_header_item_t));

  p.start_bcode_idx = p.baik->bcode_gen.len;
  p.cur_idx = p.baik->bcode_gen.len;

  res = parse_statement_list(&p, TOK_EOF);
  emit_byte(&p, OP_EXIT);

  map_offset = p.baik->bcode_gen.len - start_idx;
  memcpy(p.baik->bcode_gen.buf + start_idx +
             sizeof(baik_header_item_t) * BAIK_HDR_ITEM_MAP_OFFSET,
         &map_offset, sizeof(baik_header_item_t));

  map_len = p.offset_lineno_map.len;
  llen = BAIK_EM_varint_llen(map_len);
  mbuf_resize(&p.baik->bcode_gen, p.baik->bcode_gen.size + llen);
  BAIK_EM_varint_encode(
      map_len, (uint8_t *) p.baik->bcode_gen.buf + p.baik->bcode_gen.len, llen);
  p.baik->bcode_gen.len += llen;

  mbuf_append(&p.baik->bcode_gen, p.offset_lineno_map.buf,
              p.offset_lineno_map.len);

  total_size = p.baik->bcode_gen.len - start_idx;
  memcpy(p.baik->bcode_gen.buf + start_idx +
             sizeof(baik_header_item_t) * BAIK_HDR_ITEM_TOTAL_SIZE,
         &total_size, sizeof(baik_header_item_t));

  mbuf_free(&p.offset_lineno_map);

  if (res == BAIK_OK) {
    baik_bcode_commit(baik);
  } else {
    mbuf_free(&baik->bcode_gen);
  }

  return res;
}

baik_val_t baik_mk_null(void) {
  return BAIK_NULL;
}

int baik_is_null(baik_val_t v) {
  return v == BAIK_NULL;
}

baik_val_t baik_mk_undefined(void) {
  return BAIK_UNDEFINED;
}

int baik_is_undefined(baik_val_t v) {
  return v == BAIK_UNDEFINED;
}

baik_val_t baik_mk_number(struct baik *baik, double v) {
  baik_val_t res;
  (void) baik;
 
  if (isnan(v)) {
    res = BAIK_TAG_NAN;
  } else {
    union {
      double d;
      baik_val_t r;
    } u;
    u.d = v;
    res = u.r;
  }
  return res;
}

static double get_double(baik_val_t v) {
  union {
    double d;
    baik_val_t v;
  } u;
  u.v = v;
 
  return u.d;
}

double baik_get_double(struct baik *baik, baik_val_t v) {
  (void) baik;
  return get_double(v);
}

int baik_get_int(struct baik *baik, baik_val_t v) {
  (void) baik;
 
  return (int) (unsigned int) get_double(v);
}

int32_t baik_get_int32(struct baik *baik, baik_val_t v) {
  (void) baik;
  return (int32_t) get_double(v);
}

int baik_is_number(baik_val_t v) {
  return v == BAIK_TAG_NAN || !isnan(get_double(v));
}

baik_val_t baik_mk_boolean(struct baik *baik, int v) {
  (void) baik;
  return (v ? 1 : 0) | BAIK_TAG_BOOLEAN;
}

int baik_get_bool(struct baik *baik, baik_val_t v) {
  (void) baik;
  if (baik_is_boolean(v)) {
    return v & 1;
  } else {
    return 0;
  }
}

int baik_is_boolean(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_BOOLEAN;
}

#define BAIK_IS_POINTER_LEGIT(n) \
  (((n) &BAIK_TAG_MASK) == 0 || ((n) &BAIK_TAG_MASK) == (~0 & BAIK_TAG_MASK))

BAIK_PRIVATE baik_val_t baik_pointer_to_value(struct baik *baik, void *p) {
  uint64_t n = ((uint64_t)(uintptr_t) p);

  if (!BAIK_IS_POINTER_LEGIT(n)) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : kesalahan nilai pointer: %p", p);
  }
  return n & ~BAIK_TAG_MASK;
}

BAIK_PRIVATE baik_val_t baik_legit_pointer_to_value(void *p) {
  uint64_t n = ((uint64_t)(uintptr_t) p);

  assert(BAIK_IS_POINTER_LEGIT(n));
  return n & ~BAIK_TAG_MASK;
}

BAIK_PRIVATE void *get_ptr(baik_val_t v) {
  return (void *) (uintptr_t)(v & 0xFFFFFFFFFFFFUL);
}

void *baik_get_ptr(struct baik *baik, baik_val_t v) {
  (void) baik;
  if (!baik_is_foreign(v)) {
    return NULL;
  }
  return get_ptr(v);
}

baik_val_t baik_mk_foreign(struct baik *baik, void *p) {
  (void) baik;
  return baik_pointer_to_value(baik, p) | BAIK_TAG_FOREIGN;
}

baik_val_t baik_mk_foreign_func(struct baik *baik, baik_func_ptr_t fn) {
  union {
    baik_func_ptr_t fn;
    void *p;
  } u;
  u.fn = fn;
  (void) baik;
  return baik_pointer_to_value(baik, u.p) | BAIK_TAG_FOREIGN;
}

int baik_is_foreign(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_FOREIGN;
}

baik_val_t baik_mk_function(struct baik *baik, size_t off) {
  (void) baik;
  return (baik_val_t) off | BAIK_TAG_FUNCTION;
}

int baik_is_function(baik_val_t v) {
  return (v & BAIK_TAG_MASK) == BAIK_TAG_FUNCTION;
}

BAIK_PRIVATE void baik_op_isnan(struct baik *baik) {
  baik_val_t ret = BAIK_UNDEFINED;
  baik_val_t val = baik_arg(baik, 0);

  ret = baik_mk_boolean(baik, val == BAIK_TAG_NAN);

  baik_return(baik, ret);
}

typedef unsigned short Rune;
static int chartorune(Rune *rune, const char *str) {
  *rune = *(unsigned char *) str;
  return 1;
}
static int runetochar(char *str, Rune *rune) {
  str[0] = (char) *rune;
  return 1;
}

#ifndef BAIK_STRING_BUF_RESERVE
#define BAIK_STRING_BUF_RESERVE 100
#endif

BAIK_PRIVATE size_t unescape(const char *s, size_t len, char *to);
BAIK_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t flags);

#define GET_VAL_NAN_PAYLOAD(v) ((char *) &(v))

int baik_is_string(baik_val_t v) {
  uint64_t t = v & BAIK_TAG_MASK;
  return t == BAIK_TAG_STRING_I || t == BAIK_TAG_STRING_F ||
         t == BAIK_TAG_STRING_O || t == BAIK_TAG_STRING_5 ||
         t == BAIK_TAG_STRING_D;
}

baik_val_t baik_mk_string(struct baik *baik, const char *p, size_t len, int copy) {
  struct mbuf *m;
  baik_val_t offset, tag = BAIK_TAG_STRING_F;
  if (len == 0) {
   
    copy = 1;
  }
  m = copy ? &baik->owned_strings : &baik->foreign_strings;
  offset = m->len;

  if (len == ~((size_t) 0)) len = strlen(p);

  if (copy) {
   
    if (len <= 4) {
      char *s = GET_VAL_NAN_PAYLOAD(offset) + 1;
      offset = 0;
      if (p != 0) {
        memcpy(s, p, len);
      }
      s[-1] = len;
      tag = BAIK_TAG_STRING_I;
    } else if (len == 5) {
      char *s = GET_VAL_NAN_PAYLOAD(offset);
      offset = 0;
      if (p != 0) {
        memcpy(s, p, len);
      }
      tag = BAIK_TAG_STRING_5; 
    } else {
      if (gc_strings_is_gc_needed(baik)) {
        baik->need_gc = 1;
      }

      if ((m->len + len) > m->size) {
        char *prev_buf = m->buf;
        mbuf_resize(m, m->len + len + BAIK_STRING_BUF_RESERVE);

       
        if (p >= prev_buf && p < (prev_buf + m->len)) {
          p += (m->buf - prev_buf);
        }
      }

      embed_string(m, m->len, p, len, EMBSTR_ZERO_TERM);
      tag = BAIK_TAG_STRING_O;
    }
  } else {
   
    if (sizeof(void *) <= 4 && len <= (1 << 15)) {
     
      offset = (uint64_t) len << 32 | (uint64_t)(uintptr_t) p;
    } else {
     
      size_t pos = m->len;
      size_t llen = BAIK_EM_varint_llen(len);

      mbuf_insert(m, pos, NULL, llen + sizeof(p));

      BAIK_EM_varint_encode(len, (uint8_t *) (m->buf + pos), llen);
      memcpy(m->buf + pos + llen, &p, sizeof(p));
    }
    tag = BAIK_TAG_STRING_F;
  }
  return (offset & ~BAIK_TAG_MASK) | tag;
}


const char *baik_get_string(struct baik *baik, baik_val_t *v, size_t *sizep) {
  uint64_t tag = v[0] & BAIK_TAG_MASK;
  const char *p = NULL;
  size_t size = 0, llen;

  if (!baik_is_string(*v)) {
    goto clean;
  }

  if (tag == BAIK_TAG_STRING_I) {
    p = GET_VAL_NAN_PAYLOAD(*v) + 1;
    size = p[-1];
  } else if (tag == BAIK_TAG_STRING_5) {
    p = GET_VAL_NAN_PAYLOAD(*v);
    size = 5;
  } else if (tag == BAIK_TAG_STRING_O) {
    size_t offset = (size_t) gc_string_baik_val_to_offset(*v);
    char *s = baik->owned_strings.buf + offset;
    uint64_t v = 0;
    if (offset < baik->owned_strings.len &&
        BAIK_EM_varint_decode((uint8_t *) s, baik->owned_strings.len - offset, &v,
                         &llen)) {
      size = v;
      p = s + llen;
    } else {
      goto clean;
    }
  } else if (tag == BAIK_TAG_STRING_F) {
    uint16_t len = (*v >> 32) & 0xFFFF;
    if (sizeof(void *) <= 4 && len != 0) {
      size = (size_t) len;
      p = (const char *) (uintptr_t) *v;
    } else {
      size_t offset = (size_t) gc_string_baik_val_to_offset(*v);
      char *s = baik->foreign_strings.buf + offset;
      uint64_t v = 0;
      if (offset < baik->foreign_strings.len &&
          BAIK_EM_varint_decode((uint8_t *) s, baik->foreign_strings.len - offset, &v,
                           &llen)) {
        size = v;
        memcpy((char **) &p, s + llen, sizeof(p));
      } else {
        goto clean;
      }
    }
  } else {
    assert(0);
  }

clean:
  if (sizep != NULL) {
    *sizep = size;
  }
  return p;
}

const char *baik_get_cstring(struct baik *baik, baik_val_t *value) {
  size_t size;
  const char *s = baik_get_string(baik, value, &size);
  if (s == NULL) return NULL;
  if (s[size] != 0 || strlen(s) != size) {
    return NULL;
  }
  return s;
}

int baik_strcmp(struct baik *baik, baik_val_t *a, const char *b, size_t len) {
  size_t n;
  const char *s;
  if (len == (size_t) ~0) len = strlen(b);
  s = baik_get_string(baik, a, &n);
  if (n != len) {
    return n - len;
  }
  return strncmp(s, b, len);
}

BAIK_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok) {
  char *e;
  unsigned long res = strtoul(s, &e, 10);
  *ok = (e == s + len) && len != 0;
  return res;
}

BAIK_PRIVATE baik_err_t
str_to_ulong(struct baik *baik, baik_val_t v, int *ok, unsigned long *res) {
  enum baik_err ret = BAIK_OK;
  size_t len = 0;
  const char *p = baik_get_string(baik, &v, &len);
  *res = cstr_to_ulong(p, len, ok);

  return ret;
}

BAIK_PRIVATE int s_cmp(struct baik *baik, baik_val_t a, baik_val_t b) {
  size_t a_len, b_len;
  const char *a_ptr, *b_ptr;

  a_ptr = baik_get_string(baik, &a, &a_len);
  b_ptr = baik_get_string(baik, &b, &b_len);

  if (a_len == b_len) {
    return memcmp(a_ptr, b_ptr, a_len);
  }
  if (a_len > b_len) {
    return 1;
  } else if (a_len < b_len) {
    return -1;
  } else {
    return 0;
  }
}

BAIK_PRIVATE baik_val_t s_concat(struct baik *baik, baik_val_t a, baik_val_t b) {
  size_t a_len, b_len, res_len;
  const char *a_ptr, *b_ptr, *res_ptr;
  baik_val_t res;

  a_ptr = baik_get_string(baik, &a, &a_len);
  b_ptr = baik_get_string(baik, &b, &b_len);
  res = baik_mk_string(baik, NULL, a_len + b_len, 1);
  a_ptr = baik_get_string(baik, &a, &a_len);
  b_ptr = baik_get_string(baik, &b, &b_len);
  res_ptr = baik_get_string(baik, &res, &res_len);
  memcpy((char *) res_ptr, a_ptr, a_len);
  memcpy((char *) res_ptr + a_len, b_ptr, b_len);

  return res;
}

BAIK_PRIVATE void baik_string_slice(struct baik *baik) {
  int nargs = baik_nargs(baik);
  baik_val_t ret = baik_mk_number(baik, 0);
  baik_val_t beginSlice_v = BAIK_UNDEFINED;
  baik_val_t endSlice_v = BAIK_UNDEFINED;
  int beginSlice = 0;
  int endSlice = 0;
  size_t size;
  const char *s = NULL;

  if (!baik_check_arg(baik, -1, "this", BAIK_TYPE_STRING, NULL)) {
    goto clean;
  }
  s = baik_get_string(baik, &baik->vals.this_obj, &size);

  if (!baik_check_arg(baik, 0, "beginSlice", BAIK_TYPE_NUMBER, &beginSlice_v)) {
    goto clean;
  }
  beginSlice = baik_normalize_idx(baik_get_int(baik, beginSlice_v), size);

  if (nargs >= 2) {
   
   
    if (!baik_check_arg(baik, 1, "endSlice", BAIK_TYPE_NUMBER, &endSlice_v)) {
      goto clean;
    }
    endSlice = baik_normalize_idx(baik_get_int(baik, endSlice_v), size);
  } else {
   
    endSlice = size;
  }

  if (endSlice < beginSlice) {
    endSlice = beginSlice;
  }

  ret = baik_mk_string(baik, s + beginSlice, endSlice - beginSlice, 1);

clean:
  baik_return(baik, ret);
}

BAIK_PRIVATE void baik_string_index_of(struct baik *baik) {
  baik_val_t ret = baik_mk_number(baik, -1);
  baik_val_t substr_v = BAIK_UNDEFINED;
  baik_val_t idx_v = BAIK_UNDEFINED;
  int idx = 0;
  const char *str = NULL, *substr = NULL;
  size_t str_len = 0, substr_len = 0;

  if (!baik_check_arg(baik, -1, "this", BAIK_TYPE_STRING, NULL)) {
    goto clean;
  }
  str = baik_get_string(baik, &baik->vals.this_obj, &str_len);

  if (!baik_check_arg(baik, 0, "searchValue", BAIK_TYPE_STRING, &substr_v)) {
    goto clean;
  }
  substr = baik_get_string(baik, &substr_v, &substr_len);
  if (baik_nargs(baik) > 1) {
    if (!baik_check_arg(baik, 1, "fromIndex", BAIK_TYPE_NUMBER, &idx_v)) {
      goto clean;
    }
    idx = baik_get_int(baik, idx_v);
    if (idx < 0) idx = 0;
    if ((size_t) idx > str_len) idx = str_len;
  }
  {
    const char *substr_p;
    struct baik_generic_str mgstr, mgsubstr;
    mgstr.p = str + idx;
    mgstr.len = str_len - idx;
    mgsubstr.p = substr;
    mgsubstr.len = substr_len;
    substr_p = baik_generic_strstr(mgstr, mgsubstr);
    if (substr_p != NULL) {
      ret = baik_mk_number(baik, (int) (substr_p - str));
    }
  }

clean:
  baik_return(baik, ret);
}

BAIK_PRIVATE void baik_string_char_code_at(struct baik *baik) {
  baik_val_t ret = BAIK_UNDEFINED;
  baik_val_t idx_v = BAIK_UNDEFINED;
  int idx = 0;
  size_t size;
  const char *s = NULL;

  if (!baik_check_arg(baik, -1, "this", BAIK_TYPE_STRING, NULL)) {
    goto clean;
  }
  s = baik_get_string(baik, &baik->vals.this_obj, &size);

  if (!baik_check_arg(baik, 0, "index", BAIK_TYPE_NUMBER, &idx_v)) {
    goto clean;
  }
  idx = baik_normalize_idx(baik_get_int(baik, idx_v), size);
  if (idx >= 0 && idx < (int) size) {
    ret = baik_mk_number(baik, ((unsigned char *) s)[idx]);
  }

clean:
  baik_return(baik, ret);
}

BAIK_PRIVATE void baik_mkstr(struct baik *baik) {
  int nargs = baik_nargs(baik);
  baik_val_t ret = BAIK_UNDEFINED;

  char *ptr = NULL;
  int offset = 0;
  int len = 0;
  int copy = 0;

  baik_val_t ptr_v = BAIK_UNDEFINED;
  baik_val_t offset_v = BAIK_UNDEFINED;
  baik_val_t len_v = BAIK_UNDEFINED;
  baik_val_t copy_v = BAIK_UNDEFINED;

  if (nargs == 2) {
    ptr_v = baik_arg(baik, 0);
    len_v = baik_arg(baik, 1);
  } else if (nargs == 3) {
    ptr_v = baik_arg(baik, 0);
    offset_v = baik_arg(baik, 1);
    len_v = baik_arg(baik, 2);
  } else if (nargs == 4) {
    ptr_v = baik_arg(baik, 0);
    offset_v = baik_arg(baik, 1);
    len_v = baik_arg(baik, 2);
    copy_v = baik_arg(baik, 3);
  } else {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR,
                       "mkstr membutuhkan 2, 3 atau 4 argument: (ptr, len), (ptr, "
                       "offset, len) atau (ptr, offset, len, copy)");
    goto clean;
  }

  if (!baik_is_foreign(ptr_v)) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : pointer yang tidak dikenali ptr");
    goto clean;
  }

  if (offset_v != BAIK_UNDEFINED && !baik_is_number(offset_v)) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : offset harus angka");
    goto clean;
  }

  if (!baik_is_number(len_v)) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : len harus angka");
    goto clean;
  }

  copy = baik_is_truthy(baik, copy_v);
  ptr = (char *) baik_get_ptr(baik, ptr_v);
  if (offset_v != BAIK_UNDEFINED) {
    offset = baik_get_int(baik, offset_v);
  }
  len = baik_get_int(baik, len_v);

  ret = baik_mk_string(baik, ptr + offset, len, copy);

clean:
  baik_return(baik, ret);
}

enum unescape_error {
  SLRE_INVALID_HEX_DIGIT,
  SLRE_INVALID_ESC_CHAR,
  SLRE_UNTERM_ESC_SEQ,
};

static int hex(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -SLRE_INVALID_HEX_DIGIT;
}

static int nextesc(const char **p) {
  const unsigned char *s = (unsigned char *) (*p)++;
  switch (*s) {
    case 0:
      return -SLRE_UNTERM_ESC_SEQ;
    case 'c':
      ++*p;
      return *s & 31;
    case 'b':
      return '\b';
    case 't':
      return '\t';
    case 'n':
      return '\n';
    case 'v':
      return '\v';
    case 'f':
      return '\f';
    case 'r':
      return '\r';
    case '\\':
      return '\\';
    case 'u':
      if (isxdigit(s[1]) && isxdigit(s[2]) && isxdigit(s[3]) &&
          isxdigit(s[4])) {
        (*p) += 4;
        return hex(s[1]) << 12 | hex(s[2]) << 8 | hex(s[3]) << 4 | hex(s[4]);
      }
      return -SLRE_INVALID_HEX_DIGIT;
    case 'x':
      if (isxdigit(s[1]) && isxdigit(s[2])) {
        (*p) += 2;
        return (hex(s[1]) << 4) | hex(s[2]);
      }
      return -SLRE_INVALID_HEX_DIGIT;
    default:
      return -SLRE_INVALID_ESC_CHAR;
  }
}

BAIK_PRIVATE size_t unescape(const char *s, size_t len, char *to) {
  const char *end = s + len;
  size_t n = 0;
  char tmp[4];
  Rune r;

  while (s < end) {
    s += chartorune(&r, s);
    if (r == '\\' && s < end) {
      switch (*s) {
        case '"':
          s++, r = '"';
          break;
        case '\'':
          s++, r = '\'';
          break;
        case '\n':
          s++, r = '\n';
          break;
        default: {
          const char *tmp_s = s;
          int i = nextesc(&s);
          switch (i) {
            case -SLRE_INVALID_ESC_CHAR:
              r = '\\';
              s = tmp_s;
              n += runetochar(to == NULL ? tmp : to + n, &r);
              s += chartorune(&r, s);
              break;
            case -SLRE_INVALID_HEX_DIGIT:
            default:
              r = i;
          }
        }
      }
    }
    n += runetochar(to == NULL ? tmp : to + n, &r);
  }

  return n;
}

BAIK_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t flags) {
  char *old_base = m->buf;
  uint8_t p_backed_by_mbuf = p >= old_base && p < old_base + m->len;
  size_t n = (flags & EMBSTR_UNESCAPE) ? unescape(p, len, NULL) : len;
  size_t k = BAIK_EM_varint_llen(n);
  size_t tot_len = k + n + !!(flags & EMBSTR_ZERO_TERM);

  mbuf_insert(m, offset, NULL, tot_len);

  if (p_backed_by_mbuf) {
    p += m->buf - old_base;
  }

  BAIK_EM_varint_encode(n, (unsigned char *) m->buf + offset, k);

  if (p != 0) {
    if (flags & EMBSTR_UNESCAPE) {
      unescape(p, len, m->buf + offset + k);
    } else {
      memcpy(m->buf + offset + k, p, len);
    }
  }

  if (flags & EMBSTR_ZERO_TERM) {
    m->buf[offset + tot_len - 1] = '\0';
  }
}

#include <stdlib.h>
#include <string.h>

BAIK_PRIVATE void pinit(const char *file_name, const char *buf,
                       struct pstate *p) {
  memset(p, 0, sizeof(*p));
  p->line_no = 1;
  p->last_emitted_line_no = 1;
  p->file_name = file_name;
  p->buf = p->pos = buf;
  mbuf_init(&p->offset_lineno_map, 0);
}

static int baik_is_space(int c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\f' ||
         c == '\v';
}

BAIK_PRIVATE int baik_is_digit(int c) {
  return c >= '0' && c <= '9';
}

static int baik_is_alpha(int c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

BAIK_PRIVATE int baik_is_ident(int c) {
  return c == '_' || c == '$' || baik_is_alpha(c);
}

static int longtok(struct pstate *p, const char *first_chars,
                   const char *second_chars) {
  if (strchr(first_chars, p->pos[0]) == NULL) return TOK_EOF;
  if (p->pos[1] != '\0' && strchr(second_chars, p->pos[1]) != NULL) {
    p->tok.len++;
    p->pos++;
    return p->pos[-1] << 8 | p->pos[0];
  }
  return p->pos[0];
}

static int longtok3(struct pstate *p, char a, char b, char c) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c) {
    p->tok.len += 2;
    p->pos += 2;
    return p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
}

static int longtok4(struct pstate *p, char a, char b, char c, char d) {
  if (p->pos[0] == a && p->pos[1] == b && p->pos[2] == c && p->pos[3] == d) {
    p->tok.len += 3;
    p->pos += 3;
    return p->pos[-3] << 24 | p->pos[-2] << 16 | p->pos[-1] << 8 | p->pos[0];
  }
  return TOK_EOF;
}

static int getnum(struct pstate *p) {
  if (p->pos[0] == '0' && p->pos[1] == 'x') {
    
    strtoul(p->pos + 2, (char **) &p->pos, 16);
  } else {
    strtod(p->pos, (char **) &p->pos);
  }
  p->tok.len = p->pos - p->tok.ptr;
  p->pos--;
  return TOK_NUM;
}

static int is_reserved_word_token(const char *s, int len) {
  const char *reserved[] = {
      "berhenti",     "sama",   "catch",   "teruskan",   "debugger", "standar",
      "delete",    "kerjakan",     "lainnya", "salah",      "finally",  "untuk",
      "fungsi",  "jika",   "in",      "instanceof", "new",      "kosong",
      "balik",    "pilih", "this",    "throw",      "benar",     "try",
      "tipe",    "var",    "void",    "ulang",      "with",     "isi",
      "takterdefinisi", NULL};
  int i;
  if (!baik_is_alpha(s[0])) return 0;
  for (i = 0; reserved[i] != NULL; i++) {
    if (len == (int) strlen(reserved[i]) && strncmp(s, reserved[i], len) == 0)
      return i + 1;
  }
  return 0;
}

static int getident(struct pstate *p) {
  while (baik_is_ident(p->pos[0]) || baik_is_digit(p->pos[0])) p->pos++;
  p->tok.len = p->pos - p->tok.ptr;
  p->pos--;
  return TOK_IDENT;
}

static int getstr(struct pstate *p) {
  int quote = *p->pos++;
  p->tok.ptr++;
  while (p->pos[0] != '\0' && p->pos[0] != quote) {
    if (p->pos[0] == '\\' && p->pos[1] != '\0' &&
        (p->pos[1] == quote || strchr("bfnrtv\\", p->pos[1]) != NULL)) {
      p->pos += 2;
    } else {
      p->pos++;
    }
  }
  p->tok.len = p->pos - p->tok.ptr;
  return TOK_STR;
}

static void skip_spaces_and_comments(struct pstate *p) {
  const char *pos;
  do {
    pos = p->pos;
    while (baik_is_space(p->pos[0])) {
      if (p->pos[0] == '\n') p->line_no++;
      p->pos++;
    }
    if (p->pos[0] == '/' && p->pos[1] == '/') {
      while (p->pos[0] != '\0' && p->pos[0] != '\n') p->pos++;
    }
    if (p->pos[0] == '/' && p->pos[1] == '*') {
      p->pos += 2;
      while (p->pos[0] != '\0') {
        if (p->pos[0] == '\n') p->line_no++;
        if (p->pos[0] == '*' && p->pos[1] == '/') {
          p->pos += 2;
          break;
        }
        p->pos++;
      }
    }
  } while (pos < p->pos);
}

static int ptranslate(int tok) {
#define DT(a, b) ((a) << 8 | (b))
#define TT(a, b, c) ((a) << 16 | (b) << 8 | (c))
#define QT(a, b, c, d) ((a) << 24 | (b) << 16 | (c) << 8 | (d))
 
 
  switch (tok) {
    case ':': return TOK_COLON;
    case ';': return TOK_SEMICOLON;
    case ',': return TOK_COMMA;
    case '=': return TOK_ASSIGN;
    case '{': return TOK_OPEN_CURLY;
    case '}': return TOK_CLOSE_CURLY;
    case '(': return TOK_OPEN_PAREN;
    case ')': return TOK_CLOSE_PAREN;
    case '[': return TOK_OPEN_BRACKET;
    case ']': return TOK_CLOSE_BRACKET;
    case '*': return TOK_MUL;
    case '+': return TOK_PLUS;
    case '-': return TOK_MINUS;
    case '/': return TOK_DIV;
    case '%': return TOK_REM;
    case '&': return TOK_AND;
    case '|': return TOK_OR;
    case '^': return TOK_XOR;
    case '.': return TOK_DOT;
    case '?': return TOK_QUESTION;
    case '!': return TOK_NOT;
    case '~': return TOK_TILDA;
    case '<': return TOK_LT;
    case '>': return TOK_GT;
    case DT('<','<'): return TOK_LSHIFT;
    case DT('>','>'): return TOK_RSHIFT;
    case DT('-','-'): return TOK_MINUS_MINUS;
    case DT('+','+'): return TOK_PLUS_PLUS;
    case DT('+','='): return TOK_PLUS_ASSIGN;
    case DT('-','='): return TOK_MINUS_ASSIGN;
    case DT('*','='): return TOK_MUL_ASSIGN;
    case DT('/','='): return TOK_DIV_ASSIGN;
    case DT('&','='): return TOK_AND_ASSIGN;
    case DT('|','='): return TOK_OR_ASSIGN;
    case DT('%','='): return TOK_REM_ASSIGN;
    case DT('^','='): return TOK_XOR_ASSIGN;
    case DT('=','='): return TOK_EQ;
    case DT('!','='): return TOK_NE;
    case DT('<','='): return TOK_LE;
    case DT('>','='): return TOK_GE;
    case DT('&','&'): return TOK_LOGICAL_AND;
    case DT('|','|'): return TOK_LOGICAL_OR;
    case TT('=','=','='): return TOK_EQ_EQ;
    case TT('!','=','='): return TOK_NE_NE;
    case TT('<','<','='): return TOK_LSHIFT_ASSIGN;
    case TT('>','>','='): return TOK_RSHIFT_ASSIGN;
    case TT('>','>','>'): return TOK_URSHIFT;
    case QT('>','>','>','='): return TOK_URSHIFT_ASSIGN;
  }
 
  return tok;
}

BAIK_PRIVATE int pnext(struct pstate *p) {
  int tmp, tok = TOK_INVALID;

  skip_spaces_and_comments(p);
  p->tok.ptr = p->pos;
  p->tok.len = 1;

  if (p->pos[0] == '\0') {
    tok = TOK_EOF;
  } else if (baik_is_digit(p->pos[0])) {
    tok = getnum(p);
  } else if (p->pos[0] == '\'' || p->pos[0] == '"') {
    tok = getstr(p);
  } else if (baik_is_ident(p->pos[0])) {
    tok = getident(p);
   
    tok += is_reserved_word_token(p->tok.ptr, p->tok.len);
  } else if (strchr(",.:;{}[]()?", p->pos[0]) != NULL) {
    tok = p->pos[0];
  } else if ((tmp = longtok3(p, '<', '<', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok4(p, '>', '>', '>', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '>', '>', '>')) != TOK_EOF ||
             (tmp = longtok3(p, '=', '=', '=')) != TOK_EOF ||
             (tmp = longtok3(p, '!', '=', '=')) != TOK_EOF ||
             (tmp = longtok(p, "&", "&=")) != TOK_EOF ||
             (tmp = longtok(p, "|", "|=")) != TOK_EOF ||
             (tmp = longtok(p, "<", "<=")) != TOK_EOF ||
             (tmp = longtok(p, ">", ">=")) != TOK_EOF ||
             (tmp = longtok(p, "-", "-=")) != TOK_EOF ||
             (tmp = longtok(p, "+", "+=")) != TOK_EOF) {
    tok = tmp;
  } else if ((tmp = longtok(p, "^~+-%/*<>=!|&", "=")) != TOK_EOF) {
    tok = tmp;
  }
  if (p->pos[0] != '\0') p->pos++;
  LOG(LL_VERBOSE_DEBUG, ("  --> %d [%.*s]", tok, p->tok.len, p->tok.ptr));
  p->prev_tok = p->tok.tok;
  p->tok.tok = ptranslate(tok);
  return p->tok.tok;
}

const char *baik_typeof(baik_val_t v) {
  return baik_stringify_type(baik_get_type(v));
}

BAIK_PRIVATE const char *baik_stringify_type(enum baik_type t) {
  switch (t) {
    case BAIK_TYPE_NUMBER:
      return "angka";
    case BAIK_TYPE_BOOLEAN:
      return "boolean";
    case BAIK_TYPE_STRING:
      return "huruf";
    case BAIK_TYPE_OBJECT_ARRAY:
      return "untaian";
    case BAIK_TYPE_OBJECT_GENERIC:
      return "objek";
    case BAIK_TYPE_FOREIGN:
      return "foreign_ptr";
    case BAIK_TYPE_OBJECT_FUNCTION:
      return "fungsi";
    case BAIK_TYPE_NULL:
      return "kosong";
    case BAIK_TYPE_UNDEFINED:
      return "takterdefinisi";
    default:
      return "???";
  }
}

void baik_jprintf(baik_val_t v, struct baik *baik, struct json_out *out) {
  if (baik_is_number(v)) {
    double iv, d = baik_get_double(baik, v);
    if (modf(d, &iv) == 0) {
      json_printf(out, "%" INT64_FMT, (int64_t) d);
    } else {
      json_printf(out, "%f", baik_get_double(baik, v));
    }
  } else if (baik_is_boolean(v)) {
    json_printf(out, "%s", baik_get_bool(baik, v) ? "benar" : "salah");
  } else if (baik_is_string(v)) {
    size_t i, size;
    const char *s = baik_get_string(baik, &v, &size);
    for (i = 0; i < size; i++) {
      int ch = ((unsigned char *) s)[i];
      if (isprint(ch)) {
        json_printf(out, "%c", ch);
      } else {
        json_printf(out, "%s%02x", "\\x", ch);
      }
    }
  } else if (baik_is_array(v)) {
    json_printf(out, "%s", "<untaian>");
  } else if (baik_is_object(v)) {
    json_printf(out, "%s", "<objek>");
  } else if (baik_is_foreign(v)) {
    json_printf(out, "%s%lx%s", "<foreign_ptr@",
                (unsigned long) (uintptr_t) baik_get_ptr(baik, v), ">");
  } else if (baik_is_function(v)) {
    json_printf(out, "%s%d%s", "<fungsi@", (int) baik_get_func_addr(v), ">");
  } else if (baik_is_null(v)) {
    json_printf(out, "%s", "kosong");
  } else if (baik_is_undefined(v)) {
    json_printf(out, "%s", "takterdefinisi");
  } else {
    json_printf(out, "%s%" INT64_FMT "%s", "<???", (int64_t) v, ">");
  }
}

void baik_sprintf(baik_val_t v, struct baik *baik, char *buf, size_t n) {
  struct json_out out = JSON_OUT_BUF(buf, n);
  baik_jprintf(v, baik, &out);
}

void baik_fprintf(baik_val_t v, struct baik *baik, FILE *fp) {
  struct json_out out = JSON_OUT_FILE(fp);
  baik_jprintf(v, baik, &out);
}

#if BAIK_ENABLE_DEBUG

BAIK_PRIVATE const char *opcodetostr(uint8_t opcode) {
  static const char *names[] = {
      "NOP", "DROP", "DUP", "SWAP", "JMP", "JMP_TRUE", "JMP_NEUTRAL_TRUE",
      "JMP_FALSE", "JMP_NEUTRAL_FALSE", "FIND_SCOPE", "PUSH_SCOPE", "PUSH_STR",
      "PUSH_TRUE", "PUSH_FALSE", "PUSH_INT", "PUSH_DBL", "PUSH_NULL",
      "PUSH_UNDEF", "PUSH_OBJ", "PUSH_ARRAY", "PUSH_FUNC", "PUSH_THIS", "GET",
      "CREATE", "EXPR", "APPEND", "SET_ARG", "NEW_SCOPE", "DEL_SCOPE", "CALL",
      "RETURN", "LOOP", "BREAK", "CONTINUE", "SETRETVAL", "EXIT", "BCODE_HDR",
      "ARGS", "FOR_IN_NEXT",
  };
  const char *name = "???";
  assert(ARRAY_SIZE(names) == OP_MAX);
  if (opcode < ARRAY_SIZE(names)) name = names[opcode];
  return name;
}

BAIK_PRIVATE size_t baik_disasm_single(const uint8_t *code, size_t i) {
  char buf[40];
  size_t start_i = i;
  size_t llen;
  uint64_t n;

  snprintf(buf, sizeof(buf), "\t%-3u %-8s", (unsigned) i, opcodetostr(code[i]));

  switch (code[i]) {
    case OP_PUSH_FUNC: {
      BAIK_EM_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s %04u", buf, (unsigned) (i - n)));
      i += llen;
      break;
    }
    case OP_PUSH_INT: {
      BAIK_EM_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s\t%lu", buf, (unsigned long) n));
      i += llen;
      break;
    }
    case OP_SET_ARG: {
      size_t llen2;
      uint64_t arg_no;
      BAIK_EM_varint_decode(&code[i + 1], ~0, &arg_no, &llen);
      BAIK_EM_varint_decode(&code[i + llen + 1], ~0, &n, &llen2);
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%.*s] %u", buf, (int) n,
                             code + i + 1 + llen + llen2, (unsigned) arg_no));
      i += llen + llen2 + n;
      break;
    }
    case OP_PUSH_STR:
    case OP_PUSH_DBL: {
      BAIK_EM_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%.*s]", buf, (int) n, code + i + 1 + llen));
      i += llen + n;
      break;
    }
    case OP_JMP:
    case OP_JMP_TRUE:
    case OP_JMP_NEUTRAL_TRUE:
    case OP_JMP_FALSE:
    case OP_JMP_NEUTRAL_FALSE: {
      BAIK_EM_varint_decode(&code[i + 1], ~0, &n, &llen);
      LOG(LL_VERBOSE_DEBUG,
          ("%s\t%u", buf,
           (unsigned) (i + n + llen +
                       1)));
      i += llen;
      break;
    }
    case OP_LOOP: {
      size_t l1, l2;
      uint64_t n1, n2;
      BAIK_EM_varint_decode(&code[i + 1], ~0, &n1, &l1);
      BAIK_EM_varint_decode(&code[i + l1 + 1], ~0, &n2, &l2);
      LOG(LL_VERBOSE_DEBUG,
          ("%s\tB:%lu C:%lu (%d)", buf,
           (unsigned long) (i + 1 + l1 + n1),
           (unsigned long) (i + 1 + l1 + l2 + n2), (int) i));
      i += l1 + l2;
      break;
    }
    case OP_EXPR: {
      int op = code[i + 1];
      const char *name = "???";
     
      switch (op) {
        case TOK_DOT:       name = "."; break;
        case TOK_MINUS:     name = "-"; break;
        case TOK_PLUS:      name = "+"; break;
        case TOK_MUL:       name = "*"; break;
        case TOK_DIV:       name = "/"; break;
        case TOK_REM:       name = "%"; break;
        case TOK_XOR:       name = "^"; break;
        case TOK_AND:       name = "&"; break;
        case TOK_OR:        name = "|"; break;
        case TOK_LSHIFT:    name = "<<"; break;
        case TOK_RSHIFT:    name = ">>"; break;
        case TOK_URSHIFT:   name = ">>>"; break;
        case TOK_UNARY_MINUS:   name = "- (unary)"; break;
        case TOK_UNARY_PLUS:    name = "+ (unary)"; break;
        case TOK_NOT:       name = "!"; break;
        case TOK_TILDA:     name = "~"; break;
        case TOK_EQ:        name = "=="; break;
        case TOK_NE:        name = "!="; break;
        case TOK_EQ_EQ:     name = "==="; break;
        case TOK_NE_NE:     name = "!=="; break;
        case TOK_LT:        name = "<"; break;
        case TOK_GT:        name = ">"; break;
        case TOK_LE:        name = "<="; break;
        case TOK_GE:        name = ">="; break;
        case TOK_ASSIGN:    name = "="; break;
        case TOK_POSTFIX_PLUS:  name = "++ (postfix)"; break;
        case TOK_POSTFIX_MINUS: name = "-- (postfix)"; break;
        case TOK_MINUS_MINUS:   name = "--"; break;
        case TOK_PLUS_PLUS:     name = "++"; break;
        case TOK_LOGICAL_AND:   name = "&&"; break;
        case TOK_LOGICAL_OR:    name = "||"; break;
        case TOK_KEYWORD_TIPE:  name = "tipe"; break;
        case TOK_PLUS_ASSIGN:     name = "+="; break;
        case TOK_MINUS_ASSIGN:    name = "-="; break;
        case TOK_MUL_ASSIGN:      name = "*="; break;
        case TOK_DIV_ASSIGN:      name = "/="; break;
        case TOK_REM_ASSIGN:      name = "%="; break;
        case TOK_XOR_ASSIGN:      name = "^="; break;
        case TOK_AND_ASSIGN:      name = "&="; break;
        case TOK_OR_ASSIGN:       name = "|="; break;
        case TOK_LSHIFT_ASSIGN:   name = "<<="; break;
        case TOK_RSHIFT_ASSIGN:   name = ">>="; break;
        case TOK_URSHIFT_ASSIGN:  name = ">>>="; break;
      }
     
      LOG(LL_VERBOSE_DEBUG, ("%s\t%s", buf, name));
      i++;
      break;
    }
    case OP_BCODE_HEADER: {
      size_t start = 0;
      baik_header_item_t map_offset = 0, total_size = 0;
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + BAIK_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
      i += sizeof(baik_header_item_t) * BAIK_HDR_ITEMS_CNT;
      LOG(LL_VERBOSE_DEBUG, ("%s\t[%s] end:%lu map_offset: %lu", buf,
                             &code[i + 1], (unsigned long) start + total_size,
                             (unsigned long) start + map_offset));
      i += strlen((char *) (code + i + 1)) + 1;
      break;
    }
    default:
      LOG(LL_VERBOSE_DEBUG, ("%s", buf));
      break;
  }
  return i - start_i;
}

void baik_disasm(const uint8_t *code, size_t len) {
  size_t i, start = 0;
  baik_header_item_t map_offset = 0, total_size = 0;

  for (i = 0; i < len; i++) {
    size_t delta = baik_disasm_single(code, i);
    if (code[i] == OP_BCODE_HEADER) {
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + BAIK_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
    }

    i += delta;

    if (map_offset > 0 && i == start + map_offset) {
      i = start + total_size - 1;
      continue;
    }
  }
}

static void baik_dump_obj_stack(const char *name, const struct mbuf *m,
                               struct baik *baik) {
  char buf[50];
  size_t i, n;
  n = baik_stack_size(m);
  LOG(LL_VERBOSE_DEBUG, ("%12s (%d elems): ", name, (int) n));
  for (i = 0; i < n; i++) {
    baik_sprintf(((baik_val_t *) m->buf)[i], baik, buf, sizeof(buf));
    LOG(LL_VERBOSE_DEBUG, ("%34s", buf));
  }
}

void baik_dump(struct baik *baik, int do_disasm) {
  LOG(LL_VERBOSE_DEBUG, ("------- BAIK VM DUMP BEGIN"));
  baik_dump_obj_stack("DATA_STACK", &baik->stack, baik);
  baik_dump_obj_stack("CALL_STACK", &baik->call_stack, baik);
  baik_dump_obj_stack("SCOPES", &baik->scopes, baik);
  baik_dump_obj_stack("LOOP_OFFSETS", &baik->loop_addresses, baik);
  baik_dump_obj_stack("ARG_STACK", &baik->arg_stack, baik);
  if (do_disasm) {
    int parts_cnt = baik_bcode_parts_cnt(baik);
    int i;
    LOG(LL_VERBOSE_DEBUG, ("%23s", "CODE:"));
    for (i = 0; i < parts_cnt; i++) {
      struct baik_bcode_part *bp = baik_bcode_part_get(baik, i);
      baik_disasm((uint8_t *) bp->data.p, bp->data.len);
    }
  }
  LOG(LL_VERBOSE_DEBUG, ("------- BAIK VM DUMP END"));
}

BAIK_PRIVATE int baik_check_arg(struct baik *baik, int arg_num,
                              const char *arg_name, enum baik_type expected_type,
                              baik_val_t *parg) {
  baik_val_t arg = BAIK_UNDEFINED;
  enum baik_type actual_type;

  if (arg_num >= 0) {
    int nargs = baik_nargs(baik);
    if (nargs < arg_num + 1) {
      baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : argumen salah %s", arg_name);
      return 0;
    }

    arg = baik_arg(baik, arg_num);
  } else {
   
    arg = baik->vals.this_obj;
  }

  actual_type = baik_get_type(arg);
  if (actual_type != expected_type) {
    baik_prepend_errorf(baik, BAIK_TYPE_ERROR, "GALAT : %s should be a %s, %s given",
                       arg_name, baik_stringify_type(expected_type),
                       baik_stringify_type(actual_type));
    return 0;
  }

  if (parg != NULL) {
    *parg = arg;
  }

  return 1;
}

BAIK_PRIVATE int baik_normalize_idx(int idx, int size) {
  if (idx < 0) {
    idx = size + idx;
    if (idx < 0) {
      idx = 0;
    }
  }
  if (idx > size) {
    idx = size;
  }
  return idx;
}

BAIK_PRIVATE const char *baik_get_bcode_filename(struct baik *baik,
                                               struct baik_bcode_part *bp) {
  (void) baik;
  return bp->data.p + 1 +
         sizeof(baik_header_item_t) * BAIK_HDR_ITEMS_CNT;
}

const char *baik_get_bcode_filename_by_offset(struct baik *baik, int offset) {
  const char *ret = NULL;
  struct baik_bcode_part *bp = baik_bcode_part_get_by_offset(baik, offset);
  if (bp != NULL) {
    ret = baik_get_bcode_filename(baik, bp);
  }
  return ret;
}

int baik_get_lineno_by_offset(struct baik *baik, int offset) {
  size_t llen;
  uint64_t map_len;
  int prev_line_no, ret = 1;
  struct baik_bcode_part *bp = baik_bcode_part_get_by_offset(baik, offset);
  uint8_t *p, *pe;
  if (bp != NULL) {
    baik_header_item_t map_offset, bcode_offset;
    memcpy(&map_offset, bp->data.p + 1 +
                            sizeof(baik_header_item_t) * BAIK_HDR_ITEM_MAP_OFFSET,
           sizeof(map_offset));

    memcpy(&bcode_offset,
           bp->data.p + 1 +
               sizeof(baik_header_item_t) * BAIK_HDR_ITEM_BCODE_OFFSET,
           sizeof(bcode_offset));

    offset -= (1 + bcode_offset) + bp->start_idx;

   
    p = (uint8_t *) bp->data.p + 1 + map_offset;

    BAIK_EM_varint_decode(p, ~0, &map_len, &llen);
    p += llen;
    pe = p + map_len;

    prev_line_no = 1;
    while (p < pe) {
      uint64_t cur_offset, line_no;
      BAIK_EM_varint_decode(p, ~0, &cur_offset, &llen);
      p += llen;
      BAIK_EM_varint_decode(p, ~0, &line_no, &llen);
      p += llen;

      if (cur_offset >= (uint64_t) offset) {
        ret = prev_line_no;
        break;
      }
      prev_line_no = line_no;
    }
  }
  return ret;
}

int baik_get_offset_by_call_frame_num(struct baik *baik, int cf_num) {
  int ret = -1;
  if (cf_num == 0) {
   
    ret = baik->cur_bcode_offset;
  } else if (cf_num > 0 &&
             baik->call_stack.len >=
                 sizeof(baik_val_t) * CALL_STACK_FRAME_ITEMS_CNT * cf_num) {
   
    int pos = CALL_STACK_FRAME_ITEM_RETURN_ADDR +
              CALL_STACK_FRAME_ITEMS_CNT * (cf_num - 1);
    baik_val_t val = *vptr(&baik->call_stack, -1 - pos);
    ret = baik_get_int(baik, val);
  }
  return ret;
}

#endif
#endif
