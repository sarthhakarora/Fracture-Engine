#include "engine.h"

#include "assetmanager.h"
#include "raylib.h"
#include "stdio.h"

void engine_init(Engine* e) {
  InitWindow(e->width, e->height, e->title);

  e->isRunning = true;

  SetTargetFPS(e->fps);
  return;
}
void engine_begin_frame(Color color) {
  BeginDrawing();
  ClearBackground(color);
  return;
}

Texture2D* engine_load_texture(const char* path) {
  if (path == NULL) {
    fprintf(stderr, "engine_load_texture: path is NULL\n");
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
