#pragma once

#include <limits>
#include "../Utility/Vector2.h"
#include "../Classes/Entity.h"
#include "../Utility/Math.h"

struct collision {
	Vector2 normal;
	float depth = -std::numeric_limits<float>::infinity();
};

namespace PhysicalManager{
	void moveToTarget(Entity* entity, const Vector2& targetPos, float deltaTime);

	collision find_colliion(const Vector2& posA, float radiusA, const Vector2& posB, float radiusB);
	void resolve_collision(collision col, Entity* entityA, Entity* entityB);
}


