#ifndef BRNFCKINTERPRETER_POINTERSPACE_H
#define BRNFCKINTERPRETER_POINTERSPACE_H

#include "vector.h"

typedef struct pointerSpace {
    unsigned int pointingTo;
    char *arr;
    int size;
} PointerSpace;

typedef enum moveDirection {
    FORWARDS, BACKWARDS,
} MoveDirection;

PointerSpace new_ps();

void move(PointerSpace *pSpace, MoveDirection direction);

void inc(const PointerSpace *pSpace);

void dec(const PointerSpace *pSpace);

void write(const PointerSpace *pSpace, char byte);

char read(const PointerSpace *pSpace);

#endif //BRNFCKINTERPRETER_POINTERSPACE_H
