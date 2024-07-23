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
  result.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
  result.pEngineName = "LveEngine";
  result.engineVersion = VK_MAKE_VERSION(0, 0, 1);
  result.apiVersion = VK_API_VERSION_1_0;
  result.pNext = NULL;
  return result;
}
VkInstanceCreateInfo vkinstanceinfo(VkApplicationInfo *info) {
  VkInstanceCreateInfo result;
  memset(&result, 0, sizeof(VkInstanceCreateInfo));
  result.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  result.pApplicationInfo = info;

  uint32_t glfw_extension_count = 0;
  const char **glfw_extensions;
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  result.enabledExtensionCount = glfw_extension_count;
  result.ppEnabledExtensionNames = glfw_extensions;
  result.enabledLayerCount = 0;
  result.ppEnabledLayerNames = NULL;
  result.pNext = NULL;
  return result;
}

LvePipeline *LvePipeline_new(const char *vert_path, const char *frag_path) {
  LvePipeline *pipeline = (LvePipeline *)malloc(sizeof(LvePipeline));

  // Creating Instance
  VkApplicationInfo app_info = vkappinfo("LveEngine");
  VkInstanceCreateInfo createinfo = vkinstanceinfo(&app_info);
  VkInstance instance;
  VkResult result = vkCreateInstance(&createinfo, NULL, &instance);
  PANIC_ASSERT("Failed to Create Instance.", result == VK_SUCCESS);
  puts("Created Instance");
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
