#pragma once
#include "../Classes/Entity.h"

namespace EntityManager {
	extern Entity* entityArray[100000];
	extern int entityCount;

	extern float spawnRate;
	extern float spawnTimer;
	extern bool autoSpawn;

	void init();

	void update(SDL_Renderer* renderer,float deltaTime);

	void CreateEntity(Vector2 pos, SDL_Renderer* renderer);
	void DestroyEntity(int indesx);
}