#include "common/common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PANIC_ASSERT(const char *message, int expression) {
  if (!expression) {
    fputs(message, stderr);
    exit(EXIT_FAILURE);
  }
}
