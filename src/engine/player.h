#pragma once
#include "camera.h"
#include "raylib.h"

typedef struct {
    Vector3 position;
    BoundingBox bounds;
    float speed;
    float sprint_speed;
    bool is_moving;
} player_t;

player_t *player_create();

void player_update(player_t *player, camera_3d_t *camera);

void player_render(const player_t *player);

void player_destroy(player_t *player);