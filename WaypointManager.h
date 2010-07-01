#pragma once

#include "Waypoint.h"

class Grid;

class WaypointManager
{
	Grid* grid_;
	Waypoint startPoint_;
	Waypoint endPoint_;

	WaypointManager();
	WaypointManager(const WaypointManager&);

public:

	WaypointManager(Grid* grid);
	Waypoint& GetStartPoint();
	Waypoint& GetEndPoint();
	void AddStartPoint(float x, float y);
	void AddEndPoint(float x, float y);

};