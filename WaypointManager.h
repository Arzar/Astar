#pragma once

#include "Waypoint.h"
#include "Arrow.h"

class Grid;

class WaypointManager
{
	Grid* grid_;
	Waypoint startPoint_;
	Waypoint endPoint_;
	Arrow arrow_;

	WaypointManager();
	WaypointManager(const WaypointManager&);

public:

	WaypointManager(Grid* grid);
	Arrow& GetArrow();
	Waypoint& GetStartPoint();
	Waypoint& GetEndPoint();
	void AddStartPoint(float x, float y);
	void AddEndPoint(float x, float y);

};