#include <stdio.h>

#include "raylib.h"
#include "engine/game.h"

int main(void) {
    game_t *game = game_create(1280, 720, "Quick 3D");
    if (game == NULL) {
        fprintf(stderr, "Error: Unable to create game\n");
        return 1;
    }
    while (!WindowShouldClose()) {
        game_update(game);
        game_render(game);
    }
    game_destroy(game);
    return 0;
}
