#pragma once

class Grid;
class WaypointManager;
class Arrow;

class DrawableRegister
{
private:
	std::vector<sf::Drawable*> staticObj;
	std::vector<sf::Drawable*> tempObj;

public:

	void AddStatic(sf::Drawable& obj);
	void AddTemp(sf::Drawable& obj);

	void AddTemp(std::vector<Arrow>& drawables);

	void AddStatic(WaypointManager& waypointMgr);
	void AddTemp(WaypointManager& waypointMgr);
	
	void AddStatic(Grid& grid);
	void AddTemp(Grid& grid);

	void RemoveStatic(sf::Drawable& obj);
	void RemoveTemp(sf::Drawable& obj);

	void DrawStatic(sf::RenderTarget& App);
	void DrawTemp(sf::RenderTarget& App);

	void DrawableRegister::ClearTemp();
};