#include "lve_pipeline.h"
#include "common/files.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

VkApplicationInfo vkappinfo(const char *name) {
  VkApplicationInfo result;
  result.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  result.pApplicationName = name;
  result.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  result.pEngineName = "LveEngine";
  result.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  result.apiVersion = VK_API_VERSION_1_0;
  return result;
}
VkInstanceCreateInfo vkinstanceinfo(const char *app_name) {
  VkInstanceCreateInfo result;
  result.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  VkApplicationInfo info = vkappinfo(app_name);
  result.pApplicationInfo = &info;

  uint32_t glfw_extension_count = 0;
  const char **glfw_extensions;
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  result.enabledExtensionCount = glfw_extension_count;
  result.ppEnabledLayerNames = glfw_extensions;
  result.enabledLayerCount = 0;
  return result;
}

LvePipeline *LvePipeline_new(const char *vert_path, const char *frag_path) {
  LvePipeline *pipeline = (LvePipeline *)malloc(sizeof(LvePipeline));

  // Creating Instance
  VkInstanceCreateInfo createinfo = vkinstanceinfo("LveEngine");
  VkInstance instance;
  VkResult result = vkCreateInstance(&createinfo, NULL, &instance);
  PANIC_ASSERT("Failed to Create Instance.", result == VK_SUCCESS);

  // Load Shader Binary
  FILE *vert_fp = fopen(vert_path, "rb");
  FILE *frag_fp = fopen(frag_path, "rb");
  PANIC_ASSERT("Shader binaries are not found",
        (vert_fp != NULL) && (frag_fp != NULL));
  Bytes *vertex_binary = read_bytes(vert_fp);
  Bytes *frag_binary = read_bytes(frag_fp);
  PRINT_POINTER(vertex_binary);
  printf("Vertex Size: %d\n", (int)vertex_binary->size);
  PRINT_POINTER(frag_binary);
  printf("Frag Size: %d\n", (int)frag_binary->size);

  pipeline->instance = instance;
  return pipeline;
}

void LvePipeline_destroy(LvePipeline *self){
  vkDestroyInstance(self->instance, NULL);
  free(self);
}
