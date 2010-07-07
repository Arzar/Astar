#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>


class Arrow : public sf::Drawable
{
	sf::Shape body_;
	sf::Shape leftTip_;
	sf::Shape rightTip_;

	sf::Color color_;

	Arrow();
public:
	
	Arrow(sf::Vector2f start, sf::Vector2f end, const sf::Color color);

	virtual void Render(sf::RenderTarget& rt) const ;
	virtual ~Arrow(){}
};