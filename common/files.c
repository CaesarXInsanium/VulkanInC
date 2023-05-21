#include "files.h"
#include <stdio.h>
#include <stdlib.h>

size_t file_size(FILE *fp) {
  if (fp != NULL) {
    if (fseek(fp, 0L, SEEK_END) == 0) {
      size_t bufsize = ftell(fp);
      fseek(fp, 0L, SEEK_SET);
      return bufsize;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}

String *read_file_to_string(FILE *fp) {
  size_t size = file_size(fp);
  char *data = (char *)malloc(size + 1);
  size_t new_len = fread(data, sizeof(char), size, fp);
  if (ferror(fp) != 0) {
    fprintf(stderr, "Error in reading File!\n");
  } else {
    data[new_len++] = '\0';
  }

  String *result = (String *)malloc(sizeof(String));
  result->data = data;
  result->size = size;
  result->capacity = size;
  return result;
}

Bytes *read_bytes(FILE *fp) {
  size_t size = file_size(fp);
  uint8_t *data = (uint8_t *)malloc(size);
  fread(data, sizeof(uint8_t), size, fp);

  if (ferror(fp) != 0) {
    fprintf(stderr, "Error in Reading Bytes\n");
    free(data);
    return NULL;
  } else {
    Bytes *result = (Bytes *)malloc(sizeof(Bytes));
    result->size = size;
    result->bytes = data;
    return result;
  }
}
