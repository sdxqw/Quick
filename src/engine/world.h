#pragma once
#include "camera.h"
#include "object.h"
#include "player.h"

typedef struct {
    camera_3d_t *camera;
    player_t *player;
    object_t **objects;
    int object_count;
    float screen_width;
    float screen_height;
    float crosshair_size;
    float crosshair_thickness;
} world_t;

world_t *create_world(int screen_width, int screen_height);

void add_object_to_world(world_t *world, object_t *object);

void remove_object_from_world(world_t *world, int index);

void update_world(const world_t *world);

void render_world(const world_t *world);

void destroy_world(world_t *world);
