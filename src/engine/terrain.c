#include "terrain.h"

#include <stdlib.h>

terrain_t *terrain_create() {
    terrain_t *terrain = malloc(sizeof(terrain_t));
    if (terrain == NULL) {
        return NULL;
    }

    return terrain;
}

void render_terrain(const terrain_t *terrain) {

}