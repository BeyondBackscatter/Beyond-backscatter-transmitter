
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void initCircularBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int isCircularBufferEmpty(CircularBuffer *cb) {
    return (cb->count == 0);
}

int isCircularBufferFull(CircularBuffer *cb) {
    return (cb->count == BUFFER_SIZE);
}

void enqueue(CircularBuffer *cb, int data) {
    if (isCircularBufferFull(cb)) {
        printf("Circular buffer is full. Unable to enqueue.\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count++;
}

int dequeue(CircularBuffer *cb) {
    if (isCircularBufferEmpty(cb)) {
        printf("Circular buffer is empty. Unable to dequeue.\n");
        return -1;
    }
    int data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    initCircularBuffer(&cb);

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);

    int value = dequeue(&cb);
    printf("Dequeued value: %d\n", value);

    return 0;
}