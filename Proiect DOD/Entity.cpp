#include "Entity.h"

Entity::Entity(Vector2 _position, Vector2 _size, float _rotation)
	: Instance(_position, _size, _rotation)
{
	std::cout << this->rect.x;
}

void Entity::render(SDL_Renderer* renderer)
{
	if (this->shape == "rectangle")
	{
		Instance::render(renderer);
	}
	else if (this->shape == "circle"){
		// idk
	}
}

