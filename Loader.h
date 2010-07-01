#pragma once

#include "PathManipuler.h"

class ImageManager;
class MaterialManager;
class Grid;

class Loader
{
	PathManipuler pathManipuler;
	fs::path tile_dir;
	
public:
	Loader();
	ImageManager LoadImages();
	MaterialManager LoadMaterials(const ImageManager& imgMgr, const fs::path& mat_file_name ) const;
	Grid LoadGrid(const MaterialManager& matMgr, const fs::path& grid_file_name) const;

};
