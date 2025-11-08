#include "PhysicsManager.h"

void PhysicalManager::moveToTarget(Entity* entity, const Vector2& targetPos, float deltaTime)
{
    Vector2 direction = targetPos - entity->getPosition();
    float distance = Distance(entity->getPosition(), targetPos);
    if (distance > 0.0f) {
		Vector2 normal = Normalize(direction);
        entity->setVelocity(normal * 100.0f);
	}
}

collision PhysicalManager::find_colliion(const Vector2& posA, float radiusA, const Vector2& posB, float radiusB)
{
    collision result;

    float distance = Distance(posA, posB);

    if (distance < radiusA + radiusB) {
		result.depth = (radiusA + radiusB) - distance;
		result.normal = (posB - posA) / distance;
    }

    return result;
}

void PhysicalManager::resolve_collision(collision col, Entity* entityA, Entity* entityB)
{
    Vector2 correction = col.normal * col.depth * 0.5f;

    if (!entityA->isStatic()) {
        entityA->setPosition(entityA->getPosition() - correction);
    }
    if (!entityB->isStatic()) {
        entityB->setPosition(entityB->getPosition() + correction);
    }
}
