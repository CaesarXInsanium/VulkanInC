#include "lve_app.h"
#include "lve_window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

App App_new(const int w, const int h, const char *name) {
  LveWindow *window = NULL;
  int win_status = LveWindow_init(&window, w, h, name);
  if (win_status == EXIT_FAILURE) {
    printf("Failed to Start Window!\n");
  }
  App result = {.width = w, .height = h, .window = window};
  return result;
}
int App_run(App app) {
  printf("Window Pointer: %p\n", (void *)app.window);
  while (!LveWindow_shouldClose(app.window)) {
    glfwPollEvents();
  }
  return EXIT_SUCCESS;
}
