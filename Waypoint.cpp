#include "stdafx.h"

#include "Waypoint.h"


Waypoint::Waypoint(WaypointType type):
box_(NULL),
type_(type)
{
}

void Waypoint::SetBox(Box* box)
{
	sf::Color inColor;
	sf::Color outColor;
	if(type_ == WaypointType::START)
	{
		inColor = sf::Color::Green;
		outColor = sf::Color::White;
	}
	else if(type_ == WaypointType::END)
	{
		inColor = sf::Color::Red;
		outColor = sf::Color::Black;
	}

	box_ = box;
	int x, y;
	float width, height;

	box->GetCoordinates(x, y, width, height);
	
	float widthPercent = width * 10 / 100;
	float heightPercent = height * 10 / 100;
	float inThickness = 2.0f;
	float outThickness = 2.0f;

	cross1_ = sf::Shape::Line(x + widthPercent, y + heightPercent,
							    x + width - widthPercent, y + height - heightPercent,
								inThickness, 
								inColor, 
								outThickness,
								outColor);

	cross2_ = sf::Shape::Line(x + widthPercent, y + height - heightPercent,
			                    x + width - widthPercent, y + heightPercent,
								inThickness, 
								inColor, 
								outThickness, 
								outColor);
}

void Waypoint::Render(sf::RenderTarget& rt) const
{
	if(box_ != NULL)
	{
		rt.Draw(cross1_);
		rt.Draw(cross2_);
	}
}
