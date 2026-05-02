#include "scene.h"

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "errno.h"
#include "raylib.h"

// =====================
// SCENE
// =====================

// Creates and allocates a scene into memory
Scene scene_create(int capacity) {
  Scene scene = {
      .entities = malloc(capacity * sizeof(Entity)),
      .capacity = capacity,
      .count = 0,
      .timeScale = 1.0f,
  };

  return scene;
}

// Adds a entity into the scene
void scene_add_entity(Scene* scene, Entity entity) {
  if (scene->count >= scene->capacity) {
    if (scene->capacity == 0) scene->capacity = 1;
    else scene->capacity *= 2;
    Entity* new_entities = realloc(scene->entities, scene->capacity * sizeof(Entity));
    if (new_entities == NULL) {
      fprintf(stderr, "entity realloc failed");
      return;
    }
    scene->entities = new_entities;
  }
  scene->entities[scene->count] = entity;
  scene->count++;
}

void scene_update(Scene* scene, float dt) {
  // ignore the dt situation i really dont feel like it today
  float scaled_dt = GetFrameTime() * scene->timeScale;

  for (int i = 0; i < scene->count; i++) {
    entity_update(&scene->entities[i], scaled_dt);
  }
}

void scene_draw(Scene* scene) {
  for (int i = 0; i < scene->count; i++) {
    entity_draw(&scene->entities[i]);
  }
}

void scene_shutdown(Scene* scene) {
  for (int i = 0; i < scene->count; i++) {
    entity_destroy(&scene->entities[i]);
  }
  free(scene->entities);
  scene->entities = NULL;
  scene->count = 0;
  scene->capacity = 0;
}
