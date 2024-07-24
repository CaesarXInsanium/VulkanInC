#ifndef LVE_PIPELINE_H
#define LVE_PIPELINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "common/common.h"
#include "common/strings.h"
#include "common/files.h"
#include "lve_device.h"

typedef struct LvePipeline {
  VkInstance instance;
  VkPhysicalDevice gpu;
  VkDevice logical_device;
  VkPipeline vkpipeline;
  VkShaderModule vert_shader_module;
  VkShaderModule frag_shader_module;
} LvePipeline;

LvePipeline *LvePipeline_new(const char *vert_path, const char *frag_path);

void LvePipeline_destroy(LvePipeline *self);

void print_gpu_information(VkPhysicalDevice *devices, uint32_t count);

const char *gpu_type(int i);

// hacky solution where we simply use the first discrete GPU we find
// otherwise we selected any other thing
VkPhysicalDevice select_gpu(VkPhysicalDevice *devices, uint32_t count);

#endif
