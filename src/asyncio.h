#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef ASYNC_IO
#define ASYNC_IO

// using typedef for code simplification

typedef void *(*callback_int)(int);
typedef void *(*callback_file)(FILE *);

pthread_t fopen_t(callback_file,  const char *,  const char *);
pthread_t fscanf_t(callback_int, FILE *stream,  const char *format, ...);
pthread_t fprintf_t(callback_int, FILE *stream,  const char *format, ...);
pthread_t fclose_t(callback_int, FILE *stream);


#endif

