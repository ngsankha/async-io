#include "asyncio.h"

typedef struct fopen_struct {
    char *filename;
    char *mode;
    void *(*callback) (FILE *);
} fopen_struct;

typedef struct frw_struct {
    FILE *stream;
    char *format;
    va_list list;
    void (*callback) (int);
} frw_struct;

typedef struct fclose_struct {
    FILE *stream;
    void *(*callback) (int);
} fclose_struct;

void *__fclose_t__(fclose_struct *);
void *__fopen_t__(fopen_struct *);
void *__fscanf_t__(frw_struct *);
void *__fprintf_t__(frw_struct *);

pthread_t fopen_t(void *(*callback)(FILE *),  char *filename,  char *mode) {
    fopen_struct *args = (fopen_struct*) malloc(sizeof(fopen_struct));
    args -> filename = filename;
    args -> mode = mode;
    args -> callback = callback;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fopen_t__, args);
    return thread;
}

void *__fopen_t__(fopen_struct *ptr) {
    fopen_struct *args = (fopen_struct *)ptr;
    FILE *result = fopen(args -> filename, args -> mode);
    args -> callback(result);
    free(args);
}

pthread_t fclose_t(void *(*callback)(int), FILE *stream) {
    fclose_struct *args = (fclose_struct*) malloc(sizeof(fclose_struct));
    args -> stream = stream;
    args -> callback = callback;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fclose_t__, args);
    return thread;
}

void *__fclose_t__(fclose_struct *ptr) {
    fclose_struct *args = (fclose_struct *)ptr;
    int result = fclose(args -> stream);
    args -> callback(result);
    free(args);
}

pthread_t fscanf_t(void *(*callback)(int), FILE *stream,  char *format, ...) {
    frw_struct *args = (frw_struct*) malloc(sizeof(frw_struct));
    va_list arguments;
    va_start(arguments, *format);
    args -> stream = stream;
    args -> callback = callback;
    args -> list = arguments;
    args -> format = format;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fscanf_t__, args);
    return thread;
}

void *__fscanf_t__(frw_struct *ptr) {
    frw_struct *args = (frw_struct *)ptr;
    int result = vfscanf(args -> stream, args -> format, args -> list);
    args -> callback(result);
    free(args);
}

pthread_t fprintf_t(void *(*callback)(int), FILE *stream,  char *format, ...) {
    frw_struct *args = (frw_struct*) malloc(sizeof(frw_struct));
    va_list arguments;
    va_start(arguments, *format);
    args -> stream = stream;
    args -> callback = callback;
    args -> list = arguments;
    args -> format = format;
    pthread_t thread;
    pthread_create(&thread, NULL, &__fprintf_t__, args);
    return thread;
}

void *__fprintf_t__(frw_struct *ptr) {
    frw_struct *args = (frw_struct *)ptr;
    int result = vfprintf(args -> stream, args -> format, args -> list);
    args -> callback(result);
    free(args);
}

