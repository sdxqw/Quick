#pragma once

typedef struct {
} terrain_t;

terrain_t *terrain_create();

void render_terrain(const terrain_t *terrain);

void destroy_terrain(terrain_t *terrain);
