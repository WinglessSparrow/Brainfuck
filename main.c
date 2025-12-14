#include <stdlib.h>
#include <string.h>

#include "include/commandsSpace.h"
#include "include/fileReader.h"
#include "include/runner.h"
#include "include/pointerSpace.h"
#include "include/vector.h"

int main(const int argc, char** argv) {
    if (argc > 2) {
        printf_s("Wrong number of arguments: %d \n", argc);
        return 1;
    }

    const char* filePath = argv[1];
    const char* fileName = getFileName(filePath);

    if (!isBrainfuckFile(fileName)) {
        printf("Incorrect file extension (.b | .bf)");
        return 1;
    }

    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        printf_s("File not found on the following path: \"%s\"\n", filePath);
        return 1;
    }

    const CommandSpace commandSpace = initCommandSpace(file, fileName);

    const PointerSpace pointerSpace = new_ps();

    interpret(commandSpace, pointerSpace);

    return 0;
}
