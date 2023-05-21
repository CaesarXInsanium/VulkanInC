#include "lve_window.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "common/common.h"

int LveWindow_init(LveWindow **self, int h, int w, const char *name) {
  LveWindow *lve_window = (LveWindow *)malloc(sizeof(LveWindow));
  lve_window->width = w;
  lve_window->height = h;
  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  lve_window->window = glfwCreateWindow(w, h, name, NULL, NULL);
  lve_window->name = name;

  *self = lve_window;
  return EXIT_SUCCESS;
}

int LveWindow_destroy(LveWindow *self) {
  glfwDestroyWindow(self->window);
  glfwTerminate();
  free(self);
  return EXIT_SUCCESS;
}

void LveWindow_createSurface(LveWindow *self, VkInstance instance,
                             VkSurfaceKHR *surface) {
  PANIC_ASSERT("Failed to Create VulkanSurface",
        glfwCreateWindowSurface(instance, self->window, NULL, surface));
}
int LveWindow_shouldClose(LveWindow *self) {
  return glfwWindowShouldClose(self->window);
}
