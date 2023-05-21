#ifndef FILES_H
#define FILES_H
#include <stdint.h>
#include <stdio.h>
#include "common.h"

// Assumes a Valid File Pointer
size_t file_size(FILE *fp);
String *read_file_to_string(FILE *fp);
Bytes *read_bytes(FILE *fp);

#endif
