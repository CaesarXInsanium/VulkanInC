#ifndef COMMON_H
#define COMMON_H

// this file will mostly define structs
#include <stddef.h>
#include <stdint.h>

typedef struct String {
  size_t size;
  size_t capacity;
  char *data;
} String;

typedef struct Bytes {
  size_t size;
  uint8_t *bytes;
} Bytes;

typedef struct ArrayList {
  size_t capacity;
  size_t length;
  size_t data_size;
  void *data;
} ArrayList;

// if expression is false then program will crash
void PANIC_ASSERT(const char *message, int expression);
void PANIC(const char *message);
#define PRINT_POINTER(pointer) (printf("Pointer: %p\n",(void *)pointer))

#endif
