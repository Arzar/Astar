#include "stdafx.h"

#include "Loader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "ImageManager.h"
#include "Material.h"
#include "Grid.h"


Loader::Loader():pathManipuler()
{
	tile_dir = pathManipuler.FindDirectory("tile");
}


ImageManager Loader::LoadImages()
{
	ImageManager imMgr;
	std::vector<fs::path> image_files = pathManipuler.FindFiles(tile_dir, ".jpg");

	BOOST_FOREACH(const fs::path& p, image_files)
	{
		imMgr.Add(p);
	}
		
	return imMgr;
}



MaterialManager Loader::LoadMaterials(const ImageManager& imgMgr, const fs::path& mat_file_name) const
{
	MaterialManager matMgr;
	
	fs::path math_path = pathManipuler.FindDirectory("material");
	fs::path mat_file = math_path / mat_file_name;
	
	std::ifstream file(mat_file.string().c_str());
	if(file)
	{
		std::string s;
		while(std::getline(file, s))
		{
			char short_name_material;
			std::string name_material, name_image;
			float speed_factor;

			std::stringstream ss;
			ss << s;
			if(ss >> name_material >> short_name_material >> speed_factor >> name_image)
			{
				const sf::Image* image = imgMgr.Get(name_image);
				if(image != NULL)
				{
					Material m(name_material, short_name_material, speed_factor, image);
					matMgr.Add(m);
				}
			}
		}
	}
	
	return matMgr;
}

Grid Loader::LoadGrid(const MaterialManager& matMgr, const fs::path& grid_file_name, int widthscreen, int heightScreen) const
{
	fs::path grid_path = pathManipuler.FindDirectory("grid");
	fs::path grid_file = grid_path / grid_file_name;

	std::ifstream file(grid_file.string().c_str());
	if(file)
	{
		std::string s;
		std::getline(file, s);

		int nbCol, nbRow = 0;
		std::stringstream ss;
	    ss << s;
		if(ss >> nbCol >> nbRow)
		{
			Grid grid(nbCol, nbRow, widthscreen, heightScreen);

			int y = 0;
			while(std::getline(file, s) && (y < nbRow))
			{

				std::stringstream ss;
				ss << s;
				for(int x = 0 ; x < nbCol ; x++)
				{
					char mat;
					ss >> mat;
					Box& box = grid.GetBoxByRank(x, y);
					box.BindMaterial(matMgr.GetByShortName(mat));
				}
				y++;
			}
			return grid;
		}

		
		/*
		while(std::getline(file, s))
		{
			std::string name_material, name_image;
			float speed_factor;

			std::stringstream ss;
			ss << s;
			if(ss >> name_material >> speed_factor >> name_image)
			{
				const sf::Image* image = imgMgr.Get(name_image);
				if(image != NULL)
				{
					Material m(speed_factor, image);
					matMgr.Add(name_material, m);
				}
			}
		}
		*/
	}
	return Grid(0, 0, 0, 0);

}
