#pragma once

#include <stdbool.h>

#include "raylib.h"
struct Scene;  // forward declaration
typedef struct Scene Scene;

typedef struct {
  int width;
  int height;
  int fps;
  float dt;
  const char* title;
  bool isRunning;
  Texture2D* textures;
  Scene* activeScene;
} Engine;

void engine_init(Engine* e);
void engine_set_active_scene(Engine *e, Scene* activeScene);
void engine_begin_frame(Engine* e, Color color);
void engine_end_frame(void);
Texture2D* engine_load_texture(const char* path);
void engine_unload_texture(const char* path);
void engine_shutdown(void);
