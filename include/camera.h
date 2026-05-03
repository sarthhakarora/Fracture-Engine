#pragma once

#include "entity.h"
#include "raylib.h"

// =====================
// CAMERA
// =====================

typedef struct {
  Camera3D camera;

  // orientation
  Vector3 forward;
  float yaw;
  float pitch;

  // movement
  float speed;
  float sensitivity;
  float deltaTime;

  // follow system
  Entity* follow_target;
  Vector3 offset;

  // config
  float nearPlane;
  float farPlane;

  // state
  bool freecam_enabled;

} Cam;

// =====================
// LIFECYCLE
// =====================

// simple: basic sane defaults
Cam camera_create_simple(Vector3 position);

// advanced: full control
Cam camera_create_advanced(Vector3 position,
    float yaw,
    float pitch,
    float fovy,
    float nearPlane,
    float farPlane,
    float speed,
    float sensitivity);

// update (handles follow + forward calc)
void camera_update(Cam* cam, float dt);
void camera_rotate(Cam* cam, float yaw_delta, float pitch_delta);

// =====================
// CONTROL
// =====================

// link camera to entity
void camera_link(Cam* cam, Entity* target);

// set follow offset
void camera_set_offset(Cam* cam, Vector3 offset);

// zoom (FOV)
void camera_set_fov(Cam* cam, float fovy);

// clip planes
void camera_set_render_distance(Cam* cam, float nearPlane, float farPlane);
// =====================
// STATE
// =====================

// enable/disable freecam
void camera_set_freecam(Cam* cam, bool enabled);

// apply freecam movement (only runs if enabled)
void camera_apply_freecam(Cam* cam);
