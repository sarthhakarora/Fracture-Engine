#include "entity.h"
#include <stdbool.h>

#include "raylib.h"
#include "raymath.h"
#include "scene.h"
#include "stddef.h"
#include "log_internal.h"
#include "engine.h"
#include "inttypes.h"
#include "log_internal.h"

// =====================
// CONSTRUCTORS
// =====================
Entity* entity_create_simple(Scene* scene, Vector3 pos, ShapeType shape, EntityType type, Color color) {
  if(scene == NULL) {
    _log_msg(_LOG_GAME, _LOG_LEVEL_ERROR, "Entity creation failed - entity needs host scene");
    return NULL;
  }

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
  entity.render.has_model = false;

  Entity* e = scene_add_entity(scene, entity);

  return e;
}

Entity* entity_create_advanced(
    Scene* scene, Vector3 pos, EntityType type, float mass, Vector3 vel, RenderData render) {
  Entity entity = {
    .type = type,
    .mass = mass,
    .pos = pos,
    .render = render,
    .vel = vel,
  };
  if(scene == NULL) {
    _log_msg(_LOG_GAME, _LOG_LEVEL_ERROR, "Entity creation failed - entity needs host scene");
    return NULL;
  }

  entity.render.has_model = (render.model.meshCount > 0);
  entity.render.model = render.model;

  return scene_add_entity(scene, entity);
}

// =====================
// LOGIC
// =====================

void entity_update(Entity* entity, float dt) {
  entity->pos = Vector3Add(entity->pos, Vector3Scale(entity->vel, dt));
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
      _log_msg(_LOG_ENGINE, _LOG_LEVEL_ERROR, "Model failed to load falling back to red cube Entity id: " PRId64 "\n", entity->id);
  }
}

void entity_destroy(Entity* entity) {
}
