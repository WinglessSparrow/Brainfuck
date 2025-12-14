//
// Created by pavel on 14.12.2025.
//

#ifndef BRAINFUCK_VECTOR_2_H
#define BRAINFUCK_VECTOR_2_H

#include <stdio.h>

typedef struct vector {
    void* data;
    size_t typeSize;
    size_t size;
    unsigned int curr;
} Vector;

void push(Vector* vector, const void* items, size_t size);

void* pop(Vector* vector, size_t amount);

void erase(Vector* vector, unsigned int from, unsigned int to);

void* peek(const Vector* vector, unsigned int from, unsigned int to);

void write(Vector* vector, void* src, unsigned int from, size_t size);

Vector* new_v(unsigned int size, size_t typeSize);

void free_v(Vector* vector);

int calcExpandFactor(const Vector* vector, size_t addSize);

void expand(Vector* vector, int factor);

bool needsShrink(const Vector* vector);

void shrink(Vector* vector);

#endif //BRAINFUCK_VECTOR_2_H
