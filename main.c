#include <stdlib.h>
#include <string.h>

#include "include/commandsSpace.h"
#include "include/runner.h"
#include "include/pointerSpace.h"
#include "include/vector.h"

char* getFileName(const char* filePath) {
    const size_t lng = strlen(filePath);
    size_t nameLng = 0;
    size_t startsAt = 0;

    for (size_t i = lng - 1; i >= 1; i--) {
        if (filePath[i] == '/') {
            startsAt = i;
            nameLng = lng - i;
            break;
        }
    }

    char* fileName = malloc((nameLng + 1) * sizeof(unsigned char));

    strncpy(fileName, filePath + startsAt + 1, nameLng);

    return fileName;
}

int main(int argc, char** argv) {
    if (argc > 2) {
        printf_s("Wrong number of arguments: %d \n", argc);
        return 1;
    }

    const char* filePath = argv[1];
    char* fileName = getFileName(filePath);
    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        printf_s("File not found on the following path: \"%s\"\n", filePath);
        return 2;
    }

    const CommandSpace commandSpace = initCommandSpace(file, fileName);

    const PointerSpace pointerSpace = new_ps();

    interpret(commandSpace, pointerSpace);

    free(fileName);

    return 0;
}
