#include <stdlib.h>
#include <string.h>

// #include "include/commandsSpace.h"
// #include "include/runner.h"
// #include "include/pointerSpace.h"
#include "include/vector_2.h"

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

/*
*        src/vector.c
src/commandsSpace.c
include/commandsSpace.h
include/pointerSpace.h
include/vector.h
src/runner.c
include/runner.h
src/pointerSpace.c
src/fileReader.c
include/fileReader.h
*/

int main(int argc, char** argv) {
    Vector* vector = new_v(8, 4);

    const int b[] = {10, 20, 30, 40, 5, 6, 7, 8, 9, 10, 11};

    push(vector, b, 11);

    const int* ptr = (int*) peek(vector, 2, 7);

    for (int i = 0; i < 5; i++) {
        printf("%d, ", ptr[i]);
    }

    printf("\n");

    for (int i = 0; i < vector->curr; i++) {
        printf("%d, ", ((int*) vector->data)[i]);
    }

    erase(vector, 2, 7);

    printf("\n");

    for (int i = 0; i < vector->curr; i++) {
        printf("%d, ", ((int*) vector->data)[i]);
    }

    printf("\n");

    const int c[] = {69, 69, 69, 69, 88};

    write(vector, (void*) c, 3, 5);

    for (int i = 0; i < vector->curr; i++) {
        printf("%d, ", ((int*) vector->data)[i]);
    }

    // if (argc > 2) {
    //     printf_s("Wrong number of arguments: %d \n", argc);
    //     return 1;
    // }
    //
    // const char *filePath = argv[1];
    // char *fileName = getFileName(filePath);
    // FILE *file = fopen(filePath, "r");
    //
    // if (file == NULL) {
    //     printf_s("File not found on the following path: \"%s\"\n", filePath);
    //     return 2;
    // }
    //
    // const CommandSpace commandSpace = initCommandSpace(file, fileName);
    //
    // const PointerSpace pointerSpace = new_ps();
    //
    // interpret(commandSpace, pointerSpace);
    //
    // free(fileName);

    return 0;
}
