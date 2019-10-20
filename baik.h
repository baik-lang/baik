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
#ifndef BAIK_EXPORT_INTERNAL_HEADERS
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

#ifndef BAIK_OBJECT_PUBLIC_H_
#define BAIK_OBJECT_PUBLIC_H_

#include <stddef.h>

#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>

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
#endif
