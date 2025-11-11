#include "PhysicsManager.h"

void PhysicalManager::Update(float deltaTime, bool isDOD)
{
    if (!isDOD) {
        for (int i = 0; i < EntityManager::entityCount; i++) {
            if (EntityManager::entityArray[i] != nullptr) {
                if (EntityManager::entityArray[i]->isStatic() == false) {

                    EntityManager::entityArray[i]->update(deltaTime);

                    //PhysicalManager::moveToTargetOOP(EntityManager::entityArray[i], Vector2(1280 / 2, 1080 / 2), deltaTime);

                    for (int j = i + 1; j < EntityManager::entityCount; j++) {
                        if (EntityManager::entityArray[j] != nullptr and EntityManager::entityArray[i] != EntityManager::entityArray[j]) {
                            if (EntityManager::entityArray[j]->isStatic() == false) {
                                collision col = PhysicalManager::find_colliion(EntityManager::entityArray[i]->getPosition().x, EntityManager::entityArray[i]->getPosition().y, EntityManager::entityArray[i]->GetRadius(),
                                    EntityManager::entityArray[j]->getPosition().x, EntityManager::entityArray[j]->getPosition().y, EntityManager::entityArray[j]->GetRadius());
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

                //PhysicalManager::moveToTargetDOD(i, 1280 / 2, 1080 /2, deltaTime);

                for (int j = i + 1; j < EntityManager::entityCount; j++) {
                    if (!EntityManager::entityStatic[j] and i != j) {
                        collision col = PhysicalManager::find_colliion(EntityManager::entityPositionsX[i], EntityManager::entityPositionsY[i], EntityManager::entityRadius[i],
                            EntityManager::entityPositionsX[j], EntityManager::entityPositionsY[j], EntityManager::entityRadius[j]);
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
        EntityManager::entityPositionsX[i] = EntityManager::entityPositionsX[i] + (EntityManager::entityVelocitiesX[i] * deltaTime);
        EntityManager::entityPositionsY[i] = EntityManager::entityPositionsY[i] + (EntityManager::entityVelocitiesY[i] * deltaTime);
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

void PhysicalManager::moveToTargetDOD(int i, float posx, float posy, float deltaTime)
{
    float directionx = posx - EntityManager::entityPositionsX[i];
    float directiony = posy - EntityManager::entityPositionsY[i];

    float distance = Distance(Vector2(EntityManager::entityPositionsX[i], EntityManager::entityPositionsY[i]), Vector2(posx, posy));

    if (distance > 1.0f) {
        Vector2 normal = Normalize(Vector2(directionx, directiony));
        float speed = 100.0f * (distance / 200.0f);
        speed = std::max(speed, 20.0f);
        EntityManager::entityVelocitiesX[i] = normal.x * speed;
        EntityManager::entityVelocitiesY[i] = normal.y * speed;
    }
    else {
        EntityManager::entityVelocitiesX[i] = 0;
        EntityManager::entityVelocitiesY[i] = 0;
    }
}

collision PhysicalManager::find_colliion(float posAx,float posAy, float radiusA, float posBx, float posBy, float radiusB)
{
    collision result;

    float distance = Distance(Vector2(posAx, posAy), Vector2(posBx, posBy));

    if (distance < radiusA + radiusB) {
		result.depth = (radiusA + radiusB) - distance;
		result.normal = Normalize(Vector2(posBx - posAx, posBy - posAy));
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
		EntityManager::entityPositionsX[i] -= correction.x;
		EntityManager::entityPositionsY[i] -= correction.y;
    }
    if (!EntityManager::entityStatic[j]) {
		EntityManager::entityPositionsX[j] += correction.x;
		EntityManager::entityPositionsY[j] += correction.y;
    }
}