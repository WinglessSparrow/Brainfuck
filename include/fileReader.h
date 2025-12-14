#ifndef BRAINFUCK_FILEREADER_H
#define BRAINFUCK_FILEREADER_H

#include <stdlib.h>

#include "vector.h"

const size_t readFile(const FILE* file, const Vector* data);

const char* getFileName(const char* filePath);

bool isBrainfuckFile(const char* fileName);

#endif
