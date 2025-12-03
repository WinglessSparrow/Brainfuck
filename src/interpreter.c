#include "../include/interpreter.h"
#include "../include/pointerSpace.h"

void interpret(CommandSpace commandsSpace, PointerSpace pointerSpace) {
    while (commandsSpace.programPointer < commandsSpace.size) {
        const Command command = commandsSpace.commands[commandsSpace.programPointer];

        switch (command) {
            case POINTER_INC:
                move(&pointerSpace, FORWARDS);
                break;
            case POINTER_DEC:
                move(&pointerSpace, BACKWARDS);
                break;
            case DATA_INC:
                inc(&pointerSpace);
                break;
            case DATA_DEC:
                dec(&pointerSpace);
                break;
            case DATA_IN:
                write(&pointerSpace, (char) getchar());
                break;
            case DATA_OUT:
                putchar(read(&pointerSpace));
                break;
            case JUMP_FROM:
                if (pointerSpace.arr[pointerSpace.pointingTo] == 0) {
                    commandsSpace.programPointer = getJumpIdx(&commandsSpace, JUMP_FORWARDS);
                }
                break;
            case JUMP_TO:
                if (pointerSpace.arr[pointerSpace.pointingTo] != 0) {
                    commandsSpace.programPointer = getJumpIdx(&commandsSpace, JUMP_BACKWARDS);
                }
                break;
        }

        commandsSpace.programPointer++;
    }
}
