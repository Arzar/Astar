#pragma once

#include "Waypoint.h"
#include "Arrow.h"
#include "GraphSolver.h"

class Grid;

class WaypointManager
{
	Grid* grid_;
	GraphSolver solver_;
	Waypoint startPoint_;
	Waypoint endPoint_;
	std::vector<Arrow> arrows_;

	WaypointManager();
	WaypointManager(const WaypointManager&);

public:

	WaypointManager(Grid* grid);
	std::vector<Arrow>& GetArrows();
	Waypoint& GetStartPoint();
	Waypoint& GetEndPoint();
	void AddStartPoint(float x, float y);
	void AddEndPoint(float x, float y);

	void WaypointManager::FindPath();

};