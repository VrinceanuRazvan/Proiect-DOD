#include "Level.h"

bool Level::Init() {
    return true;
}

void Level::update() {
    for (Entity* entity : this->entities) {
        entity->update();
    }
}

void Level::render(SDL_Renderer* renderer) {
    for (Entity* entity : this->entities) {
        entity->render(renderer);
    }
}

Entity* Level::SpawnEntity(Vector2 pos, Vector2 size, float rot) {
    Entity* newEntity = new Entity(pos, size, rot);
    this->entities.push_back(newEntity);
    return newEntity;
}
