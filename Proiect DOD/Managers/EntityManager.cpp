#include "EntityManager.h"

namespace EntityManager {
    Entity* entityArray[100000];

    // dod
	Vector2 entityPositions[100000];
	Vector2 entityVelocities[100000];

    float entityRadius[100000];
    bool entityStatic[100000];

    int entityCount = 0;
    float spawnRate = 5.0f;
    float spawnTimer = 0.0f;
    bool autoSpawn = true;
}

void EntityManager::init()
{
    for (int i = 0; i < 100000; i++) {
        entityArray[i] = nullptr;
    }
}

void EntityManager::update(float deltaTime,bool isDOD)
{
    if (autoSpawn) {
        spawnTimer += deltaTime;
        float spawnInterval = 1.0f / spawnRate;
        while (spawnTimer >= spawnInterval) {
            spawnTimer -= spawnInterval;
            CreateEntity(Vector2(rand() % 1280, rand() % 1080),isDOD);
        }
    }
}

void EntityManager::CreateEntity(Vector2 position,bool isDOD)
{
        if (isDOD) {
            if (entityPositions[entityCount].x == 0 and entityPositions[entityCount].y == 0) {
				entityPositions[entityCount] = position;

				entityRadius[entityCount] = 10.0f;
				entityStatic[entityCount] = false;

                Renderer::LoadEntityTexture(entityCount, "Sprites/knight idle.bmp", 4, 0.1f);
                return;
            }
        }
        else
        {
            if (entityArray[entityCount] == nullptr) {
                entityArray[entityCount] = new Entity(entityCount, position,10.0f,false);
                Renderer::LoadEntityTexture(entityCount, "Sprites/knight idle.bmp", 4, 0.1f);
                return;
            }
        }
      entityCount++;
}

void EntityManager::Switch(bool isDOD)
{
    if (isDOD) {
        for (int i = 0; i < entityCount; i++) {
            if (entityArray[i] != nullptr) {
				entityPositions[i] = entityArray[i]->getPosition();

                entityRadius[i] = entityArray[i]->GetRadius();
                entityStatic[i] = entityArray[i]->isStatic();
                
                delete entityArray[i];
                entityArray[i] = nullptr;
            }
        }
    }
    else {
        for (int i = 0; i < entityCount; i++) {
            if (entityPositions[i].x == 0 and entityPositions[i].y ==0) {
                entityArray[i] = new Entity(i, entityPositions[i], entityRadius[i], entityStatic[i]);
				entityPositions[i] = Vector2(0, 0);
                entityRadius[i] = NULL;
                entityStatic[i] = NULL;
            }
        }
	}
}
