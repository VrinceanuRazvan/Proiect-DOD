#pragma once

#include <limits>
#include "../Utility/Vector2.h"
#include "../Classes/Entity.h"
#include "../Utility/Math.h"

#include "EntityManager.h" 

struct collision {
	Vector2 normal;
	float depth = -std::numeric_limits<float>::infinity();
};

namespace PhysicalManager{
	void Update(float deltaTime, bool isDOD);

	void moveToTargetOOP(Entity* entity, const Vector2& targetPos, float deltaTime);
	void moveToTargetDOD(int i, Vector2 targetPos, float deltaTime);

	void step(int i,float detlaTime);

	collision find_colliion(Vector2 PosA, float radiusA, Vector2 PosB, float radiusB);
	void resolve_collisionOOP(collision col, Entity* entityA, Entity* entityB);
	void resolve_collisionDOD(collision col, int i, int j);
}


