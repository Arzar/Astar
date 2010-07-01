#include "stdafx.h"

#include "DrawableRegister.h"
#include "Grid.h"
#include "WaypointManager.h"

void DrawableRegister::AddStatic(sf::Drawable& obj)
{
	staticObj.push_back(&obj);
}

void DrawableRegister::AddTemp(sf::Drawable& obj)
{
	tempObj.push_back(&obj);
}

void DrawableRegister::AddStatic(Grid& grid)
{
	for(int j = 0 ; j < grid.GetNbCol() ; j++)
	{
		for(int i = 0 ; i < grid.GetNbRow() ; i++)
		{
			AddStatic( grid.GetBoxByNumber(i, j) );
		}
	}
}

void DrawableRegister::AddTemp(WaypointManager& waypointMgr)
{
	AddTemp(waypointMgr.GetStartPoint());
	AddTemp(waypointMgr.GetEndPoint());
}

void DrawableRegister::RemoveStatic(sf::Drawable& obj)
{
	std::vector<sf::Drawable*>::iterator it = 
		std::find(staticObj.begin(), staticObj.end(), &obj);

	if(it != staticObj.end())
	{
		std::swap(*it, staticObj.back());
		staticObj.resize(staticObj.size() - 1);
	}
}

void DrawableRegister::RemoveTemp(sf::Drawable& obj)
{
	std::vector<sf::Drawable*>::iterator it 
		= std::find(tempObj.begin(), tempObj.end(), &obj);

	if(it != tempObj.end())
	{
		std::swap(*it, tempObj.back());
		tempObj.resize(tempObj.size() - 1);
	}
}

void DrawableRegister::DrawStatic(sf::RenderTarget& App)
{
	for(unsigned int i = 0 ; i < staticObj.size() ; i++)
	{
		App.Draw(*staticObj[i]);
	}
}

void DrawableRegister::DrawTemp(sf::RenderTarget& App)
{
	for(unsigned int i = 0 ; i < tempObj.size() ; i++)
	{
		App.Draw(*tempObj[i]);
	}
}

