#include "stdafx.h"

#include "SFMLMath.h"
#include <cmath>

#define M_PI       3.14159265358979323846f

namespace sf
{
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return sqrt( (p2.x - p1.x)*(p2.x - p1.x) +  (p2.y - p1.y)*(p2.y - p1.y) );
	}


	float deg2rad(float degree)
	{
		return M_PI * (degree) / 180.0f; 
	}

	float rad2deg(float rad)
	{
		return 180.0f * rad / M_PI; 
	}
};