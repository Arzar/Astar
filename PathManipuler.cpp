#include "stdafx.h"

#include "PathManipuler.h"


std::vector<fs::path> PathManipuler::FindDirectories(const std::string& searched_dir_name) const
{
	std::vector<fs::path> matches;
	fs::recursive_directory_iterator it(root_path);
	fs::recursive_directory_iterator end;

	for(; it != end ; it++)
	{
		if(fs::is_directory(*it))
		{
			const std::string& dir_name = it->path().filename().string();
			if(dir_name == searched_dir_name)
				matches.push_back(*it);
		}
	}
	return matches;
}

fs::path PathManipuler::FindDirectory(const std::string& searched_dir_name) const
{
	fs::recursive_directory_iterator it(root_path);
	fs::recursive_directory_iterator end;

	for(; it != end ; it++)
	{
		if(fs::is_directory(*it))
		{
			const std::string& dir_name = it->path().filename().string();
			if(dir_name == searched_dir_name)
				return *it;
		}
	}
	return root_path;
}
	
	
std::vector<fs::path> PathManipuler::FindFiles(const fs::path& search_path, const std::string& searched_extension) const
{
	std::vector<fs::path> matches;
	fs::recursive_directory_iterator it(search_path);
	fs::recursive_directory_iterator end;

	for(; it != end ; it++)
	{
		if(fs::is_regular_file(*it))
		{
			std::string file_name = it->path().filename().string();
			std::string extension = it->path().extension().string();
			if(extension == searched_extension)
				matches.push_back(*it);
		}
	}

	return matches;
}

