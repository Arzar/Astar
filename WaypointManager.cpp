#include "stdafx.h"

#include "WaypointManager.h"
#include "Grid.h"

WaypointManager::WaypointManager(Grid* grid):
grid_(grid),
startPoint_(WaypointType::START),
endPoint_(WaypointType::END)
{
}


Arrow& WaypointManager::GetArrow()
{
	return arrow_;
}

Waypoint& WaypointManager::GetStartPoint() 
{
	return startPoint_;
}

Waypoint& WaypointManager::GetEndPoint() 
{
	return endPoint_;
}

void WaypointManager::AddStartPoint(float x, float y)
{
	Box& box = grid_->GetBoxByLocation(x, y);
	startPoint_.SetBox(&box);
	arrow_ = Arrow(startPoint_.GetPosition(), endPoint_.GetPosition());
}

void WaypointManager::AddEndPoint(float x, float y)
{
	Box& box = grid_->GetBoxByLocation(x, y);
	endPoint_.SetBox(&box);
	arrow_ = Arrow(startPoint_.GetPosition(), endPoint_.GetPosition());
}