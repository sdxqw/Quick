#include "gun.h"

#include <stdlib.h>
#include <external/glad.h>

gun_t *gun_create(const char *model_path, const Vector3 position) {
    gun_t *gun = malloc(sizeof(gun_t));
    if (gun == NULL) {
        return NULL;
    }

    gun->model = LoadModel(model_path);
    gun->position = position;
    gun->rotation = (Vector3){0.f, 0.f, 0.f};

    return gun;
}

void gun_render(const gun_t *gun) {
    DrawModelEx(
        gun->model, gun->position, gun->rotation, 0.f, (Vector3){1.f, 1.f, 1.f}, WHITE);
}
