#ifndef LVE_PIPELINE_H
#define LVE_PIPELINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// vulkan header has to be included before GLFW
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "common/common.h"
#include "common/strings.h"
#include "common/files.h"
#include "lve_device.h"

typedef struct LvePipeline {
  VkInstance instance;
  VkPhysicalDevice physical_device;
  VkDevice logical_device;
  VkQueue graphics_queue;
  VkQueue present_queue;
  VkSurfaceKHR surface;
  VkShaderModule vert_shader_module;
  VkShaderModule frag_shader_module;

  VkPipeline vkpipeline;
} LvePipeline;

LvePipeline *LvePipeline_new(GLFWwindow *window, const char *vert_path, const char *frag_path);

void LvePipeline_destroy(LvePipeline *self);

void print_gpu_information(VkPhysicalDevice *devices, uint32_t count);

const char *gpu_type(int i);

// hacky solution where we simply use the first discrete GPU we find
// otherwise we selected any other thing
VkPhysicalDevice select_gpu(VkPhysicalDevice *devices, uint32_t count);

#endif
