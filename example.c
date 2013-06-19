#include "src/asyncio.h"

void fopen_callback(FILE *);
void fprintf_callback(int);

int main() {
    pthread_t thread = fopen_t(&fopen_callback, "test.txt", "w");
    pthread_join(thread, NULL);
}

void fopen_callback(FILE *stream) {
    if (stream != NULL) {
        printf("File Opened\n");
        pthread_t thread = fprintf_t(&fprintf_callback, stream, "%s", "Hello World!\n");
        // do any other longer tasks here
        // in case all other tasks have finished wait for the I/O to complete
        pthread_join(thread, NULL);
    } else
        printf("Error\n");
}

void fprintf_callback(int result) {
    if (result > 0) {
        printf("File Written\n");
    } else
        printf("Error\n");
}

