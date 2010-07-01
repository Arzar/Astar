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
	Grid(int nbRow, int nbCol) : 
	nbRow_(nbRow), 
	nbCol_(nbCol), 
	box_(nbRow * nbCol), 
	width_(0.0), 
	height_(0.0)
	{
	}

	Box& GetBoxByLocation(float x, float y)
	{
		float widthBox = width_ / nbCol_;
		float heightBox = height_ / nbRow_;

		int c = static_cast<int>(x / widthBox);
		int l = static_cast<int>(y / heightBox);
		return GetBoxByNumber(l, c);
	}

	Box& GetBoxByNumber(int l, int c)
	{
		return box_[c * nbCol_ + l];
	}

	const Box& GetBoxByNumber(int l, int c) const
	{
		return box_[c * nbCol_ + l];
	}


	/*
	Box& operator()(int i, int j)
	{
	
	}

	const Box& operator()(int i, int j) const
	{
		return box[j * nbCol + i];
	}
	*/

	int GetNbRow() const
	{
		return nbRow_;
	}

	int GetNbCol() const
	{
		return nbCol_;
	}

	void InitDisplay(int width, int height);
};