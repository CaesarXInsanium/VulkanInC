#ifndef LVE_WINDOW_H
#define LVE_WINDOW_H

#include <stdint.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef struct LveWindow_ {
  GLFWwindow *window;
  int width;
  int height;
  // null terminate pointer
  const char *name;
} LveWindow;

int LveWindow_init(LveWindow **self, int h, int w, const char *name);
int LveWindow_destroy(LveWindow *self);

int LveWindow_shouldClose(LveWindow *self);

#endif
