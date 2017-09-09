#include "asyncio.h"

typedef struct fopen_struct {
    char *filename;
    char *mode;
    callback_file cb_file;
} fopen_struct;

typedef struct frw_struct {
    FILE *stream;
    char *format;
    va_list list;
    callback_int cb_int;
} frw_struct;

typedef struct fclose_struct {
    FILE *stream;
    callback_int cb_int;
} fclose_struct;

void *__fclose_t__(fclose_struct *);
void *__fopen_t__(fopen_struct *);
void *__fscanf_t__(frw_struct *);
void *__fprintf_t__(frw_struct *);

pthread_t fopen_t(callback_file cb_file, const char *filename,  const char *mode) {
    fopen_struct *args = (fopen_struct*) malloc(sizeof(fopen_struct));
    args -> filename = filename;
    args -> mode = mode;
    args -> cb_file = cb_file;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fopen_t__, args);
    return thread;
}

void *__fopen_t__(fopen_struct *ptr) {
    fopen_struct *args = (fopen_struct *)ptr;
    FILE *result = fopen(args -> filename, args -> mode);
    args -> cb_file(result);
    free(args);
}

pthread_t fclose_t(callback_int cb_int, FILE *stream) {
    fclose_struct *args = (fclose_struct*) malloc(sizeof(fclose_struct));
    args -> stream = stream;
    args -> cb_int = cb_int;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fclose_t__, args);
    return thread;
}

void *__fclose_t__(fclose_struct *ptr) {
    fclose_struct *args = (fclose_struct *)ptr;
    int result = fclose(args -> stream);
    args -> cb_int(result);
    free(args);
}

pthread_t fscanf_t(callback_int cb_int, FILE *stream, const char *format, ...) {
    frw_struct *args = (frw_struct*) malloc(sizeof(frw_struct));
    va_list arguments;
    va_start(arguments, *format);
    args -> stream = stream;
    args -> cb_int = cb_int;
    args -> list = arguments;
    args -> format = format;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fscanf_t__, args);
    va_end(arguments);
    return thread;
}

void *__fscanf_t__(frw_struct *ptr) {
    frw_struct *args = (frw_struct *)ptr;
    int result = vfscanf(args -> stream, args -> format, args -> list);
    args -> cb_int(result);
    free(args);
}

pthread_t fprintf_t(callback_int cb_int, FILE *stream,  const char *format, ...) {
    frw_struct *args = (frw_struct*) malloc(sizeof(frw_struct));
    va_list arguments;
    va_start(arguments, *format);
    args -> stream = stream;
    args -> cb_int = cb_int;
    args -> list = arguments;
    args -> format = format;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fprintf_t__, args);
    va_end(arguments);
    return thread;
}

void *__fprintf_t__(frw_struct *ptr) {
    frw_struct *args = (frw_struct *)ptr;
    int result = vfprintf(args -> stream, args -> format, args -> list);
    args -> cb_int(result);
    free(args);
}

