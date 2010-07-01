#include "stdafx.h"

#include "ImageManager.h"


void ImageManager::Add(const fs::path& image_path)
{
	std::string name = image_path.stem().string();
	sf::Image image;
	image.LoadFromFile(image_path.string());

	pool[name] = image;

}

const sf::Image* ImageManager::Get(const std::string& id) const
{
	cPoolIt image = pool.find(id);
	if(image == pool.end())
		return NULL;
	else
		return &(image->second);
}

