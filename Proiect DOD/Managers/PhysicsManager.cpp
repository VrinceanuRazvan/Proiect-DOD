#include "PhysicsManager.h"

void PhysicalManager::Update(float deltaTime, bool isDOD)
{
    if (!isDOD) {
        for (int i = 0; i < EntityManager::entityCount; i++) {
            if (EntityManager::entityArray[i] != nullptr) {
                if (EntityManager::entityArray[i]->isStatic() == false) {

                    EntityManager::entityArray[i]->update(deltaTime);

                    PhysicalManager::moveToTargetOOP(EntityManager::entityArray[i], Vector2(1280 / 2, 1080 / 2), deltaTime);

                    for (int j = i + 1; j < EntityManager::entityCount; j++) {
                        if (EntityManager::entityArray[j] != nullptr and EntityManager::entityArray[i] != EntityManager::entityArray[j]) {
                            if (EntityManager::entityArray[j]->isStatic() == false) {
                                collision col = PhysicalManager::find_colliion(EntityManager::entityArray[i]->getPosition(), EntityManager::entityArray[i]->GetRadius(),
                                    EntityManager::entityArray[j]->getPosition(), EntityManager::entityArray[j]->GetRadius());
                                if (col.depth > 0.0f) {
                                    PhysicalManager::resolve_collisionOOP(col, EntityManager::entityArray[i], EntityManager::entityArray[j]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < EntityManager::entityCount; i++) {
            if (!EntityManager::entityStatic[i]) {

                PhysicalManager::step(i, deltaTime);

                PhysicalManager::moveToTargetDOD(i, Vector2( 1280 / 2, 1080 /2), deltaTime);

                for (int j = i + 1; j < EntityManager::entityCount; j++) {
                    if (!EntityManager::entityStatic[j] and i != j) {
                        collision col = PhysicalManager::find_colliion(EntityManager::entityPositions[i], EntityManager::entityRadius[i],
                            EntityManager::entityPositions[j], EntityManager::entityRadius[j]);
                        if (col.depth > 0.0f) {
                            PhysicalManager::resolve_collisionDOD(col, i, j);
                        }
                    }
                }
            }
        }
    }
}

void PhysicalManager::step(int i, float deltaTime)
{
    if (EntityManager::entityStatic[i] == false)
    {
		EntityManager::entityPositions[i] = EntityManager::entityPositions[i] + EntityManager::entityVelocities[i] * deltaTime;
    }
}

void PhysicalManager::moveToTargetOOP(Entity* entity, const Vector2& targetPos, float deltaTime)
{
    Vector2 direction = targetPos - entity->getPosition();
    float distance = Distance(entity->getPosition(), targetPos);

    if (distance > 1.0f) {
        Vector2 normal = Normalize(direction);
        float speed = 100.0f * (distance / 200.0f);
        speed = std::max(speed, 20.0f);
        entity->setVelocity(normal * speed);
    }
    else {
        entity->setVelocity(Vector2(0, 0));
    }
}

void PhysicalManager::moveToTargetDOD(int i, Vector2 pos, float deltaTime)
{
	Vector2 direction = pos - EntityManager::entityPositions[i];

    float distance = Distance(EntityManager::entityPositions[i], pos);

    if (distance > 1.0f) {
        Vector2 normal = Normalize(direction);
        float speed = 100.0f * (distance / 200.0f);
        speed = std::max(speed, 20.0f);
        EntityManager::entityVelocities[i] = normal * speed;
    }
    else {
		EntityManager::entityVelocities[i] = Vector2(0,0);
    }
}

collision PhysicalManager::find_colliion(Vector2 posA, float radiusA, Vector2 posB, float radiusB)
{
    collision result;

    float distance = Distance(posA, posB);

    if (distance < radiusA + radiusB) {
		result.depth = (radiusA + radiusB) - distance;
		result.normal = Normalize(posB - posA);
    }

    return result;
}

void PhysicalManager::resolve_collisionOOP(collision col, Entity* entityA, Entity* entityB)
{
    Vector2 correction = col.normal * col.depth * 0.5f;

    if (!entityA->isStatic()) {
        entityA->setPosition(entityA->getPosition() - correction);
    }
    if (!entityB->isStatic()) {
        entityB->setPosition(entityB->getPosition() + correction);
    }
}

void PhysicalManager::resolve_collisionDOD(collision col,int i,int j)
{
    Vector2 correction = col.normal * col.depth * 0.5f;

    if (!EntityManager::entityStatic[i]) {
		EntityManager::entityPositions[i] = EntityManager::entityPositions[i] - correction;
    }
    if (!EntityManager::entityStatic[j]) {
        EntityManager::entityPositions[j] = EntityManager::entityPositions[j] + correction;
    }
}