//
// Created by pavel on 30.11.2025.
//

#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>

void initAllocatedSpace(const Vector *vector) {
    for (size_t i = vector->curr; i < vector->size; i++) {
        vector->data[i] = 0;
    }
}

Vector *new_v(const int size) {
    Vector *vector = malloc(sizeof(Vector));

    vector->size = size;
    vector->curr = 0;
    vector->data = malloc(vector->size);

    initAllocatedSpace(vector);

    return vector;
}

void free_v(Vector *vector) {
    free(vector->data);
    free(vector);
}

void push(Vector *vector, char *bytes, size_t size) {
    if (vector->curr + size > vector->size) {
        while (vector->curr + size > vector->size) {
            vector->size *= 2;
        }

        // ReSharper disable once CppDFAMemoryLeak
        char *dataTmp = realloc(vector->data, vector->size);

        if (dataTmp == NULL) {
            printf("not enough memory to relocate\n");
            exit(0);
        }
        if (vector->data != dataTmp) {
            vector->data = dataTmp;
        }

        initAllocatedSpace(vector);
    }

    memcpy(vector->data + vector->curr, bytes, size);

    vector->curr += size;
}

char *pop(Vector *vector, const size_t amount) {
    if (vector->curr < amount) {
        printf("trying to read more bytes than available");
        exit(0);
    }

    char *buff = malloc(vector->curr);

    int count = 0;

    for (unsigned int i = vector->curr - amount - 1; i < vector->curr; i++) {
        buff[count] = vector->data[i];
        count++;
    }

    vector->curr -= amount;

    return buff;
}

char *peek(const Vector *vector, const unsigned int from, const unsigned int to) {
    const size_t size = to - from;

    if (vector->curr < to) {
        printf("Out of bounds Peek attempt");
        exit(0);
    }

    char *buff = malloc(size);

    memcpy(buff, vector->data + from, size);

    return buff;
}

void erase(Vector *vector, const unsigned int from, const unsigned int to) {
    if (vector->curr < to) {
        printf("Out of bounds Erase attempt");
    }

    for (unsigned int i = 0; i < vector->curr - from; i++) {
        vector->data[from + i] = vector->data[to + i];
    }

    vector->curr = vector->curr - (to - from);

    initAllocatedSpace(vector);
}
