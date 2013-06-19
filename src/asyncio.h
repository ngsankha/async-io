#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef ASYNC_IO
#define ASYNC_IO

pthread_t fopen_t(void *(*callback)(FILE *), const char *, const char *);
pthread_t fscanf_t(void *(*callback) (int), FILE *stream, const char *format, ...);
pthread_t fprintf_t(void *(*callback) (int), FILE *stream, const char *format, ...);
pthread_t fclose_t(void *(*callback) (int), FILE *stream);

#endif

