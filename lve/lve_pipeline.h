#ifndef LVE_PIPELINE_H
#define LVE_PIPELINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "common/common.h"
#include "common/strings.h"
#include "common/files.h"
#include "lve_device.h"

typedef struct LvePipeline {
  VkInstance instance;
  LveDevice *device;
  VkPipeline vkpipeline;
  VkShaderModule vert_shader_module;
  VkShaderModule frag_shader_module;
} LvePipeline;

LvePipeline *LvePipeline_new(const char *vert_path, const char *frag_path);

void LvePipeline_destroy(LvePipeline *self);

#endif
