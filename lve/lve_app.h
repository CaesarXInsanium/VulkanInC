#ifndef LVE_APP_H
#define LVE_APP_H
#include "lve_window.h"

typedef struct App_ {
  const int width;
  const int height;
  LveWindow* window;
} App;

App App_new(const int w, const int h, const char *name);
int App_run(App app);

#endif
