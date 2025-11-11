#include "EntityManager.h"

namespace EntityManager {
    Entity* entityArray[100000];

    // dod
    float entityPositionsX[100000];
    float entityPositionsY[100000];

    float entityVelocitiesX[100000];
    float entityVelocitiesY[100000];

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
            if (entityPositionsX[entityCount] == 0.0f && entityPositionsY[entityCount] == 0.0f) {
                entityPositionsX[entityCount] = position.x;
                entityPositionsY[entityCount] = position.y;

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
                entityPositionsX[i] = entityArray[i]->getPosition().x;
                entityPositionsY[i] = entityArray[i]->getPosition().y;

                entityRadius[i] = entityArray[i]->GetRadius();
                entityStatic[i] = entityArray[i]->isStatic();
                
                delete entityArray[i];
                entityArray[i] = nullptr;
            }
        }
    }
    else {
        for (int i = 0; i < entityCount; i++) {
            if (entityPositionsX[i] != 0.0f || entityPositionsY[i] != 0.0f) {
                entityArray[i] = new Entity(i, Vector2(entityPositionsX[i], entityPositionsY[i]),entityRadius[i],entityStatic[i]);
                entityPositionsX[i] = NULL;
                entityPositionsY[i] = NULL;
                entityRadius[i] = NULL;
                entityStatic[i] = NULL;
            }
        }
	}
}
