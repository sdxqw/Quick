#pragma once

#include "player.h"
#include "raylib.h"

typedef struct {
    Model model;
    Vector3 position;
    BoundingBox bounds;
    BoundingBox _model_bounding_box;
} object_t;

object_t *object_create(const char *model_path, Vector3 position);
void object_render( object_t *object);
bool object_check_collision(const object_t *object, const object_t *other);
bool object_check_collision_with_player(const object_t *object, const player_t *player);
void object_destroy(object_t *object);