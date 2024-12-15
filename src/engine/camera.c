#include "camera.h"
#include <stdlib.h>
#include "raymath.h"
#include <math.h>

#define HEADBOB_FREQUENCY 10.0f
#define HEADBOB_AMPLITUDE 0.06f

camera_3d_t *camera_3d_create() {
    camera_3d_t *camera = malloc(sizeof(camera_3d_t));
    if (camera == NULL) {
        return NULL;
    }

    camera->default_fovy = 60.0f;
    camera->sprint_fovy = 80.0f;
    camera->change_rate = 5.0f;

    camera->camera = (Camera){
        .position = (Vector3){0.0f, 2.0f, 0.0f},
        .target = (Vector3){0.0f, 2.0f, -1.0f},
        .up = (Vector3){0.0f, 1.0f, 0.0f},
        .fovy = camera->default_fovy,
        .projection = CAMERA_PERSPECTIVE,
    };

    camera->camera_mode = CAMERA_FREE;
    camera->pitch = 0.0f;
    camera->yaw = 0.0f;
    camera->camera_sensitivity = 0.15f;

    camera->headbob_timer = 0.0f;

    return camera;
}

void camera_update(camera_3d_t *camera, const Vector3 player_position, bool is_moving, bool is_sprinting) {
    if (camera->camera_mode == CAMERA_FIRST_PERSON) {
        // Apply head bobbing effect
        if (is_moving) {
            camera->headbob_timer += GetFrameTime() * HEADBOB_FREQUENCY;
        } else {
            camera->headbob_timer = 0.0f; // Reset headbob when not moving
        }
        const float headbob_offset = sinf(camera->headbob_timer) * HEADBOB_AMPLITUDE;

        // Smooth sprint FOV effect
        const float target_fovy = is_sprinting ? camera->sprint_fovy : camera->default_fovy;
        camera->camera.fovy += (target_fovy - camera->camera.fovy) * GetFrameTime() * camera->change_rate;

        // Adjust camera position
        camera->camera.position = (Vector3){
            player_position.x,
            player_position.y + headbob_offset,
            player_position.z};

        // Mouse input for camera rotation
        const Vector2 mouseDelta = GetMouseDelta();
        camera->yaw -= mouseDelta.x * camera->camera_sensitivity;
        camera->pitch -= mouseDelta.y * camera->camera_sensitivity;

        // Clamp pitch to avoid flipping
        camera->pitch = Clamp(camera->pitch, -89.0f, 89.0f);

        // Calculate forward direction
        const float yawRad = DEG2RAD * camera->yaw;
        const float pitchRad = DEG2RAD * camera->pitch;
        const Vector3 forward = {
            cosf(pitchRad) * sinf(yawRad),
            sinf(pitchRad),
            cosf(pitchRad) * cosf(yawRad)};

        camera->camera.target = Vector3Add(camera->camera.position, forward);
    } else {
        UpdateCamera(&camera->camera, camera->camera_mode);
    }
}

void camera_destroy(camera_3d_t *camera) {
    free(camera);
}
