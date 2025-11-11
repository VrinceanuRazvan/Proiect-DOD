#include "Entity.h"

Entity::Entity(int _id,Vector2 _position, float _radius , bool _isStatic)
	: Instance(_position, _radius,_id)
{
	this->Static = _isStatic;
	this->velocity = Vector2(0.0f, 0.0f);
}

void Entity::update(float deltaTime)
{
	if (!this->Static) {
		this->position = this->position + (this->velocity * deltaTime);
	}
}

void Entity::setVelocity(const Vector2 vel)
{
	this->velocity = vel;
}

Vector2 Entity::getVelocity() const
{
	return this->velocity;
}

bool Entity::isStatic() const
{
	return this->Static;
}

int Entity::GetId() const
{
	return this->id;
}
