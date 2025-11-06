#pragma once
#include "Instance.h"

class Entity : public Instance
{
private :
	Vector2 velocity;

	bool Static;
public:
	Entity(Vector2 _position, float _radius = 10, bool _isStatic = false);

	void update(float deltaTime);

	void setVelocity(const Vector2 vel);
	Vector2 getVelocity() const;
	bool isStatic() const;
};

