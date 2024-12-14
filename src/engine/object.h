#pragma once

#include "raylib.h"

typedef struct {
    Model model;
    Vector3 position;
    BoundingBox bounds;
} object_t;

object_t *object_create(const char *model_path, Vector3 position);
void object_render(const object_t *object);
bool object_check_collision(const object_t *object, const object_t *other);
void object_destroy(object_t *object);