//
// Created by pavel on 14.12.2025.
//

#include "../include/vector_2.h"

#include <stdlib.h>
#include <string.h>

Vector* new_v(const unsigned int size, const size_t typeSize) {
    Vector* vector = malloc(sizeof(Vector));

    vector->size = size;
    vector->typeSize = typeSize;
    vector->curr = 0;
    vector->data = calloc(vector->size, vector->typeSize);

    return vector;
}

void free_v(Vector* vector) {
    free(vector->data);
    free(vector);
}

bool needsShrink(const Vector* vector) {
    return vector->curr < vector->size / 2;
}

void shrink(Vector* vector) {
    if (!needsShrink(vector)) return;

    vector->size = vector->size / 2;

    void* newMem = calloc(vector->size, vector->typeSize);

    memcpy(newMem, vector->data, vector->curr * vector->typeSize);

    free(vector->data);

    vector->data = newMem;
}

void* pop(Vector* vector, const size_t amount) {
    if (vector->curr < amount) {
        printf("trying to read more than available");
        exit(-1);
    }

    const size_t buffSize = amount * vector->typeSize;
    void* buff = malloc(buffSize);

    memcpy(buff, vector->data - buffSize, buffSize);

    vector->curr -= amount;

    shrink(vector);

    return buff;
}

int calcExpandFactor(const Vector* vector, const size_t addSize) {
    int factor = 1;

    if (vector->curr + addSize > vector->size) {
        while (vector->curr + addSize > vector->size * factor) {
            factor *= 2;
        }
    }

    return factor;
}

void expand(Vector* vector, const int factor) {
    if (factor <= 1) return;

    vector->size *= factor;

    void* newMem = calloc(vector->size, vector->typeSize);

    memcpy(newMem, vector->data, vector->curr * vector->typeSize);

    free(vector->data);

    vector->data = newMem;
}

void push(Vector* vector, const void* items, const size_t size) {
    expand(vector, calcExpandFactor(vector, size));

    memcpy(vector->data + vector->curr, items, size * vector->typeSize);

    vector->curr += size;
}

void* peek(const Vector* vector, const unsigned int from, const unsigned int to) {
    const size_t size = to - from;

    if (vector->curr < to) {
        printf("Out of bounds Peek attempt");
        exit(0);
    }

    void* buff = malloc(size * vector->typeSize);

    memcpy(buff, vector->data + from * vector->typeSize, size * vector->typeSize);

    return buff;
}

void erase(Vector* vector, const unsigned int from, const unsigned int to) {
    if (vector->curr < to) {
        printf("Out of bounds Erase attempt (max: %d, trying from: %d to: %d)", vector->curr, from, to);
    }

    const unsigned int adjustedFrom = from * vector->typeSize;
    const unsigned int adjustedTo = to * vector->typeSize;

    for (unsigned int i = 0; i < vector->curr - adjustedFrom; i++) {
        ((char*) vector->data)[adjustedFrom + i] = ((char*) vector->data)[adjustedTo + i];
    }

    vector->curr = vector->curr - (to - from);

    shrink(vector);
}

void write(Vector* vector, void* src, const unsigned int from, const size_t size) {
    const size_t overflow = from + size - vector->curr;

    if (overflow > 0) {
        expand(vector, calcExpandFactor(vector, overflow));

        vector->curr += overflow;
    }

    for (unsigned int i = 0; i < size * vector->typeSize; i++) {
        ((char*) vector->data)[i + from * vector->typeSize] = ((char*) src)[i];
    }
}
