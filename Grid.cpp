#include "stdafx.h"

#include "Grid.h"

void Grid::InitDisplay(int widthScreen, int heightScreen)
{
	int RealScreenSize = std::min(widthScreen, heightScreen);
	width_ = (float)RealScreenSize;
	height_ = (float)RealScreenSize;

	int widthBox = RealScreenSize / nbCol_;
	int heightBox = RealScreenSize / nbRow_;


	for(int j = 0 ; j < nbCol_ ; j++)
	{
		for(int i = 0 ; i < nbRow_ ; i++)
		{
			Box& box = GetBoxByNumber(i, j);
			int xBox = j * widthBox;
			int yBox = i * heightBox;

			box.InitDisplay(xBox, yBox, widthBox, heightBox);
		}
	}
}