#include "stdafx.h"

#include "Box.h"

void Box::InitDisplay(int posX, int posY, int width, int height)
{
	x_ = posX;
	y_ = posY;
	width_ = (float)width;
	height_ = (float)height;

	_sprite.SetPosition((float)posX, (float)posY);
	sf::Vector2f size = _sprite.GetSize();

	float scaleX = (float)width / size.x;
	float scaleY = (float)height / size.y;

	_sprite.Scale(scaleX, scaleY);
}

void Box::BindMaterial(const Material& material)
{
	_material = material;
	_sprite.SetImage(*material.GetImage());
}