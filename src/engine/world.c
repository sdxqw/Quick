#include "world.h"

#include <stdlib.h>

world_t *create_world(int screen_width, int screen_height) {
    world_t *world = malloc(sizeof(world_t));
    if (world == NULL) {
        return NULL;
    }

    world->camera = camera_3d_create();
    if (world->camera == NULL) {
        free(world);
        return NULL;
    }

    world->player = player_create(world->camera);
    if (world->player == NULL) {
        camera_destroy(world->camera);
        free(world);
        return NULL;
    }

    world->objects = NULL;
    world->object_count = 0;
    world->screen_width = (float) screen_width;
    world->screen_height = (float) screen_height;
    world->crosshair_size = 10;
    world->crosshair_thickness = 2;

    return world;
}

void add_object_to_world(world_t *world, object_t *object) {
    world->objects = realloc(world->objects, (world->object_count + 1) * sizeof(object_t *));
    world->objects[world->object_count] = object;
    world->object_count++;
}

void remove_object_from_world(world_t *world, const int index) {
    if (index < 0 || index >= world->object_count) {
        return;
    }

    object_destroy(world->objects[index]);

    for (int i = index; i < world->object_count - 1; i++) {
        world->objects[i] = world->objects[i + 1];
    }

    world->object_count--;
    world->objects = realloc(world->objects, sizeof(object_t *) * world->object_count);
}


void update_world(const world_t *world) {
    player_update(world->player);
}

void render_world(const world_t *world) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(world->camera->camera);

    for (int i = 0; i < world->object_count; i++) {
        object_render(world->objects[i]);
    }

    DrawGrid(100, 1.0f);
    EndMode3D();


    DrawLineEx((Vector2){world->screen_width / 2 - world->crosshair_size, world->screen_height / 2},
               (Vector2){world->screen_width / 2 + world->crosshair_size, world->screen_height / 2},
               world->crosshair_thickness, WHITE);
    DrawLineEx((Vector2){world->screen_width / 2, world->screen_height / 2 - world->crosshair_size},
               (Vector2){world->screen_width / 2, world->screen_height / 2 + world->crosshair_size},
               world->crosshair_thickness, WHITE);

    EndDrawing();
}

void destroy_world(world_t *world) {
    for (int i = 0; i < world->object_count; i++) {
        object_destroy(world->objects[i]);
    }
    camera_destroy(world->camera);
    player_destroy(world->player);
    free(world);
}
