#include "engine.h"

#include "assetmanager.h"
#include "scene.h"
#include "stddef.h"
#include "raylib.h"
#include "log_internal.h"

void engine_init(Engine* e) {
  InitWindow(e->width, e->height, e->title);

  e->isRunning = true;
  e->activeScene = NULL;

  SetTargetFPS(e->fps);
  return;
}

void engine_set_active_scene(Engine *e, Scene* activeScene) {
  e->activeScene = activeScene;
}

void engine_begin_frame(Engine* e, Color color) {
  BeginDrawing();
  ClearBackground(color);
  e->dt = GetFrameTime();
  return;
}

Texture2D* engine_load_texture(const char* path) {
  if (path == NULL) {
    _log_msg(_LOG_ENGINE, _LOG_LEVEL_ERROR, "path is NULL");
    return NULL;
  }
  ManagedTexture* tex = asset_get_texture(path);
  if (!tex || !tex->loaded) {
    return NULL;
  }
  return &tex->texture;
}
void engine_unload_texture(const char* path) {
  asset_release_texture(path);
}

void engine_end_frame(void) {
  EndDrawing();
  return;
}
void engine_shutdown(void) {
  CloseWindow();
  return;
}
