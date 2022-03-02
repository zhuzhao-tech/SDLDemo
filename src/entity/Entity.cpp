#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {
    if (texture) {
        delete texture;
    }
}