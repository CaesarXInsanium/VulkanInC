project(
  'LittleVulkan',
  'c',
  version : '0.1',
  default_options: [
    'warning_level=3',
    'werror=true',
    'buildtype=debug',
    'debug=true',
    #'optimization=3',
    'c_std=gnu18'
  ]
)


DEPS = [
  dependency('glfw3'),
  dependency('cglm'),
  dependency('vulkan'),
]

common_src = [
  'common/common.c',
  'common/files.c',
  'common/strings.c',
]
common = library(
  'common',
  common_src,
  include_directories: include_directories('.'),
  dependencies: DEPS
)

lve_src = [
  'lve/lve_window.c',
  'lve/lve_app.c',
  'lve/lve_pipeline.c',
]

lve = library(
  'lve',
  lve_src,
  include_directories: include_directories('.'),
  dependencies: DEPS,
  link_with: [common]
)

vkvk_src = [
  'src/main.c'
]

vkvk = executable(
          'vkvk',
          vkvk_src, 
          install : true,
          dependencies: DEPS,
          link_with: [lve, common],
)
