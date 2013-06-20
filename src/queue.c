#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct queue {
    int capacity;
    int size;
    int front;
    int rear;
    pthread_t *elements;
} queue;

queue *create_queue(int maxElements) {
    queue *q = (queue *)malloc(sizeof(queue));
    q -> elements = (int *)malloc(sizeof(pthread_t) * maxElements);
    q -> size = 0;
    q -> capacity = 0;
    q -> front = 0;
    q -> rear = -1;
    return q;
}

void dequeue(queue *q) {
    if (q -> size != 0) {
        q -> size--;
        q -> front++;
        if (q -> front == q -> capacity)
            q -> front = 0;
    }
}

pthread_t front(queue *q) {
    if (q -> size != 0)
        return q -> elements[q -> front];
}

void enqueue(queue *q, pthread_t element) {
    if (q -> size == q -> capacity)
        q -> capacity++;
    else {
        q -> size++;
        q -> rear = q -> rear + 1;
        if (q -> rear == q -> capacity)
            q -> rear = 0;
        q -> elements[q -> rear] = element;
    }
}

