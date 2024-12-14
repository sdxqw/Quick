#include "camera.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "raymath.h"


camera_3d_t *camera_3d_create() {
    camera_3d_t *camera = malloc(sizeof(camera_3d_t));
    if (camera == NULL) {
        return NULL;
    }

    camera->default_fovy = 60.0f;
    camera->sprint_fovy = 75.0f;
    camera->change_rate = 5.0f;

    camera->camera = (Camera){
        .position = (Vector3){0.0f, 0.0f, 0.0f},
        .target = (Vector3){0.0f, 0.0f, 0.0f},
        .up = (Vector3){0.0f, 1.0f, 0.0f},
        .fovy = camera->default_fovy,
        .projection = CAMERA_PERSPECTIVE,
    };

    camera->camera_mode = CAMERA_FIRST_PERSON;
    camera->pitch = 0.0f;
    camera->yaw = 0.0f;
    camera->camera_sensitivity = .15f;


    return camera;
}

void camera_update_position(camera_3d_t *camera, const Vector3 position, const float headbob_offset) {
    // Adjust camera position with headbob effect
    camera->camera.position = (Vector3){position.x, position.y + headbob_offset, position.z};

    // Get mouse movement (delta)
    const Vector2 mouseDelta = GetMouseDelta();

    // Fix flipped yaw rotation by reversing the sign of mouseDelta.x
    camera->yaw -= mouseDelta.x * camera->camera_sensitivity; // Subtract instead of adding

    // Adjust pitch rotation (keeping this as is)
    camera->pitch -= mouseDelta.y * camera->camera_sensitivity;

    // Clamp pitch to avoid flipping
    if (camera->pitch > 89.0f) camera->pitch = 89.0f;
    if (camera->pitch < -89.0f) camera->pitch = -89.0f;

    // Convert yaw and pitch to radians
    const float yawRad = DEG2RAD * camera->yaw;
    const float pitchRad = DEG2RAD * camera->pitch;

    // Calculate the forward direction using spherical coordinates
    const Vector3 forward = {
        cosf(pitchRad) * sinf(yawRad),
        sinf(pitchRad),
        cosf(pitchRad) * cosf(yawRad)
    };

    // Update camera target (based on calculated forward direction)
    camera->camera.target = Vector3Add(camera->camera.position, forward);
}

void camera_destroy(camera_3d_t *camera) {
    free(camera);
}
