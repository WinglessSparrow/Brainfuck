#include "../include/commandsSpace.h"

#include <stdlib.h>
#include <string.h>

#include "../include/vector.h"

size_t readFile(FILE *file, Vector *vector) {
    size_t sumBytesRead = 0;
    size_t lastRead = 0;
    char readBuff[1024];

    do {
        lastRead = fread(readBuff, sizeof(unsigned char), 100, file);
        sumBytesRead += lastRead;

        push(vector, readBuff, lastRead);
    } while (lastRead != 0);

    return sumBytesRead;
}

CommandSpace initCommandSpace(FILE *file, const char *fileName) {
    CommandSpace commandSpace = {
        .programPointer = 0,
        .commands = nullptr,
        .size = 0,
        .jumpLinks = nullptr,
        .jumpLinksSize = 0,
        .programName = fileName,
        .programNameSize = strlen(fileName),
    };

    Vector *vector = new_v(1024);

    size_t bytesRead = readFile(file, vector);

    bytesRead -= stripProgram(vector);

    commandSpace.size = bytesRead;
    commandSpace.commands = malloc(sizeof(Command) * commandSpace.size);

    memcpy(commandSpace.commands, vector->data, bytesRead);

    free_v(vector);

    linkJumps(&commandSpace);

    return commandSpace;
}

int stripProgram(Vector *vector) {
    int from = -1;
    int ammErased = 0;

    for (int i = 0; i < vector->curr; i++) {
        switch ((Command) vector->data[i]) {
            case POINTER_INC:
            case POINTER_DEC:
            case DATA_INC:
            case DATA_DEC:
            case DATA_IN:
            case DATA_OUT:
            case JUMP_FROM:
            case JUMP_TO:
                if (from != -1) {
                    erase(vector, from, i);

                    ammErased += i - from;

                    i = from;
                    from = -1;
                }
                break;
            default:
                if (from == -1) {
                    from = i;
                }
                break;
        }
    }

    return ammErased;
}

int validateParenthesisPairs(const CommandSpace *commandSpace) {
    int ammJumpFrom = 0;
    int ammJumpTo = 0;

    for (int i = 0; i < commandSpace->size; i++) {
        if (commandSpace->commands[i] == JUMP_FROM) {
            ammJumpFrom++;
        }
        if (commandSpace->commands[i] == JUMP_TO) {
            ammJumpTo++;
        }
    }

    if (ammJumpFrom != ammJumpTo) {
        printf("not all the [ have a corresponding ]");
        exit(0);
    }

    return ammJumpFrom;
}

void linkJumps(CommandSpace *commandSpace) {
    commandSpace->jumpLinksSize = validateParenthesisPairs(commandSpace);
    commandSpace->jumpLinks = malloc(sizeof(JumpLink) * commandSpace->jumpLinksSize);
    int linksPointer = 0;

    JumpLink *stack = malloc(sizeof(JumpLink) * commandSpace->jumpLinksSize);
    int stackPointer = 0;

    for (int i = 0; i < commandSpace->size; i++) {
        if (commandSpace->commands[i] == JUMP_FROM) {
            stack[stackPointer].from = i;
            stackPointer++;
        }
        if (commandSpace->commands[i] == JUMP_TO) {
            JumpLink link = stack[stackPointer - 1];
            link.to = i;
            stackPointer--;

            commandSpace->jumpLinks[linksPointer] = link;
            linksPointer++;
        }
    }
}

int getJumpIdx(const CommandSpace *commandSpace, JumpDirection jumpDirection) {
    const unsigned int programPointer = commandSpace->programPointer;
    const JumpLink *links = commandSpace->jumpLinks;
    int idx = 0;

    if (commandSpace->commands[programPointer] != JUMP_FROM &&
        commandSpace->commands[programPointer] != JUMP_TO
    ) {
        printf("the programPointer is not pointing to a [ or ]");
        exit(-1);
    }

    if (jumpDirection == JUMP_FORWARDS) {
        while (links[idx].from != commandSpace->programPointer) {
            idx++;
        }

        return links[idx].to;
    }

    while (links[idx].to != commandSpace->programPointer) {
        idx++;
    }

    return links[idx].from;
}
