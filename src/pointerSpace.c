#include "../include/pointerSpace.h"

#include <stdlib.h>

void fillNewSpace(const PointerSpace* pSpace, const int prevSize) {
    for (int i = prevSize; i < pSpace->size; i++) {
        pSpace->arr[i] = 0;
    }
}

PointerSpace new_ps() {
    const PointerSpace pSpace = {
        .pointingTo = 0,
        .arr = malloc(1024),
        .size = 1024,
    };

    fillNewSpace(&pSpace, 0);

    return pSpace;
}

void expandArray(PointerSpace* pSpace) {
    const int prevSize = pSpace->size;

    while (pSpace->pointingTo >= pSpace->size) {
        pSpace->size *= 2;
    }

    // ReSharper disable once CppDFAMemoryLeak
    char* tmp = realloc(pSpace->arr, pSpace->size);

    if (tmp == NULL) {
        printf("not enough memory to relocate\n");
        exit(1);
    }
    if (pSpace->arr != tmp) {
        pSpace->arr = tmp;
    }

    fillNewSpace(pSpace, prevSize);
}

void move(PointerSpace* pSpace, const MoveDirection direction) {
    switch (direction) {
        case FORWARDS:
            pSpace->pointingTo++;
            if (pSpace->pointingTo >= pSpace->size) {
                expandArray(pSpace);
            }
            break;
        case BACKWARDS:
            pSpace->pointingTo--;
            break;
    }
}

void inc(const PointerSpace* pSpace) {
    pSpace->arr[pSpace->pointingTo]++;
}

void dec(const PointerSpace* pSpace) {
    pSpace->arr[pSpace->pointingTo]--;
}

void write(const PointerSpace* pSpace, const char byte) {
    pSpace->arr[pSpace->pointingTo] = byte;
}

char read(const PointerSpace* pSpace) {
    return pSpace->arr[pSpace->pointingTo];
}
