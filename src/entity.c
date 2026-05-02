#include "entity.h"

#include "errno.h"
#include "raylib.h"
#include "stddef.h"
#include "stdio.h"

// =====================
// CONSTRUCTORS
// =====================

Entity entity_create_simple(Vector3 pos, ShapeType shape, EntityType type, Color color) {
  Entity entity = {
      .type = type,
      .mass = 1.0f,
      .pos = pos,
      .render =
          {
              .color = color,
              .shape = shape,
          },
      .vel = (Vector3){0.0f, 0.0f, 0.0f},
  };

  entity.render.texture = NULL;
  entity.render.mesh = NULL;
  entity.render.has_model = false;

  return entity;
}

Entity entity_create_advanced(
    Vector3 pos, EntityType type, float mass, Vector3 vel, RenderData render) {
  Entity entity = {
      .type = type,
      .mass = mass,
      .pos = pos,
      .render = render,
      .vel = vel,
  };

  entity.render.has_model = false;

  if (entity.render.mesh != NULL) {
    entity.render.model = LoadModelFromMesh(*entity.render.mesh);
    entity.render.has_model = true;
    // NOTE: entity.render.mesh IS NOW A DANGELING POINTER BUT WE WILL ADD THE ABLITY TO CHANGE THE
    // MESH WHEN WE WANT LATER GOOD FOR NOW
    UnloadMesh(*entity.render.mesh);
    entity.render.mesh = NULL;
  }

  return entity;
}

// =====================
// RUNTIME MODIFICATION
// =====================

void entity_change_type(Entity* entity, EntityType type) {
  entity->type = type;
}

// =====================
// LOGIC
// =====================

void entity_update(Entity* entity, float dt) {
}

// =====================
// RENDERING
// =====================

void entity_draw(Entity* entity) {
  if (entity->render.has_model) {
    // For now we will not let them change the scale
    DrawModelEx(entity->render.model,
        entity->pos,
        (Vector3){0.0f, 1.0f, 0.0f},
        0.0f,
        entity->render.size,
        entity->render.color);
    return;
  }
  switch (entity->render.shape) {
    case SHAPE_NONE:
      break;
    case SHAPE_CUBE:
      DrawCube(entity->pos,
          entity->render.size.x,
          entity->render.size.y,
          entity->render.size.z,
          entity->render.color);
      break;
    case SHAPE_PLANE:
      DrawPlane(entity->pos,
          (Vector2){entity->render.size.x, entity->render.size.y},
          entity->render.color);
      break;
    case SHAPE_SPHERE:
      DrawSphere(entity->pos, entity->render.radius, entity->render.color);
      break;
    default:
      DrawCube(entity->pos,
          entity->render.size.x,
          entity->render.size.y,
          entity->render.size.z,
          entity->render.color);
      printf(
          "Error: Type - Model failed to load\nthe model got hit by a bozuka imma just give u "
          "a "
          "red cube");
  }
}

void entity_destroy(Entity* entity) {
  if (entity->render.has_model) {
    UnloadModel(entity->render.model);
  }
}
