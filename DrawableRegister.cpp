#include "stdafx.h"

#include "DrawableRegister.h"
#include "Grid.h"
#include "WaypointManager.h"
#include "Arrow.h"

void DrawableRegister::AddStatic(sf::Drawable& obj)
{
	staticObj.push_back(&obj);
}

void DrawableRegister::AddTemp(sf::Drawable& obj)
{
	tempObj.push_back(&obj);
}

void DrawableRegister::AddTemp(std::vector<Arrow>& drawables)
{
	BOOST_FOREACH(sf::Drawable& d, drawables)
	{
		tempObj.push_back(&d);
	}
}

void DrawableRegister::AddStatic(Grid& grid)
{
	for(int y = 0 ; y < grid.GetNbRow() ; y++)
	{
		for(int x = 0 ; x < grid.GetNbCol() ; x++)
		{
			AddStatic( grid.GetBoxByRank(x, y) );
		}
	}
}

void DrawableRegister::AddTemp(WaypointManager& waypointMgr)
{
	AddTemp(waypointMgr.GetStartPoint());
	AddTemp(waypointMgr.GetEndPoint());
	AddTemp(waypointMgr.GetArrows());
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

void DrawableRegister::ClearTemp()
{
	tempObj.clear();
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

