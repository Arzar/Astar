#include "stdafx.h"

#include "WaypointManager.h"
#include "Grid.h"
#include "Path.h"

WaypointManager::WaypointManager(Grid* grid):
grid_(grid),
solver_(*grid),
startPoint_(WaypointType::START),
endPoint_(WaypointType::END)
{
}

std::vector<Arrow>& WaypointManager::GetArrows()
{
	return arrows_;
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
	arrows_.clear();
	Box& box = grid_->GetBoxByLocation(x, y);
	startPoint_.SetBox(&box);
}

void WaypointManager::AddEndPoint(float x, float y)
{
	arrows_.clear();
	Box& box = grid_->GetBoxByLocation(x, y);
	endPoint_.SetBox(&box);
}

void WaypointManager::FindPath()
{
	sf::Vector2f startCoord = startPoint_.GetPosition();
	sf::Vector2f endCoord = endPoint_.GetPosition();

	int startIndex = grid_->GetBoxByLocation(startCoord.x, startCoord.y).GetNumber();
	int endIndex = grid_->GetBoxByLocation(endCoord.x, endCoord.y).GetNumber();
	
	//Path path = solver_.DijkstraSolve(startIndex, endIndex);
	Path path = solver_.AstarSolve(startIndex, endIndex);
	arrows_.clear();

	
	BOOST_FOREACH(Path::Edge edge, path.GetAllPath())
	{
		sf::Vector2f startArrow = grid_->GetBoxByNumber(edge.first).GetCenter();
		sf::Vector2f endArrow = grid_->GetBoxByNumber(edge.second).GetCenter();
		arrows_.push_back(Arrow(startArrow, endArrow, sf::Color::Red));
	}

	BOOST_FOREACH(Path::Edge edge, path.GetShortestPath())
	{
		sf::Vector2f startArrow = grid_->GetBoxByNumber(edge.first).GetCenter();
		sf::Vector2f endArrow = grid_->GetBoxByNumber(edge.second).GetCenter();
		arrows_.push_back(Arrow(startArrow, endArrow, sf::Color::Black));
	}
	
	/*
	for(unsigned int i1 = 0, i2 = 1 ; i2 < vertex.size() ; i1++, i2++)
	{
		sf::Vector2f startArrow = grid_->GetBoxByNumber(vertex[i1]).GetCenter();
		sf::Vector2f endArrow = grid_->GetBoxByNumber(vertex[i2]).GetCenter();
		arrows_.push_back(Arrow(startArrow, endArrow));
	}*/
}