#include "scene.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "log_internal.h"
#include "raylib.h"
#include "stdint.h"
#include "inttypes.h"

// =====================
// SCENE
// =====================

// Creates and allocates a scene into memory
Scene* scene_create(int capacity) {
  Scene* scene = malloc(sizeof(Scene));
  scene->entities = calloc(capacity, sizeof(Entity*));
  scene->capacity = capacity;
  scene->count = 0;
  scene->timeScale = 1.0f;
  return scene;
}

// Adds a entity into the scene
Entity* scene_add_entity(Scene* scene, Entity entity) {
  if (scene->count >= scene->capacity) {
    int old_capacity = scene->capacity;

    scene->capacity = (scene->capacity == 0) ? 1 : scene->capacity * 2;

    Entity** new_entities = realloc(scene->entities, scene->capacity * sizeof(Entity*));
    if (!new_entities) {
      _log_msg(_LOG_ENGINE, _LOG_LEVEL_ERROR, "Entity realloc failed");
      return NULL;
    }

    for (int i = old_capacity; i < scene->capacity; i++) {
      new_entities[i] = NULL;
    }

    scene->entities = new_entities;
  }

  Entity* e = malloc(sizeof(Entity));
  if (!e) return NULL;
  *e = entity;

  e->id = scene->count;

  scene->entities[scene->count] = e;
  scene->count++;

  return e;
}

void scene_update(Scene* scene, float dt) {
  float scaled_dt = dt * scene->timeScale;

  for (int i = 0; i < scene->count; i++) {
    Entity* e = scene->entities[i];

    if (!e) {
      printf("NULL entity at %d\n", i);
      exit(1);
    }

    if ((uintptr_t)e < 0x1000) {
      printf("INVALID LOW PTR at %d: %p\n", i, (void*)e);
      exit(1);
    }

    entity_update(e, scaled_dt);
  }
}

void scene_draw(Scene* scene) {
  for (int i = 0; i < scene->count; i++) {
    entity_draw(scene->entities[i]);
  }
}

void scene_shutdown(Scene* scene) {
  for (int i = 0; i < scene->count; i++) {
    if (scene->entities[i]) {
      entity_destroy(scene->entities[i]);
      free(scene->entities[i]);
    }
  }

  free(scene->entities);
  scene->entities = NULL;
}
