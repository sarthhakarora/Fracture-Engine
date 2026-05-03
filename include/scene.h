#pragma once

#include <stdint.h>

#include "entity.h"

typedef struct Scene {
  Entity **entities;
  int count;
  int capacity;
  float timeScale;
} Scene;

Scene* scene_create(int capacity);
Entity* scene_add_entity(Scene* scene, Entity entity);
void scene_update(Scene* scene, float dt);
void scene_draw(Scene* scene);
void scene_shutdown(Scene* scene);
