#include "Instance.h"

Instance::Instance(Vector2 _position, float _radius, int _id)
{
	this->id = _id;
	this->position = _position;
	this->radius = _radius;
}

Vector2 Instance::getPosition() const
{
	return this->position;
}

float Instance::GetRadius() const
{
	return this->radius;
}

void Instance::setPosition(const Vector2 pos)
{
	this->position = pos;
}