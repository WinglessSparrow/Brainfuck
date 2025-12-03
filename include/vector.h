#ifndef BRAINFUCK_VECTOR_H
#define BRAINFUCK_VECTOR_H
#include <stdio.h>

typedef struct vector {
    char *data;
    size_t size;
    unsigned int curr;
} Vector;

void push(Vector *vector, char *bytes, size_t size);

char *pop(Vector *vector, size_t amount);

void erase(Vector *vector, unsigned int from, unsigned int to);

char *peek(const Vector *vector, unsigned int from, unsigned int to);

Vector *new_v(int size);

void free_v(Vector *vector);

#endif
