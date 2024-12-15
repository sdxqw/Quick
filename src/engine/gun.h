#pragma once
#include "raylib.h"

typedef struct {
    Model model;
    Vector3 position;
    Vector3 rotation;
} gun_t;

gun_t *gun_create(const char *model_path, Vector3 position);
void gun_render(const gun_t *gun);