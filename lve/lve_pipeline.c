#include "lve_pipeline.h"
#include "common/common.h"
#include "common/files.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <vulkan/vulkan.h>

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
  VkResult instance_result = vkCreateInstance(&createinfo, NULL, &instance);
  PANIC_ASSERT("Failed to Create Instance.", instance_result == VK_SUCCESS);
  puts("Created Instance");

  // Load Shader Binary
  FILE *vert_fp = fopen(vert_path, "rb");
  FILE *frag_fp = fopen(frag_path, "rb");
  PANIC_ASSERT("Shader binaries are not found",
        (vert_fp != NULL) && (frag_fp != NULL));
  Bytes *vertex_binary = read_bytes(vert_fp);
  Bytes *frag_binary = read_bytes(frag_fp);
  PRINT_POINTER(vertex_binary);
  printf("Vertex Size: %u\n", (unsigned int)vertex_binary->size);
  PRINT_POINTER(frag_binary);
  printf("Frag Size: %u\n", (unsigned int)frag_binary->size);

  // Query Physical Devices
  uint32_t physical_device_count = 0;
  vkEnumeratePhysicalDevices(instance, &physical_device_count , NULL);
  printf("There are %u GPUS on this computer\n", physical_device_count);
  VkPhysicalDevice *physical_devices = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * physical_device_count);
  VkResult physical_devices_query_result = vkEnumeratePhysicalDevices(instance, &physical_device_count, physical_devices);
  PANIC_ASSERT("Failed to Get Physical Devices", physical_devices_query_result == VK_SUCCESS);
  //print available GPUs
  print_gpu_information(physical_devices, physical_device_count);
  VkPhysicalDevice selected_gpu = select_gpu(physical_devices, physical_device_count);


  // structure everything goes to here
  pipeline->instance = instance;
  return pipeline;
}

void LvePipeline_destroy(LvePipeline *self){
  vkDestroyInstance(self->instance, NULL);
  free(self);
}

void print_gpu_information(VkPhysicalDevice *devices, uint32_t count){
  for(uint32_t i = 0; i < count; i++){
    VkPhysicalDeviceProperties info = {0};
    vkGetPhysicalDeviceProperties(devices[i], &info);
    
    printf("apiVersion: %d,\t", info.apiVersion);
    printf("deviceType: %s, \t", gpu_type(info.deviceType));
    printf("deviceName: %s, \t", info.deviceName);
    printf("\n");
  }
}

const char *gpu_type(int i){
  switch (i){
    case 0 : return "VK_PHYSICAL_DEVICE_TYPE_OTHER";
    case 1 : return "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";
    case 2 : return "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";
    case 3 : return "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";
    case 4 : return "VK_PHYSICAL_DEVICE_TYPE_CPU";
    default: return "invalid";
  }
}

VkPhysicalDevice select_gpu(VkPhysicalDevice *devices, uint32_t count){
  PANIC_ASSERT("No Vulkan Devices?", count >0);
  if (count == 1){
    return devices[0];
  } else {
    for(uint32_t i = 0; i< count; i++){
      VkPhysicalDevice selected = devices[i];
      VkPhysicalDeviceProperties info = {0};
      vkGetPhysicalDeviceProperties(selected, &info);
      if (info.deviceType ==  VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        return selected;
      }
    }
    return devices[0];
  }
}
