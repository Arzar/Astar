#pragma once

class Material
{
	char short_name;
	std::string name;
	float speed_factor;
	const sf::Image* image;


public:
	Material():
	speed_factor(0.0),
    image(0)
	{
	}

	Material(const std::string& name, char short_name, float speed_factor, const sf::Image* image):
	short_name(short_name),
	name(name),
	speed_factor(speed_factor),
    image(image)
	{
	}

	char GetShortName() const
	{
		return short_name;
	}

	std::string GetName() const
	{
		return name;
	}

	const sf::Image* GetImage() const
	{
		return image;
	}
};

class MaterialManager
{
	
	std::map<std::string, Material> db_material;
	std::map<char, Material> db_short_material;
	
public:
	void Add(const Material& mat)
	{
		db_material[mat.GetName()] = mat;
		db_short_material[mat.GetShortName()] = mat;
	}

	
	Material GetByName(const std::string& name) const
	{
		std::map<std::string, Material>::const_iterator it = db_material.find(name);
		if(it !=  db_material.end())
		{
			return it->second;
		}
		throw std::runtime_error("bla");
	}

	Material GetByShortName(char short_name) const
	{
		std::map<char, Material>::const_iterator it = db_short_material.find(short_name);
		if(it !=  db_short_material.end())
		{
			return it->second;
		}
		throw std::runtime_error("bla");
	}
};

/*
Material CreateMaterial(MATERIAL_TYPE mt);
*/
