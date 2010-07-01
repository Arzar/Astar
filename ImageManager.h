#pragma once


class ImageManager
{
	
	std::map<std::string, sf::Image> pool;
	typedef std::map<std::string, sf::Image>::iterator PoolIt;
	typedef std::map<std::string, sf::Image>::const_iterator cPoolIt;

public:
	void Add(const fs::path& image_path);
	const sf::Image* Get(const std::string& image_name) const;
	
};

