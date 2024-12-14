// src/engine/player.c

#include "player.h"
#include <stdlib.h>
#include "raymath.h"
#include <math.h>

#define HEADBOB_FREQUENCY 10.0f
#define HEADBOB_AMPLITUDE 0.1f

player_t *player_create(camera_3d_t *camera) {
    player_t *player = malloc(sizeof(player_t));
    if (player == NULL) {
        return NULL;
    }

    player->position = (Vector3){0.0f, 2.0f, 0.0f};
    player->speed = 0.1f;
    player->vertical_speed = 0.0f; // Initialize vertical speed
    player->headbob_timer = 0.0f; // Initialize headbob timer
    player->sprint_speed = 0.2f;
    player->camera = camera;

    return player;
}

void player_update(player_t *player) {
    // Compute the forward and right directions based on camera orientation
    Vector3 forward = Vector3Normalize(Vector3Subtract(player->camera->camera.target, player->camera->camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, player->camera->camera.up));

    // Zero out the vertical component of the forward direction
    forward.y = 0.0f;
    forward = Vector3Normalize(forward);

    // Move the player based on input, relative to where the camera is looking
    bool is_moving = false;
    if (IsKeyDown(KEY_W)) {
        player->position = Vector3Add(player->position, Vector3Scale(forward, player->speed));
        is_moving = true;
    }
    if (IsKeyDown(KEY_S)) {
        player->position = Vector3Subtract(player->position, Vector3Scale(forward, player->speed));
        is_moving = true;
    }
    if (IsKeyDown(KEY_A)) {
        player->position = Vector3Subtract(player->position, Vector3Scale(right, player->speed));
        is_moving = true;
    }
    if (IsKeyDown(KEY_D)) {
        player->position = Vector3Add(player->position, Vector3Scale(right, player->speed));
        is_moving = true;
    }

    // Smooth sprinting
    if (IsKeyDown(KEY_LEFT_SHIFT) && is_moving) {
        player->speed += (player->sprint_speed - player->speed) * GetFrameTime() * player->camera->change_rate;
        player->camera->camera.fovy += (player->camera->sprint_fovy - player->camera->camera.fovy) * GetFrameTime() *
                player->camera->change_rate;
    } else {
        player->speed += (player->speed - player->speed) * GetFrameTime() * player->camera->change_rate;
        player->camera->camera.fovy += (player->camera->default_fovy - player->camera->camera.fovy) * GetFrameTime() *
                player->camera->change_rate;
    }

    // Update headbob timer if the player is moving
    if (is_moving) {
        player->headbob_timer += GetFrameTime() * HEADBOB_FREQUENCY;
    } else {
        player->headbob_timer = 0.0f;
    }

    // Calculate headbob offset
    float headbob_offset = sinf(player->headbob_timer) * HEADBOB_AMPLITUDE;

    // Update the camera position to follow the player with headbob effect
    Vector3 camera_position = player->position;
    camera_position.y += headbob_offset;
    camera_update_position(player->camera, camera_position, headbob_offset);
}


void player_destroy(player_t *player) {
    free(player);
}
