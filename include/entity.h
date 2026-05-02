#pragma once

#include "raylib.h"

typedef enum {
  ENTITY_STATIC,
  ENTITY_DYNAMIC
} EntityType;

typedef enum {
  SHAPE_NONE,
  SHAPE_CUBE,
  SHAPE_SPHERE,
  SHAPE_PLANE
} ShapeType;

typedef struct {
  Mesh* mesh;
  Model model;
  bool has_model;
  ShapeType shape;
  Color color;
  Texture2D* texture;
  Vector3 size;
  float radius;
} RenderData;

typedef struct {
  Vector3 pos;
  Vector3 vel;
  float mass;
  EntityType type;
  RenderData render;
} Entity;

Entity entity_create_simple(Vector3 pos, ShapeType shape, EntityType type, Color color);
Entity entity_create_advanced(
    Vector3 pos, EntityType type, float mass, Vector3 vel, RenderData render);
void entity_change_type(Entity* entity, EntityType type);
void entity_draw(Entity* entity);
void entity_update(Entity* entity, float dt);
void entity_destroy(Entity* entity);
