#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System//Vector2.hpp>

#include "Box.h"

enum WaypointType
{
	START,
	END
};

class Waypoint : public sf::Drawable
{
	WaypointType type_;

	sf::Shape cross1_;
	sf::Shape cross2_;

	sf::Vector2f pos_;

	Waypoint();

public:

	Waypoint(WaypointType type);

	void SetBox(Box* box);
	virtual sf::Vector2f GetPosition();

	virtual void Render(sf::RenderTarget& rt) const ;
};