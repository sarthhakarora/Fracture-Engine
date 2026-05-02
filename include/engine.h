#pragma once

#include <stdbool.h>

#include "raylib.h"
#include "scene.h"

typedef struct {
  int width;
  int height;
  int fps;
  const char* title;
  bool isRunning;
  Texture2D* textures;
} Engine;

void engine_init(Engine* e);
void engine_begin_frame(Color color);
Texture2D* engine_load_texture(const char* path);
void engine_unload_texture(const char* path);
void engine_end_frame(void);
void engine_shutdown(void);
