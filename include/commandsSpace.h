#ifndef BRNFCKINTERPRETER_COMMANDS_H
#define BRNFCKINTERPRETER_COMMANDS_H
#include <stdio.h>

#include "vector.h"

typedef enum command: char {
    POINTER_INC = '>',
    POINTER_DEC = '<',
    DATA_INC = '+',
    DATA_DEC = '-',
    DATA_IN = ',',
    DATA_OUT = '.',
    JUMP_FROM = '[',
    JUMP_TO = ']'
} Command;

typedef struct jumpLink {
    int from;
    int to;
} JumpLink;

typedef enum jumpDirection {
    JUMP_FORWARDS, JUMP_BACKWARDS,
} JumpDirection;

typedef struct commandSpace {
    unsigned int programPointer;
    Command *commands;
    size_t size;
    JumpLink *jumpLinks;
    int jumpLinksSize;
    const char *programName;
    const size_t programNameSize;
} CommandSpace;


CommandSpace initCommandSpace(FILE *file, const char *fileName);

int stripProgram(Vector *vector);

void linkJumps(CommandSpace *commandSpace);

int getJumpIdx(const CommandSpace *commandSpace, JumpDirection jumpDirection);

#endif
