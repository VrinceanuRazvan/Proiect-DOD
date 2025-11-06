#pragma once

#include <limits>
#include "../Utility/Vector2.h"
#include "../Classes/Entity.h"
#include "../Utility/Math.h"

struct collision {
	Vector2 normal;
	float depth = -std::numeric_limits<float>::infinity();
};

void moveToTarget(Entity* entity, const Vector2& targetPos, float speed, float deltaTime);
collision find_colliion(const Vector2& posA, float radiusA, const Vector2& posB, float radiusB);
void resolve_collision(collision col,Entity* entityA , Entity* entityB);