#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "Material.h"

class Box : public sf::Drawable
{
private:
	sf::Sprite _sprite;
	Material _material;

	float width_;
	float height_;
	int x_;
	int y_;

public:
	void InitDisplay(int posX, int posY, int width, int height);

	void BindMaterial(const Material& material);

	
	const Material& GetMaterial() const
	{
		return _material;
	}
	
	Material& GetMaterial()
	{
		return _material;
	}

	virtual void Render(sf::RenderTarget& rt) const
	{
		rt.Draw(_sprite);
	}

	void GetCoordinates(int& x, int& y, float& width, float& height)
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
	}
	//
	
};

