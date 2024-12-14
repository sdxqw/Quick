#pragma once
#include "world.h"

typedef struct {
    int window_width;
    int window_height;
    char *game_title;
    world_t *world;
} game_t;

game_t *game_create(int window_width, int window_height, char *game_title);

void game_update(const game_t *game);

void game_render(const game_t *game);

void game_destroy(game_t *game);
