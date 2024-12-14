#pragma once
#include "camera.h"
#include "raylib.h"

typedef struct {
    Vector3 position;
    float speed;
    float vertical_speed;
    float headbob_timer;
    float sprint_speed;
    camera_3d_t *camera;
} player_t;

player_t *player_create(camera_3d_t *camera);
void player_update(player_t *player);

void player_destroy(player_t *player);