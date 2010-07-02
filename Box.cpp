#include "stdafx.h"

#include "Box.h"

Box::Box(int number, int posX, int posY, int width, int height):
number_(number),
width_((float)width),
height_((float)height),
x_(posX),
y_(posY)
{
	_sprite.SetPosition((float)posX, (float)posY);
}

void Box::BindMaterial(const Material& material)
{
	_material = material;
	_sprite.SetImage(*material.GetImage());

	sf::Vector2f size = _sprite.GetSize();

	float scaleX = width_ / size.x;
	float scaleY = height_ / size.y;

	_sprite.Scale(scaleX, scaleY);

}

const Material& Box::GetMaterial() const
{
	return _material;
}
	
Material& Box::GetMaterial()
{
	return _material;
}

void Box::Render(sf::RenderTarget& rt) const
{
	rt.Draw(_sprite);
}

void Box::GetCoordinates(int& x, int& y, float& width, float& height)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}

float Box::GetSpeedFactor()
{
	return _material.GetSpeedFactor();
}

int Box::GetNumber()
{
	return number_;
}

sf::Vector2f Box::GetCenter() const
{
	return sf::Vector2f(x_ + width_ / 2.0f, y_ + height_ / 2.0f);
}