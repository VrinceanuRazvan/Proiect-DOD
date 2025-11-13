#pragma once
#include "../Classes/Entity.h"

#include "Renderer.h"

namespace EntityManager {
	extern Entity* entityArray[100000];

	// dod 
	extern Vector2 entityPositions[100000];

	extern Vector2 entityVelocities[100000];

	extern float entityRadius[100000];
	extern bool entityStatic[100000];

	extern int entityCount;

	extern float spawnRate;
	extern float spawnTimer;
	extern bool autoSpawn;

	void init();

	void update(float deltaTime, bool isDOD);

	void CreateEntity(Vector2 pos,bool isDOD);
	void Switch(bool isDOD);
}