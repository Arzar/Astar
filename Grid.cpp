#include "stdafx.h"

#include "Grid.h"

Grid::Grid(int nbRow, int nbCol, int widthScreen, int heightScreen) : 
nbRow_(nbRow), 
nbCol_(nbCol), 
width_(0.0), 
height_(0.0)
{

	int RealScreenSize = std::min(widthScreen, heightScreen);
	width_ = (float)RealScreenSize;
	height_ = (float)RealScreenSize;

	int widthBox = RealScreenSize / nbCol_;
	int heightBox = RealScreenSize / nbRow_;

	for(int y = 0 ; y < nbRow_ ; y++)
	{
		for(int x = 0 ; x < nbCol_ ; x++)
		{
			int xBox = x * widthBox;
			int yBox = y * heightBox;

			box_.push_back(Box(y * nbCol + x, xBox, yBox, widthBox, heightBox));
	
		}
	}
}


int Grid::Lin(int x, int y)
{
	return x * nbCol_ + y;
}