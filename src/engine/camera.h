#pragma once

#include "raylib.h"

typedef struct {
    float default_fovy;
    float sprint_fovy;
    float change_rate;
    Camera camera;
    int camera_mode;
    float pitch;
    float yaw;
    float camera_sensitivity;

} camera_3d_t;

camera_3d_t *camera_3d_create();

void camera_update_position(camera_3d_t *camera, Vector3 position, float headbob_offset);
void camera_destroy(camera_3d_t *camera);