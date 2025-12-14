//
// Created by pavel on 03.12.2025.
//

#include "../include/fileReader.h"

#include <string.h>

const char* getFileName(const char* filePath) {
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

bool isBrainfuckFile(const char* fileName) {
    const size_t lng = strlen(fileName);

    if (lng > 2) {
        return strcmp(".b", &fileName[lng - 3]) != 0 || strcmp(".bf", &fileName[lng - 4]) != 0;
    }

    return false;
}
