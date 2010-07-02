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
	int number_;
	Box();
public:
	Box(int number, int posX, int posY, int width, int height);
	virtual ~Box(){}
	
	void BindMaterial(const Material& material);
	const Material& GetMaterial() const ;
	Material& GetMaterial();
	virtual void Render(sf::RenderTarget& rt) const ;
	void GetCoordinates(int& x, int& y, float& width, float& height);
	virtual sf::Vector2f GetCenter() const;
	float GetSpeedFactor();
	int GetNumber();

	
};

