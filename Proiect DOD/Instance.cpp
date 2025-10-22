#include "Instance.h"

Instance::Instance()
{
	this->rect.x = this->position.x;
	this->rect.y = this->position.y;

	this->rect.h = this->size.y;
	this->rect.w = this->size.x;
}

Instance::Instance(Vector2 _position, Vector2 _size, float _rotation)
{
	this->position = _position;
	this->size = _size;
	this->rotation = _rotation;

	this->rect.x = _position.x;
	this->rect.y = _position.y;
	this->rect.w = _size.x;
	this->rect.h = _size.y;
}

void Instance::update()
{
}

void Instance::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(renderer, &this->rect);
}
