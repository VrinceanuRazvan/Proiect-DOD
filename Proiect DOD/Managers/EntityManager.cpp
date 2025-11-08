#include "EntityManager.h"

namespace EntityManager {
    Entity* entityArray[100000];
    int entityCount = 0;
    float spawnRate = 5.0f;
    float spawnTimer = 0.0f;
    bool autoSpawn = true;
}

void EntityManager::init()
{
    for (int i =0 ; i < 100000; i++) {
        entityArray[i] = nullptr;
	}
}

void EntityManager::update(SDL_Renderer* renderer, float deltaTime)
{
    if (autoSpawn) {
        spawnTimer += deltaTime;
        float spawnInterval = 1.0f / spawnRate;
        while (spawnTimer >= spawnInterval) {
            spawnTimer -= spawnInterval;
            CreateEntity(Vector2(rand() % 640, rand() % 480), renderer);
            entityCount++;
        }
    }
}

void EntityManager::CreateEntity(Vector2 position, SDL_Renderer* renderer)
{
    for (int i = 0; i < 100000; i++) {
        if (entityArray[i] == nullptr) {
            entityArray[i] = new Entity(position);
			entityArray[i]->LoadSpriteSheet(renderer, "./Sprites/knight idle.bmp",4);
            return;
        }
    }
}

void EntityManager::DestroyEntity(int index)
{
}