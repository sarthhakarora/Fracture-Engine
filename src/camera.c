#include "camera.h"

#include <stdio.h>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stddef.h"

Cam camera_create_simple(Vector3 position) {
  Cam cam = {
      .camera =
          {
              .position = position,
              .target = (Vector3){0.0f, 0.0f, 0.0f},
              .up = (Vector3){0.0f, 1.0f, 0.0f},
              .fovy = 90.0f,
              .projection = CAMERA_PERSPECTIVE,
          },

      .pitch = 0.0f,
      .yaw = 0.0f,

      .sensitivity = 0.1f,
      .speed = 10.0f,

      .nearPlane = 0.1f,
      .farPlane = 1000.0f,

      .freecam_enabled = true,

      .offset = (Vector3){0.0f, 0.0f, 0.0f},
      .forward = (Vector3){0.0f, 0.0f, -1.0f},
  };

  cam.follow_target = NULL;

  rlSetClipPlanes(cam.nearPlane, cam.farPlane);

  return cam;
}

Cam camera_create_advanced(Vector3 position,
    float yaw,
    float pitch,
    float fovy,
    float nearPlane,
    float farPlane,
    float speed,
    float sensitivity) {
  Cam cam = {
      .camera =
          {
              .position = position,
              .target = (Vector3){0.0f, 0.0f, 0.0f},  // temp, fixed below
              .up = (Vector3){0.0f, 1.0f, 0.0f},
              .fovy = fovy,
              .projection = CAMERA_PERSPECTIVE,
          },

      .yaw = yaw,
      .pitch = pitch,

      .speed = speed,
      .sensitivity = sensitivity,

      .nearPlane = nearPlane,
      .farPlane = farPlane,

      .offset = (Vector3){0.0f, 0.0f, 0.0f},

      .freecam_enabled = true,
  };

  cam.follow_target = NULL;

  cam.forward =
      Vector3Normalize((Vector3){cosf(pitch) * cosf(yaw), sinf(pitch), cosf(pitch) * sinf(yaw)});
  cam.camera.target = Vector3Add(cam.camera.position, cam.forward);

  rlSetClipPlanes(cam.nearPlane, cam.farPlane);

  return cam;
}

// =====================
// LINKING
// =====================
static void move_camera(Cam* camera, float dt) {
  Vector3 right = Vector3Normalize(Vector3CrossProduct(camera->forward, camera->camera.up));
  float accel = 40.0f;

  if (IsKeyDown(KEY_Q)) {
    camera->speed += accel * dt;
  }
  if (IsKeyDown(KEY_E)) {
    camera->speed -= accel * dt;
  }

  camera->speed = Clamp(camera->speed, 0.1f, 500.0f);

  if (IsKeyDown(KEY_W)) {
    camera->camera.position = Vector3Add(camera->camera.position,
        Vector3Scale(camera->forward, camera->speed * dt));
  }
  if (IsKeyDown(KEY_S)) {
    camera->camera.position = Vector3Subtract(camera->camera.position,
        Vector3Scale(camera->forward, camera->speed * dt));
  }
  if (IsKeyDown(KEY_A)) {
    camera->camera.position = Vector3Subtract(
        camera->camera.position, Vector3Scale(right, camera->speed * dt));
  }
  if (IsKeyDown(KEY_D)) {
    camera->camera.position = Vector3Add(
        camera->camera.position, Vector3Scale(right, camera->speed * dt));
  }
  if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_SPACE)) {
    camera->camera.position = Vector3Subtract(
        camera->camera.position, Vector3Scale(camera->camera.up, camera->speed * dt));
  } else if (IsKeyDown(KEY_SPACE)) {
    camera->camera.position =
        Vector3Add(camera->camera.position, Vector3Scale(camera->camera.up, camera->speed * dt));
  }
}

void camera_link(Cam* cam, Entity* target) {
  if (!cam) return;

  cam->follow_target = target;
  cam->freecam_enabled = false;  // follow overrides freecam
}

void camera_unlink(Cam* cam) {
  if (!cam) return;

  cam->follow_target = NULL;
}

void camera_set_offset(Cam* cam, Vector3 offset) {
  if (!cam) return;
  cam->offset = offset;
}

// =====================
// CONFIG
// =====================

void camera_set_render_distance(Cam* cam, float nearPlane, float farPlane) {
  if (!cam) return;

  cam->nearPlane = nearPlane;
  cam->farPlane = farPlane;

  rlSetClipPlanes(nearPlane, farPlane);
}

void camera_set_fov(Cam* cam, float fov) {
  if (!cam) return;
  cam->camera.fovy = fov;
}

// =====================
// MODE
// =====================

void camera_set_freecam(Cam* cam, bool enabled) {
  if (!cam) return;

  cam->freecam_enabled = enabled;
}

// =====================
// TRANSFORMS
// =====================

void camera_rotate(Cam* cam, float yaw_delta, float pitch_delta) {
  if (!cam) return;

  cam->yaw += yaw_delta;
  cam->pitch += pitch_delta;
  cam->pitch = Clamp(cam->pitch, -1.5f, 1.5f);
}

void camera_zoom(Cam* cam, float amount) {
  if (!cam) return;

  cam->camera.fovy += amount;
}

// =====================
// APPLY
// =====================
void camera_apply(Cam* cam) {
  if (!cam) return;

  cam->forward = Vector3Normalize((Vector3){
      cosf(cam->pitch) * cosf(cam->yaw), sinf(cam->pitch), cosf(cam->pitch) * sinf(cam->yaw)});

  cam->camera.target = Vector3Add(cam->camera.position, cam->forward);
}

void camera_update(Cam* cam, float dt) {
  if (!cam) return;
  if (cam->freecam_enabled) {
    move_camera(cam, dt);
  }
  if (cam->follow_target != NULL) {
    cam->camera.position = Vector3Add(cam->follow_target->pos, cam->offset);
  }
  camera_apply(cam);
}
