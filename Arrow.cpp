#include "stdafx.h"

#include "Arrow.h"

Arrow::Arrow()
{
}

Arrow::Arrow(sf::Vector2f start, sf::Vector2f end)
{
	float thickness = 2.0;
	float outThickness = 2.0;
	sf::Color color = sf::Color::Black;
	
	body_ = sf::Shape::Line(start, end, thickness, color, outThickness, color);

	float lengthBody = sf::distance(start, end);
	float lengthTip = lengthBody * 30.0f / 100.0f; // 30% of length
	float angle = sf::deg2rad(20.0); // 20° for the tip.

	//da calcul

	float angleRot = atan2( end.y - start.y, end.x - start.x);

	float angleRotDeg = sf::rad2deg(angleRot);

	float xArrowRefLeft = lengthBody - lengthTip * cos(angle);
	float yArrowRefLeft = lengthTip * sin(angle);

    float xArrowRefRight = xArrowRefLeft;
	float yArrowRefRight = -yArrowRefLeft;

	float xLeftTip = xArrowRefLeft * cos(angleRot) - yArrowRefLeft * sin(angleRot) + start.x;
	float yLeftTip =  xArrowRefLeft * sin(angleRot) + yArrowRefLeft * cos(angleRot) + start.y;

	float xRightTip = xArrowRefRight * cos(angleRot) - yArrowRefRight * sin(angleRot) + start.x;
	float yRightTip =  xArrowRefRight * sin(angleRot) + yArrowRefRight * cos(angleRot) + start.y;

	leftTip_ = sf::Shape::Line(end, sf::Vector2f(xLeftTip, yLeftTip), thickness, color, outThickness, color);
	rightTip_ = sf::Shape::Line(end, sf::Vector2f(xRightTip, yRightTip), thickness, color, outThickness, color);
}

void Arrow::Render(sf::RenderTarget& rt) const
{
	rt.Draw(body_);
	rt.Draw(leftTip_);
	rt.Draw(rightTip_);
}
