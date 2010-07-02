#pragma once

#include "Box.h"
#include "Waypoint.h"

class Grid
{
	float width_, height_;
	int nbRow_, nbCol_;
	std::vector<Box> box_;
		
	Grid();
	
public:
	
	Grid(int nbRow, int nbCol, int widthScreen, int heightScreen);

	Box& GetBoxByLocation(float x, float y)
	{
		float widthBox = width_ / nbCol_;
		float heightBox = height_ / nbRow_;

		int x2 = static_cast<int>(x / widthBox);
		int y2 = static_cast<int>(y / heightBox);
		return GetBoxByRank(x2, y2);
	}

	Box& GetBoxByRank(int x, int y)
	{
		return box_[y * nbCol_ + x];
	}

	Box& GetBoxByNumber(int nb)
	{
		return box_[nb];
	}
	
	const Box& GetBoxByNumber(int l, int c) const
	{
		return box_[c * nbCol_ + l];
	}

	int GetNbRow() const
	{
		return nbRow_;
	}

	int GetNbCol() const
	{
		return nbCol_;
	}

	void InitDisplay(int width, int height);

	int Lin(int l, int c);
};