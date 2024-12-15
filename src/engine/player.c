#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include "raymath.h"

player_t *player_create() {
    player_t *player = malloc(sizeof(player_t));
    if (player == NULL) {
        return NULL;
    }

    player->position = (Vector3){0.0f, 1.0f, 0.0f};
    player->bounds = (BoundingBox){
        (Vector3){player->position.x - 0.5f, 0, player->position.z - 0.5f},
        (Vector3){player->position.x + 0.5f, player->position.y + 1.0f, player->position.z + 0.5f}
    };

    player->speed = 0.1f;
    player->sprint_speed = 0.2f;
    player->is_moving = false;

    player->gun = gun_create("assets/sg.glb", (Vector3){0.0f, 0.0f, 0.0f});

    return player;
}

void player_update(player_t *player, camera_3d_t *camera) {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera->camera.target, camera->camera.position));
    const Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera->camera.up));

    // Zero out vertical component
    forward.y = 0.0f;
    forward = Vector3Normalize(forward);

    // reset movement state
    player->is_moving = false;

    // Movement input
    if (IsKeyDown(KEY_W)) {
        player->position = Vector3Add(player->position, Vector3Scale(forward, player->speed));
        player->is_moving = true;
    }
    if (IsKeyDown(KEY_S)) {
        player->position = Vector3Subtract(player->position, Vector3Scale(forward, player->speed));
        player->is_moving = true;
    }
    if (IsKeyDown(KEY_A)) {
        player->position = Vector3Subtract(player->position, Vector3Scale(right, player->speed));
        player->is_moving = true;
    }
    if (IsKeyDown(KEY_D)) {
        player->position = Vector3Add(player->position, Vector3Scale(right, player->speed));
        player->is_moving = true;
    }

    // Sprint input
    const bool is_sprinting = IsKeyDown(KEY_LEFT_SHIFT) && player->is_moving;

    // Update camera with player position and movement state
    camera_update(camera, player->position, player->is_moving, is_sprinting);

    // Update bounding box with player position
    player->bounds = (BoundingBox){
        (Vector3){player->position.x - 0.5f, 0, player->position.z - 0.5f},
        (Vector3){player->position.x + 0.5f, player->position.y + 1.0f, player->position.z + 0.5f}
    };

    Vector3 gun_offset = {0.5f, -0.5f, 1.0f}; // Right, below, and forward

    // Calculate gun position relative to the player and camera
    player->gun->position = Vector3Add(player->position,
                                        Vector3Add(Vector3Scale(forward, gun_offset.z),  // Forward
                                                   Vector3Add(Vector3Scale(right, gun_offset.x),  // Right
                                                              (Vector3){0.0f, gun_offset.y, 0.0f}))); // Up/Down

    // Update gun rotation to match camera's orientation (same as before)
    player->gun->rotation = (Vector3){
        camera->pitch, // Pitch (vertical movement)
        camera->yaw,   // Yaw (horizontal movement)
        0.0f           // Roll (typically unused for guns)
    };

}

void player_render(const player_t *player) {
    DrawBoundingBox(player->bounds, RED);
    gun_render(player->gun);
}

void player_destroy(player_t *player) {
    free(player);
}
