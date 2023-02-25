#include "lve/lve_app.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  App app = App_new(800, 600, "LveApp");
  App_run(app);
  return EXIT_SUCCESS;
}
