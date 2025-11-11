#pragma once
#include "../Utility/Vector2.h"
#include "../Utility/SpriteData.h"
#include <SDL3/SDL.h>
#include <iostream>

class Instance
{
public:
	int id;
	Vector2 position;
	float radius = 0.0f;

public:
	Instance(Vector2 _position, float _radius,int id);

	Vector2 getPosition() const;
	float GetRadius() const;
	void setPosition(const Vector2 pos);
};