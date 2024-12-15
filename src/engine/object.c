#include "object.h"

#include <stdlib.h>

#include "raymath.h"

object_t *object_create(const char *model_path, const Vector3 position) {
    object_t *object = malloc(sizeof(object_t));
    if (object == NULL) {
        return NULL;
    }

    object->model = LoadModel(model_path);
    object->position = position;
    object->bounds = GetModelBoundingBox(object->model);
    object->_model_bounding_box = object->bounds;

    return object;
}

void object_render(object_t *object) {
    object->bounds = (BoundingBox){
        Vector3Add(object->_model_bounding_box.min, object->position),
        Vector3Add(object->_model_bounding_box.max, object->position)
    };
    DrawModel(object->model, object->position, 1.0f, WHITE);
    DrawBoundingBox(object->bounds, YELLOW);
}

bool object_check_collision(const object_t *object, const object_t *other) {
    return CheckCollisionBoxes(object->bounds, other->bounds);
}

bool object_check_collision_with_player(const object_t *object, const player_t *player) {
    return CheckCollisionBoxes(object->bounds, player->bounds);
}

void object_destroy(object_t *object) {
    UnloadModel(object->model);
    free(object);
}
