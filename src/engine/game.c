#include "game.h"

#include <stdlib.h>


game_t *game_create(const int window_width, const int window_height, char *game_title) {
    game_t *game = malloc(sizeof(game_t));
    if (game == NULL) {
        return NULL;
    }
    game->window_width = window_width;
    game->window_height = window_height;
    game->game_title = game_title;
    game->world = create_world(game->window_width, game->window_height);
    if (game->world == NULL) {
        free(game);
        return NULL;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(game->window_width, game->window_height, game->game_title);
    SetTargetFPS(60);
    DisableCursor();
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

    add_object_to_world(game->world, object_create("assets/banner_blue.obj", (Vector3){0.0f, 0.0f, 0.0f}));

    return game;
}

void game_update(const game_t *game) {
    update_world(game->world);
}

void game_render(const game_t *game) {
    render_world(game->world);
}

void game_destroy(game_t *game) {
    destroy_world(game->world);
    free(game);
    CloseWindow();
}
